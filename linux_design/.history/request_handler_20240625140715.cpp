#include "request_handler.h"
#include "ssl_utils.h"
#include <iostream>

std::string RequestHandler::handleRequest(const std::string& request) {
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
