# Microsoft Developer Studio Project File - Name="Admin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Admin - Win32 Unicode Debug No PreComp
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Admin.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Admin.mak" CFG="Admin - Win32 Unicode Debug No PreComp"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Admin - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Admin - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Admin - Win32 Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Admin - Win32 Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Admin - Win32 Unicode Debug No PreComp" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Admin - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Output\VC6\Release"
# PROP Intermediate_Dir "Output\VC6\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W4 /WX /GX /Zi /O2 /I "..\..\\" /I "$(STLPORT_ROOT)\stlport" /FI"Warnings.h" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Admin - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Output\VC6\Debug"
# PROP Intermediate_Dir "Output\VC6\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /WX /GX /Zi /Od /I "..\..\\" /I "$(STLPORT_ROOT)\stlport" /FI"Warnings.h" /D "_DEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /FD /GZ /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Admin - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Admin___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "Admin___Win32_Unicode_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Output\VC6\UDebug"
# PROP Intermediate_Dir "Output\VC6\UDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\\" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /WX /GX /Zi /Od /I "..\..\\" /I "$(STLPORT_ROOT)\stlport" /FI"Warnings.h" /D "_DEBUG" /D "UNICODE" /D "_UNICODE" /D "_LIB" /D "WIN32" /D "_MBCS" /FD /GZ /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Admin - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Admin___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "Admin___Win32_Unicode_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Output\VC6\URelease"
# PROP Intermediate_Dir "Output\VC6\URelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "..\..\\" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W4 /WX /GX /Zi /O2 /I "..\..\\" /I "$(STLPORT_ROOT)\stlport" /FI"Warnings.h" /D "NDEBUG" /D "UNICODE" /D "_UNICODE" /D "_LIB" /D "WIN32" /D "_MBCS" /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Admin - Win32 Unicode Debug No PreComp"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Admin___Win32_Unicode_Debug_No_PreComp"
# PROP BASE Intermediate_Dir "Admin___Win32_Unicode_Debug_No_PreComp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Output\VC6\UDebugNoPreComp"
# PROP Intermediate_Dir "Output\VC6\UDebugNoPreComp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /GX /Zi /Od /I "..\..\\" /I "$(STLPORT_ROOT)\stlport" /FI"Warnings.h" /D "_DEBUG" /D "UNICODE" /D "_UNICODE" /D "_LIB" /D "WIN32" /D "_MBCS" /D _WIN32_WINNT=0x0400 /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /WX /GX /Zi /Od /I "..\..\\" /I "$(STLPORT_ROOT)\stlport" /FI"Warnings.h" /D "_DEBUG" /D "UNICODE" /D "_UNICODE" /D "_LIB" /D "WIN32" /D "_MBCS" /FD /GZ /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Admin - Win32 Release"
# Name "Admin - Win32 Debug"
# Name "Admin - Win32 Unicode Debug"
# Name "Admin - Win32 Unicode Release"
# Name "Admin - Win32 Unicode Debug No PreComp"
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Admin.h
# End Source File
# Begin Source File

SOURCE=.\NoPlatformSDK.h
# End Source File
# Begin Source File

SOURCE=.\SecureCRT.h
# End Source File
# Begin Source File

SOURCE=.\TargetWindowsVersion.h
# End Source File
# Begin Source File

SOURCE=.\Todo.h
# End Source File
# Begin Source File

SOURCE=.\Types.h
# End Source File
# Begin Source File

SOURCE=.\Warnings.h
# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter "*.*"
# Begin Source File

SOURCE=.\Docs\Doxyfile.developer
# End Source File
# Begin Source File

SOURCE=.\Docs\Doxyfile.user
# End Source File
# Begin Source File

SOURCE=.\Docs\Groups.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\Overview.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\ProgrammingConcepts.txt
# End Source File
# Begin Source File

SOURCE=.\Docs\Testing.txt
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Admin.cpp
# End Source File
# End Group
# End Target
# End Project