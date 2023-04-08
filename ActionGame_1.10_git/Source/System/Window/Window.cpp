#include "Window.h"

void Window::CreateMainWindow(const int width, const int heght, HINSTANCE hinstance, int nCmdShow,const LPCTSTR WindowName){

    //Windowのサイズ格納
	m_ScreanWidth  = width;
	m_ScreanHeight = heght;

    // ウィンドウクラスの属性を設定
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

    // ウィンドウクラスを登録
    if (!RegisterClass(&wc)) {
        MessageBox(nullptr, L"WindowClassが登録できませんでした。", nullptr, MB_OK);
    }
   
    // ウィンドウを作成
    m_Hwnd = CreateWindow(
        wc.lpszClassName, WindowName,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, m_ScreanWidth,
        CW_USEDEFAULT, m_ScreanHeight,
        NULL, NULL,
        m_Hinstance, NULL);

    //クライアント領域を指定した大きさにリサイズする
    RECT rw, rc;
    ::GetWindowRect(m_Hwnd, &rw);
    ::GetClientRect(m_Hwnd, &rc);
    int new_width  = (rw.right - rw.left) - (rc.right - rc.left) + m_ScreanWidth;
    int new_height = (rw.bottom - rw.top) - (rc.bottom - rc.top) + m_ScreanHeight;
    ::SetWindowPos(m_Hwnd, NULL, 0, 0, new_width, new_height, SWP_NOMOVE | SWP_NOZORDER);

    if (!m_Hwnd) {
        MessageBox(nullptr, L"Windowを作成できませんでした", nullptr, MB_OK);
    }
    else {
        //デバッグ時のみコンソール生成
#ifdef _DEBUG
        AllocConsole();
        freopen_s(&m_File, "CON", "w", stdout);
#endif

        m_Hinstance = hinstance;

        // ウィンドウを表示
        ShowWindow(m_Hwnd, nCmdShow);
        // ウィンドウを再描画
        UpdateWindow(m_Hwnd);
    }
}

bool Window::ExecMessage(){

    //Mesageループ
    while (PeekMessage(&m_Msg, NULL, 0, 0, PM_NOREMOVE)) {
        // メッセージなし
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

    // ウィンドウを再描画
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
    //コンソール解放
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

