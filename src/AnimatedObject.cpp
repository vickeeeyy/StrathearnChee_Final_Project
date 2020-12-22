#include "Main.h"

AnimatedObject::AnimatedObject()
{
	numFrames = 0;
	currentFrame = -1;
}

AnimatedObject::~AnimatedObject()
{
}

bool AnimatedObject::Advance()
{
	bool result = false;

	if (numFrames > 0)
	{
		currentFrame++;
		if (currentFrame > lastFrame) 
			currentFrame = firstFrame;
		result = true;
	}

	return result;
}

bool AnimatedObject::SetNumFrames(int n)
{
	bool result = false;

	if (n >= 0)
	{
		numFrames = n;
		lastFrame = n - 1;
		firstFrame = 0;
		if (n > 0)
		{
			if (currentFrame<firstFrame || currentFrame>lastFrame)
				currentFrame = firstFrame;
		}
		else
			currentFrame = -1;

		result = true;
	}

	return result;
}

bool AnimatedObject::SetNumFrames(int n1, int n2)
{
	bool result = false;

	if (n2 >= n1 && n1 >= 0)
	{
		numFrames = n2 - n1 + 1;
		firstFrame = n1;
		lastFrame = n2;
		if (numFrames > 0)
		{
			if (currentFrame<firstFrame || currentFrame>lastFrame)
				currentFrame = firstFrame;
		}
		else
			currentFrame = -1;

		result = true;
	}

	return result;
}


void AnimatedObject::Draw()
{
	if (currentFrame >= 0)
		frames[currentFrame].draw(x, y);

	
}