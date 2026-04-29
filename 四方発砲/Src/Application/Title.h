#pragma once
#include "State.h"
#include "SceneManager.h"

class Title : public State
{
public:
	Title();
	~Title();

	void Init() override;
	void Update() override;
	void Draw() override;
private:

};

