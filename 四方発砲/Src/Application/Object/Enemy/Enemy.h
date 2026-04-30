#pragma once
#include "../BaseObject.h"

class Player;

class Enemy :public BaseObject
{
public:
	Enemy() {}
	~Enemy() {}

	void Update();
	void Draw();
	void Init();

	void SetTarget(std::shared_ptr<Player> _player)
	{
		m_player = _player;
	}

private:
	void Release();
	void SetPosByIndex(int enemyIdx, int spawnPointIdx);

	// 自機に向かわせる用
	std::shared_ptr<Player> m_player;
	Math::Vector2 m_targetpos;	// 自機座標

	static const int enemyNum = 32;
	Math::Vector2 m_distance[enemyNum];	// 自機と敵の距離（個別）

	// 敵
	std::vector<Math::Vector2> m_spawnpos;
	KdTexture m_tex;

	Math::Matrix transmat[enemyNum];
	Math::Matrix scalemat[enemyNum];
	Math::Matrix mat[enemyNum];

	Math::Vector2 m_pos[enemyNum];
	Math::Vector2 m_move[enemyNum];
	Math::Vector2 m_scale[enemyNum];

	float m_angle[enemyNum];
	bool m_aliveFlg[enemyNum];

	const int m_moveSpd = 3;

	// スポーン関係
	int m_spawnTimer = 0;
	int m_spawnCnt = 0;
	const int m_spawnSpan = 60;
};