#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

//	Library Includes
#include <windows.h>
#include <windowsx.h>
#include "shape.h"


enum EBRUSHSTYLE
{
	NOSTYLE = -1,
	SOLID,
	HATCH
};

class CRectangle : public IShape
{
public:
	CRectangle(bool* _iBrushStyle, int _iHatchStyle, COLORREF* _FillColor, int _iPenStyle, COLORREF* _PenColor, int _X, int _Y);
	CRectangle();
	virtual ~CRectangle();

	virtual void Draw(HDC _hdc);
	void SetBrushStyle(bool* _brushStyle) { m_iBrushStyle = _brushStyle; }
	void SetFillColor(COLORREF* _newColor) { m_Color = _newColor; }
	void SetPenStyle(int _iPenStyle) { m_iPenStyle = _iPenStyle; }
	void SetPenColor(COLORREF* _newColor) { m_iPenColor = _newColor; }
	void SetHatchStyle(int _iHatchStyle) { m_iHatchStyle = _iHatchStyle; }
	

private:
	bool* m_iBrushStyle;
	int m_iHatchStyle;
	COLORREF* m_iFillColor;
	int m_iPenStyle;
	COLORREF* m_iPenColor;

	COLORREF* m_Color;
};

#endif