#include "filter.h"
#include <regex>
#include <iostream>

bool Filter::isAllowed(const std::string& request) {
    // 阻止访问某个特定域名
    std::regex blockedPattern("blocked.com");
    if(std::regex_search(request, blockedPattern)) // 进行匹配
    {
        return true;
    } else
    {
        std::cout << std::endl << "This request is blocked, included blacklist" << std::endl;
    }
}
