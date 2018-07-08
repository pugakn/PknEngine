#pragma once
#include "pkn_prerequiites.h"
#include <chrono>

namespace pugaknSDK {
  /**
  * A basic timer
  */
  class Timer {
  public:
    void Init();
    float Restart();

    float	GetDTSeconds() const;
    float GetDTMiliseconds() const;
    float GetDTMicroseconds() const;

  private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    using Duration = std::chrono::nanoseconds;
    using Seconds = std::chrono::duration<float>;
    using Milliseconds = std::chrono::duration<float, std::milli>;
    using Microseconds = std::chrono::duration<float, std::micro>;

    TimePoint m_start;
  };
  /**
  * Static class for app time management
  */
  class Time {
  public:
    static void Init();
    static void Update();

    static float GetDTSeconds();
    static float GetDTMiliseconds();
    static float GetDTMicroseconds();

    static float GetAppTimeSeconds();
    static float GetAppTimeMiliseconds();
    static float GetAppTimeMicroseconds();
  private:
    static Timer m_deltaTimer;
    static Timer m_AppTimeTimer;
    static float m_deltaSecs;
  };
}
