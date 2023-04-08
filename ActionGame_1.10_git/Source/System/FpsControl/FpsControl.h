#pragma once
#include <Windows.h>
#include <string>
#include "../Designpattern/Singleton.h"

class FpsControl:
	public Singleton<FpsControl>
{
public:
	// Fpsの計算
	bool Update();

	// ループの最後に行う関数
	void StartSubEnd();

	// Getter Setter
	std::wstring GetFps()const;
	const float GetDeletaTime()const;

private:
	float m_Fixed_Fps;
	float m_frameTime;
	float m_fps;
	LARGE_INTEGER timeStart, timeEnd, timeFreq;

public:
	FpsControl();
	~FpsControl();
};

