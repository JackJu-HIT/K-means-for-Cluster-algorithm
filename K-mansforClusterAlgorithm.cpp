/**
 * @Function:K-means for Cluster algorithm
 * @Date:2022-09-05 14:09:00
 * @Create by:juchunyu
 * @Last modified:juchunyu
 */
#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

#define SIZE 6
#define LENGTH 3

int main(){

    int sample[SIZE][2]          = {1,2,1,3,100,100,100,90,300,500,300,480};//模拟输入四个样本(1，2),(1，3),(100,100),(100,90),(300,500),(300,480)
    double classIfy[1000]           = {0}; //1表示类别1，2表示类别2
    double mCenter[LENGTH][2]       = {0,0,50,50,200,200}; //初始质心坐标
    double mCenterTemp[LENGTH][2]   = {0};
    int    iterations               = 10000; //最大迭代次数
    double tolerance                = 0.1; //收敛条件

    for(int t = 0;t < iterations;t++){
       
        /**Start Cluster**/
        for(int i = 0;i < SIZE;i++){
            double minDistance = 100000000;
            for(int j = 0;j < LENGTH;j++){
                double distance = (sample[i][0]-mCenter[j][0]) * (sample[i][0]-mCenter[j][0]) +  (sample[i][1]-mCenter[j][1]) * (sample[i][1]-mCenter[j][1]);
                distance = sqrt(distance);
                if(distance < minDistance){
                    minDistance = distance;
                    classIfy[sample[i][0]] = j + 1;
                }
            }
            
            //重新计算mCenter
            for(int j = 0;j < LENGTH; j++){
                    double xCenter = 0;
                    double yCenter = 0;
                    int    xNum    = 0;
                    for(int i = 0;i < SIZE;i++){
                        if(classIfy[sample[i][0]] == j + 1){
                            xCenter += sample[i][0];
                            yCenter += sample[i][1];
                            xNum ++;
                        }
                    }
                    mCenterTemp[j][0] = xCenter/xNum;
                    mCenterTemp[j][1] = yCenter/xNum;
            }   
        }
         //计算初始误差
        double err = 0;
        for(int i = 0;i < LENGTH;i++){
            err += sqrt((mCenter[i][0]-mCenterTemp[i][0]) * (mCenter[i][0]-mCenterTemp[i][0]) + (mCenter[i][1]-mCenterTemp[i][1]) * (mCenter[i][1]-mCenterTemp[i][1])); 
        }
        if(err < tolerance){
            cout<<"Results Have Been Found!"<<endl;
            break;
        }

        for(int j = 0;j < LENGTH;j++){
            mCenter[j][0] = mCenterTemp[j][0];
            mCenter[j][1] = mCenterTemp[j][1]; 
        }

    }
    //输出质心结果
    cout<<"mCenter"<<endl;
    for(int i  = 0;i < LENGTH;i++){
        cout<<"(";
        for(int j = 0;j < 2;j++){
            cout<<mCenter[i][j]<<" ";
        }
        cout<<")"<<endl;
    }
    
    //输出不同的簇集合
    for(int j = 0;j < LENGTH;j++){
        cout<<"No."<<j+1<<"Group"<<endl;
        for(int i  = 0;i < SIZE;i++){
            if(classIfy[sample[i][0]] == j+1){
                cout<<"("<<sample[i][0]<<","<<sample[i][1]<<")";
            }
            cout<<endl;
        }
    }
}
