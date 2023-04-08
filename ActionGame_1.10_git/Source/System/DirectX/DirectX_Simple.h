#pragma once
#include <d3d11.h>

//-------------------------------------------------
//	Direct3D�̎葱�����ȈՂɂ����֐��Q
//-------------------------------------------------

// ���̓f�o�C�X
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

	void DX11ClearRender(float ClearColor[]);	 // ��ʂ̃N���A
	void DX11FlipRender();						 // �`���̃o�b�t�@�؂�ւ�
	void DX11SetAlphaBlendState();				 // �A���t�@�u�����h�̗L����
	void DX11SetInvalidBlendState();			 // �A���t�@�u�����h�̖�����
	void DX11SetOffZbuffer();					 // Z�o�b�t�@�̗L����
	void DX11SSetOnZbuffer();					 // Z�o�b�t�@�̖�����
	void DX11SetNormalRenderTarget();            // �ʏ�̃����_�[�^�[�Q�b�g�ɖ߂�
}

