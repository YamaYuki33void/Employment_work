#include "AnimationData.h"

const std::unordered_map<std::string, std::vector<DirectX::SimpleMath::Matrix>>& AnimationData::GetAnimationMatrixList() const{
	return m_AnimationMatrixList;
}
const int AnimationData::GetMaxFream() const{
	return m_MaxFream;
}
const std::string& AnimationData::GetRootBoneName() const{
	return m_RootBoneName;
}

const KeyFreamData& AnimationData::GetKeyFreamData() const{
	return *m_pKeyFreamData;
}

void AnimationData::Animation_Data_Ejection(){

	// アニメーションデータのコピー
	for (auto masterbone : m_pFbxManger->GetAnimationData().GetAnimationMatrix()) {
		for (auto&& mat : masterbone.second) {
			m_AnimationMatrixList[masterbone.first].emplace_back(mat);
		}
	}

	// RootBoneの名前を取得
	m_RootBoneName = m_pFbxManger->GetAnimationData().GetRootBoneName();

	// アニメーション最大フレーム数を取得
	m_MaxFream = static_cast<int>(m_pFbxManger->GetAnimationData().GetAnimationMatrix().begin()->second.size());
}

AnimationData::AnimationData(const char* myformatanimfile):
	m_pFbxManger(std::make_unique<Model::FbxMyFormatManager>())
{
	// Animationバイナリファイルの読み込み
	m_pFbxManger->AnimationLoad(myformatanimfile);

	// アニメーションデータの取り出し
	Animation_Data_Ejection();

	// FbxManagerの解放
	m_pFbxManger.reset();

	// keyFreamnの作成
	m_pKeyFreamData = std::make_unique<KeyFreamData>(this);

}
