#include "window.h"
#include <stdio.h>
#define WIDTH 1280
#define HEIGHT 720

void loop_function_test(void)
{
    printf("This is a loop function test.\n");
}

int main(void)
{
  window_init(WIDTH,HEIGHT,loop_function_test);
  return 0;
}


