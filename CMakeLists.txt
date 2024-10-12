cmake_minimum_required(VERSION 3.15)

project(
        samd21g_midi_tool_software
        VERSION 1.0
        LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)
include(cmake_declare_and_fetch.cmake.in)

option(BUILD_FOR_LINUX "x86 build" ON)
if (BUILD_FOR_LINUX)
    add_compile_definitions(-DBUILD_FOR_LINUX)
    set(BUILD_SHARED_LIBRARY ON)
    set(REDIRECT_SERIAL_OUT_TO_STD_OUT OFF)

    DeclareAndFetch(teensy_x86_stubs            git@github.com:newdigate/teensy-x86-stubs.git noinstall src)
    DeclareAndFetch(teensy_x86_sd_stubs         git@github.com:newdigate/teensy-x86-sd-stubs.git noinstall src)
    DeclareAndFetch(teensy_gfx                  git@github.com:newdigate/teensy-gfx.git noinstall src)
    DeclareAndFetch(teensy_x86_encoder_stubs    git@github.com:newdigate/teensy-x86-encoder-stubs.git noinstall src)
    DeclareAndFetch(teensy_x86_bounce2_stubs    git@github.com:newdigate/teensy-x86-bounce2-stubs.git noinstall src)
    DeclareAndFetch(teensy_gfx_controls         git@github.com:newdigate/teensy-gfx-controls.git noinstall src)
    DeclareAndFetch(rgb565_colors               git@github.com:newdigate/rgb565_colors.git noinstall src)
    DeclareAndFetch(rtmidi                      https://github.com/thestk/rtmidi.git master "/")
    DeclareAndFetch(teensy_x86_midi_stubs       git@github.com:newdigate/teensy-x86-midi-stubs noinstall src)
        DeclareAndFetchSubLibrary(teensy_x86_midi_stubs     extras/rtmidi/src)
    DeclareAndFetch(teensy_st7735_linux_stubs   git@github.com:newdigate/teensy-st7735-linux-stubs.git noinstall src)
        DeclareAndFetchSubLibrary(teensy_st7735_linux_stubs   extras/opengl/src)
    include("${FETCHCONTENT_BASE_DIR}/teensy_st7735_linux_stubs-src/extras/opengl/opengl.cmake.in")

    DeclareAndFetch(midi-smf-writer             git@github.com:newdigate/midi-smf-writer.git noinstall src)

endif()

add_executable(MyExample main.cpp icons.cpp MainMenu.cpp
        MidiSpyScene.cpp
        MidiSpyScene.h)
target_link_libraries(MyExample teensy_x86_stubs teensy_gfx teensy_gfx_controls teensy_x86_bounce2_stubs teensy_st7735_linux_stubs teensy_x86_sd_stubs midi_smf_writer teensy_st7735_linux_opengl)
if (BUILD_FOR_LINUX)
    target_link_libraries(MyExample ${teensy_st7735_linux_extras_opengl_LIBS})
    target_link_libraries(MyExample ${LIBS})
    target_link_libraries(MyExample rtmidi)
endif()
