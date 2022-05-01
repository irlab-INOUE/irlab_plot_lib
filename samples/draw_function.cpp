/*
 * irplotlib samples
 * draw function
 * Kazumichi INOUE <k.inoue@oyama-ct.ac.jp>
 * 2022-05-01
 */

#include "irplotlib.h"

#include <iostream>

double function(double t) {
  return t*t - t - 1;
}

int main(int argc, char *argv[]) {
  IRPlotLib plt(800, 600);  // width x height

  std::vector<double> t;
  std::vector<double> x;

  double dt = 0.01;
  for (int i = 0; i < 5/dt; i++) {
    double tt = i * dt;
    t.emplace_back(tt);
  }

  for (int i = 0; i < t.size(); i++) {
    x.emplace_back(function(t[i]));
  }
  plt.plot(t, x);
  plt.title("Graph of the function");
  plt.show();
  plt.save();
  return 0;
}
