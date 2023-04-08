#include "GamePlayAbility.h"
#include "GameplayAbilitySystemComponent.h"

void GamePlayAbility::ActivAbility(){

	// OwnerTagの動的追加
	m_pOwnerGASComponent->AddGameplayTags(m_SettingAbilityTag.ActivationOwnedTags);

	// 継承先のアビリティ開始
	UniqueActivAbility();
}

void GamePlayAbility::EndAbility(){

	// OwnerTagの動的削除
	m_pOwnerGASComponent->RemoveGameplayTags(m_SettingAbilityTag.ActivationOwnedTags);

	// 継承先のアビリティ終了
	UniqueEndAbility();
}

void GamePlayAbility::AddAbilityTags(const std::string& name){

	// 同名タグ追加禁止
	AddTagProhibit(m_SettingAbilityTag.AbilityTags, name);
}

void GamePlayAbility::AddActrivateOwnerTags(const std::string& name){

	// 同名タグ追加禁止
	AddTagProhibit(m_SettingAbilityTag.ActivationOwnedTags, name);

}

void GamePlayAbility::AddActrivateBlockedTags(const std::string& name){

	// 同名タグ追加禁止
	AddTagProhibit(m_SettingAbilityTag.ActivationBlockedTags, name);
}

void GamePlayAbility::AddActrivateRequiredTags(const std::string& name){

	// 同名タグ追加禁止
	AddTagProhibit(m_SettingAbilityTag.ActivationRequiredTags, name);
}

void GamePlayAbility::RemoveActrivateBlockedTags(const std::string& name){

	auto iter = std::find(m_SettingAbilityTag.ActivationBlockedTags.begin(), m_SettingAbilityTag.ActivationBlockedTags.end(), name);
	if (iter != m_SettingAbilityTag.ActivationBlockedTags.end()) {
		m_SettingAbilityTag.ActivationBlockedTags.erase(iter);
	}
}

void GamePlayAbility::RemoveActrivateRequiredTags(const std::string& name){

	auto iter = std::find(m_SettingAbilityTag.ActivationRequiredTags.begin(), m_SettingAbilityTag.ActivationRequiredTags.end(), name);
	if (iter != m_SettingAbilityTag.ActivationRequiredTags.end()) {
		m_SettingAbilityTag.ActivationRequiredTags.erase(iter);
	}
}

GameplayAbilitySystemComponent& GamePlayAbility::GetGASComponent(){
	return *m_pOwnerGASComponent;
}

const std::vector<std::string>& GamePlayAbility::GetAbilityTags() const{
	return m_SettingAbilityTag.AbilityTags;
}

const std::vector<std::string>& GamePlayAbility::GetActrivateOwnerTags() const{
	return m_SettingAbilityTag.ActivationOwnedTags;
}

const std::vector<std::string>& GamePlayAbility::GetActrivateBlockedTags() const{
	return m_SettingAbilityTag.ActivationBlockedTags;
}

const std::vector<std::string>& GamePlayAbility::GetActrivateRequiredTags() const{
	return m_SettingAbilityTag.ActivationRequiredTags;
}

void GamePlayAbility::AddTagProhibit(std::vector<std::string>& tag, const std::string& name){

	// 同名禁止処理
	auto iter = std::find(tag.begin(), tag.end(), name);
	if (iter == tag.end()) {
		tag.emplace_back(name);
	}
}

GamePlayAbility::GamePlayAbility(GameplayAbilitySystemComponent* Comp):
	m_pOwnerGASComponent(Comp)
{
}
