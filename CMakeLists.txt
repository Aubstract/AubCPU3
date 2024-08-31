cmake_minimum_required(VERSION 3.28)
project(AubCPU3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Emulator
        src/emulator/main.cpp
        src/emulator/CPU/RegisterFile.hpp
        src/emulator/CPU/RegisterFile.cpp
        src/emulator/CPU/Opcode.hpp
        src/emulator/CPU/ALU.hpp
        src/emulator/CPU/ALU.cpp
        src/emulator/CPU/CPU.hpp
        src/emulator/CPU/CPU.cpp
        src/emulator/CPU/Memory.hpp
        src/emulator/IO_Devices/AddrSpaceManager.hpp
        src/emulator/IO_Devices/AddrSpaceManager.cpp
        src/emulator/log/log.hpp
        src/emulator/log/log.cpp
        src/emulator/IO_Devices/Console.hpp
        src/emulator/IO_Devices/Console.cpp
)
