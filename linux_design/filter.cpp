#include "filter.h"
#include <regex>

bool Filter::isAllowed(const std::string& request) {
    // 阻止访问某个特定域名
    std::regex blockedPattern("blocked.com");
    return !std::regex_search(request, blockedPattern); // 进行匹配
}
