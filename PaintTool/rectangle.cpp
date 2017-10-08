#include "rectangle.h"

CRectangle::CRectangle(/*HBRUSHSTYLE _iBrushStyle, */int _iHatchStyle, COLORREF* _FillColor, int _iPenStyle, COLORREF* _PenColor, int _X, int Y)
{
	//m_iBrushStyle = _iBrushStyle;
	m_iHatchStyle = _iHatchStyle;
	m_iFillColor = _FillColor;
	m_iPenStyle = _iPenStyle;
	m_iPenColor = _PenColor;

	m_iStartX = _X;
	m_iStartY = _X;
}

CRectangle::CRectangle()
{
}

CRectangle::~CRectangle()
{
}

void CRectangle::Draw(HDC _hdc)
{
	HPEN drawPen = CreatePen(m_iPenStyle, 10, *m_iPenColor);
	HBRUSH drawBrush = CreateSolidBrush(*m_iFillColor);

	SelectObject(_hdc, drawBrush);
	SelectObject(_hdc, drawPen);

	Rectangle(_hdc, m_iStartX, m_iStartY, m_iEndX, m_iEndY);
}
