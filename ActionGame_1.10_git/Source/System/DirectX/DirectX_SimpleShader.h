#pragma once

#include <locale.h>
#include <string>
#include <memory>
#include "Direct3D.h"

//--------------------------------------------
//Direct3D_Buffer���y�Ɉ�����֐��Q
//--------------------------------------------

//shader�R���p�C��
HRESULT CompileShader(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, void** ShaderObject, size_t& ShaderObjectSize, ID3DBlob** ppBlobOut);

HRESULT CompileShaderFromFile(
	const char* szFileName,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	ID3DBlob** ppBlobOut);

//���������\�Ȓ��_�o�b�t�@�̍쐬
bool CreateVertexBufferWrite(
	ID3D11Device* device,
	unsigned int stride,
	unsigned int vertexnum,
	void* vertexdata,
	ID3D11Buffer** pVertexBuffer
);

//���������\�ȃC���f�b�N�X�o�b�t�@�̍쐬
bool CreateIndexBufferWrite(
	ID3D11Device* device,
	unsigned int indexnum,
	void* indexdata,
	ID3D11Buffer** pIndexBuffer
);

//���������s�ȃC���f�b�N�X�o�b�t�@�̍쐬
bool CreateIndexBuffer(
	ID3D11Device* device,
	unsigned int indexnum,
	void* indexdata,
	ID3D11Buffer** pIndexBuffer);


//���������\�Ȓ萔�o�b�t�@�̍쐬
bool CreateConstantBufferWrite(
	ID3D11Device* device,
	unsigned int bytesize,
	ID3D11Buffer** pConstantBuffer
);

//���������s�Ȓ萔�o�b�t�@�̍쐬
bool CreateConstantBuffer(
	ID3D11Device* device,
	unsigned int bytesize,
	ID3D11Buffer** pConstantBuffer
);

// �o�b�t�@����V�F�[�_�[���\�[�X�r���[���쐬����	
bool CreateShaderResourceView(
	ID3D11Device* device,
	ID3D11Buffer* pBuffer,
	ID3D11ShaderResourceView** ppSRV
);

//DDS�t�@�C����ǂݍ��݃V�F�[�_�[���\�[�X�r���[���쐬����
bool CreateSRVfromDDS(const char* filename,
	ID3D11Device* device,
	ID3D11DeviceContext* device11Context,
	ID3D11Resource** resource,
	ID3D11ShaderResourceView** srv
);

// TGA�t�@�C������V�F�[�_�[���\�[�X�r���[���쐬����
bool CreateSRVfromTGAFile(const char* filename,
	ID3D11Device* device,
	ID3D11Resource** resource,
	ID3D11ShaderResourceView** srv
);

// WIC�t�@�C������V�F�[�_�[���\�[�X�r���[���쐬����
bool CreateSRVfromWICFile(const char* filename,
	ID3D11Device* device,
	ID3D11DeviceContext* device11Context,
	ID3D11Resource** resource,
	ID3D11ShaderResourceView** srv
);


//File����ShaderResoce���쐬����
bool CreateSRVfromFile(
	const char* filename,
	ID3D11Device* device,
	ID3D11DeviceContext* device11Context,
	ID3D11Resource** resource,
	ID3D11ShaderResourceView** srv
);

//���_�V�F�[�_�[�̍쐬
bool CreateVertexShader(ID3D11Device* device,
	const char* szFileName,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	D3D11_INPUT_ELEMENT_DESC* layout,
	unsigned int numElements,
	ID3D11VertexShader** ppVertexShader,
	ID3D11InputLayout** ppVertexLayout
);

//�s�N�Z���V�F�[�_�̍쐬
bool CreatePixelShader(ID3D11Device* device,
	const char* szFileName,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	ID3D11PixelShader** ppPixelShader
);

// StructBuffer�̐���
bool CreateStructuredBuffer(
	ID3D11Device* device,
	unsigned int stride,				// �X�g���C�h�o�C�g��
	unsigned int num,					// ��
	void* data,							// �f�[�^�i�[�������擪�A�h���X
	ID3D11Buffer** pStructuredBuffer	// RWStructuredBuffer
);

// UAV �A�N�Z�X�r���[�쐬
bool CreateUnOrderAccessView(
	ID3D11Device* device,
	ID3D11Buffer* pBuffer,
	ID3D11UnorderedAccessView** ppUAV
);

ID3D11Buffer* CreateAndCopyToBuffer(
	ID3D11Device* device,
	ID3D11DeviceContext* devicecontext,
	ID3D11Buffer* pBuffer	// RWStructuredBuffer
);

