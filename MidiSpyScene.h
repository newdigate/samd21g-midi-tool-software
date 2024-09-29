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
        _microseconds(0),
        _lastMicroseconds(0)
    {
    }

    ~MidiSpyScene() override {

    }

    void Update () override {
        unsigned long currentMicros = micros();
        if (currentMicros >= _lastMicroseconds && currentMicros - _lastMicroseconds > _microsPerTick) {
            _currentTicks +=  (currentMicros - _lastMicroseconds) / _microsPerTick;
            _lastMicroseconds = currentMicros;
        } else {
            // overflow
        }
        _microseconds = currentMicros;
    }

    void InitScreen () override {
        _microseconds = micros();
        _lastMicroseconds = _microseconds;
        _currentTicks = 0;
        _lastEventTicks = 0;
        _microsPerTick = get_microseconds_per_tick(120.0);
        mainView.fillScreen(RGB565_Black);
        mainView.setTextWrap(true);
        mainView.drawString("Recording",0,64);
        writer.setFilename("test");
        writer.writeHeader();
    }
    void UninitScreen () override {
    }

    void ButtonPressed(unsigned buttonIndex) override {
    }
    void Rotary1Changed(bool forward) override {
    }
    void Rotary2Changed(bool forward) override {}
    void NoteOn(uint8_t channel, uint8_t pitch, uint8_t velocity) override {
        auto deltaTicks = _currentTicks - _lastEventTicks;
        _lastEventTicks = _currentTicks;
        writer.addNoteOnEvent(deltaTicks, channel, pitch, velocity);
        writer.flush();
    }
    void NoteOff(uint8_t channel, uint8_t pitch, uint8_t velocity) override {
        auto deltaTicks = _currentTicks - _lastEventTicks;
        _lastEventTicks = _currentTicks;
        writer.addNoteOffEvent(deltaTicks, channel, pitch);
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
    unsigned long long _microseconds, _lastMicroseconds, _microsPerTick, _currentTicks, _lastEventTicks;
    SmfWriter writer;
    uint32_t _ticks;
};


#endif //MIDISPYSCENE_H
