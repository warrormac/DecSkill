#include "ModuleFactory.h"
#include "GeneratorModule.h"
#include "FilterModule.h"
#include "RecorderModule.h"

std::unique_ptr<IModule> createGeneratorModule(std::function<void(const std::vector<uint8_t>&)> callback) {
    return std::make_unique<GeneratorModule>(callback);
}

std::unique_ptr<IModule> createFilterModule(std::function<void(const std::vector<uint8_t>&)> callback) {
    return std::make_unique<FilterModule>(callback);
}

std::unique_ptr<IModule> createRecorderModule() {
    return std::make_unique<RecorderModule>();
}
