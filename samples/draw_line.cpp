/*
 * irplotlib samples
 * draw line
 * Kazumichi INOUE <k.inoue@oyama-ct.ac.jp>
 * 2022-05-01
 */

#include "irplotlib.h"

#include <iostream>

int main(int argc, char *argv[]) {
  IRPlotLib plt(800, 600);  // width x height

  plt.plot(cv::Point2d(-2.0, -2.0), cv::Point2d(2.0, 2.0));
  plt.plot(cv::Point2d(1.0, 0.5), cv::Point2d(-1.0, -0.5));
  plt.title("Graph of the lines");
  plt.show();
  plt.save();
  return 0;
}
