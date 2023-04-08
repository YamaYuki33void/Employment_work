#pragma once
#include "DirectX_Simple.h"

//----------------------------------------------------------------
// RenderTargetView����Textrue���쐬����N���X
//----------------------------------------------------------------

class DirectX_RenderTargetTexture {
public:
	// RenderTargetView�̍쐬
	 void CreateRenderTargetView(float width, float height);

	// �o�b�t�@�̃N���A
	void BeforeRender(float Color[]);

	// �����_�[�^�[�Q�b�g�̃Z�b�g
	void SetRenderTarget();

	// Getter
	ComPtr<ID3D11ShaderResourceView> GetShaderResourceView()const;

private:
	ComPtr<ID3D11Texture2D> BackBuffer;
	ComPtr<ID3D11RenderTargetView>m_pRenderTargetView;
	ComPtr<ID3D11ShaderResourceView>m_pShaderResourceView;
};

