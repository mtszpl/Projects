#pragma once
#include "creature.h"
class Character :
    public Creature
{
public:
    static Character& getInstance();

    Character();

    void move(const ALLEGRO_KEYBOARD_STATE key);

};

