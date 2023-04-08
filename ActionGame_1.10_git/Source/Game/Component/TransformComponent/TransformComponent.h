#pragma once
#include "../../../System/DirectX/DirectX_Simple.h"

class TransformComponent{
public:
	// �e�̐ݒ�
	void ResistParent(class TransformComponent* parenttranform);
	void RemoveParent();

	// Setter
	void SetMatrix(const DirectX::SimpleMath::Matrix& mtx);
	void SetWorldLocation(const DirectX::SimpleMath::Vector3& location);
	void SetWorldRotation(const DirectX::SimpleMath::Vector3& rotation);
	void SetWorldRotation(const DirectX::SimpleMath::Quaternion& rotation);
	
	void AddWorldOffset(const DirectX::SimpleMath::Vector3& offset);
	void AddWorldRotation(const DirectX::SimpleMath::Vector3& offset);
	void AddLocalOffset(const DirectX::SimpleMath::Vector3& offset);
	void AddLocalRotation(const DirectX::SimpleMath::Vector3& offset);
	
	// Getter
	const DirectX::SimpleMath::Matrix& GetWorldMatrix() const;
	const DirectX::SimpleMath::Vector3& GetWorldLocation()const;
	const DirectX::SimpleMath::Vector3& GetWorldRotation()const;
	const DirectX::SimpleMath::Quaternion& GetWorldQtRotation()const;

	const DirectX::SimpleMath::Matrix& GetLocalMatrix() const;
	const DirectX::SimpleMath::Vector3& GetLocalLocation()const;
	const DirectX::SimpleMath::Vector3& GetLocalRotation()const;
	
private:
	// Qt��pos����s����쐬����
	void CreateMatrix();

	// �ċA�֐�
	void ParentChildCalculation(const DirectX::SimpleMath::Matrix& mtx);
	
private:
	// ���[�J���E���[���h�s��
	DirectX::SimpleMath::Matrix     m_LocalMat;
	DirectX::SimpleMath::Matrix     m_WorldMat;
	DirectX::SimpleMath::Quaternion m_Qt;
	DirectX::SimpleMath::Vector3    m_Pos;

	// �e��Transform
	class TransformComponent* m_pParentTransform;
	std::vector<TransformComponent*> m_pChildTransformList;

public:
	TransformComponent();
	~TransformComponent() {};
};

