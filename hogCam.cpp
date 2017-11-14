/*#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>*/
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(){
	Mat imagen;//, imagenB, imagenAGris, imagenBGris, imagenUmbral;
	namedWindow("imagen",CV_WINDOW_AUTOSIZE);
	HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	VideoCapture cam(0);
	if(!cam.isOpened()){
		return -1;
	}
	while(true){
		cam>> imagen;
		vector<Rect> found, found_filtered;
    	hog.detectMultiScale(imagen, found, 0, Size(4,4), Size(0,0), 1.05, 1);
    	size_t i, j;
    	for (i=0; i<found.size(); i++){
            Rect r = found[i];
            for (j=0; j<found.size(); j++)
                if (j!=i && (r & found[j])==r)
                    break;
            if (j==found.size())
                found_filtered.push_back(r);
    	}
    	for (i=0; i<found_filtered.size(); i++){
	    	Rect r = found_filtered[i];
        	r.x += cvRound(r.width*0.1);
	    	r.width = cvRound(r.width*0.8);
	    	r.y += cvRound(r.height*0.06);
	    	r.height = cvRound(r.height*0.9);
	    	rectangle(imagen, r.tl(), r.br(), Scalar(0,255,0), 2);//cv::
		}
		imshow("imagen", imagen);
		if(waitKey(30) >= 0) break;
	}
	return 0;
}