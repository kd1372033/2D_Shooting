#include "Enemy.h"

void Enemy::Update()
{
	for (int i = 0; i < enemyNum; i++)
	{
		if (!aliveFlg[i])
		{
			m_pos[i].x = player.m_posX;
			m_pos[i].y = player.m_posY;
			//enemy[i].m_moveX = 4;
			//enemy[i].m_moveY = 4;
			//enemy[i].m_moveX = rand() % 11-5;
			//enemy[i].m_moveY = rand() % 11-5;

			//自機から見た敵の角度を求める
			deg = GetAngleDeg(player.m_posX, player.m_posY, enemy.m_posX, enemy.m_posY);

			//指定した角度とスピードで弾を飛ばす
			enemy[i].m_speed = 5;
			enemy[i].m_moveX = cos(DirectX::XMConvertToRadians(deg)) * enemy[i].m_speed;
			enemy[i].m_moveY = sin(DirectX::XMConvertToRadians(deg)) * enemy[i].m_speed;

			enemy[i].m_srcRect = { 0,0,32,32 };
			enemy[i].m_color = { rand() / (float)RAND_MAX,rand() / (float)RAND_MAX,
								rand() / (float)RAND_MAX,1.0f };

			enemy[i].m_count = 0;
			enemy[i].m_iHomingFlg = true;	//ホーミングする！
			enemy[i].m_iFlg = true;
			break;
		}
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