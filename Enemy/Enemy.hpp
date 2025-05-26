#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <list>
#include <string>
#include <vector>

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

class Bullet;
class PlayScene;
class Turret;


class Enemy : public Engine::Sprite {
protected:
    std::vector<Engine::Point> path;
    float speed;
    float baseSpeed;           // original speed for reset
    float slowDuration = 0.0f; // remaining slow effect time
    float slowFactor = 1.0f;   // current slow factor
    float hp;
    int money;
    PlayScene *getPlayScene();
    virtual void OnExplode();
    float maxHp;               // New: Maximum health
    bool isLowHealth = false;  // New: Flag for low-health state
    std::string lowHealthImg;  // New: Path to low-health image

public:
    void Slow(float factor, float duration);
    float reachEndTime;
    std::list<Turret *> lockedTurrets;
    std::list<Bullet *> lockedBullets;
    Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money);
    void Hit(float damage);
    void ApplyBurn(int dps, float duration);
    void UpdatePath(const std::vector<std::vector<int>> &mapDistance);
    void Update(float deltaTime) override;
    void Draw() const override;
    //ALLEGRO_BITMAP *bmpSlowedLowHP;
};
#endif   // ENEMY_HPP
