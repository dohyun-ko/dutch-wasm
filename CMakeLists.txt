cmake_minimum_required(VERSION 3.12)
include(FetchContent)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.10.5
)
FetchContent_MakeAvailable(json)

project(index)

set(CMAKE_CXX_STANDARD 14)

add_executable(index
    src/core/user/user.cpp
    src/core/dutch/dutch.cpp
    src/components/element/Element.cpp
    src/components/button/Button.cpp
    src/components/flex/Flex.cpp
    src/components/input/Input.cpp
    src/components/radio/Radio.cpp
    src/components/state/State.cpp
    src/components/style/Style.cpp
    src/components/text/Text.cpp
    src/globalState/userState/userState.cpp
    src/globalState/sendDutchState/sendDutchState.cpp
    src/globalState/receiveDutchState/receiveDutchState.cpp
    src/router/router.cpp
    src/pages/loginPage/loginPage.cpp
    src/pages/signUpPage/signUpPage.cpp
    src/pages/mainPage/mainPage.cpp
    src/pages/receivePage/receivePage.cpp
    src/pages/receiveDetailPage/receiveDetailPage.cpp
    src/pages/sendPage/sendPage.cpp
    src/pages/sendDetailPage/sendDetailPage.cpp
    src/pages/makeDutchPage/makeDutchPage.cpp
    src/index.cpp
)
# Link the Emscripten bindings library
target_link_libraries(index
    PRIVATE nlohmann_json::nlohmann_json
    "--bind --emrun -lembind -fexceptions -s FETCH=1 -O3 -sASYNCIFY"
)

target_compile_options(index
    PRIVATE
    -fexceptions
)

