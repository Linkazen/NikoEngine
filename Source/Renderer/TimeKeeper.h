#pragma once
#include <chrono>

class TimeKeeper {
public:
  TimeKeeper() = default;

  void Begin();

  void Tick();

  float DeltaTime();

private:
  std::chrono::steady_clock::time_point mStartTime;
  std::chrono::steady_clock::time_point mOldTime;
  std::chrono::steady_clock::time_point mCurrTime;

  float mDeltaTime = 0.f;
};
