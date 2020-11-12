#include "MGraph.h"

using std::cout; using std::cin; using std::endl;

#define D_ARC_MAXNUM(v) v * (v - 1)       //有向图(网)的最大弧数，v 是顶点数
#define ND_ARC_MAXNUM(v) v * (v - 1) / 2  //无向图(网)的最大弧数，v 是顶点数
bool MGraph::visited[MAXSIZE];
std::queue<VertecType> MGraph::Queue;

MGraph::MGraph() : vexs{ -1 }, AdjMatrix{ 0 }, vexnum(0), arcnum(0), type(NDG)
{
	if (type == DNet || type == NDNet)
		for (int i = 0; i < MAXSIZE; ++i)
			for (int j = 0; j < MAXSIZE; ++j)
				AdjMatrix[i][j] = INFINITE;        //INFINITE表示无穷
}

MGraph::~MGraph()
{
}

bool MGraph::CreateGraph()
{
	cout << "0有向图，1无向图，2有向网，3无向网" << endl;
	cout << "输入你要创建的图的类型 ";
	int i;
	cin >> i;
	switch (i)
	{
	case DG : type = DG; break;
	case NDG : type = NDG; break;
	case DNet: type = DNet; break;
	case NDNet : type = NDNet; break;
	default:
		return false;
	}

	cout << "请输入顶点数，弧(边)数，空格分隔，下同";
	cin >> vexnum >> arcnum;

	switch (type)
	{
	case DG :
	case DNet :
		if (vexnum > MAXSIZE || arcnum > D_ARC_MAXNUM(vexnum))
		{
			cout << "创建失败" << endl;
			*this = MGraph();            //创建失败，把图置于初始状态

			return false;
		}break;

	case NDG :
	case NDNet :
		if (vexnum > MAXSIZE || arcnum > ND_ARC_MAXNUM(vexnum))
		{
			cout << "创建失败" << endl;
			*this = MGraph();            //创建失败，把图置于初始状态

			return false;
		}break;
	}

	cout << "输入" << vexnum << "个顶点的值(1个VertecType) " << endl;
	for (size_t i = 0; i < vexnum; ++i)
		cin >> vexs[i];


	switch (type)
	{
	case DG :
	case NDG :
		cout << "输入" << arcnum << "条弧(边)的弧尾，弧头" << endl;
		for (size_t i = 0; i < arcnum; ++i)
		{
			cout << "第" << i + 1 << "条 ";
			VertecType v1, v2;
			cin >> v1 >> v2;

			int m = LocateVex(v1);
			int n = LocateVex(v2);
			//没有找到要创建边的顶点
			if (m == -1 || n == -1)
				continue;

			AdjMatrix[m][n] = 1;
			if (type == NDG)
				AdjMatrix[n][m] = 1;
		}break;
	case DNet :
	case NDNet :
		cout << "输入" << arcnum << "条弧(边)的弧尾，弧头, 权值" << endl;
		for (size_t i = 0; i < arcnum; ++i)
		{
			cout << "第" << i + 1 << "条 ";
			VertecType v1, v2;
			size_t w;
			cin >> v1 >> v2 >> w;

			int m = LocateVex(v1);
			int n = LocateVex(v2);
			//没有找到要创建边的顶点
			if (m == -1 || n == -1)
				continue;

			AdjMatrix[m][n] = w;
			if (type == NDNet)
				AdjMatrix[n][m] = w;
		}break;
	}

	return true;
}

void MGraph::DisPlayGraph()const
{

	cout << "图:" << endl;
	cout << "顶点数 " << vexnum << ",弧(边)数 " << arcnum << endl;

	for (size_t i = 0; i < vexnum; ++i)
		cout << "vexs[" << i << "]=" << vexs[i] << endl;

	for (size_t i = 0; i < vexnum; ++i)
	{
		for (size_t j = 0; j < vexnum; ++j)
			if (AdjMatrix[i][j] == INFINITE)
				cout << "INFINITE" << "\t";
			else
				cout << AdjMatrix[i][j] << "\t\t";
		cout << endl << endl;
	}
}

int MGraph::LocateVex(const VertecType &val)const
{
	//若图中存在于val相等的顶点，返回在图中位置，否则返回-1

	for (size_t i = 0; i < vexnum; ++i)
		if (vexs[i] == val)
			return i;

	return -1;
}

VertecType& MGraph::GetVex(int v)
{
	if (v < 0 || (size_t)v >= vexnum)
		exit(-1);

	return vexs[v];
}

size_t MGraph::size()
{
	return vexnum;
}

VertecType MGraph::FirstAdjVex(VertecType v)
{
	int v1 = LocateVex(v);
	if (v1 == -1)
		return -1;

	int k = 0;
	if (type == DNet || type == NDNet)
		k = INFINITE;

	for (size_t i = 0; i < vexnum; ++i)
		if (AdjMatrix[v1][i] != k)
			return vexs[i];

	return -1;
}

VertecType MGraph::NextAdjVex(VertecType v, VertecType w)
{
	int v1 = LocateVex(v);
	int w1 = LocateVex(w);

	if (v1 == -1 || w1 == -1)
		return -1;

	int k = 0;
	if (type == DNet || type == NDNet)
		k = INFINITE;

	for (int i = w1 + 1; (size_t)i < vexnum; ++i)
		if (AdjMatrix[v1][i] != k)
			return vexs[i];

	return -1;
}

void MGraph::InsertVex(const VertecType &v)
{
	if (vexnum == MAXSIZE)
	{
		cout << "图满，插入失败" << endl;
		return;
	}

	vexs[vexnum++] = v;
}

void MGraph::DeleteVex(VertecType &v)
{
	size_t v1 = 0;
	v1 = LocateVex(v);
	if (v1 == -1)
		return;

	//n代表有多少个临接点
	size_t n = 0;
	for (VertecType w = FirstAdjVex(v); w >= 0; w = NextAdjVex(v, w))
		++n;

	for (size_t i = 0; i < vexnum; ++i)
		for (size_t j = v1 + 1; j < vexnum; ++j)
			AdjMatrix[i][j - 1] = AdjMatrix[i][j];

	for (size_t i = v1 + 1; i < vexnum; ++i)
		for (size_t j = 0; j < vexnum; ++j)
			AdjMatrix[i - 1][j] = AdjMatrix[i][j];

	for (size_t i = 0; i < vexnum; ++i)
	{
		AdjMatrix[i][vexnum - 1] = 0;
		AdjMatrix[vexnum - 1][i] = 0;
	}

	for (size_t i = v1; i < vexnum - 1; ++i)
		vexs[i] = vexs[i + 1];

	--vexnum;
	arcnum -= n;
}

void MGraph::InsertEdge(const VertecType &v, const VertecType &w)
{
	int v1 = LocateVex(v);
	int w1 = LocateVex(w);

	if (v1 == -1 || w1 == -1)
	{
		cout << "添加失败" << endl;
		return;
	}

	int k = 1;
	if (type == DNet || type == NDNet)
	{
		cout << "输入弧(边)的权值,范围[1,INFINITE) ";
		cin >> k;
		k %= INFINITE;
	}

	AdjMatrix[v1][w1] = k;
	if (type == NDG || type == NDNet)
		AdjMatrix[w1][v1] = k;
	arcnum += 1;
}

void MGraph::DeleteEdge(VertecType &v, VertecType &w)
{
	int v1 = LocateVex(v);
	int w1 = LocateVex(w);

	if (v1 == -1 || w1 == -1)
	{
		cout << "删除失败" << endl;
		return;
	}

	int k = 0;
	if (type == DNet || type == NDNet)
		k = INFINITE;

	AdjMatrix[v1][w1] = k;
	if (type == NDG || type == NDNet)
		AdjMatrix[w1][v1] = k;
}

void MGraph::DFSTeraverse()
{
	//初始化访问标记数组
	for (size_t i = 0; i < vexnum; ++i)
		visited[i] = false;
	
	cout << "深度优先遍历:" << endl;
	for (size_t i = 0; i < vexnum; ++i)
		if (!visited[i])
			DFS(vexs[i]);
}

void MGraph::BFSTeraverse()
{
	//初始化访问标记数组
	for (size_t i = 0; i < vexnum; ++i)
		visited[i] = false;

	//初始化辅助队列
	while (!Queue.empty())
		Queue.pop();

	cout << "广度优先遍历" << endl;
	for (size_t i = 0; i < vexnum; ++i)
	{
		if (!visited[i])
		{
			visited[i] = true;
			cout << vexs[i] << " ";
			Queue.push(vexs[i]);

			while (!Queue.empty())
			{
				auto v = Queue.front();
				Queue.pop();
				for (VertecType w = FirstAdjVex(v); w >= 0; w = NextAdjVex(v, w))
				{
					int w1 = LocateVex(w);
					if (w1 != -1 && !visited[w1])
					{
						visited[w1] = true;
						cout << vexs[w1] << " ";
						Queue.push(w);
					}
				}
			}
		}
	}
}

//深度优先生成树
void MGraph::DFSTree(VertecType v, TreeNode *T)
{
	int v1 = LocateVex(v);
	visited[v1] = true; bool first = true;
	TreeNode *q = nullptr;

	for (VertecType w = FirstAdjVex(v); w >= 0; w = NextAdjVex(v, w))
	{
		if (!visited[LocateVex(w)])
		{
			TreeNode *p = (TreeNode*)malloc(sizeof(TreeNode));
			*p = { w, nullptr, nullptr };
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
			DFSTree(w, p);
		}
	}
}

//深度优先生成森林
void MGraph::DFSForest(Tree &T)
{
	if (T.root != nullptr)
		T.ClearTree();

	for (size_t i = 0; i < vexnum; i++)
		visited[i] = false;

	TreeNode *q = nullptr;
	for (size_t i = 0; i < vexnum; i++)
	{
		if (!visited[i])
		{
			TreeNode *p = (TreeNode*)malloc(sizeof(TreeNode));
			*p = { GetVex(i), nullptr, nullptr };

			if (!T.root)T.root = p;
			else
				q->Sibling = p;
			q = p;
			DFSTree(GetVex(i), p);
		}
	}
}

//广度优先生成树
void MGraph::BFSTree(VertecType v, TreeNode *T)
{
	int v1 = LocateVex(v);
	visited[v1] = true; 
	Queue.push(v);

	Tree tree;
	tree.root = T;
	TreeNode *q = nullptr;

	while (!Queue.empty())
	{
		bool first = true;
		v = Queue.front();
		Queue.pop();
		TreeNode *k = tree.FindNode(v);

		for (VertecType w = FirstAdjVex(v); w >= 0; w = NextAdjVex(v, w))
		{
			if (!visited[LocateVex(w)])
			{
				visited[LocateVex(w)] = true;
				Queue.push(w);
				TreeNode *p = (TreeNode*)malloc(sizeof(TreeNode));
				*p = { w, nullptr, nullptr };

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

//广度优先生成森林
void MGraph::BFSForest(Tree &T)
{
	if (T.root != nullptr)
		T.ClearTree();

	for (size_t i = 0; i < vexnum; i++)
		visited[i] = false;

	while (!Queue.empty())
	{
		Queue.pop();
	}

	TreeNode *q = nullptr;
	for (size_t i = 0; i < vexnum; i++)
	{
		if (!visited[i])
		{
			TreeNode *p = (TreeNode*)malloc(sizeof(TreeNode));
			*p = { GetVex(i), nullptr, nullptr };

			if (!T.root)T.root = p;
			else
				q->Sibling = p;

			q = p;
			BFSTree(GetVex(i), p);
		}
	}
}

void MGraph::Prim()
{
	//前提无向连通网

	std::vector<VertecType>U;//生成树顶点集合
	std::vector<VertecType>V;//剩余顶点集合（vexnum - U.size())
	int Tree[MAXSIZE][MAXSIZE];

	//初始化
	U.push_back(vexs[0]); //U = { v0 };
	for (size_t i = 0; i < vexnum; i++)
		V.push_back(vexs[i]);
	V.erase(V.begin());   //V = { vexs - U };

	for (int i = 0; i < MAXSIZE; ++i)
		for (int j = 0; j < MAXSIZE; j++)
			Tree[i][j] = INFINITE;

	//算法开始
	while (U.size() < vexnum)
	{
		int minWeight = INFINITE;
		int line = 0, eac = 0;
		for (auto u : U)
		{
			for (auto v : V)
			{
				auto uCur = LocateVex(u);
				auto vCur = LocateVex(v);
				if (minWeight > AdjMatrix[uCur][vCur])
				{
					minWeight = AdjMatrix[uCur][vCur];
					line = uCur;
					eac = vCur;
				}
			}
		}

		Tree[line][eac] = minWeight;
		Tree[eac][line] = minWeight;
		U.emplace_back(vexs[eac]);
		for (auto b = V.begin(); b != V.end(); b++)
			if (*b == vexs[eac])
			{
				V.erase(b);
				break;
			}
	}

	cout << "Prim算法:" << endl;
	for (size_t i = 0; i < vexnum; ++i)
	{
		for (size_t j = 0; j < vexnum; ++j)
			if (Tree[i][j] == INFINITE)
				cout << "INFINITE" << "\t";
			else
				cout << Tree[i][j] << "\t\t";
		cout << endl;
	}
}

void MGraph::Kruskal()
{
	//前提无向连通网
	typedef std::vector<VertecType> vec_verType;

	std::vector<vec_verType> equKind; //等价类集合
	Arcs arcs;                        //边集合
	int Tree[MAXSIZE][MAXSIZE];

	//初始化
	for (size_t i = 0; i < vexnum; ++i)
	{
		vec_verType temp = { vexs[i] };
		equKind.push_back(temp);
	}

	size_t n = 0;
	for (size_t i = 0; i < vexnum; i++)
	{
		for (int w = FirstAdjVex(vexs[i]); w >= 0; w = NextAdjVex(vexs[i], vexs[w]))
		{
			arcs[n].arch = vexs[i];
			arcs[n].arct = vexs[w];
			arcs[n].weight = AdjMatrix[i][w];
			++n;
		}
	}

	//排序边集合，权值(小-->大)
	std::sort(std::begin(arcs), std::begin(arcs) + n, 
		[](const Arc &rhs, const Arc &lhs) { return rhs.weight < lhs.weight; });

	for (int i = 0; i < MAXSIZE; ++i)
		for (int j = 0; j < MAXSIZE; j++)
			Tree[i][j] = INFINITE;

	//算法开始
	 for (size_t i = 0; i < n; ++i)
	 {
		 if (equKind.size() == 1)
			 break;

		 vec_verType a, b;
		 for (const auto &e : equKind)
		 {
			 for (const auto &v : e)
			 {
				 if (v == arcs[i].arch)
					 a = e;
				 if (v == arcs[i].arct)
					 b = e;
			 }
		 }
		 if (a != b)
		 {
			 auto lv1 = LocateVex(arcs[i].arch);
			 auto lv2 = LocateVex(arcs[i].arct);
			 Tree[lv1][lv2] = arcs[i].weight;
			 Tree[lv2][lv1] = arcs[i].weight;

			 for (auto beg = equKind.begin(); beg != equKind.end(); ++beg)
			 {
				 if (a == *beg)
					 beg->insert(beg->end(), b.begin(), b.end());

				 if (b == *beg)
					 beg = equKind.erase(beg);

				 if (beg == equKind.end())
					 break;
			 }
		 } 
	 }

	 cout << "Kruskal算法:" << endl;
	 for (size_t i = 0; i < vexnum; ++i)
	 {
		 for (size_t j = 0; j < vexnum; ++j)
			 if (Tree[i][j] == INFINITE)
				 cout << "INFINITE" << "\t";
			 else
				 cout << Tree[i][j] << "\t\t";
		 cout << endl;
	 }
}

std::queue<VertecType> MGraph::GetAOV()
{
	std::queue<VertecType> AOV;
	bool NotInEdge;       //没有入度
	MGraph mg = *this;    //克隆本图，保证算法执行后不会改变原来的图

	int k = 1;
	if (type == DNet)
		k = INFINITE;

	size_t i = 0;
	while (vexnum > 0)
	{
		NotInEdge = true;

		if (type == DG)
			for (size_t j = 0; j < vexnum; ++j)
				if (AdjMatrix[j][LocateVex(vexs[i])] == k)
				{
					NotInEdge = false;
					break;
				}
		if (type == DNet)
			for (size_t j = 0; j < vexnum; ++j)
				if (AdjMatrix[j][LocateVex(vexs[i])] != k)
				{
					NotInEdge = false;
					break;
				}

		if (NotInEdge == true)
		{
			AOV.push(vexs[i]);
			DeleteVex(vexs[i]);
			i = 0;
		}
		else
			++i;
	}

	*this = mg;

	return AOV;
 }

std::queue<VertecType> MGraph::GetAOE()
{
	//前提有向网，并且有且仅有一个源点和汇点

	std::queue<VertecType> AOE;
	auto aov = GetAOV();
	auto aov2 = aov;
	auto aov3 = aov;
	std::stack<VertecType> aovRet; //反转的aov, 用于求最晚开始时间
	int est[MAXSIZE];              //保存顶点的最早开始时间(earliest start time)
	int lst[MAXSIZE];              //保存顶点的最晚开始时间(Latest start time)

	//初始化
	std::memset(est, 0, sizeof(est));
	std::memset(lst, 0, sizeof(lst));

	//初始化aovRet
	while (aov2.size() != 0)
	{
		aovRet.push(aov2.front());
		aov2.pop();
	}

	//寻找最早开始时间
	aov.pop();
	for (size_t i = 1; i < vexnum; ++i)
	{
		auto v = aov.front();
		auto v1 = LocateVex(v);
		aov.pop();

		//对于每一个顶点v，寻找指向该顶的顶点w{属于vexs}，并把est[v] = max {w + <w, v>} <w, v>是w-->v 的权值
		for (size_t j = 0; j < vexnum; ++j)
		{
			auto v2 = est[j];
			if (AdjMatrix[j][v1] != INFINITE && est[i] < v2 + AdjMatrix[j][v1])
				est[i] = v2 + AdjMatrix[j][v1];
		}
	}

	//寻找最晚开始时间
	aovRet.pop();
	lst[vexnum - 1] = est[vexnum - 1];
	for (size_t i = vexnum - 2; i > 0; --i)
	{
		auto v = aovRet.top();
		auto v1 = LocateVex(v);
		lst[i] = INFINITE;
		aovRet.pop();

		//对于每一个顶点v，寻找该顶点指向的顶点w，并把lst[v] = min {w - <w, v>} <w, v>是v-->w 的权值
		for (size_t j = 0; j < vexnum; ++j)
		{
			if (AdjMatrix[v1][j] == INFINITE)
				continue;

			auto aovTemp = aov3;
			size_t k; //找到顶点w在aov中的位置
			for (k = 0; k < vexnum; ++k)
			{
				if (vexs[j] == aovTemp.front())
					break;
				aovTemp.pop();
			}
			if (lst[i] > lst[k] - AdjMatrix[v1][j])
				lst[i] = lst[k] - AdjMatrix[v1][j];
		}
	}

	//est == lst即为关键路径上的顶点
	for (size_t i = 0; i < vexnum; ++i)
	{
		if (est[i] == lst[i])
			AOE.push(aov3.front());
		aov3.pop();
	}

	return AOE;
}

void MGraph::Dijkstra(VertecType v, int dt[], int pre[])
{
	bool *S = new bool[vexnum]; //最短路径顶点集合
	int n = LocateVex(v);

	if (n == -1)
		return;

	//初始化
	for (size_t i = 0; i < vexnum; ++i)
	{
		dt[i] = AdjMatrix[n][i];
		S[i] = false;

		if (dt[i] < INFINITE)
			pre[i] = n;
		else
			pre[i] = -1;
	}

	S[n] = true;
	for (size_t i = 0; i < vexnum - 1; ++i)
	{
		int min = INFINITE;
		size_t u = n;
		for (size_t j = 0; j < vexnum; ++j)
		{
			if (!S[j] && dt[j] < min)
			{
				min = dt[j];
				u = j;
			}
		}

		S[u] = true;
		for (size_t k = 0; k < vexnum; ++k)
		{
			int w = AdjMatrix[u][k];
			if (!S[k] && w < INFINITE && dt[u] + w < dt[k])
			{
				dt[k] = dt[u] + w;
				pre[k] = u;
			}
		}
	}

	delete S;
}

void MGraph::DFS(VertecType v)
{
	visited[LocateVex(v)] = true;
	cout << v << " ";

	for (VertecType w = FirstAdjVex(v); w >= 0; w = NextAdjVex(v, w))
	{
		int w1 = LocateVex(w);
		if (w1 != -1 &&!visited[w1])
			DFS(w);
	}
}
