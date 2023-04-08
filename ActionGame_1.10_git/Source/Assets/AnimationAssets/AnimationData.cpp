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

	// �A�j���[�V�����f�[�^�̃R�s�[
	for (auto masterbone : m_pFbxManger->GetAnimationData().GetAnimationMatrix()) {
		for (auto&& mat : masterbone.second) {
			m_AnimationMatrixList[masterbone.first].emplace_back(mat);
		}
	}

	// RootBone�̖��O���擾
	m_RootBoneName = m_pFbxManger->GetAnimationData().GetRootBoneName();

	// �A�j���[�V�����ő�t���[�������擾
	m_MaxFream = static_cast<int>(m_pFbxManger->GetAnimationData().GetAnimationMatrix().begin()->second.size());
}

AnimationData::AnimationData(const char* myformatanimfile):
	m_pFbxManger(std::make_unique<Model::FbxMyFormatManager>())
{
	// Animation�o�C�i���t�@�C���̓ǂݍ���
	m_pFbxManger->AnimationLoad(myformatanimfile);

	// �A�j���[�V�����f�[�^�̎��o��
	Animation_Data_Ejection();

	// FbxManager�̉��
	m_pFbxManger.reset();

	// keyFreamn�̍쐬
	m_pKeyFreamData = std::make_unique<KeyFreamData>(this);

}
