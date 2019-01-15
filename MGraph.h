/*
项目：图-邻接矩阵
创建时间：2018/6/7 | 22:30
完成时间：2018/6/10 | 22:24
最后一次修改时间：2018/12/8
修改次数：3
修改原因：
添加最小生成树算法
添加关键路径
添加最短路径
修复一些严重的bug
//深度遍历，广度优先遍历的bug

作者：CenJieTeng
QQ: 2271369683
*/
#pragma once
#ifndef MGRAPH_H
#define MGRAPH_H
#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>
#include <stack>
#include <vector>
#include "Tree.h"
#define MAXSIZE 20
#define INFINITE INT_MAX
typedef int VertecType;
struct Arc
{
	VertecType arch, arct;
	size_t weight = 0;
};
typedef Arc Arcs[MAXSIZE * 2];

class MGraph
{
	enum GraphType { DG, NDG, DNet, NDNet };//0有向图，1无向图，2有向网，3无向网
public:
	MGraph();
	~MGraph();

public:
	bool CreateGraph();                               //创建(4种)图函数
	void DisPlayGraph()const;						              //打印显示图
	int LocateVex(const VertecType&)const;		        //定点定位函数
	VertecType& GetVex(int);					                //获取相应下标的顶点
	size_t size();                                    //获取大小
	VertecType FirstAdjVex(VertecType);               //返回某顶点的第一个邻接点
	VertecType NextAdjVex(VertecType, VertecType);    //返回v(相当于w)的下一邻接点
	void InsertVex(const VertecType&);                //插入新顶点
	void DeleteVex(VertecType&);                      //删除顶点及其弧(边)
	void InsertEdge(const VertecType&, const VertecType&); //添加弧(边)
	void DeleteEdge(VertecType&, VertecType&);        //删除弧(边)

	void DFSTeraverse();                              //深度优先遍历算法
	void BFSTeraverse();                              //广度优先遍历算法
	void DFSTree(VertecType v, TreeNode *T);          //深度优先生成树(不能单独使用)
	void DFSForest(Tree &T);                          //深度优先生成森林(当图的连通分量数量为1时，生成的是树)
	void BFSTree(VertecType v, TreeNode *T);          //广度优先生成树(不能单独使用)
	void BFSForest(Tree &T);                          //广度优先生成森林(当图的连通分量数量为1时，生成的是树)
	void Prim();                                      //最小生成树,普里姆(Prim)算法
	void Kruskal();                                   //最小生成树,克鲁斯卡尔(Kruskal)算法
	std::queue<VertecType> GetAOV();                  //获取拓扑排序后的顶点序列
	std::queue<VertecType> GetAOE();                  //获取关键路径
	void Dijkstra(VertecType, int [], int []);        //单源点到各顶点最短路径，迪杰斯特拉(Dijkstra)算法

private:
	void DFS(VertecType);                //深度遍历
	static bool visited[MAXSIZE];        //访问标记数组(深度、广度优先遍历需要用到)
	static std::queue<VertecType>Queue;  //广度遍历需要用到的辅助队列

	VertecType vexs[MAXSIZE];            //顶点集合
	int AdjMatrix[MAXSIZE][MAXSIZE];     //邻接矩阵
	size_t vexnum;                       //顶点数
	size_t arcnum;                       //弧(边)数
	//size_t weight;                       //权值，在网中要用到的变量 
	GraphType type;                      //类型
};

#endif // !MGRAPH_H
