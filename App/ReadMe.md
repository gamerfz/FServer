BaseApp
	游戏内玩家对外的主要连接,起到网关的作用,也可以作为某些游戏的大厅服务器,连接DBMgrApp,也可作为主要逻辑服,特别是处理非在线玩家的逻辑
	
BaseCenterApp
	服务端核心APP之一,主要功能是管理所有BaseApp和LoginApp,并连接DBMgrApp
	
CubbyApp
	作为辅助逻辑服,用于需要大量开房对战的游戏,非必须,根据游戏类型而定
	
DBMgrApp
	服务端核心APP之一,管理所有mysql连接,通过网络底层的消息队列,对DB做了一个缓存机制

GameApp
	逻辑服,处理游戏内主要逻辑,与BaseApp一一对应
	
GameCenterApp
	服务端核心APP之一,类似BaseCenterApp,管理所有GameApp

InterfaceApp
	外部接口,后台工具,数据查询等

LoginApp
	登录服务器,处理玩家登录相关的内容,包括平台验证等

PaymentApp
	支付服务器

RobotApp
	机器人,模拟客户端

StressApp
	机器人辅助工具,用于启动多个机器人做压力测试