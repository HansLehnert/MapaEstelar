#include "findHands.h"

handsDetection::handsDetection(void) {}
handsDetection::~handsDetection(void) {}
int WINDOWS_SIZE = 20;
double defect_min_open = 0.2;
double defect_max_open = 0.3;
double defect_min_pointing = 0.0;
double defect_max_pointing = 0.13;
double convex_min_open = 0.5;
double convex_max_open = 0.75;
double convex_min_pointing = 0.7;
double convex_max_pointing = 0.88;
int convex_num_min_open = 7;
int convex_num_max_open = 14;
int convex_num_min_pointing = 9;
int convex_num_max_pointing = 16;
double convex_circle_ratio_min_open = 0.6;
double convex_circle_ratio_max_open = 0.8;
double convex_circle_ratio_min_pointing = 0.3;
double convex_circle_ratio_max_pointing = 0.47;
double contour_circle_ratio_min_open = 0.35;
double contour_circle_ratio_max_open = 0.6;
double contour_circle_ratio_min_pointing = 0.22;
double contour_circle_ratio_max_pointing = 0.37;

using namespace cv;
using namespace std;


int handsDetection::init(handsDetection* obj)
{
	obj->vid.open(0);

	if (!obj->vid.isOpened()) {
		cerr << "Error opening input." << endl;
		return 1;
	}

	obj->thread_continue = 1;

	obj->vid >> obj->img;
	obj->img.copyTo(obj->bg);
	int time_flag = 0;
	int open_size = obj->open_centroids.size();
	int pointing_size = obj->point_centroids.size();
	obj->gesture_flag = 0;
	int gesture_flag_old = 0;
	vector<Point2f> centroid_prev;
	int same_gesture_counter = 0;
	while (obj->thread_continue) {
        vector<Point2f> centroid_last;
		obj->segSkin();
		imshow("Piel", obj->piel_morph);

		open_size = obj->open_centroids.size();
		pointing_size = obj->point_centroids.size();
		Point2f pond_centroid_1 = Point2f(0, 0);
		Point2f pond_centroid_2 = Point2f(0, 0);
		Point2f pond_centroid_3 = Point2f(0, 0);
		Point2f pond_centroid_4 = Point2f(0, 0);

		if (open_size > WINDOWS_SIZE) {
			vector<Point2f> temp_vec;
			vector<Point2f> temp_vec_pointing;
			int centroids_in_frame = 0;
			int two_hands = 0;
			int one_hand = 0;
			int no_hand = 0;
			int pointing_hand = 0;
			obj->open_centroids.pop();
			obj->point_centroids.pop();

			for (int i = 0; i <= WINDOWS_SIZE; i++) {
				temp_vec = obj->open_centroids.front();
				temp_vec_pointing = obj->point_centroids.front();
				Point2f temp_point;
				if (temp_vec.size() == 2) {
					two_hands++;
					temp_point = temp_vec[0];
					if (i == 0) {
						pond_centroid_1.x += temp_point.x;
						pond_centroid_1.y += temp_point.y;
						temp_point = temp_vec[1];
						pond_centroid_2.x += temp_point.x;
						pond_centroid_2.y += temp_point.y;
					}
					else {
						temp_point = temp_vec[0];
						if (abs(temp_point.x - pond_centroid_1.x) < 50 && abs(temp_point.y - pond_centroid_1.y) < 50) {
							pond_centroid_1.x += temp_point.x;
							pond_centroid_1.y += temp_point.y;
							temp_point = temp_vec[1];
							pond_centroid_2.x += temp_point.x;
							pond_centroid_2.y += temp_point.y;
						}
						else {
							pond_centroid_2.x += temp_point.x;
							pond_centroid_2.y += temp_point.y;
							temp_point = temp_vec[1];
							pond_centroid_1.x += temp_point.x;
							pond_centroid_1.y += temp_point.y;
						}
						pond_centroid_1.x /= 2;
						pond_centroid_1.y /= 2;
						pond_centroid_2.x /= 2;
						pond_centroid_2.y /= 2;
					}
				}
				else if (temp_vec.size() == 1) {
					temp_point = temp_vec[0];
					pond_centroid_3.x += temp_point.x;
					pond_centroid_3.y += temp_point.y;
					one_hand++;
				}
				else if (temp_vec.size() == 0) {
					no_hand++;
				}

				if (temp_vec_pointing.size() == 1) {
					temp_point = temp_vec_pointing[0];
					pond_centroid_4.x += temp_point.x;
					pond_centroid_4.y += temp_point.y;
					pointing_hand++;
				}
				obj->open_centroids.pop();
				obj->point_centroids.pop();
				obj->open_centroids.push(temp_vec);
				obj->point_centroids.push(temp_vec_pointing);
			}

			pond_centroid_3.x /= one_hand;
			pond_centroid_4.x /= pointing_hand;
			pond_centroid_3.y /= one_hand;
			pond_centroid_4.y /= pointing_hand;

			if (two_hands > 2 && one_hand < two_hands) {
				cout << "Hay dos manos! D: " << endl;
				drawMarker(obj->img, pond_centroid_1, Scalar(0, 0, 255), MARKER_CROSS, 20, 3);
				drawMarker(obj->img, pond_centroid_2, Scalar(0, 0, 255), MARKER_CROSS, 20, 3);
				gesture_flag_old = 2;
			}
			else if (one_hand > 2 && one_hand > two_hands) {
				cout << "Hay una mano! D:" << endl;
				drawMarker(obj->img, pond_centroid_3, Scalar(255, 0, 0), MARKER_CROSS, 20, 3);
				gesture_flag_old = 1;
				cout << pond_centroid_3.x << " " << pond_centroid_3.y << endl;
			}

			else if (pointing_hand > 5) {
				cout << "Hay una mano apuntando! D:" << endl;
				gesture_flag_old = 3;
				drawMarker(obj->img, pond_centroid_4, Scalar(0, 255, 0), MARKER_CROSS, 20, 3);
			}
			else if (no_hand > 10 && no_hand > two_hands && no_hand > one_hand) {
				cout << "No hay mano :c" << endl;
				gesture_flag_old = 0;
			}
		}

		if (gesture_flag_old == obj->gesture_flag) {
			same_gesture_counter++;
		}
		else {
			same_gesture_counter = 0;
		}
		obj->gesture_flag = gesture_flag_old;


		if (same_gesture_counter > 1) {
			switch (obj->gesture_flag)
			{
			case 1:
				centroid_last.push_back(pond_centroid_3);
				obj->dx = pond_centroid_3.x - centroid_prev[0].x;
				obj->dy = pond_centroid_3.y - centroid_prev[0].y;
				obj->end_point = pond_centroid_3;
				cout <<"Gesto de movimiento: \n" << "dx: " << obj->dx << ", dy: "<< obj->dy << endl;
                cout << "Prev: " << centroid_prev[0].x << "," << centroid_prev[0].y<< " Now: " << pond_centroid_3.x << "," << pond_centroid_3.y<< endl;
				break;
			case 2:
                centroid_last.push_back(pond_centroid_1);
				centroid_last.push_back(pond_centroid_2);
				double dist_1, dist_2;
                dist_1 = (pond_centroid_1.x - pond_centroid_2.x)*(pond_centroid_1.x - pond_centroid_2.x)
                    + (pond_centroid_1.y - pond_centroid_2.y)*(pond_centroid_1.y - pond_centroid_2.y);
                dist_2 = (centroid_prev[0].x - centroid_prev[1].x)*(centroid_prev[0].x - centroid_prev[1].x)
                    + (centroid_prev[0].y - centroid_prev[1].y)*(centroid_prev[0].y - centroid_prev[1].y);
				obj->zoom_ratio = sqrt(dist_2) - sqrt(dist_1);
				cout << "Gesto de zoom: \n" << "Zoom ratio: " << obj->zoom_ratio << endl;

				break;
			case 3:
				centroid_last.push_back(pond_centroid_4);
				obj->pointing_place = pond_centroid_4;
				cout << "Gesto de apuntar: \n" << "Coordenada: " << "(" << obj->pointing_place.x <<","<< obj->pointing_place.y <<")" << endl;

				break;
			default:
				break;
			}
		}
		else if (same_gesture_counter == 0) {
			switch (obj->gesture_flag)
			{
			case 1:
				centroid_last.push_back(pond_centroid_3);
				break;
			case 2:
				centroid_last.push_back(pond_centroid_1);
				centroid_last.push_back(pond_centroid_2);
				break;
			case 3:
				centroid_last.push_back(pond_centroid_4);
				break;
			default:
				break;
			}
		}

		centroid_prev = centroid_last;
		imshow("Original", obj->img);
        if (cv::waitKey(10) != -1)   break;
	}
	obj->vid.release();

	return 0;
}

/* Detección de manos y centros de objetos */
void handsDetection::segSkin(void)
{
	vector<Point2f> open_hands;
	vector<Point2f> pointing_hands;

	vid >> img;

	//Background Subsraction
	fg = bs(bg, img, 30);

	/****************
	* Thresholding
	****************/

	cvtColor(img, ycrcv, COLOR_BGR2YCrCb);
	// Separar en 3 canales
	split(ycrcv, ycrcb_planes);

	inRange(ycrcb_planes[0], 0, 255, y_plane); // 80 < Y < 255
	inRange(ycrcb_planes[1], 136, 180, cr_plane);
	inRange(ycrcb_planes[2], 85, 135, cb_plane);

	// Inicializar nueva imagen con ceros
	Mat piel = Mat::zeros(y_plane.rows, y_plane.cols, CV_8UC1);

	/* Escribir la nueva imagen pixel por pixel. Si un pixel es 255 en las tres
	* imágenes binarias, se escribe 255 en el pixel correspondiente en la nueva imagen */
	int cols = piel.cols, rows = piel.rows;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Scalar y_pixel = y_plane.at<unsigned char>(i, j);
			Scalar u_pixel = cr_plane.at<unsigned char>(i, j);
			Scalar v_pixel = cb_plane.at<unsigned char>(i, j);
			Scalar fg_pixel = fg.at<unsigned char>(i, j);
			int flag = 0;

			if (y_pixel.val[0] == 255 && u_pixel.val[0] == 255 && v_pixel.val[0] == 255)
			{
				if (fg_pixel.val[0] == 255)      piel.at<unsigned char>(i, j) = 255;
			}
		}
	}

	/**************************
	* Operaciones morfológicas
	**************************/
	piel.copyTo(piel_morph);
	morph_op(piel_morph, 2, cv::MORPH_ERODE);
	morph_op(piel_morph, 3, cv::MORPH_DILATE);

	/***************************
	* Contornos y Convexidades
	***************************/

	vector<vector<cv::Point> > contours;
	vector<cv::Vec4i> hierarchy;

	// findContours modifica la imagen fuente, por lo que la copiamos a otra
	piel_morph.copyTo(dst);
	findContours(dst, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	vector<vector<cv::Point> > hull(contours.size());
	vector<vector<int>> hull_int(contours.size());
	vector<vector<cv::Point> > app_contours(contours.size());
	vector<vector<Vec4i>> defects(contours.size());
	Moments contour_moment;

	for (size_t i = 0; i < contours.size(); i++)
	{
		int open_defect_flag = 0, open_n_convexity_flag = 0;
		int point_defect_flag = 0, point_n_convexity_flag = 0;
		int open_crcl_cnvx_flag = 0, open_crcl_cntr_flag = 0;
		int point_crcl_cnvx_flag = 0, point_crcl_cntr_flag = 0;

		double contour_length = arcLength(contours[i], true);

		// Aproximar curvas por líneas
		approxPolyDP(contours[i], app_contours[i], 0.004*contour_length, true);

		// Sólo dibujamos objetos suficientemente grandes
		if (contourArea(app_contours[i]) > 1000.0)
		{
			convexHull(Mat(app_contours[i]), hull[i]);
			convexHull(Mat(app_contours[i]), hull_int[i]);

			// Obtener defectos de convexidad
			convexityDefects(app_contours[i], hull_int[i], defects[i]);

			double defect_sum = 0;
			for (size_t j = 0; j < defects[i].size(); j++)
			{
				if (defects[i][j][3] / 256.0 > 20.0)     defect_sum += defects[i][j][3] / 256.0;
			}

			if (defect_sum >= 0.2*contour_length && defect_sum <= 0.3 *contour_length)  open_defect_flag = 1;
			if (defect_sum >= 0.0*contour_length && defect_sum <= 0.13*contour_length)  point_defect_flag = 1;

			if (open_defect_flag == 0 && point_defect_flag == 0)		continue;

			// Calcular momentos, para encontrar el centroide y dibujarlo
			contour_moment = moments(contours[i], false);
			Point2f centroid = Point2f(contour_moment.m10 / contour_moment.m00, contour_moment.m01 / contour_moment.m00);


			double convx_ratio = contourArea(app_contours[i]) / contourArea(hull[i]);

			if (convx_ratio >= 0.5 && convx_ratio <= 0.75)
			{
				if (hull[i].size() >= 8 && hull[i].size() <= 14)
				{
					open_n_convexity_flag = 1;
				}
			}
			if (convx_ratio >= 0.7 && convx_ratio <= 0.88)
			{
				if (hull[i].size() >= 9 && hull[i].size() <= 16)
				{
					point_n_convexity_flag = 1;
				}
			}

			if (open_n_convexity_flag == 0 && point_n_convexity_flag == 0)	continue;


			Point2f center;
			float radius;
			minEnclosingCircle(app_contours[i], center, radius);

			double circle_convex_ratio = contourArea(hull[i]) / (3.14159*radius*radius);
			double circle_contour_ratio = contourArea(app_contours[i]) / (3.14159*radius*radius);

			if (circle_convex_ratio > 0.68 && circle_convex_ratio < 0.8)    open_crcl_cnvx_flag = 1;
			if (circle_convex_ratio > 0.33 && circle_convex_ratio < 0.47)    point_crcl_cnvx_flag = 1;

			if (circle_contour_ratio > 0.39 && circle_contour_ratio < 0.6)    open_crcl_cntr_flag = 1;
			if (circle_contour_ratio > 0.24 && circle_contour_ratio < 0.37)    point_crcl_cntr_flag = 1;


			// Si cumple con todas las condiciones, lo guardamos
			if (open_defect_flag && open_n_convexity_flag && open_crcl_cntr_flag && open_crcl_cnvx_flag)
			{
				open_hands.push_back(centroid);
			}
			else if (point_defect_flag && point_n_convexity_flag && point_crcl_cntr_flag && point_crcl_cnvx_flag)
			{
				pointing_hands.push_back(centroid);
			}

		}

	}

	open_centroids.push(open_hands);
	point_centroids.push(pointing_hands);
}

/* Detección del gesto evaluando centroides de las manos en distintos frames*/


/* Otras Funciones */
void morph_op(Mat M, int morph_size, int type)
{
	cv::Mat element = cv::getStructuringElement(
		cv::MORPH_ELLIPSE, cv::Size(2 * morph_size + 1, 2 * morph_size + 1),
		cv::Point(morph_size, morph_size));

	cv::morphologyEx(M, M, type, element);
}

void conv_img(Mat img, Mat out)
{
	int i, j, cols = img.cols, rows = img.rows;
	int step = img.step, channels = img.channels();
	uchar *data = out.data;

	double R, G, B;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			Vec3b img_pixel = img.at<Vec3b>(i, j);

			R = (double)img_pixel[2];
			G = (double)img_pixel[1];
			B = (double)img_pixel[0];

			data[i*step + j*channels] = (uchar)(0.299*R + 0.587*G + 0.114*B + 0);
			data[i*step + j*channels + 1] = (uchar)(0.596*R - 0.275*G - 0.332*B + 0);
			data[i*step + j*channels + 2] = (uchar)(0.212*R - 0.523*G + 0.311*B + 0);

		}
	}
}

Mat bs(Mat bg, Mat img, int threshold) {
	Mat diff;
	absdiff(bg, img, diff); //Gets absolute diff between channels

	int r = diff.rows, c = diff.cols;
	//New 1-channel image full of zeros
	Mat foregroundMask = Mat::zeros(r, c, CV_8UC1);

	float t2 = threshold*threshold;
	float dist;

	for (int j = 0; j<r; ++j)
		for (int i = 0; i<c; ++i) {
			Vec3b pix = diff.at<Vec3b>(j, i);
			dist = (pix[0] * pix[0] + pix[1] * pix[1] + pix[2] * pix[2]);
			if (dist > t2)
				foregroundMask.at<unsigned char>(j, i) = 255;
		}
	return foregroundMask;
}
