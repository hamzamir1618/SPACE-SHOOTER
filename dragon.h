#ifndef DRAGON_H
#define DRAGON_H
#include "bullet.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class Dragon
{
public:
    // Bomb *bum;
    float x, y, dir_x, dir_y, health;
    Texture tex;
    Sprite sprite;
    Bullet **beam;
    int beamSize;
    bool reach;

    Dragon(string png_path, float newdirx, float newdiry)
    {
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        // x+=27;
        sprite.setPosition(200, -500);
        sprite.setScale(0.2, 0.2);
        //sprite.rotate(180);
        dir_x = newdirx;
        dir_y = newdiry;
        beamSize = 100;
        reach = false;
        beam = new Bullet *[beamSize];
        for (int a = 0; a < beamSize; a++)
        {
            beam[a] = nullptr;
        }
    }

    void update(int posx, int posy)
    {
        float nx, ny;
        nx = ny = 0;
        if (posy < 50)
            ny += dir_y;
        if (posy == 50 && posy < 75 && posx < 470)
            nx += dir_x;
        else if (posy <= 75 && posy >= 50)
        {
            ny += dir_y;
            nx -= dir_x;
        }
        else if (posy >= 75 && posx > -500)
            nx -= dir_x;

        sprite.move(nx * 0.1, ny * 0.1);
    }

    void initiateFire()
    {
        string png_path = "img/monsterBeamGreen.png";
        for (int a = 0; a < beamSize; a++)
        {
            if (beam[a] == nullptr)
            {
                beam[a] = new Bullet(png_path, sprite.getPosition().x, sprite.getPosition().y, 0, 3, 90);

                beam[a]->sprite.setPosition(beam[a]->sprite.getPosition().x + 185, beam[a]->sprite.getPosition().y + 20);
                break;
            }
        }
    }
};

#endif