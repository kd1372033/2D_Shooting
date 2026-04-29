#pragma once
#include "State.h"
#include "SceneManager.h"

class Result :public State
{
public:
	Result();
	~Result();

	void Init() override;
	void Update() override;
	void Draw() override;

private:

};

