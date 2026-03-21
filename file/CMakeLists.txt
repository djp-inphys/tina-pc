file(GLOB FILE_SOURCES "*.c" "*.C")

add_library(tina_file SHARED ${FILE_SOURCES})

target_compile_definitions(tina_file PRIVATE
    _COMPLEX_DEFINED
    __STRICT_ANSI__
    _PCC
    WIN32)

target_include_directories(tina_file PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${TINA_INCLUDE_DIR})

target_link_libraries(tina_file PRIVATE
    tina_vision
    tina_math
    tina_sys)
