#include "Engine.h"

//#include "world/World.h"

Engine& Engine::instance() {
  static Engine engine;
  return engine;
}

void Engine::postEvent(const std::string &event) {
  std::cout << event;
}

Engine::Engine() { // TODO: Stop?
  events_thread = new std::thread { Engine::events_loop };
}

void Engine::events_loop(void) {
  while (true) {
    static int counter = 0;
    std::cout << counter++ << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}
