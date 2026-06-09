class sprite
{
public:
	~sprite();
	void updatesprite();
	void bouncesprite(int SCREEN_W, int SCREEN_H);
	void load_animated_sprite(int size);
	void drawSprite();
	int getX() { return x; }
	int getY() { return y; }
	void Collision(sprite Sprites[], int cSize, int me, int WIDTH, int HEIGHT);


private:
	int x, y;
	int width, height;
	int xspeed, yspeed;
	int xdelay, ydelay;
	int xcount, ycount;
	int curframe, maxframe, animdir;
	int framecount, framedelay;
	ALLEGRO_BITMAP* image[9];
	int random_red;
	int random_green;
	int random_blue;
};