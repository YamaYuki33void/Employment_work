#include "GameplayAbilitySystemComponent.h"
#include <thread>

// 実体宣言
std::vector<std::string> GameplayAbilitySystemComponent::m_AbilityTags;

void GameplayAbilitySystemComponent::TryActiveAbilitiesbyTag(const std::string& abilityname){

	for (auto&& ability : m_GameplayAbilityList) {
		for (auto&& abilitynames : ability->GetAbilityTags()) {
			if (abilitynames.find(abilityname) != std::string::npos) {

				// アビリティが見つかったらBlock、Requiredのタグによって実行するか選別する

				// Tagの検索網をクリアしたやつのみアビリティを実行する
				if (ActivationBlockedSorting(ability.get()) == false && ActivationRequiredSorting(ability.get()) == false) {
					ability->ActivAbility();
					return;
				}
			}
		}
	}
}

void GameplayAbilitySystemComponent::AddGameplayAbility(GamePlayAbility* ability){
	m_GameplayAbilityList.emplace_back(std::move(ability));
}

void GameplayAbilitySystemComponent::AddGameplayTags(const std::string& name){

	// 同名禁止処理
	auto iter = std::find(m_AbilityTags.begin(), m_AbilityTags.end(),name);
	if (iter == m_AbilityTags.end()) {
		m_AbilityTags.emplace_back(name);
	}
}

void GameplayAbilitySystemComponent::AddGameplayTags(const std::vector<std::string>& names){

	// 同名禁止処理
	for (auto&& addname : names) {
		auto iter = std::find(m_AbilityTags.begin(), m_AbilityTags.end(), addname);
		if (iter == m_AbilityTags.end()) {
			m_AbilityTags.emplace_back(addname);
		}
	}
}

void GameplayAbilitySystemComponent::RemoveGameplayTags(const std::string& name){

	auto iter = std::find(m_AbilityTags.begin(), m_AbilityTags.end(), name);
	if (iter != m_AbilityTags.end()) {
		m_AbilityTags.erase(iter);
	}
}

void GameplayAbilitySystemComponent::RemoveGameplayTags(const std::vector<std::string>& names){

	for (auto&& removename : names) {
		auto iter = std::find(m_AbilityTags.begin(), m_AbilityTags.end(), removename);
		if (iter != m_AbilityTags.end()) {
			m_AbilityTags.erase(iter);
		}
	}
}

void GameplayAbilitySystemComponent::WaitGamePlayTagAdd(const std::string& waittagname, std::function<void()> addedfunc) {
	m_WaitTagFunctionList.emplace_back(GameplayAbilitySystemComponent::WaitTagFunction({ waittagname, addedfunc ,false }));
	ActivateWaitTagsPlay();
}

bool GameplayAbilitySystemComponent::AbilityTagSearch(const std::string& searchname){
	
	for (auto&& tag : m_AbilityTags) {
		if (tag.find(searchname) != std::string::npos) {
			return true;
		}
	}

	return false;
}

const std::vector<std::string>& GameplayAbilitySystemComponent::GetAbilityTags() const{
	return m_AbilityTags;
}

void GameplayAbilitySystemComponent::UniqeUpdate() {

	// 待機してるタグの処理
	ActivateWaitTagsPlay();
}

bool GameplayAbilitySystemComponent::ActivationBlockedSorting(GamePlayAbility* ability){
	
	bool isdiscover = false;

	// BlockTagを設定したアビリティが現在ののabilitytagsにあった場合Trueを返す
	for (auto&& tags : m_AbilityTags) {
		for (auto&& blocktag : ability->GetActrivateBlockedTags()) {
			if (tags.find(blocktag) != std::string::npos) {

				isdiscover = true;
				return isdiscover;
			}
			else {
				isdiscover = false;
			}
		}
	}

	return isdiscover;
}

bool GameplayAbilitySystemComponent::ActivationRequiredSorting(GamePlayAbility* ability){

	bool isdiscover = false;

	for (auto&& Requirtag : ability->GetActrivateRequiredTags()) {

		if (m_AbilityTags.empty()) {
			return true;
		}

		for (auto&& tags : m_AbilityTags) {

			//　設定したタグが見つからなかった時点でこの関数を抜ける
			if (tags.find(Requirtag) == std::string::npos) {
				isdiscover = true;
			}
			else {
				//見つけた場合次のRequireタグで検索する
				isdiscover = false;
				break;
			}
		}

		// 一つのタグが見つけれなかった場合この関数を抜ける
		if (isdiscover == true) {
			return isdiscover;
		}
	}

	return isdiscover;
}

void GameplayAbilitySystemComponent::ActivateWaitTagsPlay(){

	for (auto&& tag : m_AbilityTags) {
		for (auto&& wait : m_WaitTagFunctionList) {

			// 待機を待っている文字列の検索 
			if (tag.find(wait.waittagname) != std::string::npos) {

				if (wait.isActivated == false) {
					wait.waitfunction();
					wait.isActivated = true;
				}
			}
		}
	}

	// 待機したタグが追加され、関数が発動したらリストから削除する
	for (auto iter = m_WaitTagFunctionList.begin(); iter != m_WaitTagFunctionList.end();) {

		if ((*iter).isActivated == true) {
			iter = m_WaitTagFunctionList.erase(iter);
		}
		else {
			++iter;
		}
	}
}

GameplayAbilitySystemComponent::GameplayAbilitySystemComponent(Actor* actor, const std::string& ComponentName) :
	Component(actor, ComponentType::FuncType, ComponentName)
{
}
