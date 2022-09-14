#pragma once
#include "Character.h"


class Enemy :
    public Creature
{
private:
    
    bool mGotGoal = false;
    bool mIsClose = false;
    bool mISeeYou = false;
    int mViewRange = 500;
    int mMovSpeed = 2;
    int mGoalPostX;
    int mGoalPostY;

public:
    Enemy(int hp, int xCord, int yCord, char type);

    void draw();
    void move(int dir);
    void setMoveDir();

    void monitor(const Character& player);

    bool detect(const Character& player);
    void follow(const Character& player);
    bool face(const Character& player);
    Bullet* attack(const Character& player);
    void setGoal();
    void setGoal(const Character& player);

    bool getSight() const;
};

