#pragma once
#include "Terrain.h"
class DestroyableTerrain :
    public Terrain
{
private:
    bool mIsTraversable;
    int mHp;

public:
    DestroyableTerrain();

    void damage(int dmg);

};

