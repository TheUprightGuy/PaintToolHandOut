#include "ellipse.h"

CEllipse::CEllipse(COLORREF * _FillColor, int _iPenStyle, COLORREF * _PenColor, int _X, int _Y)
{
	m_iFillColor = _FillColor;
	m_iPenColor = _PenColor;

	m_iPenStyle = _iPenStyle;

	m_iStartX = _X;
	m_iStartY = _Y;
}

CEllipse::CEllipse()
{
}

CEllipse::~CEllipse()
{
}

void CEllipse::Draw(HDC _hdc)
{
	HPEN drawPen = CreatePen(m_iPenStyle, 10, *m_iPenColor);
	HBRUSH drawBrush = CreateSolidBrush(*m_iFillColor);

	SelectObject(_hdc, drawBrush);
	SelectObject(_hdc, drawPen);

	Ellipse(_hdc, m_iStartX, m_iStartY, m_iEndX, m_iEndY);
}
