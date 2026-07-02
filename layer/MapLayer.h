#pragma once

#include "gui/layer/Layer.h"

class MapLayer : public Layer {

private:
    enum class State {
        Default,
        EnteringAddress
    };

public:
    MapLayer();
    virtual ~MapLayer();

    virtual void update() override;

    const char* getName() override { return "Map Layer"; }

private:
    State m_state = State::Default;
    std::string m_ip = "192.168.1.26:8080";
};