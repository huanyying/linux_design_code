#ifndef SSL_UTILS_H
#define SSL_UTILS_H

#include <string>

class SSLUtils {
public:
    static std::string encrypt(const std::string& data);
    static std::string decrypt(const std::string& data);
};

#endif // SSL_UTILS_H
