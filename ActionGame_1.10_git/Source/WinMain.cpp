#include <Windows.h>
#include <thread>
#include "System/Window/Window.h"
#include "System/DirectX/Direct3D.h"
#include "System/Application/Application.h"

int APIENTRY WinMain(
	_In_	 HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_	 LPSTR lpCmdLine,
	_In_	 int nCmdShow) 
{
#ifdef _DEBUG
	// �������[���[�N�����m����
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	//Window���쐬
	auto* window = Window::GetInstance();
	window->CreateMainWindow(1600, 900, hInstance, nCmdShow, L"Action_AnimationEditer_1.05");

	//DirectX����������
	auto* directx = Direct3D::GetInstance();
	directx->Initialize(window->GetHwnd(), window->GetScreanWidth(), window->GetScreanHeight());

	//GameInstance���쐬
	Application app;
	app.Run();

	return window->GetMessage();
}