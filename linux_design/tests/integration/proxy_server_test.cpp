#include <gtest/gtest.h>
#include "proxy_server.h"

TEST(ProxyServerTest, StartStop) {
    ProxyServer proxy;
    ASSERT_NO_THROW(proxy.start());
    ASSERT_NO_THROW(proxy.stop());
}
