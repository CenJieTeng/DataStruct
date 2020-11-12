#include "SparseMatrix.h"

using std::cout; using std::cin; using std::endl; using std::vector;

SMatrix::SMatrix() : mu(0), nu(0), tu(0)
{
	memset(data, 0, sizeof(data));
}

SMatrix::~SMatrix()
{
}

void SMatrix::CreateSMatrixFromTXT(const char *c_str)
{
	std::ifstream inputFile(c_str);

	if (inputFile)
	{
		inputFile >> mu >> nu;
		int k = 0;
		int value = 0;
		for (int i = 0; i < mu; i++)
		{
			for (int j = 0; j < nu; j++)
			{
				inputFile >> value;
				if (value != 0)
				{
					data[k].i = i;
					data[k].j = j;
					data[k].e = value;
					k++;
				}
			}
		}
		tu = k;
	}
}

void SMatrix::PrintSMatrix() const
{
	if (tu != 0)
	{
		cout << "i j e" << endl;
		for (int i = 0; i < tu; i++)
		{
			cout << data[i].i << " " << data[i].j << " " << data[i].e << endl;
		}
		cout << "row=" << mu << " " << "col=" << nu << endl;
		cout << "not zero count is " << tu << endl;
	}
}

void SMatrix::CopySMatrix(const SMatrix &sm)
{
	mu = sm.mu;
	nu = sm.nu;
	tu = sm.tu;

	for (int i = 0; i < sm.tu; i++)
	{
		data[i].i = sm.data[i].i;
		data[i].j = sm.data[i].j;
		data[i].e = sm.data[i].e;
	}
}

void SMatrix::AddSMatrix(const SMatrix &sm1, const SMatrix &sm2)
{
	if (sm1.mu != sm2.mu || sm1.nu != sm2.nu)
		return;

	mu = sm1.mu;
	nu = sm1.nu;

	int k = 0;
	//找相同
	for (int i = 0; i < sm1.tu; i++)
	{
		data[k].i = sm1.data[i].i;
		data[k].j = sm1.data[i].j;

		for (int j = 0; j < sm2.tu; j++)
		{
			if (sm1.data[i].i == sm2.data[j].i
				&& sm1.data[i].j == sm2.data[j].j)
			{
				data[k].e = sm1.data[i].e + sm2.data[j].e;
				break;
			}
			else if (j == (sm2.tu - 1))
				data[k].e = sm1.data[i].e;
		}
		k++;
	}

	//找不同
	for (int i = 0; i < sm2.tu; i++)
	{
		for (int j = 0; j < sm1.tu; j++)
		{
			if (sm2.data[i].i == sm1.data[j].i
				&& sm2.data[i].j == sm1.data[j].j)
				break;
			else if (j == (sm2.tu - 1))
			{
				data[k].i = sm2.data[i].i;
				data[k].j = sm2.data[i].j;
				data[k].e = sm2.data[i].e;
				k++;
			}
		}
	}

	//排序
	std::sort(std::begin(data), std::begin(data) + k,
		[](const Triple &t1, const Triple &t2) ->bool
	{
		if (t1.i != t2.i)
			return t1.i < t2.i;
		else
			return t1.j < t2.j;
	}
	);

	tu = k;
}

//void SubtSMatrix(const SMatrix &sm1, const SMatrix &sm2);
//void MultSMatrix(const SMatrix &sm1, const SMatrix &sm2);

void SMatrix::TransposeSMatrix(const SMatrix &sm)
{
	mu = sm.nu;
	nu = sm.mu;
	tu = sm.tu;

	if (sm.tu != 0)
	{
		int k = 0;
		for (int i = 0; i < sm.nu; i++)
		{
			for (int j = 0; j < sm.tu; j++)
			{
				if (sm.data[j].j == i)
				{
					data[k].i = sm.data[j].j;
					data[k].j = sm.data[j].i;
					data[k].e = sm.data[j].e;
					k++;
				}
			}
		}
	}
}

void SMatrix::FastTransposeSMatrix(const SMatrix &sm)
{
	mu = sm.nu;
	nu = sm.mu;
	tu = sm.tu;

	if (sm.tu != 0)
	{
		vector<int> num(sm.nu, 0);  //每列非零元素的个数
		vector<int> cpot(sm.nu, 0); //第n列第一个非零元素所在的位置

		for (int i = 0; i < sm.tu; i++) 
			++num[sm.data[i].j];
		
		cpot[0] = 0;


		for (int i = 1; i < sm.nu; i++)
			cpot[i] = cpot[i - 1] + num[i - 1];

		for (int i = 0; i < sm.tu; i++)
		{
			int col = sm.data[i].j;

			data[cpot[col]].i = sm.data[i].j;
			data[cpot[col]].j = sm.data[i].i;
			data[cpot[col]].e = sm.data[i].e;
			cpot[col]++;
		}
	}
}
