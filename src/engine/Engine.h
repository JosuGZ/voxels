#ifndef ENGINdE_H
#define ENGINdE_H

#include <iostream>
#include <string>
#include <mingw.thread.h>

class Engine {
public:
  static Engine& instance();
  void postEvent(const std::string &event);

private:
  Engine();
  static void events_loop(void);

  std::thread *events_thread;
};

#endif // ENGINdE_H
