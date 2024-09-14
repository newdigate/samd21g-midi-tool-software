#include <iostream>

#include "View.h"
#include "teensy_controls.h"
#include <Bounce2.h>
#include <Encoder.h>

#include "scenecontroller.h"
#include "icons.h"
#include "rgb565_colors.h"
#include "st7735_opengl.h"
#include "st7735_opengl_main.h"

using namespace Bounce2;
Button button = Button();
Button button2 = Button();
Button button3 = Button();
Encoder encoderLeftRight;
Encoder encoderUpDown;



st7735_opengl<Encoder,Button> tft = st7735_opengl<Encoder,Button>(false, 0, &encoderUpDown, &encoderLeftRight, &button, &button2, &button3);
VirtualView mainView(tft, 0,0, 128, 128);

TeensyMenu *mainMenu = new TeensyMenu(mainView, 128, 64, 0, 0, RGB565_Sapphire, 0);
TeensyMenuItem dialogMenuItems[] = {
    TeensyMenuItem(*mainMenu, [] (View *v) {v->drawString("Settings", 0, 0);}, 8),
    TeensyMenuItem(*mainMenu, [] (View *v) {v->drawString("Theory", 0, 0);}, 8),
    TeensyMenuItem(*mainMenu, [] (View *v) {v->drawString("Play", 0, 0);}, 8),
    TeensyMenuItem(*mainMenu, [] (View *v) {v->drawString("Record", 0, 0);}, 8),
    TeensyMenuItem(*mainMenu, [] (View *v) {v->drawString("Loop", 0, 0);}, 8),
    TeensyMenuItem(*mainMenu, [] (View *v) {v->drawString("Spy", 0, 0);}, 8),
    TeensyMenuItem(*mainMenu, [] (View *v) {v->drawString("Sleep", 0, 0);}, 8),
  };

SceneController controller(mainView, encoderUpDown, encoderLeftRight, button, button2,button3);
const char* menuDescriptions[] = {
    "Change device settings",
    "Interactive and non-interactive lessons",
    "Play songs at your own pace, or any other pace",
    "Play songs in a non-interactive way",
    "Record your song",
    "Looping recorder",
    "Silent record",
    "Sleep","h","i","j","k","m","n","o","p"};
int lastMenuItemIndex = 0;
Scene *settingsScene = new Scene(
                        _bmp_settings_on,
                        _bmp_settings_off,
                        16, 16,
                        [] {
                              mainMenu->Update();
                        },      //            std::function<void()> update = nullptr,
                        [] {
                            mainView.fillScreen(RGB565_Blue);
                            mainMenu->NeedsUpdate = true;
                            mainView.setTextColor(RGB565_White);
                            mainView.setTextWrap(true);
                            mainView.drawString(menuDescriptions[mainMenu->GetSelectedIndex()], 0,64);
                        },   //             std::function<void()> initScreen = nullptr,
                        [] {

                        },   //             std::function<void()> uninitScreen = nullptr,
                        [] (unsigned index) {
                            mainMenu->ButtonDown(index);
                        }, //             std::function<void(unsigned)> buttonPressed = nullptr,
                        [] (bool forward) {
                            if (forward) mainMenu->IncreaseSelectedIndex();
                            else mainMenu->DecreaseSelectedIndex();
                            mainView.setTextWrap(true);
                            if (lastMenuItemIndex != -1) {
                                mainView.setTextColor(RGB565_Blue);
                                mainView.drawString(menuDescriptions[lastMenuItemIndex], 0,64);
                            }
                            mainView.setTextColor(RGB565_White);
                            mainView.drawString(menuDescriptions[mainMenu->GetSelectedIndex()], 0,64);
                            lastMenuItemIndex = mainMenu->GetSelectedIndex();
                        }, //std::function<void(bool)> rotary1Changed = nullptr,
                        [] (bool forward) { } //std::function<void(bool)> rotary2Changed = nullptr
                        );


void setup() {

    Serial.begin(9600);

    button.attach( 10, 10 ); // USE EXTERNAL PULL-UP
    button2.attach( 11, 11 ); // USE EXTERNAL PULL-UP
    button3.attach( 12, 12 ); // USE EXTERNAL PULL-UP

    button.interval(5);
    button2.interval(5);
    button3.interval(5);

    button.setPressedState(LOW);
    button2.setPressedState(LOW);
    button3.setPressedState(LOW);

    delay(10);
    for (auto && menuItem : dialogMenuItems)
        mainMenu->AddControl(&menuItem);
    mainView.fillScreen(RGB565_Black);

    controller.AddScene(settingsScene);
    controller.SetCurrentSceneIndex(0);
    controller.SetActive(false);
}

void loop() {
    controller.Process();
}

int st7735_main(int, char**) {
    return 0;
}
