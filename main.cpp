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
#include "MainMenu.h"

using namespace Bounce2;
Button button = Button();
Button button2 = Button();
Button button3 = Button();
Encoder encoderLeftRight;
Encoder encoderUpDown;

st7735_opengl<Encoder,Button> tft = st7735_opengl<Encoder,Button>(false, 0, &encoderUpDown, &encoderLeftRight, &button, &button2, &button3);
VirtualView mainView(tft, 0,0, 128, 128);

SceneController controller(mainView, encoderUpDown, encoderLeftRight, button, button2,button3);

MainScene *mainMenuScene = new MainScene(mainView);

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

    mainView.fillScreen(RGB565_Black);

    controller.AddScene(mainMenuScene);
    controller.SetCurrentSceneIndex(0);
    controller.SetActive(false);
}

void loop() {
    controller.Process();
}

int st7735_main(int, char**) {
    return 0;
}
