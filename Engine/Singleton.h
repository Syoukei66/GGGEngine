#pragma once
// =================================================================
// https://qiita.com/kikuuuty/items/fcf5f7df2f0493c437dc
// mozcŽ®ƒVƒ“ƒOƒ‹ƒgƒ“
// =================================================================

#include <mutex>
#include <assert.h>

class SingletonFinalizer
{
public:
  typedef void(*FinalizerFunc)();

  static void addFinalizer(FinalizerFunc func);
  static void finalize();
};

template <typename T>
class singleton final
{
public:
  static T& get_instance()
  {
    std::call_once(initFlag, create);
    assert(instance);
    return *instance;
  }

private:
  static void create() {
    instance = new T;
    SingletonFinalizer::addFinalizer(&singleton<T>::destroy);
  }

  static void destroy() {
    delete instance;
    instance = nullptr;
  }

  static std::once_flag initFlag;
  static T* instance;
};

template <typename T> std::once_flag singleton<T>::initFlag;
template <typename T> T* singleton<T>::instance = nullptr;