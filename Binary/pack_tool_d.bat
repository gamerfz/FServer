cls 
@echo off
::清除原有目录及文件
rd /s/q .\Game
::新建主目录开始copy
mkdir .\Game
mkdir .\Game\Log
::启动bat文件
xcopy .\start_d.bat .\Game\ /y
xcopy .\close_d.bat .\Game\ /y
::lib及dll文件
xcopy .\libmysql.dll .\Game\ /y
xcopy .\libcurld.dll .\Game\ /y
xcopy .\Lib\Core_d.lib .\Game\Lib\ /y
xcopy .\Lib\hiredis_d.lib .\Game\Lib\ /y
xcopy .\Lib\libevent_d.lib .\Game\Lib\ /y
xcopy .\Lib\libglog_static_d.lib .\Game\Lib\ /y
xcopy .\Lib\libmysql.lib .\Game\Lib\ /y
xcopy .\Lib\libprotobuf_d.lib .\Game\Lib\ /y
xcopy .\Lib\libprotoc_d.lib .\Game\Lib\ /y
xcopy .\Lib\lua_d.lib .\Game\Lib\ /y
xcopy .\Lib\mysqlpp_d.lib .\Game\Lib\ /y
xcopy .\Lib\Win32_Interop_d.lib .\Game\Lib\ /y
::exe文件
xcopy .\BaseApp_d.exe .\Game\ /y
xcopy .\BaseCenterApp_d.exe .\Game\ /y
xcopy .\CubbyApp_d.exe .\Game\ /y
xcopy .\DBMgrApp_d.exe .\Game\ /y
xcopy .\GameApp_d.exe .\Game\ /y
xcopy .\GameCenterApp_d.exe .\Game\ /y
xcopy .\InterfaceApp_d.exe .\Game\ /y
xcopy .\LoginApp_d.exe .\Game\ /y
xcopy .\PaymentApp_d.exe .\Game\ /y
::资源配置表及脚本
xcopy .\Resource\Config .\Game\Resource\Config /s/e/i/y
xcopy .\Resource\Script .\Game\Resource\Script /s/e/i/y

@echo off
echo Copy finished ...

@echo off
pause