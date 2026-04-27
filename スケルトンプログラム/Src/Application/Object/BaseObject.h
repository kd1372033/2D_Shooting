#pragma once

//　全てのゲーム内オブジェクトの基底クラス
class BaseObject
{
public:
	BaseObject() {}
	virtual ~BaseObject() { Release(); }

	virtual void Update();
	virtual void Draw();
	virtual void Init();

protected: // このクラスと派生先のクラス内からアクセス可能
	virtual void Release();

	KdTexture		m_tex;				//テクスチャ
	Math::Vector2	m_pos;				//座標
	Math::Vector2	m_scale;				//拡大率
	bool			m_aliveFlg = true;	//生存フラグ
};