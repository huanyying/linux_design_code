#include "request_handler.h"
#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

std::string RequestHandler::handleRequest(const std::string& request) {
    // 解析请求中的主机名和端口号
    std::string host = "example.com"; // 示例
    int port = 80; // 示例

    // 创建目标服务器套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Error creating socket To target server" << std::endl;
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
        std::cerr << "Connection failed To tartget server" << std::endl;
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
}

std::string RequestHandler::handleHttpsRequest(const std::string& request) {
    // 解析请求中的主机名和端口号
    std::string host = "example.com"; // 示例
    int port = 443; // HTTPS 默认端口

    // 初始化 OpenSSL
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

    // 创建 SSL 上下文
    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        std::cerr << "Unable to create SSL context" << std::endl;
        ERR_print_errors_fp(stderr);
        return "";
    }

    // 创建目标服务器套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Error creating socket" << std::endl;
        SSL_CTX_free(ctx);
        return "";
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, "93.184.216.34", &server_addr.sin_addr) <= 0) { // 示例 IP
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        close(sock);
        SSL_CTX_free(ctx);
        return "";
    }

    // 连接到目标服务器
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        close(sock);
        SSL_CTX_free(ctx);
        return "";
    }

    // 创建 SSL 结构
    SSL *ssl = SSL_new(ctx);
    if (!ssl) {
        std::cerr << "Unable to create SSL structure" << std::endl;
        ERR_print_errors_fp(stderr);
        close(sock);
        SSL_CTX_free(ctx);
        return "";
    }

    // 关联 SSL 和套接字
    SSL_set_fd(ssl, sock);

    // 建立 SSL 连接
    if (SSL_connect(ssl) <= 0) {
        std::cerr << "SSL connection failed" << std::endl;
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        close(sock);
        SSL_CTX_free(ctx);
        return "";
    }

    // 向目标服务器发送请求
    if (SSL_write(ssl, request.c_str(), request.length()) <= 0) {
        std::cerr << "SSL write failed" << std::endl;
        ERR_print_errors_fp(stderr);
        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(sock);
        SSL_CTX_free(ctx);
        return "";
    }

    // 接收目标服务器的响应
    char buffer[4096] = {0};
    int bytesRead = SSL_read(ssl, buffer, sizeof(buffer));
    if (bytesRead <= 0) {
        std::cerr << "SSL read failed" << std::endl;
        ERR_print_errors_fp(stderr);
        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(sock);
        SSL_CTX_free(ctx);
        return "";
    }
    std::string response(buffer, bytesRead);

    // 关闭 SSL 连接
    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sock);
    SSL_CTX_free(ctx);

    return response;
}
