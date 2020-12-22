#include "Main.h"


//--------------------------------------------------------------
Physics::Physics()
{
	gravity = 9.8;
	jumpspeed = 70;
	playerSpeed = 5;
	move_direction = 1;
	move_direction2 = 1;
	FallingRock_speed = 3;
	fallgroundLevel = 1030;
}

//--------------------------------------------------------------
Physics::~Physics()
{
}


//--------------------------------------------------------------
void Physics::ReadHeightMap(ofImage* hmap)
{
	//reading black pixels on image and storing into an array
	ofPixels pixels = hmap->getPixels();
	int w = hmap->getWidth();
	int h = hmap->getHeight();
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
		{
			ofColor c = pixels.getColor(i, j);
			if (c.r == 0 && c.g == 0 && c.b == 0)
			{
				groundLevels[i] = j;
				break;
			}
		}
}

//--------------------------------------------------------------
int Physics::GroundLevel(int x)
{
	return groundLevels[x];
}

//--------------------------------------------------------------
void Physics::Move(GameObject* obj, int targetX)
{
	//set ground level where the player wants to go (target x)
	//can we move forward
	int dy = GroundLevel(targetX) - (obj->y + obj->height);
	if (dy > -5)
	{
		obj->x = targetX;
		if (dy < 5)
			obj->y += dy; 
	}

	int groundLevel = GroundLevel(obj->x);

	//jump
	if (obj->jump == true)
	{
		//move using accleration function
		obj->y = obj->y0 - obj->v0 * obj->t + 0.5 * gravity * obj->t*obj->t;
		obj->t++;
		//reached the ground?
		if (obj->y > groundLevel - obj->height)
		{
			obj->y = groundLevel - obj->height;
			obj->jump = false;
		}
	}
	else //check if player has fallen
	{
		if (obj->y < groundLevel - obj->height)
		{
			obj->jump = true;
			obj->t = 0;
			obj->y0 = obj->y;
			obj->v0 = 0;
		}
	}

}


//--------------------------------------------------------------
void Physics::CheckDistance(int x, int y, GameObject* obj)
{
	//checkng distance between bullet and player
	distance = sqrt((x - obj->x) * (x - obj->x) + (y - obj->y) * (y - obj->y));

	if (distance < 100) {
		obj->x = 9000;
		obj->x = 9000;
	}

}


//--------------------------------------------------------------
void Physics::PingPong(GameObject* obj)
{
	//moving falling enemy up and down
	if (move_direction == 1)
		obj->y++;
	else
		obj->y--;
	if (obj->y <= obj->min || obj->y >= obj->max){
		move_direction = move_direction * -1;
	}
}

//--------------------------------------------------------------
void Physics::PingPongHorizontal(GameObject* obj)
{
	//moving land enemy side to side
	if (move_direction2 == 1)
		obj->x++;
	else
		obj->x--;

	if (obj->x <= obj->min || obj->x >= obj->max) {
		move_direction2 = move_direction2 * -1;
	}

}

//--------------------------------------------------------------

int Physics::PlayerCollision(GameObject* obj1, GameObject* obj2)
{
	//checking collision between player and enemies
	playerDistance = sqrt((obj1->x - obj2->x) * (obj1->x - obj2->x) + (obj1->y - obj2->y) * (obj1->y - obj2->y));

	return playerDistance;

}

//--------------------------------------------------------------

bool Physics::PickupCollision(GameObject* obj1, GameObject* obj2)
{
	//checking collision between player and pickups
	collided = false; 
	pickupDistance = sqrt((obj1->x - obj2->x) * (obj1->x - obj2->x) + (obj1->y - obj2->y) * (obj1->y - obj2->y));	

	if (pickupDistance < 100) {
		obj2->x = 2000;
		obj2->y = 2000;
		collided = true; 
	}

	return collided;

}

