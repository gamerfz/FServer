rem 启动顺序不可随意更改,优先启动DBMgr,最后对外开放的LoginApp
rem --appid见ServerConfig.xml的AppID,用于对应相关服务器获取基本配置，同时也便于启动和管理多个同类型进程

@echo off
ping /n 4 127.1>nul
start DBMgrApp.exe --appid=1
ping /n 4 127.1>nul
start BaseCenterApp.exe --appid=2
ping /n 4 127.1>nul
start GameCenterApp.exe --appid=3
ping /n 4 127.1>nul
start BaseApp.exe --appid=100
ping /n 4 127.1>nul
start InterfaceApp.exe --appid=6
ping /n 4 127.1>nul
start PaymentApp.exe --appid=5
ping /n 1 127.1>nul
start LoginApp.exe --appid=4
ping /n 4 127.1>nul