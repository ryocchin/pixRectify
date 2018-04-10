echo off

REM
REM build qt help project for hikari
REM - Japanese
REM - English
REM

set PATH=C:\PixPLOT\QtRectify\manual

del /Q %PATH%\pixrectify_jp_index.qhc
del /Q %PATH%\pixrectify_jp_index.qch
REM del /Q %PATH%\pixrectify_jp_index.qcp
					  
del /Q %PATH%\pixrectify_en_index.qhc
del /Q %PATH%\pixrectify_en_index.qch
REM del /Q %PATH%\pixrectify_en_index.qcp

REM
REM [1]Prepare HTMLs 
REM      pixrectify_jp_index.html
REM      pixrectify_en_index.html
REM
REM [2]Work on Qt help Project File (qhp) using text editor. This is xml file. 
REM      pixrectify_jp_index.qhp
REM      pixrectify_en_index.qhp
REM
REM [3]Run qhelpgenerator.exe to generate qch from above qhp
REM

%QTDIR%\bin\qhelpgenerator.exe %PATH%\pixrectify_jp_index.qhp -o %PATH%\pixrectify_jp_index.qch
%QTDIR%\bin\qhelpgenerator.exe %PATH%\pixrectify_en_index.qhp -o %PATH%\pixrectify_en_index.qch

REM 
REM [4]Use text editor to create qhcp(Qt help collection Project) file. This is xml. 
REM       pixrectify_jp_index.qhcp
REM       pixrectify_en_index.qhcp
REM
REM [5]RUn qcollectiongenerator.exe to generate the Collection file (qhc) from above qhcp.
REM 

%QTDIR%\bin\qcollectiongenerator.exe %PATH%\pixrectify_jp_index.qhcp -o %PATH%\pixrectify_jp_index.qhc
%QTDIR%\bin\qcollectiongenerator.exe %PATH%\pixrectify_en_index.qhcp -o %PATH%\pixrectify_en_index.qhc

REM 
REM test the created files using assistant.exe
REM
 
REM %QTDIR%\bin\assistant.exe -unregister %PATH%\pixrectify_jp_index.qch
REM %QTDIR%\bin\assistant.exe -collectionFile %PATH%\pixrectify_jp_index.qhc

REM %QTDIR%\bin\assistant.exe -unregister %PATH%\pixrectify_en_index.qch
REM %QTDIR%\bin\assistant.exe -collectionFile %PATH%\pixrectify_en_index.qhc
