#pragma once
#include <d3d11.h>

//-------------------------------------------------
//	Direct3Dの手続きを簡易にした関数群
//-------------------------------------------------

// 入力デバイス
#include "../Input/DirectInput.h"
#include "../Input/GamePad.h"

#include "DirectX_SimpleMath.h"
#include "DirectX_SimpleShader.h"
#include "DirectX_WorldTransform.h"

#include "DirectX_SimpleBuffer.h"
#include "DirectX_SimpleConstantBuffer.h"

namespace SimepleD3D {

	//Getter
	ID3D11Device* DX11GetDevice();
	ID3D11DeviceContext* DX11GetDeviceContext();

	void DX11ClearRender(float ClearColor[]);	 // 画面のクリア
	void DX11FlipRender();						 // 描画後のバッファ切り替え
	void DX11SetAlphaBlendState();				 // アルファブレンドの有効化
	void DX11SetInvalidBlendState();			 // アルファブレンドの無効化
	void DX11SetOffZbuffer();					 // Zバッファの有効化
	void DX11SSetOnZbuffer();					 // Zバッファの無効化
	void DX11SetNormalRenderTarget();            // 通常のレンダーターゲットに戻す
}

