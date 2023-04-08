#pragma once
#include "../ModelComponent/ModelComponent.h"
#include "../../../Assets/ModelAssets/StaticMeshData.h"

class StaticMeshComponent :
    public ModelComponent
{
public:
    // Getter
    class StaticMeshData* GetMeshData()const;

    // Setter
    void SetModelData(const std::string& modelname);

private:
    void UniqeDraw()override;

private:
    // モデルデータ
    std::unique_ptr<class StaticMeshData> m_pModelData;

public:
    StaticMeshComponent(class Actor* actor, const std::string& ComponentName = "StaticMesh");
    ~StaticMeshComponent()override {};
};

