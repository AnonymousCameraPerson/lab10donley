#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <stdio.h>
#include "Sprite.h"

#include <iostream>
using namespace std;

void sprite::drawSprite(int seconds)
{
	if (isColliding) {
		if (random_specialty == 0) {
			random_red = rand() % 255;
			random_green = rand() % 255;
			random_blue = rand() % 255;
			al_draw_tinted_bitmap(image[curframe], al_map_rgb(random_red, random_green, random_blue), x, y, 0);
		}
		else if (random_specialty == 1) {
			if (seconds < 10)
				al_draw_scaled_bitmap(image[curframe], 0, 0, width, height, x, y, permWidth, permHeight, 0);
		}
	}
	else {
		al_draw_tinted_bitmap(image[curframe], al_map_rgb(random_red, random_green, random_blue), x, y, 0);
	}

}

void sprite::updatesprite()
{
	//update x position
	if (++xcount > xdelay)
	{
		xcount = 0;
		x += xspeed;
	}

	//update y position
	if (++ycount > ydelay)
	{
		ycount = 0;
		y += yspeed;
	}


	if (framecount++ > framedelay)
	{
		framecount = 0;
		curframe++;
		if (curframe >= maxframe)
			curframe = 0;
	}
}

void sprite::bouncesprite(int SCREEN_W, int SCREEN_H)
{
	//simple screen bouncing behavior
	if (x < 0)
	{
		x = 0;
		xspeed = rand() % 2 + 4;
		//xspeed = 1;
		animdir *= -1;
	}

	else if (x > SCREEN_W - width)
	{
		x = SCREEN_W - width;
		xspeed = rand() % 2 - 6;
		//xspeed = 1;
		animdir *= -1;
	}

	if (y < 0)
	{
		y = 0;
		yspeed = rand() % 2 + 4;
		//yspeed = 1;
		animdir *= -1;
	}

	else if (y > SCREEN_H - height)
	{
		y = SCREEN_H - height;
		yspeed = rand() % 2 - 6;
		//yspeed = 1;
		animdir *= -1;
	}

}

void sprite::load_animated_sprite(int size)
{
	//load the animated sprite
	char s[80];
	maxframe = size;
	for (int n = 0; n < size; n++)
	{
		
		sprintf_s(s, "Alien%d.bmp", n);
		image[n] = al_load_bitmap(s);
		//isColliding[n] = false;
		al_convert_mask_to_alpha(image[n], al_map_rgb(255, 255, 255));
	}
	width = al_get_bitmap_width(image[0]);
	height = al_get_bitmap_height(image[0]);
	permWidth = width / 2.0f;
	permHeight = height / 2.0f;
	curframe = 0;
	framedelay = 5;
	framecount = 0;
	random_red = 255;
	random_green = 255;
	isColliding = false;
	random_blue = 255;
	//random_specialty = rand() % 3;
	random_specialty = rand() % 2;
	angle = 0;
}

sprite::~sprite()
{
	for (int i = 0; i < maxframe; i++)
		al_destroy_bitmap(image[i]);
}

void sprite::Collision(sprite Sprites[], int cSize, int me, int WIDTH, int HEIGHT) {
	

	for (int i = 0; i < cSize; i++) {
		if (i != me) {
			if ((x >= Sprites[i].getX() - width/2) &&( x <= Sprites[i].getX() + width/2) && 
				(y >= Sprites[i].getY() - height/2) && (y <= Sprites[i].getY() + height/2)) {

					isColliding = true;

					if (random_specialty == 0) {
						isColliding = true;
						x = rand() % WIDTH;
						y = rand() % HEIGHT;
						break;
					}
					else if (random_specialty == 1) {
						isColliding = true;
						scaledInHalf = true;
						x = rand() % WIDTH;
						y = rand() % HEIGHT;
						permWidth /= 2;
						permHeight /= 2;
						break;
					}
					//else if (random_specialty == 2) {
					//		angle += 0.5;
					//		break;
					//}
					//else if (random_specialty == 3) {
					//	x = x;
					//	y = y;
					//	break;
					//}
			}
			else {
				isColliding = false;
				//random_red = 255;
				//random_green = 255;
				//random_blue = 255;
			}

		}
	}
}