#include <gtest/gtest.h>
#include "request_handler.h"

TEST(RequestHandlerTest, HandleRequest) {
    RequestHandler handler;
    std::string request = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\n";
    std::string response = handler.handleRequest(request);
    EXPECT_EQ(response, "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!");
}

TEST(RequestHandlerTest, HandleHttpsRequest) {
    RequestHandler handler;
    std::string request = "encrypted(GET / HTTPS/1.1\r\nHost: example.com\r\n\r\n)";
    std::string response = handler.handleHttpsRequest(request);
    EXPECT_EQ(response, "encrypted(HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, HTTPS!)");
}
