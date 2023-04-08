#include "DirectInput.h"
#include "../Window/Window.h"

bool DirectInput::Initialize(HINSTANCE hInst, HWND hwnd, int width, int height){

	HRESULT	hr;
	hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_dinput, NULL);
	if (FAILED(hr)) {
		return false;
	}

	// �L�[�{�[�h�f�o�C�X����
	m_dinput->CreateDevice(GUID_SysKeyboard, &m_dikeyboard, NULL);
	if (FAILED(hr)) {
		return false;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = m_dikeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		return false;
	}

	// �������x���̐ݒ�
	hr = m_dikeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		return false;
	}

	// �}�E�X�f�o�C�X����
	m_dinput->CreateDevice(GUID_SysMouse, &m_dimouse, NULL);
	if (FAILED(hr)) {
		return false;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = m_dimouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(hr)) {
		return false;
	}

	// �������x���̐ݒ�
	hr = m_dimouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		return false;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize       = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj        = 0;
	diprop.diph.dwHow        = DIPH_DEVICE;
	diprop.dwData            = DIPROPAXISMODE_REL;			// ���Βl���[�h
	m_dimouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);	// �����[�h�̐ݒ�


	DIPROPRANGE diprg;
	diprg.diph.dwSize       = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwObj        = DIJOFS_X;
	diprg.diph.dwHow        = DIPH_BYOFFSET;
	diprg.lMin              = 0;
	diprg.lMax              = width - 1;
	m_dimouse->SetProperty(DIPROP_RANGE, &diprg.diph);		// �w�����͈̔͂��w��

	diprg.diph.dwObj        = DIJOFS_Y;
	diprg.diph.dwHow        = DIPH_BYOFFSET;
	diprg.lMin              = 0;
	diprg.lMax              = height - 1;
	m_dimouse->SetProperty(DIPROP_RANGE, &diprg.diph);	    // �x�����͈̔͂��w��

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
	// �f�o�C�X�̔F��
	hr = m_dikeyboard->Acquire();
	// �O��̏�Ԃ�ۑ�
	memcpy(&m_oldkeybuffer, m_keybuffer, sizeof(m_keybuffer));
	hr = m_dikeyboard->GetDeviceState(sizeof(m_keybuffer), (LPVOID)&m_keybuffer);
	if (hr == DIERR_INPUTLOST) {
		// �f�o�C�X�̔F��
		hr = m_dikeyboard->Acquire();
	}

	MouseBufferUpdate();
}

void DirectInput::MouseBufferUpdate(){

	HRESULT	hr;
	DIMOUSESTATE2		mouseStateOld = m_MouseState;

	GetCursorPos(&m_MousePoint);
	ScreenToClient(m_hwnd, &m_MousePoint);

	// �f�o�C�X�̔F��
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
			// �f�o�C�X�̔F��
			hr = m_dimouse->Acquire();
		}
	}
}

DirectInput::DirectInput() :
	m_dinput    (nullptr), 
	m_dikeyboard(nullptr)
{
	//���͏���������
	Initialize(
		Window::GetInstance()->GetHinstance(),
		Window::GetInstance()->GetHwnd(),
		Window::GetInstance()->GetScreanWidth(),
		Window::GetInstance()->GetScreanHeight()
	);
}
