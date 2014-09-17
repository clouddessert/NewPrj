# Microsoft Developer Studio Project File - Name="NodePlat" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=NodePlat - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NodePlat.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NodePlat.mak" CFG="NodePlat - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NodePlat - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "NodePlat - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NodePlat - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "NodePlat - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
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
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "NodePlat - Win32 Release"
# Name "NodePlat - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AllParamSheet.cpp

!IF  "$(CFG)" == "NodePlat - Win32 Release"

!ELSEIF  "$(CFG)" == "NodePlat - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Alg\CooperativeMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgAllSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgCtlView.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgEighthPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgFifthPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgFourthPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgFstPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgListView.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgSecPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgSeventhPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgSixthPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgThreePage.cpp
# End Source File
# Begin Source File

SOURCE=.\Alg\MultipleIdentify.cpp
# End Source File
# Begin Source File

SOURCE=.\MySocket.cpp
# End Source File
# Begin Source File

SOURCE=.\NetworkSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\NodePlat.cpp
# End Source File
# Begin Source File

SOURCE=.\NodePlat.rc
# End Source File
# Begin Source File

SOURCE=.\NodePlatDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\NodePlatView.cpp
# End Source File
# Begin Source File

SOURCE=.\ParamFstPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ParamSecondPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Alg\SingleIdentify.cpp

!IF  "$(CFG)" == "NodePlat - Win32 Release"

!ELSEIF  "$(CFG)" == "NodePlat - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Alg\XSi.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AllParamSheet.h
# End Source File
# Begin Source File

SOURCE=".\Comm Struct.h"
# End Source File
# Begin Source File

SOURCE=.\CommHeader.h
# End Source File
# Begin Source File

SOURCE=.\Alg\CooperativeMsg.h
# End Source File
# Begin Source File

SOURCE=.\DrawView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MsgAllSheet.h
# End Source File
# Begin Source File

SOURCE=.\MsgCtlView.h
# End Source File
# Begin Source File

SOURCE=.\MsgEighthPage.h
# End Source File
# Begin Source File

SOURCE=.\MsgFifthPage.h
# End Source File
# Begin Source File

SOURCE=.\MsgFourthPage.h
# End Source File
# Begin Source File

SOURCE=.\MsgFstPage.h
# End Source File
# Begin Source File

SOURCE=.\MsgListView.h
# End Source File
# Begin Source File

SOURCE=.\MsgSecPage.h
# End Source File
# Begin Source File

SOURCE=.\MsgSeventhPage.h
# End Source File
# Begin Source File

SOURCE=.\MsgSixthPage.h
# End Source File
# Begin Source File

SOURCE=.\MsgSocket.h
# End Source File
# Begin Source File

SOURCE=.\MsgThreePage.h
# End Source File
# Begin Source File

SOURCE=.\Alg\MultipleIdentify.h
# End Source File
# Begin Source File

SOURCE=.\MySocket.h
# End Source File
# Begin Source File

SOURCE=.\NetworkSetting.h
# End Source File
# Begin Source File

SOURCE=.\NodePlat.h
# End Source File
# Begin Source File

SOURCE=.\NodePlatDoc.h
# End Source File
# Begin Source File

SOURCE=.\NodePlatView.h
# End Source File
# Begin Source File

SOURCE=.\ParamFstPage.h
# End Source File
# Begin Source File

SOURCE=.\ParamSecondPage.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StructHeader.h
# End Source File
# Begin Source File

SOURCE=.\Alg\XSi.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\feiji.bmp
# End Source File
# Begin Source File

SOURCE=.\res\map.bmp
# End Source File
# Begin Source File

SOURCE=.\res\missile.bmp
# End Source File
# Begin Source File

SOURCE=.\res\NodePlat.ico
# End Source File
# Begin Source File

SOURCE=.\res\NodePlat.rc2
# End Source File
# Begin Source File

SOURCE=.\res\NodePlatDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\ship1.bmp
# End Source File
# Begin Source File

SOURCE=".\res\²¶»ñ.bmp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
