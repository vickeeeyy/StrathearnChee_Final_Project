#pragma once

class Level : public ofBaseApp {

public:
	Level();
	~Level();

	ofImage backgroundImage;
	ofVec2f backgroundPos;

	bool level1;
	bool level2;
	bool level3;

	void setup();
	void draw();

};
