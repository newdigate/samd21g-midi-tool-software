#include <Arduino.h>
#include <Bounce2.h>
#include <Encoder.h>
#include "View.h"
#include "teensy_controls.h"
#include "scenecontroller.h"
#include "icons.h"
#include "rgb565_colors.h"
#include "MainMenu.h"

#include <MIDI.h>

#include "MidiSpyScene.h"
#ifdef BUILD_FOR_LINUX
#include "RtMidiMIDI.h"
#include "RtMidiTransport.h"
MIDI_CREATE_RTMIDI_INSTANCE(RtMidiMIDI, rtMIDI,  MIDI);
using TMidi = RtMidiMIDI;
#else
MIDI_CREATE_DEFAULT_INSTANCE();
#endif

using namespace Bounce2;
Button button = Button();
Button button2 = Button();
Button button3 = Button();
Encoder encoderLeftRight(7,10);
Encoder encoderUpDown(4, 15);
#ifdef BUILD_FOR_LINUX
#include "st7735_opengl.h"
#include "st7735_opengl_main.h"
st7735_opengl<Encoder,Button> tft = st7735_opengl(false, 0, &encoderUpDown, &encoderLeftRight, &button, &button2, &button3);
VirtualView mainView(tft, 0,0, 128, 128);
#else
#include <Adafruit_ST7735.h>
#include "st7735view.h"
#define TFT_CS          6
#define TFT_RST         1   // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC          2
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
SceneController<Adafruit_ST7735,Encoder,Button> controller(tft, encoderUpDown, encoderLeftRight, button, button2,button3);
ST7735 mainView(tft);
#endif



SceneController controller(mainView, encoderUpDown, encoderLeftRight, button, button2,button3, MIDI);

MidiSpyScene midiSpyScene(mainView);
TeensyControl midiSpy(mainView, [] (){ midiSpy.fillScreen(RGB565_African_violet); }, 128, 128, 0, 0);

MainScene mainMenu = MainScene(mainView, controller);

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


void sendMessage(byte channel, midi::MidiType type, byte data1, byte data2){
    midi::Message<128U> m;
    m.channel = channel;
    m.type = type;
    m.data1 = data1;
    m.data2 = data2;
    m.valid = true;
    m.length = 3;
    MIDI.send(m);
}

void setup() {

    Serial.begin(9600);

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

    controller.AddScene(&mainMenu);
    controller.SetCurrentSceneIndex(0);
    controller.SetActive(false);

    mainMenu.AddSketch(menuLabels[0], menuDescriptions[0], &midiSpy);
    mainMenu.AddSketch(menuLabels[1], menuDescriptions[1], &midiSpy);
    mainMenu.AddSketch(menuLabels[2], menuDescriptions[2], &midiSpy);
    mainMenu.AddSketch(menuLabels[3], menuDescriptions[3], &midiSpy);
    mainMenu.AddSketch(menuLabels[4], menuDescriptions[4], &midiSpy);
    mainMenu.AddSketch(menuLabels[5], menuDescriptions[5], &midiSpy);
    mainMenu.AddSketch(menuLabels[6], menuDescriptions[6], &midiSpy);
    // Connect the handleNoteOn function to the library,
    // so it is called upon reception of a NoteOn.

    // Initiate MIDI communications, listen to all channels
    MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
    controller.Process();
    MIDI.read();
}

int st7735_main(int, char**) {
    return 0;
}
