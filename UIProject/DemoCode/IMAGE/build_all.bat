xcopy  /Y  Images.txt  Images_backup.txt

mergePNG -m -o 1000 -d 1  Images.txt
cd new
xcopy /Y  Images.txt  ..\Images.txt
cd  ..

mergePNG -m -o 1001 -d 1  Images.txt
cd new
xcopy /Y  Images.txt  ..\Images.txt
cd  ..

mergePNG -m -o 1002 -d 1  Images.txt
cd new
xcopy /Y  Images.txt  ..\Images.txt
cd  ..

mergePNG -m -o 1003 -d 1  Images.txt
cd new
xcopy /Y  Images.txt  ..\Images.txt
cd  ..

mergePNG -m -o 1004 -d 1  Images.txt
cd new
xcopy /Y  Images.txt  ..\Images.txt
cd  ..

mergePNG -m -o 1005 -d 1  Images.txt
cd new
xcopy /Y  Images.txt  ..\Images.txt
cd  ..

mergePNG -w 2048 -m -o 1006 -d 1 Images.txt
cd new
xcopy /Y  Images.txt  ..\Images.txt
cd  ..

mergePNG -w 2048 -m -o 1007 -d 1 Images.txt
cd new
xcopy /Y  Images.txt  ..\Images.txt
cd  ..

xcopy /Y   /s *.*  ..\..\jni\RES
pause



cd ..\..\jni\RES
rem call topngx.bat
call res_en.bat
cd ..\..\IMAGE_KARAOKE
pause