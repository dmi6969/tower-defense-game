// #pragma once
// #include "Bullet.hpp"

// class Turret;
// class Enemy;

// class FireBullet : public Bullet {
// public:
//     // position: 子彈初始位置
//     // forwardDirection: 前進單位向量
//     // rotation: 子彈朝向（弧度）
//     // parent: 所屬砲塔指標
//     FireBullet(Engine::Point position,
//                Engine::Point forwardDirection,
//                float rotation,
//                Turret* parent);

//     // 撞到敵人時觸發：套用灼傷，並在地面放火焰特效
//     virtual void OnExplode(Enemy* enemy) override;

// private:
//     // 灼傷參數
//     static constexpr int BurnDPS = 5;
//     static constexpr float BurnDuration = 5.0f;
// };