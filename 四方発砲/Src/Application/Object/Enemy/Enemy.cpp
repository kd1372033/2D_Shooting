#include "Enemy.h"

void Enemy::Update()
{
	if (!m_aliveFlg) return;

	for (int i = 0; i < enemyNum; i++)
	{
		
	}


	for (int i = 0; i < enemyNum; i++)
	{
		transmat[i] = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);
		scalemat[i] = Math::Matrix::CreateScale(scale[i].x, scale[i].y, 0);
		mat[i] = scalemat[i] * transmat[i];
	}
}

void Enemy::Draw()
{
	if (!m_aliveFlg) return;

	for (int i = 0; i < enemyNum; i++)
	{
		SHADER.m_spriteShader.SetMatrix(mat[i]);
		SHADER.m_spriteShader.DrawTex(&m_tex[i], Math::Rectangle(0, 0, 64, 64), 1.0f);
	}
}

void Enemy::Init()
{
	for (int i = 0; i < enemyNum; i++)
	{
		m_tex[i].Load("Texture/Game/Enemy.png");
		scale[i] = { 1.0f, 1.0f };
		switch (i)
		{
		case 0:
			m_pos[0] = { 0,328 };
			break;
		case 1:
			m_pos[1] = { 608,328 };
			break;
		case 2:
			m_pos[2] = { 608,0 };
			break;
		case 3:
			m_pos[3] = { 608,-328 };
			break;
		case 4:
			m_pos[4] = { 0,-328 };
			break;
		case 5:
			m_pos[5] = { -608,-328 };
			break;
		case 6:
			m_pos[6] = { -608,0 };
			break;
		case 7:
			m_pos[7] = { -608,328 };
			break;
		default:
			break;
		}
	}
	m_aliveFlg = true;
}

void Enemy::Release()
{
	for (int i = 0; i < enemyNum; i++)
	{
		m_tex[i].Release();
	}
}