file(GLOB MATH_SOURCES "*.c" "*.C")

add_library(tina_math SHARED ${MATH_SOURCES})

target_compile_definitions(tina_math PRIVATE
    _COMPLEX_DEFINED
    __STRICT_ANSI__
    _PCC
    WIN32)

target_include_directories(tina_math PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${TINA_INCLUDE_DIR})
