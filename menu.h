
#include "game.h"
class Menu{
public: 
Sprite menuBackground; //Menu background sprite
Texture menu_texture;
Texture alphabetTex[26];
Sprite *alphabetSprite; 
Sprite *titleSprite; 
Sprite *entSprite;

//add menu attributes here
Menu()
{
    for(int a=0;a<26;a++)
    {
        string path="Alphabets/";
        path+= (char)(a + 'a');
        path+=".png";
        alphabetTex[a].loadFromFile(path);
    } 

    menu_texture.loadFromFile("img/backgroundneo3.jpg");
    menuBackground.setTexture(menu_texture);

}

void display_menu()

{

    RenderWindow window(VideoMode(780, 702), title);
    Clock clock;
    float timer=0;


    Game g; 
//display menu screen here

// add functionality of all the menu options here

//if Start game option is chosen 
string name="";
string title="SPACE SHOOTER OMEGA"; 
string prompt="ENTER YOUR NAME";
while(window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds(); 
        clock.restart();
        Event e;
        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            break;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            name+=' ';
            while(Keyboard::isKeyPressed(Keyboard::Space));
        } 
        else if (Keyboard::isKeyPressed(Keyboard::BackSpace))
        {
            if(name!="")
            {
                string temp="";
                for(int a=0;a<name.length()-1;a++)
                {
                    temp+=name[a];
                }
                name=temp;
            }
            while(Keyboard::isKeyPressed(Keyboard::Backspace));
        } 
        if(name.length()<10)
        {
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                name+='A';
                while(Keyboard::isKeyPressed(Keyboard::A));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::B))
            {
                name+='B';
                while(Keyboard::isKeyPressed(Keyboard::B));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::C))
            {
                name+='C';
                while(Keyboard::isKeyPressed(Keyboard::C));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::D))
            {
                name+='D';
                while(Keyboard::isKeyPressed(Keyboard::D));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::E))
            {
                name+='E';
                while(Keyboard::isKeyPressed(Keyboard::E));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::F))
            {
                name+='F';
                while(Keyboard::isKeyPressed(Keyboard::F));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::G))
            {
                name+='G';
                while(Keyboard::isKeyPressed(Keyboard::G));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::H))
            {
                name+='H';
                while(Keyboard::isKeyPressed(Keyboard::H));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::I))
            {
                name+='I';
                while(Keyboard::isKeyPressed(Keyboard::I));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::J))
            {
                name+='J';
                while(Keyboard::isKeyPressed(Keyboard::J));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::K))
            {
                name+='K';
                while(Keyboard::isKeyPressed(Keyboard::K));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::L))
            {
                name+='L';
                while(Keyboard::isKeyPressed(Keyboard::L));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::M))
            {
                name+='M';
                while(Keyboard::isKeyPressed(Keyboard::M));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::N))
            {
                name+='N';
                while(Keyboard::isKeyPressed(Keyboard::N));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::O))
            {
                name+='O';
                while(Keyboard::isKeyPressed(Keyboard::O));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::P))
            {
                name+='P';
                while(Keyboard::isKeyPressed(Keyboard::P));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::Q))
            {
                name+='Q';
                while(Keyboard::isKeyPressed(Keyboard::Q));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::R))
            {
                name+='R';
                while(Keyboard::isKeyPressed(Keyboard::R));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::S))
            {
                name+='S';
                while(Keyboard::isKeyPressed(Keyboard::S));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::T))
            {
                name+='T';
                while(Keyboard::isKeyPressed(Keyboard::T));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::U))
            {
                name+='U';
                while(Keyboard::isKeyPressed(Keyboard::U));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::V))
            {
                name+='V';
                while(Keyboard::isKeyPressed(Keyboard::V));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::W))
            {
                name+='W';
                while(Keyboard::isKeyPressed(Keyboard::W));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::X))
            {
                name+='X';
                while(Keyboard::isKeyPressed(Keyboard::X));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::Y))
            {
                name+='Y';
                while(Keyboard::isKeyPressed(Keyboard::Y));
            } 
            else if (Keyboard::isKeyPressed(Keyboard::Z))
            {
                name+='Z';
                while(Keyboard::isKeyPressed(Keyboard::Z));
            } 
        }
        window.clear(Color::Black); 
        window.draw(menuBackground);  // setting background

        titleSprite=new Sprite[title.length()];
        for(int i=0;i<title.length();i++)
        {
            if(title[i]!=' ')
            {
                titleSprite[i].setTexture(alphabetTex[title[i]-'A']);
                titleSprite[i].scale(1,1);
                titleSprite[i].setPosition((i*30)+125,52);
                window.draw(titleSprite[i]);
            }
            // alphabetSprite[a].setPosition(0,0);a
        } 

        entSprite=new Sprite[prompt.length()];
        for(int a=0;prompt[a];a++)
        {
            if(prompt[a]!=' ')
            {
                entSprite[a].setTexture(alphabetTex[prompt[a]-'A']);
                entSprite[a].scale(0.5,0.5);
                entSprite[a].setPosition((a*30)+20,250);
                window.draw(entSprite[a]);
            }
            // alphabetSprite[a].setPosition(0,0);a
        }

        //cout<<name<<endl;
        //timer++;
    	//window.display();  //Displying all the sprites
         

        alphabetSprite=new Sprite[name.length()];
        for(int a=0;name[a];a++)
        {
            if(name[a]!=' ')
            {
                alphabetSprite[a].setTexture(alphabetTex[name[a]-'A']);
                alphabetSprite[a].scale(0.5,0.5);
                alphabetSprite[a].setPosition((a*30)+235,310);
                window.draw(alphabetSprite[a]);
            }
            // alphabetSprite[a].setPosition(0,0);a
        }

//        cout<<name<<endl;
        timer++;
    	window.display();  //Displaying all the sprites
        delete[] titleSprite; 
        delete[]entSprite;
        delete[] alphabetSprite;

     
     }

    g.start_game(window,clock,timer,name);

}


};
