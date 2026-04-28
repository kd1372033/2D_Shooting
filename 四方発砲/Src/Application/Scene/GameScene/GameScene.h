#pragma once
#include "../BaseScene/BaseScene.h"

class Player;
class Enemy;

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
};