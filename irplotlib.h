/*************************************************
 IRLaboratory Plot Library
 Author: Kazumichi INOUE <k.inoue@oyama-ct.ac.jp>
 Create: 2022-04-30_Sat
 *************************************************/

#include <opencv2/opencv.hpp>
#include <vector>

struct Dataset {
  int type;
  std::vector<double> x;
  std::vector<double> y;
  Dataset() {
    type = 0;   // デフォルトは線で描画 1で散布図
  };
};

class IRPlotLib {
  private:
    std::vector<Dataset> data;

    cv::Mat img_base;
    cv::Mat img;
    cv::Size WIN_SIZE;
    cv::Size GRAPH_SIZE;

    cv::Scalar BACK_COLOR;
    double max_x, min_x, max_y, min_y;
    double cx_size, cy_size;

    int ORIGIN_X_px;  // ピクセル単位の原点座標
    int ORIGIN_Y_px;  // ピクセル単位の原点座標

    void grid();  // グリッド

    bool flag_xlim;  // set_xlimでセットされた場合にtrue
    bool flag_ylim;  // set_ylimでセットされた場合にtrue

    double mergin_graph_x = 0.05;
    double mergin_graph_y = 0.05;

    std::vector<double> ticks_x;
    std::vector<double> ticks_y;

    void plot_run();
    std::vector<cv::Scalar> color;
    int color_index = 0;

    void draw_title();
    std::string graph_title;

  public:
    IRPlotLib() { std::cerr << "Hello, irplotlib\n"; };
    IRPlotLib(int width, int height);

    void set_xlim(double xmin, double xmax);
    void set_ylim(double ymin, double ymax);

    void plot(std::vector<double> &t, std::vector<double> &x);
    void scatter(std::vector<double> &x, std::vector<double> &y);
    void title(std::string str);
    void show();
    void save();
};
