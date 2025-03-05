# DecSkill

A modular C++ project implementing a **byte array processing pipeline** with three independent modules:
- **GeneratorModule** → Generates random byte arrays.
- **FilterModule** → Filters byte arrays containing a specific byte sequence.
- **RecorderModule** → Records and prints all received byte arrays.

The project is **multithreaded** and uses **STL (Standard Template Library) only**.

---

##  Getting Started

### 🔹 **1. Clone the Repository**
To pull the latest version of this project, run:
```sh
git clone https://github.com/warrormac/DecSkill.git
cd DecSkill
```

If you've already cloned the repository and want to update:
```sh
git pull origin main
```

Requirements
Before running the project, ensure you have the following installed:

* C++ Compiler (GCC/Clang)
```sh
  sudo apt update && sudo apt install g++
```
* CMake (Build System)
```sh
  sudo apt install cmake
```
* Google Test (For Running Unit Tests)
```sh
  sudo apt install libgtest-dev
```
* Make (Build Automation)
```sh
  sudo apt install make
```

## Build the Project
Run the following commands from the project root directory:
```sh
  rm -rf build
  mkdir build && cd build
  cmake ..
  make
```
This will compile the project and create an executable inside build/.


## Run the Application
After building the project, run:
```sh
  ./build/DECSKILL
```
This will start the three-threaded module pipeline.

##  Run Tests
Unit tests are written using Google Test.
 1. Run All Tests
  ```sh
    cd build
    ctest --output-on-failure
  ```
2. Run Specific Tests
  ```sh
    ./tests/test_generator --gtest_filter=GeneratorModuleTest.*
    ./tests/test_filter --gtest_filter=FilterModuleTest.*
    ./tests/test_recorder --gtest_filter=RecorderModuleTest.*

  ```

## Project Structure
```sh
  DecSkill/
│── include/          # Header files (.h)
│── src/              # Implementation files (.cpp)
│── tests/            # Unit tests
│── CMakeLists.txt    # CMake configuration
│── README.md         # Project documentation
│── build/            # Compiled output (ignored in Git)

```
