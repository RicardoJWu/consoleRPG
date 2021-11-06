#include "RPGGameInstance.h"

int main() {
	while (1)
	{
		RPGGameInstance::Get()->GameStart();
		RPGGameInstance::ShutDown();
	}
}