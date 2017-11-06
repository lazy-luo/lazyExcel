# Microsoft Developer Studio Generated NMAKE File, Based on LGridLib.dsp
!IF "$(CFG)" == ""
CFG=LGridLib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to LGridLib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LGridLib - Win32 Release" && "$(CFG)" != "LGridLib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LGridLib.mak" CFG="LGridLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LGridLib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LGridLib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "LGridLib - Win32 Release"

OUTDIR=.\Bin/Release
INTDIR=.\Bin/Release

!IF "$(RECURSE)" == "0" 

ALL : ".\Bin\LGridLib.dll"

!ELSE 

ALL : "LTableLib - Win32 Release" ".\Bin\LGridLib.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LTableLib - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\LGrid.obj"
	-@erase "$(INTDIR)\LGridLib.obj"
	-@erase "$(INTDIR)\LGridLib.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LGridLib.exp"
	-@erase "$(OUTDIR)\LGridLib.lib"
	-@erase ".\Bin\LGridLib.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LGRIDLIB_EXPORTS" /D "LTABLELIB_EXPORTS" /Fp"$(INTDIR)\LGridLib.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LGridLib.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\LGridLib.pdb" /machine:I386 /out:"Bin/LGridLib.dll" /implib:"$(OUTDIR)\LGridLib.lib" 
LINK32_OBJS= \
	"$(INTDIR)\LGrid.obj" \
	"$(INTDIR)\LGridLib.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"..\LTableLib\Bin\Release\LTableLib.lib"

".\Bin\LGridLib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LGridLib - Win32 Debug"

OUTDIR=.\Bin/Debug
INTDIR=.\Bin/Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\Bin\LGridLib.dll"

!ELSE 

ALL : "LTableLib - Win32 Debug" ".\Bin\LGridLib.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LTableLib - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\LGrid.obj"
	-@erase "$(INTDIR)\LGridLib.obj"
	-@erase "$(INTDIR)\LGridLib.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LGridLib.exp"
	-@erase "$(OUTDIR)\LGridLib.lib"
	-@erase "$(OUTDIR)\LGridLib.pdb"
	-@erase ".\Bin\LGridLib.dll"
	-@erase ".\Bin\LGridLib.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LGRIDLIB_EXPORTS" /D "LTABLELIB_EXPORTS" /Fp"$(INTDIR)\LGridLib.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LGridLib.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\LGridLib.pdb" /debug /machine:I386 /out:"Bin/LGridLib.dll" /implib:"$(OUTDIR)\LGridLib.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\LGrid.obj" \
	"$(INTDIR)\LGridLib.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"..\LTableLib\Bin\Debug\LTableLib.lib"

".\Bin\LGridLib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("LGridLib.dep")
!INCLUDE "LGridLib.dep"
!ELSE 
!MESSAGE Warning: cannot find "LGridLib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LGridLib - Win32 Release" || "$(CFG)" == "LGridLib - Win32 Debug"
SOURCE=.\Src\LGrid.cpp

"$(INTDIR)\LGrid.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LGridLib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\LGridLib.cpp

"$(INTDIR)\LGridLib.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LGridLib.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "LGridLib - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LGRIDLIB_EXPORTS" /D "LTABLELIB_EXPORTS" /Fp"$(INTDIR)\LGridLib.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LGridLib.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LGridLib - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LGRIDLIB_EXPORTS" /D "LTABLELIB_EXPORTS" /Fp"$(INTDIR)\LGridLib.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LGridLib.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "LGridLib - Win32 Release"

"LTableLib - Win32 Release" : 
   cd "\L_SRC\VCProg\MyVCProc\LPowerReport\LGridBook\LTableLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LTableLib.mak CFG="LTableLib - Win32 Release" 
   cd "..\LGridLib"

"LTableLib - Win32 ReleaseCLEAN" : 
   cd "\L_SRC\VCProg\MyVCProc\LPowerReport\LGridBook\LTableLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LTableLib.mak CFG="LTableLib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\LGridLib"

!ELSEIF  "$(CFG)" == "LGridLib - Win32 Debug"

"LTableLib - Win32 Debug" : 
   cd "\L_SRC\VCProg\MyVCProc\LPowerReport\LGridBook\LTableLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LTableLib.mak CFG="LTableLib - Win32 Debug" 
   cd "..\LGridLib"

"LTableLib - Win32 DebugCLEAN" : 
   cd "\L_SRC\VCProg\MyVCProc\LPowerReport\LGridBook\LTableLib"
   $(MAKE) /$(MAKEFLAGS) /F .\LTableLib.mak CFG="LTableLib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\LGridLib"

!ENDIF 


!ENDIF 

