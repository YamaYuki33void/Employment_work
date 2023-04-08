#include "TransformComponent.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void TransformComponent::ResistParent(TransformComponent* parenttranform){

	// ���ɐe������΂��̊֐��𔲂���
	if (m_pParentTransform != nullptr) {
		return;
	}

	// �I�������̂����g�ł���΁A���̊֐��𔲂���
	if (this == parenttranform) {
		return;
	}

	// �I�������̂����ɐe�Ȃ炱�̊֐��𔲂���
	if (m_pParentTransform == parenttranform) {
		return;
	}

	// �I���������̂������̎q�ł���΂��̊֐��𔲂���
	auto iter = std::find(m_pChildTransformList.begin(), m_pChildTransformList.end(), parenttranform);
	if (iter != m_pChildTransformList.end()) {
		return;
	}

	// �����̐e�|�C���^�ɃZ�b�g����
	m_pParentTransform = parenttranform;

	// �e�̎q�����X�g�Ɏ�����ǉ����Ă��炤
	parenttranform->m_pChildTransformList.emplace_back(this);
	
	// ���݂̈ʒu�֌W�����񂾂܂ܐe�q�֌W������
	auto Localmat = m_LocalMat * m_pParentTransform->m_WorldMat.Invert();
	m_Qt = Quaternion::CreateFromRotationMatrix(Localmat);
	m_Pos = Localmat.Translation();

	CreateMatrix();

	// �e�q�֌W���v�Z���Ȃ���
	m_pParentTransform->ParentChildCalculation(Matrix::Identity);
}

void TransformComponent::RemoveParent(){

	// �؂藣���e�����Ȃ���΂��̊֐��𔲂���
	if (m_pParentTransform == nullptr) {
		return;
	}

	// �e�̃��X�g���玩�g������
	auto& parentchildlist = m_pParentTransform->m_pChildTransformList;
	auto iter = std::find(parentchildlist.begin(), parentchildlist.end(), this);
	if (iter != parentchildlist.end()) {

		// �����ƃf�[�^�����ւ��č폜����
		std::iter_swap(iter, parentchildlist.end() - 1);
		parentchildlist.pop_back();
	}

	m_Qt = Quaternion::CreateFromRotationMatrix(m_WorldMat);
	m_Pos = m_WorldMat.Translation();
	m_pParentTransform = nullptr;

	CreateMatrix();
	ParentChildCalculation(Matrix::Identity);
}

void TransformComponent::SetMatrix(const DirectX::SimpleMath::Matrix& mtx){

	// �s����ړ��E��]�E�X�P�[���ɕ�������
	m_Pos = { mtx._41,mtx._42,mtx._43 };

	m_Qt = Quaternion::CreateFromRotationMatrix(mtx);

	CreateMatrix();
	ParentChildCalculation(Matrix::Identity);
}

void TransformComponent::SetWorldLocation(const DirectX::SimpleMath::Vector3& location){

	if (m_pParentTransform != nullptr) {
		auto worldpos = location;
		m_WorldMat._41 = worldpos.x; 	m_WorldMat._42 = worldpos.y; 	m_WorldMat._43 = worldpos.z;
		m_Pos = (m_WorldMat * m_pParentTransform->m_WorldMat.Invert()).Translation();
	}
	else {
		m_Pos = location;
	}

	CreateMatrix();
	ParentChildCalculation(Matrix::Identity);
}

void TransformComponent::SetWorldRotation(const DirectX::SimpleMath::Vector3& rotation){

	// offset����Qt���쐬
	Vector3 radian = { XMConvertToRadians(rotation.x),XMConvertToRadians(rotation.y) ,XMConvertToRadians(rotation.z) };
	Quaternion offsetqt = Quaternion::CreateFromYawPitchRoll(radian);

	if (m_pParentTransform != nullptr) {
		auto localrot = Matrix::CreateFromQuaternion(offsetqt) * m_pParentTransform->m_WorldMat.Invert();
		m_Qt = Quaternion::CreateFromRotationMatrix(localrot);
	}
	else {
		m_Qt = offsetqt;
	}

	CreateMatrix();
	ParentChildCalculation(Matrix::Identity);
}

void TransformComponent::SetWorldRotation(const DirectX::SimpleMath::Quaternion& rotation){

	if (m_pParentTransform != nullptr) {

		auto localrot = Matrix::CreateFromQuaternion(rotation) * m_pParentTransform->m_WorldMat.Invert();
		m_Qt = Quaternion::CreateFromRotationMatrix(localrot);
	}
	else {
		m_Qt = rotation;
	}

	CreateMatrix();
	ParentChildCalculation(Matrix::Identity);
}

void TransformComponent::AddWorldOffset(const DirectX::SimpleMath::Vector3& offset){

	if (m_pParentTransform != nullptr) {
		auto worldpos = m_WorldMat.Translation() + offset;
		m_WorldMat._41 = worldpos.x; 	m_WorldMat._42 = worldpos.y; 	m_WorldMat._43 = worldpos.z;
		m_Pos = (m_WorldMat * m_pParentTransform->m_WorldMat.Invert()).Translation();
	}
	else {
		m_Pos = m_Pos + offset;
	}

	CreateMatrix();
	ParentChildCalculation(Matrix::Identity);
}

void TransformComponent::AddWorldRotation(const DirectX::SimpleMath::Vector3& offset){

	// offset����Qt���쐬
	Vector3 radian = { XMConvertToRadians(offset.x),XMConvertToRadians(offset.y) ,XMConvertToRadians(offset.z) };
	Quaternion offsetqt = Quaternion::CreateFromYawPitchRoll(radian);
	
	if (m_pParentTransform != nullptr) {
		auto worldqt = Quaternion::CreateFromRotationMatrix(m_WorldMat);
		auto resultmat = Matrix::CreateFromQuaternion(worldqt * offsetqt);
		auto localrot = resultmat * m_pParentTransform->m_WorldMat.Invert();
		m_Qt = Quaternion::CreateFromRotationMatrix(localrot);
	}
	else {
		m_Qt = m_Qt * offsetqt;
	}

	CreateMatrix();
	ParentChildCalculation(Matrix::Identity);
}

void TransformComponent::AddLocalOffset(const DirectX::SimpleMath::Vector3& offset){

	Vector3 resultpos = m_WorldMat.Translation();

	// x��
	resultpos.x += (m_WorldMat._11 * offset.x);
	resultpos.y += (m_WorldMat._12 * offset.x);
	resultpos.z += (m_WorldMat._13 * offset.x);
	// y��
	resultpos.x += (m_WorldMat._21 * offset.y);
	resultpos.y += (m_WorldMat._22 * offset.y);
	resultpos.z += (m_WorldMat._23 * offset.y);
	//�@z��
	resultpos.x += (m_WorldMat._31 * offset.z);
	resultpos.y += (m_WorldMat._32 * offset.z);
	resultpos.z += (m_WorldMat._33 * offset.z);

	if (m_pParentTransform != nullptr) {
		m_WorldMat._41 = resultpos.x; m_WorldMat._42 = resultpos.y; m_WorldMat._43 = resultpos.z;
		m_Pos = (m_WorldMat * m_pParentTransform->m_WorldMat.Invert()).Translation();
	}
	else {
		m_Pos = resultpos;
	}

	CreateMatrix();
	ParentChildCalculation(Matrix::Identity);
}

void TransformComponent::AddLocalRotation(const DirectX::SimpleMath::Vector3& offset){

	Vector3 radian = { XMConvertToRadians(offset.x),XMConvertToRadians(offset.y) ,XMConvertToRadians(offset.z) };
	auto offsetqt = Quaternion::Identity;
	auto qtx = Quaternion::CreateFromAxisAngle(Vector3(m_WorldMat._11, m_WorldMat._12, m_WorldMat._13), radian.x);
	auto qty = Quaternion::CreateFromAxisAngle(Vector3(m_WorldMat._21, m_WorldMat._22, m_WorldMat._23), radian.y);
	auto qtz = Quaternion::CreateFromAxisAngle(Vector3(m_WorldMat._31, m_WorldMat._32, m_WorldMat._33), radian.z);
	offsetqt = qtz * qtx * qty;

	if (m_pParentTransform != nullptr) {
		auto worldqt = Quaternion::CreateFromRotationMatrix(m_WorldMat);
		auto resultmat = Matrix::CreateFromQuaternion(worldqt * offsetqt);
		auto localrot = resultmat * m_pParentTransform->m_WorldMat.Invert();
		m_Qt = Quaternion::CreateFromRotationMatrix(localrot);
	}
	else {
		m_Qt = m_Qt * offsetqt;
	}

	CreateMatrix();
	ParentChildCalculation(Matrix::Identity);

}

const DirectX::SimpleMath::Matrix& TransformComponent::GetWorldMatrix() const{
	return m_WorldMat;
}

const DirectX::SimpleMath::Matrix& TransformComponent::GetLocalMatrix() const{
	return m_LocalMat;
}

const DirectX::SimpleMath::Vector3& TransformComponent::GetLocalLocation() const{
	return m_LocalMat.Translation();
}

const DirectX::SimpleMath::Vector3& TransformComponent::GetLocalRotation() const{
	return m_LocalMat.ToEuler();
}

const DirectX::SimpleMath::Vector3& TransformComponent::GetWorldLocation() const{
	return m_WorldMat.Translation();
}

const DirectX::SimpleMath::Vector3& TransformComponent::GetWorldRotation() const{
	return m_WorldMat.ToEuler();
}

const DirectX::SimpleMath::Quaternion& TransformComponent::GetWorldQtRotation() const{
	return Quaternion::CreateFromRotationMatrix(m_WorldMat);
}

void TransformComponent::CreateMatrix(){

	// �s��̍쐬
	m_LocalMat = Matrix::CreateFromQuaternion(m_Qt) * Matrix::CreateTranslation(m_Pos);
}

void TransformComponent::ParentChildCalculation(const DirectX::SimpleMath::Matrix& mtx){

	if (m_pParentTransform != nullptr) {
		m_WorldMat = m_LocalMat * m_pParentTransform->m_WorldMat;
	}
	else {
		m_WorldMat = m_LocalMat;
	}

	// �ċA�֐��łǂ�ǂ�e�q�֌W�œ������Ă���
	for (auto&& child : m_pChildTransformList) {
		child->ParentChildCalculation(m_WorldMat);
	}
}

TransformComponent::TransformComponent():
	m_LocalMat(Matrix::Identity),
	m_WorldMat(Matrix::Identity),
	m_pParentTransform(nullptr),
	m_Pos(),
	m_Qt()
{
}
