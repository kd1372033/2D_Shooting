#include "Player.h"

Player::Player()
{
	tex.Load("Texture/Game/player.png");
	pos = { 0,0 };
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	//弾の発射処理

	//自機は固定のため移動なし
	mat = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
}

void Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(&tex, Math::Rectangle(0, 0, 64, 64), 1.0f);
}

void Player::Hit()
{
}
