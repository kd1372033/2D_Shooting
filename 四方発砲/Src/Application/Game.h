#pragma once
#include "State.h"
#include "SceneManager.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Game/Bullet.h"

class Game : public State
{
public:
	Game();
	~Game();

	void Init() override;
	void Update() override;
	void Draw() override;

private:
	Player player;
	Enemy enemy;
	Bullet bullet;
};

