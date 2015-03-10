//______________________________________________________________________________________
// Program : SimplAR 2 - OpenCV Simple Augmented Reality Program with Chessboard
// Author  : Bharath Prabhuswamy
//______________________________________________________________________________________

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <highgui.h>
#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <thread>

using namespace std;
using namespace cv;

#define CHESSBOARD_WIDTH 6
#define CHESSBOARD_HEIGHT 5
//The pattern actually has 6 x 5 squares, but has 5 x 4 = 20 'ENCLOSED' corners


IplImage* ipl_image_from_data(char* data)
{


  IplImage *currframe;
  IplImage *dst;
 
  currframe = cvCreateImage(cvSize(320,240), IPL_DEPTH_8U, 3);
  dst = cvCreateImage(cvSize(320,240), IPL_DEPTH_8U, 3);
 
  currframe->imageData = (char*)data;
  cvCvtColor(currframe, dst, CV_BGR2RGB);
  cvReleaseImage(&currframe);
  return dst;
}



Mat getMatFromStram(char* data){
	Mat img = Mat(ipl_image_from_data(data), false);
	return img;
}

void* initZMQ(){
	 //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    // listen to requests
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);
    return responder;
}

void listenForData(void* responder,char*buffer,int n){
	zmq_recv (responder, buffer, n, 0);
	cout<<buffer;
	// printf ("Received %s\n",buffer);
    zmq_send (responder, "World", 5, 0);
}



void scale(vector<Point2f>& corners,float v){
	Point2f pt;
	float n = corners.size();
	cout<<" n : "<< n<<endl;

	// find center and move to center
	float X = 0.0,Y=0.0;
	for (std::vector<Point2f>::iterator it = corners.begin() ; it != corners.end(); ++it)
  	{
  		cout<<it->x<<" "<<it->y<<endl;
  		//pt = *it;
  		// pt = pt *2;
  		X += it->x;
  		Y += it->y;
  		// cout << pt;
  	}
  	X = X / n;
  	Y = Y/n;

	for (std::vector<Point2f>::iterator it = corners.begin() ; it != corners.end(); ++it)
  	{
  		//pt = *it;
  		// pt = pt *2;
  		it->x =  (it->x -X)*v +X;
  		it->y =  (it->y -Y)*v +Y; //  =Point2f( 0,0 );
  		// cout << pt;
  	}
}

bool flag;
Size board_size(CHESSBOARD_WIDTH-1, CHESSBOARD_HEIGHT-1);
vector<Point2f> corners;
bool reading=false;
Mat bwimg,img;
void asyncCheck(){
	int i = 0;
	bool iFlag = false;
	while(true){

		while(bwimg.empty()==false ){
			reading=true;
			// printf("Runnin %x\n",flag);
			this_thread::yield();
			iFlag = findChessboardCorners(bwimg, board_size, corners);
			// printf("cunt %d  %d\n",i,iFlag);
			this_thread::yield();
			if(flag!=iFlag){
				this_thread::yield();
				//i=1;
				flag = true;
			}
			if(i==0)
				flag = iFlag;
			else
				i--;
			// flag = findChessboardCorners(bwimg, board_size, corners);


			// scale the corners
			// imshow("bw",bwimg);
/////
			// printf("%s\n", );








///////
			reading=false;
		}
	}
}

void miau(){
	while(true){
		while(img.empty()==false ){

			imshow("Camera", img);
			imshow("Camera2", img);
			int xOff=130,yOff=205;
			moveWindow("Camera",xOff,yOff);
			moveWindow("Camera2",910+xOff,yOff);
		}
	}
}
VideoCapture capture;// ( "http://localhost:8124/");

void readThreadImage(){
	
	while(true){
		capture >> img;

	}
}
 

int main ( int argc, char **argv )
{

	// Mat img;
	Mat display = imread("wild.jpg");
	Mat display1 = imread("shingani.jpg");
	Mat display2 = imread("raytheon.jpg");
	Mat display3 = imread("tree.jpg");
	Mat display4 = imread("us.jpg");
	Mat* currentDisplay = &display;
	capture = VideoCapture( "http://localhost:8124/");
	// capture = VideoCapture( 0);
	capture >> img;
	// VideoCapture capture(0);// "http://localhost:8124/"
	
	// int key = 0;
 // namedWindow("Camera", CV_WINDOW_NORMAL);
 // setWindowProperty("Camera", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
    
	
	flag = 0;
	if(display.empty())
	{
		cerr << "ERR: Unable to find overlay image.\n" << endl;
		return -1;
	}
	
	if ( !capture.isOpened() )
	{
		cerr << "ERR: Unable to capture frames from device 0" << endl;
		return -1;
	}
    printf("%s\n",argv[1]);
    int key = 0;
    void *responder = initZMQ();
    int size = 3*640*480;//100*320*240*3;

	char* buffer = new char[size];
	

/*
	int iLoop1 = 2000;
	while(iLoop1--){
		capture >> img;
	}
	*/


	std::thread thAsync (asyncCheck);
	std::thread thAsync3 (readThreadImage);
	// std::thread thAs (miau);

	while(1)
	{
		// Query for a frame from Capture device
		// capture >> img;
	
		//listenForData(responder,buffer,size);
		//img = getMatFromStram((char*)buffer);
		// debug buffer
		// fwrite(buffer, 1024*12, 1, stdout);
		// cin.read (buffer,255);
		// cout<<buffer<<"Mia\n";
		// cin >> cout;
		// printf("Te quiero\n");ß
		// printf("%s\n", );

		Mat cpy_img(img.rows, img.cols, img.type());
		Mat neg_img(img.rows, img.cols, img.type());
		Mat gray;
		Mat blank((*currentDisplay).rows, (*currentDisplay).cols, (*currentDisplay).type());

        cvtColor(img, gray, CV_BGR2GRAY);

        // img = getMatFromStram(NULL);
        //if(reading==false)
        bwimg = gray  ; // > 150 
// 
//        imshow("blackwhite",bwimg);

		
		// printf("vio %d\n",flag);
		if(flag == 1 )
		{            
			//printf("saw tarage\n");
			
			// 
			// This function identifies the chessboard pattern from the gray image, saves the valid group of corners
			cornerSubPix(gray, corners, Size(11,11), Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1));
			// scale(corners,2);
			
			vector<Point2f> src;			// Source Points basically the 4 end co-ordinates of the overlay image
			vector<Point2f> dst;			// Destination Points to transform overlay image	
			
			src.push_back(Point2f(0,0));
			src.push_back(Point2f((*currentDisplay).cols,0));
			src.push_back(Point2f((*currentDisplay).cols, (*currentDisplay).rows));
			src.push_back(Point2f(0, (*currentDisplay).rows));
	
			dst.push_back(corners[0]);
			dst.push_back(corners[CHESSBOARD_WIDTH-2]);
			dst.push_back(corners[(CHESSBOARD_WIDTH-1)*(CHESSBOARD_HEIGHT-1)-1]);
			dst.push_back(corners[(CHESSBOARD_WIDTH-1)*(CHESSBOARD_HEIGHT-2)]);
	
			// Compute the transformation matrix, 
			// i.e., transformation required to overlay the (*currentDisplay) image from 'src' points to 'dst' points on the image
			Mat warp_matrix = getPerspectiveTransform(src, dst)*5;

			blank = Scalar(0);
			neg_img = Scalar(0);								// Image is white when pixel values are zero
			cpy_img = Scalar(0);								// Image is white when pixel values are zero

			bitwise_not(blank,blank);

			// Note the jugglery to augment due to OpenCV's limitation passing two images of DIFFERENT sizes while using "cvWarpPerspective"
			// printVect();

			warpPerspective((*currentDisplay), neg_img, warp_matrix, Size(neg_img.cols, neg_img.rows));	// Transform overlay Image to the position	- [ITEM1]
			warpPerspective(blank, cpy_img, warp_matrix, Size(cpy_img.cols, neg_img.rows));		// Transform a blank overlay image to position	
			bitwise_not(cpy_img, cpy_img);							// Invert the copy paper image from white to black
			bitwise_and(cpy_img, img, cpy_img);						// Create a "hole" in the Image to create a "clipping" mask - [ITEM2]						
			bitwise_or(cpy_img, neg_img, img);						// Finally merge both items [ITEM1 & ITEM2]



	 
		}

		imshow("Camera", img);
		// imshow("Camera3", img);
		imshow("Camera2", img);
		int xOff=130,yOff=205;
 		moveWindow("Camera",xOff,yOff);
		moveWindow("Camera2",910+xOff,yOff);

 		// moveWindow("Camera",xOff,yOff);


		// cvShowImage("Camera", img);
		switch(waitKey(1)){
			case '1':
				currentDisplay = &display;
			break;
			case '2':
				currentDisplay = &display1;
			break;
			case '3':
				currentDisplay = &display2;
			break;
			case '4':
				currentDisplay = &display3;
			break;
			case '5':
				currentDisplay = &display4;
			break;
		}
		// printf("%d\n", waitKey(1));
/*
		if(waitKey(1)== 27){
			break;
		}*/
		//cvWaitKey(0);	
	}
    
	destroyAllWindows();
	return 0;
}




