#include "StaticMeshComponent.h"
#include "../../../Assets/ModelAssets/ModelAssets.h"

StaticMeshData* StaticMeshComponent::GetMeshData() const{
	return m_pModelData.get();
}

void StaticMeshComponent::SetModelData(const std::string& modelname){

	// モデルデータを動的に確保しAssetsデータからディープコピーする
	if (m_pModelData != nullptr) {
		m_pModelData.reset();
	}

	m_pModelData = std::make_unique<StaticMeshData>(*ModelAssets::GetInstance()->GetStaticMeshData(modelname));
}

void StaticMeshComponent::UniqeDraw() {

	if (m_pModelData != nullptr) {
		m_pModelData->Draw(GetTransformComponent()->GetWorldMatrix());
	}
}

StaticMeshComponent::StaticMeshComponent(Actor* actor, const std::string& ComponentName):
	ModelComponent(actor,ComponentName)
{
}
