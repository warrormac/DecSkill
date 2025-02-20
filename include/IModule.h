#ifndef IMODULE_H
#define IMODULE_H

#include <vector>
#include <cstdint>

class IModule {
public:
    virtual ~IModule() = default;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void receiveData(const std::vector<uint8_t>& data) = 0;
};

#endif // IMODULE_H
