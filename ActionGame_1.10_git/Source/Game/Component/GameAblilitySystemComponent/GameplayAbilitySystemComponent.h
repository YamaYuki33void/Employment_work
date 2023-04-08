#pragma once
#include "../../../System/DirectX/DirectX_Simple.h"
#include "../Component.h"
#include "GamePlayAbility.h"
#include <thread>

//-----------------------------------------------------
//  ������ŃA�r���e�B�̊Ǘ������A
//  �^�O�ŃA�r���e�B�����s����R���|�[�l���g
//-----------------------------------------------------

class GameplayAbilitySystemComponent :
    public Component
{
public:
    // Ability�̎��s
    void TryActiveAbilitiesbyTag(const std::string& abilityname);

    // Ability�̒ǉ�
    void AddGameplayAbility(class GamePlayAbility* ability);

    // GameplayTag�̒ǉ�
    void AddGameplayTags(const std::string& name);
    void AddGameplayTags(const std::vector<std::string>& names);

    // GameplayTag�̍폜
    void RemoveGameplayTags(const std::string& name);
    void RemoveGameplayTags(const std::vector<std::string>& names);

    // GameTag�̒ǉ��ҋ@
    void WaitGamePlayTagAdd(const std::string& waittagname, std::function<void()> addedfunc);

    // Tag�̌���
    bool AbilityTagSearch(const std::string& searchname);

    // Getter
    const std::vector<std::string>& GetAbilityTags()const;

private:
    void UniqeUpdate()override;

    // �^�O�̑I��
    bool ActivationBlockedSorting(class GamePlayAbility* ability);
    bool ActivationRequiredSorting(class GamePlayAbility* ability);

    void ActivateWaitTagsPlay();

private:
    // GameplayTag�ꗗ
    std::vector<std::unique_ptr<class GamePlayAbility>>m_GameplayAbilityList;

    // ���݂̃A�r���e�B�^�O
    static std::vector<std::string> m_AbilityTags;

    struct WaitTagFunction {
        std::string waittagname;
        std::function<void()> waitfunction;
        bool isActivated;
    };
    std::vector<WaitTagFunction> m_WaitTagFunctionList;

public:
    GameplayAbilitySystemComponent(class Actor* actor, const std::string& ComponentName = "GASComponent");
    ~GameplayAbilitySystemComponent()override {};
};

