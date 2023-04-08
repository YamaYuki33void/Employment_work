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
	// アニメーションデータの取り出し
	void Animation_Data_Ejection();

private:
	// アニメーションボーンデータ
	std::unordered_map<std::string, std::vector<DirectX::SimpleMath::Matrix>> m_AnimationMatrixList;

	// 最大フレーム数
	int m_MaxFream;

	// ルートボーン
	std::string m_RootBoneName;

	// KeyFream
	std::unique_ptr<class KeyFreamData> m_pKeyFreamData;

	// Fbx解析データ
	std::unique_ptr<Model::FbxMyFormatManager>m_pFbxManger;

public:
	AnimationData(const char* myformatanimfile);
	~AnimationData() {};
};

