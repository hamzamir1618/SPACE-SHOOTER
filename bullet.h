#ifndef BULLET_H
#define BULLET_H
#include <string.h>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class Bullet
{
public:
    int x, y;
    float dir_x, dir_y;
    Texture tex;
    Sprite sprite;

    Bullet(string png_path, int x, int y, float newdirx, float newdiry, int rotat)
    {
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        // x+=27;
        sprite.setPosition(x, y);
        sprite.setScale(0.75, 0.75);
        /*  if (monster)
              sprite.rotate(90);
          else*/
        sprite.rotate(rotat);

        dir_x = newdirx;
        dir_y = newdiry;
    }
    void update()
    {
        int nx, ny;
        nx = ny = 0;
        nx += dir_x;
        ny += dir_y;
        sprite.move(nx * 0.5, ny * 0.5);
    }
};
#endif