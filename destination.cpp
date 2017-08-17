#include <bits/stdc++.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "SwarmBot.h"

using namespace std;
using namespace cv;

int sizeX=600;
int sizeY=600;
int BotSize=10;

vector <Points> pts;
Mat A;
int destCount=0;

bool isValid(int i,int j){
  return (i>=0 && i<=sizeX && j>=0 && j<=sizeY);
}

void showDest(){
	/*
  for(int i=bots.at(bots.size()-1).x-BotSize;i<=bots.at(bots.size()-1).x+BotSize;i++){
    for(int j=bots.at(bots.size()-1).y-BotSize;j<=bots.at(bots.size()-1).y+BotSize;j++){
      if(isValid(i,j)){
	A.at<Vec3b>(j,i)[0]=A.at<Vec3b>(j,i)[1]=A.at<Vec3b>(j,i)[2]=255;
      }
    }
  }*/
	/*RotatedRect bot = RotatedRect(Point2f(bots.at(bots.size() - 1).x, bots.at(bots.size() - 1).y), Size2f(2*BotSize, 3*BotSize), bots.at(bots.size() - 1).theta);
	Point2f vertices[4];
	bot.points(vertices);
	for (int i = 0; i < 4; i++)
    line(A, vertices[i], vertices[(i+1)%4], Scalar(255,255,255));*/
  circle( A , Point2i(pts.at(pts.size()-1).x , pts.at(pts.size()-1).y) , 5 , Scalar( 0, 0, 255 ) , -1 , 8);
	//cout << bots.at(bots.size() - 1).x << " " << bots.at(bots.size() - 1).y << endl;
}
	
void CallBackFunc(int event, int i, int j, int flags, void* userdata){
  if(event == EVENT_LBUTTONDOWN){
    Points p;
    p.x=i;
    p.y=j; 
    pts.push_back(p);
    destCount++;
    showDest();
    imshow("InputDestWindow",A);
  }
  else if(event == EVENT_RBUTTONDOWN){
    fstream fs;
		fs.open("Dest.txt" , ios::out ); 
    for(int t=0;t<pts.size();t++){
      Points p=pts.at(t);
      destination(p);
    }
    fs.close();
    exit(0);
  }
}

int main(){

  A=Mat(sizeX,sizeY,CV_8UC3,Scalar(0,0,0));
  namedWindow("InputDestWindow",WINDOW_AUTOSIZE);
  setMouseCallback("InputDestWindow", CallBackFunc, NULL);
  imshow("InputDestWindow",A);
  waitKey(0);
  return 0;

}
