#include "irplotlib.h"

std::vector<double> make_tick(double min, double max);

IRPlotLib::IRPlotLib(int width, int height) {
  WIN_SIZE = cv::Size(width, height);
  GRAPH_SIZE.width = 0.8 * width;
  GRAPH_SIZE.height = 0.8 * height;

  BACK_COLOR = cv::Scalar(255, 255, 255);
  img_base = cv::Mat(WIN_SIZE, CV_8UC3, BACK_COLOR);
  cv::rectangle(img_base,
      cv::Point((WIN_SIZE.width - GRAPH_SIZE.width)/2, (WIN_SIZE.height - GRAPH_SIZE.height)/2),
      cv::Point((WIN_SIZE.width - GRAPH_SIZE.width)/2 + GRAPH_SIZE.width,
        (WIN_SIZE.height - GRAPH_SIZE.height)/2 + GRAPH_SIZE.height),
      cv::Scalar(0, 0, 0), 1, cv::LINE_8);
  cv::rectangle(img_base,
      cv::Point((WIN_SIZE.width - GRAPH_SIZE.width)/2 - 1, (WIN_SIZE.height - GRAPH_SIZE.height)/2 -1),
      cv::Point((WIN_SIZE.width - GRAPH_SIZE.width)/2 + GRAPH_SIZE.width + 1,
        (WIN_SIZE.height - GRAPH_SIZE.height)/2 + GRAPH_SIZE.height + 1),
      cv::Scalar(242, 242, 242), 1, cv::LINE_4);
  cv::rectangle(img_base,
      cv::Point((WIN_SIZE.width - GRAPH_SIZE.width)/2 + 1, (WIN_SIZE.height - GRAPH_SIZE.height)/2 +1),
      cv::Point((WIN_SIZE.width - GRAPH_SIZE.width)/2 + GRAPH_SIZE.width - 1,
        (WIN_SIZE.height - GRAPH_SIZE.height)/2 + GRAPH_SIZE.height - 1),
      cv::Scalar(242, 242, 242), 1, cv::LINE_4);


  img_base.copyTo(img);

  ORIGIN_X_px = (WIN_SIZE.width - GRAPH_SIZE.width)/2;
  ORIGIN_Y_px = (WIN_SIZE.height - GRAPH_SIZE.height)/2 + GRAPH_SIZE.height;
  //drawAxis();

  flag_xlim = false;
  flag_ylim = false;
    /*
       インデックス	色	名称	カラーコード
       */
  color.emplace_back(cv::Scalar(180, 119, 31));  // 0	青	tab:blue	#1f77b4
  color.emplace_back(cv::Scalar(14, 127, 255));  // 1	オレンジ	tab:orange	#ff7f0e
  color.emplace_back(cv::Scalar(44, 160, 44));   // 2	緑	tab:green	#2ca02c
  color.emplace_back(cv::Scalar(40, 39, 214));   // 3	赤	tab:red	#d62728
  color.emplace_back(cv::Scalar(189, 103, 148)); // 4	紫	tab:purple	#9467bd
  color.emplace_back(cv::Scalar(75, 86, 140));   // 5	茶	tab:brown	#8c564b
  color.emplace_back(cv::Scalar(194, 119, 227)); // 6	ピンク	tab:pink	#e377c2
  color.emplace_back(cv::Scalar(127, 127, 127)); // 7	灰	tab:gray	#7f7f7f
  color.emplace_back(cv::Scalar(34, 189, 188));  // 8	オリーブ	tab:olive	#bcbd22
  color.emplace_back(cv::Scalar(207, 190, 23));  // 9	水色	tab:cyan	#17becf
}

void IRPlotLib::set_xlim(double xmin, double xmax) {
  flag_xlim = true;
  max_x = xmax;
  min_x = xmin;
  cx_size = (max_x - min_x)/GRAPH_SIZE.width;
  ticks_x = make_tick(min_x, max_x);
}

void IRPlotLib::set_ylim(double ymin, double ymax) {
  flag_ylim = true;
  max_y = ymax;
  min_y = ymin;
  cy_size = (max_y - min_y)/GRAPH_SIZE.height;
  ticks_y = make_tick(min_y, max_y);
}

void IRPlotLib::xlabel(std::string label) {
  x_label = label;
}
void IRPlotLib::ylabel(std::string label) {
  y_label = label;
}

void IRPlotLib::plot(std::vector<double> &t,
                     std::vector<double> &x) {
  Dataset dat;
  dat.type = 0;
  dat.x = t;
  dat.y = x;
  data.emplace_back(dat);
};

void IRPlotLib::plot(cv::Point2d x1, cv::Point2d x2) {
  Dataset dat;
  dat.type = 0;
  std::vector<double> x{x1.x, x2.x};
  std::vector<double> y{x1.y, x2.y};
  dat.x = x;
  dat.y = y;
  data.emplace_back(dat);
};

void IRPlotLib::scatter(std::vector<double> &x,
                     std::vector<double> &y) {
  Dataset dat;
  dat.type = 1;
  dat.x = x;
  dat.y = y;
  data.emplace_back(dat);
};

void IRPlotLib::show() {
  // キャンバスを初期化
  img_base.copyTo(img);
  grid();
  plot_run();
  draw_title();
  draw_label();
  cv::imshow("TEST", img);
  cv::waitKey(0);
}

void IRPlotLib::plot_run() {
  for (auto d: data) {
    if (d.type == 0) {
      for (size_t i = 1; i < d.x.size(); i++) {
        int ix0 = (d.x[i-1] - min_x)/cx_size;
        int iy0 = (d.y[i-1] - min_y)/cy_size;
        int ix1 = (d.x[i  ] - min_x)/cx_size;
        int iy1 = (d.y[i  ] - min_y)/cy_size;
        if (0 <= ix1 && ix1 <= GRAPH_SIZE.width && 0 <= iy1 && iy1 <= GRAPH_SIZE.height) {
          cv::line(img,
              cv::Point(ix0 + ORIGIN_X_px,-iy0 + ORIGIN_Y_px),
              cv::Point(ix1 + ORIGIN_X_px,-iy1 + ORIGIN_Y_px),
              color[color_index % color.size()], 1, cv::LINE_AA);
#if 0
          cv::circle(img,
              cv::Point(ix1 + ORIGIN_X_px,-iy1 + ORIGIN_Y_px),
              2, cv::Scalar(0, 0, 200), 1);
#endif
        }
      }
    } else if (d.type == 1) {
      for (size_t i = 0; i < d.x.size(); i++) {
        int ix = (d.x[i  ] - min_x)/cx_size;
        int iy = (d.y[i  ] - min_y)/cy_size;
        if (0 <= ix && ix <= GRAPH_SIZE.width && 0 <= iy && iy <= GRAPH_SIZE.height) {
          cv::circle(img,
              cv::Point(ix + ORIGIN_X_px, -iy + ORIGIN_Y_px),
              2, color[color_index % color.size()], -1, cv::LINE_AA);
        }
      }
    }
    color_index++;
  }
}

void IRPlotLib::draw_title() {
  cv::Size textSize = cv::getTextSize(graph_title, cv::FONT_HERSHEY_PLAIN, 1.0, 1, 0);
  cv::putText(img,
      graph_title,
      cv::Point(WIN_SIZE.width/2 - textSize.width/2, // グラフの中央寄せ
        ORIGIN_Y_px - 1.05 * GRAPH_SIZE.height),
      cv::FONT_HERSHEY_PLAIN,
      1, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
}

void IRPlotLib::draw_label() {
  // xlabel
  cv::Size textSize_x = cv::getTextSize(x_label, cv::FONT_HERSHEY_PLAIN, 1.0, 1, 0);
  cv::putText(img,
      x_label,
      cv::Point(WIN_SIZE.width/2 - textSize_x.width/2, // グラフの中央寄せ
        ORIGIN_Y_px + (WIN_SIZE.height - GRAPH_SIZE.height)/3),
      cv::FONT_HERSHEY_PLAIN,
      1, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
  // ylabel
  cv::Size textSize_y = cv::getTextSize(y_label, cv::FONT_HERSHEY_PLAIN, 1.0, 1, 0);
  cv::Mat y_label_img = cv::Mat(cv::Size(textSize_y.width, textSize_y.height + 1), CV_8UC3, BACK_COLOR);
  cv::putText(y_label_img,
      y_label,
      cv::Point(0, textSize_y.height + 1),
      cv::FONT_HERSHEY_PLAIN,
      1, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
  cv::Point2d ctr(y_label_img.cols/2, y_label_img.rows/2);
  cv::Mat mat = cv::getRotationMatrix2D(ctr, 90, 1.0);
  mat.at<double>(0, 2) += -y_label_img.rows;
  mat.at<double>(1, 2) += WIN_SIZE.height/2;
  cv::warpAffine(y_label_img,
      img, mat, img.size(),
      cv::INTER_LINEAR, cv::BORDER_TRANSPARENT);
}

void IRPlotLib::title(std::string str) {
  graph_title = str;
}

void IRPlotLib::grid() {
  double min, max;
  if (!flag_xlim) {
    // 値の範囲をチェック
    min = 99999;
    max = -min;
    for (auto d: data) {
      for (auto val: d.x) {
        if (min > val) {
          min = val;
        } else if (max < val) {
          max = val;
        }
      }
    }
    double range = max - min;
    min_x = min - mergin_graph_x * range;
    max_x = max + mergin_graph_x * range;
    std::cout << "max_x: " << max_x << "  min_x:" << min_x << " range:" << range << "\n";
    cx_size = (max_x - min_x)/GRAPH_SIZE.width;

    ticks_x = make_tick(min_x, max_x);
  }

  if (!flag_ylim) {
    min = 99999;
    max = -min;
    for (auto d: data) {
      for (auto val: d.y) {
        if (min > val) {
          min = val;
        } else if (max < val) {
          max = val;
        }
      }
    }
    double range = max - min;
    min_y = min - mergin_graph_y * range;
    max_y = max + mergin_graph_y * range;
    std::cout << "max_y: " << max_y << "  min_y:" << min_y << " range:" << range << "\n";
    cy_size = (max_y - min_y)/GRAPH_SIZE.height;

    ticks_y = make_tick(min_y, max_y);
  }

  // X軸に並行なグリッド
  for (auto y: ticks_y) {
    cv::line(img,
        cv::Point(ORIGIN_X_px + 1,                    -(y - min_y)/cy_size + ORIGIN_Y_px),
        cv::Point(ORIGIN_X_px + GRAPH_SIZE.width - 1, -(y - min_y)/cy_size + ORIGIN_Y_px),
        cv::Scalar(189, 189, 189), 1, cv::LINE_8
        );
    cv::line(img,
        cv::Point(ORIGIN_X_px    ,                    -(y - min_y)/cy_size + ORIGIN_Y_px),
        cv::Point(ORIGIN_X_px - 4,                    -(y - min_y)/cy_size + ORIGIN_Y_px),
        cv::Scalar(0, 0, 0), 1, cv::LINE_8);

    std::stringstream numStr;
    numStr << double(int(y * 100))/100;
    cv::Size textSize = cv::getTextSize(numStr.str(), cv::FONT_HERSHEY_PLAIN, 1.0, 1, 0);
    cv::putText(img,
        numStr.str(),
        cv::Point(ORIGIN_X_px - textSize.width - 10,                    -(y - min_y)/cy_size + ORIGIN_Y_px),
        cv::FONT_HERSHEY_PLAIN,
        1, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
  }
  // Y軸に並行なグリッド
  for (auto x: ticks_x) {
    cv::line(img,
        cv::Point((x - min_x)/cx_size + ORIGIN_X_px, ORIGIN_Y_px - 1),
        cv::Point((x - min_x)/cx_size + ORIGIN_X_px, ORIGIN_Y_px - GRAPH_SIZE.height + 1),
        cv::Scalar(189, 189, 189), 1, cv::LINE_8);
    cv::line(img,
        cv::Point((x - min_x)/cx_size + ORIGIN_X_px, ORIGIN_Y_px),
        cv::Point((x - min_x)/cx_size + ORIGIN_X_px, ORIGIN_Y_px + 4),
        cv::Scalar(0, 0, 0), 1, cv::LINE_8);
    std::stringstream numStr;
    numStr << double(int(x * 100))/100;
    cv::Size textSize = cv::getTextSize(numStr.str(), cv::FONT_HERSHEY_PLAIN, 1.0, 1, 0);
    cv::putText(img,
        numStr.str(),
        cv::Point((x - min_x)/cx_size + ORIGIN_X_px - textSize.width/2, ORIGIN_Y_px + 24),
        cv::FONT_HERSHEY_PLAIN,
        1, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
  }
}

void IRPlotLib::save() {
  cv::imwrite("irplot.png", img);
}

std::vector<double> make_tick(double min, double max) {
  double tick_max, tick_min;
  std::vector<double> tick;
  if (max >= 0) {
    tick_max = floor(max);
  } else {
    tick_max = ceil(max);
  }

  if (min >= 0) {
    tick_min = floor(min);
  } else {
    tick_min = ceil(min);
  }
  for (double i = tick_min; i <= tick_max; i += (tick_max - tick_min)/8.0) {
    tick.emplace_back(i);
  }
  for (auto i: tick) {
    std::cout << i << " ";
  }
  std::cout << "\n";
  return tick;
}
