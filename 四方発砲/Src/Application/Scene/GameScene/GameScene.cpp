#include "GameScene.h"
#include "../SceneManager.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"
#include "../../Object/Bullet/Bullet.h"

void GameScene::Init()
{
	m_player = std::make_shared<Player>();
	//m_enemy = std::make_shared<Enemy>();
	m_bullet = std::make_shared<Bullet>();

	m_player->Init();
	//m_enemy->Init();
	m_bullet->Init();
	//m_enemy->SetTarget(m_player);
}

void GameScene::Update()
{
	m_player->Update();
	//m_enemy->Update();
	m_bullet->Update();

	// 自機の位置を取得
	Math::Vector2 pPos = m_player->GetPos();

	// 入力判定
	bool up = (GetAsyncKeyState('W') & 0x8000);
	bool down = (GetAsyncKeyState('S') & 0x8000);
	bool left = (GetAsyncKeyState('A') & 0x8000);
	bool right = (GetAsyncKeyState('D') & 0x8000);

	// --- 8方向の判定 ---
	if (up && right) {
		m_bullet->Shot(pPos, NE);
	}
	else if (up && left) {
		m_bullet->Shot(pPos, NW);
	}
	else if (down && right) {
		m_bullet->Shot(pPos, SE);
	}
	else if (down && left) {
		m_bullet->Shot(pPos, SW);
	}
	else if (up) {
		m_bullet->Shot(pPos, N);
	}
	else if (down) {
		m_bullet->Shot(pPos, S);
	}
	else if (left) {
		m_bullet->Shot(pPos, W);
	}
	else if (right) {
		m_bullet->Shot(pPos, E);
	}


	if (GetAsyncKeyState('R') & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
	}
}

void GameScene::Draw()
{
	m_bullet->Draw();

	m_player->Draw();
	//m_enemy->Draw();

	// 文字列表示
	SHADER.m_spriteShader.DrawString(0, 0, "Game", Math::Vector4(1, 1, 0, 1));
}

void GameScene::Release()
{

}