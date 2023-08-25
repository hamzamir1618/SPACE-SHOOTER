#include <SFML/Graphics.hpp>
#include "bullet.h"
#include "score.h"
#include "life.h"
#include <string.h>

using namespace sf;
class Player
{
public:
	Texture tex, tex2;
	string bulletPng;
	int deltashift, projectilesize;
	Bullet **projectile;
	Sprite sprite, sprite2;
	Score score;
	Life life;
	bool powa, fire, shipSwitch, bulletSwitch;
	float speed;
	int x, y;
	Player(string png_path1, string png_path2)
	{
		powa = shipSwitch = fire = bulletSwitch = false;
		speed = 0.25;
		projectilesize = 50;
		projectile = new Bullet *[projectilesize];
		for (int a = 0; a < projectilesize; a++)
		{
			projectile[a] = nullptr;
		}
		deltashift = 2;
		tex.loadFromFile(png_path1);
		sprite.setTexture(tex);
		tex2.loadFromFile(png_path2);
		sprite2.setTexture(tex2);
		x = 340;
		y = 600;
		// x=340;y=700;
		sprite.setPosition(x, y);
		sprite.setScale(0.0525, 0.0525);
		score.score = 0;
	}
	/*void fire()
	{
	}*/
	void changeShipSprite(string png_path)
	{
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		shipSwitch = false;
	}

	/*void changeShipSprite(string png_path)
	{
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		bulletSwitch = false;
	}*/

	void move(std::string s, int posx, int posy)
	{
		float delta_x = 0, delta_y = 0;
		if (posx >= 840)
			sprite.setPosition(-70, posy);
		else if (posx <= -75)
			sprite.setPosition(830, posy);
		// if(s=="l")
		// move the player left
		// else if(s=="r")
		// move the player right
		if (s == "u" && posy >= 5)
			delta_y = -deltashift;
		else if (s == "d" && posy <= 615)
			delta_y = deltashift;
		else if (s == "l")
			delta_x = -deltashift;
		else if (s == "r")
			delta_x = deltashift;

		delta_x *= speed;
		delta_y *= speed;
		sprite.move(delta_x, delta_y);
	}

	void initiateBullets()
	{
		// string png_path;
		float k = 0;
		if (fire)
		{
			bulletPng = "img/fire2.png";
			k = -4.5;
		}
		else
			bulletPng = "img/player_laser.png";
		for (int a = 0; a < projectilesize; a++)
		{
			if (projectile[a] == nullptr)
			{
				projectile[a] = new Bullet(bulletPng, sprite.getPosition().x, sprite.getPosition().y, 0, -3, 270);

				projectile[a]->sprite.setPosition(projectile[a]->sprite.getPosition().x - 5.5 + k, projectile[a]->sprite.getPosition().y + 60);
				break;
			}
		}
	}

	void initiatePowerupBullets()
	{
		int i = 0;
		float k = -3, j = -20;
		for (; i < 7; i++, k++, j += 5)
		{
			for (int a = 0; a < projectilesize; a++)
			{
				if (projectile[a] == nullptr)
				{
					projectile[a] = new Bullet(bulletPng, sprite.getPosition().x, sprite.getPosition().y, 0 + k, -3, 270);

					projectile[a]->sprite.setPosition(projectile[a]->sprite.getPosition().x + j, projectile[a]->sprite.getPosition().y + 60);
					break;
				}
			}
		}
	}
};
