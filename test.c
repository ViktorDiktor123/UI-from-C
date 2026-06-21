#include "UI.h"

int main() {
  rect(0, 0, 15, 15, false);
  rect(14, 0, 15, 15, true);
  rect(0, 14, 15, 15, true);
  rect(14, 14, 15, 15, false);
  draw();
  return 0;
}
