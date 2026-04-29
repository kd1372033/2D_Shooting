#pragma once

class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase();

	virtual void Init() = 0 { return; }//純粋仮想関数
	void Update();
	virtual void Draw() = 0 { return; }//仮想関数	
protected:
	KdTexture  tex;
	Math::Vector2  pos;
	Math::Vector2  move;
	Math::Matrix  mat;
};

