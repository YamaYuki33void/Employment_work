#include "DirectX_SimpleShader.h"
#include <vector>
#include <d3dcompiler.h>
#include "DirectTex/include/DirectXTex.h"
#include "DirectTex/include/DDSTextureLoader.h"
#include "DirectTex/include/WICTextureLoader.h"

#pragma comment(lib,"d3dcompiler.lib")


std::string GetFileExt(const char* filename) {
	std::string extname;
	std::string fullpathstr(filename);
	size_t ext_i = fullpathstr.find_last_of(".");
	extname = fullpathstr.substr(ext_i + 1, fullpathstr.size() - ext_i);
	return extname;
}

bool readShader(const char* csoName, std::vector<unsigned char>& byteArray)
{
	FILE* fp;
	int ret = fopen_s(&fp, csoName, "rb");
	if (ret != 0) {
		return false;
	}
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	byteArray.resize(size);
	fseek(fp, 0, SEEK_SET);

	fread(byteArray.data(), byteArray.size(), 1, fp);
	fclose(fp);

	return true;
}

HRESULT CompileShader(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, void** ShaderObject, size_t& ShaderObjectSize, ID3DBlob** ppBlobOut)
{
	HRESULT hr;
	static std::vector<unsigned char> byteArray;
	*ppBlobOut = nullptr;

	std::string extname = GetFileExt(szFileName);
	if (extname == "cso") {
		bool sts = readShader(szFileName, byteArray);
		if (!sts) {
			FILE* fp;
			fopen_s(&fp, "debug.txt", "a");
			fprintf(fp, "file open error \n");
			fclose(fp);
			return E_FAIL;
		}
		*ShaderObject = byteArray.data();
		ShaderObjectSize = byteArray.size();
	}
	else if (extname == "compute.hlsl") {

		//�R���s���[�g�V�F�[�_�[�R���p�C��
		ID3DBlob* pCSBlob = NULL;
		hr = CompileShaderFromFile(szFileName, szEntryPoint, szShaderModel, ppBlobOut);
		if (FAILED(hr))
		{
			MessageBox(nullptr,
				L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return E_FAIL;
		}
	}
	else {
		hr = CompileShaderFromFile(szFileName, szEntryPoint, szShaderModel, ppBlobOut);
		if (FAILED(hr)) {
			if (*ppBlobOut)(*ppBlobOut)->Release();
			return E_FAIL;
		}
		*ShaderObject = (*ppBlobOut)->GetBufferPointer();
		ShaderObjectSize = (*ppBlobOut)->GetBufferSize();
	}

	return S_OK;
}

HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	ID3DBlob* p1 = nullptr;

	HRESULT hr = S_OK;

	WCHAR	filename[512];
	size_t 	wLen = 0;
	int err = 0;

	// char -> wchar�ɕϊ�
	setlocale(LC_ALL, "japanese");
	err = mbstowcs_s(&wLen, filename, 512, szFileName, _TRUNCATE);

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(
		filename,							// filename LPCWST pFileName
		nullptr,							// D3D_SHADER_MACRO *pDefines
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	// ID3DInclude *pInclude
		szEntryPoint,						// LPCSTR pEntrypoint
		szShaderModel,						// LPCSTR pTarget
		dwShaderFlags,						// UINT Flags1
		0,									// UINT Flags2
		ppBlobOut,							// ID3DBlob** ppCode
		&pErrorBlob);						// ID3DBlob** ppErrorMsg 
	if (FAILED(hr))
	{
		if (pErrorBlob != nullptr) {
			MessageBox(NULL,
				(LPCTSTR)pErrorBlob->GetBufferPointer(), nullptr, MB_OK);
		}
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}

bool CreateVertexBufferWrite(
	ID3D11Device* device,
	unsigned int stride,
	unsigned int vertexnum,
	void* vertexdata,
	ID3D11Buffer** pVertexBuffer
)
{
	HRESULT hr;

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;			    // �o�b�t�@�g�p���@
	bd.ByteWidth = stride * vertexnum;		    // �o�b�t�@�̑傫��
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;    // ���_�o�b�t�@
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU�A�N�Z�X�\

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertexdata;				// �o�b�t�@�̏����l

	hr = device->CreateBuffer(&bd, &InitData, pVertexBuffer);// �o�b�t�@����
	if (FAILED(hr)) {
		MessageBox(nullptr, L"CreateBuffer(vertex buffer) error",nullptr, MB_OK);
		return false;
	}

	return true;
}


bool CreateIndexBufferWrite(
	ID3D11Device* device,
	unsigned int indexnum,
	void* indexdata,
	ID3D11Buffer** pIndexBuffer
)
{
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;					// �o�b�t�@�g�p���@
	bd.ByteWidth = sizeof(unsigned int) * indexnum;	// �o�b�t�@�̑傫
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;			// �C���f�b�N�X�o�b�t�@
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		// CPU�A�N�Z�X�\

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = indexdata;

	HRESULT hr = device->CreateBuffer(&bd, &InitData, pIndexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"CreateBuffer(index buffer) error", nullptr, MB_OK);
		return false;
	}

	return true;
}

bool CreateIndexBuffer(ID3D11Device* device, unsigned int indexnum, void* indexdata, ID3D11Buffer** pIndexBuffer) {

	// �C���f�b�N�X�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(unsigned int) * indexnum;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = indexdata;

	HRESULT hr = device->CreateBuffer(&bd, &InitData, pIndexBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"CreateBuffer(index buffer) error", nullptr, MB_OK);
		return false;
	}

	return true;

}

bool CreateConstantBufferWrite(
	ID3D11Device* device,
	unsigned int bytesize,
	ID3D11Buffer** pConstantBuffer
)
{
	// �R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;				// �o�b�t�@�g�p���@
	bd.ByteWidth = bytesize;					// �o�b�t�@�̑傫
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// �R���X�^���g�o�b�t�@
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPU�A�N�Z�X�\

	HRESULT hr = device->CreateBuffer(&bd, nullptr, pConstantBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"CreateBuffer(constant buffer) error", nullptr, MB_OK);
		return false;
	}

	return true;
}

bool CreateConstantBuffer(ID3D11Device* device, unsigned int bytesize, ID3D11Buffer** pConstantBuffer) {

	D3D11_BUFFER_DESC bd;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = bytesize;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	HRESULT hr = device->CreateBuffer(&bd, nullptr, pConstantBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"CreateBuffer(constant buffer) error", nullptr, MB_OK);
		return false;
	}

	return true;
}

bool CreateShaderResourceView(
	ID3D11Device* device,
	ID3D11Buffer* pBuffer,
	ID3D11ShaderResourceView** ppSRV
)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	pBuffer->GetDesc(&bd);

	D3D11_SHADER_RESOURCE_VIEW_DESC  srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	srvDesc.BufferEx.FirstElement = 0;

	if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS) {
		srvDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		srvDesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
		srvDesc.BufferEx.NumElements = bd.ByteWidth / 4;
	}
	else if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED) {
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.BufferEx.NumElements = bd.ByteWidth / bd.StructureByteStride;
	}
	else {
		return false;
	}

	HRESULT hr;
	hr = device->CreateShaderResourceView(pBuffer, &srvDesc, ppSRV);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"CreateShaderResourceView error", nullptr, MB_OK);
		return false;
	}

	return true;
}

bool CreateSRVfromDDS(const char* filename,
	ID3D11Device* device,
	ID3D11DeviceContext* device11Context,
	ID3D11Resource** resource,
	ID3D11ShaderResourceView** srv
)
{
	ID3D11Resource* texr = nullptr;		// �e�N�X�`�����\�[�X

	wchar_t ws[512];
	size_t ret;

	setlocale(LC_CTYPE, "jpn");
	mbstowcs_s(&ret, ws, 512, filename, _TRUNCATE);

	// �e�N�X�`���ǂݍ���
	HRESULT hr = DirectX::CreateDDSTextureFromFile(
		device,
		device11Context,
		ws,
		resource, srv);
	if (FAILED(hr)) {
		MessageBox(NULL, L"CreateWICTextureFromFile", nullptr, MB_OK);
		return false;
	}

	return true;
}

// TGA�t�@�C������V�F�[�_�[���\�[�X�r���[���쐬����
bool CreateSRVfromTGAFile(const char* filename,
	ID3D11Device* device,
	ID3D11Resource** resource,
	ID3D11ShaderResourceView** srv
)
{
	HRESULT		hr;

	wchar_t ws[512];
	size_t ret;

	setlocale(LC_CTYPE, "jpn");
	mbstowcs_s(&ret, ws, 512, filename, _TRUNCATE);

	DirectX::TexMetadata meta;
	DirectX::GetMetadataFromTGAFile(ws, meta);

	std::unique_ptr<DirectX::ScratchImage> image(new DirectX::ScratchImage);
	hr = LoadFromTGAFile(ws, &meta, *image);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Texture Load error", nullptr, MB_OK);
		return false;
	}

	// �e�N�X�`������
	hr = CreateTexture(
		device,
		image->GetImages(), image->GetImageCount(), meta,
		resource);
	if (FAILED(hr)) {
		MessageBox(nullptr,L"CreateTexture error", nullptr, MB_OK);
		return false;
	}

	// �V�F�[�_�[���\�[�X�r���[�쐬
	hr = DirectX::CreateShaderResourceView(device, image->GetImages(), image->GetImageCount(), meta, srv);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"CreateShaderResourceView error", nullptr, MB_OK);
		return false;
	}

	return true;
}

// WIC�t�@�C������V�F�[�_�[���\�[�X�r���[���쐬����
bool CreateSRVfromWICFile(const char* filename,
	ID3D11Device* device,
	ID3D11DeviceContext* device11Context,
	ID3D11Resource** resource,
	ID3D11ShaderResourceView** srv
)
{
	ID3D11Resource* texr = nullptr;		// �e�N�X�`�����\�[�X

	wchar_t ws[512];
	size_t ret;

	setlocale(LC_CTYPE, "jpn");
	mbstowcs_s(&ret, ws, 512, filename, _TRUNCATE);

	// �e�N�X�`���ǂݍ���
	HRESULT hr = DirectX::CreateWICTextureFromFile(
		device,
		device11Context,
		ws,
		resource, srv);								// 20200505 modify
	//		&texr, srv);
	if (FAILED(hr)) {
		MessageBox(NULL, L"CreateWICTextureFromFile", nullptr, MB_OK);
		return false;
	}

	return true;
}

bool CreateSRVfromFile(
	const char* filename,
	ID3D11Device* device,
	ID3D11DeviceContext* device11Context,
	ID3D11Resource** resource,
	ID3D11ShaderResourceView** srv) {

	std::string fname(filename);

	std::string ext;

	// �g���q���擾����
	ext = GetFileExt(fname.c_str());


	// DDS�t�@�C��
	if (ext == "dds") {
		bool sts = CreateSRVfromDDS(fname.c_str(),
			device,
			device11Context,
			resource,
			srv);
		if (!sts) {
			MessageBox(nullptr, (LPCTSTR)fname.c_str(), L"texload error", MB_OK);
			return false;
		}
	}
	// TGA�t�@�C��
	else if (ext == "tga") {
		bool sts = CreateSRVfromTGAFile(fname.c_str(),
			device,
			resource,
			srv);
		if (!sts) {
			MessageBox(nullptr, (LPCTSTR)fname.c_str(), L"texload error", MB_OK);
			return false;
		}
	}
	// ���̑��t�@�C��
	else {
		bool sts = CreateSRVfromWICFile(fname.c_str(),
			device,
			device11Context,
			resource,
			srv);
		if (!sts) {
			MessageBox(nullptr, (LPCTSTR)fname.c_str(), L"texload error", MB_OK);
			return false;
		}
	}
	return true;
}

bool CreateVertexShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, D3D11_INPUT_ELEMENT_DESC* layout, unsigned int numElements, ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppVertexLayout)
{
	HRESULT hr;

	ID3DBlob* pBlob = nullptr;

	void* ShaderObject;
	size_t	ShaderObjectSize;

	// �t�@�C���̊g���q�ɍ��킹�ăR���p�C��
	hr = CompileShader(szFileName, szEntryPoint, szShaderModel, &ShaderObject, ShaderObjectSize, &pBlob);
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return false;
	}

	// ���_�V�F�[�_�[�𐶐�
	hr = device->CreateVertexShader(ShaderObject, ShaderObjectSize, nullptr, ppVertexShader);
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return false;
	}

	// ���_�f�[�^��`����
	hr = device->CreateInputLayout(
		layout,
		numElements,
		ShaderObject,
		ShaderObjectSize,
		ppVertexLayout);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"CreateInputLayout error",nullptr, MB_OK);
		pBlob->Release();
		return false;
	}

	return true;
}


bool CreatePixelShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3D11PixelShader** ppPixelShader)
{
	HRESULT hr;

	ID3DBlob* pBlob = nullptr;

	void* ShaderObject;
	size_t	ShaderObjectSize;

	// �t�@�C���̊g���q�ɍ��킹�ăR���p�C��
	hr = CompileShader(szFileName, szEntryPoint, szShaderModel, &ShaderObject, ShaderObjectSize, &pBlob);
	if (FAILED(hr))
	{
		return false;
	}

	// �s�N�Z���V�F�[�_�[�𐶐�
	hr = device->CreatePixelShader(ShaderObject, ShaderObjectSize, nullptr, ppPixelShader);
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return false;
	}

	return true;
}

bool CreateStructuredBuffer(ID3D11Device* device, unsigned int stride, unsigned int num, void* data, ID3D11Buffer** pStructuredBuffer)
{
	HRESULT hr;

	// Structured�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;		// UA�o�b�t�@
	bd.ByteWidth = stride * num;													// �o�b�t�@�̑傫��
	bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;							// RWStructuredBuffer
	bd.StructureByteStride = stride;												// �\�����o�b�t�@�T�C�Y
	bd.CPUAccessFlags = 0;															// CPU�A�N�Z�X�s�v

	if (data != nullptr) {
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));

		InitData.pSysMem = data;// �o�b�t�@�̏����l

		hr = device->CreateBuffer(&bd, &InitData, pStructuredBuffer);	// �o�b�t�@����
	}
	else {
		hr = device->CreateBuffer(&bd, nullptr, pStructuredBuffer);		// �o�b�t�@����
	}
	if (FAILED(hr)) {
		MessageBox(nullptr, L"CreateBuffer(StructuredBuffer) error", L"Error", MB_OK);
		return false;
	}

	return true;
}

bool CreateUnOrderAccessView(ID3D11Device* device, ID3D11Buffer* pBuffer, ID3D11UnorderedAccessView** ppUAV)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	pBuffer->GetDesc(&bd);

	D3D11_UNORDERED_ACCESS_VIEW_DESC  uavDesc;
	ZeroMemory(&uavDesc, sizeof(uavDesc));
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.FirstElement = 0;

	if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS) {
		uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
		uavDesc.Buffer.NumElements = bd.ByteWidth / 4;
	}
	else if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED) {
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.Buffer.NumElements = bd.ByteWidth / bd.StructureByteStride;
	}
	else {
		return false;
	}

	HRESULT hr;
	hr = device->CreateUnorderedAccessView(pBuffer, &uavDesc, ppUAV);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"CreateUnorderedAccessView error", L"Error", MB_OK);
		return false;
	}

	return true;
}

ID3D11Buffer* CreateAndCopyToBuffer(ID3D11Device* device, ID3D11DeviceContext* devicecontext, ID3D11Buffer* pBuffer){

	HRESULT hr;
	ID3D11Buffer* CloneBuffer = nullptr;

	// Structured�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	pBuffer->GetDesc(&bd);

	bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	bd.Usage = D3D11_USAGE_STAGING;
	bd.BindFlags = 0;
	bd.MiscFlags = 0;

	hr = device->CreateBuffer(&bd, nullptr, &CloneBuffer);
	if (SUCCEEDED(hr)) {
		devicecontext->CopyResource(CloneBuffer, pBuffer);
	}

	return CloneBuffer;
}

