#pragma once
#include <stdio.h>
#include <string>
#include <Windows.h>
#include "../Designpattern/Singleton.h"

//-----------------------------------------
//	Window表示クラス(Singleton作成)
//-----------------------------------------

//コールバック関数
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window :
	public Singleton<Window>
{
public:
	friend Singleton<Window>;

	//window作成
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

    int m_ScreanWidth;  //スクリーン横幅      
	int m_ScreanHeight; //スクリーン縦幅        

private:
	Window();
	~Window()override;
};

