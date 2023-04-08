#pragma once
#include "Direct3D.h"

//================================================================
//  定数バッファを型に合わせて作成するテンプレートクラス
//  テンプレートクラス
//  簡単に作成する事が出来る
//===============================================================

template<class T>
class SimpleConstantBuffer{
public:
	// 定数バッファの作成
	void CreateCBuffer(const int regista_nunber);

	// 定数バッファの更新
	void CBufferUpdate(const T *data);

private:
	// GPUに渡すバッファ
	ComPtr<ID3D11Buffer> m_pCBuffer;

	// GPUに渡すデータ
	T m_BufferData;

	// GPUのレジスタ番号
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
	//GPUへ定数バッファをセット
	devcon->VSSetConstantBuffers(m_Regista_Nunber, 1, m_pCBuffer.GetAddressOf());
}
