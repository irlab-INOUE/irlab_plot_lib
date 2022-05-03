#include <iostream>
#include <vector>

#include "irplotlib.h"

int main(int argc, char *argv[]) {
  IRPlotLib plt(800, 600);  // width x height

  //plt.set_xlim( 0.6, 2.2);
  //plt.set_ylim(-1, 1);

  std::vector<double> t;
  std::vector<std::vector<double>> x;

  double dt = 0.01;
  for (int i = 0; i < 2*M_PI/dt; i++) {
    double tt = i * dt;
    t.emplace_back(tt);
  }

  for (int k = 0; k < 10; k++) {
    std::vector<double> tmp;
    for (int i = 0; i < t.size(); i++) {
      tmp.emplace_back(1.0/(k+1) * sin((k+1)*t[i]));
    }
    x.emplace_back(tmp);
  }

  for (auto xx: x) {
    plt.plot(t, xx);
  }
  plt.title("test-plot-sin");
  plt.xlabel("t[s]");
  plt.ylabel("function");
  plt.show();
  plt.save();
  return 0;
}
