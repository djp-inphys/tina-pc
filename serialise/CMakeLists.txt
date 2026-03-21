file(GLOB SERIALISE_SOURCES "*.c" "*.C")

add_library(tina_serialise SHARED ${SERIALISE_SOURCES})

target_compile_definitions(tina_serialise PRIVATE
    _COMPLEX_DEFINED
    __STRICT_ANSI__
    _PCC
    WIN32)

target_include_directories(tina_serialise PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${TINA_INCLUDE_DIR})
