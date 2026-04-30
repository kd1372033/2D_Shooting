#pragma once
#include "../BaseScene/BaseScene.h"

class Player;
class Enemy;
class Bullet;

class GameScene : public BaseScene
{
public:
	GameScene() {}
	~GameScene()override {}

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Release()	override;

private:
	std::shared_ptr<Player> m_player;
	std::shared_ptr<Enemy> m_enemy;
	std::shared_ptr<Bullet> m_bullet;

	static const int N = 90;	//北
	static const int W = 180;	//西
	static const int S = 270;	//南
	static const int E = 360;	//東
	static const int NE = 29;	//北東
	static const int NW = 151;	//北西
	static const int SE = 331;	//南東
	static const int SW = 210;	//南西
};