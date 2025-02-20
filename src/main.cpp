#include <iostream>
#include <thread>
#include <chrono>
#include "IModule.h"
#include "ModuleFactory.h"

int main() {
    std::cout << "[Main] Creating modules..." << std::endl;

    auto recorder = createRecorderModule();

    auto filter = createFilterModule([&](const std::vector<uint8_t>& data) {
        recorder->receiveData(data);
    });
    
    auto generator = createGeneratorModule([&](const std::vector<uint8_t>& data) {
        filter->receiveData(data);
    });

    std::cout << "[Main] Starting modules..." << std::endl;
    generator->start();
    filter->start();
    recorder->start();

    std::this_thread::sleep_for(std::chrono::seconds(100));

    std::cout << "[Main] Stopping modules..." << std::endl;
    generator->stop();
    filter->stop();
    recorder->stop();

    std::cout << "[Main] Program finished." << std::endl;
    return 0;
}
