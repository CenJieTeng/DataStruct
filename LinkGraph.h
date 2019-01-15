//项目：图-临接表
//创建时间：2018/12/10 13:39
//完成时间：
//最后一次修改时间:
//
//
//
//作者：CenJieTeng
//QQ: 2271369683

#pragma once
#ifndef LINKGRAPH_H
#define LINKGRAPH_H
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include "Tree.h"
#define MAXSIZE 20
#define INFINITE INT_MAX

namespace cjt
{
	struct ArcNode
	{
		int adjVex;
		ArcNode *nextArc;
		int weight;
	};

	template <typename T>
	class LinkGraph
	{
		struct VNode;
		using VertecType = T;
		enum GraphType { DG, NDG, DNet, NDNet };//0有向图，1无向图，2有向网，3无向网
	public:
		LinkGraph();
		~LinkGraph();

		LinkGraph(const LinkGraph &lg);
		LinkGraph& operator=(const LinkGraph &lg);

	public:
		bool CreateGraph();                                     //创建图
		void ClearGraph();                                      //清除图
		void DisPlayGraph()const;						                    //打印显示图
		int LocateVex(const VertecType&)const;		              //定点定位函数
		VNode& GetVex(int n);					                          //获取相应下标的顶点
		int GetWeight(const VertecType&, const VertecType&);    //获取某条边的权值
		ArcNode * GetLastArcNode(const size_t n)const;          //获取第n个顶点最后一个弧(边)结点的指针
		ArcNode * GetReVerLastArcNode(const size_t n)const;     //获取第n个顶点最后一个(reVer表)弧(边)结点的指针
		size_t size();                                          //获取大小
		VNode* FirstAdjVex(const VNode &v);                     //返回某顶点的第一个邻接点
		VNode* NextAdjVex(const VNode &v, const VNode &w);      //返回v(相当于w)的下一邻接点
		void InsertVex(const VertecType&);                      //插入新顶点
		void DeleteVex(const VertecType&);                      //删除顶点及其弧( 边)
		void InsertEdge(const VertecType&, const VertecType&);  //添加弧(边)
		void DeleteEdge(const VertecType&, const VertecType&);  //删除弧(边)

		void DFSTeraverse();                              //深度优先遍历算法
		void BFSTeraverse();                              //广度优先遍历算法
		void DFSTree(VNode v, TreeNode *T);               //深度优先生成树(不能单独使用)
		void DFSForest(Tree &T);                          //深度优先生成森林(当图的连通分量数量为1时，生成的是树)
		void BFSTree(VNode v, TreeNode *T);               //广度优先生成树(不能单独使用)
		void BFSForest(Tree &T);                          //广度优先生成森林(当图的连通分量数量为1时，生成的是树)
		void Prim(Tree &T, const VertecType &v);          //最小生成树,普里姆(Prim)算法
		void Kruskal(Tree &T);                            //最小生成树,克鲁斯卡尔(Kruskal)算法
		std::queue<VertecType> GetAOV();                  //获取拓扑排序后的顶点序列
		std::queue<VertecType> GetAOE();                  //获取关键路径
		void Dijkstra(VertecType, int**, int**);            //单源点到各顶点最短路径，迪杰斯特拉(Dijkstra)算法

	protected:
		typedef struct VNode
		{
			T data;
			ArcNode * firstArc;
		}VNode, AdjList[MAXSIZE];

	private:
		bool DeleteEdge_Tool(VNode *verPtr, int v, int w);                      //删除弧(边)
		ArcNode* GetLastArcNode_Tool(const VNode *verPtr, const size_t n)const; //获取第n个顶点最后一个(verPtr表)弧(边)结点的指针
		void DFS(const VNode&);                                                 //深度遍历

	private:
		static bool visited[MAXSIZE];                     //访问标记数组(深度、广度优先遍历需要用到)
		static std::queue<VNode>Queue;                    //广度遍历需要用到的辅助队列
		AdjList vertices;
		AdjList reVertices;                               //有向图的逆邻接表
		size_t vexnum, arcnum;
		GraphType type;
	};


}

#endif // !LINKGRAPH_H

//-------------------------------------华丽的分割线-------------------------------------------------

namespace cjt
{

	using std::cout; using std::cin; using std::endl;
	#define D_ARC_MAXNUM(v) v * (v - 1)       //有向图(网)的最大弧数，v 是顶点数
	#define ND_ARC_MAXNUM(v) v * (v - 1) / 2  //无向图(网)的最大弧数，v 是顶点数

	template <typename T> bool LinkGraph<T>::visited[MAXSIZE];
	template <typename T> std::queue<typename LinkGraph<T>::VNode> LinkGraph<T>::Queue;


	template <typename T>
	LinkGraph<T>::LinkGraph() : vexnum(0), arcnum(0), type(DNet)
	{
		if (type == DG || type == NDG)
		{
			for (int i = 0; i < MAXSIZE; ++i)
			{
				vertices[i].data = 0;
				vertices[i].firstArc = nullptr;
			}
		}
		else
		{
			for (int i = 0; i < MAXSIZE; ++i)
			{
				vertices[i].data = INFINITE;
				vertices[i].firstArc = nullptr;
			}
		}

		//初始化逆邻接表
		for (int i = 0; i < MAXSIZE; ++i)
		{
			reVertices[i].firstArc = nullptr;
		}
	}

	template <typename T>
	LinkGraph<T>::~LinkGraph()
	{
		ClearGraph();
	}

	//拷贝构造函数
	template <typename T>
	LinkGraph<T>::LinkGraph(const LinkGraph &lg)
	{
		for (size_t i = 0; i < lg.vexnum; ++i)
		{
			vertices[i].data = lg.vertices[i].data;
			ArcNode *q = lg.vertices[i].firstArc;

			if (q != nullptr)
			{
				ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
				*p = { q->adjVex, nullptr, q->weight };
				vertices[i].firstArc = p;

				q = q->nextArc;
				while (q)
				{
					ArcNode *p2 = (ArcNode*)malloc(sizeof(ArcNode));
					*p2 = { q->adjVex, nullptr, q->weight };

					p->nextArc = p2;
					p = p2;
					q = q->nextArc;
				}
			}
			else
				vertices[i].firstArc = nullptr;
		}

		for (size_t i = 0; i < lg.vexnum; ++i)
		{
			reVertices[i].data = lg.reVertices[i].data;
			ArcNode *q = lg.reVertices[i].firstArc;

			if (q != nullptr)
			{
				ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
				*p = { q->adjVex, nullptr, q->weight };
				reVertices[i].firstArc = p;

				q = q->nextArc;
				while (q)
				{
					ArcNode *p2 = (ArcNode*)malloc(sizeof(ArcNode));
					*p2 = { q->adjVex, nullptr, q->weight };

					p->nextArc = p2;
					p = p2;
					q = q->nextArc;
				}
			}
			else
				reVertices[i].firstArc = nullptr;
		}

		vexnum = lg.vexnum;
		arcnum = lg.arcnum;
		type = lg.type;
	}

	//拷贝赋值运算符
	template<typename T>
	LinkGraph<T>& LinkGraph<T>::operator=(const LinkGraph &lg)
	{
		LinkGraph lgTemp = *this;
		if (this != &lg)
		{
			this->ClearGraph();

			try
			{
				for (size_t i = 0; i < lg.vexnum; ++i)
				{
					vertices[i].data = lg.vertices[i].data;
					ArcNode *q = lg.vertices[i].firstArc;

					if (q != nullptr)
					{
						ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
						*p = { q->adjVex, nullptr, q->weight };
						vertices[i].firstArc = p;

						q = q->nextArc;
						while (q)
						{
							ArcNode *p2 = (ArcNode*)malloc(sizeof(ArcNode));
							*p2 = { q->adjVex, nullptr, q->weight };

							p->nextArc = p2;
							p = p2;
							q = q->nextArc;
						}
					}
					else
						vertices[i].firstArc = nullptr;
				}

				for (size_t i = 0; i < lg.vexnum; ++i)
				{
					reVertices[i].data = lg.reVertices[i].data;
					ArcNode *q = lg.reVertices[i].firstArc;

					if (q != nullptr)
					{
						ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
						*p = { q->adjVex, nullptr, q->weight };
						reVertices[i].firstArc = p;

						q = q->nextArc;
						while (q)
						{
							ArcNode *p2 = (ArcNode*)malloc(sizeof(ArcNode));
							*p2 = { q->adjVex, nullptr, q->weight };

							p->nextArc = p2;
							p = p2;
							q = q->nextArc;
						}
					}
					else
						reVertices[i].firstArc = nullptr;
				}

				vexnum = lg.vexnum;
				arcnum = lg.arcnum;
				type = lg.type;
			}
			catch (const std::bad_alloc)
			{
				this->ClearGraph();
				*this = lgTemp;
			}
		
		}

		return *this;
	}

	//创建图
	template <typename T>
	bool LinkGraph<T>::CreateGraph()
	{
		cout << "0有向图，1无向图，2有向网，3无向网" << endl;
		cout << "输入你要创建的图的类型 ";
		int i;
		cin >> i;
		switch (i)
		{
		case DG: type = DG; break;
		case NDG: type = NDG; break;
		case DNet: type = DNet; break;
		case NDNet: type = NDNet; break;
		default:
			return false;
		}

		cout << "请输入顶点数，弧(边)数，空格分隔，下同";
		size_t arcnumTemp = 0;
		cin >> vexnum >> arcnumTemp;

		switch (type)
		{
		case DG:
		case DNet:
			if (vexnum > MAXSIZE || arcnumTemp > D_ARC_MAXNUM(vexnum))
			{
				cout << "创建失败" << endl;
				*this = LinkGraph();            //创建失败，把图置于初始状态

				return false;
			}break;

		case NDG:
		case NDNet:
			if (vexnum > MAXSIZE || arcnumTemp > ND_ARC_MAXNUM(vexnum))
			{
				cout << "创建失败" << endl;
				*this = LinkGraph();            //创建失败，把图置于初始状态

				return false;
			}break;
		}

		cout << "输入" << vexnum << "个顶点的值(1个VertecType) " << endl;
		for (size_t i = 0; i < vexnum; ++i)
		{
			cin >> vertices[i].data;
			if (type == DG || type == DNet)
				reVertices[i].data = vertices[i].data;
		}
		


		cout << "输入" << arcnumTemp << "条弧(边)的弧尾，弧头" << endl;
		for (size_t i = 0; i < arcnumTemp; ++i)
		{
			cout << "第" << i + 1 << "条 ";
			VertecType v1, v2;
			cin >> v1 >> v2;

			//创建边
			InsertEdge(v1, v2);
		}

		return true;
	}

	//清除图
	template <typename T>
	void LinkGraph<T>::ClearGraph()
	{
		if (vexnum == 0)
			return;

		for (int i = (int)vexnum - 1; i >= 0; i--)
			DeleteVex(vertices[i].data);
	}

	//打印显示图
	template <typename T>
	void LinkGraph<T>::DisPlayGraph()const
	{
		cout << "临接表" << endl;
		for (size_t i = 0; i < vexnum; ++i)
		{
			cout << i << "|"<< " data " << vertices[i].data << " --> ";

			auto p = vertices[i].firstArc;
			while (p != nullptr)
			{
				cout << p->adjVex << " --> ";
				p = p->nextArc;
			}
			cout  << "NULL"<< endl;
		}

		if (type == DG || type == DNet)
		{
			cout << "逆临接表" << endl;

			for (size_t i = 0; i < vexnum; ++i)
			{
				cout << i << "|" << " data " << vertices[i].data << " --> ";

				auto p = reVertices[i].firstArc;
				while (p != nullptr)
				{
					cout << p->adjVex << " --> ";
					p = p->nextArc;
				}
				cout << "NULL" << endl;
			}
		}
	
	}

	//定点定位函数
	template <typename T>
	int LinkGraph<T>::LocateVex(const VertecType &x)const
	{
		for (size_t i = 0; i < vexnum; ++i)
			if (vertices[i].data == x)
				return i;

		return -1;
	}

	//获取相应下标的顶点
	template<typename T>
	typename LinkGraph<T>::VNode& LinkGraph<T>::GetVex(int n)
	{
		if (n < 0 || (size_t)n > vexnum)
			exit(-1);

		return vertices[n];
	}

	//获取某条边的权值
	template <typename T>
	int LinkGraph<T>::GetWeight(const VertecType &vt, const VertecType &wt)
	{
		if (type == DG || type == NDG)
			return 0;

		int v1 = LocateVex(vt);
		int w1 = LocateVex(wt);
		if (v1 == -1 || w1 == -1)
			return INFINITE;

		auto p = GetVex(v1).firstArc;
		while (p && p->adjVex != w1)
			p = p->nextArc;

		if (p)
			return p->weight;

		return INFINITE;
	}

	//获取第n个顶点最后一个弧(边)结点的指针
	template <typename T>
	ArcNode* LinkGraph<T>::GetLastArcNode(const size_t n)const
	{
		return GetLastArcNode_Tool(vertices, n);
	}

	//获取第n个顶点最后一个(reVer表)弧(边)结点的指针
	template <typename T>
	ArcNode* LinkGraph<T>::GetReVerLastArcNode(const size_t n)const
	{
		return GetLastArcNode_Tool(reVertices, n);
	}

	//获取大小
	template <typename T>
	size_t LinkGraph<T>::size() 
	{
		return vexnum;
	}

	//获取第n个顶点最后一个表结点的指针
	template <typename T>
	ArcNode* LinkGraph<T>::GetLastArcNode_Tool(const VNode *verPtr, size_t n)const
	{
		if (n > vexnum)
			return nullptr;

		ArcNode *p = verPtr[n].firstArc;
		if (p == nullptr)
			return p;

		while (p->nextArc != nullptr)
			p = p->nextArc;

		return p;
	}

	//返回某顶点的第一个邻接点序号
	template <typename T>
	inline typename LinkGraph<T>::VNode* LinkGraph<T>::FirstAdjVex(const VNode &v)
	{
		auto p = v.firstArc;
		if (p != nullptr)
			return &vertices[p->adjVex];

		return nullptr;
	}

	//返回v(相当于w)的下一邻接点
	template <typename T>
	typename LinkGraph<T>::VNode* LinkGraph<T>::NextAdjVex(const VNode &v, const VNode &w)
	{
		auto p = v.firstArc;
		while (p != nullptr && GetVex(p->adjVex).data != w.data)
			p = p->nextArc;

		if (p != nullptr && p->nextArc != nullptr)
		{
			p = p->nextArc;
			return &vertices[p->adjVex];
		}
		

		return nullptr;
	}

	//插入新顶点
	template <typename T>
	void LinkGraph<T>::InsertVex(const VertecType &v)
	{
		if (vexnum == MAXSIZE)
			return;

		vertices[vexnum].firstArc = nullptr;
		vertices[vexnum].data = v;

		if (type == DG || type == DNet)
		{
			reVertices[vexnum].firstArc = nullptr;
			reVertices[vexnum].data = v;
		}

		++vexnum;
	}

	//删除顶点及其弧(边)
	template <typename T>
	void LinkGraph<T>::DeleteVex(const VertecType &v)
	{
		int v1 = LocateVex(v);

		if (v1 == -1)
			return;

		//删除附着顶点v的边
		for (size_t i = 0; i < vexnum; ++i)
			DeleteEdge(v, vertices[i].data);

		//更新移动后的指向
		for (size_t j = 0; j < vexnum - 1; ++j)
		{
			ArcNode *p = vertices[j].firstArc;
			while (p != nullptr)
			{
				if (p->adjVex > v1)
					p->adjVex -= 1;
				p = p->nextArc;
			}

			p = reVertices[j].firstArc;
			while (p != nullptr)
			{
				if (p->adjVex > v1)
					p->adjVex -= 1;
				p = p->nextArc;
			}
		}	

		vexnum--;
	}

	//添加弧(边)
	template <typename T>
	void LinkGraph<T>::InsertEdge(const VertecType &v, const VertecType &w)
	{
		//v w 已经存在边，退出
		if (type == DG || type == NDG)
		{
			if (GetWeight(v, w) != 0)
				return;
		}
		else
		{
			if (GetWeight(v, w) != INFINITE)
				return;
		}
	

		int v1 = LocateVex(v);
		int w1 = LocateVex(w);
		//没有找到要创建边的顶点
		if (v1 == -1 || w1 == -1)
			return;

		int wg = 0;
		if (type == DNet || type == NDNet)
		{
			cout << "输入弧(边)的权值,范围[1,INFINITE) ";
			cin >> wg;
		}

		ArcNode *arcPtr = GetLastArcNode(v1);
		ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
		*p = { w1, nullptr, wg };

		if (arcPtr == nullptr) 
			vertices[v1].firstArc = p;
		else
			arcPtr->nextArc = p;

		//如果是无向图(网)，反过来建立邻接表
		if (type == NDG || type == NDNet)
		{
			ArcNode *arcPtr = GetLastArcNode(w1);
			ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
			*p = { v1, nullptr, wg };

			if (arcPtr == nullptr)
				vertices[w1].firstArc = p;
			else
				arcPtr->nextArc = p;
		}
		else //建立逆邻接表
		{
			ArcNode *arcPtr = GetReVerLastArcNode(w1);
			ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
			*p = { v1, nullptr, wg };

			if (arcPtr == nullptr)
				reVertices[w1].firstArc = p;
			else
				arcPtr->nextArc = p;
		}

		arcnum++;
	}


	//删除弧(边)
	template <typename T>
	void LinkGraph<T>::DeleteEdge(const VertecType &v, const VertecType &w)
	{
		int v1 = LocateVex(v);
		int w1 = LocateVex(w);
		//没有找到要删除边的顶点
		if (v1 == -1 || w1 == -1)
			return;

		bool rt = DeleteEdge_Tool(vertices, v1, w1);

		if (type == NDG || type == NDNet)
			rt |= DeleteEdge_Tool(vertices, w1, v1);
		else
		{
			rt = DeleteEdge_Tool(vertices, w1, v1);
			rt |= DeleteEdge_Tool(reVertices, v1, w1);
			rt |= DeleteEdge_Tool(reVertices, w1, v1);
		}
		
		
		if (rt)
			arcnum--;
	}

	//删除弧(边)TOOL
	template <typename T>
	bool LinkGraph<T>::DeleteEdge_Tool(VNode *verPtr,int v, int w)
	{
		if (!verPtr[v].firstArc)
			return false;

		auto dp = verPtr[v].firstArc;
		if (verPtr[v].firstArc->adjVex == w)
		{
			verPtr[v].firstArc = dp->nextArc;
			delete dp;

			return true;
		}
		else
		{
			ArcNode *beforDp = nullptr;
			while (dp && dp->adjVex != w)
			{
				beforDp = dp;
				dp = dp->nextArc;
			}

			if (!dp || !beforDp)
				return false;

			beforDp->nextArc = dp->nextArc;
			delete dp;

			return true;
		}

		return false;
	}

	//深度优先遍历算法
	template <typename T>
	void LinkGraph<T>::DFSTeraverse()
	{
		if (vexnum == 0)
			return;

		//初始化标记访问数组
		for (size_t i = 0; i < vexnum; ++i)
			visited[i] = false;

		cout << "深度优先遍历:" << endl;
		for (size_t i = 0; i < vexnum; ++i)
			if (!visited[i])
				DFS(vertices[i]);
	}

	//深度遍历
	template <typename T>
	void LinkGraph<T>::DFS(const VNode &v)
	{
		visited[LocateVex(v.data)] = true;
		cout << v.data << " ";

		for (auto w = FirstAdjVex(v); nullptr != w; w = NextAdjVex(v, *w))
		{
			int w1 = LocateVex(w->data);
			if (w1 != -1 && !visited[w1])
				DFS(*w);
		}
		
	}

	//广度优先遍历算法
	template <typename T>
	void LinkGraph<T>::BFSTeraverse()
	{
		if (vexnum == 0)
			return;

		//初始化标记访问数组
		for (size_t i = 0; i < vexnum; ++i)
			visited[i] = false;

		//初始化辅助队列
		while (!Queue.empty())
			Queue.pop();

		cout << "广度优先遍历:" << endl;
		for (size_t i = 0; i < vexnum; ++i)
		{
			if (!visited[i])
			{
				visited[i] = true;
				cout << vertices[i].data << " ";
				Queue.push(vertices[i]);

				while (!Queue.empty())
				{
					VNode v = Queue.front();
					Queue.pop();
					for (auto w = FirstAdjVex(v); nullptr != w; w = NextAdjVex(v, *w))
					{
						int w1 = LocateVex(w->data);
						if (w1 != -1 && !visited[w1])
						{
							visited[LocateVex(w->data)] = true;
							cout << w->data << " ";
							Queue.push(*w);
						}
					}
				}
			}
		}
	}

	//深度优先生成树(不能单独使用)
	template <typename T>
	void LinkGraph<T>::DFSTree(VNode v, TreeNode *T)
	{
		bool first = true;
		TreeNode *q = nullptr;

		for (auto w = FirstAdjVex(v); nullptr != w; w = NextAdjVex(v, *w))
		{
			int w1 = LocateVex(w->data);

			if (w1 != -1 && !visited[w1])
			{
				visited[w1] = true;
				TreeNode *p = (TreeNode*)malloc(sizeof(TreeNode));
				p->data = w->data;
				p->Child = p->Sibling = nullptr;

				if (first)
				{
					T->Child = p;
					first = false;
				}
				else
				{
					q->Sibling = p;
				}
				q = p;

				DFSTree(*w, p);
			}
		}
	}

	//深度优先生成森林(当图的连通分量数量为1时，生成的是树)
	template <typename T>
	void LinkGraph<T>::DFSForest(Tree &T)
	{
		if (vexnum == 0)
			return;

		if (T.root != nullptr)
			T.ClearTree();

		//初始化标记访问数组
		for (size_t i = 0; i < vexnum; ++i)
			visited[i] = false;

		TreeNode *q = nullptr;
		for (size_t i = 0; i < vexnum; ++i)
		{
			if (!visited[i])
			{
				visited[i] = true;
				TreeNode *p = (TreeNode*)malloc(sizeof(TreeNode));
				p->data = vertices[i].data;
				p->Child = p->Sibling = nullptr;

				if (!T.root)T.root = p;
				else
				{
					q->Sibling = p;
				}
				q = p;

				DFSTree(vertices[i], p);
			}
		}
	}

	//广度优先生成树(不能单独使用)
	template <typename T>
	void LinkGraph<T>::BFSTree(VNode v, TreeNode *T)
	{
		visited[LocateVex(v.data)] = true;
		Queue.push(v);

		Tree tree;
		tree.root = T;
		TreeNode *q = nullptr;
	

		while (!Queue.empty())
		{
			bool first = true;
			v = Queue.front();
			Queue.pop();
			TreeNode *k = tree.FindNode(v.data);

			for (auto w = FirstAdjVex(v); nullptr != w; w = NextAdjVex(v, *w))
			{
				int w1 = LocateVex(w->data);
				if (w1 != -1 && !visited[w1])
				{
					TreeNode *p = (TreeNode*)malloc(sizeof(TreeNode));
					p->data = w->data;
					p->Child = p->Sibling = nullptr;

					visited[LocateVex(w->data)] = true;
					Queue.push(*w);

					if (first)
					{
						k->Child = p;
						first = false;
					}
					else
					{
						q->Sibling = p;
					}
					q = p;
				}
			}
		}

		tree.root = nullptr;
	}

	//广度优先生成森林(当图的连通分量数量为1时，生成的是树)
	template <typename T>
	void LinkGraph<T>::BFSForest(Tree &T)
	{
		if (vexnum == 0)
			return;

		if (T.root != nullptr)
			T.ClearTree();

		//初始化标记访问数组
		for (size_t i = 0; i < vexnum; ++i)
			visited[i] = false;

		//初始化辅助队列
		while (!Queue.empty())
			Queue.pop();

		TreeNode *q = nullptr;
		for (size_t i = 0; i < vexnum; ++i)
		{
			if (!visited[i])
			{
				visited[i] = true;
				TreeNode *p = (TreeNode*)malloc(sizeof(TreeNode));
				p->data = vertices[i].data;
				p->Child = p->Sibling = nullptr;

				if (!T.root)T.root = p;
				else
				{
					q->Sibling = p;
				}
				q = p;

				BFSTree(vertices[i], p);
			}
		}
	}

	//最小生成树,普里姆(Prim)算法
	template <typename T>
	void LinkGraph<T>::Prim(Tree &T, const VertecType &v)
	{
		//前提无向连通网
		if (type != NDNet)
			return;

		if (vexnum == 0)
			return;

		cout << "Prim:" << endl;

		if (T.root != nullptr)
			T.ClearTree();

		TreeNode *p = (TreeNode*)malloc(sizeof(TreeNode));
		*p = { v, nullptr, nullptr };
		T.root = p;

		//辅助结构(记录从顶点集U到V-U的代价最小的边)
		struct _Type
		{
			VertecType adjVex;
			int lowcost;
		}closedge[MAXSIZE];

		int k = LocateVex(v);

		//辅助数组初始化
		for (size_t i = 0; i < vexnum; ++i)
			if (i != k)closedge[i] = { v, GetWeight(GetVex(i).data, v) };

		closedge[k].lowcost = 0; //初始化U
		for (size_t i = 1; i < vexnum; ++i)
		{
			int min = INFINITE;
			//找出权值最小的边,并记录该顶点的下标
			for (size_t j = 0; j < vexnum; ++j)
				if (closedge[j].lowcost != 0 && closedge[j].lowcost < min)
				{
					min = closedge[j].lowcost;
					k = j;
				}

			cout << closedge[k].adjVex << "---" << GetVex(k).data << endl;
			//生成树结点，并入树
			p = (TreeNode*)malloc(sizeof(TreeNode));
			*p = { GetVex(k).data, nullptr, nullptr };
			TreeNode *q = T.FindNode(closedge[k].adjVex);
			if (q->Child == nullptr)
				q->Child = p;
			else
			{
				q = q->Child;
				while (q->Sibling != nullptr)
					q = q->Sibling;

				q->Sibling = p;
			}

			closedge[k].lowcost = 0; //并入U

			//更新到各顶点的权值，和所对应的顶点
			for (size_t m = 0; m < vexnum; m++)
			{
				VertecType vk = GetVex(k).data;
				VertecType vm = GetVex(m).data;

				if (GetWeight(vk, vm) < closedge[m].lowcost)
				{
					closedge[m].adjVex = vk;
					closedge[m].lowcost = GetWeight(vk, vm);
				}
			}
		}
	}

	//最小生成树,克鲁斯卡尔(Kruskal)算法
	template <typename T>
	void LinkGraph<T>::Kruskal(Tree &T)
	{
		//前提无向连通网
		if (type != NDNet)
			return;

		if (vexnum == 0)
			return;

		cout << "Kruskal:" << endl;

		if (T.root != nullptr)
			T.ClearTree();

		typedef std::vector<VNode> vec_VNode; //连通分量
		std::vector<vec_VNode> V;             //连通分量集合
		struct Arc
		{
			int fAdjvex, sAdjvex; //该边附着的顶点
			int weight;           //权值
		};
		std::vector<Arc> Arcs;                //边集合

		//初始化连通分量集(初始每个顶点各存放在不同的连通分量)
		for (size_t i = 0; i < vexnum; ++i)
		{
			vec_VNode temp;
			temp.push_back(vertices[i]);
			V.push_back(temp);
		}

		//初始化边集合
		for (size_t i = 0; i < vexnum; i++)
		{
			VNode v = GetVex(i);
			for (auto w = FirstAdjVex(v); nullptr != w; w = NextAdjVex(v, *w))
			{
				int w1 = LocateVex(w->data);
				if (w1 > (int)i) //防止重复加入相同的边
				{
					Arc temp{ (int)i, w1, GetWeight(v.data, w->data) };
					Arcs.push_back(temp);
				}
			}
		}

		//排序边集合，权值(小-->大)
		std::sort(Arcs.begin(), Arcs.end(),
			[](const Arc &lhs, const Arc &rhs) {return lhs.weight < rhs.weight; });

		size_t n = 0;
		while ((int)V.size() != 1 && n < Arcs.size())
		{
			Arc arcTemp = Arcs[n++];

			//找出附着在弧上的两个顶点所在的连通分量下标
			int a = 0, b = 0; 
			int k = 0; //当前连通分量下标
			for (const auto &vec_v : V) //对于每一个连通分量
			{
				for (const auto &v : vec_v) //对于每一个顶点
				{
					if (v.data == GetVex(arcTemp.fAdjvex).data)
						a = k;

					if (v.data == GetVex(arcTemp.sAdjvex).data)
						b = k;
				}
				++k;
			}

			//生成树顶点 & 合并连通分量
			if (a != b)//如果两个顶点不在同一个联通分量
			{
				VNode va = GetVex(arcTemp.fAdjvex);
				VNode vb = GetVex(arcTemp.sAdjvex);

				//生成树结点
				cout << va.data << "-->" << vb.data << endl;


				//合并
				V[a].insert(V[a].end(), V[b].begin(), V[b].end()); //在连通分量V[a]的后面插入V[b]

				//更新连通分量集V
				V.erase(V.begin() + b); //删除连通分量V[b]
			}
		}
	}

	//获取拓扑排序后的顶点序列
	template <typename T>
	std::queue<typename LinkGraph<T>::VertecType> LinkGraph<T>::GetAOV()
	{
		std::queue<VertecType> AOV;
		LinkGraph<T> lg = *this;     //克隆本图，保证算法执行后不会改变原来的图

		//前提有向无环图(网)
		if (type != DG && type != DNet)
			return AOV;

		size_t vexnumTemp = vexnum;
		for (size_t i = 0; i < vexnumTemp; ++i)
		{
			int n = -1;
			for (size_t j = 0; j < vexnum; ++j)
			{
				ArcNode *dptr = reVertices[j].firstArc;
				if (dptr == nullptr)
				{
					n = j;
					break;
				}
			}
			if (n != -1)
			{
				AOV.push(GetVex(n).data);
				DeleteVex(GetVex(n).data);
			}
			else
				break;
		}

		*this = lg;
		return AOV;
	}

	//获取关键路径
	template <typename T>
	std::queue<typename LinkGraph<T>::VertecType> LinkGraph<T>::GetAOE()
	{
		//前提有且只有一个源点和一个汇点的有向网

		std::queue<VertecType> AOE;
		auto aov = GetAOV();
		decltype(GetAOV()) aovTemp;
		std::stack<VertecType> aovRet; //反转的aov, 用于求最晚开始时间
		int est[MAXSIZE];              //保存顶点的最早开始时间(earliest start time)
		int lst[MAXSIZE];              //保存顶点的最晚开始时间(Latest start time)

		//初始化
		std::memset(est, 0, sizeof(est));
		//std::memset(lst, 0, sizeof(lst));

		//反向aov
		aovTemp = aov;
		while (!aovTemp.empty())
		{
			aovRet.push(aovTemp.front());
			aovTemp.pop();
		}

		//寻找最早开始时间
		aovTemp = aov;
		aovTemp.pop();
		for (size_t i = 1; i < vexnum; ++i)
		{
			VertecType v = aovTemp.front();
			int v1 = LocateVex(v);
			aovTemp.pop();

			//对于每一个顶点v，寻找指向该顶的顶点w{属于vexs}，并把est[v] = max {w + <w, v>} <w, v>是w-->v 的权值//寻找v顶点的入度，
			ArcNode *p = reVertices[v1].firstArc;
			while (p)
			{
				size_t k;
				auto aovTemp2 = aov;
				//寻找w在aov中的位置
				for (k = 0; k < vexnum; ++k)
				{
					if (aovTemp2.front() == vertices[p->adjVex].data)
						break;

					aovTemp2.pop();
				}

				if (est[i] < est[k] + p->weight)
					est[i] = est[k] + p->weight;

				p = p->nextArc;
			}
		}

		//寻找最晚开始时间
		for (size_t i = 0; i < vexnum; ++i)
			lst[i] = est[vexnum - 1];

		aovRet.pop();
		lst[0] = 0;
		for (size_t i = vexnum - 2; i > 0; --i)
		{
			VertecType v = aovRet.top();
			int v1 = LocateVex(v);
			aovRet.pop();

			//对于每一个顶点v，寻找该顶点指向的顶点w，并把lst[v] = min {w - <w, v>} <w, v>是v-->w 的权值
			ArcNode *p = vertices[v1].firstArc;
			while (p)
			{
				size_t k;
				aovTemp = aov;
				for (k = 0; k < vexnum; ++k)
				{
					if (aovTemp.front() == vertices[p->adjVex].data)
						break;

					aovTemp.pop();
				}

				if (lst[i] > lst[k] - p->weight)
					lst[i] = lst[k] - p->weight;

				p = p->nextArc;
			}
		}

		//最早开始时间等于最晚开始时间是关键路径上的顶点
		for (size_t i = 0; i < vexnum; ++i)
		{
			if (est[i] == lst[i])
				AOE.push(aov.front());

			aov.pop();
		}
		
		return AOE;
	}

	//单源点到各顶点最短路径，迪杰斯特拉(Dijkstra)算法
	template <typename T>
	void LinkGraph<T>::Dijkstra(VertecType v, int **dt, int **pre)
	{
		bool *S = new bool[vexnum];   //标记已经求得的最短路径顶点集合
		*dt      = new int[vexnum];   //v到各顶点的权值集合
		*pre     = new int[vexnum];   //路径的索引集合, 保存指向该顶点的上一个顶点，如a->c->b，则 pre[b] = c, pre[c] = a

		int v1 = LocateVex(v);
		if (v1 == -1)
			return;

		//初始化
		for (size_t i = 0; i < vexnum; ++i)
		{
			S[i] = false;
			(*pre)[i] = -1;
		}
		S[v1] = true;  //v并入S集合

		//初始化dt为v到其它各顶点w(vex - S)的权值，若有弧<v,w>,则pre[w] = v
		for (size_t i = 0; i < vexnum; ++i)
		{
			if (!S[i]) //在S集合外查找
			{
				(*dt)[i] = GetWeight(v, vertices[i].data);

				if ((*dt)[i] != INFINITE)
					(*pre)[i] = v1;
			}
		}

		for (size_t i = 0; i < vexnum - 1; ++i)
		{
			//寻找v到各顶点权值最小的顶点w，w并人S
			int min = INFINITE;
			int w = -1;
			for (size_t j = 0; j < vexnum; ++j)
			{
				if (!S[j] && (*dt)[j] < min)
				{
					w = j;
					min = (*dt)[j];
				}
			}
			//找不到
			if (w == -1)
				continue;
			S[w] = true; //w并入S

			//计算w到其它顶点x(vex - S)的权值，如果dt[w] + weight<w, x> 小于 dt[x], 替换 dt,和pre
			for (size_t j = 0; j < vexnum; ++j)
			{
				if (!S[j])
				{
					int weigth = GetWeight(GetVex(w).data, GetVex(j).data);
					if (weigth != INFINITE && weigth + (*dt)[w] < (*dt)[j])
					{
						(*dt)[j] = weigth + (*dt)[w];
						(*pre)[j] = w;
					}
				}
			}
		}

		delete S;
	}

}
