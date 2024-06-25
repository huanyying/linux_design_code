#include "request_handler.h"
#include "ssl_utils.h"
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

std::string RequestHandler::handleRequest(const std::string& request) {

// 解析请求中的主机名和端口号
    std::string host = "example.com"; // 示例
    int port = 80; // 示例

    // 创建目标服务器套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return "";
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, "93.184.216.34", &server_addr.sin_addr) <= 0) { // 示例 IP
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        close(sock);
        return "";
    }

    // 连接到目标服务器
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        close(sock);
        return "";
    }

    // 向目标服务器发送请求
    send(sock, request.c_str(), request.length(), 0);

    // 接收目标服务器的响应
    char buffer[4096] = {0};
    int bytesRead = read(sock, buffer, sizeof(buffer));
    std::string response(buffer, bytesRead);

    // 关闭套接字
    close(sock);

    return response;

    // 处理HTTP请求
    std::cout << "Handling HTTP request: " << request << std::endl;
    // 模拟响应
    return "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!";
}

std::string RequestHandler::handleHttpsRequest(const std::string& request) {
    // 处理HTTPS请求
    std::cout << "Handling HTTPS request: " << request << std::endl;
    // 使用SSL/TLS解密和加密
    std::string decryptedRequest = SSLUtils::decrypt(request);
    // 模拟响应
    std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, HTTPS!";
    return SSLUtils::encrypt(response);
}
