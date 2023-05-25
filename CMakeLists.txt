# Use a recent version of CMake
cmake_minimum_required(VERSION 3.12)
# Name your project
project(index)

set(CMAKE_CXX_STANDARD 14)
# Add your source files
add_executable(index
    components/element/Element.cpp
    components/button/Button.cpp
    components/flex/Flex.cpp
    components/input/Input.cpp
    components/state/State.cpp
    components/style/Style.cpp
    apiClient/apiClient.cpp
    apiClient/queryParam.cpp
    pages/loginPage/LoginPage.cpp
    pages/mainPage/MainPage.cpp
    pages/page/Page.cpp
    index.cpp
)
# Link the Emscripten bindings library
target_link_libraries(index
    "--bind -s FETCH=1 -O3 -sASYNCIFY"
)

