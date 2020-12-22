#pragma once


class Score{

public:

	Score();
	~Score();

	int AddScore_Coin();
	int AddScore_Chest();
	int InitializeScore();

	int currentScore;

};
