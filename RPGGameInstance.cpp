#include "RPGGameInstance.h"
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

//Don't use namespace std to avoid ambiguity

std::shared_ptr<RPGGameInstance> RPGGameInstance::Instance = NULL;

void RPGGameInstance::Initialize()
{
	Instance = std::make_shared<RPGGameInstance>();

}

std::shared_ptr<RPGGameInstance> RPGGameInstance::Get()
{
	if (!Instance) {
		Initialize();
	}
	return Instance;
}

void RPGGameInstance::ShutDown()
{
	Instance.reset();
}

void RPGGameInstance::GameStart() //init map, prompt move or shop choices for player
{
	try {
		srand(time(NULL));
		LoadMap();
		while (1)
		{
			Refresh();
			std::cout << "*\t1.Move\t2.Shop\t\t\t\t" << std::endl;
			std::cout << "*Enter:";
			int Choice;
			std::cin >> Choice;
			if (Choice == 1) {
				Move();
			}
			else {
				Shop();
			}
			std::cout << std::endl;
			std::cout << "Round Over\n";
			system("pause");
		}
	}
	catch (std::string error) {
		std::cout << std::endl << error << std::endl;
	}
	system("pause");
}

void RPGGameInstance::LoadMap()
{
	std::string StrMap = "";
	std::ifstream Mapfile;
	Mapfile.open("Map.m");
	Mapfile >> StrMap;
	StrMap += "AAAAAAAAAAAAAAAAAAAAAAAAAAAAA";//make sure player step on slimeKing
	Mapfile.close();
	for (auto a : StrMap) {
		switch (a)
		{
		case '0':
			Map.push_back(MakePathPoint(EPathPointType::HealthBottle));
			break;
		case '1':
			Map.push_back(MakePathPoint(EPathPointType::StrengthGem));
			break;
		case '2':
			Map.push_back(MakePathPoint(EPathPointType::DefenceGem));
			break;
		case '3':
			Map.push_back(MakePathPoint(EPathPointType::ExperienceBottle));
			break;
		case '4':
			Map.push_back(MakePathPoint(EPathPointType::Slime));
			break;
		case '5':
			Map.push_back(MakePathPoint(EPathPointType::BigSlime));
			break;
		case '6':
			Map.push_back(MakePathPoint(EPathPointType::GiantSlime));
			break;
		case '7':
			Map.push_back(MakePathPoint(EPathPointType::SlimeImp));
			break;
		case '8':
			Map.push_back(MakePathPoint(EPathPointType::SlimeDevil));
			break;
		case '9':
			Map.push_back(MakePathPoint(EPathPointType::EliteSlime));
			break;
		case 'A':
			Map.push_back(MakePathPoint(EPathPointType::SlimeKing));
			break;

		default:
			break;
		}
	}
}

void RPGGameInstance::Refresh()
{
	system("cls");
	std::cout << "*****************************************************************" << std::endl;
	std::cout << "*                                                               *" << std::endl;
	std::cout << "*\t\tHero has moved " << Player.Position + 1 << " steps\t\t\t\t*" << std::endl;
	std::cout << "*Attack:\t" << Player.Attack << "\t\tDefence: \t" << Player.Defence << "\t\t*" << std::endl;
	std::cout << "*Health:\t" << Player.Health << "\t\tExpirence: \t" << Player.FreeExperience << "\t\t*" << std::endl;
	std::cout << "\t\t\t\t\t\t\t" << std::endl;
	std::cout << "*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->-*" << std::endl;
	std::cout << "*===============================================================*" << std::endl;
	std::cout << "* @";
	for (int i = 0; i < 6; i++) {
		Map.at(Player.Position+i+1)->Draw();
	}
	std::cout << "\t\t*" << std::endl;

}

void RPGGameInstance::Move()
{
	int moveNum = rand() % 6 + 1;
	for (int i = 0; i < moveNum; i++) {
		Player.Position++;
		Refresh();
		system("timeout 1 >nul");
	}
	Map.at(Player.Position)->StepOn(Player);
}

void RPGGameInstance::Shop()
{
	std::cout << "*****************************************************************\n";
	std::cout << "*                                                               *" << std::endl;
	std::cout << "*\t You have " << Player.FreeExperience << "\t EXP\t\t*" << std::endl;
	std::cout << "\t\t\t\t\t\t\t\n";
	std::cout << "*1.Attack+1 per 2 EXP\t\t\t\t\t\n";
	std::cout << "*2.Defence+1 per 2 EXP\t\t\t\t\t\n";
	std::cout << "*3.Health+20 per 2 EXP\t\t\t\t\t\n";
	std::cout << "*Enter the index: ";
	int index;
	std::cin >> index;
	std::cout << "*Enter the amount: ";
	int NumOfIncrease;
	std::cin >> NumOfIncrease;
	if (NumOfIncrease * 2 > Player.FreeExperience) {
		std::cout << "You don't have enought EXP\n";
		return;
	}
	switch (index)
	{
	case 1:
		Player.FreeExperience -= 2 * NumOfIncrease;
		Player.Attack += NumOfIncrease;
		break;
	case 2:
		Player.FreeExperience -= 2 * NumOfIncrease;
		Player.Attack += NumOfIncrease;
		break;
	case 3:
		Player.FreeExperience -= 2 * NumOfIncrease;
		Player.Attack += NumOfIncrease * 20;
		break;
	default:
		std::cout << "Wrong Input";
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		break;
	}
}

std::shared_ptr<PathPoint> RPGGameInstance::MakePathPoint(EPathPointType type)
{
	switch (type)
	{
	case EPathPointType::HealthBottle:
	case EPathPointType::StrengthGem:
	case EPathPointType::DefenceGem:
	case EPathPointType::ExperienceBottle:
		return std::make_shared<TreasurePoint>(type);
		break;
	case EPathPointType::Slime:
	case EPathPointType::BigSlime:
	case EPathPointType::GiantSlime:
	case EPathPointType::SlimeImp:
	case EPathPointType::SlimeDevil:
	case EPathPointType::EliteSlime:
	case EPathPointType::SlimeKing:
		return std::make_shared<MonsterPoint>(type);
		break;
	default:
		return NULL;
		break;
	}
}
