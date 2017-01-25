# Microsoft Developer Studio Project File - Name="RosterMaker" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=RosterMaker - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RosterMaker.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RosterMaker.mak" CFG="RosterMaker - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RosterMaker - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "RosterMaker - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RosterMaker - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp1 /MD /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /force /out:"program/RosterMaker.exe"

!ELSEIF  "$(CFG)" == "RosterMaker - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Zp1 /MDd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /force /out:"program/RosterMaker.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "RosterMaker - Win32 Release"
# Name "RosterMaker - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "lib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\lib\prompt.lib
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\lib\FileIO2.lib
# End Source File
# Begin Source File

SOURCE="..\tdbaccess\c++ lib\Debug\tdbAccess.lib"
# End Source File
# End Group
# Begin Group "dll"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tdbaccess\tdbaccess.dll
# End Source File
# End Group
# Begin Source File

SOURCE=.\Edit_Append.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcessTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\roster2csv.cpp
# End Source File
# Begin Source File

SOURCE=.\RosterMaker.cpp
# End Source File
# Begin Source File

SOURCE=.\RosterMaker.rc
# End Source File
# Begin Source File

SOURCE=.\RosterMakerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "std"

# PROP Default_Filter ""
# Begin Source File

SOURCE="C:\Apps\MSVC++6\VC98\Include\BASETSD.H"
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\include\codeShortcuts.h
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\include\FileIO2.h
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\include\stdMacros.h
# End Source File
# End Group
# Begin Group "tdb"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\tdbaccess\c++ include\tdbAccess.h"
# End Source File
# End Group
# Begin Source File

SOURCE=.\buildFlags.h
# End Source File
# Begin Source File

SOURCE=.\Edit_Append.h
# End Source File
# Begin Source File

SOURCE=.\numTeams.h
# End Source File
# Begin Source File

SOURCE=.\overallRtg.h
# End Source File
# Begin Source File

SOURCE=.\playerAge.h
# End Source File
# Begin Source File

SOURCE=.\playerFields.h
# End Source File
# Begin Source File

SOURCE=.\posPrototypes.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\roster2csv.h
# End Source File
# Begin Source File

SOURCE=.\RosterMaker.h
# End Source File
# Begin Source File

SOURCE=.\RosterMakerDlg.h
# End Source File
# Begin Source File

SOURCE=.\skinTone.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\teamArea.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\IDR_FIRS.bin
# End Source File
# Begin Source File

SOURCE=.\res\IDR_SURN.bin
# End Source File
# Begin Source File

SOURCE=.\res\RosterMaker.ico
# End Source File
# Begin Source File

SOURCE=.\res\RosterMaker.rc2
# End Source File
# End Group
# End Target
# End Project
