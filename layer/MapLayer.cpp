#include "MapLayer.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/UiManager.h"
#include "gui/Utils.h"
#include "gui/components/UiComponents.h"
#include "gui/renderer/Renderer.h"

MapLayer::MapLayer()
{
}

MapLayer::~MapLayer()
{
}

void MapLayer::update()
{
    Color activeColor = Utils::getColorFromBrytec(GlobalOutputs::values["guageColor"]);
    Color backgroundColor = GetColor(GlobalOutputs::gray);

    int newScreenNum = (int)GlobalOutputs::values["screenLayout"];
    if (newScreenNum != 1)
        UiManager::get().removeLayer(this);

    Ui::Text({ 400.0f, 100.0f }, "Map", 100);
}