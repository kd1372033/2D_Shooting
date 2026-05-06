#include "Bullet.h"
#include "../../Scene/GameScene/GameScene.h"

void Bullet::Update()
{
	// 方向ベクトルに基づいて X/Y 両方を移動
	m_pos.x += m_deg.x * m_moveSpd;
	m_pos.y += m_deg.y * m_moveSpd;

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);

	if (m_pos.y > 360 || m_pos.y < -360 ||
		m_pos.x > 640 || m_pos.x < -640)
	{
		OnHit();
		return;
	}

	if (!m_owner) return;

	for (auto& obj : m_owner->GetObjList())
	{
		if (obj.get() == this) continue;

		if (obj->GetObjType() == ObjectType::Enemy)
		{
			Math::Vector2 v = obj->GetPos() - m_pos;

			float distance = v.Length();
			float hitDistance = m_radius + obj->GetRadius();

			// 判定
			if (distance < hitDistance)
			{
				// Hit時の処理
				obj->OnHit();

				// 弾自身も消える場合
				m_aliveFlg = false;
			}
		}
	}
}


void Bullet::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 32, 32), 1.0f);
}

void Bullet::Init()
{
	m_tex.Load("Texture/Game/bullet.png");
	m_aliveFlg = true;
	m_deg = { 0,0 };
	m_objType = ObjectType::Bullet;
}

void Bullet::Shot(const Math::Vector2& _startPos, float _angle)
{
	m_pos = _startPos;

	// 速度を計算
	m_deg.x = cos(DirectX::XMConvertToRadians(_angle)) * (float)m_moveSpd;
	m_deg.y = sin(DirectX::XMConvertToRadians(_angle)) * (float)m_moveSpd;
}

void Bullet::OnHit()
{
	m_aliveFlg = false;
}

void Bullet::Release()
{

}
