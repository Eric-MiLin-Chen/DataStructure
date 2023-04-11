#include <iostream>
#include "DFSFindCircle.h"
using namespace std;

int main()
{
    int infity = DEFAULT_INFINITY;
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    // int m[6][6] = {
    //     {infity, 1, infity, infity, infity, infity},
    //     {1, infity, 1, infity, infity, infity},
    //     {infity, 1, infity, 1, infity, infity},
    //     {infity, infity, 1, infity, 1, infity},
    //     {infity, infity, infity, 1, infity, 1},
    //     {infity, infity, infity, infity, 1, infity}};

    int m[6][6] = {
        {infity, 34, 46, infity, infity, 19},
        {34, infity, infity, infity, 12, infity},
        {46, infity, infity, 17, infity, 25},
        {infity, infity, 17, infity, 38, 25},
        {infity, 12, infity, 38, infity, 26},
        {19, infity, 25, 25, 26, infity}};
    int n = 6;

    AdjMatrixUndirNetwork<char, int> net(vexs, n);

    for (int u = 0; u < n; u++)         // 生成邻接矩阵的行
        for (int v = u + 1; v < n; v++) // 生成邻接矩阵元素的值
            if (m[u][v] != infity)
                net.InsertArc(u, v, m[u][v]);
    net.Display(); // 显示网net
    int *Circle = NULL;

    DFS<char, int> test(net);
    int len;
    int *ans = test.GetCircle(len);
    if (len)
    {
        for (int i = 0; i < len; i++)
            cout << ans[i] << " ";
    }
    else
        cout << "NULL!";
    cout << endl;
    // cout << ans << endl;
    return 0;
}