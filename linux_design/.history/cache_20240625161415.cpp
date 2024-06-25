#include "cache.h"

std::string Cache::get(const std::string& request) { // 获取数据对应的响应
    if (cache.find(request) != cache.end()) {
        return cache[request];
    }
    return "";
}

void Cache::put(const std::string& request, const std::string& response) {
    cache[request] = response;
}
