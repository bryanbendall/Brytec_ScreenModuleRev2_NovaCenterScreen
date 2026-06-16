#pragma once

#include "data/communication/NetworkStats.h"
#include "gui/layer/Layer.h"

class InfoLayer : public Layer {

public:
    InfoLayer();
    virtual ~InfoLayer();

    virtual void update() override;

    const char* getName() override { return "Info Layer"; }

private:
    NetworkStats m_stats;
};