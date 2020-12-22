#include "Main.h"

GameObject::GameObject()
{
	x = 140;
	y = 991;
	speed = 4.5;
	height = 39;
	width = 39;

	img = new ofImage();

}

//--------------------------------------------------------------
GameObject::~GameObject()
{
}


//--------------------------------------------------------------
void GameObject::Draw()
{
	img->draw(x, y);
}

ofImage* GameObject::GetImage()
{
	return img;
}

void GameObject::SetImage(ofImage* image)
{
	delete img; //remove default image
	img = image;
}





