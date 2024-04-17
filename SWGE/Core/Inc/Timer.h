#ifndef INCLUDED_CORE_TIMER_H
#define INCLUDED_CORE_TIMER_H

namespace SWGE {
namespace Core {

class Timer
{
public:
	Timer();

	void Initialize();
	void Update();
	void Reset();

	float GetElapsedTime() const;
	float GetTotalTime() const;
	float GetFPS() const; //Frames per second

private:
	std::chrono::high_resolution_clock::time_point mLastTime;
	std::chrono::high_resolution_clock::time_point mCurrentTime;

	float mElapsedTime;
	float mTotalTime;
	
	float mLastUpdateTime;
	float mFrameSinceLastSecond;
	float mFramesPerSecond;
};
} // namespace SWGE
} // namespace Core

#endif // #ifndef INCLUDED_CORE_TIMER_H