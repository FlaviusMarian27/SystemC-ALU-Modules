cmake_minimum_required(VERSION 3.10)
project(ALU)

set(CMAKE_CXX_STANDARD 17)

# Setează manual unde e SystemC (în funcție de ce ai tu pe PC)
# Presupunem că ai instalat în C:/systemc-install
include_directories("C:/systemc-install/include")
link_directories("C:/systemc-install/lib")

# Executabil
add_executable(main
    main.cpp
)

# Link la biblioteca systemc (static)
target_link_libraries(main systemc)
