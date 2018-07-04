#include "pkn_time.h"

namespace pugaknSDK {
  void Timer::Init() {
    m_start = Clock::now();
  }

  float Timer::Restart() {
    float ret = std::chrono::duration_cast<Seconds>(Duration(Clock::now() - m_start)).count();
    Init();
    return ret;
  }

  float Timer::GetDTSeconds() const
  {
    return std::chrono::duration_cast<Seconds>(Duration(Clock::now() - m_start)).count();
  }

  float Timer::GetDTMiliseconds() const
  {
    return std::chrono::duration_cast<Milliseconds>(Duration(Clock::now() - m_start)).count();
  }

  float Timer::GetDTMicroseconds() const
  {
    return std::chrono::duration_cast<Microseconds>(Duration(Clock::now() - m_start)).count();
  }


  /////////////////////////////////////////////////////////////////////////////////
  //////////////////////             GLOBAL  TIMER                                  
  /////////////////////////////////////////////////////////////////////////////////
  Timer Time::m_AppTimeTimer;
  Timer Time::m_deltaTimer;
  float Time::m_deltaSecs;

  void Time::Init()
  {
    m_AppTimeTimer.Init();
    m_deltaTimer.Init();
  }

  void Time::Update()
  {
    m_deltaSecs = m_deltaTimer.Restart();
  }

  float Time::GetDTSeconds()
  {
    return m_deltaSecs;
  }

  float Time::GetDTMiliseconds()
  {
    return m_deltaSecs * 1000.0f;
  }

  float Time::GetDTMicroseconds()
  {
    return m_deltaSecs * 1000000.0f;
  }

  float Time::GetAppTimeSeconds()
  {
    return m_AppTimeTimer.GetDTSeconds();
  }

  float Time::GetAppTimeMiliseconds()
  {
    return m_AppTimeTimer.GetDTMiliseconds();
  }

  float Time::GetAppTimeMicroseconds()
  {
    return m_AppTimeTimer.GetDTMicroseconds();
  }
}

