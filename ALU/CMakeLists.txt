cmake_minimum_required(VERSION 3.10)
project(ALU_Modules)

set(CMAKE_CXX_STANDARD 17)

# Include path către SystemC
include_directories("C:/systemc-install/include")
link_directories("C:/systemc-install/lib")

# Executabilul și fișierele sursă
add_executable(main
    main.cpp
    rca32.h
    Subtractor32.h
    booth_multiplier.h
    shift_unit.h
)

# Link cu SystemC
target_link_libraries(main systemc)
