#include "Player.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/GameScene/GameScene.h"
#include "../Bullet/Bullet.h"
#include "../Enemy/Enemy.h"
#include "../Score/Score.h"

void Player::Update()
{
	//　死亡処理
	if (m_hp <= 0) {
		std::vector<int> diePatterns = { 9, 10, 11, 12 };

		if (++m_dieTimer > 30) {
			if (m_dieIndex < (int)diePatterns.size() - 1) {
				m_dieIndex++;
				m_animCnt = diePatterns[m_dieIndex];
			}
			else {
				// アニメーションが終わったらシーン遷移
				SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
			}
			m_dieTimer = 0;
		}

		// 行列更新
		transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
		scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1.0f);
		mat = scalemat * transmat;
		return;
	}

	// --- 通常時のアニメーション制御 ---
	std::vector<int> patterns;
	if (m_hp >= 3) { patterns = { 0, 1, 2, 1 }; }
	else if (m_hp == 2) { patterns = { 3, 4, 5, 4 }; }
	else if (m_hp == 1) { patterns = { 6, 7, 8, 7 }; }

	if (++m_animTimer > 10) {
		m_animIndex = (m_animIndex + 1) % patterns.size();
		m_animCnt = patterns[m_animIndex];
		m_animTimer = 0;
	}


	transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1.0f);
	mat = scalemat * transmat;

	//弾
	if (!m_canControl) return;
	bool Up = (GetAsyncKeyState(VK_UP) & 0x8000);
	bool Down = (GetAsyncKeyState(VK_DOWN) & 0x8000);
	bool Left = (GetAsyncKeyState(VK_LEFT) & 0x8000);
	bool Right = (GetAsyncKeyState(VK_RIGHT) & 0x8000);

	// どの方角に撃つか判定
	int shotDir = -1;

	if (Up && Right)      shotDir = NE;
	else if (Up && Left)  shotDir = NW;
	else if (Down && Right) shotDir = SE;
	else if (Down && Left)  shotDir = SW;
	else if (Up)    shotDir = N;
	else if (Down)  shotDir = S;
	else if (Left)  shotDir = W;
	else if (Right) shotDir = E;

	if (m_shotTimer > 0) m_shotTimer--;

	// 3. 発射処理（1つのブロックにまとめる）
	if (shotDir != -1 && m_shotTimer <= 0) {
		auto bullet = std::make_shared<Bullet>();
		bullet->Init();
		bullet->SetPos(m_pos);
		bullet->Shot(m_pos, (float)shotDir); // 角度を渡す
		bullet->SetOwner(m_owner); // オーナーを渡す
		m_owner->AddObject(bullet);
		m_shotTimer = 15;
	}

	if (!m_owner) return;
	if (m_mutekiTimer > 0) m_mutekiTimer--;

	for (auto& obj : m_owner->GetObjList())
	{
		if (obj.get() == this) continue;

		// 1. 敵かどうかをチェック
		if (obj->GetObjType() == ObjectType::Enemy)
		{
			if (!obj->GetAliveFlg()) continue;

			Math::Vector2 v = obj->GetPos() - m_pos;
			float distance = v.Length();
			float hitDistance = m_radius + obj->GetRadius();

			if (distance < hitDistance)
			{
				if (m_mutekiTimer <= 0)
				{
					obj->OnHit();
					this->OnHit();
					m_mutekiTimer = 30;
				}
			}
		}
	}

	// デバッグキー
	if (GetAsyncKeyState('Z') & 0x8000) {
		m_hp = 3; // 回復
	}
	if (GetAsyncKeyState('X') & 0x8000) {
		m_hp = 0; // 即死
	}

}

void Player::Draw()
{
	Math::Rectangle rc;

	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(640 * m_animCnt, 0, 640, 640), 1.0f);
}

void Player::Init()
{
	m_tex.Load("Texture/Game/player.png");
	m_pos = {};		//0,0で初期化
	m_scale = { 0.5f,0.5f };
	m_aliveFlg = true;
	m_animCnt = 0;
	m_shotTimer = 15.0f;
	m_objType = ObjectType::Player;

	m_hp = 3;
	m_dieTimer = 0;
	m_dieIndex = 0;
	m_animTimer = 0;
	m_animIndex = 0;
	m_isCleanupDone = false;
	m_mutekiTimer = 0;
}

void Player::OnHit()
{
	m_hp -= 1;
}

void Player::Release()
{
	m_tex.Release();
}