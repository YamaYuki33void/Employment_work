#include "ModelAssets.h"
#include "../../System/CSVLoader/csv.h"

void ModelAssets::LoadInitalize(){

	{
		// StativMeshÇÃì«Ç›çûÇ›
		std::string assetsname, modelpath, texpath;

		io::CSVReader<3> skMeshSeet("AssetsData/Model/StaticMesh/StaticMesh_Seet.csv");
		skMeshSeet.read_header(io::ignore_extra_column, "AssetsName", "ModelPath", "TexPath");

		while (skMeshSeet.read_row(assetsname, modelpath, texpath)) {
			AddStaticModel(assetsname, modelpath, texpath);
		}
	}

	{
		// SkeletalMeshÇÃì«Ç›çûÇ›
		std::string assetsname, modelpath, texpath, skeletonname;

		io::CSVReader<4> skMeshSeet("AssetsData/Model/SkeletalMesh/SkeletalMesh_Seet.csv");
		skMeshSeet.read_header(io::ignore_extra_column, "AssetsName", "ModelPath", "TexPath","SkeletonName");

		while (skMeshSeet.read_row(assetsname, modelpath, texpath, skeletonname)) {
			AddSkeletalModel(assetsname, modelpath, texpath, skeletonname);
		}
	}
}

StaticMeshData* ModelAssets::GetStaticMeshData(const std::string& assetsname){

	if (auto iter = m_pStaticMeshDataList.find(assetsname) != m_pStaticMeshDataList.end()) {
		return m_pStaticMeshDataList.at(assetsname).get();
	}
	else {
		MessageBoxA(nullptr, std::string(assetsname + "  notData").c_str(), nullptr, MB_OK);
		return nullptr;
	}
}

SkeletalMeshData* ModelAssets::GetSkeletalMeshData(const std::string& assetsname){

	if (auto iter = m_pSkeletalMeshDataList.find(assetsname) != m_pSkeletalMeshDataList.end()) {
		return m_pSkeletalMeshDataList.at(assetsname).get();
	}
	else {
		MessageBoxA(nullptr, std::string(assetsname + "  notData").c_str(), nullptr, MB_OK);
		return nullptr;
	}
}

void ModelAssets::AddStaticModel(const std::string& assetsname, const std::string& modelpath, const std::string& texpath){
	m_pStaticMeshDataList.emplace(assetsname, std::make_unique<StaticMeshData>(modelpath.c_str(), texpath.c_str()));
}

void ModelAssets::AddSkeletalModel(const std::string& assetsname, const std::string& modelpath, const std::string& texpath, const std::string& skeletonname){
	m_pSkeletalMeshDataList.emplace(assetsname, std::make_unique<SkeletalMeshData>(modelpath.c_str(), texpath.c_str(), skeletonname.c_str()));
}
