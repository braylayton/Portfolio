#ifndef INCLUDED_CORE_APPLICATION_H
#define INCLUDED_CORE_APPLICATION_H

namespace SWGE {
namespace Core {

class Application
{
public:
	Application();
	virtual ~Application();

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	void Initialize(HINSTANCE instance, LPCSTR appName);
	void Terminate();

	void Update();

	void Kill() { mRunning = false; }

	HINSTANCE GetInstance() const {return mInstance;}
	const char* GetAppName() const { return mAppName.c_str(); }
	bool IsRunning() const { return mRunning; }


private:
	virtual void OnInitialize() = 0;
	virtual void OnTerminate() = 0;
	virtual void OnUpdate() = 0;

	HINSTANCE mInstance;
	//HWND mWindow;
	std::string mAppName;
	bool mRunning;
};

}// namespace core
}// namespace SWGE



#endif //INCLUDED_CORE_APPLICATION_H
