#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
//master cg
using namespace std;
using namespace cv;

string face_cascade_name = "haarcascade_frontalface_alt.xml";
//该文件存在于OpenCV安装目录下的\sources\data\haarcascades内，需要将该xml文件复制到当前工程目录下
CascadeClassifier face_cascade;
void detectAndDisplay(Mat frame);
int main(int argc, char** argv) {
	Mat image;
	image = imread("face3.jpg", 1);  //当前工程的image目录下的mm.jpg文件，注意目录符号
	if (!face_cascade.load(face_cascade_name)) {
		printf("级联分类器错误，可能未找到文件，拷贝该文件到工程目录下！\n");
		return -1;
	}
	detectAndDisplay(image); //调用人脸检测函数
	waitKey(0);
	//暂停显示一下。
}

void detectAndDisplay(Mat face) {
	std::vector<Rect> faces;
	Mat face_gray;
	std::cout << "a";
	cvtColor(face, face_gray, CV_BGR2GRAY);  //rgb类型转换为灰度类型
	equalizeHist(face_gray, face_gray);   //直方图均衡化

	face_cascade.detectMultiScale(face_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(1, 1));

	for (int i = 0; i < faces.size(); i++) {
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(face, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 0), 2, 7, 0);
	}
	imshow("人脸识别", face);
}