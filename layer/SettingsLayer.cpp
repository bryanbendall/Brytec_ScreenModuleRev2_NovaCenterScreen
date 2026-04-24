#include "SettingsLayer.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/UiManager.h"
#include "gui/Utils.h"
#include "gui/components/UiComponents.h"
#include "gui/input/TouchInput.h"
#include "gui/renderer/Renderer.h"
#include <fmt/format.h>

SettingsLayer::SettingsLayer()
{
}

SettingsLayer::~SettingsLayer()
{
}

void SettingsLayer::update()
{
    Color activeColor = Utils::getColorFromBrytec(GlobalOutputs::values["guageColor"]);
    Color backgroundColor = GetColor(GlobalOutputs::gray);

    int newScreenNum = (int)GlobalOutputs::values["screenLayout"];
    if (newScreenNum != 3)
        UiManager::get().removeLayer(this);

    Ui::Text({ 400.0f, 100.0f }, "Settings", 100);

    float& boostEnable = GlobalInputs::values["boostEnable"];
    if (Ui::Button("Boost Enable", { 260.0f, 240.0f }, { 240.0f, 80.0f }, 30, boostEnable > 0.0f ? activeColor : backgroundColor, activeColor))
        boostEnable > 0.0f ? boostEnable = 0.0f : boostEnable = 1.0f;

    float& fuelTypeGas = GlobalInputs::values["fuelTypeGas"];
    std::string fuelType = fuelTypeGas > 0.0f ? "Gas" : "Meth";
    if (Ui::Button(fuelType, { 540.0f, 240.0f }, { 240.0f, 80.0f }, 30, backgroundColor, activeColor))
        fuelTypeGas > 0.0f ? fuelTypeGas = 0.0f : fuelTypeGas = 1.0f;

    {
        float& baseBoost = GlobalInputs::values["baseBoost"];

        Ui::Text({ 400.0f, 350.0f }, "Base Boost", 40);

        if (Ui::Button("-", { 325.0f, 425.0f }, { 50.0f, 50.0f }, 30, backgroundColor, activeColor))
            baseBoost -= 1.0f;

        // Clamp bottom to 0
        if (baseBoost < 0.0f)
            baseBoost = 0.0f;

        std::string lable = fmt::format("{:.0f}", baseBoost);
        Ui::Text({ 400.0f, 425.0f }, lable.c_str(), 40);

        if (Ui::Button("+", { 475.0f, 425.0f }, { 50.0f, 50.0f }, 30, backgroundColor, activeColor))
            baseBoost += 1.0f;

        // Clamp top to 15
        if (baseBoost > 15.0f)
            baseBoost = 15.0f;
    }

    {
        float& maxBoost = GlobalInputs::values["maxBoost"];

        Ui::Text({ 400.0f, 500.0f }, "Max Boost", 40);

        if (Ui::Button("-", { 325.0f, 575.0f }, { 50.0f, 50.0f }, 30, backgroundColor, activeColor))
            maxBoost -= 1.0f;

        // Clamp bottom to 0
        if (maxBoost < 0.0f)
            maxBoost = 0.0f;

        std::string lable = fmt::format("{:.0f}", maxBoost);
        Ui::Text({ 400.0f, 575.0f }, lable.c_str(), 40);

        if (Ui::Button("+", { 475.0f, 575.0f }, { 50.0f, 50.0f }, 30, backgroundColor, activeColor))
            maxBoost += 1.0f;

        // Clamp top to 20
        if (maxBoost > 20.0f)
            maxBoost = 20.0f;
    }

    {
        float& primeGas = GlobalInputs::values["primeGas"];

        if (Ui::MomentaryButton("Prime Gas", { 275.0f, 690.0f }, { 200.0f, 80.0f }, 30, primeGas > 0.0f ? activeColor : backgroundColor))
            primeGas = 1.0f;
        else
            primeGas = 0.0f;

        float& primeMeth = GlobalInputs::values["primeMeth"];

        if (Ui::MomentaryButton("Prime Meth", { 525.0f, 690.0f }, { 200.0f, 80.0f }, 30, primeMeth > 0.0f ? activeColor : backgroundColor))
            primeMeth = 1.0f;
        else
            primeMeth = 0.0f;
    }

    float& useKph = GlobalInputs::values["useKph"];

    if (Ui::Button("Mph", { 300.0f, 840.0f }, { 200.0f, 80.0f }, 30, useKph < 0.5f ? activeColor : backgroundColor, activeColor))
        useKph = 0.0f;
    if (Ui::Button("Kph", { 500.0f, 840.0f }, { 200.0f, 80.0f }, 30, useKph > 0.5f ? activeColor : backgroundColor, activeColor))
        useKph = 1.0f;

    AnimationManager::get().tryGetValue(m_savedCooldown);

    if (m_savedCooldown > 0.0f) {
        Ui::Text({ 400.0f, 1040.0f }, "Settings Saved!", 30);
    } else {
        if (Ui::Button("Save", { 400.0f, 1040.0f }, { 200.0f, 80.0f }, 30, backgroundColor, activeColor)) {
            GlobalInputs::saveToFile();
            m_saved = true;
            m_savedCooldown = 1.0f;
            AnimationManager::get().animate(m_savedCooldown).add(0.0f, 2.0f);
        }
    }
}