#pragma once
class ofApp : public ofBaseApp{

	public:

		ofTrueTypeFont font;

		ofEasyCam camera;
		
		Window window;
		AnimatedObject player;
		Bullet bullet;
		Render render;
		Physics physics;
		GUI gui;
		Score score;
		Timer timer; 
		Level levels;
		Music music;
		
		GameObject enemy[NUM_ENEMIES];
		GameObject coins[NUM_COINS];
		GameObject hearts[NUM_HEARTS];
		GameObject land_enemies[NUM_LAND_ENEMIES];
		GameObject spikes[NUM_SPIKES];
		GameObject chests[NUM_CHESTS];
		GameObject doors[NUM_DOORS];

		ofImage hmapImage; 
		ofImage enemyImage;
		ofImage landenemyImage;
		ofImage coinImage;
		ofImage heartImage;
		ofImage spikeImage;
		ofImage doorImage;
		ofImage doorImage2;
		ofImage doorImage3;
		ofImage chestImage;
		ofImage spikeImage_2;


		int maxSize = 5; 
		int ind = 5; 

		int x;
		int x2;
		int y;
		int collision;
		int collision2;
		int collision3;
		int collision4;
		int collision5;
		int collision6;
		bool hasFired;
		bool pickup;

		int playerScore;

		bool timerReached;
		float endtime;
		float btimer;
		float storingTime;

		bool keyDown[255];
		bool keyRelease[255];
		
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void levelPickups();

		
};
