#include "cache.h"

std::string Cache::get(const std::string& request) {
    if (cache.find(request) != cache.end()) {
        return cache[request];
    }
    return "";
}

void Cache::put(const std::string& request, const std::string& response) {
    cache[request] = response;
}
