#pragma once
#include "../BaseObject.h"

class GameScene;

class Bullet :public BaseObject
{
public:
	Bullet() {}
	~Bullet()override { Release(); }

	void Update() override;
	void Draw() override;
	void Init() override;
	void Shot(const Math::Vector2& _startPos, float _angle);
	void OnHit() override;

	void SetPos(Math::Vector2 _pos) { m_pos = _pos; }
	void SetOwner(GameScene* _owner) { m_owner = _owner; }

private:
	void Release() override;
	GameScene* m_owner;

	Math::Vector2 m_deg;
	Math::Vector2 m_scale = { 0.5f,0.5f };
	Math::Matrix m_mat;
	int m_moveSpd = 3;
	int m_radius = 16;


};