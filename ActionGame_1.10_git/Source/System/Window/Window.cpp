#include "Window.h"

void Window::CreateMainWindow(const int width, const int heght, HINSTANCE hinstance, int nCmdShow,const LPCTSTR WindowName){

    //Window�̃T�C�Y�i�[
	m_ScreanWidth  = width;
	m_ScreanHeight = heght;

    // �E�B���h�E�N���X�̑�����ݒ�
    WNDCLASS wc;
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hinstance;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = WindowName;

    // �E�B���h�E�N���X��o�^
    if (!RegisterClass(&wc)) {
        MessageBox(nullptr, L"WindowClass���o�^�ł��܂���ł����B", nullptr, MB_OK);
    }
   
    // �E�B���h�E���쐬
    m_Hwnd = CreateWindow(
        wc.lpszClassName, WindowName,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, m_ScreanWidth,
        CW_USEDEFAULT, m_ScreanHeight,
        NULL, NULL,
        m_Hinstance, NULL);

    //�N���C�A���g�̈���w�肵���傫���Ƀ��T�C�Y����
    RECT rw, rc;
    ::GetWindowRect(m_Hwnd, &rw);
    ::GetClientRect(m_Hwnd, &rc);
    int new_width  = (rw.right - rw.left) - (rc.right - rc.left) + m_ScreanWidth;
    int new_height = (rw.bottom - rw.top) - (rc.bottom - rc.top) + m_ScreanHeight;
    ::SetWindowPos(m_Hwnd, NULL, 0, 0, new_width, new_height, SWP_NOMOVE | SWP_NOZORDER);

    if (!m_Hwnd) {
        MessageBox(nullptr, L"Window���쐬�ł��܂���ł���", nullptr, MB_OK);
    }
    else {
        //�f�o�b�O���̂݃R���\�[������
#ifdef _DEBUG
        AllocConsole();
        freopen_s(&m_File, "CON", "w", stdout);
#endif

        m_Hinstance = hinstance;

        // �E�B���h�E��\��
        ShowWindow(m_Hwnd, nCmdShow);
        // �E�B���h�E���ĕ`��
        UpdateWindow(m_Hwnd);
    }
}

bool Window::ExecMessage(){

    //Mesage���[�v
    while (PeekMessage(&m_Msg, NULL, 0, 0, PM_NOREMOVE)) {
        // ���b�Z�[�W�Ȃ�
        if (!(::GetMessage(&m_Msg, NULL, 0, 0)))
            return false;

        TranslateMessage(&m_Msg);
        DispatchMessage(&m_Msg);
    }

    return true;
}

const HINSTANCE& Window::GetHinstance() const{
    return m_Hinstance;
}

const HWND& Window::GetHwnd() const{
    return m_Hwnd;
}

const long Window::GetMessage() const{
    return m_Msg.message;
}

const int Window::GetScreanWidth() const{
    return m_ScreanWidth;
}

const int Window::GetScreanHeight() const{
    return m_ScreanHeight;
}

void Window::SetMyWindowText(LPCWSTR WindowName) {
    SetWindowText(m_Hwnd, WindowName);
}

void Window::MyWindowResizing(){

    // �E�B���h�E���ĕ`��
    UpdateWindow(m_Hwnd);
}

Window::Window() :
    m_Hinstance   (),
    m_Hwnd        (),
    m_Msg         (),
    m_File        (),
    m_ScreanWidth (),
    m_ScreanHeight()
{
}

Window::~Window(){

#ifdef _DEBUG
    //�R���\�[�����
    fclose(m_File);
    ::FreeConsole();
#endif
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

    if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam)) {
        return true;
    }

    switch (uMsg) {
    case WM_MOUSEMOVE:
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_SIZE:
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

