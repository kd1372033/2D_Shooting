#pragma once

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Init();
	void Update();
	void Draw();
	void Hit();
	void Shot(Math::Vector2 pos, float targetangle);

	bool GetAlive() { return alive; }
	Math::Vector2 GetPos() { return pos; }
	float GetRadius() { return radius; }
private:
	const float radius = 8.0f;
	bool alive;
	Math::Vector2 pos;

	KdTexture tex;

};