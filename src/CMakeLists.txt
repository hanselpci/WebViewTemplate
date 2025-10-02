cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME example)

add_executable(${TARGET_NAME} WIN32)
target_sources(${TARGET_NAME} PRIVATE main.cpp)

target_link_libraries(${TARGET_NAME} PRIVATE webview::core_static)

if(MSVC)
    # Disable some warnings when using MSVC
    target_compile_definitions(${TARGET_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
