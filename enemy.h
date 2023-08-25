#include <SFML/Graphics.hpp>
#include "bomb.h"
#include "enemyWave.h"
#include "monster.h" 
#include "dragon.h"
#include <string.h>

using namespace sf;
class Enemy
{
public:
    Texture tex, exptex;
    Sprite sprite, expsprite;
    int deltashift, enemyTroops;
    float frameTime;
    enemyWave **enemyArray;
    Monster *monster; 
    Dragon *dragon;
    // Bomb *bum;
    float speed = 0.1;
    int x, y, health;
    Enemy(std::string png_path)
    {
        health = 3;
        monster = nullptr; 
        dragon = nullptr;

        enemyTroops = 22;
        enemyArray = new enemyWave *[1000];
        for (int a = 0; a < 1000; a++)
        {
            enemyArray[a] = nullptr;
        }
        //  bum= nullptr;
        deltashift = 2;
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        x = 100;
        y = 100;
        // x=340;y=700;
        sprite.setPosition(x, y);
        sprite.setScale(0.75, 0.75);
        frameTime = 0.5f;
        exptex.loadFromFile("img/explosion.png");
        //      monster.setMonster("img/monster1.png",3,3);
    }

    void removeHim(int index)
    {
        if (index != enemyTroops - 1)
        {
            delete enemyArray[index];
            for (int a = index; a < enemyTroops - 1; a++)
            {
                enemyArray[a] = enemyArray[a + 1];
            }
        }
        else
        {
            delete enemyArray[enemyTroops - 1];
        }
        enemyArray[enemyTroops - 1] = nullptr;
        enemyTroops--;
    }

    void move(std::string s)
    {
        float delta_x = 0, delta_y = 0;
        // if(s=="l")
        // move the player left
        // else if(s=="r")
        // move the player right
        if (s == "u")
            delta_y = -deltashift;
        else if (s == "d")
            delta_y = deltashift;
        else if (s == "l")
            delta_x = -deltashift;
        else if (s == "r")
            delta_x = deltashift;

        delta_x *= speed;
        delta_y *= speed;
        sprite.move(delta_x, delta_y);
    }

    void initiateWave()
    {
        string png_path;
        int x = rand();
        x %= 3;

        for (int a = 0; a < enemyTroops; a++)
        {
            x %= 3;
            switch (x)
            {
            case 0:
                png_path = "img/enemy_shipnew.png";
                /* code */
                break;
            case 1:
                png_path = "img/betaenemy.png";
                break;
            case 2:
                png_path = "img/gammaenemy3.png";

            default:
                break;
            }
            if (enemyArray[a] == nullptr)

            {
                enemyArray[a] = new enemyWave(png_path, sprite.getPosition().x, sprite.getPosition().y, 3, 3);

                enemyArray[a]->sprite.setPosition(enemyArray[a]->sprite.getPosition().x, enemyArray[a]->sprite.getPosition().y);
                break;
            }
        }
    }

    void initiateMonster()
    {
        if (monster == nullptr)
            monster = new Monster("img/monster1.png", 3, 3);
    }

    IntRect explosion(float timer, IntRect texrect, RenderWindow &window, int x, int y)
    {
        if (timer >= frameTime)
            texrect.left += 138;
        expsprite.setTextureRect(texrect);
        expsprite.setPosition(x, y);
        window.draw(expsprite);
        return texrect;
    }
};