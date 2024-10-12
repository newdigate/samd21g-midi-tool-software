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
    MidiSpyScene(View &mainView, int sdChipSelect) : BaseScene(mainView, 128, 128, 0, 0, _bmp_settings_on, _bmp_settings_off, 16, 16),
        mainView(mainView),
        _microseconds(0),
        _lastMicroseconds(0),
        _sdChipSelect(sdChipSelect)
    {
    }

    ~MidiSpyScene() override {

    }

    void Update () override {
        if (_sdConnected) {
            if (_isRecording) {
                unsigned long currentMicros = micros();
                if (_lastMicroseconds == 0)
                    _lastMicroseconds = currentMicros;
                else if (currentMicros - _lastMicroseconds > _microsPerTick) {
                    _currentTicks += (currentMicros - _lastMicroseconds) / _microsPerTick;
                    _lastMicroseconds = currentMicros;
                    //Serial.printf("ticks %d", _currentTicks);
                }

                _microseconds = currentMicros;
                bool writerError = writer.isError();
                int errorNumber = writerError ? writer.getErrorNumber() : 0;
                if (writerError != _hasError || errorNumber != _lastErrorNumber) {
                    _hasError = writerError;
                    _lastErrorNumber = errorNumber;
                    fillScreen(RGB565_Red);
                    drawString("write error", 1, 1);
                    drawNumber(_lastErrorNumber, 1, 11);
                }
            }
        } else {
            int sdConnected = SD.begin(_sdChipSelect);
            if (sdConnected != _sdConnected) {
                _sdConnected = sdConnected;
                if (_sdConnected)
                   fillScreen(RGB565_Black);
                else {
                    fillScreen(RGB565_Red);
                    drawString("uSD card not connected", 1, 1);
                }
            }
        }
    }

    void InitScreen () override {
        _microseconds = micros();
        _lastMicroseconds = 0;
        _currentTicks = 0;
        _lastEventTicks = 0;
        _microsPerTick = get_microseconds_per_tick(120.0);
        _sdConnected = SD.begin(_sdChipSelect);
        if (!_sdConnected) {
            drawString("uSD card not connected", 1, 1);
        } else {
            mainView.fillScreen(RGB565_Black);
            mainView.setTextWrap(true);
            mainView.drawString("Ready", 0, 64);
        }
    }
    void UninitScreen () override {
    }

    void ButtonPressed(unsigned buttonIndex) override {
        if (!_isRecording)
            StartRecording();
        else
            StopRecording();
    }
    void Rotary1Changed(bool forward) override {
    }
    void Rotary2Changed(bool forward) override {}
    void NoteOn(uint8_t channel, uint8_t pitch, uint8_t velocity) override {
        auto deltaTicks = _currentTicks - _lastEventTicks;
        _lastEventTicks = _currentTicks;
        writer.addNoteOnEvent(deltaTicks, channel, pitch, velocity);
    }
    void NoteOff(uint8_t channel, uint8_t pitch, uint8_t velocity) override {
        auto deltaTicks = _currentTicks - _lastEventTicks;
        _lastEventTicks = _currentTicks;
        writer.addNoteOffEvent(deltaTicks, channel, pitch);
    }
    void ControlChange(uint8_t channel, uint8_t data1, uint8_t data2) override {
        auto deltaTicks = _currentTicks - _lastEventTicks;
        _lastEventTicks = _currentTicks;
        writer.addControlChange(deltaTicks, data1, data2, channel);
    }

    unsigned int get_microseconds_per_tick(double beats_per_minute) {
        double micros_per_beat = 60000000.0 / beats_per_minute;
        unsigned int micros_per_tick = micros_per_beat / 480;
        return micros_per_tick;
    }

    void StartRecording() {
        _isRecording = true;
        mainView.fillScreen(RGB565_Black);
        mainView.setTextWrap(true);
        mainView.drawString("Recording",0,64);
        writer.setFilename("test");
        writer.writeHeader();
        mainView.drawString(writer.getFilename(),0,74);
        _microseconds = micros();
        _lastMicroseconds = 0;
        _currentTicks = 0;
        _lastEventTicks = 0;
    }

    void StopRecording() {
        mainView.fillScreen(RGB565_Black);
        mainView.drawString("Ready",0,64);
        writer.addEndofTrack(0,0);
        writer.close();
        _isRecording = false;
    }

private:
    View &mainView;
    unsigned long long _microseconds, _lastMicroseconds, _microsPerTick, _currentTicks, _lastEventTicks;
    SmfWriter writer;
    bool _sdConnected = false, _hasError = false, _isRecording = false;
    int _sdChipSelect, _lastErrorNumber = 0;
};


#endif //MIDISPYSCENE_H
