# Enable testing
enable_testing()

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add test executables
add_executable(test_generator test_generator.cpp ../src/GeneratorModule.cpp)
add_executable(test_filter test_filter.cpp ../src/FilterModule.cpp)
add_executable(test_recorder test_recorder.cpp ../src/RecorderModule.cpp)

# Link with Google Test and pthread
target_link_libraries(test_generator PRIVATE ${GTEST_LIBRARIES} pthread)
target_link_libraries(test_filter PRIVATE ${GTEST_LIBRARIES} pthread)
target_link_libraries(test_recorder PRIVATE ${GTEST_LIBRARIES} pthread)

# Register tests
add_test(NAME GeneratorModuleTest COMMAND test_generator)
add_test(NAME FilterModuleTest COMMAND test_filter)
add_test(NAME RecorderModuleTest COMMAND test_recorder)