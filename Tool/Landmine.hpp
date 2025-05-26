#ifndef LANDMINE_HPP
#define LANDMINE_HPP

#include <string>
//#include "Engine/Sprite.hpp"
#include <allegro5/base.h>
#include <list>
#include <string>
class PlayScene;

class Landmine : public Engine::Sprite {
public:
    Landmine(std::string img, float x, float y);
    void Update(float deltaTime) override;
    void Explode();
    PlayScene* getPlayScene();
    static const int Price;
    bool Enabled = true;
    bool Preview = false;
protected:

    float countdown;
    float explosionRadius;
    int damage;
    
};

#endif // LANDMINE_HPP
