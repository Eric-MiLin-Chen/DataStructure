#ifndef __DIGISTRA_H__
#define __DIGISTRA_H__
#include <iostream>
#include "AdjMatrixUndirNetwork.h"

template <class ElemType, class WeightType>
void ShortestPathFloyd(const AdjMatrixUndirNetwork<ElemType, WeightType> &g, int **path, WeightType **dist)
{
    for (int u = 0; u < g.GetVexNum(); u++) // 初始化
        for (int v = 0; v < g.GetVexNum(); v++)
        {
            dist[u][v] = (u != v) ? g.GetWeight(u, v) : 0;
            if (u != v && dist[u][v] < g.GetInfinity())
                path[u][v] = u;
            else
                path[u][v] = -1;
        }
    for (int k = 0; k < g.GetVexNum(); k++)     // 求A(k)
        for (int i = 0; i < g.GetVexNum(); i++) // 加入k为中间顶点
            for (int j = 0; j < g.GetVexNum(); j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
}

template <class ElemType, class WeightType>
void ShortestPathDij(const AdjMatrixUndirNetwork<ElemType, WeightType> &graph, int v0, int *path, WeightType *dist)
{
    WeightType minVal, infinity = graph.GetInfinity();
    int v, u;
    // 初始化dist和path数组
    for (v = 0; v < graph.GetVexNum(); v++)
    {
        dist[v] = graph.GetWeight(v0, v);
        if (dist[v] == infinity)
            path[v] = -1;
        else
            path[v] = v0;
        graph.SetTag(v, UNVISITED);
    }
    graph.SetTag(v0, VISITED);
    for (int i = 1; i < graph.GetVexNum(); i++)
    { // 找n-1个终点
        minVal = infinity;
        u = v0;
        for (v = 0; v < graph.GetVexNum(); v++) // 找最短的路径
            if (graph.GetTag(v) == UNVISITED && dist[v] < minVal)
            {
                u = v;
                minVal = dist[v];
            }
        graph.SetTag(u, VISITED);
        // 对u的邻接点，修改路径和路径长度
        for (v = graph.FirstAdjVex(u); v != -1; v = graph.NextAdjVex(u, v))
            if (graph.GetTag(v) == UNVISITED &&
                minVal + graph.GetWeight(u, v) < dist[v])
            {
                dist[v] = minVal + graph.GetWeight(u, v);
                path[v] = u;
            }
    }
}

#endif