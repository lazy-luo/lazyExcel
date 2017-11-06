# Microsoft Developer Studio Generated NMAKE File, Based on LGridBook.dsp
!IF "$(CFG)" == ""
CFG=LGridBook - Win32 Debug
!MESSAGE No configuration specified. Defaulting to LGridBook - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LGridBook - Win32 Release" && "$(CFG)" != "LGridBook - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LGridBook.mak" CFG="LGridBook - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LGridBook - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LGridBook - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "LGridBook - Win32 Release"

OUTDIR=.\Bin/Release
INTDIR=.\Bin/Release
# Begin Custom Macros
OutDir=.\Bin/Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\Bin\LGridBook.dll" "$(OUTDIR)\LGridBook.bsc"

!ELSE 

ALL : "LTableLib - Win32 Release" "LSheetLib - Win32 Release" "LGridLib - Win32 Release" ".\Bin\LGridBook.dll" "$(OUTDIR)\LGridBook.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LGridLib - Win32 ReleaseCLEAN" "LSheetLib - Win32 ReleaseCLEAN" "LTableLib - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\LBook.obj"
	-@erase "$(INTDIR)\LBook.sbr"
	-@erase "$(INTDIR)\LGridBook.obj"
	-@erase "$(INTDIR)\LGridBook.pch"
	-@erase "$(INTDIR)\LGridBook.sbr"
	-@erase "$(INTDIR)\LTabArea.obj"
	-@erase "$(INTDIR)\LTabArea.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LGridBook.bsc"
	-@erase "$(OUTDIR)\LGridBook.exp"
	-@erase "$(OUTDIR)\LGridBook.lib"
	-@erase ".\Bin\LGridBook.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LGRIDBOOK_EXPORTS" /D "LSHEETLIB_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LGridBook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LGridBook.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\LBook.sbr" \
	"$(INTDIR)\LGridBook.sbr" \
	"$(INTDIR)\LTabArea.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\LGridBook.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\LGridBook.pdb" /machine:I386 /out:"Bin/LGridBook.dll" /implib:"$(OUTDIR)\LGridBook.lib" 
LINK32_OBJS= \
	"$(INTDIR)\LBook.obj" \
	"$(INTDIR)\LGridBook.obj" \
	"$(INTDIR)\LTabArea.obj" \
	"$(INTDIR)\StdAfx.obj" \
	".\LGridLib\Bin\Release\LGridLib.lib" \
	".\LSheetLib\Bin\Release\LSheetLib.lib" \
	".\LTableLib\Bin\Release\LTableLib.lib"

".\Bin\LGridBook.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LGridBook - Win32 Debug"

OUTDIR=.\Bin/Debug
INTDIR=.\Bin/Debug
# Begin Custom Macros
OutDir=.\Bin/Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\Bin\LGridBook.dll" "$(OUTDIR)\LGridBook.bsc"

!ELSE 

ALL : "LTableLib - Win32 Debug" "LSheetLib - Win32 Debug" "LGridLib - Win32 Debug" ".\Bin\LGridBook.dll" "$(OUTDIR)\LGridBook.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LGridLib - Win32 DebugCLEAN" "LSheetLib - Win32 DebugCLEAN" "LTableLib - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\LBook.obj"
	-@erase "$(INTDIR)\LBook.sbr"
	-@erase "$(INTDIR)\LGridBook.obj"
	-@erase "$(INTDIR)\LGridBook.pch"
	-@erase "$(INTDIR)\LGridBook.sbr"
	-@erase "$(INTDIR)\LTabArea.obj"
	-@erase "$(INTDIR)\LTabArea.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LGridBook.bsc"
	-@erase "$(OUTDIR)\LGridBook.exp"
	-@erase "$(OUTDIR)\LGridBook.lib"
	-@erase "$(OUTDIR)\LGridBook.pdb"
	-@erase ".\Bin\LGridBook.dll"
	-@erase ".\Bin\LGridBook.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LGRIDBOOK_EXPORTS" /D "LSHEETLIB_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LGridBook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LGridBook.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\LBook.sbr" \
	"$(INTDIR)\LGridBook.sbr" \
	"$(INTDIR)\LTabArea.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\LGridBook.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\LGridBook.pdb" /debug /machine:I386 /out:"Bin/LGridBook.dll" /implib:"$(OUTDIR)\LGridBook.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\LBook.obj" \
	"$(INTDIR)\LGridBook.obj" \
	"$(INTDIR)\LTabArea.obj" \
	"$(INTDIR)\StdAfx.obj" \
	".\LGridLib\Bin\Debug\LGridLib.lib" \
	".\LSheetLib\Bin\Debug\LSheetLib.lib" \
	".\LTableLib\Bin\Debug\LTableLib.lib"

".\Bin\LGridBook.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("LGridBook.dep")
!INCLUDE "LGridBook.dep"
!ELSE 
!MESSAGE Warning: cannot find "LGridBook.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LGridBook - Win32 Release" || "$(CFG)" == "LGridBook - Win32 Debug"
SOURCE=.\Src\LBook.cpp

"$(INTDIR)\LBook.obj"	"$(INTDIR)\LBook.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LGridBook.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\LGridBook.cpp

"$(INTDIR)\LGridBook.obj"	"$(INTDIR)\LGridBook.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LGridBook.pch"


SOURCE=.\Base\LTabArea.cpp

"$(INTDIR)\LTabArea.obj"	"$(INTDIR)\LTabArea.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LGridBook.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "LGridBook - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LGRIDBOOK_EXPORTS" /D "LSHEETLIB_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LGridBook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\LGridBook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LGridBook - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LGRIDBOOK_EXPORTS" /D "LSHEETLIB_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LGridBook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\LGridBook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "LGridBook - Win32 Release"

"LGridLib - Win32 Release" : 
   cd ".\LGridLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LGridLib.mak CFG="LGridLib - Win32 Release" 
   cd ".."

"LGridLib - Win32 ReleaseCLEAN" : 
   cd ".\LGridLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LGridLib.mak CFG="LGridLib - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "LGridBook - Win32 Debug"

"LGridLib - Win32 Debug" : 
   cd ".\LGridLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LGridLib.mak CFG="LGridLib - Win32 Debug" 
   cd ".."

"LGridLib - Win32 DebugCLEAN" : 
   cd ".\LGridLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LGridLib.mak CFG="LGridLib - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "LGridBook - Win32 Release"

"LSheetLib - Win32 Release" : 
   cd ".\LSheetLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LSheetLib.mak CFG="LSheetLib - Win32 Release" 
   cd ".."

"LSheetLib - Win32 ReleaseCLEAN" : 
   cd ".\LSheetLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LSheetLib.mak CFG="LSheetLib - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "LGridBook - Win32 Debug"

"LSheetLib - Win32 Debug" : 
   cd ".\LSheetLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LSheetLib.mak CFG="LSheetLib - Win32 Debug" 
   cd ".."

"LSheetLib - Win32 DebugCLEAN" : 
   cd ".\LSheetLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LSheetLib.mak CFG="LSheetLib - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "LGridBook - Win32 Release"

"LTableLib - Win32 Release" : 
   cd ".\LTableLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LTableLib.mak CFG="LTableLib - Win32 Release" 
   cd ".."

"LTableLib - Win32 ReleaseCLEAN" : 
   cd ".\LTableLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LTableLib.mak CFG="LTableLib - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "LGridBook - Win32 Debug"

"LTableLib - Win32 Debug" : 
   cd ".\LTableLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LTableLib.mak CFG="LTableLib - Win32 Debug" 
   cd ".."

"LTableLib - Win32 DebugCLEAN" : 
   cd ".\LTableLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LTableLib.mak CFG="LTableLib - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 


!ENDIF 

