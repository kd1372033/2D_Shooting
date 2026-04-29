#include "Game.h"

Game::Game()
{
	tag = Stage::Game;
}

Game::~Game()
{
}

void Game::Init()
{
	player.Init();
	enemy.Init();
	bullet.Init();
}

void Game::Update()
{
	player.Update();
	enemy.Update();
	bullet.Update();
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		SCENEMANAGER.ChangState(new Result());
	}
}

void Game::Draw()
{
	player.Draw();
	enemy.Draw();
	bullet.Draw();

	SHADER.m_spriteShader.DrawString(0, 0, "Game", Math::Vector4(1, 1, 0, 1));

}
