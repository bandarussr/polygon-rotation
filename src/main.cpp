#include "PolygonRotation.h"
#include <cstdio>
#include <cstdlib>
#include <vector>

int main(int argc, char **argv) {
  std::vector<int> x;
  std::vector<int> y;

  if (argc != 2) {
    std::fprintf(stderr, "%s <problem num>", argv[0]);
    std::exit(1);
  }

  if (atoi(argv[1]) == 0) {
    x.push_back(0);
    x.push_back(1);
    x.push_back(1);
    x.push_back(0);
    y.push_back(1);
    y.push_back(1);
    y.push_back(0);
    y.push_back(0);
  }

  if (atoi(argv[1]) == 1) {
    x.push_back(0);
    x.push_back(1);
    x.push_back(0);
    x.push_back(-1);
    y.push_back(2);
    y.push_back(1);
    y.push_back(0);
    y.push_back(1);
  }

  if (atoi(argv[1]) == 2) {
    x.push_back(0);
    x.push_back(3);
    x.push_back(0);
    x.push_back(-2);
    x.push_back(-2);
    y.push_back(2);
    y.push_back(0);
    y.push_back(-3);
    y.push_back(-1);
    y.push_back(1);
  }

  if (atoi(argv[1]) == 3) {
    x.push_back(0);
    x.push_back(3);
    x.push_back(3);
    x.push_back(0);
    x.push_back(-1);
    x.push_back(-1);
    y.push_back(2);
    y.push_back(2);
    y.push_back(-2);
    y.push_back(-2);
    y.push_back(-1);
    y.push_back(1);
  }

  if (atoi(argv[1]) == 4) {
    x.push_back(0);
    x.push_back(4);
    x.push_back(4);
    x.push_back(0);
    y.push_back(3);
    y.push_back(3);
    y.push_back(1);
    y.push_back(1);
  }

  if (atoi(argv[1]) == 5) {
    x.push_back(0);
    x.push_back(4);
    x.push_back(0);
    y.push_back(3);
    y.push_back(3);
    y.push_back(1);
  }

  if (atoi(argv[1]) == 6) {
    x.push_back(0);
    x.push_back(4);
    x.push_back(2);
    x.push_back(0);
    y.push_back(3);
    y.push_back(3);
    y.push_back(2);
    y.push_back(2);
  }

  if (atoi(argv[1]) == 7) {
    x.push_back(0);
    x.push_back(1);
    x.push_back(4);
    x.push_back(4);
    x.push_back(2);
    x.push_back(0);
    y.push_back(5);
    y.push_back(4);
    y.push_back(3);
    y.push_back(2);
    y.push_back(1);
    y.push_back(1);
  }

  if (atoi(argv[1]) == 8) {
    x.push_back(0);
    x.push_back(1);
    x.push_back(1);
    x.push_back(1);
    x.push_back(0);
    x.push_back(-2);
    x.push_back(-1);
    y.push_back(3);
    y.push_back(3);
    y.push_back(2);
    y.push_back(1);
    y.push_back(1);
    y.push_back(1);
    y.push_back(2);
  }

  if (atoi(argv[1]) == 9) {
    x.push_back(0);
    x.push_back(3);
    x.push_back(0);
    x.push_back(-2);
    x.push_back(-2);
    y.push_back(6);
    y.push_back(4);
    y.push_back(1);
    y.push_back(3);
    y.push_back(5);
  }

  double vol = PolygonRotation::getVolume(x, y);
  std::printf("%lf\n", vol);
  
  exit(0);
}
