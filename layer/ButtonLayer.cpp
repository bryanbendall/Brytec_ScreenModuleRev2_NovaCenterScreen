#include "ButtonLayer.h"

#include "data/GlobalInputs.h"
#include "gui/UiManager.h"
#include "gui/Utils.h"
#include "gui/components/UiComponents.h"
#include "gui/renderer/Renderer.h"
#include "layer/HvacLayer.h"
#include "layer/InfoLayer.h"
#include "layer/MapLayer.h"
#include "layer/SettingsLayer.h"

ButtonLayer::ButtonLayer()
{
    setScreen(Screens::Info);
}

ButtonLayer::~ButtonLayer()
{
}

void ButtonLayer::update()
{
    Color activeColor = Utils::getColorFromBrytec(GlobalOutputs::values["guageColor"]);
    Color backgroundColor = GetColor(GlobalOutputs::black);

    int currentScreen = (int)GlobalOutputs::values["screenLayout"];

    if (Ui::Button("Info", { 100, 1230 }, { 200, 100 }, 38, currentScreen == Screens::Info ? activeColor : backgroundColor, activeColor))
        setScreen(Screens::Info);
    if (Ui::Button("Map", { 300, 1230 }, { 200, 100 }, 38, currentScreen == Screens::Map ? activeColor : backgroundColor, activeColor))
        setScreen(Screens::Map);
    if (Ui::Button("Hvac", { 500, 1230 }, { 200, 100 }, 38, currentScreen == Screens::Hvac ? activeColor : backgroundColor, activeColor))
        setScreen(Screens::Hvac);
    if (Ui::Button("Settings", { 700, 1230 }, { 200, 100 }, 38, currentScreen == Screens::Settings ? activeColor : backgroundColor, activeColor))
        setScreen(Screens::Settings);
}

void ButtonLayer::setScreen(Screens screen)
{
    GlobalInputs::values["screenLayout"] = (float)screen;

    switch (screen) {
    case Screens::Info:
        UiManager::get().pushLayerBack<InfoLayer>();
        break;
    case Screens::Map:
        UiManager::get().pushLayerBack<MapLayer>();
        break;
    case Screens::Hvac:
        UiManager::get().pushLayerBack<HvacLayer>();
        break;
    case Screens::Settings:
        UiManager::get().pushLayerBack<SettingsLayer>();
        break;
    }
}