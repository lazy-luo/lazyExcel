# Microsoft Developer Studio Generated NMAKE File, Based on LSheetLib.dsp
!IF "$(CFG)" == ""
CFG=LSheetLib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to LSheetLib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LSheetLib - Win32 Release" && "$(CFG)" != "LSheetLib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LSheetLib.mak" CFG="LSheetLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LSheetLib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LSheetLib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "LSheetLib - Win32 Release"

OUTDIR=.\Bin/Release
INTDIR=.\Bin/Release
# Begin Custom Macros
OutDir=.\Bin/Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\Bin\LSheetLib.dll" "$(OUTDIR)\LSheetLib.bsc"

!ELSE 

ALL : "LGridLib - Win32 Release" ".\Bin\LSheetLib.dll" "$(OUTDIR)\LSheetLib.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LGridLib - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\LSheet.obj"
	-@erase "$(INTDIR)\LSheet.sbr"
	-@erase "$(INTDIR)\LSheetLib.obj"
	-@erase "$(INTDIR)\LSheetLib.pch"
	-@erase "$(INTDIR)\LSheetLib.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LSheetLib.bsc"
	-@erase "$(OUTDIR)\LSheetLib.exp"
	-@erase "$(OUTDIR)\LSheetLib.lib"
	-@erase ".\Bin\LSheetLib.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LSHEETLIB_EXPORTS" /D "LGRIDLIB_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LSheetLib.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LSheetLib.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\LSheet.sbr" \
	"$(INTDIR)\LSheetLib.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\LSheetLib.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\LSheetLib.pdb" /machine:I386 /out:"Bin/LSheetLib.dll" /implib:"$(OUTDIR)\LSheetLib.lib" 
LINK32_OBJS= \
	"$(INTDIR)\LSheet.obj" \
	"$(INTDIR)\LSheetLib.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"..\LGridLib\Bin\Release\LGridLib.lib"

".\Bin\LSheetLib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LSheetLib - Win32 Debug"

OUTDIR=.\Bin/Debug
INTDIR=.\Bin/Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\Bin\LSheetLib.dll"

!ELSE 

ALL : "LGridLib - Win32 Debug" ".\Bin\LSheetLib.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LGridLib - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\LSheet.obj"
	-@erase "$(INTDIR)\LSheetLib.obj"
	-@erase "$(INTDIR)\LSheetLib.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LSheetLib.exp"
	-@erase "$(OUTDIR)\LSheetLib.lib"
	-@erase "$(OUTDIR)\LSheetLib.pdb"
	-@erase ".\Bin\LSheetLib.dll"
	-@erase ".\Bin\LSheetLib.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LSHEETLIB_EXPORTS" /D "LGRIDLIB_EXPORTS" /Fp"$(INTDIR)\LSheetLib.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LSheetLib.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\LSheetLib.pdb" /debug /machine:I386 /out:"Bin/LSheetLib.dll" /implib:"$(OUTDIR)\LSheetLib.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\LSheet.obj" \
	"$(INTDIR)\LSheetLib.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"..\LGridLib\Bin\Debug\LGridLib.lib"

".\Bin\LSheetLib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("LSheetLib.dep")
!INCLUDE "LSheetLib.dep"
!ELSE 
!MESSAGE Warning: cannot find "LSheetLib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LSheetLib - Win32 Release" || "$(CFG)" == "LSheetLib - Win32 Debug"
SOURCE=.\Src\LSheet.cpp

!IF  "$(CFG)" == "LSheetLib - Win32 Release"


"$(INTDIR)\LSheet.obj"	"$(INTDIR)\LSheet.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LSheetLib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LSheetLib - Win32 Debug"


"$(INTDIR)\LSheet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LSheetLib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\LSheetLib.cpp

!IF  "$(CFG)" == "LSheetLib - Win32 Release"


"$(INTDIR)\LSheetLib.obj"	"$(INTDIR)\LSheetLib.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LSheetLib.pch"


!ELSEIF  "$(CFG)" == "LSheetLib - Win32 Debug"


"$(INTDIR)\LSheetLib.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LSheetLib.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "LSheetLib - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LSHEETLIB_EXPORTS" /D "LGRIDLIB_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LSheetLib.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\LSheetLib.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LSheetLib - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LSHEETLIB_EXPORTS" /D "LGRIDLIB_EXPORTS" /Fp"$(INTDIR)\LSheetLib.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LSheetLib.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "LSheetLib - Win32 Release"

"LGridLib - Win32 Release" : 
   cd "\L_SRC\VCProg\MyVCProc\LPowerReport\LGridBook\LGridLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LGridLib.mak CFG="LGridLib - Win32 Release" 
   cd "..\LSheetLib"

"LGridLib - Win32 ReleaseCLEAN" : 
   cd "\L_SRC\VCProg\MyVCProc\LPowerReport\LGridBook\LGridLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LGridLib.mak CFG="LGridLib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\LSheetLib"

!ELSEIF  "$(CFG)" == "LSheetLib - Win32 Debug"

"LGridLib - Win32 Debug" : 
   cd "\L_SRC\VCProg\MyVCProc\LPowerReport\LGridBook\LGridLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LGridLib.mak CFG="LGridLib - Win32 Debug" 
   cd "..\LSheetLib"

"LGridLib - Win32 DebugCLEAN" : 
   cd "\L_SRC\VCProg\MyVCProc\LPowerReport\LGridBook\LGridLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LGridLib.mak CFG="LGridLib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\LSheetLib"

!ENDIF 


!ENDIF 

