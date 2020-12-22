#pragma once

class GUI {

public:

	GUI();
	~GUI();

	ofTrueTypeFont font;		//intializing font
	ofTrueTypeFont font2;

	ofImage red_button_image;
	ofImage red_button_1_image;		//intializing UI images
	ofImage mainScreen_image;
	ofImage control_image;
	ofImage instruction_image;
	ofImage win_image;
	ofImage lose_image;

	ofRectangle beginButton;
	ofRectangle controlButton;			//intializing button shapes
	ofRectangle instructionButton;
	ofRectangle backButton;

	bool boolbegin;
	bool boolcontrol;		//button bools
	bool boolinstruction;
	bool boolback;
	bool menu;

	bool win;			//game state bools
	bool lose;

	void setup();
	void timerDraw(int x, bool timerReached, float endtime, float btimer, float storingTime);
	void menuDraw();
};
