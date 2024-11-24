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
    explicit MediaButtonBarMenuItem(TeensyMenu &menu, std::function<void(MediaButtonType)> buttonPressedCallback) :
        TeensyMenuItem (menu, nullptr, 16, nullptr, nullptr, nullptr, nullptr),
        _button_bar(*this, 128, 16, 0, 0),
        _buttonPressedCallback(buttonPressedCallback)
    {
    }

    ~MediaButtonBarMenuItem() override = default;

    void Initialize() {
        _button_bar.Init();
    }
    void Update(const unsigned millis) override {
        _button_bar.Update(millis);
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

    void ForceRedraw() override {
        _button_bar.ForceRedraw();
    }

protected:
    TeensyMediaButtonBar _button_bar;
    std::function<void(MediaButtonType)> _buttonPressedCallback;

};

class MediaTimeMenuItem : public TeensyMenuItem {
public:
    explicit MediaTimeMenuItem(TeensyMenu &menu, MediaPosition &position) : TeensyMenuItem(menu, nullptr, 12, nullptr, nullptr, nullptr,
                                                                  nullptr), _media_position(position),
                                                   _timeIndicator(*this, 128, 10, 0, 0) {
        _children.push_back(&_timeIndicator);
    }

    ~MediaTimeMenuItem() override = default;

    void Init() {
        if (_initialized) return;
        _timeIndicator.Init();
        _initialized = true;
    }
    void SetTime(const unsigned milliseconds) {
        _timeIndicator.SetTime( _media_position.GetMilliseconds());
    }
private:
    MediaPosition &_media_position;
    TeensyTimeIndicator _timeIndicator;
    bool _initialized = false;
};

class MidiSpyScene : public BaseScene {
public:
    const String _label = "hell0, 0 world";
    MidiSpyScene(View &mainView, int sdChipSelect) : BaseScene(mainView, 128, 128, 0, 0, _bmp_settings_on,
                                                               _bmp_settings_off, 16, 16),
                                                     mainView(mainView),
                                                     _media_position(),
                                                     _menu(mainView, 128, 128, 0, 0, 0x092D /*Sapphire*/, 0),
                                                     _mediaButtonBarMenuItem(
                                                         new MediaButtonBarMenuItem(_menu, [&] (MediaButtonType buttonType) {
                                                             MediaButtonPressed(buttonType);
                                                         })
                                                     ),
                                                     _mediaTimeMenuItem(new MediaTimeMenuItem(_menu, _media_position)),
                                                     sceneMenuItems{
                                                         _mediaButtonBarMenuItem,
                                                         _mediaTimeMenuItem,
                                                         new TeensyStringMenuItem(_menu, _label, nullptr)
                                                     },
                                                     _microseconds(0),
                                                     _lastMicroseconds(0),
                                                     _microsPerTick(0),
                                                     _currentTicks(0),
                                                     _lastEventTicks(0),
                                                     _sdChipSelect(sdChipSelect) {
        _menu.AddControl(sceneMenuItems[0]);
        _menu.AddControl(sceneMenuItems[1]);
        _menu.AddControl(sceneMenuItems[2]);
    }

    ~MidiSpyScene() override {

    }

    void Update (unsigned milliseconds) override {
        if (_sdConnected) {
            //_button_bar.Update(milliseconds);
            _menu.Update(milliseconds);
            if (_isRecording) {
                unsigned long currentMicros = micros();
                if (_lastMicroseconds == 0) {
                    _lastMicroseconds = currentMicros;
                    _media_position.SetMilliseconds(0);
                }
                else if (currentMicros - _lastMicroseconds > _microsPerTick) {
                    auto deltaTicks = currentMicros - _lastMicroseconds;
                    _currentTicks += deltaTicks / _microsPerTick;
                    _lastMicroseconds = currentMicros;
                    _media_position.SetMilliseconds(_media_position.GetMilliseconds() + deltaTicks/1000);
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
        _mediaTimeMenuItem->SetTime(milliseconds);
        TeensyControl::Update(milliseconds);
    }

    void InitScreen () override {
        _mediaTimeMenuItem->Init();
        _microseconds = micros();
        _lastMicroseconds = 0;
        _currentTicks = 0;
        _lastEventTicks = 0;
        _microsPerTick = get_microseconds_per_tick(120.0);
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
            auto deltaTicks = _currentTicks - _lastEventTicks;
            _lastEventTicks = _currentTicks;
            Serial.print("ON pitch: ");
            Serial.print(pitch);
            Serial.print(" velocity: ");
            Serial.println(velocity);
            writer.addNoteOnEvent(deltaTicks, channel, pitch, velocity);
        }
    }
    void NoteOff(uint8_t channel, uint8_t pitch, uint8_t velocity) override {
        if (_isRecording) {
            auto deltaTicks = _currentTicks - _lastEventTicks;
            _lastEventTicks = _currentTicks;
            Serial.print("OFF pitch: ");
            Serial.print(pitch);
            Serial.print(" velocity: ");
            Serial.println(velocity);
            writer.addNoteOffEvent(deltaTicks, channel, pitch);
        }
    }
    void ControlChange(uint8_t channel, uint8_t data1, uint8_t data2) override {
        if (_isRecording) {
            auto deltaTicks = _currentTicks - _lastEventTicks;
            _lastEventTicks = _currentTicks;
            writer.addControlChange(deltaTicks, data1, data2, channel);
        }
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
        writer.addSetTempo(0, 120.0);
        mainView.drawString(writer.getFilename(),0,74);
        _microseconds = micros();
        _lastMicroseconds = 0;
        _currentTicks = 0;
        _lastEventTicks = 0;
        _menu.ForceRedraw();
    }

    void StopRecording() {
        mainView.fillScreen(RGB565_Black);
        mainView.drawString("Ready",0,64);
        writer.addEndofTrack(0,0);
        writer.close();
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
    MediaTimeMenuItem *_mediaTimeMenuItem;
    TeensyMenuItem *sceneMenuItems[3];
    unsigned long long _microseconds, _lastMicroseconds, _microsPerTick, _currentTicks, _lastEventTicks;
    SmfWriter writer;
    bool _sdConnected = false, _hasError = false, _isRecording = false;
    int _sdChipSelect, _lastErrorNumber = 0;
};


#endif //MIDISPYSCENE_H
