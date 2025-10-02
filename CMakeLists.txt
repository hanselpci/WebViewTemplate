cmake_minimum_required(VERSION 3.16)
project(template LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# show compiler information
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C compiler: ${CMAKE_C_COMPILER}")

include(FetchContent)
# Do not build webview as a shared library
set(WEBVIEW_BUILD_SHARED_LIBRARY OFF)

FetchContent_Declare(
    webview
    GIT_REPOSITORY https://github.com/webview/webview
    GIT_TAG 0.12.0
)
FetchContent_MakeAvailable(webview)

add_subdirectory(src)

# Copy HTML file to build directory
file(COPY ${PROJECT_SOURCE_DIR}/web DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})

# Enable console window on Windows if building in Debug mode
# Remove console window on Windows if building in Release mode
if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
        LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    )
endif()

