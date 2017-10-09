#ifndef __ELLIPSE_H__
#define __ELLIPSE_H__

//	Library Includes
#include <windows.h>
#include <windowsx.h>

#include "shape.h"

class CEllipse : public IShape
{
public:
	CEllipse(COLORREF* _FillColor, int _iPenStyle, COLORREF* _PenColor, int _X, int _Y);
	CEllipse();
	virtual ~CEllipse();

	virtual void Draw(HDC _hdc);
	void SetColor(COLORREF* _newColor) { _newColor = m_Color; }


private:
	COLORREF* m_iFillColor;
	int m_iPenStyle;
	COLORREF* m_iPenColor;

	COLORREF* m_Color;
};

#endif