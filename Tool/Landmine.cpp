
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <utility>
#include <math.h>
#include "Enemy/Enemy.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
//#include "Engine/IObject.hpp"
//#include "Engine/IScene.hpp"
//#include "Engine/Point.hpp"
#include "Scene/PlayScene.hpp"
#include "Landmine.hpp"

PlayScene* Landmine::getPlayScene() {
    return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
const int Landmine::Price = 1000;
// 簡化後的建構子，固定傷害、半徑和時間
Landmine::Landmine(std::string img, float x, float y)
    : Sprite(img, x, y),
      countdown(1.0f),    // 時間設為1
      explosionRadius(100.0f), // 半徑設為100
      damage(1000)            // 傷害設為1000
{}

void Landmine::Update(float deltaTime) {
    if (!Enabled) return;
    countdown -= deltaTime;
    if (countdown <= 0) {
        Explode();
        countdown--;
    }
}

void Landmine::Explode() {
    PlayScene* scene = getPlayScene();
    for (auto& it : scene->EnemyGroup->GetObjects()) {
        Enemy* enemy = dynamic_cast<Enemy*>(it);
        float disx = std::abs(Position.x - enemy->Position.x); // 使用 float 提高精度
        float disy = std::abs(Position.y - enemy->Position.y); // 使用 float 提高精度
        float dis = std::sqrt(disx * disx + disy * disy);     // 使用 float 計算距離
        if (dis <= explosionRadius) {
            enemy->Hit(damage);
        }
        //damage = 0;
    }
    // 移除地雷（目前註解中，視需求可啟用）
    scene->UIGroup->RemoveObject(GetObjectIterator());
}