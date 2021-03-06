#ifndef __LINE_H__
#define __LINE_H__

//	Library Includes
#include <windows.h>
#include <windowsx.h>
//#include <gdiplus.h>
#include "shape.h"

class CLine : public IShape
{
public:
	//CLine(int _iStartX, int _iStartY, int _iEndX, int _iEndY, COLORREF _newColour, int _iStyle, int _iWidth); 
	CLine(int _iStyle, int* _iWidth, COLORREF* _newColor, int _iStartX, int _iStartY);
	CLine();
	virtual ~CLine();

	virtual void Draw(HDC _hdc);
	void SetWidth(int* _iNewWidth) { m_iWidth = _iNewWidth; }
	int* GetWidth(int* _iNewWidth) { return(m_iWidth); }


private:
	
	int m_iStyle;
	int* m_iWidth;
	COLORREF* m_Color;
};

#endif