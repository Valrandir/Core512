@echo off
xcopy Res\* Debug\Res /D /I /Y
xcopy hge.dll Debug\ /D /I /Y
xcopy bass.dll Debug\ /D /I /Y
