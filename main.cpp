#include <stdio.h>
#include <windows.h>
#include<iostream>
#include <iomanip>
#include<fstream> 
#include <string.h>
#include <stdlib.h>
#include <conio.h>
using namespace std;

#define MAXVEX 13     //最大顶点个数 
#define INFINITY 3276//若没有通路，记为INFINITY = 32762
int PathMatirx[MAXVEX][MAXVEX];
int ShortPath[MAXVEX][MAXVEX];

//景点结构体
typedef struct {
	int Num;//编号
	string name;       //景点名
	string info;    //简介
}VextexType;

//邻接矩阵
typedef struct {
	int AdjMatrix[MAXVEX][MAXVEX]; //二维数组存放
	VextexType vex[MAXVEX];    //顶点信息
	int vexnum;		//顶点数 
	int arcnum;     //边数 
}MGraph;



void InitGraph(MGraph& G) {
	int i = 0, j = 0;
	G.vexnum = 13;
	G.arcnum = 19;
	for (int i = 0; i < 13; i++) {
		G.vex[i].Num = i + 1;//第1号景点到第13号景点
	}
	G.vex[0].name = "孙中山像";
	G.vex[0].info = "华南理工大学的精神象征";
	G.vex[1].name = "逸夫人文馆";
	G.vex[1].info = "举办重要学术活动的场所";
	G.vex[2].name = "图书馆";
	G.vex[2].info = "学校文献信息中心";
	G.vex[3].name = "西湖苑宾馆";
	G.vex[3].info = "供外来访客居住的酒店";
	G.vex[4].name = "北区运动场";
	G.vex[4].info = "田径场和篮球场";
	G.vex[5].name = "31-34号楼";
	G.vex[5].info = "主要教学楼群";
	G.vex[6].name = "北区博学楼";
	G.vex[6].info = "大型综合教学楼";
	G.vex[7].name = "西湖文化长廊";
	G.vex[7].info = "校园文化景观";
	G.vex[8].name = "麟鸿楼";
	G.vex[8].info = "材料科学与工程学院";
	G.vex[9].name = "清清文理楼";
	G.vex[9].info = "文科学院教学楼";
	G.vex[10].name = "西区体育馆";
	G.vex[10].info = "综合性体育场馆";
	G.vex[11].name = "校医院";
	G.vex[11].info = "学校医疗服务中心";
	G.vex[12].name = "南门";
	G.vex[12].info = "学校正门";
	//注意无向图是对称的
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			G.AdjMatrix[i][j] = INFINITY;
			G.AdjMatrix[0][1] = G.AdjMatrix[1][0] = 500;
			G.AdjMatrix[0][2] = G.AdjMatrix[2][0] = 200;
			G.AdjMatrix[1][3] = G.AdjMatrix[3][1] = 300;
			G.AdjMatrix[1][9] = G.AdjMatrix[9][1] = 300;
			G.AdjMatrix[2][9] = G.AdjMatrix[9][2] = 600;
			G.AdjMatrix[2][4] = G.AdjMatrix[4][2] = 2000;
			G.AdjMatrix[3][5] = G.AdjMatrix[5][3] = 200;
			G.AdjMatrix[3][9] = G.AdjMatrix[9][3] = 300;
			G.AdjMatrix[4][9] = G.AdjMatrix[9][4] = 1500;
			G.AdjMatrix[4][8] = G.AdjMatrix[8][4] = 1900;
			G.AdjMatrix[5][6] = G.AdjMatrix[6][5] = 1000;
			G.AdjMatrix[5][10] = G.AdjMatrix[10][5] = 700;
			G.AdjMatrix[6][10] = G.AdjMatrix[10][6] = 1500;
			G.AdjMatrix[6][7] = G.AdjMatrix[7][6] = 1100;
			G.AdjMatrix[6][12] = G.AdjMatrix[12][6] = 2000;
			G.AdjMatrix[7][9] = G.AdjMatrix[9][7] = 200;
			G.AdjMatrix[7][12] = G.AdjMatrix[12][7] = 700;
			G.AdjMatrix[8][9] = G.AdjMatrix[9][8] = 400;
			G.AdjMatrix[10][11] = G.AdjMatrix[11][10] = 1200;
			G.AdjMatrix[10][12] = G.AdjMatrix[12][10] = 1000;
			G.AdjMatrix[11][12] = G.AdjMatrix[12][11] = 800;
		}
	}
}

void Menu() {
	system("cls");//清屏
	cout << endl;
	cout << "|----------------------------欢迎来到华南理工大学-------------------------------\n";
	cout << "|---------------------------校园导游系统功能菜单图------------------------------\n";
	cout << "|*******************************************************************************\n";
	cout << "|      1.校园景点一览         2.最短路径查询                                    \n";
	cout << "|      3.更新景点信息                                           \n";
	cout << "|      0.退出                                                                   \n";
	cout << "|*******************************************************************************\n";
	cout << endl;
}

void PrintAllInfo(MGraph& G) {
	cout.setf(ios::left, ios::adjustfield);
	cout << setw(10) << "编号" << setw(15) << "名称" << "简介" << endl;
	for (int i = 0; i < G.vexnum; i++) {
		cout << setw(10) << G.vex[i].Num << setw(15) << G.vex[i].name << G.vex[i].info << endl;
	}
}



void Floyd(MGraph& G) {
	//对Floyd的两个数组进行初始化
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			PathMatirx[i][j] = j;
			ShortPath[i][j] = G.AdjMatrix[i][j];
		}
	}
	for (int k = 0; k < G.vexnum; k++) {
		for (int v = 0; v < G.vexnum; v++) {
			for (int w = 0; w < G.vexnum; w++) {
				if (ShortPath[v][w] > ShortPath[v][k] + ShortPath[k][w]) {
					//更新最短路径
					ShortPath[v][w] = ShortPath[v][k] + ShortPath[k][w];
					//更新路径中间经过的节点
					PathMatirx[v][w] = PathMatirx[v][k];
				}
			}
		}
	}
}

void ShortestPathOfAnyTwo(MGraph& G) {
	int start, end, k;
	bool flag1 = false;
	bool flag2 = false;
	cout << "请您输入要查询最短路径的两个不同的景点的编号！" << endl;
	cout << "请您输入起点景点的编号：";
	cin >> start;
	cout << "请您输入终点景点的编号：";
	cin >> end;
	if (start == end) {
		cout << "对不起！您所输入的两个景点的编号一样,请重新输入" << endl;
	}
	for (int i = 0; i < G.vexnum; i++) {
		if (start == G.vex[i].Num) {
			flag1 = true;
		}
		if (end == G.vex[i].Num) {
			flag2 = true;
		}
	}
	if (!(flag1 == true && flag2 == true)) {
		cout << "您输入的两个景点中有不存在的情况,请重新输入" << endl;
	}
	cout << "从景点 " << G.vex[start - 1].name << " 到景点 " << G.vex[end - 1].name << "的最短路径长度为：" << ShortPath[start][end] << endl;
	cout << "具体路径为：" << endl;
	k = PathMatirx[start][end];
	cout << start << "--->";
	while (k != end) {
		cout << k << "--->";
		k = PathMatirx[k][end];
	}
	cout << end << endl;
}




void UpdateIifo(MGraph& G) {
	//更新景点信息
	int number;
	string info;
	string name;
	cout << "请输入您想更新的景点的编号" << endl;
	cin >> number;
	if (number<1 || number>G.vexnum) {
		cout << "您的输入有误，请重新输入" << endl;
		return;
	}
	cout << "请输入景点新的信息" << endl;
	cin >> info;
	cout << info << endl;
	G.vex[number - 1].info = info;
	cin >> name;
	cout << name << endl;
	G.vex[number - 1].name = name;
	cout << "修改成功" << endl;
	PrintAllInfo(G);
}

void PrintAdj(MGraph& G) {
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			cout << G.AdjMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	cout << "欢迎来到华南理工大学五山校区" << endl;
	MGraph G;
	InitGraph(G);//初始化
	Menu();//用户看到菜单
	bool flag = true;
	while (flag) {
		cout << "请输入您的选择：" << endl;
		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			PrintAllInfo(G);
			break;
		case 2:
			Floyd(G);
			ShortestPathOfAnyTwo(G);
			break;
		case 3:
			UpdateIifo(G);
			break;
		case 4:
			PrintAdj(G);
			break;
		case 0:
			cout << "感谢您的使用，再见" << endl;
			flag = false;
			break;
		default:
			cout << "您的输入有误，请重新输入" << endl;
		};
	}
}


