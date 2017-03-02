#pragma once

#include<iostream>
#include<cstring>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<time.h>

#define N 20	//ս���߶�
#define M 40	//ս�����
#define PixelWidth 20	//�ɻ���С 
#define EP_num 20	//�л��������
#define EPBomb_num 80	//�л�����ӵ���
#define MPBomb_num 20	//�һ�����ӵ���
#define BossBlood 10	//�л�Boss��Ѫ��
#define ScoreThreshold 100	//����Boss�ķ�������
#define UniqueSkill 100	//һ���ؼ��ķ���Ҫ��
using namespace std;


class EnemyPlane;
class MyPlane;
class Bomb;
class Control
{
private:
	int score;//����
	int stage;//�׶�
	int unique_skill_num;//������
	int used_US;//���ô�����
	bool win;//ʤ����
	bool run;//��ͣ��
	bool live;//������
	bool god_like;//����ʱ
public:
	MyPlane* MP;
	EnemyPlane* EP[EP_num];
	Bomb* MB[MPBomb_num];
	Bomb* EB[EPBomb_num];
	Control();
	void Choose_Fly(char inputchar);//��ʼ����
	void KeyboardOperate(char inputchar);//��������
	void In_Pause(char inputchar);
	void To_End(char inputchar);//����ǰ�Ļ�����ͣ
	void The_End(char inputchar);//��������
	void NewEP(int i);
	void BombMove();
	//��EnemyPlane��ͬ�������ж��ӵ����˱߽����ɾ���������ӵ��˶���������Control������Bomb��
	void EnemyShoot(int v);
	void HitCheck();
	void ImpackCheck();
	void Unique_Skill();//��ʵֻ�зɻ�3���ؼ��������ؼ��������жϽ׶ξ�ʵ����
	void End_US();
	//һЩ��ȡ˽�г�Աֵ�ĺ���
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
	bool vertical;//б�У�
	bool is_right;//����б�У�
	int frequence;//�ƶ�Ƶ�ʣ�500ms/��1000ms/��
	int scoreweight;//����Ȩ�أ�����л���õķ���
	int blood;//bossѪ��
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
	bool is_right;//����б�У�
	bool vertical;//б�У�
	int weight;//�˺�ֵ
public:
	Bomb(int i, int j, int k, bool l);//�ӵ���λ�ã����ͣ�б�еķ�����б�������⣩
};