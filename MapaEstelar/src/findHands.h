#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/features2d.hpp>
#include<chrono>
#include <set>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <thread>
#include <mutex>

using namespace std;
using namespace cv;

class handsDetection{
	public:
		handsDetection();
		~handsDetection();
		void startThread(void);
		int init(void);
		void segSkin(void);
		void GestureRecognition(void);
	private:
		int hands_number;
		int gesture_detected;
		int gesture_flag;
		double zoom_ratio;
		double zoom_angle;
		double dx;
		double dy;
		Point2d end_point;
		Point2f pointing_place;
		std::thread hands_thread;
		Mat ycrcv, y_plane, cr_plane, cb_plane, piel_morph, fg, dst, img, bg;
		vector<vector<Point>> hull_prev;
		set<int> convex_flag_prev, convex_flag_cur;
		vector<Mat> ycrcb_planes;
		VideoCapture vid;
		queue<vector<Point2f>> point_centroids;
		queue<vector<Point2f>> open_centroids;
		vector<Point2f> mov_direction;
};

void morph_op(Mat M, int morph_size, int type);
void conv_img(Mat img, Mat out);
Mat bs(Mat bg, Mat img, int threshold);