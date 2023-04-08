#include "KeyFreamData.h"
#include "AnimationData.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const std::unordered_map<std::string, DirectX::SimpleMath::Matrix>& KeyFreamData::GetAnimationKeyFreamMatrix(float fream)const{
	
	for (auto&& animbone : m_pOwnerAnimationData->GetAnimationMatrixList()) {
		m_kyashMatList.at(animbone.first) = CreateLerpMatrix(animbone.first,fream);
	}

	return m_kyashMatList;
}

const std::unordered_map<std::string, DirectX::SimpleMath::Matrix>& KeyFreamData::GetRootAnimationKeyFreamMatrix(float fream) const{

	for (auto&& animbone : m_pOwnerAnimationData->GetAnimationMatrixList()) {
		Matrix animmat = CreateLerpMatrix(animbone.first, fream);
		animmat._41 -= CreateLerpMatrix(m_pOwnerAnimationData->GetRootBoneName(), fream)._41;
		animmat._43 -= CreateLerpMatrix(m_pOwnerAnimationData->GetRootBoneName(), fream)._43;

		m_kyashMatList.at(animbone.first) = animmat;
	}

	return m_kyashMatList;
}

const DirectX::SimpleMath::Vector3& KeyFreamData::GetRootMotionOffsetPos(float fream) const{

	// 最大フレームを超えたら最大フレームに補正する
	float maxfream = static_cast<float>(m_pOwnerAnimationData->GetMaxFream());
	float nowfream = fream;
	float backfream = fream - 1;

	if (maxfream - 1 < nowfream) {
		nowfream = static_cast<float>(m_pOwnerAnimationData->GetMaxFream() - 1);
	}
	if (backfream < 0) {
		backfream = static_cast<float>(0);
	}
	const auto& list = m_pOwnerAnimationData->GetAnimationMatrixList();
	const auto& backmat = list.at(m_pOwnerAnimationData->GetRootBoneName()).at(static_cast<int>(backfream)).LeftHand();
	const auto& nowmat  = list.at(m_pOwnerAnimationData->GetRootBoneName()).at(static_cast<int>(nowfream)).LeftHand();

	m_kyashVec.x = nowmat._41 - backmat._41;
	m_kyashVec.z = nowmat._43 - backmat._43;

	return m_kyashVec;
}

const DirectX::SimpleMath::Matrix& KeyFreamData::CreateLerpMatrix(const std::string& bonename,float fream)const {

	// 選択したフレームでのアニメーションデータの補間をして行列を返す
	float maxfream = static_cast<float>(m_pOwnerAnimationData->GetMaxFream());
	float inputfream = fream;
	float nextfream = fream + 1;

	// 最大フレームを超えたら最大フレームに補正する
	if (maxfream - 1 < inputfream) {
		inputfream = static_cast<float>(m_pOwnerAnimationData->GetMaxFream() - 1);
	}
	if (maxfream - 1 < nextfream) {
		nextfream = static_cast<float>(m_pOwnerAnimationData->GetMaxFream() - 1);
	}

	float clump = fream - floorf(fream);
	int backanimfream = static_cast<int>(floorf(inputfream));
	int nextanimfream = static_cast<int>(floorf(nextfream));
	
	// 0～1のクランプ値を取得する
	const auto& list = m_pOwnerAnimationData->GetAnimationMatrixList();
	m_kyashMat = Matrix::Lerp(list.at(bonename).at(backanimfream), list.at(bonename).at(nextanimfream), clump);

	return m_kyashMat;
}

KeyFreamData::KeyFreamData(AnimationData* data):
	m_pOwnerAnimationData(data)
{
	for (auto&& masterbone : data->GetAnimationMatrixList()) {
		m_kyashMatList[masterbone.first];
	}
}
