#pragma once
#include "../BaseObject.h"

class Enemy :public BaseObject
{
public:
	Enemy() {}
	~Enemy() { Release(); }

	void Update();
	void Draw();
	void Init();


private:
	void Release();

	std::vector<Math::Vector2> m_spawnpos;
	static const int enemyNum = 8;
	Math::Matrix transmat[enemyNum];
	Math::Matrix scalemat[enemyNum];
	Math::Matrix mat[enemyNum];
	Math::Vector2 m_pos[enemyNum];
	Math::Vector2 scale[enemyNum];
	KdTexture m_tex[enemyNum];


};