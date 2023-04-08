#include "DirectX_RenderTargetTexture.h"

void DirectX_RenderTargetTexture::CreateRenderTargetView(float width, float height){

	auto* D3D = Direct3D::GetInstance();
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	// Setup the render target texture description.
	textureDesc.Width  = static_cast<UINT> (width);
	textureDesc.Height = static_cast<UINT> (height);
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	// Create the render target texture.
	if (FAILED(D3D->GetDevice()->CreateTexture2D(&textureDesc, NULL, BackBuffer.GetAddressOf()))) {
		return;
	}

	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	// Create the render target view.
	if (FAILED(D3D->GetDevice()->CreateRenderTargetView(BackBuffer.Get(), &renderTargetViewDesc, m_pRenderTargetView.GetAddressOf()))) {
		return;
	}

	// Setup the description of the shader resource view.
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	// Create the shader resource view.
	if (FAILED(D3D->GetDevice()->CreateShaderResourceView(BackBuffer.Get(), &shaderResourceViewDesc, m_pShaderResourceView.GetAddressOf()))) {
		return;
	}
}

void DirectX_RenderTargetTexture::BeforeRender(float Color[]){

	// Directx‚ÌInstance‚ÌŽæ“¾
	auto* D3D = Direct3D::GetInstance();

	// Clear the back buffer.
	D3D->GetDeviceContext()->ClearRenderTargetView(m_pRenderTargetView.Get(), Color);

	// Clear the depth buffer.
	D3D->GetDeviceContext()->ClearDepthStencilView(D3D->GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DirectX_RenderTargetTexture::SetRenderTarget(){

	// Directx‚ÌInstance‚ÌŽæ“¾
	auto* D3D = Direct3D::GetInstance();

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	D3D->GetDeviceContext()->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), D3D->GetDepthStencilView().Get());
}

ComPtr<ID3D11ShaderResourceView> DirectX_RenderTargetTexture::GetShaderResourceView() const{
	return m_pShaderResourceView;
}
