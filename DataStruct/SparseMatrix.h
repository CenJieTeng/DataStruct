//项目：稀疏矩阵的压缩储存
//创建时间：2018/11/25 20:15
//完成时间：
//最后一次修改时间：
//修改次数：
//修改原因：
//
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include <vector>
#define MAXSIZE 100

typedef int DataType;
struct Triple
{
	int i;
	int j;
	DataType e;
};

class SMatrix
{
public:
	SMatrix();
	~SMatrix();

public:
	void CreateSMatrixFromTXT(const char *c_str);
	void PrintSMatrix() const;
	void CopySMatrix(const SMatrix &sm);
	void AddSMatrix(const SMatrix &sm1, const SMatrix &sm2);
	void SubtSMatrix(const SMatrix &sm1, const SMatrix &sm2);
	void MultSMatrix(const SMatrix &sm1, const SMatrix &sm2);
	void TransposeSMatrix(const SMatrix &sm);
	void FastTransposeSMatrix(const SMatrix &sm);

private:
	Triple data[MAXSIZE];
	int mu;
	int nu;
	int tu;
};

#endif // !SPARSEMATRIX_H
