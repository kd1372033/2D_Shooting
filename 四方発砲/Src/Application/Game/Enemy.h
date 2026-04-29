#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw();
	void Hit();

	bool GetAlive() { return alive; }
	Math::Vector2 GetPos() { return pos; }
	float GetRadius() { return radius; }//円判定するために
private:
	bool alive;
	Math::Vector2 pos;
	float radius;

	KdTexture tex;
	Math::Matrix mat;
	const int enemy = 20;//敵の数

};

