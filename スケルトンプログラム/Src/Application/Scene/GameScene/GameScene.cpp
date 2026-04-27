#include "GameScene.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"

void GameScene::Init()
{
	m_player = std::make_shared<Player>();
	m_enemy = std::make_shared<Enemy>();

	m_player->Init();
	m_enemy->Init();
}

void GameScene::Update()
{
	m_player->Update();
	m_enemy->Update();
	
}

void GameScene::Draw()
{
	m_player->Draw();
	m_enemy->Draw();
	// 文字列表示
	SHADER.m_spriteShader.DrawString(0, 0, "Game", Math::Vector4(1, 1, 0, 1));
}

void GameScene::Release()
{

}