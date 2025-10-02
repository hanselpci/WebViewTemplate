cmake_minimum_required(VERSION 3.16)

add_executable(${PROJECT_NAME} WIN32)
target_sources(${PROJECT_NAME} PRIVATE main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE webview::core_static)

if(MSVC)
    # Disable some warnings when using MSVC
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
