#pragma once

#include<iostream>
#include<cstring>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<time.h>

#define N 20	//战场高度
#define M 40	//战场宽度
#define PixelWidth 20	//飞机大小 
#define EP_num 20	//敌机最大数量
#define EPBomb_num 80	//敌机最多子弹数
#define MPBomb_num 20	//我机最多子弹数
#define BossBlood 10	//敌机Boss的血量
#define ScoreThreshold 100	//出现Boss的分数上限
#define UniqueSkill 100	//一个特技的分数要求
using namespace std;


class EnemyPlane;
class MyPlane;
class Bomb;
class Control
{
private:
	int score;//分数
	int stage;//阶段
	int unique_skill_num;//大招数
	int used_US;//已用大招数
	bool win;//胜利？
	bool run;//暂停？
	bool live;//死亡？
	bool god_like;//大招时
public:
	MyPlane* MP;
	EnemyPlane* EP[EP_num];
	Bomb* MB[MPBomb_num];
	Bomb* EB[EPBomb_num];
	Control();
	void Choose_Fly(char inputchar);//开始界面
	void KeyboardOperate(char inputchar);//结束界面
	void In_Pause(char inputchar);
	void To_End(char inputchar);//结束前的画面暂停
	void The_End(char inputchar);//结束界面
	void NewEP(int i);
	void BombMove();
	//与EnemyPlane不同，由于判断子弹出了边界则会删除，所以子弹运动函数放在Control而不是Bomb内
	void EnemyShoot(int v);
	void HitCheck();
	void ImpackCheck();
	void Unique_Skill();//其实只有飞机3的特技，其他特技在其他判断阶段就实现了
	void End_US();
	//一些获取私有成员值的函数
	int GetScore() const { return score; }
	int GetStage() const { return stage; }
	int GetUSN() const { return unique_skill_num; }
	bool GetGL() const { return god_like; }
	bool GetRun() const { return run; }
	bool GetLive() const { return live; }
	bool GetWin() const { return win; }
};
class Plane
{
	friend class BattleField;
	friend class Control;
protected:
	int version;
	int point_x, point_y;
public:
	int GetPointx() const { return point_x; }
	int GetPointy() const { return point_y; }
	int GetVersion() const { return version; }
};
class MyPlane : public Plane
{
	friend class Control;
protected:
	int blood;
	int scoremultiples;
public:
	MyPlane(int x);
	int GetBlood() const { return blood; }
	int GetSM() const { return scoremultiples; }
};
class EnemyPlane :public Plane
{
	friend class Control;
protected:
	bool vertical;//斜行？
	bool is_right;//向右斜行？
	int frequence;//移动频率，500ms/格，1000ms/格
	int scoreweight;//分数权重，击落敌机获得的分数
	int blood;//boss血量
public:
	EnemyPlane(int x);
	void Move();
	int GetFrequence() { return frequence; }
	int GetBlood() { return blood; }
};
class Bomb :public Plane
{
	friend class Control;
private:
	bool is_right;//向右斜行？
	bool vertical;//斜行？
	int weight;//伤害值
public:
	Bomb(int i, int j, int k, bool l);//子弹的位置，类型，斜行的方向（无斜行则随意）
};