#include <allegro5/base.h>
#include "Enemy/Enemy.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "IceBullet.hpp"
#include "Scene/PlayScene.hpp"
#include "UI/Animation/DirtyEffect.hpp"

IceBullet::IceBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret *parent)
    : Bullet(
        "play/bullet-11.png",   // 子彈貼圖（請自行準備對應資源）
        400,                      // 速度：比普通子彈稍慢
        1,                        // 傷害值
        position,
        forwardDirection,
        rotation - ALLEGRO_PI / 2,
        parent
      )
{ }

void IceBullet::OnExplode(Enemy *enemy) {
    // 1. 對敵人造成減速效果：速度降低至原速的 50%，持續 2 秒
    constexpr float slowFactor = 0.5f;
    constexpr float slowDuration = 2.0f;
    enemy->Slow(slowFactor, slowDuration);

    // 2. 在碰撞位置生成冰霜特效
    //    DirtyEffect 可重複使用，參數分別為：貼圖、持續幀數、X, Y
    getPlayScene()->GroundEffectGroup->AddNewObject(
        new DirtyEffect("play/dirty-1.png", 4, enemy->Position.x, enemy->Position.y)
    );
}