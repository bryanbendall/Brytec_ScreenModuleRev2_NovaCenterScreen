#pragma once

#include "gui/layer/Layer.h"

class SettingsLayer : public Layer {

public:
    SettingsLayer();
    virtual ~SettingsLayer();

    virtual void update() override;

    const char* getName() override { return "Settings Layer"; }

private:
    bool m_saved = true;
    float m_savedCooldown = 0.0f;
};