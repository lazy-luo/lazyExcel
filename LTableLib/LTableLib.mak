# Microsoft Developer Studio Generated NMAKE File, Based on LTableLib.dsp
!IF "$(CFG)" == ""
CFG=LTableLib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to LTableLib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LTableLib - Win32 Release" && "$(CFG)" != "LTableLib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LTableLib.mak" CFG="LTableLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LTableLib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LTableLib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "LTableLib - Win32 Release"

OUTDIR=.\Bin/Release
INTDIR=.\Bin/Release
# Begin Custom Macros
OutDir=.\Bin/Release
# End Custom Macros

ALL : ".\Bin\LTableLib.dll" "$(OUTDIR)\LTableLib.bsc"


CLEAN :
	-@erase "$(INTDIR)\LCellItem.obj"
	-@erase "$(INTDIR)\LCellItem.sbr"
	-@erase "$(INTDIR)\LColItem.obj"
	-@erase "$(INTDIR)\LColItem.sbr"
	-@erase "$(INTDIR)\LRowItem.obj"
	-@erase "$(INTDIR)\LRowItem.sbr"
	-@erase "$(INTDIR)\LSerial.obj"
	-@erase "$(INTDIR)\LSerial.sbr"
	-@erase "$(INTDIR)\LStyle.obj"
	-@erase "$(INTDIR)\LStyle.sbr"
	-@erase "$(INTDIR)\LTable.obj"
	-@erase "$(INTDIR)\LTable.sbr"
	-@erase "$(INTDIR)\LTableLib.obj"
	-@erase "$(INTDIR)\LTableLib.pch"
	-@erase "$(INTDIR)\LTableLib.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LTableLib.bsc"
	-@erase "$(OUTDIR)\LTableLib.exp"
	-@erase "$(OUTDIR)\LTableLib.lib"
	-@erase ".\Bin\LTableLib.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LTABLELIB_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LTableLib.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LTableLib.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\LCellItem.sbr" \
	"$(INTDIR)\LColItem.sbr" \
	"$(INTDIR)\LRowItem.sbr" \
	"$(INTDIR)\LSerial.sbr" \
	"$(INTDIR)\LStyle.sbr" \
	"$(INTDIR)\LTable.sbr" \
	"$(INTDIR)\LTableLib.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\LTableLib.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\LTableLib.pdb" /machine:I386 /out:"Bin/LTableLib.dll" /implib:"$(OUTDIR)\LTableLib.lib" 
LINK32_OBJS= \
	"$(INTDIR)\LCellItem.obj" \
	"$(INTDIR)\LColItem.obj" \
	"$(INTDIR)\LRowItem.obj" \
	"$(INTDIR)\LSerial.obj" \
	"$(INTDIR)\LStyle.obj" \
	"$(INTDIR)\LTable.obj" \
	"$(INTDIR)\LTableLib.obj" \
	"$(INTDIR)\StdAfx.obj"

".\Bin\LTableLib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LTableLib - Win32 Debug"

OUTDIR=.\Bin/Debug
INTDIR=.\Bin/Debug
# Begin Custom Macros
OutDir=.\Bin/Debug
# End Custom Macros

ALL : ".\Bin\LTableLib.dll" "$(OUTDIR)\LTableLib.bsc"


CLEAN :
	-@erase "$(INTDIR)\LCellItem.obj"
	-@erase "$(INTDIR)\LCellItem.sbr"
	-@erase "$(INTDIR)\LColItem.obj"
	-@erase "$(INTDIR)\LColItem.sbr"
	-@erase "$(INTDIR)\LRowItem.obj"
	-@erase "$(INTDIR)\LRowItem.sbr"
	-@erase "$(INTDIR)\LSerial.obj"
	-@erase "$(INTDIR)\LSerial.sbr"
	-@erase "$(INTDIR)\LStyle.obj"
	-@erase "$(INTDIR)\LStyle.sbr"
	-@erase "$(INTDIR)\LTable.obj"
	-@erase "$(INTDIR)\LTable.sbr"
	-@erase "$(INTDIR)\LTableLib.obj"
	-@erase "$(INTDIR)\LTableLib.pch"
	-@erase "$(INTDIR)\LTableLib.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LTableLib.bsc"
	-@erase "$(OUTDIR)\LTableLib.exp"
	-@erase "$(OUTDIR)\LTableLib.lib"
	-@erase "$(OUTDIR)\LTableLib.pdb"
	-@erase ".\Bin\LTableLib.dll"
	-@erase ".\Bin\LTableLib.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LTABLELIB_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LTableLib.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LTableLib.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\LCellItem.sbr" \
	"$(INTDIR)\LColItem.sbr" \
	"$(INTDIR)\LRowItem.sbr" \
	"$(INTDIR)\LSerial.sbr" \
	"$(INTDIR)\LStyle.sbr" \
	"$(INTDIR)\LTable.sbr" \
	"$(INTDIR)\LTableLib.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\LTableLib.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\LTableLib.pdb" /debug /machine:I386 /out:"Bin/LTableLib.dll" /implib:"$(OUTDIR)\LTableLib.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\LCellItem.obj" \
	"$(INTDIR)\LColItem.obj" \
	"$(INTDIR)\LRowItem.obj" \
	"$(INTDIR)\LSerial.obj" \
	"$(INTDIR)\LStyle.obj" \
	"$(INTDIR)\LTable.obj" \
	"$(INTDIR)\LTableLib.obj" \
	"$(INTDIR)\StdAfx.obj"

".\Bin\LTableLib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("LTableLib.dep")
!INCLUDE "LTableLib.dep"
!ELSE 
!MESSAGE Warning: cannot find "LTableLib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LTableLib - Win32 Release" || "$(CFG)" == "LTableLib - Win32 Debug"
SOURCE=.\Base\LCellItem.cpp

"$(INTDIR)\LCellItem.obj"	"$(INTDIR)\LCellItem.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LTableLib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Base\LColItem.cpp

"$(INTDIR)\LColItem.obj"	"$(INTDIR)\LColItem.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LTableLib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Base\LRowItem.cpp

"$(INTDIR)\LRowItem.obj"	"$(INTDIR)\LRowItem.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LTableLib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\LComm\LSerial.cpp

"$(INTDIR)\LSerial.obj"	"$(INTDIR)\LSerial.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LTableLib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Base\LStyle.cpp

"$(INTDIR)\LStyle.obj"	"$(INTDIR)\LStyle.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LTableLib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Src\LTable.cpp

"$(INTDIR)\LTable.obj"	"$(INTDIR)\LTable.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LTableLib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\LTableLib.cpp

"$(INTDIR)\LTableLib.obj"	"$(INTDIR)\LTableLib.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LTableLib.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "LTableLib - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LTABLELIB_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LTableLib.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\LTableLib.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LTableLib - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LTABLELIB_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LTableLib.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\LTableLib.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

