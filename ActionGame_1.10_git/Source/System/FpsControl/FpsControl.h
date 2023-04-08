#pragma once
#include <Windows.h>
#include <string>
#include "../Designpattern/Singleton.h"

class FpsControl:
	public Singleton<FpsControl>
{
public:
	// Fps�̌v�Z
	bool Update();

	// ���[�v�̍Ō�ɍs���֐�
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

