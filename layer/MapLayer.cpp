#include "MapLayer.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/UiManager.h"
#include "gui/Utils.h"
#include "gui/components/UiComponents.h"
#include "gui/renderer/Renderer.h"
#include <imgui.h>

MapLayer::MapLayer()
{
}

MapLayer::~MapLayer()
{
}

void MapLayer::update()
{
    static Vector2 textureSize = { 800.0f, 1100.0f };

    Color activeColor = Utils::getColorFromBrytec(GlobalOutputs::values["guageColor"]);
    Color backgroundColor = GetColor(GlobalOutputs::gray);

    switch (m_state) {
    case State::Default: {
        Texture2D* texture = AssetManager::get().getCameraTexture("ScreenCapture");
        if (texture) {
            Renderer::submitTextureCrop({ 400.0f, 620.0f }, *texture, textureSize, WHITE);

            if (Ui::RoundedButton("Close", { 100.0f, 32.0f }, { 180.0f, 60.0f }, 30)) {
                RemoteCamera& screenCaptureCamera = CameraController::get().getCamera("ScreenCapture");
                screenCaptureCamera.close();
            }

        } else {
            Ui::Text({ 400.0f, 100.0f }, "Map", 100);

            int fontSize = 30;

            std::string ipAddr = m_ip;
            int textWidth = MeasureText(ipAddr.c_str(), fontSize);

            if (Ui::RoundedButton(ipAddr, { 400.0f, 600.0f }, { textWidth + 80.0f, 80.0f }, fontSize)) {
                m_state = State::EnteringAddress;
            }

            if (Ui::RoundedButton("Connect", { 400.0f, 690.0f }, { 200.0f, 80.0f }, fontSize)) {
                RemoteCamera& screenCaptureCamera = CameraController::get().getCamera("ScreenCapture");
                screenCaptureCamera.open("http://" + m_ip + "/stream.mjpeg");
            }
        }
    } break;

    case State::EnteringAddress:
        int cols = 4;
        int rows = 4;
        Vector2 center = { 400.0f, 400.0f };
        static Vector2 buttonSize = { 120.0f, 80.0f };
        static float buttonSpacing = 10.0f;
        Vector2 topLeft = center - Vector2 { ((cols - 1) / 2.0f) * (buttonSize.x + buttonSpacing), ((rows - 1) / 2.0f) * (buttonSize.y + buttonSpacing) };
        static int textSize = 30;

        ImGui::Text("Number buttons");
        ImGui::DragFloat2("Button size", (float*)&buttonSize);
        ImGui::DragFloat("Button spacing", &buttonSpacing);
        ImGui::DragInt("Button text size", &textSize);

        static std::string buttonNames[] = {
            "7",
            "8",
            "9",
            "C",
            "4",
            "5",
            "6",
            ":",
            "1",
            "2",
            "3",
            ".",
            "",
            "0",
            "",
            "Ok",
        };

        for (int x = 0; x < cols; x++) {
            for (int y = 0; y < rows; y++) {
                std::string& name = buttonNames[y * rows + x];
                if (name == "")
                    continue;

                if (Ui::RoundedButton(name, topLeft + Vector2 { (buttonSize.x + buttonSpacing) * x, (buttonSize.y + buttonSpacing) * y }, buttonSize, textSize)) {

                    if (name == "Ok")
                        m_state = State::Default;
                    else if (name == "C")
                        m_ip.clear();
                    else
                        m_ip += name;
                }
            }
        }

        Color backgroundColor = GetColor(GlobalOutputs::black);
        Color borderColor = GetColor(GlobalOutputs::gray);
        Vector2 size = { (buttonSize.x + buttonSpacing) * cols, buttonSize.y };
        Vector2 outputCenter = { center.x, topLeft.y - buttonSize.y - buttonSpacing };
        Renderer::submitRoundedBorderBox(outputCenter, size, 0.0f, size.y / 2.0f, 2.0f, backgroundColor, borderColor);
        Renderer::submitText(outputCenter, m_ip, textSize, GetColor(GlobalOutputs::white));

        break;
    }
}