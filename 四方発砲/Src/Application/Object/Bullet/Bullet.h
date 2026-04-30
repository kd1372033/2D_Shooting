#pragma once
#include "../BaseObject.h"

class Bullet :public BaseObject
{
public:
	Bullet() {}
	~Bullet()override { Release(); }

	void Update() override;
	void Draw() override;
	void Init() override;

	void Shot(const Math::Vector2& _startPos, float _angle);

private:
	void Release() override;

	static const int bulletNum = 20;
	Math::Vector2 m_pos[bulletNum];
	Math::Vector2 m_deg[bulletNum];
	Math::Vector2 m_scale = { 0.5f,0.5f };
	Math::Matrix m_mat[bulletNum];
	bool m_aliveFlg[bulletNum];
	const int m_moveSpd = 10;
};