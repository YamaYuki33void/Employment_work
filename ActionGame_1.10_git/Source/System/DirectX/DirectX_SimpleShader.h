#pragma once

#include <locale.h>
#include <string>
#include <memory>
#include "Direct3D.h"

//--------------------------------------------
//Direct3D_Bufferを楽に扱える関数群
//--------------------------------------------

//shaderコンパイル
HRESULT CompileShader(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, void** ShaderObject, size_t& ShaderObjectSize, ID3DBlob** ppBlobOut);

HRESULT CompileShaderFromFile(
	const char* szFileName,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	ID3DBlob** ppBlobOut);

//書き換え可能な頂点バッファの作成
bool CreateVertexBufferWrite(
	ID3D11Device* device,
	unsigned int stride,
	unsigned int vertexnum,
	void* vertexdata,
	ID3D11Buffer** pVertexBuffer
);

//書き換え可能なインデックスバッファの作成
bool CreateIndexBufferWrite(
	ID3D11Device* device,
	unsigned int indexnum,
	void* indexdata,
	ID3D11Buffer** pIndexBuffer
);

//書き換え不可なインデックスバッファの作成
bool CreateIndexBuffer(
	ID3D11Device* device,
	unsigned int indexnum,
	void* indexdata,
	ID3D11Buffer** pIndexBuffer);


//書き換え可能な定数バッファの作成
bool CreateConstantBufferWrite(
	ID3D11Device* device,
	unsigned int bytesize,
	ID3D11Buffer** pConstantBuffer
);

//書き換え不可な定数バッファの作成
bool CreateConstantBuffer(
	ID3D11Device* device,
	unsigned int bytesize,
	ID3D11Buffer** pConstantBuffer
);

// バッファからシェーダーリソースビューを作成する	
bool CreateShaderResourceView(
	ID3D11Device* device,
	ID3D11Buffer* pBuffer,
	ID3D11ShaderResourceView** ppSRV
);

//DDSファイルを読み込みシェーダーリソースビューを作成する
bool CreateSRVfromDDS(const char* filename,
	ID3D11Device* device,
	ID3D11DeviceContext* device11Context,
	ID3D11Resource** resource,
	ID3D11ShaderResourceView** srv
);

// TGAファイルからシェーダーリソースビューを作成する
bool CreateSRVfromTGAFile(const char* filename,
	ID3D11Device* device,
	ID3D11Resource** resource,
	ID3D11ShaderResourceView** srv
);

// WICファイルからシェーダーリソースビューを作成する
bool CreateSRVfromWICFile(const char* filename,
	ID3D11Device* device,
	ID3D11DeviceContext* device11Context,
	ID3D11Resource** resource,
	ID3D11ShaderResourceView** srv
);


//FileからShaderResoceを作成する
bool CreateSRVfromFile(
	const char* filename,
	ID3D11Device* device,
	ID3D11DeviceContext* device11Context,
	ID3D11Resource** resource,
	ID3D11ShaderResourceView** srv
);

//頂点シェーダーの作成
bool CreateVertexShader(ID3D11Device* device,
	const char* szFileName,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	D3D11_INPUT_ELEMENT_DESC* layout,
	unsigned int numElements,
	ID3D11VertexShader** ppVertexShader,
	ID3D11InputLayout** ppVertexLayout
);

//ピクセルシェーダの作成
bool CreatePixelShader(ID3D11Device* device,
	const char* szFileName,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	ID3D11PixelShader** ppPixelShader
);

// StructBufferの生成
bool CreateStructuredBuffer(
	ID3D11Device* device,
	unsigned int stride,				// ストライドバイト数
	unsigned int num,					// 個数
	void* data,							// データ格納メモリ先頭アドレス
	ID3D11Buffer** pStructuredBuffer	// RWStructuredBuffer
);

// UAV アクセスビュー作成
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

