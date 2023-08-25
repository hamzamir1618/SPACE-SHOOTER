
#include <SFML/Graphics.hpp>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "point.h"
#include "player.h"
#include "enemy.h"
#include "monster.h"
#include "phase.h"
#include "addon.h"
#include <fstream>

bool checkCollision(const Sprite &sprite1, const Sprite &sprite2, int r);
void playAnimation(RenderWindow &, const string &, const int);
void displayText(RenderWindow &, const string &, int, int, int);
void initiateLifeDrops(LifeDrop *);

const char title[] = "Space Shooter Omega";

using namespace sf;
using namespace std;

class Game
{
public:
	string name;
	bool pause, end, over, monster1, monsterBeam, dragon1, dragonFire;
	Sprite background; // Game background sprite
	Texture bg_texture;
	Sprite pauseIcon;
	Texture pauseTex;
	Phase phase;
	Monster *monster;
	Addons *addon;
	int fireframe, enemySpeed, hits, addonInterval, timefire, timepowerup;
	Player *p; // player
	// add other game attributes
	Enemy *dushman;

	Game()
	{
		monster = nullptr;
		p = new Player("img/player_shipnew.png", "img/playershipnew.png");
		// p->sprite.scale(0.07,0.07);
		bg_texture.loadFromFile("img/backgroundnew4.png");
		background.setTexture(bg_texture);
		end = pause = over = monster1 = monsterBeam = dragon1 = dragonFire = false;
		hits = enemySpeed = fireframe = addonInterval = timefire = timepowerup = 0;
		background.setScale(1, 0.9);
		dushman = new Enemy("img/enemy_shipnew.png");
		// dushman->initiateMonster();
		addon = new Addons();
		dushman->sprite.setPosition(10, 100);
		dushman->sprite.scale(0.09, 0.09);
		dushman->sprite.rotate(180);
		pauseTex.loadFromFile("img/pauseIcon.png");
		pauseIcon.setTexture(pauseTex);
		pauseIcon.setPosition(300, 250);
		pauseIcon.scale(0.09, 0.09);

		// lifedrop = nullptr;
	}

	void start_game(RenderWindow &window, Clock &clock, float &timer, const string &name)
	{
		srand(time(0));
		IntRect extexrect(0, 0, 138, 138);
		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;
			// cout<<time<<endl;
			Event e;
			while (window.pollEvent(e))
			{
				if (e.type == Event::Closed) // If cross/close is clicked/pressed
					window.close();			 // close the game
			}

			if (!pause)
			{
				if (Keyboard::isKeyPressed(Keyboard::Left))								// If left key is pressed
					p->move("l", p->sprite.getPosition().x, p->sprite.getPosition().y); // Player will move to left
				if (Keyboard::isKeyPressed(Keyboard::Right))							// If right key is pressed
					p->move("r", p->sprite.getPosition().x, p->sprite.getPosition().y); // player will move to right
				if (Keyboard::isKeyPressed(Keyboard::Up))								// If up key is pressed
					p->move("u", p->sprite.getPosition().x, p->sprite.getPosition().y); // playet will move upwards
				if (Keyboard::isKeyPressed(Keyboard::Down))								// If down key is pressed
					p->move("d", p->sprite.getPosition().x, p->sprite.getPosition().y); // player will move downwards
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) // If escape key is pressed
				break;									  // game will exit
			if (Keyboard::isKeyPressed(Keyboard::P))	  // If P is pressed
			{
				if (pause && !over)
					pause = false;
				else
					pause = true;
				while (Keyboard::isKeyPressed(Keyboard::P))
					;
			} // game will pause if playing and resume if paused

			if (!pause) // incrememnting timers
			{
				fireframe++;
				enemySpeed++;
				addonInterval++;
				// if (p->fire)
				timefire++;
				// else if (p->powa)
				timepowerup++;
			}

			if ((timefire % 5000 == 0) && !pause) // timing fire mode
			{
				p->fire = false;
				timefire = 0;
				p->shipSwitch = true;
			}

			if ((timepowerup % 6875 == 0) && !pause) // timing powerup mode
			{
				p->powa = false;
				timepowerup = 0;
				p->shipSwitch = true;
			}

			if (Keyboard::isKeyPressed(Keyboard::Space) && !p->powa)
			{
				if ((fireframe % 100 == 0) && !pause)
					p->initiateBullets();
			}

			else if ((fireframe % 100 == 0) && !pause && p->powa)
				p->initiatePowerupBullets();

			if (end)
			{
				end = false;
				phase.number++;
				if (phase.number == 2)
				{
					dushman->enemyTroops = 17;
				}
				else if (phase.number == 3)
					dushman->enemyTroops = 20;
				else if (phase.number == 4)
					monster1 = true;
				/*else if (phase.number == 5)
					dragon1 = true;*/
			}
			//*********************** INITIATING MOTIONS ******************************
			//*************************************M O N S T E R ************************************************************************************************
			if (monster1 && !pause)
			{
				if (dushman->monster == nullptr)
					dushman->monster = new Monster("img/monster1.png", 1, 1);
			}

			/*if (monster1 && !pause)
			{
				if (dushman->monster == nullptr)
					dushman->monster = new Monster("img/monster1.png", 1, 1);
			}*/

			if (addonInterval % 2000 == 0)
			{
				if (monsterBeam)
					monsterBeam = false;
				else
					monsterBeam = true;
			}

			if ((enemySpeed % 35 == 0) && !pause && dushman->monster != nullptr && monsterBeam && monster1)
				dushman->monster->initiateBullets();

			//************************** D R A G O N ********************************************************************************

			if (dragon1 && !pause)
			{
				if (dushman->dragon == nullptr)
					dushman->dragon = new Dragon("img/monster.png", 1, 1);
			}

			/*if (dragon1 && !pause)
			{
				if (dushman->dragon == nullptr)
					dushman->dragon = new Dragon("img/monster.png", 1, 1);
			}*/

			if (addonInterval % 2000 == 0)
			{
				if (dragonFire)
					dragonFire = false;
				else
					dragonFire = true;
			}

			if ((enemySpeed % 35 == 0) && !pause && dushman->dragon != nullptr && dragonFire && dragon1)
				dushman->dragon->initiateFire();

			//************************************************************************************************************
			if ((enemySpeed % 250 == 0) && !pause)
				dushman->initiateWave();

			if ((addonInterval % 10000 == 0) && !pause)
				addon->initiateLifeDrops();

			if ((addonInterval % 20000 == 0) && !pause)
				addon->initiatePowerupDrops();

			if ((addonInterval % 5000 == 0) && !pause)
				addon->initiateFireDrops();

			//********************************************************************************

			window.clear(Color::Black); // clears the screen
			window.draw(background);	// setting background

			//******************** M O N S T E R *****************************************************************************
			if (dushman->monster != nullptr && monster1)
			{

				if (!pause)
				{
					dushman->monster->update(dushman->monster->sprite.getPosition().x, dushman->monster->sprite.getPosition().y);
				}
			}

			if (dushman->monster != nullptr && monster1)
			{
				if (dushman->monster->sprite.getPosition().x < -300)
				{
					delete dushman->monster;
					dushman->monster = nullptr;
					end = true; 
					monster1=false; 
					dragon1=true;
				}
			}
			//************************************************************************************************

			//******************** D R A G O N *****************************************************************************
			if (dushman->dragon != nullptr && dragon1)
			{

				if (!pause)
				{
					dushman->dragon->update(dushman->dragon->sprite.getPosition().x, dushman->dragon->sprite.getPosition().y);
				}
			}

			if (dushman->dragon != nullptr && dragon1)
			{
				if (dushman->dragon->sprite.getPosition().x < -300)
				{
					delete dushman->dragon;
					dushman->dragon = nullptr;
					end = true;
					dragon1 = false; 
					over=true;
				}
			}

			//************************************************************************************************
			if (addon->lifedrop != nullptr)
			{
				if (!pause)
					addon->lifedrop->update();
				window.draw(addon->lifedrop->sprite);
				if (checkCollision(p->sprite, addon->lifedrop->sprite, 150))
				{
					p->life.addLife();
					addon->lifedrop->sprite.setPosition(1000, 1000);
				}

				if (addon->lifedrop->sprite.getPosition().y > 800 + addon->lifedrop->dTime)
				{
					delete addon->lifedrop;
					addon->lifedrop = nullptr;
				}
			}

			if (addon->powerup != nullptr)
			{
				if (!pause)
					addon->powerup->update();
				window.draw(addon->powerup->sprite);
				if (checkCollision(p->sprite, addon->powerup->sprite, 150))
				{
					p->powa = p->shipSwitch = true;
					p->fire = false;
					addon->powerup->sprite.setPosition(1000, 1000);
				}

				if (addon->powerup->sprite.getPosition().y > 800 + addon->powerup->pTime)
				{
					delete addon->powerup;
					addon->powerup = nullptr;
				}
			}

			if (addon->fire != nullptr)
			{
				if (!pause)
					addon->fire->update();
				window.draw(addon->fire->sprite);
				if (checkCollision(p->sprite, addon->fire->sprite, 150))
				{
					p->fire = true;
					p->powa = false;
					addon->fire->sprite.setPosition(1000, 1000);
				}

				if (addon->fire->sprite.getPosition().y > 800 + addon->fire->fTime)
				{
					delete addon->fire;
					addon->fire = nullptr;
				}
			}

			for (int a = 0; a < dushman->enemyTroops; a++)
			{
				if (dushman->enemyArray[a] != nullptr)
				{
					if (!pause)
						dushman->enemyArray[a]->update(dushman->enemyArray[a]->sprite.getPosition().x,
													   dushman->enemyArray[a]->sprite.getPosition().y,
													   phase.number);
					window.draw(dushman->enemyArray[a]->sprite);

					//**********B O M B  I M P L E M E N T A T I O N***************************************************

					dushman->enemyArray[a]->initiateBullets();
					if (dushman->enemyArray[a]->bum != nullptr)
					{
						if (!pause)
							dushman->enemyArray[a]->bum->update();
						window.draw(dushman->enemyArray[a]->bum->sprite);

						if (checkCollision(p->sprite, dushman->enemyArray[a]->bum->sprite, 90))
						{

							dushman->enemyArray[a]->bum->sprite.setPosition(-1000, 2000);
							if (!p->powa)
							{
								if (p->life.death())
								{
									over = true;
									pause = true;
								}
							}
							break;
						}

						if (dushman->enemyArray[a]->bum->sprite.getPosition().y > 800 + dushman->enemyArray[a]->bum->bTime)
						{
							delete dushman->enemyArray[a]->bum;
							dushman->enemyArray[a]->bum = nullptr;
						}
					}

					//***********************************************************************************************
					if (dushman->enemyArray[a]->sprite.getPosition().y < 0)
					{
						delete dushman->enemyArray[a];
						dushman->enemyArray[a] = nullptr;
					}
				}
			}

			//******************* P L A Y E R  L A S E R S *******************************************************************************

			// cout << "apple" << endl;
			for (int a = 0; a < p->projectilesize; a++)
			{
				if (p->projectile[a] != nullptr)
				{
					if (!pause)
						p->projectile[a]->update();
					window.draw(p->projectile[a]->sprite);

					if (p->projectile[a]->sprite.getPosition().y < 0)
					{
						delete p->projectile[a];
						p->projectile[a] = nullptr;
					}
				}
			}

			for (int a = 0; a < p->projectilesize; a++)
			{
				if (p->projectile[a] == nullptr)
					continue;
				for (int i = 0; i < dushman->enemyTroops; i++)
				{
					if (dushman->enemyArray[i] == nullptr)
						continue;

					// if (p->projectile[a]->sprite.getGlobalBounds().intersects(dushman->enemyArray[i]->sprite.getGlobalBounds()))
					if (checkCollision(p->projectile[a]->sprite, dushman->enemyArray[i]->sprite, 100))
					{
						//                        playAnimation(window, "explosion.png", 4);
						if (p->fire)
							dushman->enemyArray[i]->health = 0;
						else
							dushman->enemyArray[i]->health--;

						if (dushman->enemyArray[i]->health <= 0)
						{
							extexrect = dushman->explosion(timer,
														   extexrect,
														   window,
														   dushman->enemyArray[i]->sprite.getPosition().x,
														   dushman->enemyArray[i]->sprite.getPosition().y);
							dushman->removeHim(i);
							p->score.score += 10;
						}
						if (!p->fire)
						{
							delete p->projectile[a];
							p->projectile[a] = nullptr;
							break;
						}
					}
				}
			}
			if (dushman->enemyTroops == 0)
			{
				end = true;
			}

			//********************************** M O N S T E R ***************************************************************************************

			if (dushman->monster != nullptr)
			{
				for (int a = 0; a < dushman->monster->beamSize; a++)
				{
					if (dushman->monster->beam[a] != nullptr)
					{
						if (!pause)
							dushman->monster->beam[a]->update();
						window.draw(dushman->monster->beam[a]->sprite);

						if (dushman->monster->beam[a]->sprite.getPosition().y > 800)
						{
							delete dushman->monster->beam[a];
							dushman->monster->beam[a] = nullptr;
						}
					}
				}
			}
			//**************************************************************************************************************************

			//********************************** D R A G O N ***************************************************************************************

			if (dushman->dragon != nullptr)
			{
				for (int a = 0; a < dushman->dragon->beamSize; a++)
				{
					if (dushman->dragon->beam[a] != nullptr)
					{
						if (!pause)
							dushman->dragon->beam[a]->update();
						window.draw(dushman->dragon->beam[a]->sprite);

						if (dushman->dragon->beam[a]->sprite.getPosition().y > 800)
						{
							delete dushman->dragon->beam[a];
							dushman->dragon->beam[a] = nullptr;
						}
					}
				}
			}
			//**************************************************************************************************************************

			if (!over)
			{
				if (p->powa && p->shipSwitch)
					p->changeShipSprite("img/playershipnew.png");
				else if (!p->powa && p->shipSwitch)
					p->changeShipSprite("img/player_shipnew.png");
				window.draw(p->sprite);
			} // setting player on screen

			if (dushman->monster != nullptr && monster1)
				window.draw(dushman->monster->sprite);

			if (dushman->dragon != nullptr && dragon1)
				window.draw(dushman->dragon->sprite);

			if (pause && !over)
				window.draw(pauseIcon);
			if (over)
			{
				displayText(window, "GAME OVER\n Score : " + p->score.getScoreString(), 48, 150, 300);
			}

			p->life.displayLives(window);
			//	window.draw(dushman->sprite);    // setting enemy on screen
			//			cout << p->score.getScoreString() << '\n';
			//    displayText(window, p->score.getScoreString(),24,700,10);
			window.display();
		}
		if (over)
		{
			fstream file;
			file.open("scores.txt", ios::in);
			if (!file.is_open())
			{
				file.close();
				file.open("scores.txt", ios::out);
				file << 1;
				file << '\n';
				file << p->score.score;
				file << '\n';
				file << name;
			}
			else
			{
				int x;
				file >> x;
				int *arr = new int[x + 1];
				string *names = new string[x + 1];
				for (int a = 0; a < x; a++)
				{
					file >> arr[a];
					getline(file, names[a]);
					getline(file, names[a]);
				}
				arr[x] = p->score.score;
				names[x] = name;
				x++;
				for (int a = 0; a < x - 1; a++)
				{
					for (int b = a + 1; b < x; b++)
					{
						if (arr[a] < arr[b])
						{
							int temp = arr[a];
							string temp2 = names[a];
							arr[a] = arr[b];
							names[a] = names[b];
							arr[b] = temp;
							names[b] = temp2;
						}
					}
				}
				file.close();

				file.open("scores.txt", ios::out);
				file << x;
				for (int a = 0; a < x; a++)
				{
					file << '\n';
					file << arr[a];
					file << '\n';
					file << names[a];
				}
				file.close();
				delete[] arr;
				arr = nullptr;
				delete[] names;
				names = nullptr;
			}
		}
		window.close();
	}
};

//**********************************************************************************************************************

bool checkCollision(const Sprite &sprite1, const Sprite &sprite2, int r)
{
	int radius = r;
	// Get the positions and sizes of the sprites
	int x1, x2, y1, y2;
	x1 = sprite1.getPosition().x;
	y1 = sprite1.getPosition().y;
	x2 = sprite2.getPosition().x;
	y2 = sprite2.getPosition().y;

	bool coll = false;
	for (int a = 0; a <= radius; a++)
	{
		if (x1 + a == x2)
		{
			coll = true;
			break;
		}
	}
	if (coll)
	{
		coll = false;
		for (int a = 0; a <= radius; a++)
		{
			if (y1 + a == y2)
			{
				coll = true;
				break;
			}
		}
	}

	return coll; // No collision
}

//*************************************************************************************************************************

void displayText(RenderWindow &window, const string &message, int size, int x, int y)
{
	Font font;
	if (!font.loadFromFile("SPACE.ttf"))
	{
		cout << "failure\n";
	}

	// Create a text object
	Text text(message, font, size);
	text.setFillColor(Color::White);
	text.setPosition(x, y);

	window.draw(text);

	// Display the window
	// window.display();
}

//*************************************************************************************************************

//**************************************************************************************************************