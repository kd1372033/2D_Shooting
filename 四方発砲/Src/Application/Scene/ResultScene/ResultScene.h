#pragma once
#include "../BaseScene.h"

class Score;

class ResultScene : public BaseScene
{
public:
	ResultScene() {}
	~ResultScene() {}

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Release()	override;


private:
	std::shared_ptr<Score> m_score;
	KdTexture m_backTex;
	KdTexture m_scoreTex;
	KdTexture m_highscoreTex;
	KdTexture m_starttex;
	KdTexture m_resultTex;

	Math::Vector2 m_backPos;
	Math::Vector2 m_startPos;
	Math::Vector2 scorePos;
	Math::Vector2 highscorePos;
	Math::Vector2 m_resultPos;

	Math::Matrix backmat;
	Math::Matrix startmat;
	Math::Matrix scoremat;
	Math::Matrix highscoremat;
	Math::Matrix resultmat;

	float m_alpha = 0.0f;
	float m_delta = 0.01f;

	int m_finalScore = 0;

	bool m_resultFlg = false;
};