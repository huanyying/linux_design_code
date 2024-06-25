#include "proxy_server.h"

int main(int argc, char* argv[]) {
    ProxyServer proxyServer;    // 创建一个代理服务器
    proxyServer.start();    // 启动服务器
    return 0;
}
