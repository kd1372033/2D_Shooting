#include "Result.h"

Result::Result()
{
	tag = Stage::Result;
}

Result::~Result()
{

}

void Result::Init()
{

}

void Result::Update()
{
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
	{
		SCENEMANAGER.ChangState(new Title());
	}
}

void Result::Draw()
{
	SHADER.m_spriteShader.DrawString(0, 0, "Result", Math::Vector4(1, 1, 0, 1));
}
