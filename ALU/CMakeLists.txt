cmake_minimum_required(VERSION 3.10)
project(SystemC_ALU_Modules)

# Set standard
set(CMAKE_CXX_STANDARD 11)

# Include SystemC headers and link lib
include_directories("C:/systemc-install/include")
link_directories("C:/systemc-install/lib")

# Add executable
add_executable(main 
    ALU/main.cpp
)

# Link SystemC
target_link_libraries(main systemc)
