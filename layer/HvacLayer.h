#pragma once

#include "gui/layer/Layer.h"

class HvacLayer : public Layer {

public:
    HvacLayer();
    virtual ~HvacLayer();

    virtual void update() override;

    const char* getName() override { return "Hvac Layer"; }
};