#include "GameApp.h"
#include <Core\Inc\Core.h>

//class Car
//{
//public:
//	META_CLASS_DECLARE;
//
//	SWGE::Math::Vector3 position;
//	float fuel;
//};

//META_CLASS_BEGIN(Car)
//	META_FIELD_BEGIN
//	//META_FIELD(position, "Position")
//	META_FIELD(fuel, "Fuel")
//	META_FIELD_END
//META_CLASS_END




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int nCmdShow)
{
	//Car::StaticGetMetaClass()->Dump();
	GameApp myApp;
	myApp.Initialize(hInstance, "Hello Physics!");

	while (myApp.IsRunning())
	{
		myApp.Update();
	}

	myApp.Terminate();
	return 0;
}