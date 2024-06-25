#ifndef FILTER_H
#define FILTER_H

#include <string>

class Filter {
public:
    bool isAllowed(const std::string& request);
};

#endif // FILTER_H
