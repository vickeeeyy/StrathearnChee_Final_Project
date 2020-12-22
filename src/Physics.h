#pragma once


class Physics {

public:
	Physics();
	~Physics();

	float playerSpeed;
	float gravity;
	int jumpspeed;
	int fallgroundLevel;
	int groundLevel;
	int move_direction;
	int move_direction2;
	int FallingRock_speed;
	

	//Distances
	float distance;
	float playerDistance;
	float pickupDistance;

	bool collided = false;

	void CheckDistance(int x, int y, GameObject* obj);
	int PlayerCollision(GameObject* obj1, GameObject* obj2);
	bool PickupCollision(GameObject* obj1, GameObject* obj2);
	void PingPong(GameObject* obj);
	void PingPongHorizontal(GameObject* obj);

	int GroundLevel(int x);
	int groundLevels[6500];
	void ReadHeightMap(ofImage* hmap);
	void Move(GameObject* obj, int targetX);

};
