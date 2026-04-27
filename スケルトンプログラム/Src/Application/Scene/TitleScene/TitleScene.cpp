#include "TitleScene.h"

void TitleScene::Init()
{
}

void TitleScene::Update()
{
}

void TitleScene::Draw()
{


	// 文字列表示
	SHADER.m_spriteShader.DrawString(0, 0, "Title", Math::Vector4(1, 1, 0, 1));

}

void TitleScene::Release()
{
}