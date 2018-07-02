#pragma once
#include <iostream>;
namespace pugaknSDK {
  //Use this as a Singleton class template 
  //Usage: MyClass : Public Module<MyClass>
  template <typename T>
  class Module
  {
  public:
    static T& Instance() {
      PKN_ASSERT(__Var());
      return *__Var();
    };
    static T* InstancePtr() {
      PKN_ASSERT(__Var());
      return __Var();
    };
    static void StartUp() {
      if (!__Var()) {
        __Var() = new T();
        PKN_DEBUG_ONLY(std::cout << typeid(__Var()).name() << " StartUp" << std::endl);
      }
    }
  protected:
    static T*& __Var() {
      static T* inst = nullptr;
      return inst;
    }
  };
}

