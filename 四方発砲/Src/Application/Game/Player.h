#pragma once
#include "Bullet.h"
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();
	void Hit();

private:
	KdTexture tex;
	Math::Matrix mat;
	Math::Vector2 pos;

	const int bullet = 20;//弾数
};