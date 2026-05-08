#pragma once
#include "../BaseObject.h"

class GameScene;
class Score;
class Enemy;

class Player :public BaseObject
{
public:
	Player() {}
	~Player()override { /*Release();*/ }

	void Update()override;
	void Draw()override;
	void Init()override;
	void OnHit()override;

	void SetScore(std::shared_ptr<Score> _score) { m_score = _score; }
	void SetOwner(GameScene* _owner) { m_owner = _owner; }

private:

	void Release()override;

	std::shared_ptr<Score> m_score;
	std::shared_ptr<Enemy> m_enemy;
	Math::Matrix transmat;
	Math::Matrix scalemat;
	Math::Matrix mat;
	int m_hp = 3;
	float m_shotTimer;
	int m_animCnt = 0;	//アニメーションカウンタ
	int m_radius = 160;

	GameScene* m_owner;

	//発射角
	static const int N = 90;	//北
	static const int W = 180;	//西
	static const int S = 270;	//南
	static const int E = 360;	//東
	static const int NE = 29;	//北東
	static const int NW = 151;	//北西
	static const int SE = 331;	//南東
	static const int SW = 209;	//南西
};