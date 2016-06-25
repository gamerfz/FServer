::启动顺序不可随意更改,优先启动DBMgr,最后对外开放的LoginApp
::--appid见ServerConfig.xml的AppID,用于对应相关服务器获取基本配置，同时也便于启动和管理多个同类型进程


rem ====== Servers start now ======

@echo off
ping /n 4 127.1>nul
start DBMgrApp_d.exe --appid=1
ping /n 4 127.1>nul
start BaseCenterApp_d.exe --appid=2
ping /n 4 127.1>nul
start GameCenterApp_d.exe --appid=3
ping /n 4 127.1>nul
start GameApp_d.exe --appid=101
ping /n 4 127.1>nul
::start GameApp_d.exe --appid=103
::ping /n 4 127.1>nul
start BaseApp_d.exe --appid=100
ping /n 4 127.1>nul
::start BaseApp_d.exe --appid=102
::ping /n 4 127.1>nul
::start InterfaceApp_d.exe --appid=6
::ping /n 4 127.1>nul
::start PaymentApp_d.exe --appid=5
::ping /n 1 127.1>nul
start LoginApp_d.exe --appid=4
ping /n 4 127.1>nul






