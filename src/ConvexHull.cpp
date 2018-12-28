#include "ConvexHull.h"

#include <stack>
#include <vector>
#include <chrono>
#include <fstream>
#include <iostream>


using namespace std;

/****** 极点判断法，O(n^4) *****/
bool toLeft(Point a, Point b, Point c)
{
    /*
     *       | a.x  a.y  1 |
     * 2*S = | b.x  b.y  1 |
     *       | c.x  c.y  1 |
     */
    float area_2 = a.x * b.y - a.y * b.x +
                   b.x * c.y - b.y * c.x +
                   c.x * a.y - c.y * a.x;

    return area_2 > 0;
}

bool inTriangle(Point p, Point q, Point r, Point s)
{
    bool pqLeft = toLeft(p, q, s);
    bool qrLeft = toLeft(q, r, s);
    bool rpLeft = toLeft(r, p, s);

    return (pqLeft == qrLeft) && (qrLeft == rpLeft);
}

void extremePoint(Point S[], int n)
{
    cout << "********** 最笨的方法，遍历各点，O(n^4) **********" << endl;
    for (int i = 0; i < n; ++i)
        S[i].extreme = true;

    for (int p = 0; p < n; ++p) {
        for (int q = p + 1; q < n; ++q)
            for (int r = q + 1; r < n; ++r)
                for (int s = 0; s < n; ++s) {
                    if (s == p || s == q || s == r || !S[s].extreme)
                        continue;
                    if (inTriangle(S[p], S[q], S[r], S[s]))
                        S[s].extreme = false; // 无法知道各极点的后继
                }
    }
}

/****** 极边判断法，O(n^3) *****/
void checkEdge(Point S[], int n, int p, int q)
{
    bool lEmpty = true, rEmpty = true;
    for (int k = 0; k < n && (lEmpty || rEmpty); ++k) {
        if ((k != p) && (k != q))
            toLeft(S[p], S[q], S[k]) ?
            lEmpty = false : rEmpty = false;
    }
    if (lEmpty || rEmpty)
        S[p].extreme = S[q].extreme = true; // 无法知道各极点的后继
}

void markEE(Point S[], int n)
{
    cout << "********** 稍笨的方法，从边入手，O(n^3) **********" << endl;
    for (int i = 0; i < n; ++i)
        S[i].extreme = false;

    for (int p = 0; p < n; ++p) {
        for (int q = p + 1; q < n; ++q)
            checkEdge(S, n, p, q);
    }

}

/*****
 * Jarvis March法，O(n^2)
 * 准确的说复杂度是O(nh), h为凸包的size
 * 具有输出敏感性，复杂度与输出的规模有关
 *****/
void JarvisMarch(Point S[], int n)  // n > 2
{
    cout << "********** 不错的方法，相邻原则(JarvisMarch)，O(n^2) **********" << endl;
    // 1.确认第一个极点，最低最左原则: Lowest-then-leftmost
    int ltl = 0;
    for (int i = 1; i < n; ++i) {
        if (S[i].y < S[ltl].y ||    // lower
            (S[i].y == S[ltl].y && S[i].x < S[ltl].x) )
            ltl = i;
    }
    cout << "Index of Lowest-then-leftmost:  " << ltl << endl;
    // 2.从第一个极点S[ltl]开始，由to-Left-test陆续找到下一个极点s，直到s==ltl
    int k = ltl;
    do {
        S[k].extreme = true;
        int s = -1;
        for (int t = 0; t < n; ++t) // check
            if (t != k && t != s && // candidate t
                (s == -1 || !toLeft(S[k], S[s], S[t])) )
                s = t; // update s if t lies right to line_sk
        S[k].succ = s; k = s;
        cout << "next is " << s << endl;
    } while (ltl != k); // quit when ltl reached

}

/*****
 * Graham Scan法，O(nlogn)
 * 所有点围绕某一点的极角有序排列
 * 根据欧拉公式知，平面图中所有边的数目+面数不会超过3n
 * scan的过程中最多会迭代2n-5步（不考虑退化情况）
 * 对于输入平面上x(y)方向上已经有序的点集处理，可以达到O(n)的复杂度：
 * 1) 从右往左做一次GS得到上凸包 upper hull
 * 2) 从左往右再做一次GS得到下凸包 lower hull
 * 3) 结合上下两个凸包，即可得到完整的 convex hull
 *
 *****/
double dist(Point a, Point b)
{
    return ((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

void GrahamScan(Point P[], int n)
{
    cout << "********** 最优的方法，极角扫描(GrahamScan)，O(nlogn) **********" << endl;

    // step 1 - 找到ltl点
    int ltl = 0;
    for (int i = 1; i < n; ++i) {
        if (P[i].y < P[ltl].y ||    // lower
            (P[i].y == P[ltl].y && P[i].x < P[ltl].x) )
            ltl = i;
    }
    cout << "Index of Lowest-then-leftmost:  " << ltl << endl;

    // step 2 - 按极角大小逆时针排序
    vector<pair<float, int>> V;
    V.push_back(make_pair(0.0, ltl));
    for (int i = 0; i < n; ++i) {
        if (i == ltl) continue;

        float angle = atan2(float(P[i].y-P[ltl].y), float(P[i].x-P[ltl].x));
        if (angle < 0) angle += 2 * float(M_PI);
        V.push_back(make_pair(angle, i));
    }
    sort(V.begin(), V.end());

    // step 3 - 极角最小的存入栈中开始扫描，这里为了方便访问用vector来模拟栈
    vector<Point*> T, S;
    S.push_back(&P[V[0].second]); S.push_back(&P[V[1].second]);
    for (int i = n-1; i > 1; --i) T.push_back(&P[V[i].second]);

    while (!T.empty()) {
        int p = S.size();

        // test type of current turn
        if (toLeft(*S[p-2], *S[p-1], *T.back())) {
            S.push_back(T.back());
            T.pop_back();
        }
        else S.pop_back();
    }

    // 所有的极点存在栈S内
    for (int i = 0; i < int(S.size() - 1); ++i) {
        S[i]->extreme = true;
        S[i]->succ = S[i+1]->id;
    }
    S.back()->extreme = true;
    S.back()->succ = ltl;
}

int main(int argc, char *argv[])
{
    // 读取点的数据
//    ifstream ifs("../OJViewers/PA1/example/ch_points.txt");
//    if (!ifs.is_open())
//        cerr << "Open file failed...\n";

//    int n, m = 0;
//    ifs >> n;
//    Point *S = new Point[10];
//    for (int i = 0; i < n; ++i)
//        ifs >> S[i].x >> S[i].y;

    if (argc < 2) {
        cout << "Usage: ConvexHull [number_of_points]\n";
        return -1;
    }
    srand(unsigned(time(nullptr)));

    // 随机生成n个二维点
    int n = atoi(argv[1]);
    Point *S1 = new Point[n];
    Point *S2 = new Point[n];
    Point *S3 = new Point[n];
    Point *S4 = new Point[n];
    for (int i = 0; i < n; ++i) {
        S1[i].id = S2[i].id = S3[i].id = S4[i].id = i;
        S1[i].x = S2[i].x = S3[i].x = S4[i].x = rand() % 500 + 80;
        S1[i].y = S2[i].y = S3[i].y = S4[i].y = rand() % 500 + 80;
    }

    // 求凸包的极点
    Point *S = nullptr;
    for (int i=0; i<4; ++i) {
        auto t1 = chrono::steady_clock::now();
        switch (i) {
            case 0:
                extremePoint(S1, n); S = S1; break;
            case 1:
                markEE(S2, n); S = S2; break;
            case 2:
                JarvisMarch(S3, n); S = S2; break;
            default:
                GrahamScan(S4, n); S = S3; break;
        }
        auto t2 = chrono::steady_clock::now();

        cout << "extreme points:\n";
        int m = 0;
        for (int i = 0; i < n; ++i)
            if (S[i].extreme) {
                printf(" - Point %3d(%3d, %3d)\n", i, S[i].x, S[i].y);
                m++;
            }
        auto dt = chrono::duration_cast<chrono::duration<double>>(t2 - t1).count();
        cout << "get tatal " << m << " extreme points. Cost time(us): "
             << 1000000*dt << endl << endl;
    }

    showConvexHull(S3, n);
    showConvexHull(S4, n);

    return 0;
}
