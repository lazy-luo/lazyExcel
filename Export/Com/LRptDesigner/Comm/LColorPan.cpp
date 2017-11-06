///////////////////////////////////////////////////////////////////////////////////////////////
//@模块		:	颜色选择菜单
//@作者		:	罗智勇
//@创建时间	:	2005-09-16
///////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LColorPan.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define MAX_COLORS      100
#define DEFAULT_BOX_VALUE -3
#define CUSTOM_BOX_VALUE  -2
#define INVALID_COLOR    -1

ColorTableEntry CLColorPan::m_crColors[] = 
{
    { RGB(0x00, 0x00, 0x00),    _T("黑色")             },
    { RGB(0xA5, 0x2A, 0x00),    _T("褐色")             },
    { RGB(0x00, 0x40, 0x40),    _T("橄榄绿")  },
    { RGB(0x00, 0x55, 0x00),    _T("深绿")        },
    { RGB(0x00, 0x00, 0x5E),    _T("深灰蓝")         },
    { RGB(0x00, 0x00, 0x8B),    _T("深蓝")         },
    { RGB(0x4B, 0x00, 0x82),    _T("靛蓝")            },
    { RGB(0x28, 0x28, 0x28),    _T("灰色-80%")         },

    { RGB(0x8B, 0x00, 0x00),    _T("深红")          },
    { RGB(0xFF, 0x68, 0x20),    _T("桔黄")            },
    { RGB(0x8B, 0x8B, 0x00),    _T("深黄")       },
    { RGB(0x00, 0x93, 0x00),    _T("绿色")             },
    { RGB(0x38, 0x8E, 0x8E),    _T("青色")              },
    { RGB(0x00, 0x00, 0xFF),    _T("蓝色")              },
    { RGB(0x7B, 0x7B, 0xC0),    _T("蓝-灰")         },
    { RGB(0x66, 0x66, 0x66),    _T("灰色-50%")         },

    { RGB(0xFF, 0x00, 0x00),    _T("红色")               },
    { RGB(0xFF, 0xAD, 0x5B),    _T("浅桔黄")      },
    { RGB(0x32, 0xCD, 0x32),    _T("酸橙色")              }, 
    { RGB(0x3C, 0xB3, 0x71),    _T("海绿")         },
    { RGB(0x7F, 0xFF, 0xD4),    _T("宝石蓝")              },
    { RGB(0x7D, 0x9E, 0xC0),    _T("浅蓝")        },
    { RGB(0x80, 0x00, 0x80),    _T("紫色")            },
    { RGB(0x7F, 0x7F, 0x7F),    _T("灰色-40%")         },

    { RGB(0xFF, 0xC0, 0xCB),    _T("粉红")              },
    { RGB(0xFF, 0xD7, 0x00),    _T("金色")              },
    { RGB(0xFF, 0xFF, 0x00),    _T("黄色")            },    
    { RGB(0x00, 0xFF, 0x00),    _T("鲜绿")      },
    { RGB(0x40, 0xE0, 0xD0),    _T("青绿")         },
    { RGB(0xC0, 0xFF, 0xFF),    _T("天蓝")           },
    { RGB(0x48, 0x00, 0x48),    _T("梅红")              },
    { RGB(0xC0, 0xC0, 0xC0),    _T("灰色-25%")        },

    { RGB(0xFF, 0xE4, 0xE1),    _T("玫瑰红")              },
    { RGB(0xD2, 0xB4, 0x8C),    _T("棕黄")               },
    { RGB(0xFF, 0xFF, 0xE0),    _T("浅黄")      },
    { RGB(0x98, 0xFB, 0x98),    _T("浅绿")       },
    { RGB(0xAF, 0xEE, 0xEE),    _T("浅青绿")    },
    { RGB(0x68, 0x83, 0x8B),    _T("淡蓝")         },
    { RGB(0xE6, 0xE6, 0xFA),    _T("淡紫")          },
    { RGB(0xFF, 0xFF, 0xFF),    _T("白色")             }
};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLColorPan::CLColorPan(CPoint p, COLORREF pClr, CWnd* pParentWnd,
                LPCTSTR szDefaultText /* = NULL */,
                LPCTSTR szCustomText  /* = NULL */)
{
	m_strDefaultText = (szDefaultText)? szDefaultText : _T("自动");
    m_strCustomText  = (szCustomText)?  szCustomText  : _T("其他颜色...");
	Create(p,NULL,pParentWnd);
	FindCellFromColor(pClr);
	m_crColor          = m_crInitialColor =pClr;
	Invalidate();
}

CLColorPan::~CLColorPan()
{
	m_Font.DeleteObject();
    m_Palette.DeleteObject();
}

void CLColorPan::Initialise()
{
	m_nNumColors       = sizeof(m_crColors)/sizeof(ColorTableEntry);
    ASSERT(m_nNumColors <= MAX_COLORS);
    if (m_nNumColors > MAX_COLORS)
        m_nNumColors = MAX_COLORS;
	
    m_nNumColumns       = 0;
    m_nNumRows          = 0;
    m_nBoxSize          = 18;
    m_nMargin           = ::GetSystemMetrics(SM_CXEDGE);
    m_nCurrentSel       = INVALID_COLOR;
    m_nChosenColorSel  = INVALID_COLOR;
    
    if (m_nBoxSize - 2*m_nMargin - 2 < 5) m_nBoxSize = 5 + 2*m_nMargin + 2;
    //字体
    NONCLIENTMETRICS ncm;
    ncm.cbSize = sizeof(NONCLIENTMETRICS);
    VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));
    m_Font.CreateFontIndirect(&(ncm.lfMessageFont));

    //创建调色板
    struct {
        LOGPALETTE    LogPalette;
        PALETTEENTRY  PalEntry[MAX_COLORS];
    } pal;

    LOGPALETTE* pLogPalette = (LOGPALETTE*) &pal;
    pLogPalette->palVersion    = 0x300;
    pLogPalette->palNumEntries = (WORD) m_nNumColors; 

    for (int i = 0; i < m_nNumColors; i++)
    {
        pLogPalette->palPalEntry[i].peRed   = GetRValue(m_crColors[i].crColor);
        pLogPalette->palPalEntry[i].peGreen = GetGValue(m_crColors[i].crColor);
        pLogPalette->palPalEntry[i].peBlue  = GetBValue(m_crColors[i].crColor);
        pLogPalette->palPalEntry[i].peFlags = 0;
    }
	
    m_Palette.CreatePalette(pLogPalette);
}
void CLColorPan::OnDraw(CDC* pDC,const RECT& rctClip)
{
	if (m_strDefaultText.GetLength())
        DrawCell(pDC, DEFAULT_BOX_VALUE);
    for (int i = 0; i < m_nNumColors; i++)
        DrawCell(pDC, i);
    if (m_strCustomText.GetLength())
        DrawCell(pDC, CUSTOM_BOX_VALUE);

}
void CLColorPan::GetWindowSize(CRect& rct)
{
	CSize TextSize;
    if (m_strCustomText.GetLength() || m_strDefaultText.GetLength())
    {
        CClientDC dc(this);
        CFont* pOldFont = (CFont*) dc.SelectObject(&m_Font);
        TextSize = CSize(0,0);
        if (m_strCustomText.GetLength())
            TextSize = dc.GetTextExtent(m_strCustomText);
        if (m_strDefaultText.GetLength())
        {
            CSize DefaultSize = dc.GetTextExtent(m_strDefaultText);
            if (DefaultSize.cx > TextSize.cx) TextSize.cx = DefaultSize.cx;
            if (DefaultSize.cy > TextSize.cy) TextSize.cy = DefaultSize.cy;
        }

        dc.SelectObject(pOldFont);
        TextSize += CSize(2*m_nMargin,2*m_nMargin);

        TextSize.cy += 2*m_nMargin + 2;
    }
    //m_nNumColumns = (int) sqrt((double)m_nNumColors);    // for a square window (yuk)
    m_nNumColumns = 8;
    m_nNumRows = m_nNumColors / m_nNumColumns;
    if (m_nNumColors % m_nNumColumns) m_nNumRows++;
    CRect rect;
    GetWindowRect(rect);

    rct.SetRect(rect.left, rect.top, 
                         rect.left + m_nNumColumns*m_nBoxSize + 2*m_nMargin,
                         rect.top  + m_nNumRows*m_nBoxSize + 2*m_nMargin);

    if (m_strDefaultText.GetLength()) 
    {
        if (TextSize.cx > rct.Width())
            rct.right = rct.left + TextSize.cx;
        TextSize.cx = rct.Width()-2*m_nMargin;
        m_DefaultTextRect.SetRect(m_nMargin, m_nMargin, 
                                  m_nMargin+TextSize.cx, 2*m_nMargin+TextSize.cy);
        rct.bottom += m_DefaultTextRect.Height() + 2*m_nMargin;
    }

    if (m_strCustomText.GetLength()) 
    {
        if (TextSize.cx > rct.Width())
            rct.right = rct.left + TextSize.cx;
        TextSize.cx = rct.Width()-2*m_nMargin;

        m_CustomTextRect.SetRect(m_nMargin, rct.Height(), 
                                 m_nMargin+TextSize.cx, 
                                 rct.Height()+m_nMargin+TextSize.cy);
        rct.bottom += m_CustomTextRect.Height() + 2*m_nMargin;
   }

    CSize ScreenSize(::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN));
    if (rct.right > ScreenSize.cx)
        rct.OffsetRect(-(rct.right - ScreenSize.cx), 0);
    if (rct.left < 0)
        rct.OffsetRect( -rct.left, 0);
	
    if (rct.bottom > ScreenSize.cy)
    {
        CRect ParentRect;
        m_pParent->GetWindowRect(ParentRect);
        rct.OffsetRect(0, -(ParentRect.Height() + rct.Height()));
    }
}
LPVOID CLColorPan::GetSelectValue(int& nMessage)
{
	COLORREF clr=GetColor(m_nCurrentSel);
	if (nMessage != LPN_SELENDCANCEL && m_nCurrentSel == CUSTOM_BOX_VALUE)
    {
		ShowWindow(SW_HIDE);
        CColorDialog dlg(m_crInitialColor, CC_FULLOPEN | CC_ANYCOLOR, 
			this->GetParent()->GetParent());
		
        if (dlg.DoModal() == IDOK)
            clr = dlg.GetColor();
        else
            nMessage = LPN_SELENDCANCEL;

    } 
	
    if (nMessage == LPN_SELENDCANCEL)
        clr = m_crInitialColor;
	return (LPVOID)clr;
}
//鼠标离开事件
void CLColorPan::OnMouseOut()
{
	CClientDC dc(this);
	DrawCell(&dc, m_nCurrentSel,TRUE);
	m_nCurrentSel=INVALID_COLOR;
}
BOOL CLColorPan::GetCellRect(int nIndex, const LPRECT& rect)
{
    if (nIndex == CUSTOM_BOX_VALUE)
    {
        ::SetRect(rect, 
                  m_CustomTextRect.left,  m_CustomTextRect.top,
                  m_CustomTextRect.right, m_CustomTextRect.bottom);
        return TRUE;
    }
    else if (nIndex == DEFAULT_BOX_VALUE)
    {
        ::SetRect(rect, 
                  m_DefaultTextRect.left,  m_DefaultTextRect.top,
                  m_DefaultTextRect.right, m_DefaultTextRect.bottom);
        return TRUE;
    }

    if (nIndex < 0 || nIndex >= m_nNumColors)
        return FALSE;

    rect->left = GetColumn(nIndex) * m_nBoxSize + m_nMargin;
    rect->top  = GetRow(nIndex) * m_nBoxSize + m_nMargin;

    if (m_strDefaultText.GetLength()) 
        rect->top += (m_nMargin + m_DefaultTextRect.Height());

    rect->right = rect->left + m_nBoxSize;
    rect->bottom = rect->top + m_nBoxSize;

    return TRUE;
}
void CLColorPan::FindCellFromColor(COLORREF crColor)
{
	if (crColor == CLR_DEFAULT && m_strDefaultText.GetLength())
    {
        m_nChosenColorSel = DEFAULT_BOX_VALUE;
        return;
    }

    for (int i = 0; i < m_nNumColors; i++)
    {
        if (GetColor(i) == crColor)
        {
            m_nChosenColorSel = i;
            return;
        }
    }

    if (m_strCustomText.GetLength())
        m_nChosenColorSel = CUSTOM_BOX_VALUE;
    else
        m_nChosenColorSel = INVALID_COLOR;
}
void CLColorPan::CreateToolTips()
{
    if (!m_ToolTip.Create(this)) return;

	m_ToolTip.ModifyStyle(WS_CHILD,TTS_ALWAYSTIP );
	m_ToolTip.Update();
    for (int i = 0; i < m_nNumColors; i++)
    {
        CRect rect;
        if (!GetCellRect(i, rect)) continue;
            m_ToolTip.AddTool(this, GetColorName(i), rect, 1);
    }
}

int CLColorPan::GetIndex(int row, int col) const
{ 
    if ((row == CUSTOM_BOX_VALUE || col == CUSTOM_BOX_VALUE) && m_strCustomText.GetLength())
        return CUSTOM_BOX_VALUE;
    else if ((row == DEFAULT_BOX_VALUE || col == DEFAULT_BOX_VALUE) && m_strDefaultText.GetLength())
        return DEFAULT_BOX_VALUE;
    else if (row < 0 || col < 0 || row >= m_nNumRows || col >= m_nNumColumns)
        return INVALID_COLOR;
    else
    {
        if (row*m_nNumColumns + col >= m_nNumColors)
            return INVALID_COLOR;
        else
            return row*m_nNumColumns + col;
    }
}

int CLColorPan::GetRow(int nIndex) const               
{ 
    if (nIndex == CUSTOM_BOX_VALUE && m_strCustomText.GetLength())
        return CUSTOM_BOX_VALUE;
    else if (nIndex == DEFAULT_BOX_VALUE && m_strDefaultText.GetLength())
        return DEFAULT_BOX_VALUE;
    else if (nIndex < 0 || nIndex >= m_nNumColors)
        return INVALID_COLOR;
    else
        return nIndex / m_nNumColumns; 
}

int CLColorPan::GetColumn(int nIndex) const            
{ 
    if (nIndex == CUSTOM_BOX_VALUE && m_strCustomText.GetLength())
        return CUSTOM_BOX_VALUE;
    else if (nIndex == DEFAULT_BOX_VALUE && m_strDefaultText.GetLength())
        return DEFAULT_BOX_VALUE;
    else if (nIndex < 0 || nIndex >= m_nNumColors)
        return INVALID_COLOR;
    else
        return nIndex % m_nNumColumns; 
}

void CLColorPan::DrawCell(CDC* pDC, int nIndex,BOOL bMouseOut)
{
    if (m_strCustomText.GetLength() && nIndex == CUSTOM_BOX_VALUE)
    {
        CRect TextButtonRect = m_CustomTextRect;
        TextButtonRect.top += 2*m_nMargin;
		
        //填充背景色
        pDC->FillSolidRect(TextButtonRect, ::GetSysColor(COLOR_3DFACE));
		
        //画水平分隔线
        pDC->FillSolidRect(m_CustomTextRect.left+2*m_nMargin, m_CustomTextRect.top,
                           m_CustomTextRect.Width()-4*m_nMargin, 1, ::GetSysColor(COLOR_3DSHADOW));
        pDC->FillSolidRect(m_CustomTextRect.left+2*m_nMargin, m_CustomTextRect.top+1,
                           m_CustomTextRect.Width()-4*m_nMargin, 1, ::GetSysColor(COLOR_3DHILIGHT));
        TextButtonRect.DeflateRect(1,1);
		
        // 填充背景色
        if ((m_nChosenColorSel == nIndex && m_nCurrentSel != nIndex) || (bMouseOut && m_nChosenColorSel == nIndex)){
			HBRUSH hBrush=HBrushDitherCreate(RGB(192,192,192),RGB(255,255,255));
			CBrush brush;
			brush.Attach(hBrush);
			pDC->FillRect(&TextButtonRect,&brush);
			brush.Detach();
			DeleteObject(hBrush);
            //pDC->FillSolidRect(TextButtonRect, ::GetSysColor(COLOR_3DLIGHT));
        }else
            pDC->FillSolidRect(TextButtonRect, ::GetSysColor(COLOR_3DFACE));
		
        //画单元
        if (m_nCurrentSel == nIndex  && m_nChosenColorSel != nIndex && !bMouseOut) 
            pDC->DrawEdge(TextButtonRect, BDR_RAISEDINNER, BF_RECT);
        else if (m_nChosenColorSel == nIndex)
            pDC->DrawEdge(TextButtonRect, BDR_SUNKENOUTER, BF_RECT);
		
        CFont *pOldFont = (CFont*) pDC->SelectObject(&m_Font);
        pDC->SetBkMode(TRANSPARENT);
        pDC->DrawText(m_strCustomText, TextButtonRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        pDC->SelectObject(pOldFont);
		
        return;
    }
	
    if (m_strDefaultText.GetLength() && nIndex == DEFAULT_BOX_VALUE)
    {
        pDC->FillSolidRect(m_DefaultTextRect, ::GetSysColor(COLOR_3DFACE));
        CRect TextButtonRect = m_DefaultTextRect;
        TextButtonRect.DeflateRect(1,1);

        if ((m_nChosenColorSel == nIndex && m_nCurrentSel != nIndex) || (bMouseOut && m_nChosenColorSel == nIndex)){
			HBRUSH hBrush=HBrushDitherCreate(RGB(192,192,192),RGB(255,255,255));
			CBrush brush;
			brush.Attach(hBrush);
			pDC->FillRect(&TextButtonRect,&brush);
			brush.Detach();
			DeleteObject(hBrush);
            //pDC->FillSolidRect(TextButtonRect, ::GetSysColor(COLOR_3DLIGHT));
        }else
            pDC->FillSolidRect(TextButtonRect, ::GetSysColor(COLOR_3DFACE));

        CRect LineRect = TextButtonRect;
        LineRect.DeflateRect(2*m_nMargin,2*m_nMargin);
        CPen pen(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));
        CPen* pOldPen = pDC->SelectObject(&pen);
        pDC->SelectStockObject(NULL_BRUSH);
        pDC->Rectangle(LineRect);
        pDC->SelectObject(pOldPen);

        if (m_nCurrentSel == nIndex && m_nChosenColorSel != nIndex && !bMouseOut){
            pDC->DrawEdge(TextButtonRect, BDR_RAISEDINNER, BF_RECT);
        }else if (m_nChosenColorSel == nIndex)
            pDC->DrawEdge(TextButtonRect, BDR_SUNKENOUTER, BF_RECT);

        CFont *pOldFont = (CFont*) pDC->SelectObject(&m_Font);
        pDC->SetBkMode(TRANSPARENT);
        pDC->DrawText(m_strDefaultText, TextButtonRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        pDC->SelectObject(pOldFont);

        return;
    }        

    CRect rect;
    if (!GetCellRect(nIndex, rect)) return;

    CPalette* pOldPalette = NULL;
    if (pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
    {
        pOldPalette = pDC->SelectPalette(&m_Palette, FALSE);
        pDC->RealizePalette();
    }

    if ((m_nChosenColorSel == nIndex && m_nCurrentSel != nIndex) || (bMouseOut && m_nChosenColorSel == nIndex)){
		HBRUSH hBrush=HBrushDitherCreate(RGB(192,192,192),RGB(255,255,255));
		CBrush brush;
		brush.Attach(hBrush);
		pDC->FillRect(&rect,&brush);
		brush.Detach();
		DeleteObject(hBrush);
        //pDC->FillSolidRect(rect, ::GetSysColor(COLOR_3DHILIGHT));
    }else 
        pDC->FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));

    if (m_nCurrentSel == nIndex && m_nChosenColorSel != nIndex && !bMouseOut) 
        pDC->DrawEdge(rect, BDR_RAISEDINNER, BF_RECT);
    else if (m_nChosenColorSel == nIndex)
        pDC->DrawEdge(rect, BDR_SUNKENOUTER, BF_RECT);

    CBrush brush(PALETTERGB(GetRValue(GetColor(nIndex)), 
                            GetGValue(GetColor(nIndex)), 
                            GetBValue(GetColor(nIndex)) ));
    CPen   pen;
    pen.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));

    CBrush* pOldBrush = (CBrush*) pDC->SelectObject(&brush);
    CPen*   pOldPen   = (CPen*)   pDC->SelectObject(&pen);


    rect.DeflateRect(m_nMargin+1, m_nMargin+1);
    pDC->Rectangle(rect);

    pDC->SelectObject(pOldBrush);
    pDC->SelectObject(pOldPen);
    brush.DeleteObject();
    pen.DeleteObject();

    if (pOldPalette && pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
        pDC->SelectPalette(pOldPalette, FALSE);
}

void CLColorPan::ChangeSelection(int nIndex)
{
    CClientDC dc(this);        

    if (nIndex > m_nNumColors)
        nIndex = CUSTOM_BOX_VALUE; 

    if ((m_nCurrentSel >= 0 && m_nCurrentSel < m_nNumColors) ||
        m_nCurrentSel == CUSTOM_BOX_VALUE || m_nCurrentSel == DEFAULT_BOX_VALUE)
    {
        
        int OldSel = m_nCurrentSel;
        m_nCurrentSel = INVALID_COLOR;
        DrawCell(&dc, OldSel);
    }

    m_nCurrentSel = nIndex;
    DrawCell(&dc, m_nCurrentSel);

    if (m_nCurrentSel == CUSTOM_BOX_VALUE)
        m_pParent->SendMessage(LPN_SELCHANGE, (WPARAM) m_crInitialColor, 0);
    else if (m_nCurrentSel == DEFAULT_BOX_VALUE)
    {
        m_crColor = CLR_DEFAULT;
        m_pParent->SendMessage(LPN_SELCHANGE, (WPARAM) CLR_DEFAULT, 0);
    }
    else
    {
        m_crColor = GetColor(m_nCurrentSel);
        m_pParent->SendMessage(LPN_SELCHANGE, (WPARAM) m_crColor, 0);
    }
}
void CLColorPan::OnMouseOver(UINT nFlags, CPoint point) 
{
	int nNewSelection = INVALID_COLOR;

	point.x -= m_nMargin;
	point.y -= m_nMargin;

	if (m_strCustomText.GetLength() && m_CustomTextRect.PtInRect(point))
		nNewSelection = CUSTOM_BOX_VALUE;
	else if (m_strDefaultText.GetLength() && m_DefaultTextRect.PtInRect(point))
		nNewSelection = DEFAULT_BOX_VALUE;
	else
	{
		if (m_strDefaultText.GetLength()) 
			point.y -= m_DefaultTextRect.Height();  

		nNewSelection = GetIndex(point.y / m_nBoxSize, point.x / m_nBoxSize);

		if (nNewSelection < 0 || nNewSelection >= m_nNumColors)
		{
			return;
		}
	}
	if (nNewSelection != m_nCurrentSel)
		ChangeSelection(nNewSelection);
    
}

void CLColorPan::ShowToolTips(LPMSG lpMsg)
{
	if(m_ToolTip.m_hWnd){
		m_ToolTip.RelayEvent(lpMsg);
	}
}
