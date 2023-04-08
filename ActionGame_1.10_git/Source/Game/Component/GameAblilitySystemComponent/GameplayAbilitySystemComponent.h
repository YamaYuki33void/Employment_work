#pragma once
#include "../../../System/DirectX/DirectX_Simple.h"
#include "../Component.h"
#include "GamePlayAbility.h"
#include <thread>

//-----------------------------------------------------
//  文字列でアビリティの管理をし、
//  タグでアビリティを実行するコンポーネント
//-----------------------------------------------------

class GameplayAbilitySystemComponent :
    public Component
{
public:
    // Abilityの実行
    void TryActiveAbilitiesbyTag(const std::string& abilityname);

    // Abilityの追加
    void AddGameplayAbility(class GamePlayAbility* ability);

    // GameplayTagの追加
    void AddGameplayTags(const std::string& name);
    void AddGameplayTags(const std::vector<std::string>& names);

    // GameplayTagの削除
    void RemoveGameplayTags(const std::string& name);
    void RemoveGameplayTags(const std::vector<std::string>& names);

    // GameTagの追加待機
    void WaitGamePlayTagAdd(const std::string& waittagname, std::function<void()> addedfunc);

    // Tagの検索
    bool AbilityTagSearch(const std::string& searchname);

    // Getter
    const std::vector<std::string>& GetAbilityTags()const;

private:
    void UniqeUpdate()override;

    // タグの選別
    bool ActivationBlockedSorting(class GamePlayAbility* ability);
    bool ActivationRequiredSorting(class GamePlayAbility* ability);

    void ActivateWaitTagsPlay();

private:
    // GameplayTag一覧
    std::vector<std::unique_ptr<class GamePlayAbility>>m_GameplayAbilityList;

    // 現在のアビリティタグ
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

