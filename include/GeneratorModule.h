#ifndef GENERATOR_MODULE_H
#define GENERATOR_MODULE_H

#include "IModule.h"
#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <random>

class GeneratorModule : public IModule {
public:
    using Callback = std::function<void(const std::vector<uint8_t>&)>;

    explicit GeneratorModule(Callback callback);
    ~GeneratorModule();

    void start() override;
    void stop() override;
    void receiveData(const std::vector<uint8_t>& data) override {}

private:
    void run();
    std::vector<uint8_t> generateRandomBytes();

    std::thread workerThread;
    std::atomic<bool> running{false};
    Callback sendDataCallback;
};

#endif // GENERATOR_MODULE_H
