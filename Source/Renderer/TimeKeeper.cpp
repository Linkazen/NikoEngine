#include "TimeKeeper.h"

void TimeKeeper::Begin() {
  mStartTime = std::chrono::steady_clock::now();
  mOldTime = mStartTime;
  mCurrTime = mStartTime;

  mDeltaTime = 0;
}

void TimeKeeper::Tick() {
  mOldTime = mCurrTime;
  mCurrTime = std::chrono::steady_clock::now();

  mDeltaTime = std::chrono::duration<float, std::chrono::seconds::period>(
                   mCurrTime - mOldTime)
                   .count();
}

float TimeKeeper::DeltaTime() { return mDeltaTime; }
