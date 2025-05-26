#include <algorithm>
#include <string>

#include "Engine/Point.hpp"
#include "Slider.hpp"

Slider::Slider(float x, float y, float w, float h)
    : ImageButton("stage-select/slider.png", "stage-select/slider-blue.png", x, y),
      Bar("stage-select/bar.png", x, y, w, h),
      End1("stage-select/end.png", x, y + h / 2, 0, 0, 0.5, 0.5),
      End2("stage-select/end.png", x + w, y + h / 2, 0, 0, 0.5, 0.5) {
    Position.x += w / 2;
    Position.y += h / 2;
    Anchor = Engine::Point(0.5, 0.5);
}

void Slider::Draw() const {
    // TODO HACKATHON-5 (3/4): The slider's component should be drawn here.
    ImageButton::Draw();
    //背景條
    Bar.Draw();
    //兩端的圖標
    End1.Draw();
    End2.Draw();
}
void Slider::SetOnValueChangedCallback(std::function<void(float value)> onValueChangedCallback) {
    OnValueChangedCallback = onValueChangedCallback;
}
void Slider::SetValue(float value) {
    // TODO HACKATHON-5 (4/4)
    value = std::min(1.0f, std::max(0.0f, value));
    // 計算滑桿按鈕的 x
    Position.x = Bar.Position.x + value * Bar.Size.x;
    // 呼叫回調函數（如果已設置）
    if (OnValueChangedCallback) {
        OnValueChangedCallback(value);
    }
}
void Slider::OnMouseDown(int button, int mx, int my) {
    if ((button & 1) && mouseIn)
        Down = true;
}
void Slider::OnMouseUp(int button, int mx, int my) {
    Down = false;
}
void Slider::OnMouseMove(int mx, int my) {
    ImageButton::OnMouseMove(mx, my);
    if (Down) {
        // Clamp
        float clamped = std::min(std::max(static_cast<float>(mx), Bar.Position.x), Bar.Position.x + Bar.Size.x);
        float value = (clamped - Bar.Position.x) / Bar.Size.x * 1.0f;
        SetValue(value);
    }
}
