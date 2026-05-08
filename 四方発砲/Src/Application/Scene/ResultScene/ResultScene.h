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
	Math::Vector2 m_backPos;
	Math::Matrix backmat;

	KdTexture m_starttex;
	Math::Vector2 m_startPos;
	Math::Matrix startmat;
	float m_alpha = 0.0f;
	float m_delta = 0.01f;

	Math::Matrix scoremat;
	Math::Matrix highscoremat;
	Math::Vector2 scorePos;
	Math::Vector2 highscorePos;

	int m_finalScore = 0;
};