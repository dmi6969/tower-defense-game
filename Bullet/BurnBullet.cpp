// #include <random>
// #include <string>
// #include "Enemy/Enemy.hpp"
// #include "Engine/Group.hpp"
// #include "Engine/Point.hpp"
// #include "BurnBullet.hpp"
// #include "Scene/PlayScene.hpp"
// #include "UI/Animation/DirtyEffect.hpp"

// FireBullet::FireBullet(Engine::Point position,
//                        Engine::Point forwardDirection,
//                        float rotation,
//                        Turret* parent)
//     : Bullet(
//         "play/bullet-3.png",  // 子彈圖
//         600,                     // 速度（略慢於雷射）
//         1,                       // 直擊傷害（可調）
//         position,
//         forwardDirection,
//         rotation - ALLEGRO_PI / 2,
//         parent) {
// }

// void FireBullet::OnExplode(Enemy* enemy) {
//     // 1) 造成一次基礎傷害
//     //enemy->Hit(Parent->GetAttackDamage());

//     // 2) 套用灼傷：BurnDPS 每秒，持續 BurnDuration 秒
//     enemy->ApplyBurn(BurnDPS, BurnDuration);

//     // 3) 隨機尺寸、隨機幀數的火焰地面特效
//     std::random_device dev;
//     std::mt19937 rng(dev());
//     std::uniform_int_distribution<int> dist(2, 6);

//     auto scene = getPlayScene();
//     scene->GroundEffectGroup->AddNewObject(
//         new DirtyEffect("play/dirty-fire.png",  // 假設用火焰素材
//                         dist(rng),              // 隨機幀數
//                         enemy->Position.x,
//                         enemy->Position.y));

// }