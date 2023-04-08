#include "DirectInput.h"
#include "../Window/Window.h"

bool DirectInput::Initialize(HINSTANCE hInst, HWND hwnd, int width, int height){

	HRESULT	hr;
	hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_dinput, NULL);
	if (FAILED(hr)) {
		return false;
	}

	// キーボードデバイス生成
	m_dinput->CreateDevice(GUID_SysKeyboard, &m_dikeyboard, NULL);
	if (FAILED(hr)) {
		return false;
	}

	// データフォーマットの設定
	hr = m_dikeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		return false;
	}

	// 協調レベルの設定
	hr = m_dikeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		return false;
	}

	// マウスデバイス生成
	m_dinput->CreateDevice(GUID_SysMouse, &m_dimouse, NULL);
	if (FAILED(hr)) {
		return false;
	}

	// データフォーマットの設定
	hr = m_dimouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(hr)) {
		return false;
	}

	// 協調レベルの設定
	hr = m_dimouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		return false;
	}

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize       = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj        = 0;
	diprop.diph.dwHow        = DIPH_DEVICE;
	diprop.dwData            = DIPROPAXISMODE_REL;			// 相対値モード
	m_dimouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);	// 軸モードの設定


	DIPROPRANGE diprg;
	diprg.diph.dwSize       = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwObj        = DIJOFS_X;
	diprg.diph.dwHow        = DIPH_BYOFFSET;
	diprg.lMin              = 0;
	diprg.lMax              = width - 1;
	m_dimouse->SetProperty(DIPROP_RANGE, &diprg.diph);		// Ｘ方向の範囲を指定

	diprg.diph.dwObj        = DIJOFS_Y;
	diprg.diph.dwHow        = DIPH_BYOFFSET;
	diprg.lMin              = 0;
	diprg.lMax              = height - 1;
	m_dimouse->SetProperty(DIPROP_RANGE, &diprg.diph);	    // Ｙ方向の範囲を指定

	m_hwnd   = hwnd;
	m_height = height;
	m_width  = width;

	return true;
}

bool DirectInput::GetKeyPress(int vkey){
	if (m_keybuffer[vkey] & 0x80) {
		return true;
	}
	else {
		return false;
	}
}

bool DirectInput::GetKeyTrigger(int vkey){
	if (((m_keybuffer[vkey] ^ m_oldkeybuffer[vkey]) & m_keybuffer[vkey]) & 0x80) {
		return true;
	}
	else {
		return false;
	}
}

const DirectX::XMFLOAT2& DirectInput::GetMousePos() const{
	return DirectX::XMFLOAT2{ static_cast<float>(m_MousePoint.x) ,static_cast<float>(m_MousePoint.y) };
}

void DirectInput::KeyBufferUpdate() {
	HRESULT	hr;
	// デバイスの認識
	hr = m_dikeyboard->Acquire();
	// 前回の状態を保存
	memcpy(&m_oldkeybuffer, m_keybuffer, sizeof(m_keybuffer));
	hr = m_dikeyboard->GetDeviceState(sizeof(m_keybuffer), (LPVOID)&m_keybuffer);
	if (hr == DIERR_INPUTLOST) {
		// デバイスの認識
		hr = m_dikeyboard->Acquire();
	}

	MouseBufferUpdate();
}

void DirectInput::MouseBufferUpdate(){

	HRESULT	hr;
	DIMOUSESTATE2		mouseStateOld = m_MouseState;

	GetCursorPos(&m_MousePoint);
	ScreenToClient(m_hwnd, &m_MousePoint);

	// デバイスの認識
	hr = m_dimouse->Acquire();

	hr = m_dimouse->GetDeviceState(sizeof(m_MouseState), &m_MouseState);
	if (SUCCEEDED(hr)) {
		for (int cnt = 0; cnt < 8; cnt++)
		{
			m_MouseStateTrigger.rgbButtons[cnt] = ((mouseStateOld.rgbButtons[cnt] ^ m_MouseState.rgbButtons[cnt]) & m_MouseState.rgbButtons[cnt]);
		}
	}
	else {
		if (hr == DIERR_INPUTLOST) {
			// デバイスの認識
			hr = m_dimouse->Acquire();
		}
	}
}

DirectInput::DirectInput() :
	m_dinput    (nullptr), 
	m_dikeyboard(nullptr)
{
	//入力処理初期化
	Initialize(
		Window::GetInstance()->GetHinstance(),
		Window::GetInstance()->GetHwnd(),
		Window::GetInstance()->GetScreanWidth(),
		Window::GetInstance()->GetScreanHeight()
	);
}
