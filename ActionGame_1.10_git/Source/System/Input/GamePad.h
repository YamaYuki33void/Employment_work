#pragma once 
#include <Windows.h>
#include <DirectXMath.h>
#include <Xinput.h>
#include<unordered_map>
#pragma comment (lib, "xinput.lib")

#include "../Designpattern/Singleton.h"

enum class GAMEPAD {
	GAMEPAD_A,
	GAMEPAD_B,
	GAMEPAD_X,
	GAMEPAD_Y,

	//LRƒ{ƒ^ƒ“
	GAMEPAD_LEFT_SHOULDER,
	GAMEPAD_RIGHT_SHOULDER,

	// L2,R2
	GAMEPAD_LEFT_THUMB,
	GAMEPAD_RIGHT_THUMB,

	GAMEPAD_START
};

class GamePad :
	public Singleton<GamePad>
{
public:
	friend Singleton<GamePad>;

	bool CheckButton(GAMEPAD pad);
	bool CheckButtonTrigger(GAMEPAD pad);
	float CheckThumbLX()const;
	float CheckThumbLY()const;
	float CheckThumbRX()const;
	float CheckThumbRY()const;

	void KeyBufferUpdate();

	// Getter
	float GetLStickLength()const;

private:
	const float MaxStick = 32767.0f;
	bool mKeyState[256];
	bool mOldState[256];
	XINPUT_STATE state;
	std::unordered_map<GAMEPAD, WORD>KeyCatalog;

private:
	GamePad();
	~GamePad()override {};
};