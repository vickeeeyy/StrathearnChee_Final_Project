#include "Main.h"


//--------------------------------------------------------------
Music::Music()
{

}


//--------------------------------------------------------------
Music::~Music()
{
}

void Music::setup()
{
	backgroundSound.load("sounds/background.mp3");

}

//--------------------------------------------------------------
void Music::Background() {


	backgroundSound.play();


}