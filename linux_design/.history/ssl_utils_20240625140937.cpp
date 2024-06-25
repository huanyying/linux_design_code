#include "ssl_utils.h"
#include <openssl/ssl.h>
#include <openssl/err.h>

std::string SSLUtils::encrypt(const std::string& data) {
    // 模拟加密，实际使用OpenSSL实现
    return "encrypted(" + data + ")";
}

std::string SSLUtils::decrypt(const std::string& data) {
    // 模拟解密，实际使用OpenSSL实现
    return data.substr(10, data.length() - 11);
}
