#pragma once
#include <chrono>


class TimeKeeper
{
public:
	TimeKeeper() {};
	void Begin() {
		mStartTime = std::chrono::steady_clock::now();
		mOldTime = mStartTime;
		mCurrTime = mStartTime;

		mDeltaTime = 0;
	}
	void Tick() {
		mOldTime = mCurrTime;
		mCurrTime = std::chrono::steady_clock::now();
		

		mDeltaTime = std::chrono::duration<float, std::chrono::seconds::period>(mCurrTime - mOldTime).count();
	}

	float DeltaTime() {
		return mDeltaTime;
	}
private:
	std::chrono::steady_clock::time_point mStartTime;
	std::chrono::steady_clock::time_point mOldTime;
	std::chrono::steady_clock::time_point mCurrTime;

	float mDeltaTime = 0.f;
};
