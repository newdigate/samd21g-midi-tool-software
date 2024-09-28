//
// Created by Moolet on 15/09/2024.
//

#ifndef MAINMENU_H
#define MAINMENU_H
#include <st7735_opengl_main.h>
#include <sys/types.h>

#include "rgb565_colors.h"
#include "scenecontroller.h"
#include "teensy_controls.h"
#include "icons.h"

#define numMenuItems 7

template <typename TMidi>
class MainScene : public BaseScene {
public:
    MainScene(View &mainView, SceneController<VirtualView, Encoder, Bounce2::Button, TMidi> &controller) :
        BaseScene(mainView, 128, 128, 0, 0, _bmp_settings_on, _bmp_settings_off, 16, 16),
        mainMenu(mainView, 128, 64, 0, 0, RGB565_Sapphire, RGB565_Black),
        mainView(mainView),
        sketchDescriptions(),
        _controller(controller)
    {
    }

    virtual ~MainScene() {
    }

    void Update () override {
        mainMenu.Update();
    }

    void InitScreen () override {
        mainView.fillScreen(RGB565_Blue);
        mainMenu.NeedsUpdate = true;
        mainView.setTextColor(RGB565_White);
        mainView.setTextWrap(true);
        mainView.drawString(sketchDescriptions[mainMenu.GetSelectedIndex()].c_str(),0,64);
    }
    void UninitScreen () override {}

    void ButtonPressed(unsigned buttonIndex) override {
        mainMenu.ButtonDown(buttonIndex);
    }
    void Rotary1Changed(bool forward) override {
        if (forward) mainMenu.IncreaseSelectedIndex();
        else mainMenu.DecreaseSelectedIndex();
        mainView.setTextWrap(true);
        mainView.fillRect(0, 64, 128, 64, RGB565_Blue);
        mainView.setTextColor(RGB565_White);
        mainView.drawString(sketchDescriptions[mainMenu.GetSelectedIndex()], 0,64);
    }
    void Rotary2Changed(bool forward) override {}

    void AddSketch(const String &sketchName, const String &sketchDescription, TeensyControl* sketchControl) {
        auto *sketchMenuItem = new TeensyStringMenuItem(mainMenu, sketchName, std::bind(&MainScene::MenuItemClicked, this, sketchDescriptions.size(), std::placeholders::_1) ) ;
        sketchDescriptions.push_back(sketchDescription);
        mainMenu.AddControl(sketchMenuItem);
        sketchControls.push_back(sketchControl);
    }
    void MenuItemClicked(const int menuItemIndex, const int buttonIndex) const {
        Serial.println("MenuItemClicked!!!!!");
        if (buttonIndex == 1 && menuItemIndex <= sketchControls.size()) {
            _controller.AddDialog(sketchControls[menuItemIndex]);
        }
    }
private:
    TeensyMenu mainMenu;
    View &mainView;

    std::vector<TeensyControl*> sketchControls;
    std::vector<String> sketchDescriptions;

    SceneController<VirtualView, Encoder, Bounce2::Button, TMidi> &_controller;
};

#endif //MAINMENU_H
