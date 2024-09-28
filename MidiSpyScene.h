//
// Created by Moolet on 22/09/2024.
//

#ifndef MIDISPYSCENE_H
#define MIDISPYSCENE_H
#include "icons.h"
#include "rgb565_colors.h"
#include "scenecontroller.h"
#include <SD.h>

#include "smfwriter.h"

class MidiSpyScene : public BaseScene {
public:
    MidiSpyScene(View &mainView) : BaseScene(mainView, 128, 128, 0, 0, _bmp_settings_on, _bmp_settings_off, 16, 16),
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
        writer.setFilename("test.mid");
        writer.writeHeader();
    }
    void UninitScreen () override {}

    void ButtonPressed(unsigned buttonIndex) override {
    }
    void Rotary1Changed(bool forward) override {
    }
    void Rotary2Changed(bool forward) override {}
    void NoteOn(uint8_t channel, uint8_t pitch, uint8_t velocity) override {
        writer.addNoteOnEvent(0, channel, pitch, velocity);
        writer.flush();
    }
    void NoteOff(uint8_t channel, uint8_t pitch, uint8_t velocity) override {
        writer.addNoteOffEvent(0, channel, pitch);
        writer.flush();
    }
    void ControlChange(uint8_t channel, uint8_t data1, uint8_t data2) override {
        writer.addControlChange(480, data1, data2, channel);
        writer.flush();
    }

    unsigned int get_microseconds_per_tick(double beats_per_minute) {
        double micros_per_beat = 60000000.0 / beats_per_minute;
        unsigned int micros_per_tick = micros_per_beat / 480;
        return micros_per_tick;
    }

private:
    View &mainView;
    unsigned long long _milliseconds, _lastMilliseconds;
    SmfWriter writer;
};


#endif //MIDISPYSCENE_H
