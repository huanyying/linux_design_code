#include "proxy_server.h"
#include "request_handler.h"
#include "filter.h"
#include "cache.h"
#include "logger.h"
#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

void ProxyServer::start() {
    std::cout << "Proxy server started" << std::endl;

    // 初始化各个组件
    RequestHandler requestHandler;
    Filter filter;
    Cache cache;
    Logger logger;

    // 创建服务器套接字
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return;
    }

    // 绑定地址和端口
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(server_fd);
        return;
    }

    // 监听连接
    if (listen(server_fd, 10) == -1) {
        std::cerr << "Failed to listen on socket" << std::endl;
        close(server_fd);
        return;
    }

    // 处理客户端连接
    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd == -1) {
            std::cerr << "Failed to accept connection" << std::endl;
            continue;
        }

        // 使用一个新的线程来处理请求
        std::thread([client_fd, &requestHandler, &filter, &cache, &logger]() {
            char buffer[1024] = {0};

            // 读取客户端传入的数据
            read(client_fd, buffer, 1024);

            std::string request(buffer);    // 转换为 string

            // 请求过滤
            if (!filter.isAllowed(request)) {
                std::cout << "Request blocked" << std::endl;
                close(client_fd);
                return;
            }

            // 缓存处理
            std::string response = cache.get(request);  // 从缓存中回应
            if (response.empty()) { // 缓存没有命中，转发数据
                response = requestHandler.handleRequest(request);
                cache.put(request, response);
            }

            // 日志记录
            logger.log("Processed request: " + request);

            send(client_fd, response.c_str(), response.length(), 0);
            close(client_fd);
        }).detach();
    }

    // 关闭服务器套接字
    close(server_fd);
}


void ProxyServer::stop() {
    std::cout << "Proxy server stopped" << std::endl;
}
