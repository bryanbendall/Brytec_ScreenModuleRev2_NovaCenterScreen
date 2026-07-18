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
#include <cmath>
#include <imgui.h>

ButtonLayer::ButtonLayer()
{
    setScreen(Screens::Info);
}

ButtonLayer::~ButtonLayer()
{
}

void ButtonLayer::update()
{
    // Update screen layout from animation
    AnimationManager& anim = AnimationManager::get();
    bool screenLayoutChange = anim.tryGetValue(GlobalInputs::values["screenLayout"]);

    if (screenLayoutChange) {
        // std::cout << "change" << std::endl;
    }

    // Bottom buttons
    if (Ui::InvisibleButton("Info", { 100, 1230 }, { 200, 100 }, 38))
        setScreen(Screens::Info);
    if (Ui::InvisibleButton("Map", { 300, 1230 }, { 200, 100 }, 38))
        setScreen(Screens::Map);
    if (Ui::InvisibleButton("Hvac", { 500, 1230 }, { 200, 100 }, 38))
        setScreen(Screens::Hvac);
    if (Ui::InvisibleButton("Settings", { 700, 1230 }, { 200, 100 }, 38))
        setScreen(Screens::Settings);

    float currentScreen = GlobalOutputs::values["screenLayout"];
    Color activeColor = Utils::getColorFromBrytec(GlobalOutputs::values["guageColor"]);
    Renderer::submitBox({ 100.0f + currentScreen * 200.0f, 1182 }, { 200, 4 }, 0.0f, activeColor);
    Renderer::submitBox({ 100 + currentScreen * 200.0f, 1230 }, { 200, 100 }, 0.0f, Fade(activeColor, 0.3f));
}

void ButtonLayer::setScreen(Screens screen)
{
    removeScreen((Screens)GlobalInputs::values["screenLayout"]);

    AnimationManager& anim = AnimationManager::get();
    anim.animate(GlobalInputs::values["screenLayout"]).add((float)screen, 0.2f, Easing::InOutExpo);

    // GlobalInputs::values["screenLayout"] = (float)screen;

    switch (screen) {
    case Screens::Info:
        UiManager::get().pushLayerBack<InfoLayer>(nullptr);
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

void ButtonLayer::removeScreen(Screens screen)
{
    switch (screen) {
    case Screens::Info: {
        auto infoLayer = UiManager::get().getLayer<InfoLayer>();
        if (infoLayer)
            UiManager::get().removeLayer(infoLayer);
    } break;
    case Screens::Map: {
        auto mapLayer = UiManager::get().getLayer<MapLayer>();
        if (mapLayer)
            UiManager::get().removeLayer(mapLayer);
    } break;
    case Screens::Hvac: {
        auto hvacLayer = UiManager::get().getLayer<HvacLayer>();
        if (hvacLayer)
            UiManager::get().removeLayer(hvacLayer);
    } break;
    case Screens::Settings: {
        auto settingsLayer = UiManager::get().getLayer<SettingsLayer>();
        if (settingsLayer)
            UiManager::get().removeLayer(settingsLayer);
    } break;
    }
}