#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "../Designpattern/Singleton.h"
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

// 16バイトにアラインメントする。
#define ALIGN16 _declspec(align(16))

class WorldTransformation : 
	public Singleton<WorldTransformation>
{
public:
	friend Singleton<WorldTransformation>;

	//座標変換リスト
	enum class TYPE {
		WORLD,
		VIEW,
		PROJECTION,
		MAXLIST
	};

	void Initalize();
	void SetTransform(TYPE type, const DirectX::XMFLOAT4X4& matrix);


	// 定数バッファ定義
	ALIGN16 struct ConstantBufferWorld {
		DirectX::XMMATRIX World;              //ワールド変換行列
	};
	ALIGN16 struct ConstantBufferView {
		DirectX::XMMATRIX View;		          //ビュー変換行列		
	};
	ALIGN16 struct ConstantBufferProjection{
		DirectX::XMMATRIX Projection;         //毎フレーム設定
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

