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
//	キーボードからの入力処理クラス
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
	char					m_keybuffer[256];	// キーボードバッファ
	char					m_oldkeybuffer[256];// 前回の入力キーボードバッファ
	DIMOUSESTATE2			m_MouseState;		// マウスの状態
	DIMOUSESTATE2			m_MouseStateTrigger;// マウスの状態
	POINT					m_MousePoint;		// マウス座標
	int						m_width;			// マウスのＸ座標最大
	int						m_height;			// マウスのＹ座標最大
	HWND					m_hwnd;

private:
	DirectInput();
	~DirectInput()override{};
};

