!include "MUI.nsh"

!define NAME "flume-dc"
!define COMPANY "Saratoga Data Systems"
!define INSTDIR "C:\Flume\bin\${NAME}"

Icon "favicon.ico"

Name "Flume Installer"

RequestExecutionLevel admin

Section "Install"
	SetShellVarContext all
	SetOutPath ${INSTDIR}
	File "${NAME}.exe"
	File "vcredist_x64.exe"
	File "favicon.ico"

	WriteUninstaller "${INSTDIR}\Uninstall.exe"

	ExecWait "${INSTDIR}\vcredist_x64.exe /install /quiet"
	createDirectory "$SMPROGRAMS\${COMPANY}"
	createShortcut "$SMPROGRAMS\${COMPANY}\Flume DC.lnk" "${INSTDIR}\${NAME}.exe" "" "${INSTDIR}\favicon.ico" 
	createShortcut "$DESKTOP\Flume DC.lnk" "${INSTDIR}\${NAME}.exe" "" "${INSTDIR}\favicon.ico" 
	createShortcut "$SMPROGRAMS\${COMPANY}\Uninstall.lnk" "${INSTDIR}\Uninstall.exe" "" "${INSTDIR}\favicon.ico" 

	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "DisplayName" "Flume (remove only)"
  	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "UninstallString" "${INSTDIR}\Uninstall.exe"
SectionEnd

Section "un.Uninstall"
	SetShellVarContext all
	RMDir /r "${INSTDIR}"
	RMDir /r "$SMPROGRAMS\${COMPANY}"

  	DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}"
SectionEnd
