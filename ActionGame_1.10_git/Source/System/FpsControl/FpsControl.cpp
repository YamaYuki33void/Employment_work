#include "FpsControl.h"

bool FpsControl::Update() {

	//�P�t���[���̌v�Z
	const float OneFrameTime = 1.0f / m_Fixed_Fps;

	// ���̎��Ԃ��擾
	QueryPerformanceCounter(&timeEnd);

	// (���̎��� - �O�t���[���̎���) / ���g�� = �o�ߎ���(�b�P��)
	m_frameTime = static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<float>(timeFreq.QuadPart);
	
	if (m_frameTime < OneFrameTime) {
		DWORD sleepTime = static_cast<DWORD>((OneFrameTime - m_frameTime) * 1000);
		timeBeginPeriod(1);
		Sleep(sleepTime);
		timeEndPeriod(1);
		return true;
	}
	else {

		// Fps�̌v�Z
		m_fps = 1 / m_frameTime;

		return false;
	}
}

void FpsControl::StartSubEnd() {
	timeStart = timeEnd;
}

std::wstring FpsControl::GetFps()const {
	return std::to_wstring(m_fps);
}

const float FpsControl::GetDeletaTime() const{
	return m_frameTime;
}

FpsControl::FpsControl():
	m_Fixed_Fps(60.0f),
	m_frameTime(),
	m_fps      (),
	timeStart  (),
	timeEnd    (),
	timeFreq   ()
{
	// ����v�Z
	QueryPerformanceFrequency(&timeFreq);
	QueryPerformanceCounter(&timeStart);
}

FpsControl::~FpsControl() {
}
