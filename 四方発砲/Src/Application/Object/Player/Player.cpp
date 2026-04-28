#include "Player.h"

void Player::Update()
{

	transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1.0f);
	mat = scalemat * transmat;
}

void Player::Draw()
{
	Math::Rectangle rc;
	switch (m_animCnt)
	{
	case 0:
		rc = { 0,0,64,64 };
		break;
	case 1:
		rc = { 64,0,64,64 };
		break;
	case 2:
		rc = { 128,0,64,64 };
		break;
	case 3:
		rc = { 192,0,64,64 };
		break;

	default:
		break;
	}
	
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 650, 650), 1.0f);
}

void Player::Init()
{
	m_tex.Load("Texture/Game/player.png");
	m_pos = {};		//0,0で初期化
	m_scale = {0.5f,0.5f};
	m_aliveFlg = true;
}

void Player::Release()
{
	m_tex.Release();
}