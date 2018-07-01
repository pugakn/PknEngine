#pragma once
namespace pugaknSDK {
  template <typename T>
  class Module
  {
  public:
    static T Instance() {
      PKN_ASSERT(__Var())
      return *__Var();
    };
    static T* InstancePtr() {
      PKN_ASSERT(__Var())
      return __Var();
    };
    static void StartUp() {
      if (!__Var()) {
        __Var() = new T();
      }
    }
  protected:
    static T*& __Var() {
      static T* inst = nullptr;
      return inst;
    }
  };
}

