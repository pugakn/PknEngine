#pragma once
namespace pugaknSDK {
  template <typename T>
  class Module
  {
  public:
    static T Instance() {
      return *__Var();
    };
    static T* InstancePtr() {
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

