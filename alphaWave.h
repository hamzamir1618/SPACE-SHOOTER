#ifndef ALPHAENEMY_H
#define ALPHAENEMY_H
#include "bomb.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class AlphaWave{
public: 
Bomb *bum;
float x,y,dir_x,dir_y,health; 
Texture tex;
Sprite sprite;


AlphaWave(string png_path, int x, int y,float newdirx, float newdiry)
{   health=3;
    bum= nullptr;
    tex.loadFromFile(png_path);
    sprite.setTexture(tex);
    // x+=27;
    sprite.setPosition(x,y);
    sprite.setScale(0.065,0.065);
    sprite.rotate(180);
    dir_x=newdirx;
    dir_y=newdiry;
}
// 

void update(int posx,int posy,int phaseNumber)
{
    float nx, ny;
    nx=ny=0; 
//*********** R E C T A N G L E ***********************************
if (phaseNumber==1){
    if (posy==100 && posy<300 && posx<720) 
    nx+=dir_x; 
    else if (posy<300 && posx==720) 
    ny+=dir_y; 
    else if (posx>100 && posy==300) 
    nx-=dir_x; 
    else if (posx==100&& posy<=300&&posy>100)  
    ny-=dir_y; 
} 
//*********** T R I A N G L E ************************************* 
else if (phaseNumber==2){
    if (posy==100 && posy<400 && posx<720) 
    nx+=dir_x; 
    else if (posy<400 && posx>390) 
    {ny+=dir_y; 
    nx-=dir_x;} 
    else if (posy>100 && posx>=10) 
    {ny-=dir_y; 
    nx-=dir_x;}  
} 

//*********** D I A M O N D *************************************** 
 
else if (phaseNumber==3){ 
    dir_y=1.5;
    if (posy==100 && posx<=390) 
    nx+=dir_x; 
    else if (posx>=390 && posx<740 &&posy<300) 
    {ny+=dir_y; 
    nx+=dir_x;} 
    else if (posx>390 && posx<=740 &&posy<500) 
    {ny+=dir_y; 
    nx-=dir_x;} 
    else if (posx>90 && posx<=390 && posy<500 && posy>200) 
    {ny-=dir_y; 
    nx-=dir_x;} 
    else if (posx>=80 && posx<390 &&posy>100) 
    {ny-=dir_y; 
    nx+=dir_x;} 
}

//*****************************************************************
    sprite.move(nx*0.1, ny*0.1);
} 
//*****************************************************************
  void initiateBullets() {
        if (bum==nullptr)
        {
            bum=new Bomb(sprite.getPosition().x-48,sprite.getPosition().y-15,0,2);
            bum->tex.loadFromFile("img/dushman_bum.png");
            bum->sprite.setTexture(bum->tex); 
            bum->sprite.scale(0.35,0.35);
            //bum->sprite.rotate(180);
            bum->bTime=rand();
            bum->bTime%=5000;
        }
    }

};
#endif