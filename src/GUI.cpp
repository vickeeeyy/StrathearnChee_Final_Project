#include "Main.h"

//--------------------------------------------------------------
GUI::GUI()
{

	beginButton.set(645, 480, 323, 92);
	controlButton.set(645, 600, 323, 92);
	instructionButton.set(645, 720, 323, 92);		//setting button position on sizes
	backButton.set(25, 20, 64, 70);

	boolbegin = false;
	boolcontrol = false;
	boolinstruction = false;
	boolback = false;				//intializing bools
	menu = true;
	win = false;
	lose = false;

}

//--------------------------------------------------------------
GUI::~GUI()
{

}

void GUI::setup() {
	
	//load font
	font.load("fonts/kenvector_future.ttf", 16, true);
	font2.load("fonts/kenvector_future.ttf", 40, true);

	//loading in gui images
	red_button_image.load("images/red_button.png");
	red_button_1_image.load("images/red_button_1.png");
	mainScreen_image.load("images/MainScreen.png");
	control_image.load("images/ControlsScreen.png");
	instruction_image.load("images/InstructionsScreen.png");
	win_image.load("images/Win_Image.png");
	lose_image.load("images/Lose_Image.png");


}

void GUI::menuDraw() {


	//drawing menu images based on button choice
	if (menu == true)
		mainScreen_image.draw(0, 0);

	if (boolbegin == true)
		mainScreen_image.clear();

	if (boolcontrol == true)
		control_image.draw(0,0);

	if (boolinstruction == true)
		instruction_image.draw(0, 0);

	if (boolback == true)
		mainScreen_image.draw(0, 0);


}

void GUI::timerDraw(int x, bool timerReached, float endtime, float btimer, float storingTime) {

	red_button_image.draw(1390,20);
	red_button_1_image.draw(732, 14);


	//drawing score 
	font.drawString("Score: " + ofToString(x), 1400, 50);

	if (timerReached == false) {
		string  info;
		info += "" + ofToString(btimer / 1000.0, 0);
		font.drawString(info, 739, 45);
	}

	else if (timerReached == true) {
		lose = true;				
	}

	//drawing win image and score	
	if (win == true) {
		win_image.draw(0,0);										
		font2.drawString(ofToString(x), 820, 625);
	}

	//drawing lose image and score
	if (lose == true) {
		lose_image.draw(0, 0);							
		font2.drawString(ofToString(x), 820, 595);
	}


}
