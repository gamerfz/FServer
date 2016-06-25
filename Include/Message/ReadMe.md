proto-build.exe
.proto转c++文件的工具,详细见proto-build项目

GlobalDef.proto
Client与Server公用数据结构定义(message+enum)
MessageBase.proto
消息基类+消息类型定义 所有用于网络通信的消息定义proto文件都需要import "MessageBase.proto"
ServerMsg.proto
Server内部消息,客户端请无视
ClientMsg.proto
Client与Server之间通信消息


