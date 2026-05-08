#pragma once
#include "../BaseObject.h"

class Score :public BaseObject
{
public:
	Score(){}
	~Score(){}

	void DrawNumber(float x, float y, int value);
	void Draw() override;
	void Init() override;

	void Load();
	void Save();
	void Add(int _points) { m_value += _points; }


	int GetSaveScore(int index) { return saveScore[index]; }
	int GetValue() { return m_value; } // 現在のスコアを返す
	int GetHighScore() { return saveScore[0]; }

	void Reset() { m_value = 0; }

	static const int saveNum = 50;
	int saveScore[saveNum];
private:
	int m_value = 0;      // 現在のスコア
	int m_hiScore = 0;    // ハイスコア（必要であれば）

	KdTexture m_fontTex;
};


//	void AddScore(int _pts) { score += _pts; }
//
//	void SetScore(int& _hitscore) {score = _hitscore;}
//
//
//private:
//	int score;
//};