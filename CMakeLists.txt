cmake_minimum_required(VERSION 3.15)

project(
        samd21g_midi_tool_software
        VERSION 1.0
        LANGUAGES C CXX)

set (CMAKE_CXX_STANDARD 17)

#option(BUILD_FOR_LINUX "x86 build" ON)
if (BUILD_FOR_LINUX)
    include(cmake_declare_and_fetch.cmake.in)
    add_compile_definitions(-DBUILD_FOR_LINUX)

    DeclareAndFetch(teensy_x86_stubs            https://github.com/newdigate/teensy-x86-stubs.git main src)
    DeclareAndFetch(teensy_x86_sd_stubs         https://github.com/newdigate/teensy-x86-sd-stubs.git noinstall src)
    DeclareAndFetch(teensy_gfx                  https://github.com/newdigate/teensy-gfx.git main src)
    DeclareAndFetch(teensy_x86_encoder_stubs    https://github.com/newdigate/teensy-x86-encoder-stubs.git noinstall src)
    DeclareAndFetch(teensy_x86_bounce2_stubs    https://github.com/newdigate/teensy-x86-bounce2-stubs.git noinstall src)
    DeclareAndFetch(teensy_gfx_controls         https://github.com/newdigate/teensy-gfx-controls.git main src)
    DeclareAndFetch(rgb565_colors               https://github.com/newdigate/rgb565_colors.git noinstall src)
    DeclareAndFetch(rtmidi                      https://github.com/thestk/rtmidi.git master "/")
    DeclareAndFetch(teensy_x86_midi_stubs       https://github.com/newdigate/teensy-x86-midi-stubs.git noinstall "" src extras/rtmidi/src)
   #     DeclareAndFetchSubLibrary(teensy_x86_midi_stubs     )
    DeclareAndFetch(teensy_st7735_linux_stubs   https://github.com/newdigate/teensy-st7735-linux-stubs.git noinstall "" src extras/opengl/src)
    #    DeclareAndFetchSubLibrary(teensy_st7735_linux_stubs   )
    include("${FETCHCONTENT_BASE_DIR}/teensy_st7735_linux_stubs-src/extras/opengl/opengl.cmake.in")

    DeclareAndFetch(midi-smf-writer             https://github.com/newdigate/midi-smf-writer.git noinstall src)

    add_executable(MyExample main.cpp icons.cpp MainMenu.cpp
            MidiSpyScene.cpp
            MidiSpyScene.h)
    #add_compile_options(-fno-rtti)

    target_link_libraries(MyExample teensy_x86_stubs teensy_gfx teensy_gfx_controls teensy_x86_bounce2_stubs teensy_st7735_linux_stubs teensy_x86_sd_stubs midi_smf_writer teensy_st7735_linux_opengl)
    if (BUILD_FOR_LINUX)
        target_link_libraries(MyExample ${teensy_st7735_linux_extras_opengl_LIBS})
        target_link_libraries(MyExample ${LIBS})
        target_link_libraries(MyExample rtmidi)
    endif()

else ()
    set(CMAKE_EXE_LINKER_FLAGS "--specs=nano.specs" CACHE INTERNAL "")

    include(FetchContent)
    FetchContent_Declare(teensy_cmake_macros
            GIT_REPOSITORY https://github.com/newdigate/teensy-cmake-macros
            GIT_TAG        main
    )
    FetchContent_MakeAvailable(teensy_cmake_macros)
    include(${teensy_cmake_macros_SOURCE_DIR}/CMakeLists.include.txt)

    import_arduino_library(cores ${teensy_cores_SOURCE_DIR}/teensy4 avr util)

    import_arduino_library_git(SPI https://github.com/PaulStoffregen/SPI.git master "")
    import_arduino_library_git(SdFat https://github.com/PaulStoffregen/SdFat.git master "src" common DigitalIO ExFatLib FatLib FsLib iostream SdCard SpiDriver)
    import_arduino_library_git(SD https://github.com/PaulStoffregen/SD.git Juse_Use_SdFat src)
    import_arduino_library_git(Encoder https://github.com/PaulStoffregen/Encoder.git master "")
    import_arduino_library_git(Bounce2 https://github.com/PaulStoffregen/Bounce2.git master src)
    import_arduino_library_git(SerialFlash https://github.com/PaulStoffregen/SerialFlash.git master "" util)
    import_arduino_library_git(Wire https://github.com/PaulStoffregen/Wire.git master "" utility)
    import_arduino_library_git(arm_math https://github.com/PaulStoffregen/arm_math.git master src)
    import_arduino_library_git(adafruit_busio https://github.com/adafruit/Adafruit_BusIO master "")
    import_arduino_library_git(adafruit_gfx https://github.com/adafruit/Adafruit-GFX-Library.git master "")
    import_arduino_library_git(adafruit_st77xx https://github.com/adafruit/Adafruit-ST7735-Library.git master "")
    import_arduino_library_git(TeensyGFX https://github.com/newdigate/teensy-gfx.git main src)
    import_arduino_library_git(TeensyGFXControls https://github.com/newdigate/teensy-gfx-controls.git main src)
    import_arduino_library_git(rgb565_colors https://github.com/newdigate/rgb565_colors.git noinstall src)
    import_arduino_library_git(MIDI https://github.com/PaulStoffregen/MIDI master src)
    import_arduino_library_git(midi-smf-writer https://github.com/newdigate/midi-smf-writer noinstall src)

    teensy_add_executable(MyExample main.cpp icons.cpp MainMenu.cpp MidiSpyScene.cpp)
    teensy_target_link_libraries(MyExample adafruit_st77xx adafruit_busio adafruit_gfx  Encoder Bounce2 SerialFlash Wire arm_math TeensyGFX TeensyGFXControls MIDI midi-smf-writer SD SdFat SPI cores)
    target_link_libraries(MyExample.elf stdc++)
endif()


