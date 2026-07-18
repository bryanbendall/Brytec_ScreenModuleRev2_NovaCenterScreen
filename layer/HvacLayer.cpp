#include "HvacLayer.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/UiManager.h"
#include "gui/Utils.h"
#include "gui/components/UiComponents.h"
#include "gui/renderer/Renderer.h"
#include <fmt/format.h>

HvacLayer::HvacLayer()
{
}

HvacLayer::~HvacLayer()
{
}

void HvacLayer::update()
{
    Color activeColor = Utils::getColorFromBrytec(GlobalOutputs::values["guageColor"]);
    Color backgroundColor = GetColor(GlobalOutputs::black);
    Color borderColor = GetColor(GlobalOutputs::gray);

    Ui::Text({ 400.0f, 100.0f }, "Hvac", 100);

    Ui::SmallGaugeSpec acPressSpec { };
    acPressSpec.value = GlobalOutputs::values["acPress"];
    acPressSpec.center = { 220.0f, 330.0f };
    acPressSpec.size = 250.0f;
    acPressSpec.label = "Press";
    acPressSpec.max = 500.0f;
    Ui::SmallGauge(acPressSpec);

    Ui::SmallGaugeSpec acTempSpec { };
    acTempSpec.value = GlobalOutputs::values["acCoreTemp"];
    acTempSpec.center = { 580.0f, 330.0f };
    acTempSpec.size = 250.0f;
    acTempSpec.label = "Temp";
    acTempSpec.iconFilename = "water-temp.svg";
    Ui::SmallGauge(acTempSpec);

    {
        float& acOnTemp = GlobalInputs::values["acOnTemp"];

        Ui::Text({ 220.0f, 550.0f }, "Clutch On", 40);

        if (Ui::RoundedButton("-", { 145.0f, 625.0f }, { 80.0f, 80.0f }, 30, backgroundColor, activeColor, borderColor))
            acOnTemp -= 1.0f;

        std::string lable = fmt::format("{:.0f}", acOnTemp);
        Ui::Text({ 220.0f, 625.0f }, lable.c_str(), 30);

        if (Ui::RoundedButton("+", { 295.0f, 625.0f }, { 80.0f, 80.0f }, 30, backgroundColor, activeColor, borderColor))
            acOnTemp += 1.0f;
    }

    {
        Color c = GlobalOutputs::values["acClutchStatus"] ? GetColor(GlobalOutputs::green) : GetColor(GlobalOutputs::gray);
        Renderer::submitCircle({ 400.0f, 600.0f }, 40, c);
    }

    {
        float& acOffTemp = GlobalInputs::values["acOffTemp"];

        Ui::Text({ 580.0f, 550.0f }, "Clutch Off", 40);

        if (Ui::RoundedButton("-", { 505.0f, 625.0f }, { 80.0f, 80.0f }, 30, backgroundColor, activeColor, borderColor))
            acOffTemp -= 1.0f;

        std::string lable = fmt::format("{:.0f}", acOffTemp);
        Ui::Text({ 580.0f, 625.0f }, lable.c_str(), 30);

        if (Ui::RoundedButton("+", { 655.0f, 625.0f }, { 80.0f, 80.0f }, 30, backgroundColor, activeColor, borderColor))
            acOffTemp += 1.0f;
    }

    {
        float& hvacFan = GlobalInputs::values["hvacFan"];

        Ui::Text({ 400.0f, 760.0f }, "Fan", 40);

        if (Ui::RoundedButton("Off", { 250.0f - 30.0f, 840.0f }, { 100.0f, 80.0f }, 30, hvacFan == 0.0f ? activeColor : backgroundColor, activeColor, borderColor))
            hvacFan = 0.0f;
        if (Ui::RoundedButton("Lo", { 350.0f - 10.0f, 840.0f }, { 100.0f, 80.0f }, 30, hvacFan == 1.0f ? activeColor : backgroundColor, activeColor, borderColor))
            hvacFan = 1.0f;
        if (Ui::RoundedButton("Med", { 450.0f + 10.0f, 840.0f }, { 100.0f, 80.0f }, 30, hvacFan == 2.0f ? activeColor : backgroundColor, activeColor, borderColor))
            hvacFan = 2.0f;
        if (Ui::RoundedButton("Hi", { 550.0f + 30.0f, 840.0f }, { 100.0f, 80.0f }, 30, hvacFan == 3.0f ? activeColor : backgroundColor, activeColor, borderColor))
            hvacFan = 3.0f;
    }

    {
        float& acEnable = GlobalInputs::values["acEnable"];

        if (Ui::RoundedButton("A/C Enable", { 400.0f, 970.0f }, { 200.0f, 80.0f }, 30, acEnable > 0.0f ? activeColor : backgroundColor, activeColor, borderColor))
            acEnable > 0.0f ? acEnable = 0.0f : acEnable = 1.0f;
    }

    {
        float& hvacLevel = GlobalInputs::values["hvacLevel"];

        if (Ui::RoundedButton("Defrost", { 175.0f - 30.0f, 1100.0f }, { 150.0f, 80.0f }, 30, hvacLevel == 0.0f ? activeColor : backgroundColor, activeColor, borderColor))
            hvacLevel = 0.0f;
        if (Ui::RoundedButton("Dash", { 325.0f - 10.0f, 1100.0f }, { 150.0f, 80.0f }, 30, hvacLevel == 1.0f ? activeColor : backgroundColor, activeColor, borderColor))
            hvacLevel = 1.0f;
        if (Ui::RoundedButton("Bi Level", { 475.0f + 10.0f, 1100.0f }, { 150.0f, 80.0f }, 30, hvacLevel == 2.0f ? activeColor : backgroundColor, activeColor, borderColor))
            hvacLevel = 2.0f;
        if (Ui::RoundedButton("Floor", { 625.0f + 30.0f, 1100.0f }, { 150.0f, 80.0f }, 30, hvacLevel == 3.0f ? activeColor : backgroundColor, activeColor, borderColor))
            hvacLevel = 3.0f;
    }
}