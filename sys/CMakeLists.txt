file(GLOB SYS_SOURCES "*.c" "*.C")

add_library(tina_sys SHARED ${SYS_SOURCES})

target_compile_definitions(tina_sys PRIVATE
    _COMPLEX_DEFINED
    __STRICT_ANSI__
    _PCC
    WIN32)

target_include_directories(tina_sys PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${TINA_INCLUDE_DIR})
