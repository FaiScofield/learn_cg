/*
 * ConvexHull 凸包问题
 * 理论最低复杂度，Lower Bound: O(nlogn)
 */

#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <opencv2/opencv.hpp>
#include <sstream>

// 二维点
struct Point
{
    int x, y;       // 坐标值
    bool extreme;   // 是否是极点
    int id;      // 点的索引
    int succ;    // 如是极点，那么它的直接后继

    Point() { extreme = false; succ = id = -1;}
};


// 凸包可视化
void showConvexHull(Point S[], int n)
{
    cv::Mat display(640, 640, CV_8UC3, cv::Scalar(255, 255, 255, 0.5));

    // 画点
    for (int i=0; i<n; ++i) {
        if (S[i].extreme) {
            cv::circle(display, cv::Point(S[i].x, S[i].y), 5,
                       cv::Scalar(255, 0, 0), -1);
            cv::line(display, cv::Point(S[i].x, S[i].y),
                     cv::Point(S[S[i].succ].x, S[S[i].succ].y),
                     cv::Scalar(0, 255, 0), 2);
        }
        else
            cv::circle(display, cv::Point(S[i].x, S[i].y), 5,
                       cv::Scalar(255, 0, 255), -1);

        // 画极线
        std::stringstream point_index;
        point_index << "p" << i;
        cv::putText(display, point_index.str(), cv::Point(S[i].x, S[i].y-10), 1, 1, cv::Scalar(0, 0, 0));
    }

    cv::namedWindow("ConvexHull");
    cv::imshow("ConvexHull", display);
    cv::waitKey();
}


#endif // CONVEXHULL_H
