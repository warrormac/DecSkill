#include <gtest/gtest.h>
#include "../include/GeneratorModule.h"

TEST(GeneratorModuleTest, GeneratesValidByteArray) {
    GeneratorModule generator([](const std::vector<uint8_t>& data) {
        EXPECT_GE(data.size(), 1);
        EXPECT_LE(data.size(), 100);
        for (uint8_t byte : data) {
            EXPECT_GE(byte, 0);
            EXPECT_LE(byte, 255);
        }
    });

    generator.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    generator.stop();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(GeneratorModuleTest, HandlesMultipleStartsAndStops) {
    GeneratorModule generator([](const std::vector<uint8_t>& data) {});

    for (int i = 0; i < 3; ++i) {  // Start and stop 3 times
        generator.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        generator.stop();
        EXPECT_TRUE(true);  // Just ensuring no crash
    }
}
