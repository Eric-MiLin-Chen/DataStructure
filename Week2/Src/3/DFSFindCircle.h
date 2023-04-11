#ifndef __DFS_FIND_CIRCLE_H__
#define __DFS_FIND_CIRCLE_H__
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
    int *_DFSFindCircle(int i, int &len);

public:
    // AdjMatrixUndirNetwork<ElemType, WeightType> _graph;
    DFS(const AdjMatrixUndirNetwork<ElemType, WeightType> &graph);
    ~DFS();
    int *GetCircle(int &len);
};

template <typename Elemtype, typename WeightType>
DFS<Elemtype, WeightType>::DFS(const AdjMatrixUndirNetwork<Elemtype, WeightType> &graph) : _graph(graph), VexNum(graph.GetVexNum()), circle_exist(false), path_top(-1)
{
    path = new int[VexNum];
    memset(path, 0, VexNum);
}

template <typename Elemtype, typename WeightType>
DFS<Elemtype, WeightType>::~DFS()
{
    if (path != NULL)
        delete[] path;
}

template <typename Elemtype, typename WeightType>
int *DFS<Elemtype, WeightType>::GetCircle(int &len)
{
    for (int i = 0; i < VexNum; i++)
        _graph.SetTag(i, UNVISITED);
    for (int i = 0; i < VexNum; i++)
    {
        if (_graph.GetTag(i) == UNVISITED)
            return _DFSFindCircle(i, len);
    }
    return NULL;
}

template <typename Elemtype, typename WeightType>
int *DFS<Elemtype, WeightType>::_DFSFindCircle(int i, int &len)
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
                ans = _DFSFindCircle(u, len);
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
                    len = path_top - start + 1;
                    // for (int i = 0; i <= path_top; i++)
                    //     printf("%d ", ans[i]);
                    // printf("\n");
                    return ans;
                }
            }
        }
    }
    if (circle_exist == false)
    {
        len = 0;
        return NULL;
    }
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