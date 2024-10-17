# C++集群聊天服务端和客户端
![result](result.png)
## 介绍
* 使用Muduo库构建服务端和客户端网络层代码；
* 使用Json第三方库序列化和反序列化通信数据；
* 使用Nginx的TCP**负载均衡**功能，分发客户端请求；
* 使用中间件Redis的发布-订阅制，解决**跨服务器分布式**通信；
* 使用MySQL接口，实现数据持久化；
* 基于Cmake编译构建项目。

## 使用
1. 编译项目
```bash
cd ./build
cmake ..
make
```
2. 启动各项服务
```
# mysql服务 3306端口
sudo servcie mysql start

# nginx服务 8000端口，可以在配置中更改对外客户端端口
cd /usr/local/nginx/sbin
sudo ./nginx

# nginx配置文件，配置多台服务器的权重，ip地址和端口
vim /usr/local/nginx/conf/nginx.conf

# redis服务 6379端口
sudo service redis-server start

# 查看端口检查各项服务是启动
netstat -tanp
```

3. 启动服务器
```
# ./bin/ChatServer [your ip] [your port]
./bin/ChatServer 127.0.0.1 6000 # 服务器1
./bin/ChatServer 127.0.0.1 6001 # 服务器2
```

4. 启动客户端
```
./bin/ChatClient 127.0.0.1 8000
```