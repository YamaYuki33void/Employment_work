#include "DirectX_WorldTransform.h"
#include "DirectX_SimpleShader.h"
#include "DirectX_Simple.h"

using namespace DirectX;

void WorldTransformation::Initalize() {

	auto* device = SimepleD3D::DX11GetDevice();

	//world  view Projectionの定数バッファを作成
	bool sts = CreateConstantBuffer(device, sizeof(ConstantBufferWorld),      m_pConstantBufferWorld.GetAddressOf());
	     sts = CreateConstantBuffer(device, sizeof(ConstantBufferView),       m_pConstantBufferView.GetAddressOf());
	     sts = CreateConstantBuffer(device, sizeof(ConstantBufferProjection), m_pConstantBufferProjection.GetAddressOf());

	if (!sts) {
		MessageBox(NULL, L"CreateBuffer(constant buffer Transform) error", nullptr, MB_OK);
	}
	
}

void WorldTransformation::SetTransform(TYPE type, const XMFLOAT4X4& matrix){

	auto* devcon = SimepleD3D::DX11GetDeviceContext();


	ALIGN16 XMMATRIX mat;
	mat = DirectX::XMLoadFloat4x4(&matrix);

	switch (type) {
	case TYPE::WORLD:
		m_CBWorld.World = XMMatrixTranspose(mat);
		devcon->UpdateSubresource(m_pConstantBufferWorld.Get(), 0, nullptr, &m_CBWorld, 0, 0);
		devcon->VSSetConstantBuffers(0, 1, m_pConstantBufferWorld.GetAddressOf());
		devcon->PSSetConstantBuffers(0, 1, m_pConstantBufferWorld.GetAddressOf());
		break;

	case TYPE::VIEW:
		m_CBView.View = XMMatrixTranspose(mat);
		devcon->UpdateSubresource(m_pConstantBufferView.Get(), 0, nullptr, &m_CBView, 0, 0);
		devcon->VSSetConstantBuffers(1, 1, m_pConstantBufferView.GetAddressOf());
		devcon->PSSetConstantBuffers(1, 1, m_pConstantBufferView.GetAddressOf());
		break;

	case TYPE::PROJECTION:
		m_CBProjection.Projection = XMMatrixTranspose(mat);
		devcon->UpdateSubresource(m_pConstantBufferProjection.Get(), 0, nullptr, &m_CBProjection, 0, 0);
		devcon->VSSetConstantBuffers(2, 1, m_pConstantBufferProjection.GetAddressOf());
		devcon->PSSetConstantBuffers(2, 1, m_pConstantBufferProjection.GetAddressOf());
		break;
	}
}

WorldTransformation::WorldTransformation() :
	m_pConstantBufferWorld(),
	m_pConstantBufferView(),
	m_pConstantBufferProjection(),
	m_CBWorld(),
	m_CBView(),
	m_CBProjection()
{
}
