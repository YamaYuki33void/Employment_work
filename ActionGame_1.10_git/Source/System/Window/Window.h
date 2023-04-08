#pragma once
#include <stdio.h>
#include <string>
#include <Windows.h>
#include "../Designpattern/Singleton.h"

//-----------------------------------------
//	Window�\���N���X(Singleton�쐬)
//-----------------------------------------

//�R�[���o�b�N�֐�
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window :
	public Singleton<Window>
{
public:
	friend Singleton<Window>;

	//window�쐬
	void CreateMainWindow(const int width, const int heght, HINSTANCE hinstance, int nCmdShow,const LPCTSTR WindowName = L"None");
	bool ExecMessage();

	//Getter Setter//
	void  SetMyWindowText(LPCWSTR WindowName);
	void  MyWindowResizing();
	const HINSTANCE& GetHinstance()const;
	const HWND& GetHwnd()const;
	const long GetMessage() const;
	const int GetScreanWidth()const;
	const int GetScreanHeight()const;

private:
	HINSTANCE m_Hinstance;
	HWND      m_Hwnd;
	MSG       m_Msg;                   
	FILE*     m_File;

    int m_ScreanWidth;  //�X�N���[������      
	int m_ScreanHeight; //�X�N���[���c��        

private:
	Window();
	~Window()override;
};

