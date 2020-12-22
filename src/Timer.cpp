#include "Main.h"


//--------------------------------------------------------------
Timer::Timer()
{

}


//--------------------------------------------------------------
Timer::~Timer()
{

}

//--------------------------------------------------------------
int Timer::InitializeTimer() {

	//load font
	font.load("fonts/kenvector_future.ttf", 16, true);

	//timer set up
	startTime = 200000;			 // get the start time
	endTime = 0;				// in milliseconds
	bTimerReached = false;
	storingtime = 0.0f;

	cout << "Start Time: " << startTime << endl;

	return endTime;

}

//--------------------------------------------------------------
int Timer::DrawTimer() {

	float barWidth = 100;

	// update the timer this frame
	timer = startTime - ofGetElapsedTimeMillis();

	if (timer <= endTime && !bTimerReached) {
		bTimerReached = true;
	}

	return timer;

}

//--------------------------------------------------------------
void Timer::InfoTimer(bool *timerReached, float *endtime, float *btimer, float *storingTime) {

	*timerReached = bTimerReached;
	*endtime = endTime;
	*btimer = timer;
	*storingTime = storingtime;
}