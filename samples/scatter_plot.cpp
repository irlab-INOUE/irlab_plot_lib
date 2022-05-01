/*
 * irplotlib samples
 * scatter plot
 * Kazumichi INOUE <k.inoue@oyama-ct.ac.jp>
 * 2022-05-01
 */

#include "irplotlib.h"

#include <iostream>

int main(int argc, char *argv[]) {
  IRPlotLib plt(800, 600);  // width x height

  std::vector<double> x;
  std::vector<double> y;

  // 乱数生成
  cv::RNG rng(cv::getTickCount());

  for (int i = 0; i < 10000; i++) {
    double xx = rng.gaussian(1.0);
    double yy = rng.gaussian(1.0);
    x.emplace_back(xx);
    y.emplace_back(yy);
  }

  plt.scatter(x, y);
  plt.title("Graph of the random value");
  plt.show();
  plt.save();
  return 0;
}
