#pragma once

#include "gui/layer/Layer.h"

class MapLayer : public Layer {

public:
    MapLayer();
    virtual ~MapLayer();

    virtual void update() override;

    const char* getName() override { return "Map Layer"; }
};