#include "AnimationAssets.h"
#include "../../System/CSVLoader/csv.h"
#include <thread>

void AnimationAssets::LoadInitalize(){

	// スレッド変数
	std::vector<std::thread> anim_th;
	std::string skeletonname, assetsname, modelpath;

	// Animationの読み込み
	io::CSVReader<3> skMeshSeet("AssetsData/Animation/Animation_Seet.csv");
	skMeshSeet.read_header(io::ignore_extra_column, "SkeletonName", "AssetsName", "ModelPath");

	while (skMeshSeet.read_row(skeletonname, assetsname, modelpath)) {
		anim_th.emplace_back(&AnimationAssets::AddAnimation, this, skeletonname, assetsname, modelpath);
	}

	for (auto&& wait_th : anim_th) {
		wait_th.join();
	}
}

const std::unordered_map<std::string, std::unique_ptr<class AnimationData>>* AnimationAssets::GetSkeletonToAnimData(const std::string& skeletonname) const{
	
#ifdef _DEBUG

	// スケルトンの名前の検索
	if (m_AnimationList.count(skeletonname) != 0) {
		return &m_AnimationList.at(skeletonname);
	}
	else {
		MessageBoxA(nullptr, std::string(skeletonname + "  NotSkeletonName").c_str(), nullptr, MB_OK);
	}

#else

	return &m_AnimationList.at(skeletonname);

#endif
}

const std::unique_ptr<class AnimationData>* AnimationAssets::GetAnimData(const std::string& skeletonname, const std::string& animdata) const{

	const auto* animlist = GetSkeletonToAnimData(skeletonname);

#ifdef _DEBUG

	if (animlist->count(animdata) != 0) {
		return &animlist->at(animdata);
	}
	else {
		MessageBoxA(nullptr, std::string(skeletonname + " " + animdata + "  not animname").c_str(), nullptr, MB_OK);
	}
#else
	return &animlist->at(animdata);

#endif
	return nullptr;
}

void AnimationAssets::AddAnimation(const std::string& skeletonname, const std::string& assetsname, const std::string& animationpath){
	m_AnimationList[skeletonname][assetsname] = std::make_unique<AnimationData>(animationpath.c_str());
}

