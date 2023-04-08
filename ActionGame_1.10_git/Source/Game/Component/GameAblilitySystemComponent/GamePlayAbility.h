#pragma once
#include "../../../System/DirectX/DirectX_Simple.h"

//---------------------------------------------------
//	アビリティ基底クラス
//---------------------------------------------------

// Tag構造体
struct AbilityTag {
	std::vector<std::string> AbilityTags;            // アビリティの名前
	std::vector<std::string> ActivationOwnedTags;    // 実行中に付与される名前
	std::vector<std::string> ActivationRequiredTags; // このタグを持っていないと実行できない
	std::vector<std::string> ActivationBlockedTags;  // このタグを持っている場合実行出来ない
};


class GamePlayAbility{
public:
	// アビリティの開始
	void ActivAbility();

	// アビリティの終了
	void EndAbility();

	// 設定用のタグの追加
	void AddAbilityTags(const std::string& name);
	void AddActrivateOwnerTags(const std::string& name);
	void AddActrivateBlockedTags(const std::string& name);
	void AddActrivateRequiredTags(const std::string& name);

	// 設定用のタグの削除
	void RemoveActrivateBlockedTags(const std::string& name);
	void RemoveActrivateRequiredTags(const std::string& name);

	// Getter
	class GameplayAbilitySystemComponent& GetGASComponent();
	const std::vector<std::string>& GetAbilityTags()const;
	const std::vector<std::string>& GetActrivateOwnerTags()const;
	const std::vector<std::string>& GetActrivateBlockedTags()const;
	const std::vector<std::string>& GetActrivateRequiredTags()const;
	
private:
	virtual void UniqueActivAbility() = 0;
	virtual void UniqueEndAbility() = 0;

	void AddTagProhibit(std::vector<std::string>& tag, const std::string& name);

private:
	// 設定用のアビリティタグ
	AbilityTag m_SettingAbilityTag;

	// Owner
	class GameplayAbilitySystemComponent* m_pOwnerGASComponent;

public:
	GamePlayAbility(class GameplayAbilitySystemComponent* Comp);
	virtual~GamePlayAbility() {};
};

