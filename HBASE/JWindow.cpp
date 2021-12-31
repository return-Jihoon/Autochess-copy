#include "JWindow.h"
#include "Debug.h"
#include <assert.h>
#include "GameThread.h"

///////////////////////// static Member
int Window::g_WindowCount = 0;
void(__stdcall  *Window::m_LoopFunc)() = nullptr;
HINSTANCE Window::m_MainHInst;
std::map<std::wstring, WNDCLASSEXW> Window::g_WinClassMap; // Windowclass�� �����ϴ� �ڷᱸ��
std::map<std::wstring, HPTR<Window>> Window::g_WinMap; // Windowclass�� ���ؼ� ������� Window�� �����ϴ� �ڷᱸ��
Window* Window::m_MainWindow = nullptr;

int Window::_delta = 0;

Window* Window::MainWindow()
{
	return m_MainWindow;
}

///////////////////////// static MgrFunc
LRESULT CALLBACK Window::DEFMSG(HWND _HWnd, UINT _Msg, WPARAM _W, LPARAM _L)
{
	switch (_Msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		// �ڵ� ����̽� ���ؽ�Ʈ
		// 1. �⺻ ���� ������ ȭ�鿡 �����츦 �׸��� ���� ����.
		HDC hdc = BeginPaint(_HWnd, &ps);

		EndPaint(_HWnd, &ps);
	}
	break;
	case WM_SETCURSOR:
	{
		//SetCursor(NULL);
	}
	break;
	case WM_DESTROY:
	{
		// GetMessage�Լ����� 0�� �����ϰ� �ϴ� �Լ��� ���̴�.
		// PostQuitMessage(0);

		DestroyHWindow(_HWnd);
	}
	break;
		
	case WM_MOUSEWHEEL:
		_delta = (short)HIWORD(_W);
		break;
	default:
		// ���� ���Ǿ��Ѱ� �츮�� �⺻������ �������� �������
		// �޼����� ó���� �ٲ�... 
		return DefWindowProc(_HWnd, _Msg, _W, _L);
	}
	return 0;
}

void Window::Init(const HINSTANCE& _MainHInst)
{
	m_MainHInst = _MainHInst;

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = DEFMSG;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_MainHInst;
	wcex.hIcon = 0;// LoadIcon(hInstance, MAKEINTRESOURCE(IDI_AR22API));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;// MAKEINTRESOURCEW(IDC_AR22API);
	wcex.lpszClassName = L"Default"; // L"AR22API"
	wcex.hIconSm = 0;// LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	CreateHWindowClass(wcex);
}

bool Window::CreateHWindowClass(const WNDCLASSEXW& _wcex) 
{
	if (0 == RegisterClassExW(&_wcex))
	{
		BOOM;
		return false;
	}

	g_WinClassMap.insert(std::map<std::wstring, WNDCLASSEXW>::value_type(_wcex.lpszClassName, _wcex));

	return true;
}

WNDCLASSEXW Window::FindHWindowClass(const wchar_t* _Name)
{
	std::map<std::wstring, WNDCLASSEXW>::iterator FindIter = g_WinClassMap.find(_Name);

	if (g_WinClassMap.end() == FindIter)
	{
		WNDCLASSEXW W;
		W.hInstance = 0;
		return W;
	}
	return FindIter->second;
}

HPTR<Window> Window::FindHWindow(const wchar_t* _Name) 
{
	std::map<std::wstring, HPTR<Window>>::iterator FindIter = g_WinMap.find(_Name);

	if (g_WinMap.end() == FindIter)
	{
		return nullptr;
	}
	return FindIter->second;
}

// true�� ���� �Ϸ�.
bool Window::DestroyHWindow(HWND _HWnd) 
{
	std::map<std::wstring, HPTR<Window>>::iterator Loop = g_WinMap.begin();
	std::map<std::wstring, HPTR<Window>>::iterator End = g_WinMap.end();

	for (; Loop != End; ++Loop)
	{
		if (Loop->second->m_HWnd == _HWnd)
		{
			if (nullptr != Loop->second)
			{
				// delete Loop->second;
				Loop->second = nullptr;
			}
			g_WinMap.erase(Loop);
			--g_WindowCount;
			return true;
		}
	}

	return true;
}

HPTR<Window> Window::CreateHWindow(const wchar_t* _TitleName, bool _IsShow /*= true*/)
{
	return CreateHWindow(L"Default", _TitleName, _TitleName, _IsShow);
}

HPTR<Window> Window::CreateHWindow(const wchar_t* _WindowName, const wchar_t* _TitleName, bool _IsShow /*= true*/)
{
	return CreateHWindow(L"Default", _WindowName, _TitleName, _IsShow);
}
// /*= true*/ ����Ʈ ���ڴ� ���𿡼��� ����� �����ϴ�.
HPTR<Window> Window::CreateHWindow(const wchar_t* _ClassName, const wchar_t* _WindowName, const wchar_t* _TitleName, bool _IsShow /*= true*/)
{
	// �ڽ��� Ŭ���� ������ �ɹ��Լ��ϱ� �׾ȿ����� private�� public�̱� �빮�� �����ϴ�.
	// �� �̸��� �����찡 �־�?
	// �̹� �ִٸ� ���� �ʿ䵵 ����.
	if (g_WinMap.end() != g_WinMap.find(_WindowName))
	{
		BOOM;
		return nullptr;
	}

	// �� �׷� �̸��� �����찡 ������?
	// �����ϱ� ����� �ְڴ�?
	Window* NewWindow = new Window();
	NewWindow->SetName(_WindowName);

	// ����� �����ϱ� ��¥ ����� ����.
	if (false == NewWindow->Create(_ClassName, _TitleName))
	{
		// �����ߴٸ� ��Ʈ��.
		BOOM;
		delete NewWindow;
		return nullptr;
	}

	

	if (0 == g_WinMap.size())
	{
		m_MainWindow = NewWindow;
	}

	g_WinMap.insert(std::map<std::wstring, Window*>::value_type(_WindowName, NewWindow));

	if (true == _IsShow)
	{
		NewWindow->Show();
	}

	++g_WindowCount;

	// �ڵ��� ��Ȥ�� ���� ������ �Ǹ� ������ �뼭 �޴´�.
	return NewWindow;
}

void Window::AllWindowUpdate()
{
	std::map<std::wstring, HPTR<Window>>::iterator StartIter = g_WinMap.begin();
	std::map<std::wstring, HPTR<Window>>::iterator EndIter = g_WinMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		StartIter->second->Update();
	}
}

//////////////////////////////////// Member

// WS_OVERLAPPEDWINDOW ��Ÿ���� �츮�� �Ϲ������� �˰� �ִ�
// ����Ʈ ������ ��Ÿ��

bool Window::Create(const wchar_t* _Class, const wchar_t* _Title) 
{
	WNDCLASSEXW FindClass = FindHWindowClass(_Class);

	if (0 == FindClass.hInstance)
	{
		BOOM;
	}
	// = 10 | 20
	// or And
	m_iStyle = WS_OVERLAPPEDWINDOW;
	m_iMenu = TRUE;

	if (nullptr == FindClass.lpszMenuName)
	{
		m_iMenu = FALSE;
	}

	m_HWnd = CreateWindowW(_Class, _Title, m_iStyle,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_MainHInst, nullptr);

	if (nullptr == m_HWnd)
	{
		BOOM;
		return false;
	}

	m_HDC = GetDC(m_HWnd);

	if (nullptr == m_HDC)
	{
		BOOM;
		return false;
	}

	Init();

	return true;
}

void Window::Show() 
{
	ShowWindow(m_HWnd, SW_SHOW);
	UpdateWindow(m_HWnd);
}

void Window::Hide()
{
	ShowWindow(m_HWnd, SW_HIDE);
	UpdateWindow(m_HWnd);
}

Vector4 Window::Size()
{
	return m_WinSize;
}

void Window::Size(int _X, int _Y) 
{
	// �ý��� ���� ũ�⸦ ����ؼ� �־��ش� 

	m_WinSize.x = (float)_X;
	m_WinSize.y = (float)_Y;

	// ������ ������ + ũ��
	RECT Rc = {0, 0, _X, _Y};
	AdjustWindowRect(&Rc, m_iStyle, m_iMenu);
	SetWindowPos(m_HWnd, 0, 0, 0, Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOMOVE | SWP_NOZORDER);
}

void Window::Pos(int _X, int _Y) 
{
	SetWindowPos(m_HWnd, 0, _X, _Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void Window::SizeAndPos(int _PosX, int _PosY, int _SizeX, int _SizeY)
{
	Pos(_PosX, _PosY);
	Size(_SizeX, _SizeY);
}

void Window::Update() 
{
	m_PrevMosuePos = m_MosuePos;
	POINT PT;
	GetCursorPos(&PT);
	ScreenToClient(m_HWnd, &PT);
	m_MosuePos = { (float)PT.x, (float)PT.y };
}

Vector4 Window::MousePos() 
{
	return m_MosuePos;
}

Vector4 Window::MouseDir()
{
	return m_MosuePos - m_PrevMosuePos;
}

void Window::InsertOtherWindow(Window* _Win) 
{
	if (nullptr != FindHWindow(_Win->GetName()))
	{
		BOOM;
	}

	g_WinMap.insert(std::map<std::wstring, Window*>::value_type(_Win->GetName(), _Win));
	++g_WindowCount;
}

void Window::BasicPeekLoop(void(__stdcall *_LoopFunc)())
{
	m_LoopFunc = _LoopFunc;

	if (nullptr == m_LoopFunc)
	{
		return;
	}

	// SetExitFunc();

	MSG msg;
	while (0 != Window::WindowCount())
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// HWINDOW::Update();
			// �޽��� ����Ÿ���̶�� �ϴ� �ð���
			// �� ������ ������ ������.
			// �� ������ ������.
			// �Լ� ������.
			m_LoopFunc();
		}
	}

	// HRESMGR::Inst().Destroy();
	Thread::AllThreadReset();
}

void Window::Init() 
{
	RECT Rc;

	GetWindowRect(m_HWnd, &Rc);
	GetClientRect(m_HWnd, &Rc);
	m_WinSize.x = (float)Rc.right;
	m_WinSize.y = (float)Rc.bottom;
}

Vector4 Window::MousePosInt()
{
	Vector4 tmp = m_MosuePos;

	tmp.x = m_MosuePos.x * 0.01f - 8.0f;
	tmp.y = m_MosuePos.y *-0.01f + 4.5f;

	return tmp;
}