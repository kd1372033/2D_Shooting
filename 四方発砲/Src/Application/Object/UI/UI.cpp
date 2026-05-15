#include "UI.h"

void UI::Update()
{
	m_alpha = 0.3f;
	controlMat = Math::Matrix::CreateTranslation(m_controlPos.x, m_controlPos.y, 0.0f);
}

void UI::Draw()
{
	SHADER.m_spriteShader.SetMatrix(controlMat);
	Math::Rectangle controlrc = { 0,0,1280,720 };
	Math::Color controlcolor = { 1.0f, 1.0f, 1.0f, m_alpha };
	SHADER.m_spriteShader.DrawTex(&m_controlTex, 0, 0,
		&controlrc, &controlcolor);
}

void UI::Init()
{
	m_controlTex.Load("Texture/Game/Control.png");
	m_controlPos = { 0,0 };
	m_alpha = 1.0f;
}

void UI::Release()
{

}
