#include "Enemy.h"
#include "../Player/Player.h"
#include "../../Scene/GameScene/GameScene.h"

void Enemy::Update()
{
	if (!m_owner) return;

	std::vector<int> patterns = { 0, 1 };

	static int timer = 0;
	static int index = 0; // 配列のどこを指すか

	if (++timer > 10) {
		index = (index + 1) % patterns.size();
		m_animCnt = patterns[index];
		timer = 0;
	}

	if (m_player) {
		m_targetpos = m_player->GetPos();
	}

	// --- 2. 移動処理 (ここをスッキリさせます) ---
	m_distance = m_targetpos - m_pos; // ターゲットへのベクトル
	float len = m_distance.Length();   // 距離

	if (len > 1.0f) // ある程度離れているなら追跡
	{
		Math::Vector2 moveDir = m_distance / len; // 正規化（方向を出す）
		m_pos += moveDir * (float)m_moveSpd;      // 移動
	}

	scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1.0f);
	transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	mat = scalemat * transmat;
}

void Enemy::Draw()
{
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(64 * m_animCnt, 0, 64, 64), 1.0f);
}

void Enemy::Init()
{
	//srand(time(0));
	m_objType = ObjectType::Enemy;

	m_tex.Load("Texture/Game/Enemy.png");
	m_animCnt = 0;
	m_index = 0;
	m_timer = 0;
	m_moveSpd = 3;
	m_scale = { 1.0f, 1.0f };
	m_aliveFlg = true;
	int r = rand() % 8;
	switch (r)
	{
	case 0: m_pos = { 0, 328 };     break;	//北
	case 1: m_pos = { 608, 328 };   break;	//北東
	case 2: m_pos = { 608, 0 };     break;	//東
	case 3: m_pos = { 608, -328 };  break;	//南東
	case 4: m_pos = { 0, -328 };    break;	//南
	case 5: m_pos = { -608, -328 }; break;	//南西
	case 6: m_pos = { -608, 0 };    break;	//西
	case 7: m_pos = { -608, 328 };  break;	//北西
	}
}

void Enemy::OnHit()
{
	m_aliveFlg = false;
}

void Enemy::Release()
{
	m_tex.Release();
}