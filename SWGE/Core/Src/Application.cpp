#include "Precompiled.h"
#include "Application.h"

using namespace SWGE;
using namespace SWGE::Core;

Application::Application()
	: mInstance(nullptr)
	, mRunning(true)
{
}

Application::~Application()
{
}

void Application::Initialize(HINSTANCE instance, LPCSTR appname)
{
	mInstance = instance;
	mAppName = appname;
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	OnInitialize();
}

void Application::Terminate()
{
	OnTerminate();
	CoUninitialize();
}

void Application::Update()
{
	OnUpdate();
}