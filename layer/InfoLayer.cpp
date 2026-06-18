#include "InfoLayer.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/UiManager.h"
#include "gui/Utils.h"
#include "gui/components/UiComponents.h"
#include "gui/renderer/Renderer.h"

InfoLayer::InfoLayer()
{
}

InfoLayer::~InfoLayer()
{
}

void InfoLayer::update()
{
    Color activeColor = Utils::getColorFromBrytec(GlobalOutputs::values["guageColor"]);
    Color backgroundColor = GetColor(GlobalOutputs::gray);

    int newScreenNum = (int)GlobalOutputs::values["screenLayout"];
    if (newScreenNum != 0)
        UiManager::get().removeLayer(this);

    Ui::Text({ 400.0f, 100.0f }, "Info", 100);

    if (Ui::RoundedButton("Show ImGui", { 400.0f, 240.0f }, { 300.0f, 80.0f }, 30))
        GlobalOutputs::values["showImGui"] = GlobalOutputs::values["showImGui"] > 0.0f ? 0.0f : 1.0f;

    float y = 340.0f;
    for (auto& stat : m_stats.getStats()) {
        Renderer::submitText({ 50.0f, y }, stat.interface + "  -  " + stat.ipAddress + "  -  " + stat.ssidName, 20, GetColor(GlobalOutputs::white), Renderer::TextAnchor::Left);
        y += 30.0f;
    }
}