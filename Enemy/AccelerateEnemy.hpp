#ifndef ACCELERATEENEMY_HPP
#define ACCELERATEENEMY_HPP

#include "Enemy.hpp"
#include "Engine/Sprite.hpp"

class AccelerateEnemy : public Enemy {
public:
    // x, y: 初始位置；其餘參數傳給基底 Enemy
    AccelerateEnemy(int x, int y);
    // 每幀更新時檢查是否需觸發加速
    void Update(float deltaTime) override;
    void Draw() const override;

private:
    float maxHp;       // 紀錄初始最大生命
    bool accelerated;  // 是否已經觸發過加速
    Sprite head;
    float targetRotation;
};

#endif  // ACCELERATEENEMY_HPP