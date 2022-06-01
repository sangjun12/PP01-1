#include "MGameLoop.hpp"

int main()
{
	MuSeoun_Engine::MGameLoop gLoop;
	gLoop.Run();

	_CrtDumpMemoryLeaks;
	return 0;
}