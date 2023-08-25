#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class Life
{
public:
    int lives;
    Texture tex;
    Sprite sprite;
    Life()
    {
        lives = 3;
        tex.loadFromFile("img/life-heart.png");
        sprite.setTexture(tex); 
        sprite.setScale(0.05,0.05);
    }
    void addLife()
    {
        if (lives < 3)
            lives++;
    }

    bool death()
    {
        lives--;
        if (lives <= 0)
            return true;

        return false;
    } 
    void displayLives(RenderWindow &window){ 
        /*for (int i=0,k=720;i<lives;i++,k-10){ 
            sprite.setPosition(k,0);
            window.draw(sprite);
        }*/  
        if (lives==3){
        sprite.setPosition(720,0);
        window.draw(sprite);  
        sprite.setPosition(670,0);
        window.draw(sprite);  
        sprite.setPosition(620,0);
        window.draw(sprite);} 
        else if (lives==2){
        sprite.setPosition(720,0);
        window.draw(sprite);  
        sprite.setPosition(670,0);
        window.draw(sprite); }
        else if (lives==1){
        sprite.setPosition(720,0);
        window.draw(sprite);}  

    } 
};