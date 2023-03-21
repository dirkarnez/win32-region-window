cmake_minimum_required(VERSION 3.8)
project("winapi-helloworld")


SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -Wl,--subsystem,windows")

add_executable(${PROJECT_NAME} WIN32 
# "src/main.cpp"
# "src/main.v2.cpp"
"src/main.v3.cpp"
# "src/skin.cpp"
# "src/skin.h"
)
target_link_libraries(${PROJECT_NAME} user32 gdi32 dwmapi uxtheme)
target_compile_definitions(${PROJECT_NAME} PRIVATE _UNICODE UNICODE _WIN32_WINNT=0x0603)

