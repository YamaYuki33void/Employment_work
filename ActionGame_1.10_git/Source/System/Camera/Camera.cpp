#include "Camera.h"
#include "../Window/Window.h"
#include "../DirectX/DirectX_WorldTransform.h"

using namespace DirectX;

void Camera::Initialize(float nearclip, float farclip, float fov, float width, float height, DirectX::XMFLOAT3 eye, DirectX::XMFLOAT3 lookat, DirectX::XMFLOAT3 up){
	SetProjection(nearclip, farclip, fov, width, height);
	SetCamera(eye, lookat, up);
}

void Camera::CreateCameraMatrix() {
	XMVECTOR Eye = XMVectorSet(m_Eye.x, m_Eye.y, m_Eye.z, 0.0f);
	XMVECTOR At =  XMVectorSet(m_Lookat.x, m_Lookat.y, m_Lookat.z, 0.0f);
	XMVECTOR Up =  XMVectorSet(m_Up.x, m_Up.y, m_Up.z, 0.0f);

	XMMATRIX camera;
	camera = XMMatrixLookAtLH(Eye, At, Up);
	
	DirectX::XMStoreFloat4x4(&m_Camera, camera);
}

void Camera::CreateProjectionMatrix() {
	XMMATRIX projection;
	projection = XMMatrixPerspectiveFovLH(m_Fov, m_Aspect, m_near, m_far);
	XMStoreFloat4x4(&m_Projection, projection);
}

void Camera::Transform_Update(const DirectX::XMFLOAT3& eye, const  DirectX::XMFLOAT3& lookat, const  DirectX::XMFLOAT3& up){
	
	SetCamera(eye, lookat, up);

	XMFLOAT4X4 mtx;
	// プロジェクション変換行列取得
	mtx =GetProjectionMatrix();
	WorldTransformation::GetInstance()->SetTransform(WorldTransformation::TYPE::PROJECTION, mtx);
	// ビュー変換行列を取得
	mtx = GetCameraMatrix();
	WorldTransformation::GetInstance()->SetTransform(WorldTransformation::TYPE::VIEW, mtx);
}

void Camera::Transform_Update(){

	XMFLOAT4X4 mtx;
	// プロジェクション変換行列取得
	mtx = GetProjectionMatrix();
	WorldTransformation::GetInstance()->SetTransform(WorldTransformation::TYPE::PROJECTION, mtx);
	// ビュー変換行列を取得
	mtx = GetCameraMatrix();
	WorldTransformation::GetInstance()->SetTransform(WorldTransformation::TYPE::VIEW, mtx);
}


void Camera::SetProjection(float nearclip, float farclip, float fov, float width, float height){
	SetNear(nearclip);
	SetFar(farclip);
	SetFov(fov);
	SetAspect(width, height);
	CreateProjectionMatrix();
}

void Camera::SetCamera(const XMFLOAT3& eye, const XMFLOAT3& lookat, const XMFLOAT3& up){
	SetEye(eye);
	SetLookat(lookat);
	SetUp(up);
	CreateCameraMatrix();
	CreateProjectionMatrix();
}

void Camera::SetEye(const XMFLOAT3& eye){
	m_Eye = eye;
}

void Camera::SetLookat(const XMFLOAT3& lookat){
	m_Lookat = lookat;
}

void Camera::SetUp(const XMFLOAT3& up){
	m_Up = up;
}

void Camera::SetNear(float nearclip){
	m_near = nearclip;
}

void Camera::SetFar(float farclip){
	m_far = farclip;
}

void Camera::SetFov(float fov){
	m_Fov = fov;
}

void Camera::SetAspect(float width, float height){
	m_Aspect = width / height;
}

const XMFLOAT4X4& Camera::GetCameraMatrix() const{
	return m_Camera;
}

const XMFLOAT4X4& Camera::GetProjectionMatrix() const{
	return m_Projection;
}

const XMFLOAT3& Camera::GetEye() const{
	return m_Eye;
}

const XMFLOAT3& Camera::GetLookat() const{
	return m_Lookat;
}

const XMFLOAT3& Camera::GetUp() const{
	return m_Up;
}

const float Camera::GetFov() const{
	return m_Fov;
}

Camera::Camera():
	m_Camera(),
	m_Projection(),
	m_Eye(),
	m_Lookat(),
	m_Up(),
	m_near(),
	m_Aspect(),
	m_Fov(),
	m_far()
{

	// カメラの初期化
	XMFLOAT3 eye   (0, 90, -500);
	XMFLOAT3 lookat(0, 90, 0);
	XMFLOAT3 up    (0, 1, 0);

	Initialize(
		10.0f,							                  // ニアクリップ
		20000.0f,						                  // ファークリップ
		XM_PI / 5.0f,					                  // 視野角
		(float)Window::GetInstance()->GetScreanWidth(),   // スクリーン幅
		(float)Window::GetInstance()->GetScreanHeight(),  // スクリーンの高さ
		eye, lookat, up);

}
