cls 
@echo off
::清除原有目录及文件
rd /s/q .\Game
::新建主目录开始copy
mkdir .\Game
mkdir .\Game\Log
::启动bat文件
xcopy .\start.bat .\Game\ /y
xcopy .\close.bat .\Game\ /y
::lib及dll文件
xcopy .\libmysql.dll .\Game\ /y
xcopy .\libcurld.dll .\Game\ /y
xcopy .\Lib\Core.lib .\Game\Lib\ /y
xcopy .\Lib\hiredis.lib .\Game\Lib\ /y
xcopy .\Lib\libevent.lib .\Game\Lib\ /y
xcopy .\Lib\libglog_static.lib .\Game\Lib\ /y
xcopy .\Lib\libmysql.lib .\Game\Lib\ /y
xcopy .\Lib\libprotobuf.lib .\Game\Lib\ /y
xcopy .\Lib\libprotoc.lib .\Game\Lib\ /y
xcopy .\Lib\lua.lib .\Game\Lib\ /y
xcopy .\Lib\mysqlpp.lib .\Game\Lib\ /y
xcopy .\Lib\Win32_Interop.lib .\Game\Lib\ /y
::exe文件
xcopy .\BaseApp.exe .\Game\ /y
xcopy .\BaseCenterApp.exe .\Game\ /y
xcopy .\CubbyApp.exe .\Game\ /y
xcopy .\DBMgrApp.exe .\Game\ /y
xcopy .\GameApp.exe .\Game\ /y
xcopy .\GameCenterApp.exe .\Game\ /y
xcopy .\InterfaceApp.exe .\Game\ /y
xcopy .\LoginApp.exe .\Game\ /y
xcopy .\PaymentApp.exe .\Game\ /y
::资源配置表及脚本
xcopy .\Resource\Config .\Game\Resource\Config /s/e/i/y
xcopy .\Resource\Script .\Game\Resource\Script /s/e/i/y

@echo off
echo Copy finished ...

@echo off
pause