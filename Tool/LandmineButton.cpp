#include <allegro5/color.h>
#include "Engine/GameEngine.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "LandmineButton.hpp"

PlayScene* LandmineButton::getPlayScene() {
    return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

LandmineButton::LandmineButton(std::string img, std::string imgIn, Engine::Sprite Base, Engine::Sprite MineIcon, float x, float y, int money)
    : ImageButton(img, imgIn, x, y), money(money), Base(Base), MineIcon(MineIcon) {
}

void LandmineButton::Update(float deltaTime) {
    ImageButton::Update(deltaTime);


    if (getPlayScene()->GetMoney() >= money) {
        Enabled = true;
        Base.Tint = MineIcon.Tint = al_map_rgba(255, 255, 255, 255);
    } else {
        Enabled = false;
        Base.Tint = MineIcon.Tint = al_map_rgba(0, 0, 0, 160);
    }
}

void LandmineButton::Draw() const {
    ImageButton::Draw();
    Base.Draw();
    MineIcon.Draw();
}