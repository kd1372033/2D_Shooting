#pragma once

class BaseObject
{
public:
	BaseObject() {}
	virtual ~BaseObject() { Release(); }

	virtual void Update();
	virtual void Draw();
	virtual void Init();

protected:
	virtual void Release();

	KdTexture		m_tex;				//テクスチャ
	Math::Vector2	m_pos;				//座標
	Math::Vector2	m_scale;				//拡大率
	bool			m_aliveFlg = true;	//生存フラグ
};