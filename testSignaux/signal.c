#include "signal.h"

static void signalHandler(int signum){
  printf("%s\n", "hello");
}
