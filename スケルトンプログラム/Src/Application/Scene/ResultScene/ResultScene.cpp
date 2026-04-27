#include "ResultScene.h"

void ResultScene::Init()
{
}

void ResultScene::Update()
{
}

void ResultScene::Draw()
{

	// 文字列表示
	SHADER.m_spriteShader.DrawString(0, 0, "Result", Math::Vector4(1, 1, 0, 1));
}

void ResultScene::Release()
{
}