@echo off
xcopy Res\* Release\Res /D /I /Y
xcopy hge.dll Release\ /D /I /Y
xcopy bass.dll Release\ /D /I /Y

xcopy Release\Res\* Exec\Res\ /D /I /Y
xcopy Release\Core512.exe Exec\ /D /I /Y
xcopy Release\*.dll Exec\ /D /I /Y
