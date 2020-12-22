#pragma once


class Timer {

public:

	Timer();
	~Timer();

	ofTrueTypeFont font;

	float timer;
	float startTime;
	float endTime;
	bool  bTimerReached;
	float storingtime;

	int InitializeTimer();
	int DrawTimer();
	void InfoTimer(bool *timerReached, float *endtime, float *btimer, float *storingTime);


};
