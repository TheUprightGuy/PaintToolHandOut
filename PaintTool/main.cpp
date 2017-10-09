
//#define WIN32_LEAN_AND_MEAN

#include <windows.h>   // Include all the windows headers.
#include <windowsx.h>  // Include useful macros.
#include <strstream>
#include <sstream>
#include <string>

#include "resource.h"
#include "shape.h"
#include "line.h"
#include "canvas.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polygon.h"
#include "stamp.h"
#include "backBuffer.h"

#define WINDOW_CLASS_NAME L"WINCLASS1"

//Global variables
HINSTANCE g_hInstance;
CCanvas* g_pCanvas;
IShape* g_pShape = 0;
HMENU g_hMenu;

HWND g_Dialog;

int g_iWidth;
//Enum to decalre the type of tool supported by the application.
enum ESHAPE
{
	FREEHAND = 0,
	LINESHAPE,
	RECTANGLESHAPE,
	ELLIPSESHAPE,
	POLYGONSHAPE,
	STAMP
};


void GameLoop()
{
	//One frame of game logic occurs here...
}

//Taken from MDS GD1M02Calc
template<typename T>
std::string ToString(const T& _value)
{
	std::strstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

template<typename T>
std::wstring ToWideString(const T& _value)
{
	std::wstringstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

void WriteToEditBox(HWND _hDlg, int _iResourceID, float _fValue)
{
	std::wstring _strValue = ToWideString(_fValue);
	SetDlgItemText(_hDlg, _iResourceID, _strValue.c_str());
}

float ReadFromEditBox(HWND _hDlg, int _iResourceID)
{
	wchar_t _pcValue[10];
	ZeroMemory(_pcValue, 10);
	GetDlgItemText(_hDlg, _iResourceID, _pcValue, 10);
	if (_pcValue[0] == 0)
	{
		return 0.0f;
	}
	else
	{
		return static_cast<float>(_wtof(_pcValue));
	}
}
////////////////////////////////////////////////////

LRESULT CALLBACK DialogProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	static int test;


	switch (_msg)
	{
	case WM_INITDIALOG:
	{
		WriteToEditBox(_hwnd, IDC_EDIT1, 10);
		SendMessage(_hwnd, SBM_SETRANGE, 10, 100);
		SendMessage(_hwnd, SBM_SETPOS, 10, TRUE);
	//	int test;
	}
	break;
	case WM_HSCROLL:
	{
		switch (LOWORD(_wparam)) {
			case SB_THUMBTRACK:
			{
				DWORD value = HIWORD(_wparam);
				WriteToEditBox(_hwnd, IDC_EDIT1, value);
			}
			default:break;
			}
		
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
		case IDCANCEL:
		{
			ShowWindow(_hwnd, SW_HIDE);
			return TRUE;
		}
			break;

		case IDOK:
		{
			g_iWidth = ReadFromEditBox(_hwnd, IDC_EDIT1);
			ShowWindow(_hwnd, SW_HIDE);
			return TRUE;
		}
			break;
		default:
			break;
		}
	}
	break;
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}


LRESULT CALLBACK WindowProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	// This is the main message handler of the system.
	PAINTSTRUCT ps; // Used in WM_PAINT.
	HDC hdc;        // Handle to a device context.
	
	static POINT mouseStart;
	static POINT mouseEnd;
	static bool bDrawing;

	static COLORREF rgbBrushCurrent;
	static COLORREF rgbPenCurrent;
	static COLORREF CustCol[16];
	static CHOOSECOLOR cc;
	 

	switch (_msg)
	{
	case WM_CREATE:
	{
		// Do initialization stuff here.
		g_iWidth = 10;
		// Return Success.
		return (0);
	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(_hwnd, &ps);
		// You would do all your painting here...
		
		if (!bDrawing)
		{

		}

		EndPaint(_hwnd, &ps);
		// Return Success.
		return (0);
	}
	break;
	case WM_MOUSEMOVE:
	{
		break;
	}
	case WM_LBUTTONDOWN:
	{
		if (g_pShape != NULL)
		{
			bDrawing = true;
			mouseStart.x = static_cast<int>(LOWORD(_lparam));
			mouseStart.y = static_cast<int>(HIWORD(_lparam));
		}
	
		break;
	}
	case WM_LBUTTONUP:
	{
		if (bDrawing)
		{
			bDrawing = false;
			mouseEnd.x = static_cast<int>(LOWORD(_lparam));
			mouseEnd.y = static_cast<int>(HIWORD(_lparam));

			g_pShape->SetStartX(mouseStart.x);
			g_pShape->SetStartY(mouseStart.y);
			g_pShape->SetEndX(mouseEnd.x);
			g_pShape->SetEndY(mouseEnd.y);

			g_pShape->Draw(GetDC(_hwnd));	
		}
		

		break;
	}

	case WM_COMMAND:
	{

		switch (LOWORD(_wparam))
		{
		case ID_SHAPE_LINE:
		{
			g_pShape = new CLine(0, &g_iWidth, &rgbPenCurrent, mouseStart.x, mouseStart.y);
			break;
		}
		case ID_SHAPE_R:
		{
			g_pShape = new CRectangle(0, &rgbBrushCurrent, 0, &rgbPenCurrent, mouseStart.x, mouseStart.y);
			break;
		}
		case ID_SHAPE_ELLIPSE:
		{
			g_pShape = new CEllipse(&rgbBrushCurrent, 0 , &rgbPenCurrent, mouseStart.x, mouseStart.y);
			break;
		}
		case ID_PEN_WIDTH:
		{
			ShowWindow(g_Dialog, SW_SHOWNORMAL);
			break;
		}
		case ID_PEN_COLOR:
		{
			cc;
			cc.lStructSize = sizeof(cc);
			cc.hwndOwner = _hwnd;
			cc.lpCustColors = CustCol;
			cc.rgbResult = rgbPenCurrent;
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;
				
			ChooseColor(&cc);
			rgbPenCurrent = cc.rgbResult;

			break;
		}
		case ID_BRUSH_COLOR:
		{
			cc;
			cc.lStructSize = sizeof(cc);
			cc.hwndOwner = _hwnd;
			cc.lpCustColors = CustCol;
			cc.rgbResult = rgbBrushCurrent;
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;
				
			ChooseColor(&cc);
			rgbBrushCurrent = cc.rgbResult;

			break;
		}
		case ID_FILE_EXIT:
		{
			PostQuitMessage(0);
			bDrawing = false;
			break;
		}
		case ID_HELP_ABOUT:
		{
			MessageBox(_hwnd, L"This paint tool was developed by .............", L"Author Information", MB_OK | MB_ICONINFORMATION);
			break;
		}
		default:
			break;
		}

		return(0);
	}
	break;

	case WM_DESTROY:
	{
		// Kill the application, this sends a WM_QUIT message.
		PostQuitMessage(0);

		// Return success.
		return (0);
	}
	break;

		default:break;
	} // End switch.

	  // Process any messages that we did not take care of...

	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}

int WINAPI WinMain(HINSTANCE _hInstance,
	HINSTANCE _hPrevInstance,
	LPSTR _lpCmdLine,
	int _nCmdShow)
{
	WNDCLASSEX winclass; // This will hold the class we create.
	HWND hwnd;           // Generic window handle.
	//trackbar;
	MSG msg;             // Generic message.

	g_hInstance = _hInstance;
	// First fill in the window class structure.
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground =
		static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the window class
	if (!RegisterClassEx(&winclass))
	{
		return (0);
	}

	g_hMenu = LoadMenu(_hInstance, MAKEINTRESOURCE(IDR_MENU1));
	// create the window
	hwnd = CreateWindowEx(NULL, // Extended style.
		WINDOW_CLASS_NAME,      // Class.
		L"Jack's Paint Tool",   // Title.
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100,                    // Initial x,y.
		1500, 800,                // Initial width, height.
		NULL,                   // Handle to parent.
		g_hMenu,                   // Handle to menu.
		_hInstance,             // Instance of this application.
		NULL);                  // Extra creation parameters.

	if (!(hwnd))
	{
		return (0);
	}

	g_Dialog = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DialogProc);

	// Enter main event loop
	while (true)
	{
		// Test if there is a message in queue, if so get it.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Test if this is a quit.
			if (msg.message == WM_QUIT)
			{
				break;
			}

			if (g_Dialog == 0 ||
				!IsDialogMessage(g_Dialog, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}

		// Main game processing goes here.
		GameLoop(); //One frame of game logic occurs here...
	}

	// Return to Windows like this...
	return (static_cast<int>(msg.wParam));
}
