#include "Player.h"
#include "../../Scene/GameScene/GameScene.h"
#include "../Bullet/Bullet.h"

void Player::Update()
{
	// アニメーション制御
	std::vector<int> patterns;
	if (m_hp >= 3) { patterns = { 0, 1, 2, 1 }; }
	else if (m_hp == 2) { patterns = { 3, 4, 5, 4 }; }
	else { patterns = { 6, 7, 8, 7 }; }

	// タイマーでコマを進める
	static int timer = 0;
	static int index = 0; // 配列のどこを指すか

	if (++timer > 10) {
		index = (index + 1) % patterns.size(); // 0, 1, 2, 3, 0... と繰り返す
		m_animCnt = patterns[index];           // 現在の番号を代入
		timer = 0;
	}

	//弾
	bool Up = (GetAsyncKeyState('W') & 0x8000);
	bool Down = (GetAsyncKeyState('S') & 0x8000);
	bool Left = (GetAsyncKeyState('A') & 0x8000);
	bool Right = (GetAsyncKeyState('D') & 0x8000);

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
		m_shotTimer = 15; // ★ここで連射速度をセット（10なら秒間6発、5なら秒間12発）
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
				this->OnHit();
			}
		}
	}

	transmat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	scalemat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1.0f);
	mat = scalemat * transmat;
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
	m_shotTimer = 30.0f;
	m_objType = ObjectType::Player;
}

void Player::OnHit()
{
	m_hp -= 1;
}

void Player::Release()
{
	m_tex.Release();
}