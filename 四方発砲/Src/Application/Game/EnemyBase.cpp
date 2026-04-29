#include "EnemyBase.h"

EnemyBase::EnemyBase()
{
	tex.Load("Texture/Game/enemy.png");

}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update() {
	//座標確定処理
	pos += move;

	mat = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
}