#include "AnimationLerp.h"
#include "../../ComponentList.h"
#include "../../../../System/FpsControl/FpsControl.h"

using namespace DirectX::SimpleMath;

void AnimationLerp::StartLerp(const std::unordered_map<std::string, DirectX::SimpleMath::Matrix>* nextbone, float lerptime){

	// スタート行列を入れる
	for (auto&& animbone : m_pSkeletonData->GetBoneList()) {
		m_StartBone.at(animbone.first) = animbone.second.GetAnimationMatrix();
	}

	// 次の行列を入れる
	for (auto&& animbone : m_pSkeletonData->GetBoneList()) {
		m_NextBone.at(animbone.first) = nextbone->at(animbone.first);
	}

	m_IsLerp = true;
	m_Lerptime = lerptime;
	m_Clump = 0.0f;
	m_ElapsedTime = 0.0f;
}

bool AnimationLerp::LerpUpdate(){

	if (m_IsLerp) {

		for (auto&& bone : m_pSkeletonData->GetBoneList()) {
			const auto& mat1 = m_StartBone.at(bone.first);
			const auto& mat2 = m_NextBone.at(bone.first);

			const auto& veclerp = Vector3::Lerp(mat1.Translation(), mat2.Translation(), m_Clump);
			const auto& qtslerp = Quaternion::Slerp(Quaternion::CreateFromRotationMatrix(mat1), Quaternion::CreateFromRotationMatrix(mat2), m_Clump);

			// 球面線形補間してなめらかに補完する
			auto blendmat = Matrix::CreateFromQuaternion(qtslerp);
			blendmat._41 = veclerp.x; blendmat._42 = veclerp.y; blendmat._43 = veclerp.z;

			m_LerpBone.at(bone.first) = blendmat;
		}

		m_ElapsedTime += FpsControl::GetInstance()->GetDeletaTime();
		m_Clump = m_ElapsedTime / m_Lerptime;
		if (1.0f < m_Clump) {
			m_Clump = 1.0f;
			m_IsLerp = false;
		}

		// ボーンの適応
		m_pSkeletonData->SetAnimationBone(&m_LerpBone);

		return m_IsLerp;
	}
	else {
		return m_IsLerp;
	}
}

AnimationLerp::AnimationLerp(SkeletonData* skdata):
	m_IsLerp(false),
	m_Clump(0.0f),
	m_ElapsedTime(0.0f),
	m_pSkeletonData(skdata)
{
	/// キャッシュを作っておく
	for (auto&& animbone : skdata->GetBoneList()) {
		m_StartBone[animbone.first];
		m_NextBone[animbone.first];
		m_LerpBone[animbone.first];
	}
}
