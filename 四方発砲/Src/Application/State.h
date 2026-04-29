#pragma once

enum class Stage
{
	Title,
	Game,
	Result,
};

class State
{
public:
	State() {}
	virtual ~State() {}

	virtual void Init() = 0;//純粋仮想関数
	virtual void Update() = 0;//純粋仮想関数
	virtual void Draw() = 0;//純粋仮想関数

	Stage GetTag() { return tag; }

protected:
	Stage tag = Stage::Title;	//今どのステージか判断するための変数

};
