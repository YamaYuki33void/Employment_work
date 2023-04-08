#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "../Designpattern/Singleton.h"
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

// 16�o�C�g�ɃA���C�������g����B
#define ALIGN16 _declspec(align(16))

class WorldTransformation : 
	public Singleton<WorldTransformation>
{
public:
	friend Singleton<WorldTransformation>;

	//���W�ϊ����X�g
	enum class TYPE {
		WORLD,
		VIEW,
		PROJECTION,
		MAXLIST
	};

	void Initalize();
	void SetTransform(TYPE type, const DirectX::XMFLOAT4X4& matrix);


	// �萔�o�b�t�@��`
	ALIGN16 struct ConstantBufferWorld {
		DirectX::XMMATRIX World;              //���[���h�ϊ��s��
	};
	ALIGN16 struct ConstantBufferView {
		DirectX::XMMATRIX View;		          //�r���[�ϊ��s��		
	};
	ALIGN16 struct ConstantBufferProjection{
		DirectX::XMMATRIX Projection;         //���t���[���ݒ�
	};
private:
	ComPtr<ID3D11Buffer>     m_pConstantBufferWorld;
	ComPtr<ID3D11Buffer>     m_pConstantBufferView;
	ComPtr<ID3D11Buffer>     m_pConstantBufferProjection;
	ConstantBufferWorld      m_CBWorld;				
	ConstantBufferView       m_CBView;				
	ConstantBufferProjection m_CBProjection;	

private:
	WorldTransformation();
	~WorldTransformation()override{};
};

