#include "Main.h"


//--------------------------------------------------------------
Score::Score()
{
	currentScore = 0;
}


//--------------------------------------------------------------
Score::~Score()
{
	
}

//--------------------------------------------------------------
int Score::InitializeScore() {

	return currentScore;

}

//--------------------------------------------------------------
int Score::AddScore_Coin() {

	currentScore = currentScore + 100;

	return currentScore;

}

//--------------------------------------------------------------
int Score::AddScore_Chest() {

	currentScore = currentScore + 500;

	return currentScore;

}