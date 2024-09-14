cmake_minimum_required(VERSION 3.15)

project(
        samd21g_midi_tool_software
        VERSION 1.0
        LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)
include(FetchContent)
FetchContent_Declare(cmake_declare_and_fetch
        GIT_REPOSITORY https://github.com/newdigate/cmake-declare-and-fetch.git
        GIT_TAG        main
)
FetchContent_MakeAvailable(cmake_declare_and_fetch)
include("${FETCHCONTENT_BASE_DIR}/cmake_declare_and_fetch-src/DeclareAndFetchCMake.in")

set(BUILD_SHARED_LIBRARY ON)
set(REDIRECT_SERIAL_OUT_TO_STD_OUT OFF)

DeclareAndFetch(teensy_x86_stubs            https://github.com/newdigate/teensy-x86-stubs.git feature/shared_serial src)
DeclareAndFetch(teensy_gfx                  https://github.com/newdigate/teensy-gfx.git main src)
DeclareAndFetch(teensy_x86_encoder_stubs    https://github.com/newdigate/teensy-x86-encoder-stubs.git noinstall src)
DeclareAndFetch(teensy_x86_bounce2_stubs    https://github.com/newdigate/teensy-x86-bounce2-stubs.git noinstall src)
DeclareAndFetch(teensy_gfx_controls         https://github.com/newdigate/teensy-gfx-controls.git noinstall src)
DeclareAndFetch(rgb565_colors               https://github.com/newdigate/rgb565_colors.git noinstall src)
DeclareAndFetch(teensy_st7735_linux_stubs   https://github.com/newdigate/teensy-st7735-linux-stubs.git noinstall "src;extras/opengl/src")

include("${FETCHCONTENT_BASE_DIR}/teensy_st7735_linux_stubs-src/extras/opengl/opengl.cmake.in")

# Adding something we can run - Output name matches target name
add_executable(MyExample main.cpp)

# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.
target_link_libraries(MyExample teensy_x86_stubs teensy_gfx teensy_gfx_controls teensy_x86_bounce2_stubs)
target_link_libraries(MyExample ${teensy_st7735_linux_stubs_LIBS})
target_link_libraries(MyExample ${teensy_st7735_linux_extras_opengl_LIBS})
target_link_libraries(MyExample ${LIBS})