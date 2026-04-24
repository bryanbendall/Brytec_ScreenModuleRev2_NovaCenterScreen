#pragma once

#include "gui/layer/Layer.h"

class ButtonLayer : public Layer {

    enum Screens {
        Info,
        Map,
        Hvac,
        Settings
    };

public:
    ButtonLayer();
    virtual ~ButtonLayer();

    virtual void update() override;

    const char* getName() override { return "Button Layer"; }

private:
    void setScreen(Screens screen);
};