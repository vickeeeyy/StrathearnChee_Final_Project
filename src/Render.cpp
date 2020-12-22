#include "Main.h"

Render::Render()
{
}


Render::~Render()
{
}

void Render::Draw(GameObject* obj)
{
	obj->GetImage()->draw(obj->x, obj->y);
}

