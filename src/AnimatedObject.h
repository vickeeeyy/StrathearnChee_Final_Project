#pragma once
#define MAX_FRAMES 24

class AnimatedObject : public GameObject
{
private:

	int currentFrame;
	int numFrames;
	int firstFrame;
	int lastFrame;

public:

	ofImage frames[MAX_FRAMES];

	ofImage player_R_0;
	ofImage player_R_1;
	ofImage player_R_2;
	ofImage player_L_0;
	ofImage player_L_1;
	ofImage player_L_2;
	ofImage player_jump;
	ofImage player_hurt_1;

	AnimatedObject();
	~AnimatedObject();

	bool Advance();
	bool SetNumFrames(int n);
	bool SetNumFrames(int n1, int n2);
	void Draw();
};