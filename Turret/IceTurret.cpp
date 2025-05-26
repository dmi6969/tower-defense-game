#include <allegro5/base.h>
#include <cmath>
#include <string>

//#include "Bullet/FireBullet.hpp"
#include "Bullet/IceBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "IceTurret.hpp"
#include "Scene/PlayScene.hpp"

const int IceTurret::Price = 250;
IceTurret::IceTurret(float x, float y)
    : Turret("play/tower-base.png", "play/turret-3.png", x, y, 100, Price, 0.5) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void IceTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    getPlayScene()->BulletGroup->AddNewObject(new IceBullet(Position + normalized * 36, diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
}
