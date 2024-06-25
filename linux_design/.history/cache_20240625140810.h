#ifndef CACHE_H
#define CACHE_H

#include <unordered_map>
#include <string>

class Cache {
public:
    std::string get(const std::string& request);
    void put(const std::string& request, const std::string& response);
private:
    std::unordered_map<std::string, std::string> cache;
};

#endif // CACHE_H
