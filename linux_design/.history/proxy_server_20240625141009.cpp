#include "proxy_server.h"
#include "request_handler.h"
#include "filter.h"
#include "cache.h"
#include "logger.h"
#include <iostream>

void ProxyServer::start() {
    std::cout << "Proxy server started" << std::endl;
    
    RequestHandler requestHandler;
    Filter filter;
    Cache cache;
    Logger logger;

    std::string request = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\n";
    
    // 请求过滤
    if (!filter.isAllowed(request)) {
        std::cout << "Request blocked" << std::endl;
        return;
    }
    
    // 缓存处理
    std::string response = cache.get(request);
    if (response.empty()) {
        response = requestHandler.handleRequest(request);
        cache.put(request, response);
    }
    
    // 日志记录
    logger.log("Processed request: " + request);
    std::cout << "Response: " << response << std::endl;
}

void ProxyServer::stop() {
    std::cout << "Proxy server stopped" << std::endl;
}
