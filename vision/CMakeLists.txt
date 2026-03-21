file(GLOB VISION_SOURCES "*.c" "*.C")

add_library(tina_vision SHARED ${VISION_SOURCES})

target_compile_definitions(tina_vision PRIVATE
    _COMPLEX_DEFINED
    __STRICT_ANSI__
    _PCC
    WIN32)

target_include_directories(tina_vision PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${TINA_INCLUDE_DIR})

target_link_libraries(tina_vision PRIVATE
    tina_math
    tina_sys)
