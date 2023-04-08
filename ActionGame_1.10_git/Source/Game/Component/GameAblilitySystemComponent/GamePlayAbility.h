#pragma once
#include "../../../System/DirectX/DirectX_Simple.h"

//---------------------------------------------------
//	�A�r���e�B���N���X
//---------------------------------------------------

// Tag�\����
struct AbilityTag {
	std::vector<std::string> AbilityTags;            // �A�r���e�B�̖��O
	std::vector<std::string> ActivationOwnedTags;    // ���s���ɕt�^����閼�O
	std::vector<std::string> ActivationRequiredTags; // ���̃^�O�������Ă��Ȃ��Ǝ��s�ł��Ȃ�
	std::vector<std::string> ActivationBlockedTags;  // ���̃^�O�������Ă���ꍇ���s�o���Ȃ�
};


class GamePlayAbility{
public:
	// �A�r���e�B�̊J�n
	void ActivAbility();

	// �A�r���e�B�̏I��
	void EndAbility();

	// �ݒ�p�̃^�O�̒ǉ�
	void AddAbilityTags(const std::string& name);
	void AddActrivateOwnerTags(const std::string& name);
	void AddActrivateBlockedTags(const std::string& name);
	void AddActrivateRequiredTags(const std::string& name);

	// �ݒ�p�̃^�O�̍폜
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
	// �ݒ�p�̃A�r���e�B�^�O
	AbilityTag m_SettingAbilityTag;

	// Owner
	class GameplayAbilitySystemComponent* m_pOwnerGASComponent;

public:
	GamePlayAbility(class GameplayAbilitySystemComponent* Comp);
	virtual~GamePlayAbility() {};
};

