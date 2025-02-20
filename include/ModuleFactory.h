#ifndef MODULE_FACTORY_H
#define MODULE_FACTORY_H

#include "IModule.h"
#include <functional>
#include <memory>

std::unique_ptr<IModule> createGeneratorModule(std::function<void(const std::vector<uint8_t>&)> callback);
std::unique_ptr<IModule> createFilterModule(std::function<void(const std::vector<uint8_t>&)> callback);
std::unique_ptr<IModule> createRecorderModule();

#endif // MODULE_FACTORY_H
