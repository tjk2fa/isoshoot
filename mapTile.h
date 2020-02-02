//
// Created by Tom on 1/31/20.
//

#ifndef GAME_MAPTILE_H
#define GAME_MAPTILE_H
#include <vector>
class Entity;


class mapTile {
    public:
        std::vector<Entity*> entities;
        bool empty;
};


#endif //GAME_MAPTILE_H
