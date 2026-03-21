cmake_minimum_required(VERSION 3.16)

project(tina-pc C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# External headers (must point to the installed TINA headers)
set(TINA_INCLUDE_DIR "" CACHE PATH "Path to TINA public headers")

add_subdirectory(math)
add_subdirectory(sys)
add_subdirectory(vision)
add_subdirectory(file)
add_subdirectory(serialise)
