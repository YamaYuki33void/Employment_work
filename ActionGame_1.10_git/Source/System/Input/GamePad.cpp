#include "GamePad.h"

bool GamePad::CheckButton(GAMEPAD pad) {
	return mKeyState[static_cast<int>(pad)];
}

bool GamePad::CheckButtonTrigger(GAMEPAD pad) {
	return (mKeyState[static_cast<int>(pad)]) && !(mOldState[static_cast<int>(pad)]);
}

float GamePad::CheckThumbLX()const {
	float Lx = state.Gamepad.sThumbLX;
	return Lx / MaxStick;
};
float GamePad::CheckThumbLY()const {
	float Ly = state.Gamepad.sThumbLY;
	return Ly / MaxStick;
};
float GamePad::CheckThumbRX()const {
	float Rx = state.Gamepad.sThumbRX;
	return Rx / MaxStick;
};
float GamePad::CheckThumbRY()const {
	float Ry = state.Gamepad.sThumbRY;
	return Ry / MaxStick;
};

void GamePad::KeyBufferUpdate() {
	// 前のフレームのキー状態を保存
	memcpy_s(mOldState, sizeof(mOldState), mKeyState, sizeof(mKeyState));
	XInputGetState(0, &state);

	//ボタンが押されたかチェック
	for (int i = 0; i < KeyCatalog.size(); i++) {
		if (state.Gamepad.wButtons & KeyCatalog[static_cast<GAMEPAD>(i)]) {
			mKeyState[i] = true;
		}
		else {
			mKeyState[i] = false;
		}
	}
}

float GamePad::GetLStickLength() const{

	DirectX::XMFLOAT2 inputaxis{ CheckThumbLX(),CheckThumbLY() };

	if (inputaxis.x * inputaxis.x + inputaxis.y * inputaxis.y > 0.000001f) {
		float a = (fabs(inputaxis.x) >= fabs(inputaxis.y)) ? inputaxis.y / inputaxis.x : inputaxis.x / inputaxis.y;       //絶対値の小さい方を大きい方で割る
		float b = 1.0f / sqrt(1.0f + a * a);

		inputaxis.x *= b;
		inputaxis.y *= b;
	}

	float StickLength = sqrtf((inputaxis.x * inputaxis.x) + (inputaxis.y * inputaxis.y));
	
	return StickLength;
}

GamePad::GamePad() {

	for (int i = 0; i < 256; i++) {
		mKeyState[i] = false;
	}
	//登録
	KeyCatalog.emplace(GAMEPAD::GAMEPAD_A, XINPUT_GAMEPAD_A);
	KeyCatalog.emplace(GAMEPAD::GAMEPAD_B, XINPUT_GAMEPAD_B);
	KeyCatalog.emplace(GAMEPAD::GAMEPAD_X, XINPUT_GAMEPAD_X);
	KeyCatalog.emplace(GAMEPAD::GAMEPAD_Y, XINPUT_GAMEPAD_Y);
	KeyCatalog.emplace(GAMEPAD::GAMEPAD_LEFT_SHOULDER,  XINPUT_GAMEPAD_LEFT_SHOULDER);
	KeyCatalog.emplace(GAMEPAD::GAMEPAD_RIGHT_SHOULDER, XINPUT_GAMEPAD_RIGHT_SHOULDER);
	KeyCatalog.emplace(GAMEPAD::GAMEPAD_LEFT_THUMB,  XINPUT_GAMEPAD_LEFT_THUMB);
	KeyCatalog.emplace(GAMEPAD::GAMEPAD_RIGHT_THUMB, XINPUT_GAMEPAD_RIGHT_THUMB);
	KeyCatalog.emplace(GAMEPAD::GAMEPAD_START, XINPUT_GAMEPAD_START);
	/*KeyCatalog.emplace(GAMEPAD::GAMEPAD_LEFT_THUMB, XINPUT_GAMEPAD_LEFT_THUMB);
	KeyCatalog.emplace(GAMEPAD::GAMEPAD_RIGHT_THUMB, XINPUT_GAMEPAD_RIGHT_THUMB);*/
}
