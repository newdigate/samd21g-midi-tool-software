//
// Created by Moolet on 22/09/2024.
//

#ifndef MIDISPYSCENE_H
#define MIDISPYSCENE_H
#include "icons.h"
#include "rgb565_colors.h"
#include "scenecontroller.h"
#include <SD.h>
#include "buttons.h"
#include "smfwriter.h"
#include "seven_segment.h"
#include "DeltaTimeSequencer.h"

class MediaPosition {
public:
    [[nodiscard]] unsigned GetMilliseconds() const {
        return _milliseconds;
    }

    void SetMilliseconds(unsigned milliseconds) {
        _milliseconds = milliseconds;
    }

protected:
    unsigned _milliseconds = 0;
};

enum MediaButtonType {
    None,
    Stop,
    Play,
    Pause,
    Record,
    Fastfwd
};
class MediaButtonBarMenuItem : public TeensyMenuItem {
public:
    explicit MediaButtonBarMenuItem(TeensyMenu &menu, std::function<void(MediaButtonType)> buttonPressedCallback, bool &isRecording) :
        TeensyMenuItem (menu, nullptr, 16, nullptr, nullptr, nullptr, nullptr),
        _button_bar(*this, 128, 16, 0, 0, isRecording),
        _buttonPressedCallback(buttonPressedCallback)
    {
    }

    ~MediaButtonBarMenuItem() override = default;

    void Initialize() {
        _button_bar.Init();
        _children.push_back(&_button_bar);
    }
    void ButtonDown(const unsigned char buttonNumber) override {
        _button_bar.ButtonDown(buttonNumber);
        int selectedButton =_button_bar.GetSelectedIndex();
        MediaButtonType buttonType;
        switch (selectedButton) {
            case 1: buttonType = MediaButtonType::Stop; break;
            case 2: buttonType = MediaButtonType::Play; break;
            case 3: buttonType = MediaButtonType::Fastfwd; break;
            default: buttonType = MediaButtonType::None; break;
        }
        _buttonPressedCallback(buttonType);
    }
    void ValueScroll(const bool forward) override {
        _button_bar.IndexScroll(forward);
    }
    void IndexScroll(const bool forward) override {
        _button_bar.ValueScroll(forward);
    }

protected:
    TeensyMediaButtonBar _button_bar;
    std::function<void(MediaButtonType)> _buttonPressedCallback;

};

class MidiSpyScene : public BaseScene {
public:
    MidiSpyScene(View &mainView, int sdChipSelect, bool &isRecording) : BaseScene(mainView, 128, 128, 0, 0, _bmp_settings_on,
                                                               _bmp_settings_off, 16, 16),
                                                     mainView(mainView),
                                                     _media_position(),
                                                     _menu(mainView, 128, 128, 0, 0, 0x092D /*Sapphire*/, 0),
                                                     _mediaButtonBarMenuItem(
                                                         new MediaButtonBarMenuItem(_menu, [&] (MediaButtonType buttonType) {
                                                             MediaButtonPressed(buttonType);
                                                         }, isRecording)
                                                     ),
                                                     _timeIndicator(new TeensyTimeIndicator(_menu, 128, 16, 0, 0)),
                                                     _filenameMenuItem(new TeensyCharMenuItem(_menu, nullptr, [] (uint8_t buttonNumber) -> void {} )),
                                                    _statusMenuItem(new TeensyCharMenuItem(_menu, nullptr, [] (uint8_t buttonNumber) -> void {} )),
                                                     sceneMenuItems {
                                                         _mediaButtonBarMenuItem,
                                                         _timeIndicator,
                                                         _statusMenuItem,
                                                         _filenameMenuItem
                                                     },
                                                     _lastUIUpdate(0),
                                                    _deltaTimeSequencer(_tempo, _microsPerTick, true),
                                                     _microsPerTick(_deltaTimeSequencer.getMicrosPerTick()),
                                                     _sdChipSelect(sdChipSelect),
                                                     _isRecording(isRecording)
                                                     {
        _menu.AddControl(sceneMenuItems[0]);
        _menu.AddControl(sceneMenuItems[1]);
        _menu.AddControl(sceneMenuItems[2]);
        _menu.AddControl(sceneMenuItems[3]);
    }

    ~MidiSpyScene() override {

    }

    void Update (unsigned milliseconds) override {
        if (_sdConnected) {
            //_button_bar.Update(milliseconds);
            if (_isRecording) {
                unsigned long currentMicros = micros();

                if (currentMicros - _lastUIUpdate > 100000 ) {
                    _lastUIUpdate = currentMicros;

                    _media_position.SetMilliseconds( _deltaTimeSequencer.getMicroseconds(currentMicros));
                    _timeIndicator->SetTime(_media_position.GetMilliseconds());

                    TeensyControl::Update(milliseconds);
                    _menu.Update(milliseconds);

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
            } else
            {
                TeensyControl::Update(milliseconds);
                _menu.Update(milliseconds);
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
        _timeIndicator->Init();
        _lastUIUpdate = micros();
        _deltaTimeSequencer.stop();
        _sdConnected = SD.begin(_sdChipSelect);
        _mediaButtonBarMenuItem->Initialize();
        ForceRedraw();
        _menu.ForceRedraw();
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
        _menu.ButtonDown(buttonIndex);
        //_button_bar.ButtonDown(buttonIndex);
/*        if (!_isRecording)
            StartRecording();
        else
            StopRecording();
            */
    }
    void IndexScroll(const bool forward) override {
        _menu.IndexScroll(forward);
    }
    void ValueScroll(const bool forward) override {
       _menu.ValueScroll(forward);
    }


    void NoteOn(uint8_t channel, uint8_t pitch, uint8_t velocity) override {
        if (_isRecording) {
            const auto deltaTicks = _deltaTimeSequencer.get_delta(micros());
/*
            Serial.print("ON pitch: ");
            Serial.print(pitch);
            Serial.print(" channel: ");
            Serial.print(channel);
            Serial.print(" velocity: ");
            Serial.print(velocity);
            Serial.print(" delta: ");
            Serial.println((unsigned long)deltaTicks);
*/
            writer.addNoteOnEvent(deltaTicks, channel, pitch, velocity);
        }
    }
    void NoteOff(uint8_t channel, uint8_t pitch, uint8_t velocity) override {
        if (_isRecording) {
            const auto deltaTicks = _deltaTimeSequencer.get_delta(micros());/*
            Serial.print("OFF pitch: ");
            Serial.print(pitch);
            Serial.print(" channel: ");
            Serial.print(channel);
            Serial.print(" velocity: ");
            Serial.print(velocity);
            Serial.print(" delta: ");
            Serial.println((unsigned long)deltaTicks);
*/
            writer.addNoteOffEvent(deltaTicks, channel, pitch);
        }
    }
    void ControlChange(uint8_t channel, uint8_t data1, uint8_t data2) override {
        if (_isRecording) {
            const auto deltaTicks = _deltaTimeSequencer.get_delta(micros());
            /*
            Serial.print("CC data1: ");
            Serial.print(data1);
            Serial.print(" data2: ");
            Serial.print(data2);
            Serial.print(" channel: ");
            Serial.print(channel);
            Serial.print(" delta: ");
            Serial.println((unsigned long)deltaTicks);
            */
            writer.addControlChange(deltaTicks, data1, data2, channel);
        }
    }

    void StartRecording() {
        _isRecording = true;
        writer.setFilename(_filename);
        _filenameMenuItem->SetString(writer.getFilename());
        _statusMenuItem->SetString("Recording");
        writer.writeHeader();
        writer.addSetTempo(0, _tempo);
        _lastUIUpdate = micros();
        _deltaTimeSequencer.start(micros());
        _menu.ForceRedraw();
    }

    void StopRecording() {
        writer.addEndofTrack(0,0);
        writer.close();
        _statusMenuItem->SetString("Ready");
        _isRecording = false;
        _menu.ForceRedraw();
    }

    void MediaButtonPressed(const MediaButtonType buttonType) {
        switch (buttonType) {
            case MediaButtonType::None: break;
            default: {
                if (!_isRecording)
                    StartRecording();
                else
                    StopRecording();
                break;
            };
        }
    }

private:
    View &mainView;
    TeensyMenu _menu;
    MediaPosition _media_position;
    MediaButtonBarMenuItem *_mediaButtonBarMenuItem;
    TeensyTimeIndicator *_timeIndicator;
    TeensyCharMenuItem *_filenameMenuItem;
    TeensyCharMenuItem *_statusMenuItem;
    TeensyControl *sceneMenuItems[4];
    unsigned long long _lastUIUpdate, _microsPerTick;
    DeltaTimeSequencer _deltaTimeSequencer;
    SmfWriter writer;
    bool _sdConnected = false, _hasError = false, &_isRecording;
    int _sdChipSelect, _lastErrorNumber = 0;
    double _tempo = 120.0;
    char _filename[4] { 't','e','s','t' };
};


#endif //MIDISPYSCENE_H
