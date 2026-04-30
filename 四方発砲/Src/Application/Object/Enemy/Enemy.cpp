#include "Enemy.h"
#include "../Player/Player.h"

void Enemy::Update()
{
	int activeCount = 0;
	for (int i = 0; i < enemyNum; i++)
	{
		if (m_aliveFlg[i]) activeCount++;
	}

	// --- 4体未満なら、新しい敵を1体出現させる ---
	if (activeCount < 4)
	{
		// 配列の中から、出現していない敵を探す
		for (int i = 0; i < enemyNum; i++)
		{
			if (!m_aliveFlg[i])
			{
				m_aliveFlg[i] = true;
				int r = rand() % 8;
				SetPosByIndex(i, r);
				break; // 1体出したのでループを抜ける
			}
		}
	}

	// 自機の座標を取得（ループの外で1回取ればOK）
	if (m_player)
	{
		m_targetpos = m_player->GetPos();
	}

	for (int i = 0; i < enemyNum; i++)
	{
		// 1. 自機へのベクトルを計算
		m_distance[i] = m_targetpos - m_pos[i];

		// 2. 移動処理
		float len = m_distance[i].Length(); // 自機までの距離
		if (len > 0.1f) // 重なり防止
		{
			// 正規化（方向ベクトル）を求めて、速度(m_moveSpd)を掛ける
			Math::Vector2 moveDir = m_distance[i] / len;
			m_pos[i] += moveDir * (float)m_moveSpd;
		}

		// 3. 行列の更新
		// 注意：ScaleのZは2Dでも1.0fにしておくのが無難です
		scalemat[i] = Math::Matrix::CreateScale(m_scale[i].x, m_scale[i].y, 1.0f);
		transmat[i] = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);
		mat[i] = scalemat[i] * transmat[i];
	}
}

void Enemy::Draw()
{
	for (int i = 0; i < enemyNum; i++)
	{
		if (!m_aliveFlg[i]) continue;

		SHADER.m_spriteShader.SetMatrix(mat[i]);
		SHADER.m_spriteShader.DrawTex(&m_tex[i], Math::Rectangle(0, 0, 64, 64), 1.0f);
	}
}

void Enemy::Init()
{
	srand(time(0));
	m_spawnTimer = 0;
	m_spawnCnt = 0;

	for (int i = 0; i < enemyNum; i++)
	{
		m_tex[i].Load("Texture/Game/Enemy.png");
		m_scale[i] = { 1.0f, 1.0f };
		m_aliveFlg[i] = false;
		int r = rand() % 8;
		SetPosByIndex(i, r);
	}
}

void Enemy::Release()
{
	for (int i = 0; i < enemyNum; i++)
	{
		m_tex[i].Release();
	}
}

void Enemy::SetPosByIndex(int enemyIdx, int spawnPointIdx)
{
	switch (spawnPointIdx)
	{
	case 0: m_pos[enemyIdx] = { 0, 328 };     break;	//北
	case 1: m_pos[enemyIdx] = { 608, 328 };   break;	//北東
	case 2: m_pos[enemyIdx] = { 608, 0 };     break;	//東
	case 3: m_pos[enemyIdx] = { 608, -328 };  break;	//南東
	case 4: m_pos[enemyIdx] = { 0, -328 };    break;	//南
	case 5: m_pos[enemyIdx] = { -608, -328 }; break;	//南西
	case 6: m_pos[enemyIdx] = { -608, 0 };    break;	//西
	case 7: m_pos[enemyIdx] = { -608, 328 };  break;	//北西
	}
}
