#include "Main.h"

Bullet::Bullet() {

	bulletImage.load("images/Bullet.png");
	screenWidth = 1275;

}

Bullet::~Bullet() {


}


void Bullet::setPositions(GameObject* obj) {

	//setting bullet position to beside player
	bulletPos.x = obj->x + 50;
	bulletPos.y = obj->y + 30;


}

int Bullet::checkPositions(GameObject* obj, int *y_position) {

	//resetting bullet's position once it goes off screen
	if (bulletPos.x > obj->x + screenWidth) {

		bulletPos.x = 0;
		bulletPos.y = 0;
	}

	*y_position = bulletPos.y;

	return bulletPos.x;
	


}

void Bullet::Draw(GameObject* obj) {

	//moving bullet across the screen
	if (bulletPos.x < obj->x + screenWidth) {

		bulletImage.draw(bulletPos.x, bulletPos.y);
		bulletPos.x += 5;
	}


}