#pragma once
#include "Direct3D.h"

//================================================================
//  �萔�o�b�t�@���^�ɍ��킹�č쐬����e���v���[�g�N���X
//  �e���v���[�g�N���X
//  �ȒP�ɍ쐬���鎖���o����
//===============================================================

template<class T>
class SimpleConstantBuffer{
public:
	// �萔�o�b�t�@�̍쐬
	void CreateCBuffer(const int regista_nunber);

	// �萔�o�b�t�@�̍X�V
	void CBufferUpdate(const T *data);

private:
	// GPU�ɓn���o�b�t�@
	ComPtr<ID3D11Buffer> m_pCBuffer;

	// GPU�ɓn���f�[�^
	T m_BufferData;

	// GPU�̃��W�X�^�ԍ�
	int m_Regista_Nunber;
};

template<class T>
inline void SimpleConstantBuffer<T>::CreateCBuffer(const int regista_nunber){

	auto* device = Direct3D::GetInstance()->GetDevice().Get();

	m_Regista_Nunber = regista_nunber;

	bool sts = CreateConstantBufferWrite(device, sizeof(T), m_pCBuffer.GetAddressOf());
	if (!sts) {
		MessageBox(nullptr, L"constant buffer create fail", nullptr, MB_OK);
	}
}

template<class T>
inline void SimpleConstantBuffer<T>::CBufferUpdate(const T* data) {

	auto* devcon = Direct3D::GetInstance()->GetDeviceContext().Get();

	D3D11_MAPPED_SUBRESOURCE pData;
	HRESULT hr = devcon->Map(m_pCBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		memcpy_s(pData.pData, pData.RowPitch, (void*)(data), sizeof(T));
		devcon->Unmap(m_pCBuffer.Get(), 0);
	}
	//GPU�֒萔�o�b�t�@���Z�b�g
	devcon->VSSetConstantBuffers(m_Regista_Nunber, 1, m_pCBuffer.GetAddressOf());
}
