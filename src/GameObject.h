#pragma once

class GameObject: public ofBaseApp {

protected:
	ofImage * img;

public:
	
	GameObject();
	~GameObject();

	int min;
	int max;

	//Player
	int x;
	int y;
	float speed;
	int y0;
	int v0;
	float t;
	bool jump;

	int height;
	int width;

	virtual void Draw();
	virtual ofImage* GetImage();
	virtual void SetImage(ofImage* image);
};

