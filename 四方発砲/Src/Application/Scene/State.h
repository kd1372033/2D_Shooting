#pragma once
#pragma once

class State
{
public:
	State() {}
	virtual ~State() {}

	virtual void Init() = 0;//純粋仮想関数
	virtual void Update() = 0;//純粋仮想関数
	virtual void Draw() = 0;//純粋仮想関数

	int GetScore() { return m_score; }

protected:
	int m_score;

};
