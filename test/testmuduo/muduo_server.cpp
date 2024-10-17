#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <string>
#include <functional>

using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;


/*基于muduo网络库开发服务器程序
1. 组合TcpServer对象
2. 创建EventLoop事件循环对象
3. 明确TcpServer构造需要什么参数，输出ChatServer的构造函数
4. 在当前服务类的构造函数当中，注册处理连接的回调函数和处理读写事件的回调函数
5. 设置合适的线程数量，muduo库回自己分配I/O线程和worker线程
*/
class ChatServer{
public:
    ChatServer(EventLoop *loop, // 事件循环
				const InetAddress &listenAddr,  // IP + Port
				const string &nameArg)  // 服务器的名字
		: _server(loop, listenAddr, nameArg), _loop(loop){
		// 给服务器注册连接的创建和断开回调
		_server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

		// 给服务器注册用户读写事件回调
		_server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

		// 设置服务器线程数量
		_server.setThreadNum(4);
	}

	void start(){
		_server.start();
	}

private:
	// 专门处理用户的连接创建和断开
	void onConnection(const TcpConnectionPtr& conn)
	{
		if(conn->connected())
			cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << "state:online" << endl;
		else
		{
			cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << "state:offline" << endl;
			conn->shutdown();
		}
	}

	// 专门处理用户的读写事件
	void onMessage(const TcpConnectionPtr &conn, // 连接
					Buffer *buffer,  // 缓冲区
					Timestamp time)  // 接受到数据的事件信息
	{
		string buf = buffer->retrieveAllAsString();
		cout << "recv data:" << buf << "time:" << time.toString() << endl;
		conn->send(buf);
	}


    TcpServer _server;  // server
    EventLoop *_loop;  // epoll
};

int main()
{
	EventLoop loop;

	InetAddress addr("127.0.0.1", 6000);
	ChatServer server(&loop, addr, "ChatServer");

	server.start();
	loop.loop();

	return 0;
}