#pragma once
#define DIRECTINPUT_VERSION 0x0800

#include <DirectXMath.h>
#include <dinput.h>
#include <Windows.h>
#include <wrl/client.h>
#include "../Designpattern/Singleton.h"

#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"dxguid.lib")

using Microsoft::WRL::ComPtr;

//===========================================
//	�L�[�{�[�h����̓��͏����N���X
//===========================================

class DirectInput :
	public Singleton<DirectInput>
{
public:
	friend Singleton<DirectInput>;

	bool Initialize(HINSTANCE hInst, HWND hwnd, int width, int height);

	bool GetKeyPress(int vkey);
	bool GetKeyTrigger(int vkey);

	const DirectX::XMFLOAT2& GetMousePos() const;
	
	void KeyBufferUpdate();
	void MouseBufferUpdate();

private:

private:
	ComPtr<IDirectInput8>	    m_dinput;
	ComPtr<IDirectInputDevice8>	m_dikeyboard;
	ComPtr<IDirectInputDevice8>	m_dimouse;
	char					m_keybuffer[256];	// �L�[�{�[�h�o�b�t�@
	char					m_oldkeybuffer[256];// �O��̓��̓L�[�{�[�h�o�b�t�@
	DIMOUSESTATE2			m_MouseState;		// �}�E�X�̏��
	DIMOUSESTATE2			m_MouseStateTrigger;// �}�E�X�̏��
	POINT					m_MousePoint;		// �}�E�X���W
	int						m_width;			// �}�E�X�̂w���W�ő�
	int						m_height;			// �}�E�X�̂x���W�ő�
	HWND					m_hwnd;

private:
	DirectInput();
	~DirectInput()override{};
};

