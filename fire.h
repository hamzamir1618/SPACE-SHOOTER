#ifndef FIRE_H
#define FIRE_H
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
using namespace sf;

class Fire
{
public:
    int x, y;
    int fTime;
    int dir_x, dir_y;
    Texture tex;
    Sprite sprite;

    Fire(int x, int y, int newdirx, int newdiry)
    {
        
        sprite.setPosition(x, y);
        sprite.setScale(0.75, 0.75);
        //sprite.rotate(270);
        dir_x = newdirx;
        dir_y = newdiry;
        fTime = 0;
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