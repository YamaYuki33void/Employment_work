#include "DirectX_Simple.h"
#include "Direct3D.h"

ID3D11Device* SimepleD3D::DX11GetDevice(){
    return Direct3D::GetInstance()->GetDevice().Get();
}

ID3D11DeviceContext* SimepleD3D::DX11GetDeviceContext(){
    return Direct3D::GetInstance()->GetDeviceContext().Get();
}

void SimepleD3D::DX11ClearRender(float ClearColor[]){
	
	// ターゲットバッファクリア
	Direct3D::GetInstance()->GetDeviceContext().Get()->ClearRenderTargetView(
		Direct3D::GetInstance()->GetBackBufferView().Get(), ClearColor);

	// Zバッファクリア
	Direct3D::GetInstance()->GetDeviceContext().Get()->ClearDepthStencilView(
		Direct3D::GetInstance()->GetDepthStencilView().Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void SimepleD3D::DX11FlipRender(){

	// フリップ
	Direct3D::GetInstance()->GetSwapChain()->Present(0, 0);
}

void SimepleD3D::DX11SetAlphaBlendState(){

	Direct3D::GetInstance()->SetOnAlphaBlending();
}

void SimepleD3D::DX11SetInvalidBlendState(){

	Direct3D::GetInstance()->SetInvalidBlending();
}

void SimepleD3D::DX11SetOffZbuffer(){

	Direct3D::GetInstance()->SetOffZbuffer();
}

void SimepleD3D::DX11SSetOnZbuffer(){

	Direct3D::GetInstance()->SetOnZbuffer();
}

void SimepleD3D::DX11SetNormalRenderTarget(){

	Direct3D::GetInstance()->SetRenderTargetView();
}
