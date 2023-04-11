#ifndef __MY_DFS_H__
#define __MY_DFS_H__
#include <iostream>
#include "AdjMatrixUndirNetwork.h"
using namespace std;

template <typename ElemType, typename WeightType>
class DFS
{
private:
    AdjMatrixUndirNetwork<ElemType, WeightType> _graph;
    int *path;
    int VexNum;
    bool circle_exist;
    int path_top;
    int _find(int Vex);
    int *_DFSFindCircle(int i);

public:
    // AdjMatrixUndirNetwork<ElemType, WeightType> _graph;
    DFS(const AdjMatrixUndirNetwork<ElemType, WeightType> &graph);
    ~DFS();
    int *GetCircle();
};

template <typename Elemtype, typename WeightType>
DFS<Elemtype, WeightType>::DFS(const AdjMatrixUndirNetwork<Elemtype, WeightType> &graph) : _graph(graph), VexNum(graph.GetVexNum()), circle_exist(false), path_top(-1)
{
    path = new int[VexNum];
    memset(path, 0, VexNum);
}

// template <typename Elemtype, typename WeightType>
// void DFS<Elemtype, WeightType>::init(AdjMatrixUndirNetwork<Elemtype, WeightType> &_graph)
// {
// }

template <typename Elemtype, typename WeightType>
DFS<Elemtype, WeightType>::~DFS()
{
    if (path != NULL)
        delete[] path;
}

template <typename Elemtype, typename WeightType>
int *DFS<Elemtype, WeightType>::GetCircle()
{
    for (int i = 0; i < VexNum; i++)
    {
        if (_graph.GetTag(i) == UNVISITED)
        {
            for (int j = 0; j < VexNum; j++)
                _graph.SetTag(i, UNVISITED);
            int *ans = _DFSFindCircle(i);
            if (ans == NULL)
                printf("NULL!");
        }
    }
}

template <typename Elemtype, typename WeightType>
int *DFS<Elemtype, WeightType>::_DFSFindCircle(int i)
{
    path[++path_top] = i;
    _graph.SetTag(i, VISITED);
    int tmp = path_top;
    int *ans = NULL;
    for (int u = _graph.FirstAdjVex(i); u >= 0; u = _graph.NextAdjVex(i, u))
    {
        path_top = tmp;
        if (_graph.GetWeight(i, u) != _graph.GetInfinity())
        {
            if (_graph.GetTag(u) == UNVISITED)
            {
                ans = _DFSFindCircle(u);
                if (ans != NULL)
                    return ans;
            }
            else
            {
                int start = _find(u);
                if (start != -1)
                {
                    ans = new int[path_top - start];
                    for (int j = start; j <= path_top; j++)
                        ans[j - start] = path[j];
                    for (int i = 0; i <= path_top; i++)
                    {
                        printf("%d ", ans[i]);
                    }
                    printf("\n");
                    return ans;
                }
            }
        }
    }
    if (circle_exist == false)
        return NULL;
}

template <typename Elemtype, typename WeightType>
int DFS<Elemtype, WeightType>::_find(int Vex)
{
    int index = -1;
    for (int i = 0; i <= path_top; i++)
    {
        if (path[i] == Vex && path_top - i > 1)
        {
            circle_exist = true;
            index = i;
        }
    }
    return index;
}

#endif