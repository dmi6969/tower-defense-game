#ifndef ICETURRET_HPP
#define ICETURRET_HPP
#include "Turret.hpp"

class IceTurret : public Turret {
public:
    static const int Price;
    IceTurret(float x, float y);
    void CreateBullet() override;
};
#endif   // MACHINEGUNTURRET_HPP