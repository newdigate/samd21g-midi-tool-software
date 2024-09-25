//
// Created by Moolet on 22/09/2024.
//

#ifndef MIDISPYSCENE_H
#define MIDISPYSCENE_H
#include "icons.h"
#include "rgb565_colors.h"
#include "scenecontroller.h"
#include <MIDI.h>

class MidiSpyScene : public BaseScene {
public:
    MidiSpyScene(View &mainView) : BaseScene(_bmp_settings_on, _bmp_settings_off, 16, 16),
        mainView(mainView),
        _milliseconds(0),
        _lastMilliseconds(0)
    {
    }

    ~MidiSpyScene() override {

    }

    void Update () override {
    }

    void InitScreen () override {
        _milliseconds = millis();
        mainView.fillScreen(RGB565_Blue);
        mainView.setTextWrap(true);
        mainView.drawString("Recording",0,64);
    }
    void UninitScreen () override {}

    void ButtonPressed(unsigned buttonIndex) override {
    }
    void Rotary1Changed(bool forward) override {
    }
    void Rotary2Changed(bool forward) override {}
    bool HandleNoteOnOff(bool noteDown, uint8_t channel, uint8_t pitch, uint8_t velocity) override { return false; }
    bool HandleControlChange(uint8_t channel, uint8_t data1, uint8_t data2) override { return false; }

private:
    View &mainView;
    unsigned long long _milliseconds, _lastMilliseconds;
};


#endif //MIDISPYSCENE_H
