#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "../../Game/Component/TransformComponent/TransformComponent.h"

//-----------------------------------------------------------------
//	モデルの骨を扱うデータ
//-----------------------------------------------------------------
class OneBone {
public:

	// Getter
	class TransformComponent* GetTransformComponent();
	const DirectX::SimpleMath::Matrix& GetAnsMatrix()const;
	const DirectX::SimpleMath::Matrix& GetAnimationMatrix()const;
	const int GetBoneIndex()const;

	// Ownerの設定
	void SetOwner(class SkeletonData* data);
	void SetAnimationMatrix(const DirectX::SimpleMath::Matrix& mat);

private:
	// BoneTransfrom
	class TransformComponent m_BoneMatrix;

	// AnimationBone
	DirectX::SimpleMath::Matrix m_AnimationMatrix;

	// OffsetMatrix
	DirectX::SimpleMath::Matrix m_OffsetMatrix;

	// Boneナンバー
	int m_BoneIndex;

	// OwnerData
	class SkeletonData* m_pOwnerSkeletonData;

public:
	OneBone(const DirectX::SimpleMath::Matrix& offsetmat, const DirectX::SimpleMath::Matrix& animmat, int boneindex, class SkeletonData* data);
	~OneBone() {};
};

class SkeletonData{
public:
	// Bone定数バッファデータの更新
	void UpdateCBufferSkeleton();

	// Getter
	class SkeletalMeshData& GetSkeletalMeshData()const;
	const std::unordered_map <std::string, class OneBone>& GetBoneList()const;
	const std::string& GetSkeletonName()const;
	class OneBone& GetBone(const std::string& bonename);

	// Ownerの設定
	void SetOwner(class SkeletalMeshData* data);
	void SetAnimationBone(const std::unordered_map <std::string, DirectX::SimpleMath::Matrix>* animbonelist);

private:
	// Boneデータの取り出し
	void Bone_Data_Ejection();

private:
	// ボーン行列格納用のコンスタントバッファ
	struct CBufferBoneMatrix {
		DirectX::XMFLOAT4X4  mBoneMatrix[100];
	};

	// BoneをGpuに送るための定数バッファ
	class SimpleConstantBuffer<CBufferBoneMatrix> m_CBufferSkeleton;

	// Boneリスト
	std::unordered_map<std::string, class OneBone> m_BoneList;

	// スケルトンの名前
	std::string m_SkeletonName;

	// skeletonOwnerポインタ
	class SkeletalMeshData* m_pOwnerSkeletonMeshData;

public:
	SkeletonData(class SkeletalMeshData* data, const std::string& skeletonname);
	SkeletonData() {};
	~SkeletonData() {};
};

