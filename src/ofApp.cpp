#include "Main.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//load music
	music.setup();

	//play music
	music.Background();

	//loading in camera
	camera.setPosition(ofVec3f(player.x, player.y, 0));
	camera.setupPerspective();

	//load font
	font.load("fonts/kenvector_future.ttf", 16, true);

	//setup functions
	gui.setup();
	window.main();
	player.setup();
	timer.InitializeTimer();
	playerScore = score.InitializeScore();

	//load right player images
	player.player_R_0.load("images/Player_0_R.png");
	player.player_R_1.load("images/Player_1_R.png");
	player.player_R_2.load("images/Player_2_R.png");

	//load left player images
	player.player_L_0.load("images/Player_0_L.png");
	player.player_L_1.load("images/Player_1_L.png");
	player.player_L_2.load("images/Player_2_L.png");

	//load jump player images
	player.player_jump.load("images/Player_jump.png");

	//load hurt player images
	player.player_hurt_1.load("images/Player_Hurt_1.png");

	//load enemy images
	enemyImage.load("images/FallingRock.png");
	landenemyImage.load("images/ShootingEnemy.png");
	spikeImage.load("images/Spikes.png");
	spikeImage_2.load("images/Spikes_2.png");

	//load pickup images
	coinImage.load("images/Coin.png");
	chestImage.load("images/Chest.png");

	//load level doors images
	doorImage.load("images/Door_1.png");
	doorImage2.load("images/Door_2.png");
	doorImage3.load("images/Door_3.png");

	//load in heart image for lives
	heartImage.load("images/Heart.png");
	for (int i = 0; i < NUM_HEARTS; i++)
	{
		hearts[i].x = 20 + i * 100;
		hearts[i].y = 10;
		hearts[i].SetImage(&heartImage);
	}

	//keyboard array
	for (int i = 0; i < 255; i++)
		keyDown[i] = false;

	for (int j = 0; j < 255; j++)
		keyRelease[j] = false;


	player.GetImage()->load("images/Player_0.png");

	player.SetNumFrames(24);

	//Walking right
	player.frames[0] = player.player_R_0;
	player.frames[1] = player.player_R_0;
	player.frames[2] = player.player_R_0;
	player.frames[3] = player.player_R_1;
	player.frames[4] = player.player_R_1;
	player.frames[5] = player.player_R_1;
	player.frames[6] = player.player_R_2;
	player.frames[7] = player.player_R_2;
	player.frames[8] = player.player_R_2;

	//Walking left
	player.frames[9] = player.player_L_0;
	player.frames[10] = player.player_L_0;
	player.frames[11] = player.player_L_0;
	player.frames[12] = player.player_L_1;
	player.frames[13] = player.player_L_1;
	player.frames[14] = player.player_L_1;
	player.frames[15] = player.player_L_2;
	player.frames[16] = player.player_L_2;
	player.frames[17] = player.player_L_2;


	//Jumping
	player.frames[18] = player.player_jump;
	player.frames[19] = player.player_jump;
	player.frames[20] = player.player_jump;

	//Hit
	player.frames[21] = player.player_hurt_1;
	player.frames[22] = player.player_hurt_1;
	player.frames[23] = player.player_hurt_1;


	pickup = false; 
	

	
}
//--------------------------------------------------------------
void ofApp::update(){

	//if player falls into water
	if (player.y > physics.fallgroundLevel) {
		gui.lose = true;
	}

	//if begin button is pressed
	if (gui.boolbegin == true) {
		gui.menu = false;
		levels.level1 = true;
		levels.setup();
		hmapImage.load("images/Level_01_Height_Map.png");
		physics.ReadHeightMap(&hmapImage);
		levelPickups();


	}

	//if game has started
	if (gui.menu == false) {

		timer.DrawTimer();

		int targetX = player.x;

		//right arrow is pressed
		if (keyDown[OF_KEY_RIGHT] == true) {
			player.SetNumFrames(0, 8);
			player.Advance();
			targetX += player.speed;
		}

		//left arrow is pressed
		if (keyDown[OF_KEY_LEFT] == true) {
			player.SetNumFrames(9, 17);
			targetX -= player.speed;
			player.Advance();
		}

		//up arrow is pressed
		if (keyDown[OF_KEY_UP] == true && player.jump == false) {

			player.jump = true;
			player.t = 0;
			player.y0 = player.y;
			player.v0 = physics.jumpspeed;
			targetX += player.speed * 20;
			player.Advance();
		}
		physics.Move(&player, targetX);

		if (player.jump == true) {
			player.SetNumFrames(18, 20);
		}

		//set camera position
		camera.setPosition(ofVec3f((player.x) + 600, (player.y) - 50, 700));

		//if spacebar is pressed
		if (keyRelease[' '] == true) {

			hasFired = true;

		}
		else
			hasFired = false;

		if (hasFired == true) {
			bullet.checkPositions(&player, &y);
		}
		else
			bullet.setPositions(&player);



		//falling enemies
		for (int i = 0; i < NUM_ENEMIES; i++)
		{
			physics.PingPong(&enemy[i]);

			collision = physics.PlayerCollision(&player, &enemy[i]);

			if (collision < 30) {
				player.SetNumFrames(21, 23);
				player.Advance();
				for (int i = ind; i < maxSize - 1; i++) {
					hearts[i] = hearts[i + 1];
				}
				hearts[maxSize - 1] = {};
				if (ind > 0) {
					ind = ind - 1;
				}
			}

			if (ind == 0) {
				gui.lose = true;
			}
		}

		//coins
		for (int i = 0; i < NUM_COINS; i++) {
			pickup = physics.PickupCollision(&player, &coins[i]);
		
			if (pickup == true) {
				playerScore = score.AddScore_Coin();
			}


		}

		//chest
		for (int i = 0; i < NUM_CHESTS; i++) {
			pickup = physics.PickupCollision(&player, &chests[i]);
			if (pickup == true) {
				playerScore = score.AddScore_Chest();
			}


		}

		//spikes
		for (int i = 0; i < NUM_SPIKES; i++) {
			collision3 = physics.PlayerCollision(&player, &spikes[i]);

			if (collision3 < 100) {
				player.SetNumFrames(21, 23);
				player.Advance();
				for (int i = ind; i < maxSize - 1; i++) {
					hearts[i] = hearts[i + 1];
				}
				hearts[maxSize - 1] = {};
				if (ind > 0) {
					ind = ind - 1;
				}
			}


		}

		//land enemies
		for (int i = 0; i < NUM_LAND_ENEMIES; i++)
		{
			physics.CheckDistance(x, y, &land_enemies[i]);
			physics.PingPongHorizontal(&land_enemies[i]);

			collision2 = physics.PlayerCollision(&player, &land_enemies[i]);

			if (collision2 < 100) {
				player.SetNumFrames(21, 23);
				player.Advance();

				for (int i = ind; i < maxSize - 1; i++) {
					hearts[i] = hearts[i + 1];
				}
				hearts[maxSize - 1] = {};
				if (ind > 0) {
					ind = ind - 1;
					cout << "index: " << ind << endl;
				}
			}
		}


		//level 1 door collision
		//start of level 2
		if (levels.level1 == true) {

			collision4 = physics.PlayerCollision(&player, &doors[0]);
			if (collision4 < 80) {
				levels.level1 = false;
				levels.level2 = true;
				levels.level3 = false;
				gui.menu = false;
				levels.setup();
				hmapImage.load("images/Level_02_Height_Map.png");
				physics.ReadHeightMap(&hmapImage);
				player.x = 125;
				player.y = 585;
				levelPickups();

			}

		}

		//level 2 door collision
		//start of level 3
		if (levels.level2 == true) {

			collision5 = physics.PlayerCollision(&player, &doors[1]);

			if (collision5 < 80) {
				levels.level1 = false;
				levels.level2 = false;
				levels.level3 = true;
				levels.setup();
				hmapImage.load("images/Level_03_Height_Map.png");
				physics.ReadHeightMap(&hmapImage);
				player.x = 125;
				player.y = 585;
				levelPickups();

			}
		}

		//level 3 door collision
		//end of game
		if (levels.level3 == true) {

			collision6 = physics.PlayerCollision(&player, &doors[2]);

			if (collision6 < 80) {
				gui.win = true;

			}
		}

	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	if (gui.menu == false) {

	camera.begin();		//start camera
	
	levels.draw();		//drawing level images

	//draw bullet
	if (hasFired == true) {
		bullet.Draw(&player);
		x = bullet.checkPositions(&player, &y);
		y = y;
	}
	
	//draw enemies and pickups
	for (int i = 0; i < NUM_ENEMIES; i++)
		render.Draw(&enemy[i]);

	for (int i = 0; i < NUM_COINS; i++)
		render.Draw(&coins[i]);

	for (int i = 0; i < NUM_LAND_ENEMIES; i++)
		render.Draw(&land_enemies[i]);

	for (int i = 0; i < NUM_SPIKES; i++)
		render.Draw(&spikes[i]);

	for (int i = 0; i < NUM_CHESTS; i++)
		render.Draw(&chests[i]);

	for (int i = 0; i < NUM_DOORS; i++)
		render.Draw(&doors[i]);

	player.Draw();

	camera.end();		//end camera


	//draw timer
	timer.InfoTimer(&timerReached, &endtime, &btimer, &storingTime);
	timerReached = timerReached;
	endtime = endtime;
	btimer = btimer;
	storingTime = storingTime;

	gui.timerDraw(playerScore, timerReached, endtime, btimer, storingTime);

	//draw heart
	for (int i = 0; i < NUM_HEARTS; i++)
		render.Draw(&hearts[i]);
	}

	gui.menuDraw();		//draw main menu

}

void ofApp::levelPickups() {

	//setting level 1 pickups
	if (levels.level1 == true) {

		for (int i = 3; i < 13; i++) {
			enemy[i].x = 6000;
			enemy[i].y = 6000;
		}

		enemy[0].x = 905;
		enemy[0].y = 870;
		enemy[0].min = 500;
		enemy[0].max = 872;
		enemy[0].SetImage(&enemyImage);

		enemy[1].x = 1600;
		enemy[1].y = 750;
		enemy[1].min = 500;
		enemy[1].max = 872;
		enemy[1].SetImage(&enemyImage);

		enemy[2].x = 3655;
		enemy[2].y = 750;
		enemy[2].min = 500;
		enemy[2].max = 872;
		enemy[2].SetImage(&enemyImage);

		for (int i = 1; i < 9; i++) {
			land_enemies[i].x = 6000;
			land_enemies[i].y = 6000;
		}

		land_enemies[0].x = 4700;
		land_enemies[0].y = 1050;
		land_enemies[0].min = 4699;
		land_enemies[0].max = 5200;
		land_enemies[0].SetImage(&landenemyImage);

		for (int i = 24; i < 59; i++) {
			coins[i].x = 6000;
			coins[i].y = 6000;
		}

		coins[0].x = 800;
		coins[0].y = 1040;
		coins[0].SetImage(&coinImage);

		coins[1].x = 940;
		coins[1].y = 910;
		coins[1].SetImage(&coinImage);

		coins[2].x = 1050;
		coins[2].y = 780;
		coins[2].SetImage(&coinImage);

		coins[3].x = 1150;
		coins[3].y = 780;
		coins[3].SetImage(&coinImage);

		coins[4].x = 1250;
		coins[4].y = 780;
		coins[4].SetImage(&coinImage);

		coins[5].x = 1632;
		coins[5].y = 780;
		coins[5].SetImage(&coinImage);

		coins[6].x = 1850;
		coins[6].y = 780;
		coins[6].SetImage(&coinImage);

		coins[7].x = 1940;
		coins[7].y = 860;
		coins[7].SetImage(&coinImage);

		coins[8].x = 2030;
		coins[8].y = 940;
		coins[8].SetImage(&coinImage);

		coins[9].x = 2120;
		coins[9].y = 1020;
		coins[9].SetImage(&coinImage);

		coins[10].x = 3688;
		coins[10].y = 778;
		coins[10].SetImage(&coinImage);

		coins[11].x = 3925;
		coins[11].y = 778;
		coins[11].SetImage(&coinImage);

		coins[12].x = 4114;
		coins[12].y = 778;
		coins[12].SetImage(&coinImage);

		coins[13].x = 4300;
		coins[13].y = 778;
		coins[13].SetImage(&coinImage);

		coins[14].x = 4400;
		coins[14].y = 778;
		coins[14].SetImage(&coinImage);

		coins[15].x = 4490;
		coins[15].y = 858;
		coins[15].SetImage(&coinImage);

		coins[16].x = 4580;
		coins[16].y = 938;
		coins[16].SetImage(&coinImage);

		coins[17].x = 4670;
		coins[17].y = 1018;
		coins[17].SetImage(&coinImage);

		coins[18].x = 5593;
		coins[18].y = 910;
		coins[18].SetImage(&coinImage);

		coins[19].x = 5720;
		coins[19].y = 790;
		coins[19].SetImage(&coinImage);

		coins[20].x = 5847;
		coins[20].y = 670;
		coins[20].SetImage(&coinImage);

		coins[21].x = 5974;
		coins[21].y = 533;
		coins[21].SetImage(&coinImage);

		coins[22].x = 6074;
		coins[22].y = 533;
		coins[22].SetImage(&coinImage);

		coins[23].x = 6174;
		coins[23].y = 533;
		coins[23].SetImage(&coinImage);


		for (int i = 1; i < 10; i++) {
			spikes[i].x = 6000;
			spikes[i].y = 6000;
		}

		spikes[0].x = 3050;
		spikes[0].y = 943;
		spikes[0].SetImage(&spikeImage);
		
		for (int i = 1; i < 3; i++) {
			chests[i].x = 6000;
			chests[i].y = 6000;
		}
	
		chests[0].x = 5400;
		chests[0].y = 1040;
		chests[0].SetImage(&chestImage);
		

		doors[0].x = 6270;
		doors[0].y = 415;
		doors[0].SetImage(&doorImage);
		

	}

	//setting level 2 pickups
	else if (levels.level2 == true) {

		for (int i = 0; i < 3; i++)
		{
			enemy[i].x = 6000;
			enemy[i].y = 6000;

		}

		enemy[3].x = 536;
		enemy[3].y = 700;
		enemy[3].min = 863;
		enemy[3].max = 873;
		enemy[3].SetImage(&enemyImage);

		enemy[4].x = 2200;
		enemy[4].y = 750;
		enemy[4].min = 500;
		enemy[4].max = 872;
		enemy[4].SetImage(&enemyImage);

		enemy[5].x = 4367;
		enemy[5].y = 750;
		enemy[5].min = 500;
		enemy[5].max = 872;
		enemy[5].SetImage(&enemyImage);

		enemy[6].x = 5223;
		enemy[6].y = 632;
		enemy[6].min = 500;
		enemy[6].max = 872;
		enemy[6].SetImage(&enemyImage);

		enemy[7].x = 5558;
		enemy[7].y = 632;
		enemy[7].min = 500;
		enemy[7].max = 872;
		enemy[7].SetImage(&enemyImage);

		enemy[8].x = 6150;
		enemy[8].y = 750;
		enemy[8].min = 500;
		enemy[8].max = 872;
		enemy[8].SetImage(&enemyImage);

		chests[0].x = 6000;
		chests[0].y = 6000;
	
		chests[1].x = 4382;
		chests[1].y = 917;
		chests[1].SetImage(&chestImage);

		land_enemies[0].x = 6000;
		land_enemies[0].y = 6000;
	
		land_enemies[1].x = 800;
		land_enemies[1].y = 1050;
		land_enemies[1].min = 1100;
		land_enemies[1].max = 4000;
		land_enemies[1].SetImage(&landenemyImage);

		land_enemies[2].x = 1900;
		land_enemies[2].y = 923;
		land_enemies[2].min = 700;
		land_enemies[2].max = 2000;
		land_enemies[2].SetImage(&landenemyImage);

		land_enemies[3].x = 3000;
		land_enemies[3].y = 798;
		land_enemies[3].min = 4699;
		land_enemies[3].max = 5200;
		land_enemies[3].SetImage(&landenemyImage);

		spikes[0].x = 6000;
		spikes[0].y = 6000;
		

		spikes[1].x = 640;
		spikes[1].y = 1070;
		spikes[1].SetImage(&spikeImage);

		spikes[2].x = 3600;
		spikes[2].y = 1070;
		spikes[2].SetImage(&spikeImage);

		spikes[3].x = 4655;
		spikes[3].y = 814;
		spikes[3].SetImage(&spikeImage);

		doors[0].x = 6000;
		doors[0].y = 6000;

		doors[1].x = 6265;
		doors[1].y = 798;
		doors[1].SetImage(&doorImage2);

		//-----------COINS-------------//

		for (int i = 0; i < 24; i++)
		{
			coins[i].x = 6000;
			coins[i].y = 6000;
			
		}

		coins[24].x = 460;
		coins[24].y = 780;
		coins[24].SetImage(&coinImage);

		coins[25].x = 560;
		coins[25].y = 910;
		coins[25].SetImage(&coinImage);

		coins[26].x = 735;
		coins[26].y = 1042;
		coins[26].SetImage(&coinImage);

		coins[27].x = 1370;
		coins[27].y = 1042;
		coins[27].SetImage(&coinImage);

		coins[28].x = 1440;
		coins[28].y = 965;
		coins[28].SetImage(&coinImage);

		coins[29].x = 2230;
		coins[29].y = 910;
		coins[29].SetImage(&coinImage);

		coins[30].x = 2750;
		coins[30].y = 780;
		coins[30].SetImage(&coinImage);

		coins[31].x = 2850;
		coins[31].y = 650;
		coins[31].SetImage(&coinImage);

		coins[32].x = 2950;
		coins[32].y = 780;
		coins[32].SetImage(&coinImage);

		coins[33].x = 3380;
		coins[33].y = 810;
		coins[33].SetImage(&coinImage);

		coins[34].x = 3460;
		coins[34].y = 900;
		coins[34].SetImage(&coinImage);

		coins[35].x = 3540;
		coins[35].y = 1000;
		coins[35].SetImage(&coinImage);

		coins[36].x = 5090;
		coins[36].y = 780;
		coins[36].SetImage(&coinImage);

		coins[37].x = 5106 + 150;
		coins[37].y = 780;
		coins[37].SetImage(&coinImage);

		coins[38].x = 5266 + 150;
		coins[38].y = 778;
		coins[38].SetImage(&coinImage);

		coins[39].x = 5435 + 150;
		coins[39].y = 778;
		coins[39].SetImage(&coinImage);

		coins[40].x = 5996;
		coins[40].y = 785;
		coins[40].SetImage(&coinImage);

		coins[41].x = 6085;
		coins[41].y = 890;
		coins[41].SetImage(&coinImage);

	}

	//setting level 3 pickups
	else if (levels.level3 == true) {

		for (int i = 0; i < 9; i++)
		{
			enemy[i].x = 6000;
			enemy[i].y = 6000;

		}

		enemy[9].x = 2814 - 180;
		enemy[9].y = 700;
		enemy[9].min = 699;
		enemy[9].max = 873;
		enemy[9].SetImage(&enemyImage);

		enemy[10].x = 2814 + 175;
		enemy[10].y = 700;
		enemy[10].min = 699;
		enemy[10].max = 873;
		enemy[10].SetImage(&enemyImage);

		enemy[11].x = 3680;
		enemy[11].y = 568;
		enemy[11].min = 460;
		enemy[11].max = 873;
		enemy[11].SetImage(&enemyImage);

		enemy[12].x = 6100;
		enemy[12].y = 445;
		enemy[12].min = 699;
		enemy[12].max = 873;
		enemy[12].SetImage(&enemyImage);

		for (int i = 0; i < 5; i++)
		{
			land_enemies[i].x = 7000;
			land_enemies[i].y = 7000;

		}

		land_enemies[5].x = 1945;
		land_enemies[5].y = 920;
		land_enemies[5].min = 1944;
		land_enemies[5].max = 2500;
		land_enemies[5].SetImage(&landenemyImage);

		land_enemies[6].x = 4250;
		land_enemies[6].y = 1050;
		land_enemies[6].min = 6000;
		land_enemies[6].max = 5900;
		land_enemies[6].SetImage(&landenemyImage);

		land_enemies[7].x = 5900;
		land_enemies[7].y = 662;
		land_enemies[7].min = 6300;
		land_enemies[7].max = 6400;
		land_enemies[7].SetImage(&landenemyImage);

		land_enemies[8].x = 6000;
		land_enemies[8].y = 6000;
		land_enemies[8].min = 4699;
		land_enemies[8].max = 5200;
		land_enemies[8].SetImage(&landenemyImage);

		for (int i = 0; i < 43; i++)
		{
			coins[i].x = 6000;
			coins[i].y = 6000;


		}

		coins[43].x = 555;
		coins[43].y = 780;
		coins[43].SetImage(&coinImage);

		coins[44].x = 660;
		coins[44].y = 890;
		coins[44].SetImage(&coinImage);

		coins[45].x = 765;
		coins[45].y = 1000;
		coins[45].SetImage(&coinImage);

		coins[46].x = 765 + 250;
		coins[46].y = 1000;
		coins[46].SetImage(&coinImage);

		coins[47].x = 660 + 450;
		coins[47].y = 890;
		coins[47].SetImage(&coinImage);

		coins[48].x = 550 + 650;
		coins[48].y = 780;
		coins[48].SetImage(&coinImage);

		coins[49].x = 3710 - 230;
		coins[49].y = 780;
		coins[49].SetImage(&coinImage);

		coins[50].x = 3710;
		coins[50].y = 780;
		coins[50].SetImage(&coinImage);

		coins[51].x = 3710 + 230;
		coins[51].y = 780;
		coins[51].SetImage(&coinImage);

		coins[52].x = 3280;
		coins[52].y = 900;
		coins[52].SetImage(&coinImage);

		coins[53].x = 4090;
		coins[53].y = 900;
		coins[53].SetImage(&coinImage);

		coins[54].x = 4236;
		coins[54].y = 1030;
		coins[54].SetImage(&coinImage);

		coins[55].x = 4900;
		coins[55].y = 1030;
		coins[55].SetImage(&coinImage);

		coins[56].x = 4900 + 130;
		coins[56].y = 910;
		coins[56].SetImage(&coinImage);

		coins[57].x = 5030 + 120;
		coins[57].y = 790;
		coins[57].SetImage(&coinImage);

		coins[58].x = 5160 + 120;
		coins[58].y = 670;
		coins[58].SetImage(&coinImage);

		for (int i = 0; i < 4; i++)
		{
			spikes[i].x = 6000;
			spikes[i].y = 6000;


		}

		spikes[4].x = 800 + 37;
		spikes[4].y = 1070;
		spikes[4].SetImage(&spikeImage);

		spikes[5].x = 864 + 37;
		spikes[5].y = 1070;
		spikes[5].SetImage(&spikeImage);

		spikes[6].x = 1700;
		spikes[6].y = 813;
		spikes[6].SetImage(&spikeImage);

		spikes[7].x = 3340;
		spikes[7].y = 941;
		spikes[7].SetImage(&spikeImage);

		spikes[8].x = 3403;
		spikes[8].y = 441;
		spikes[8].SetImage(&spikeImage_2);

		doors[1].x = 6000;
		doors[1].y = 6000;

		doors[2].x = 6300;
		doors[2].y = 624;
		doors[2].SetImage(&doorImage3);

		for (int i = 0; i < 2; i++)
		{
			chests[i].x = 6000;
			chests[i].y = 6000;

		}

		chests[2].x = 2820;
		chests[2].y = 914;
		chests[2].SetImage(&chestImage);


	}

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	keyDown[key] = true;
	keyRelease[key] = false;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	keyDown[key] = false;
	keyRelease[key] = true;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	//checking if mouse is pressed inside buttons
	if (gui.beginButton.inside(x, y)) {
		gui.boolbegin = true;
	}

	if (gui.controlButton.inside(x, y)) {
		gui.boolcontrol = true;
	}

	if (gui.instructionButton.inside(x, y)) {
		gui.boolinstruction = true;
	}

	if (gui.backButton.inside(x, y)) {
		gui.boolback = true;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

	//checking if mouse is released inside buttons

	if (gui.beginButton.inside(x, y)) {
		gui.boolbegin = false;
	}

	if (gui.backButton.inside(x, y)) {
		gui.boolback = false;
		gui.boolcontrol = false;
		gui.boolinstruction = false;
	}
}
