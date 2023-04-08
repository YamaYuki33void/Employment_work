#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "../InterfaceAssets.h"
#include "StaticMeshData.h"
#include "SkeletalMeshData.h"

class ModelAssets :
	public InterfaceAssets, public Singleton<ModelAssets>
{
public:
	friend Singleton<ModelAssets>;

public:
	// ���񃍁[�h
	void LoadInitalize()override;

	// Getter
	class StaticMeshData* GetStaticMeshData(const std::string& assetsname);
	class SkeletalMeshData* GetSkeletalMeshData(const std::string& assetsname);

private:
	void AddStaticModel(const std::string& assetsname, const std::string& modelpath, const std::string& texpath);
	void AddSkeletalModel(const std::string& assetsname, const std::string& modelpath, const std::string& texpath, const std::string& skeletonname);

private:
	// Static���f�����X�g
	std::unordered_map<std::string, std::unique_ptr<class StaticMeshData>> m_pStaticMeshDataList;

	// Skeletal���f�����X�g
	std::unordered_map<std::string, std::unique_ptr<class SkeletalMeshData>> m_pSkeletalMeshDataList;
private:
	ModelAssets() {};
	~ModelAssets() {};
};


