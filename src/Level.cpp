#include "Main.h"


//--------------------------------------------------------------
Level::Level()
{
	level1 = false;
	level2 = false;
	level3 = false;
}
//--------------------------------------------------------------

Level::~Level()
{

}
//--------------------------------------------------------------

void Level::setup() {

	//intializing images
	
	if (level1 == true) {
		backgroundImage.load("images/Level_01_Image.png");
	}
	else if (level2 == true) {
		backgroundImage.load("images/Level_02_Image.png");
	}
	else if (level3 == true) {
		backgroundImage.load("images/Level_03_Image.png");
	}

}
//--------------------------------------------------------------
void Level::draw() {

	//draw images
	backgroundImage.draw(backgroundPos.x, backgroundPos.y);

}