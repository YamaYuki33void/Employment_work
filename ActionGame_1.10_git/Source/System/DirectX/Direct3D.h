#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>
#include "../Designpattern/Singleton.h"

using Microsoft::WRL::ComPtr;

//--------------------------------------
//	Direct3D�쐬(singleton�쐬)
//--------------------------------------

class Direct3D : 
	public Singleton<Direct3D>
{
public:
	friend Singleton<Direct3D>;

	//DirectX�����������A�g�p�ł���悤�ɂ���
	bool Initialize(const HWND hWnd, const int width, const int height);

	void SetRenderTargetView(); //�o�b�N�o�b�t�@�����ɖ߂�
	void SetOnAlphaBlending();  //�A���t�@�u�����h��L���ɂ���
	void SetInvalidBlending();  //�u�����h�𖳌��ɂ���
	void SetOnZbuffer();        //Z�o�b�t�@��L���ɂ���
	void SetOffZbuffer();       //Z�o�b�t�@�𖳌��ɂ���

	//Getter Setter//
	ComPtr<ID3D11Device>             GetDevice()const;
	ComPtr<ID3D11DeviceContext>      GetDeviceContext()const;
	ComPtr<IDXGISwapChain>           GetSwapChain()const;
	ComPtr<ID3D11RenderTargetView>   GetBackBufferView()const;
	ComPtr<ID3D11DepthStencilView>   GetDepthStencilView()const;

private:
	ComPtr<ID3D11Device>		     m_pDevice;               // Direct3D�f�o�C�X
	ComPtr<ID3D11DeviceContext>	     m_pDeviceContext;        // Direct3D�f�o�C�X�R���e�L�X�g
	ComPtr<IDXGISwapChain>		     m_pSwapChain;            // �X���b�v�`�F�C��
	ComPtr<ID3D11RenderTargetView>   m_pRenderTargetView;     // �o�b�N�o�b�t�@�[��RT�r���[
	ComPtr<ID3D11RasterizerState>	 m_pRasterState;		  // ���X�^�[�X�e�[�^�X
	ComPtr<ID3D11SamplerState>	     m_pSamplerstate;	      // �T���v���[�X�e�[�g
	ComPtr<ID3D11BlendState>	     m_pAlphablendingState;   // �A���t�@�u�����h�X�e�[�g
	ComPtr<ID3D11BlendState>	     m_pInvalidblendingState; // �u�����h�X�e�[�g�i�����j
	ComPtr<ID3D11Texture2D>		     m_pDepthStencilBuffer;   // �y�o�b�t�@�A�X�e���V���o�b�t�@
	ComPtr<ID3D11DepthStencilState>  m_pDepthStencilState;    // �y�o�b�t�@�A�X�e���V���X�e�[�g
	ComPtr<ID3D11DepthStencilView>   m_pDepthStencilView;     // �y�o�b�t�@�A�X�e���V���r���[

private:
	Direct3D(){};
	~Direct3D()override;
};
