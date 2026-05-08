#include "Enemy.h"
#include "../Player/Player.h"
#include "../../Scene/GameScene/GameScene.h"
//#include "../Score/Score.h"

void Enemy::Update()
{
	if (!m_owner) return;

	if (m_isExploding) {
		// --- 爆発中の処理 ---
		if (++m_explodeTimer > 2) { // 5フレームごとに次のコマへ
			m_explodeTimer = 0;
			m_animCnt++;

			// 10コマ（最後）まで再生したら消滅
			if (m_animCnt >= 10) {
				m_aliveFlg = false;
			}
		}
		return; // 爆発中は移動させないためにここで抜ける
	}

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
	if (m_isExploding) {
		// 爆発中：爆発テクスチャのみ描画
		SHADER.m_spriteShader.SetMatrix(explodeMat);
		Math::Rectangle rc = Math::Rectangle(32 * m_animCnt, 0, 32, 32);
		SHADER.m_spriteShader.DrawTex(&m_explodeTex, 0, 0, &rc);
	}
	else {
		// 生存中：敵本体のみ描画
		SHADER.m_spriteShader.SetMatrix(mat);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(64 * m_animCnt, 0, 64, 64), 1.0f);
	}
}

void Enemy::Init()
{
	//srand(time(0));
	m_objType = ObjectType::Enemy;

	m_tex.Load("Texture/Game/Enemy.png");
	m_explodeTex.Load("Texture/Game/explosion.png");
	m_explodeanimCnt = 0;
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
	if (m_isExploding) return;
	Explode(m_pos);
}

void Enemy::Explode(Math::Vector2 _pos)
{
	m_isExploding = true;
	m_animCnt = 0;      // 0コマ目から開始
	m_explodeTimer = 0; // タイマーリセット

	explodeMat = Math::Matrix::CreateScale(2.0f, 2.0f, 1.0f) * Math::Matrix::CreateTranslation(_pos.x, _pos.y, 0);
}

void Enemy::Release()
{
	m_tex.Release();
}