# Microsoft Developer Studio Generated NMAKE File, Based on CLGridBook.dsp
!IF "$(CFG)" == ""
CFG=CLGridBook - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CLGridBook - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CLGridBook - Win32 Debug" && "$(CFG)" != "CLGridBook - Win32 Unicode Debug" && "$(CFG)" != "CLGridBook - Win32 Release MinSize" && "$(CFG)" != "CLGridBook - Win32 Release MinDependency" && "$(CFG)" != "CLGridBook - Win32 Unicode Release MinSize" && "$(CFG)" != "CLGridBook - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CLGridBook.mak" CFG="CLGridBook - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CLGridBook - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CLGridBook - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CLGridBook - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CLGridBook - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CLGridBook - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CLGridBook - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "CLGridBook - Win32 Debug"

OUTDIR=.\../../Bin/Build/Com/Debug
INTDIR=.\../../Bin/Build/Com/Debug
# Begin Custom Macros
OutDir=.\../../Bin/Build/Com/Debug
# End Custom Macros

ALL : "..\..\Bin\CLGridBook.dll" ".\CLGridBook.tlb" ".\CLGridBook.h" ".\CLGridBook_i.c" "$(OUTDIR)\CLGridBook.bsc" ".\../../Bin/Build/Com/Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CLBookLib.obj"
	-@erase "$(INTDIR)\CLBookLib.sbr"
	-@erase "$(INTDIR)\CLGridBook.obj"
	-@erase "$(INTDIR)\CLGridBook.pch"
	-@erase "$(INTDIR)\CLGridBook.res"
	-@erase "$(INTDIR)\CLGridBook.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CLGridBook.bsc"
	-@erase "$(OUTDIR)\CLGridBook.exp"
	-@erase "$(OUTDIR)\CLGridBook.lib"
	-@erase "..\..\Bin\CLGridBook.dll"
	-@erase ".\CLGridBook.h"
	-@erase ".\CLGridBook.tlb"
	-@erase ".\CLGridBook_i.c"
	-@erase ".\../../Bin/Build/Com/Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_LCOM_EXPORT_" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CLGridBook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\CLGridBook.res" /d "_NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/o"$(OUTDIR)\CLGridBook.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CLBookLib.sbr" \
	"$(INTDIR)\CLGridBook.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\CLGridBook.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mtx.lib mtxguid.lib delayimp.lib /nologo /subsystem:windows /dll /pdb:none /debug /machine:I386 /def:".\CLGridBook.def" /out:"../../Bin/CLGridBook.dll" /implib:"$(OUTDIR)\CLGridBook.lib" /delayload:mtxex.dll 
DEF_FILE= \
	".\CLGridBook.def"
LINK32_OBJS= \
	"$(INTDIR)\CLBookLib.obj" \
	"$(INTDIR)\CLGridBook.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CLGridBook.res"

"..\..\Bin\CLGridBook.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\../../Bin/Build/Com/Debug
TargetPath=\L_SRC\VCProg\MyVCProc\LPowerReport\LGridBook\Bin\CLGridBook.dll
InputPath=\L_SRC\VCProg\MyVCProc\LPowerReport\LGridBook\Bin\CLGridBook.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Execute mtxrereg.exe before using MTS components in MTS 
<< 
	

!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\CLGridBook.dll" ".\CLGridBook.tlb" ".\CLGridBook.h" ".\CLGridBook_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CLBookLib.obj"
	-@erase "$(INTDIR)\CLGridBook.obj"
	-@erase "$(INTDIR)\CLGridBook.pch"
	-@erase "$(INTDIR)\CLGridBook.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CLGridBook.dll"
	-@erase "$(OUTDIR)\CLGridBook.exp"
	-@erase "$(OUTDIR)\CLGridBook.ilk"
	-@erase "$(OUTDIR)\CLGridBook.lib"
	-@erase "$(OUTDIR)\CLGridBook.pdb"
	-@erase ".\CLGridBook.h"
	-@erase ".\CLGridBook.tlb"
	-@erase ".\CLGridBook_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\CLGridBook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\CLGridBook.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CLGridBook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mtx.lib mtxguid.lib delayimp.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\CLGridBook.pdb" /debug /machine:I386 /def:".\CLGridBook.def" /out:"$(OUTDIR)\CLGridBook.dll" /implib:"$(OUTDIR)\CLGridBook.lib" /pdbtype:sept /delayload:mtxex.dll 
DEF_FILE= \
	".\CLGridBook.def"
LINK32_OBJS= \
	"$(INTDIR)\CLBookLib.obj" \
	"$(INTDIR)\CLGridBook.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CLGridBook.res"

"$(OUTDIR)\CLGridBook.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\CLGridBook.dll
InputPath=.\DebugU\CLGridBook.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Execute mtxrereg.exe before using MTS components in MTS 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Release MinSize"

OUTDIR=.\../../Bin/Build/Com/ReleaseMinSize
INTDIR=.\../../Bin/Build/Com/ReleaseMinSize
# Begin Custom Macros
OutDir=.\../../Bin/Build/Com/ReleaseMinSize
# End Custom Macros

ALL : "..\..\Bin\CLGridBook.dll" "$(OUTDIR)\CLGridBook.bsc" ".\../../Bin/Build/Com/ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CLBookLib.obj"
	-@erase "$(INTDIR)\CLBookLib.sbr"
	-@erase "$(INTDIR)\CLGridBook.obj"
	-@erase "$(INTDIR)\CLGridBook.pch"
	-@erase "$(INTDIR)\CLGridBook.res"
	-@erase "$(INTDIR)\CLGridBook.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CLGridBook.bsc"
	-@erase "$(OUTDIR)\CLGridBook.exp"
	-@erase "$(OUTDIR)\CLGridBook.lib"
	-@erase "..\..\Bin\CLGridBook.dll"
	-@erase ".\CLGridBook.h"
	-@erase ".\CLGridBook.tlb"
	-@erase ".\CLGridBook_i.c"
	-@erase ".\../../Bin/Build/Com/ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_LCOM_EXPORT_" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CLGridBook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\CLGridBook.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CLGridBook.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CLBookLib.sbr" \
	"$(INTDIR)\CLGridBook.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\CLGridBook.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mtx.lib mtxguid.lib delayimp.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CLGridBook.pdb" /machine:I386 /def:".\CLGridBook.def" /out:"../../Bin/CLGridBook.dll" /implib:"$(OUTDIR)\CLGridBook.lib" /delayload:mtxex.dll 
DEF_FILE= \
	".\CLGridBook.def"
LINK32_OBJS= \
	"$(INTDIR)\CLBookLib.obj" \
	"$(INTDIR)\CLGridBook.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CLGridBook.res"

"..\..\Bin\CLGridBook.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\../../Bin/Build/Com/ReleaseMinSize
TargetPath=\L_SRC\VCProg\MyVCProc\LPowerReport\LGridBook\Bin\CLGridBook.dll
InputPath=\L_SRC\VCProg\MyVCProc\LPowerReport\LGridBook\Bin\CLGridBook.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Execute mtxrereg.exe before using MTS components in MTS 
<< 
	

!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\CLGridBook.dll" ".\CLGridBook.tlb" ".\CLGridBook.h" ".\CLGridBook_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CLBookLib.obj"
	-@erase "$(INTDIR)\CLGridBook.obj"
	-@erase "$(INTDIR)\CLGridBook.pch"
	-@erase "$(INTDIR)\CLGridBook.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CLGridBook.dll"
	-@erase "$(OUTDIR)\CLGridBook.exp"
	-@erase "$(OUTDIR)\CLGridBook.ilk"
	-@erase "$(OUTDIR)\CLGridBook.lib"
	-@erase ".\CLGridBook.h"
	-@erase ".\CLGridBook.tlb"
	-@erase ".\CLGridBook_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_LCOM_EXPORT_" /Fp"$(INTDIR)\CLGridBook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\CLGridBook.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CLGridBook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mtx.lib mtxguid.lib delayimp.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\CLGridBook.pdb" /machine:I386 /def:".\CLGridBook.def" /out:"$(OUTDIR)\CLGridBook.dll" /implib:"$(OUTDIR)\CLGridBook.lib" /delayload:mtxex.dll 
DEF_FILE= \
	".\CLGridBook.def"
LINK32_OBJS= \
	"$(INTDIR)\CLBookLib.obj" \
	"$(INTDIR)\CLGridBook.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CLGridBook.res"

"$(OUTDIR)\CLGridBook.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\CLGridBook.dll
InputPath=.\ReleaseMinDependency\CLGridBook.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Execute mtxrereg.exe before using MTS components in MTS 
<< 
	

!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\CLGridBook.dll" ".\CLGridBook.tlb" ".\CLGridBook.h" ".\CLGridBook_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CLBookLib.obj"
	-@erase "$(INTDIR)\CLGridBook.obj"
	-@erase "$(INTDIR)\CLGridBook.pch"
	-@erase "$(INTDIR)\CLGridBook.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CLGridBook.dll"
	-@erase "$(OUTDIR)\CLGridBook.exp"
	-@erase "$(OUTDIR)\CLGridBook.lib"
	-@erase ".\CLGridBook.h"
	-@erase ".\CLGridBook.tlb"
	-@erase ".\CLGridBook_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CLGridBook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\CLGridBook.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CLGridBook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mtx.lib mtxguid.lib delayimp.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CLGridBook.pdb" /machine:I386 /def:".\CLGridBook.def" /out:"$(OUTDIR)\CLGridBook.dll" /implib:"$(OUTDIR)\CLGridBook.lib" /delayload:mtxex.dll 
DEF_FILE= \
	".\CLGridBook.def"
LINK32_OBJS= \
	"$(INTDIR)\CLBookLib.obj" \
	"$(INTDIR)\CLGridBook.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CLGridBook.res"

"$(OUTDIR)\CLGridBook.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\CLGridBook.dll
InputPath=.\ReleaseUMinSize\CLGridBook.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Execute mtxrereg.exe before using MTS components in MTS 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\CLGridBook.dll" ".\CLGridBook.tlb" ".\CLGridBook.h" ".\CLGridBook_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CLBookLib.obj"
	-@erase "$(INTDIR)\CLGridBook.obj"
	-@erase "$(INTDIR)\CLGridBook.pch"
	-@erase "$(INTDIR)\CLGridBook.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CLGridBook.dll"
	-@erase "$(OUTDIR)\CLGridBook.exp"
	-@erase "$(OUTDIR)\CLGridBook.lib"
	-@erase ".\CLGridBook.h"
	-@erase ".\CLGridBook.tlb"
	-@erase ".\CLGridBook_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CLGridBook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\CLGridBook.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CLGridBook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mtx.lib mtxguid.lib delayimp.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CLGridBook.pdb" /machine:I386 /def:".\CLGridBook.def" /out:"$(OUTDIR)\CLGridBook.dll" /implib:"$(OUTDIR)\CLGridBook.lib" /delayload:mtxex.dll 
DEF_FILE= \
	".\CLGridBook.def"
LINK32_OBJS= \
	"$(INTDIR)\CLBookLib.obj" \
	"$(INTDIR)\CLGridBook.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CLGridBook.res"

"$(OUTDIR)\CLGridBook.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\CLGridBook.dll
InputPath=.\ReleaseUMinDependency\CLGridBook.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Execute mtxrereg.exe before using MTS components in MTS 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("CLGridBook.dep")
!INCLUDE "CLGridBook.dep"
!ELSE 
!MESSAGE Warning: cannot find "CLGridBook.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CLGridBook - Win32 Debug" || "$(CFG)" == "CLGridBook - Win32 Unicode Debug" || "$(CFG)" == "CLGridBook - Win32 Release MinSize" || "$(CFG)" == "CLGridBook - Win32 Release MinDependency" || "$(CFG)" == "CLGridBook - Win32 Unicode Release MinSize" || "$(CFG)" == "CLGridBook - Win32 Unicode Release MinDependency"
SOURCE=.\CLBookLib.cpp

!IF  "$(CFG)" == "CLGridBook - Win32 Debug"


"$(INTDIR)\CLBookLib.obj"	"$(INTDIR)\CLBookLib.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CLGridBook.pch"


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Unicode Debug"


"$(INTDIR)\CLBookLib.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CLGridBook.pch"


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Release MinSize"


"$(INTDIR)\CLBookLib.obj"	"$(INTDIR)\CLBookLib.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CLGridBook.pch" ".\CLGridBook.h"


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Release MinDependency"


"$(INTDIR)\CLBookLib.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CLGridBook.pch"


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Unicode Release MinSize"


"$(INTDIR)\CLBookLib.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CLGridBook.pch"


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Unicode Release MinDependency"


"$(INTDIR)\CLBookLib.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CLGridBook.pch"


!ENDIF 

SOURCE=.\CLGridBook.cpp

!IF  "$(CFG)" == "CLGridBook - Win32 Debug"


"$(INTDIR)\CLGridBook.obj"	"$(INTDIR)\CLGridBook.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CLGridBook.pch"


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Unicode Debug"


"$(INTDIR)\CLGridBook.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CLGridBook.pch"


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Release MinSize"


"$(INTDIR)\CLGridBook.obj"	"$(INTDIR)\CLGridBook.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CLGridBook.pch" ".\CLGridBook.h" ".\CLGridBook_i.c"


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Release MinDependency"


"$(INTDIR)\CLGridBook.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CLGridBook.pch"


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Unicode Release MinSize"


"$(INTDIR)\CLGridBook.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CLGridBook.pch"


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Unicode Release MinDependency"


"$(INTDIR)\CLGridBook.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CLGridBook.pch"


!ENDIF 

SOURCE=.\CLGridBook.idl

!IF  "$(CFG)" == "CLGridBook - Win32 Debug"

MTL_SWITCHES=/tlb ".\CLGridBook.tlb" /h "CLGridBook.h" /iid "CLGridBook_i.c" /Oicf 

".\CLGridBook.tlb"	".\CLGridBook.h"	".\CLGridBook_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Unicode Debug"

MTL_SWITCHES=/tlb ".\CLGridBook.tlb" /h "CLGridBook.h" /iid "CLGridBook_i.c" /Oicf 

".\CLGridBook.tlb"	".\CLGridBook.h"	".\CLGridBook_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\CLGridBook.tlb" /h "CLGridBook.h" /iid "CLGridBook_i.c" /Oicf 

".\CLGridBook.tlb"	".\CLGridBook.h"	".\CLGridBook_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\CLGridBook.tlb" /h "CLGridBook.h" /iid "CLGridBook_i.c" /Oicf 

".\CLGridBook.tlb"	".\CLGridBook.h"	".\CLGridBook_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\CLGridBook.tlb" /h "CLGridBook.h" /iid "CLGridBook_i.c" /Oicf 

".\CLGridBook.tlb"	".\CLGridBook.h"	".\CLGridBook_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb ".\CLGridBook.tlb" /h "CLGridBook.h" /iid "CLGridBook_i.c" /Oicf 

".\CLGridBook.tlb"	".\CLGridBook.h"	".\CLGridBook_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CLGridBook.rc

"$(INTDIR)\CLGridBook.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\dlldatax.c
SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "CLGridBook - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_LCOM_EXPORT_" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CLGridBook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\CLGridBook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\CLGridBook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CLGridBook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_LCOM_EXPORT_" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CLGridBook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\CLGridBook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_LCOM_EXPORT_" /Fp"$(INTDIR)\CLGridBook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CLGridBook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CLGridBook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CLGridBook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CLGridBook - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CLGridBook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CLGridBook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

