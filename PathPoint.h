#pragma once
#include <unordered_map>
enum class EPathPointType : int {
	HealthBottle = 0,
	StrengthGem,
	DefenceGem,
	ExperienceBottle,
	Slime,
	BigSlime,
	GiantSlime,
	SlimeImp,
	SlimeDevil,
	EliteSlime,
	SlimeKing
};

struct SlimeProperty
{
	int Health;
	int Attack;
	int Defence;
	int Experience;
	SlimeProperty(){}
	SlimeProperty(int _Health, int _Attack, int _Defence, int _Experience);
};

struct PlayerState {
	int Health;
	int Attack;
	int Defence;
	int FreeExperience;
	int Position;
	PlayerState();
};

class PathPoint {
public:
	void Draw();
	virtual void StepOn(PlayerState&Player) = 0;
	PathPoint(EPathPointType _Type);
protected:
	EPathPointType Type;
};

class MonsterPoint :public PathPoint {
public:
	MonsterPoint(EPathPointType _Type);
	virtual void StepOn(PlayerState&Player) override;
private:
	static std::unordered_map<int, SlimeProperty>SlimeProperties;
};

class TreasurePoint :public PathPoint {
public:
	TreasurePoint(EPathPointType _Type);
	virtual void StepOn(PlayerState& Player) override;

}; 