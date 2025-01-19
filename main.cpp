#include <Arduino.h>
#include <Bounce2.h>
#include <Encoder.h>
#include "View.h"
#include "teensy_controls.h"
#include "scenecontroller.h"
#include "rgb565_colors.h"
#include "MainMenu.h"
#include <MIDI.h>
#include "MidiSpyScene.h"
#ifdef BUILD_FOR_LINUX
#define SDCARD_SS_PIN 0
#include "RtMidiMIDI.h"
#include "RtMidiTransport.h"
MIDI_CREATE_RTMIDI_INSTANCE(RtMidiMIDI, rtMIDI,  MIDI);
using TMidiTransport = RtMidiTransport<RtMidiMIDI>;
using TMidi = midi::MidiInterface<TMidiTransport>;
#else
using TMidiTransport = midi::SerialMIDI<arduino::HardwareSerial>;
using TMidi = midi::MidiInterface<TMidiTransport>;
MIDI_CREATE_DEFAULT_INSTANCE();
#endif

int loopCount = 0;
bool isRecording = false;

using namespace Bounce2;
Button button = Button();
Button button2 = Button();
Button button3 = Button();
Encoder encoderLeftRight(7,18);
Encoder encoderUpDown(4, 15);
#ifdef BUILD_FOR_LINUX
#include "st7735_opengl.h"
#include "st7735_opengl_main.h"
st7735_opengl<Encoder,Button> tft = st7735_opengl(false, 0, &encoderUpDown, &encoderLeftRight, &button, &button2, &button3);
VirtualView mainView(tft, 0,0, 128, 128);
SceneController controller(mainView, encoderUpDown, encoderLeftRight, button, button2,button3, MIDI);
#else
#include <Adafruit_ST7735.h>
#include "st7735view.h"
#define TFT_CS          6
#define TFT_RST         1   // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC          2
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
ST7735 mainView(tft);
VirtualView virtualView(mainView, 0, 0, 128, 128);
SceneController<VirtualView,Encoder,Button, TMidiTransport> controller(virtualView, encoderUpDown, encoderLeftRight, button, button2,button3, MIDI);
#endif

MidiSpyScene midiSpyScene(mainView, SDCARD_SS_PIN, isRecording);

MainScene<TMidiTransport> mainMenu = MainScene<TMidiTransport>(mainView, controller);

const char* menuDescriptions[numMenuItems] = {
    "Change device settings",
    "Lesson plans",
    "Play songs",
    "Record your song",
    "Looping recorder",
    "Silent record",
    "Sleep"};

const String menuLabels[numMenuItems] = {
    "Settings",
    "Theory",
    "Play",
    "Record",
    "Loop",
    "Spy",
    "Sleep"};

#ifdef BUILD_FOR_LINUX
#define SDCARD_SS_PIN 0
#endif

const int chipSelect = SDCARD_SS_PIN;

void setup() {

    Serial.begin(115200);

    button.attach( 3, INPUT_PULLUP ); // USE EXTERNAL PULL-UP
    button2.attach( 16, INPUT_PULLUP ); // USE EXTERNAL PULL-UP
    button3.attach( 12, 12 ); // USE EXTERNAL PULL-UP

    button.interval(55);
    button2.interval(55);
    button3.interval(5);

    button.setPressedState(LOW);
    button2.setPressedState(LOW);
    button3.setPressedState(LOW);

    delay(10);
#ifndef BUILD_FOR_LINUX
    tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
    tft.setRotation(1);
#endif
    tft.fillScreen(RGB565_Black);

    if (!SD.begin(chipSelect)) {
      Serial.println("initialization failed. Things to check:");
      Serial.println("1. is a card inserted?");
      Serial.println("2. is your wiring correct?");
      Serial.println("3. did you change the chipSelect pin to match your shield or module?");
      Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
      tft.println("SD card not detected!!!");
      delay(2111);
    }
    controller.Init();
    controller.AddScene(&mainMenu);
    controller.AddScene(&midiSpyScene);
    controller.SetCurrentSceneIndex(1);
    controller.SetActive(false);

    mainMenu.AddSketch(menuLabels[0], menuDescriptions[0], 1);
    mainMenu.AddSketch(menuLabels[1], menuDescriptions[1], 1);
    mainMenu.AddSketch(menuLabels[2], menuDescriptions[2], 1);
    mainMenu.AddSketch(menuLabels[3], menuDescriptions[3], 1);
    mainMenu.AddSketch(menuLabels[4], menuDescriptions[4], 1);
    mainMenu.AddSketch(menuLabels[5], menuDescriptions[5], 1);
    mainMenu.AddSketch(menuLabels[6], menuDescriptions[6], 1);
    // Connect the handleNoteOn function to the library,
    // so it is called upon reception of a NoteOn.

    midiSpyScene.StartRecording();

    // Initiate MIDI communications, listen to all channels
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();
}


void loop() {
    while (MIDI.read()) ;
    if (isRecording) {
        loopCount += 1;
        if (loopCount % 100 == 0) {
            controller.Process();
            loopCount = 0;
        }
    } else
        controller.Process();
}

#ifdef BUILD_FOR_LINUX
int st7735_main(int, char**) {
    SD.setSDCardFolderPath("/Users/moolet/Development/github/samd21g-midi-tool-software/resources/sd");
    return 0;
}
#endif