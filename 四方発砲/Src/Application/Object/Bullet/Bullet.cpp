#include "Bullet.h"
#include <cmath>

void Bullet::Update()
{
	for (int i = 0; i < bulletNum; i++)
	{
		if (!m_aliveFlg[i]) continue;

		// 方向ベクトルに基づいて X/Y 両方を移動
		m_pos[i].x += m_deg[i].x * m_moveSpd;
		m_pos[i].y += m_deg[i].y * m_moveSpd;

		if (m_pos[i].y > 360 || m_pos[i].y < -360 ||
			m_pos[i].x > 640 || m_pos[i].x < -640)
		{
			m_aliveFlg[i] = false;
		}
	}
	for (int i = 0; i < bulletNum; i++)
	{
		m_mat[i] = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0.0f);
	}
}

void Bullet::Draw()
{
	for (int i = 0; i < bulletNum; i++)
	{
		if (!m_aliveFlg[i]) continue;
		SHADER.m_spriteShader.SetMatrix(m_mat[i]);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 32, 32), 1.0f);
	}
}

void Bullet::Init()
{
	m_tex.Load("Texture/Game/bullet.png");
	for (int i = 0; i < bulletNum; i++)
	{
		m_aliveFlg[i] = false;
		m_pos[i] = { 0,0 };
		m_deg[i] = { 0,0 };
	}
}

void Bullet::Shot(const Math::Vector2& _startPos, float _angle)
{
	for (int i = 0; i < bulletNum; i++)
	{
		if (!m_aliveFlg[i])
		{
			m_aliveFlg[i] = true;
			m_pos[i] = _startPos;

			// 角度は度数法で渡される想定 -> ラジアンに変換
			const float deg = DirectX::XMConvertToRadians(_angle);
			m_deg[i].x = std::cosf(deg);
			m_deg[i].y = std::sinf(deg);

			// 初期行列を設定しておく
			m_mat[i] = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0.0f);
			break;
		}
	}
}

void Bullet::Release()
{

}
