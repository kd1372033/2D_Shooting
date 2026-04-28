#include "ResultScene.h"
#include "../SceneManager.h"

void ResultScene::Init()
{
}

void ResultScene::Update()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}
}

void ResultScene::Draw()
{

	// 文字列表示
	SHADER.m_spriteShader.DrawString(0, 0, "Result", Math::Vector4(1, 1, 0, 1));
}

void ResultScene::Release()
{
}