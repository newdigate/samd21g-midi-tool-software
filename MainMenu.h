//
// Created by Moolet on 15/09/2024.
//

#ifndef MAINMENU_H
#define MAINMENU_H
#include "rgb565_colors.h"
#include "scenecontroller.h"
#include "teensy_controls.h"
#include "icons.h"

#define numMenuItems 7

class MainMenu : public TeensyMenu {
public:
    MainMenu(View &mainView) : TeensyMenu(mainView, 128, 64, 0, 0, RGB565_Sapphire, 0 ) {

        dialogMenuItems[0] = new TeensyMenuItem(*this, [this] (View *v) {v->drawString(menuLabels[0], 0, 1);}, 10);
        dialogMenuItems[1] = new TeensyMenuItem(*this, [this] (View *v) {v->drawString(menuLabels[1], 0, 1);}, 10);
        dialogMenuItems[2] = new TeensyMenuItem(*this, [this] (View *v) {v->drawString(menuLabels[2], 0, 1);}, 10);
        dialogMenuItems[3] = new TeensyMenuItem(*this, [this] (View *v) {v->drawString(menuLabels[3], 0, 1);}, 10);
        dialogMenuItems[4] = new TeensyMenuItem(*this, [this] (View *v) {v->drawString(menuLabels[4], 0, 1);}, 10);
        dialogMenuItems[5] = new TeensyMenuItem(*this, [this] (View *v) {v->drawString(menuLabels[5], 0, 1);}, 10);
        dialogMenuItems[6] = new TeensyMenuItem(*this, [this] (View *v) {v->drawString(menuLabels[6], 0, 1);}, 10);

        for (int i=0; i<numMenuItems; i++)
            AddControl(dialogMenuItems[i]);
    }
    ~MainMenu() override {
        for (int i=0; i<numMenuItems; i++)
            delete dialogMenuItems[i];
        TeensyMenu::~TeensyMenu();
    }

    TeensyMenuItem *dialogMenuItems[numMenuItems];
    const char* menuLabels[numMenuItems] = {
        "Settings",
        "Theory",
        "Play",
        "Record",
        "Loop",
        "Spy",
        "Sleep"};

    int lastMenuItemIndex = 0;
};

class MainScene : public BaseScene {
public:
    MainScene(View &mainView) : BaseScene(_bmp_settings_on, _bmp_settings_off, 16, 16),
        mainView(mainView)
    {
        mainMenu = new MainMenu(mainView);
    }

    virtual ~MainScene() {
    }

    void Update () override {
        mainMenu->Update();
    }

    void InitScreen () override {
        mainView.fillScreen(RGB565_Blue);
        mainMenu->NeedsUpdate = true;
        mainView.setTextColor(RGB565_White);
        mainView.setTextWrap(true);
        mainView.setTextSize(2);
        mainView.drawString(menuDescriptions[mainMenu->GetSelectedIndex()], 0,64);
    }
    void UninitScreen () override {}

    void ButtonPressed(unsigned buttonIndex) override {
        mainMenu->ButtonDown(buttonIndex);
    }
    void Rotary1Changed(bool forward) override {
        if (forward) mainMenu->IncreaseSelectedIndex();
        else mainMenu->DecreaseSelectedIndex();
        mainView.setTextWrap(true);
        mainView.setTextSize(2);
        if (lastMenuItemIndex != -1) {
            mainView.setTextColor(RGB565_Blue);
            mainView.drawString(menuDescriptions[lastMenuItemIndex], 0,64);
        }
        mainView.setTextColor(RGB565_White);
        mainView.drawString(menuDescriptions[mainMenu->GetSelectedIndex()], 0,64);
        lastMenuItemIndex = mainMenu->GetSelectedIndex();
    }
    void Rotary2Changed(bool forward) override {}
    bool HandleNoteOnOff(bool noteDown, uint8_t channel, uint8_t pitch, uint8_t velocity) override { return false; }
    bool HandleControlChange(uint8_t channel, uint8_t data1, uint8_t data2) override { return false; }
private:
    MainMenu *mainMenu;
    View &mainView;
    int lastMenuItemIndex = 0;

    const char* menuDescriptions[numMenuItems] = {
        "Change device settings",
        "Interactive and non-interactive lessons",
        "Play songs at your own pace, or any other pace",
        "Record your song",
        "Looping recorder",
        "Silent record",
        "Sleep"};
};

#endif //MAINMENU_H
