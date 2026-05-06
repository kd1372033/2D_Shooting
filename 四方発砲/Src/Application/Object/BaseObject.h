#pragma once

class BaseObject
{
public:

	enum class ObjectType
	{
		None,		// 0:タイプ無し
		Player,		// 1:プレイヤー
		Enemy,		// 2:エネミー
		Bullet		// 3:弾
	};

	BaseObject() {}
	virtual ~BaseObject() { Release(); }

	virtual void Update();
	virtual void Draw();
	virtual void Init();
	virtual void OnHit() {}

	ObjectType GetObjType() { return m_objType; }
	Math::Vector2 GetPos() { return m_pos; }
	bool GetAliveFlg() { return m_aliveFlg; }
	int GetRadius() { return m_radius; }


protected:
	virtual void Release();

	ObjectType		m_objType = ObjectType::None;


	KdTexture		m_tex;				//テクスチャ
	Math::Vector2	m_pos;				//座標
	Math::Vector2	m_scale;				//拡大率
	bool			m_aliveFlg = true;	//生存フラグ
	int				m_radius=0;
};