#pragma once
#include <vector>
#include <memory>
#include "Direct3D.h"

using Microsoft::WRL::ComPtr;

//--------------------------------------------
// 頂点バッファのテンプレート
//--------------------------------------------

class SimpleVertexBuffer {
public:
	// 頂点バッファの作成
	template<typename T>void TCreateVertexBuffer(const std::vector<T>& vertexdata);
	
	// 頂点バッファの更新
	template<typename T>void TVertexBufferRemake(const std::vector<T>& vertexdata);

	// Getter
	const ComPtr<ID3D11Buffer> GetVertexBuffer()const;

private:
	// 頂点バッファ
	ComPtr<ID3D11Buffer> m_pVertexBuffer; 

public:
	SimpleVertexBuffer();
	~SimpleVertexBuffer() {};
};

//---------------------------------------------
// インデックスバッファのテンプレート
//--------------------------------------------

class SimpleIndexBuffer {
public:
	// インデックスバッファの作成
	template<typename T>void TCreateIndexBuffer(const std::vector<T>& indexdata);

	// Getter
	const ComPtr<ID3D11Buffer> GetIndexBuffer()const;

private:
	ComPtr<ID3D11Buffer> m_pIndexBuffer;

public:
	SimpleIndexBuffer();
	~SimpleIndexBuffer() {};
};


template<typename T>
inline void SimpleVertexBuffer::TCreateVertexBuffer(const std::vector<T>& vertexdata){

	auto device = Direct3D::GetInstance()->GetDevice().Get();

	// 頂点バッファ生成
	if (m_pVertexBuffer == nullptr) {
		CreateVertexBufferWrite(device,
			static_cast<unsigned int>(sizeof(T)),
			static_cast<unsigned int>(vertexdata.size()),
			(void*)vertexdata.data(),
			m_pVertexBuffer.GetAddressOf());
	}
}

template<typename T>
inline void SimpleVertexBuffer::TVertexBufferRemake(const std::vector<T>& vertexdata){

	auto devcon = Direct3D::GetInstance()->GetDeviceContext().Get();

	if (m_pVertexBuffer != nullptr) {

		//作成済みならば内容を書き換える
		D3D11_MAPPED_SUBRESOURCE pData;
		HRESULT hr = devcon->Map(m_pVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
		if (SUCCEEDED(hr)) {
			memcpy_s(pData.pData, pData.RowPitch, (void*)(vertexdata.data()), sizeof(T) * vertexdata.size());
			devcon->Unmap(m_pVertexBuffer.Get(), 0);
		}
	}
}

template<typename T>
inline void SimpleIndexBuffer::TCreateIndexBuffer(const std::vector<T>& indexdata){

	auto device = Direct3D::GetInstance()->GetDevice().Get();

	if (m_pIndexBuffer == nullptr) {

		// インデックスバッファ生成
		CreateIndexBuffer(device,
			static_cast<unsigned int>(indexdata.size()),
			(void*)indexdata.data(),
			m_pIndexBuffer.GetAddressOf());
	}
}
