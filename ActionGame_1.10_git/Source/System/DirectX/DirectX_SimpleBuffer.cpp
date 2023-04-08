#include "DirectX_SimpleBuffer.h"

const ComPtr<ID3D11Buffer> SimpleVertexBuffer::GetVertexBuffer() const{
	return m_pVertexBuffer;
}

SimpleVertexBuffer::SimpleVertexBuffer():
	m_pVertexBuffer(nullptr)
{
}

const ComPtr<ID3D11Buffer> SimpleIndexBuffer::GetIndexBuffer() const{
	return m_pIndexBuffer;
}

SimpleIndexBuffer::SimpleIndexBuffer():
	m_pIndexBuffer(nullptr)
{
}
