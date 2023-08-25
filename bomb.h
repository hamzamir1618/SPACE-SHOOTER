#ifndef BOMB_H
#define BOMB_H
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
using namespace sf;

class Bomb
{
public:
    int x, y;
    int bTime;
    int dir_x, dir_y;
    Texture tex;
    Sprite sprite;

    Bomb(int x, int y, int newdirx, int newdiry)
    {
        tex.loadFromFile("img/player_laser.png");
        sprite.setTexture(tex);
        // x+=27;
        sprite.setPosition(x, y);
        sprite.setScale(0.75, 0.75);
        sprite.rotate(270);
        dir_x = newdirx;
        dir_y = newdiry;
        bTime = 0;
    }
    void update()
    {
        int nx, ny;
        nx = ny = 0;
        nx += dir_x;
        ny += dir_y;
        sprite.move(nx * 0.1, ny * 0.1);
    }
};
#endif