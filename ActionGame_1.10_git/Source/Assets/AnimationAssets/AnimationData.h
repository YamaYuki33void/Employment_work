#pragma once
#include "../../Manager/FbxManager/FbxMyFormatManager.h"
#include "../../System/DirectX/DirectX_Simple.h"
#include "KeyFreamData.h"

class AnimationData{
public:
	// Getter
	const std::unordered_map<std::string, std::vector<DirectX::SimpleMath::Matrix>>& GetAnimationMatrixList()const;
	const int GetMaxFream()const;
	const std::string& GetRootBoneName()const;
	const KeyFreamData& GetKeyFreamData()const;

private:
	// �A�j���[�V�����f�[�^�̎��o��
	void Animation_Data_Ejection();

private:
	// �A�j���[�V�����{�[���f�[�^
	std::unordered_map<std::string, std::vector<DirectX::SimpleMath::Matrix>> m_AnimationMatrixList;

	// �ő�t���[����
	int m_MaxFream;

	// ���[�g�{�[��
	std::string m_RootBoneName;

	// KeyFream
	std::unique_ptr<class KeyFreamData> m_pKeyFreamData;

	// Fbx��̓f�[�^
	std::unique_ptr<Model::FbxMyFormatManager>m_pFbxManger;

public:
	AnimationData(const char* myformatanimfile);
	~AnimationData() {};
};

