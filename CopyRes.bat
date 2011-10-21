@echo off

xcopy Res\* Debug\Res /D /I /Y
xcopy hge.dll Debug\ /D /I /Y

xcopy Res\* Release\Res /D /I /Y
xcopy hge.dll Release\ /D /I /Y
