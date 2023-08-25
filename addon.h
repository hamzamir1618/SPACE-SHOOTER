#include <SFML/Graphics.hpp> 
#include "lifedrop.h"  
#include "powerup.h" 
#include "fire.h"
using namespace sf; 
using namespace std;
class Addons{
public: 
LifeDrop *lifedrop; 
PowerUp *powerup;
Fire *fire;
float x,y,dir_x,dir_y; 
//Texture tex;
//Sprite sprite;
Addons(){
    lifedrop= nullptr; 
    powerup=nullptr; 
    fire=nullptr;

}
 void initiateLifeDrops() {
        if (lifedrop==nullptr)
        {   int x= rand() % 711 + 10,y=-20;
            lifedrop=new LifeDrop(x,y,0,2);
            lifedrop->tex.loadFromFile("img/life gem heart.png");
            lifedrop->sprite.setTexture(lifedrop->tex); 
            lifedrop->sprite.scale(0.09,0.09);
            //bum->sprite.rotate(180);
            lifedrop->dTime=rand();
            lifedrop->dTime%=5000;
        }
    } 

     void initiatePowerupDrops() {
        if (powerup==nullptr)
        {   int x= rand() % 711 + 10,y=-20;
            powerup=new PowerUp(x,y,0,2);
            powerup->tex.loadFromFile("img/powerup.png");
            powerup->sprite.setTexture(powerup->tex); 
            powerup->sprite.scale(0.3,0.3);
            //bum->sprite.rotate(180);
            powerup->pTime=rand();
            powerup->pTime%=30000;
        }
    } 

    void initiateFireDrops() {
        if (fire==nullptr)
        {   int x= rand() % 711 + 10,y=-20;
            fire=new Fire(x,y,0,2);
            fire->tex.loadFromFile("img/firedrop.png");
            fire->sprite.setTexture(fire->tex); 
            fire->sprite.scale(0.3,0.3);
            //bum->sprite.rotate(180);
            fire->fTime=rand();
            fire->fTime%=10000;
        }
    }


};