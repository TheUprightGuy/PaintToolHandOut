#include "line.h"

CLine::CLine(int _iStyle, int* _iWidth, COLORREF* _newColor, int _iStartX, int _iStartY)
{
	m_iStyle = _iStyle;
	m_iWidth = _iWidth;
	m_Color = _newColor;
	
	/*SetStartX(_iStartX);
	SetStartY(_iStartY);*/

	m_iStartX = _iStartX;
	m_iStartY = _iStartY;
}

CLine::CLine()
{
}

CLine::~CLine()
{
}

void CLine::Draw(HDC _hdc)
{

	HPEN green_pen = CreatePen(m_iStyle, *m_iWidth, *m_Color);
	// Select the pen into the context:
	//HPEN old_pen = static_cast<HPEN>

	HPEN old_pen = static_cast<HPEN>(SelectObject(_hdc, green_pen));
	MoveToEx(_hdc, m_iStartX, m_iStartY, NULL); 
	LineTo(_hdc, m_iEndX, m_iEndY);

	SelectObject(_hdc, old_pen); // Restore old pen.

	DeleteObject(green_pen); // Delete the green pen.
							 
	//ReleaseDC(GetDC(_hdc), _hdc); // Release the DC.
}
