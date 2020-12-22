#pragma once

class Bullet : public GameObject {

public:

	ofVec2f bulletPos;
	ofImage bulletImage;
	int screenWidth;

public:


	Bullet();
	~Bullet();

	void setPositions(GameObject* obj);
	int checkPositions(GameObject* obj, int *y_position);
	void Draw(GameObject* obj);


};