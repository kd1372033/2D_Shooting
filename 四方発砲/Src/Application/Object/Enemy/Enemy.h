#pragma once
#include "../BaseObject.h"

class Player;
class GameScene;

class Enemy :public BaseObject
{
public:
	Enemy() {}
	~Enemy() {}

	void Update() override;
	void Draw() override;
	void Init() override;

	void OnHit() override;
	void Explode(Math::Vector2 _pos);	// 爆発
	void SetOwner(GameScene* _owner) { m_owner = _owner; }
	void SetTarget(std::shared_ptr<Player> _player)
	{
		m_player = _player;
	}


private:
	void Release() override;

	// 自機に向かわせる用
	std::shared_ptr<Player> m_player;
	Math::Vector2 m_targetpos;	// 自機座標
	GameScene* m_owner;

	Math::Vector2 m_distance;	// 自機と敵の距離（個別）

	// 敵
	std::vector<Math::Vector2> m_spawnpos;
	KdTexture m_tex;
	KdTexture m_explodeTex;
	int m_animCnt;
	int m_explodeanimCnt;
	int m_timer = 0;
	int m_index = 0;
	bool m_isExploding = false; // 爆発中かどうか
	int  m_explodeTimer = 0;    // アニメのコマ送り用タイマー

	Math::Matrix transmat;
	Math::Matrix scalemat;
	Math::Matrix mat;
	Math::Matrix explodeMat;

	Math::Vector2 m_move;
	Math::Vector2 m_scale;

	float m_angle = 0.0f;
	int m_radius = 32;
	int m_moveSpd;

	// スポーン関係
	int m_spawnTimer = 0;
	int m_spawnCnt = 0;
	const int m_spawnSpan = 60;

	//int m_score = 100;
};