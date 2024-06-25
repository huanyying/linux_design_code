#include "proxy_server.h"

int main(int argc, char* argv[]) {
    ProxyServer proxyServer;
    proxyServer.start();    // 启动服务器
    return 0;
}
