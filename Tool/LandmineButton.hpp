#ifndef LANDMINEBUTTON_HPP
#define LANDMINEBUTTON_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include "UI/Component/ImageButton.hpp"
#include "Engine/Sprite.hpp"

class PlayScene;

class LandmineButton : public Engine::ImageButton {
public:
    LandmineButton(std::string img, std::string imgIn, Engine::Sprite Base, Engine::Sprite MineIcon, float x, float y, int money);
    void Update(float deltaTime) override;
    void Draw() const override;
    int money;
private:
    Engine::Sprite Base, MineIcon;
    PlayScene* getPlayScene();
};

#endif // LANDMINEBUTTON_HPP