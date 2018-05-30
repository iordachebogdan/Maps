#include "application.h"

int main() {
#ifdef TESTING
  freopen("unit_tests/test1.txt", "r", stdin);
#endif

  maps::Application app;
  app.run();

  return 0;
}