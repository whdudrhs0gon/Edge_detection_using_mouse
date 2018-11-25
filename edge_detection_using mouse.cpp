#include "cv.hpp"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Rect box;
bool do_draw = false, finish = false;
#define RED Scalar(0, 0, 255)
#define GREEN Scalar(0,255,0)
#define BLUE Scalar(255,0,0)

int main() {
	void onMouse(int event, int x, int y, int, void*);

	Mat f = imread("lena.jpg");
	assert(!f.empty());

	namedWindow("edge detection");
	setMouseCallback("edge detection", onMouse, (void*)&f);

	while (!finish)
	{
		Mat tmp = f.clone();
		if (do_draw) rectangle(tmp, box, RED, 2);
		imshow("edge detection", tmp);
		if (waitKey(20) == 27) break;
	}
	Mat gray;
	cvtColor(f, gray, CV_BGR2GRAY);

	Mat patch = gray(box);
	Canny(patch, patch, 30, 30 * 2.5, 3);
	patch = 255 - patch;
	imshow("edge detection", gray);

	waitKey();
	return 0;
}


void onMouse(int event, int x, int y, int, void*)
{
	if (event == EVENT_MOUSEMOVE && !finish)
	{
		box.width = x - box.x;
		box.height = y - box.y;
	}
	else if (event == EVENT_LBUTTONDOWN && !finish)
	{
		do_draw = true;
		box = Rect(x, y, 0, 0);
	}
	else if (event == EVENT_LBUTTONUP && !finish)
	{
		do_draw = false;
		if (box.width < 0)
		{
			box.x += box.width;
			box.width *= -1;
		}
		if (box.height < 0)
		{
			box.y += box.height;
			box.height *= -1;
			finish = true;
		}
	}
}

