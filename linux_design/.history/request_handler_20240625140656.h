#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string>

class RequestHandler {
public:
    std::string handleRequest(const std::string& request);
    std::string handleHttpsRequest(const std::string& request);
};

#endif // REQUEST_HANDLER_H
