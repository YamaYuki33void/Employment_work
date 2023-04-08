#pragma once
#include "DirectX_Simple.h"

//----------------------------------------------------------------
// RenderTargetViewからTextrueを作成するクラス
//----------------------------------------------------------------

class DirectX_RenderTargetTexture {
public:
	// RenderTargetViewの作成
	 void CreateRenderTargetView(float width, float height);

	// バッファのクリア
	void BeforeRender(float Color[]);

	// レンダーターゲットのセット
	void SetRenderTarget();

	// Getter
	ComPtr<ID3D11ShaderResourceView> GetShaderResourceView()const;

private:
	ComPtr<ID3D11Texture2D> BackBuffer;
	ComPtr<ID3D11RenderTargetView>m_pRenderTargetView;
	ComPtr<ID3D11ShaderResourceView>m_pShaderResourceView;
};

