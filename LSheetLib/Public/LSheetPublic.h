#ifndef _LSHEETPUBLIC_H_
#define _LSHEETPUBLIC_H_
#include "../../LGridLib/Src/LGrid.h"
#ifdef _WIN32
	#include "../../OSFace/WIN32/GDI/LPrintDC.h"
#else
	#include "../../OSFace/Linux/GDI/LPrintDC.h"
#endif
#include "../../LComm/LMemDC.h"
#include "../../LComm/LClipDC.h"

#include "LSheetApi.h"
#endif