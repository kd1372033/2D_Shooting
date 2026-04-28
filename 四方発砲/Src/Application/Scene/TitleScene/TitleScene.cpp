#include "TitleScene.h"
#include "../SceneManager.h"

void TitleScene::Init()
{
}

void TitleScene::Update()
{

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
	}
}

void TitleScene::Draw()
{


	// 文字列表示
	SHADER.m_spriteShader.DrawString(0, 0, "Title", Math::Vector4(1, 1, 0, 1));

}

void TitleScene::Release()
{
}