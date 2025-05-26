#include "AccelerateEnemy.hpp"
#include "Engine/Resources.hpp"
#include <random>
AccelerateEnemy::AccelerateEnemy(int x, int y)
    : Enemy("play/nothing.png", x, y, 30, 50,50, 10)  
    , head("play/enemy-9.png",x,y)
    , maxHp(hp)      // hp 是從 Enemy 建構式帶入的初始值
    , accelerated(false)
{}

void AccelerateEnemy::Draw() const{
    Enemy::Draw();
    head.Draw();
}

void AccelerateEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    // 若血量低於 40% 且尚未加速，則速度翻倍
    if (!accelerated && hp < maxHp * 0.1f) {
        baseSpeed *= 5.0f;  // 提高基礎速度
        speed      *= 5.0f;  // 馬上套用到當前速度
        accelerated = true;
        head.bmp = Engine::Resources::GetInstance().GetBitmap("play/enemy-10.png");
        
    }
    head.Position = Position;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(0.0f, 4.0f);
    float rnd = dist(rng);
    if (rnd < deltaTime) {
        // Head arbitrary rotation.
        std::uniform_real_distribution<> distRadian(-ALLEGRO_PI, ALLEGRO_PI);
        targetRotation = distRadian(rng);
    }
    head.Rotation = (head.Rotation + deltaTime * targetRotation) / (1 + deltaTime);
    if(accelerated) head.bmp = Engine::Resources::GetInstance().GetBitmap("play/enemy-10.png");
    // 呼叫基底進行路徑、緩速、移動等邏輯
    
}