#pragma once
#include "../DirectX/DirectX_Simple.h"
#include "../Designpattern/Singleton.h"

class Camera
	:public Singleton<Camera>
{
public:
	friend Singleton<Camera>;

	// ����������
	void Initialize(float nearclip, float farclip, float fov, float width, float height,
		 DirectX::XMFLOAT3 eye, DirectX::XMFLOAT3 lookat, DirectX::XMFLOAT3 up);

	// �J�����s����쐬
	void CreateCameraMatrix();

	// �v���W�F�N�V�����s����쐬
	void CreateProjectionMatrix();

	// �J�����̍X�V
	void Transform_Update(const DirectX::XMFLOAT3& eye, const  DirectX::XMFLOAT3& lookat, const  DirectX::XMFLOAT3& up);
	void Transform_Update();

	//Getter Setter//
	void  SetProjection(float nearclip, float farclip, float fov, float width, float height);
	void  SetCamera(const DirectX::XMFLOAT3& eye, const  DirectX::XMFLOAT3& lookat, const  DirectX::XMFLOAT3& up);
	void  SetEye(const DirectX::XMFLOAT3& eye);
	void  SetLookat(const DirectX::XMFLOAT3& lookat);
	void  SetUp(const DirectX::XMFLOAT3& up);
	void  SetNear(float nearclip);
	void  SetFar(float farclip);
	void  SetFov(float fov);
	void  SetAspect(float width, float height);
	const DirectX::XMFLOAT4X4& GetCameraMatrix()const;
	const DirectX::XMFLOAT4X4& GetProjectionMatrix()const;
	const DirectX::XMFLOAT3& GetEye()const;
	const DirectX::XMFLOAT3& GetLookat()const;
	const DirectX::XMFLOAT3& GetUp()const;
	const float GetFov()const;

private:
	DirectX::XMFLOAT4X4	m_Camera, m_Projection;
	DirectX::XMFLOAT3	m_Eye, m_Lookat, m_Up;
	float m_near, m_Aspect, m_Fov, m_far;

private:
	Camera();
	~Camera()override {};
};