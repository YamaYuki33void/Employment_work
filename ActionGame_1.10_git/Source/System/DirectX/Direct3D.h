#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>
#include "../Designpattern/Singleton.h"

using Microsoft::WRL::ComPtr;

//--------------------------------------
//	Direct3D作成(singleton作成)
//--------------------------------------

class Direct3D : 
	public Singleton<Direct3D>
{
public:
	friend Singleton<Direct3D>;

	//DirectXを初期化し、使用できるようにする
	bool Initialize(const HWND hWnd, const int width, const int height);

	void SetRenderTargetView(); //バックバッファを元に戻す
	void SetOnAlphaBlending();  //アルファブレンドを有効にする
	void SetInvalidBlending();  //ブレンドを無効にする
	void SetOnZbuffer();        //Zバッファを有効にする
	void SetOffZbuffer();       //Zバッファを無効にする

	//Getter Setter//
	ComPtr<ID3D11Device>             GetDevice()const;
	ComPtr<ID3D11DeviceContext>      GetDeviceContext()const;
	ComPtr<IDXGISwapChain>           GetSwapChain()const;
	ComPtr<ID3D11RenderTargetView>   GetBackBufferView()const;
	ComPtr<ID3D11DepthStencilView>   GetDepthStencilView()const;

private:
	ComPtr<ID3D11Device>		     m_pDevice;               // Direct3Dデバイス
	ComPtr<ID3D11DeviceContext>	     m_pDeviceContext;        // Direct3Dデバイスコンテキスト
	ComPtr<IDXGISwapChain>		     m_pSwapChain;            // スワップチェイン
	ComPtr<ID3D11RenderTargetView>   m_pRenderTargetView;     // バックバッファーのRTビュー
	ComPtr<ID3D11RasterizerState>	 m_pRasterState;		  // ラスターステータス
	ComPtr<ID3D11SamplerState>	     m_pSamplerstate;	      // サンプラーステート
	ComPtr<ID3D11BlendState>	     m_pAlphablendingState;   // アルファブレンドステート
	ComPtr<ID3D11BlendState>	     m_pInvalidblendingState; // ブレンドステート（無効）
	ComPtr<ID3D11Texture2D>		     m_pDepthStencilBuffer;   // Ｚバッファ、ステンシルバッファ
	ComPtr<ID3D11DepthStencilState>  m_pDepthStencilState;    // Ｚバッファ、ステンシルステート
	ComPtr<ID3D11DepthStencilView>   m_pDepthStencilView;     // Ｚバッファ、ステンシルビュー

private:
	Direct3D(){};
	~Direct3D()override;
};
