# Microsoft Developer Studio Project File - Name="LRptDesigner" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=LRptDesigner - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LRptDesigner.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LRptDesigner.mak" CFG="LRptDesigner - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LRptDesigner - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "LRptDesigner - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LRptDesigner - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../Bin/Build/LRptDesigner/COM/Release"
# PROP Intermediate_Dir "../../../Bin/Build/LRptDesigner/COM/Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"../../../Bin/LRptDesigner_Com.exe"

!ELSEIF  "$(CFG)" == "LRptDesigner - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../Bin/Build/LRptDesigner/COM/Debug"
# PROP Intermediate_Dir "../../../Bin/Build/LRptDesigner/COM/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"../../../Bin/LRptDesigner_Com.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "LRptDesigner - Win32 Release"
# Name "LRptDesigner - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\clgridbook.cpp
# End Source File
# Begin Source File

SOURCE=.\DesignerTollBar.cpp
# End Source File
# Begin Source File

SOURCE=.\EditToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\FontComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\FormatToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Comm\LColorPan.cpp
# End Source File
# Begin Source File

SOURCE=.\Comm\LColorPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\LFlatComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\Ctrl\LFlatEdit.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Comm\LImagePan.cpp
# End Source File
# Begin Source File

SOURCE=.\Comm\LImagePicker.cpp
# End Source File
# Begin Source File

SOURCE=.\Comm\LPickerBtn.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Comm\LPopupPan.cpp
# End Source File
# Begin Source File

SOURCE=.\Comm\LReg.cpp
# End Source File
# Begin Source File

SOURCE=.\LRptDesigner.cpp
# End Source File
# Begin Source File

SOURCE=.\LRptDesigner.rc
# End Source File
# Begin Source File

SOURCE=.\LRptDesignerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\LRptDesignerView.cpp
# End Source File
# Begin Source File

SOURCE=.\Comm\LToolTip.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\SizeComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ToolBarComboBox.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\clgridbook.h
# End Source File
# Begin Source File

SOURCE=.\DesignerTollBar.h
# End Source File
# Begin Source File

SOURCE=.\EditToolBar.h
# End Source File
# Begin Source File

SOURCE=.\FontComboBox.h
# End Source File
# Begin Source File

SOURCE=.\FormatToolBar.h
# End Source File
# Begin Source File

SOURCE=.\Comm\LColorPan.h
# End Source File
# Begin Source File

SOURCE=.\Comm\LColorPicker.h
# End Source File
# Begin Source File

SOURCE=.\LFlatComboBox.h
# End Source File
# Begin Source File

SOURCE=.\Ctrl\LFlatEdit.h
# End Source File
# Begin Source File

SOURCE=.\Comm\LImagePan.h
# End Source File
# Begin Source File

SOURCE=.\Comm\LImagePicker.h
# End Source File
# Begin Source File

SOURCE=.\Comm\LPickerBtn.h
# End Source File
# Begin Source File

SOURCE=.\Comm\LPopupPan.h
# End Source File
# Begin Source File

SOURCE=.\Comm\LReg.h
# End Source File
# Begin Source File

SOURCE=.\LRptDesigner.h
# End Source File
# Begin Source File

SOURCE=.\LRptDesignerDoc.h
# End Source File
# Begin Source File

SOURCE=.\LRptDesignerView.h
# End Source File
# Begin Source File

SOURCE=.\Comm\LToolTip.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SizeComboBox.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ToolBarComboBox.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\BackColor.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BackColor_new.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fonttype.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ForeColor_new.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GridLineAll.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GridLineHorz.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GridLineNone.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GridLineVert.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Line.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LineBorder.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LineBottom.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LineLeft.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LineRight.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LineTop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LRptDesigner.ico
# End Source File
# Begin Source File

SOURCE=.\res\LRptDesigner.rc2
# End Source File
# Begin Source File

SOURCE=.\res\LRptDesignerDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\noLine.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
