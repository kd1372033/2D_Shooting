#pragma once
#include "../BaseScene.h"

class Score;

class TitleScene : public BaseScene
{
public:
	TitleScene() {}
	~TitleScene() { Release(); }

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Release()	override;

private:
	KdTexture m_logoTex;
	KdTexture m_backTex;
	KdTexture m_playerTex;
	KdTexture m_starttex;

	Math::Vector2 m_logoPos;
	Math::Vector2 m_backPos;
	Math::Vector2 m_playerPos;
	Math::Vector2 m_startPos;
	Math::Vector2 m_playerScale;
	Math::Matrix logomat;
	Math::Matrix backmat;
	Math::Matrix playermat;
	Math::Matrix startmat;
	float playerdeg;
	int m_animCnt;

	float m_alpha;
	float m_delta;

};