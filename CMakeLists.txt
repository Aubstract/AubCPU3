cmake_minimum_required(VERSION 3.28)
project(SoftCPU2)

set(CMAKE_CXX_STANDARD 17)

add_executable(SoftCPU2
        src/emulator/main.cpp
        src/emulator/CPU/RegisterFile.hpp
        src/emulator/CPU/RegisterFile.cpp
        src/emulator/CPU/Opcode.hpp
        src/emulator/CPU/ALU.hpp
        src/emulator/CPU/ALU.cpp
        src/emulator/CPU/Register.hpp
        src/emulator/CPU/CPU.hpp
        src/emulator/CPU/CPU.cpp
        src/emulator/CPU/Memory.hpp
        src/emulator/IO_Devices/IODevice.hpp
        src/emulator/IO_Devices/IOManager.hpp
        src/emulator/IO_Devices/IOManager.cpp
        src/emulator/log/log.hpp
        src/emulator/log/log.cpp
        src/emulator/IO_Devices/FancyConsole.hpp
        src/emulator/IO_Devices/FancyConsole.cpp
)
