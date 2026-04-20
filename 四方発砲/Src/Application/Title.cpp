#include "Title.h"

Title::Title()
{
	tag = Stage::Title;
}

Title::~Title()
{
}

void Title::Init()
{

}

void Title::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SCENEMANAGER.ChangState(new Game());
	}
}

void Title::Draw()
{
	SHADER.m_spriteShader.DrawString(0, 0, "Title", Math::Vector4(1, 1, 0, 1));

}
