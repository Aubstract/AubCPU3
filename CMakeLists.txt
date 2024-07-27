cmake_minimum_required(VERSION 3.28)
project(SoftCPU2)

set(CMAKE_CXX_STANDARD 17)

add_executable(SoftCPU2
        src/computer/main.cpp
        src/computer/CPU/RegisterFile.hpp
        src/computer/CPU/RegisterFile.cpp
        src/computer/CPU/Opcode.hpp
        src/computer/CPU/ALU.hpp
        src/computer/CPU/ALU.cpp
        src/computer/CPU/Register.hpp
        src/computer/CPU/CPU.hpp
        src/computer/CPU/CPU.cpp
        src/computer/CPU/Memory.hpp
        src/computer/IO_Devices/IODevice.hpp
        src/computer/IO_Devices/IOManager.hpp
        src/computer/IO_Devices/IOManager.cpp
        src/computer/log/log.hpp
        src/computer/log/log.cpp
        src/computer/IO_Devices/FancyConsole.hpp
        src/computer/IO_Devices/FancyConsole.cpp
)
