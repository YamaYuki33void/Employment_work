#pragma once
#include "../ModelComponent/ModelComponent.h"
#include "../../../Assets/ModelAssets/SkeletalMeshData.h"

class SkeletalMeshComponent :
    public ModelComponent
{
public:
    // Getter
    const std::string& GetModelDataName()const;
    class SkeletalMeshData* GetModelData()const;
    class AnimationControllerComponent* GetAnimController()const;

    // Setter
    void SetModelData(const std::string& modelname);

public:
    void UniqeDraw()override;

private:
    // ���f���f�[�^
    std::unique_ptr<class SkeletalMeshData> m_pModelData;

    // ���f���f�[�^�̖��O
    std::string m_ModelDataName;

    // �A�j���[�V�����R���|�l���g
    class AnimationControllerComponent* m_pAnimControllerComponent;
    
public:
    SkeletalMeshComponent(class Actor* actor, const std::string& ComponentName = "SkeletalMesh");
    ~SkeletalMeshComponent()override {};
};

