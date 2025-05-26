#ifndef ICEBULLET_HPP
#define ICEBULLET_HPP

#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine { struct Point; }

/// 冰凍子彈：撞擊時對敵人造成減速並在地面產生冰霜特效
class IceBullet : public Bullet {
public:
    /// \param position 發射起點
    /// \param forwardDirection 子彈行進方向
    /// \param rotation 子彈初始旋轉角度
    /// \param parent 所屬砲塔指標
    explicit IceBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret *parent);

    /// 撞擊效應：對敵人減速並生成冰霜特效
    void OnExplode(Enemy *enemy) override;
};

#endif  // ICEBULLET_HPP