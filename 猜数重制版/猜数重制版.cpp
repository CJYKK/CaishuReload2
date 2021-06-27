//各种头文件和将命名空间用关键字namespace来定义
#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <fstream>
#include <conio.h>
using namespace std;

//清空屏幕
void clear_screen() 
{
#ifdef __linux__
	system("clear");
#elif defined(_WIN32)
	system("cls");
#endif
}

//获取随机数
long long random_number(int range)
{
	srand(time(NULL));
	int answer = rand() % range;
	return answer;
}

//保存成绩
void save_score(long long answer, long long score)
{
	cout << "请问是否需要记录您的成绩？（Y/n)" << endl;
	char save = _getch();
	if (save == 'Y' || save == 'y')
	{
		cout << "请输入您的姓名：";
		string name;
		cin >> name;
		cout << endl;
		cout << "开始进行成绩记录……" << endl;
		ofstream out("./CaishuReload2_Data/Score.txt", ios::app);
		out << "记录者：" << name << "，正确答案：" << answer << "，猜测次数：" << score << "次" << endl;
		out.close();
		cout << "记录完成，感谢您的游玩，再见！" << endl;
	}
	else if (save == 'n' || save == 'N')
	{
		cout << "感谢您的游玩，再见！" << endl;
	}
}

//游戏模式1
void game_mode_1()
{
	long long range = 0;
	cout << "请输入随机数的取值范围（最终的答案将会在0~x之间）：";
	cin >> range;
	int answer = random_number(range);
	clear_screen();
	long long score = 0;
	long long guess = 0;
	while (true)
	{
		score++;
		cout << "请进行您的第" << score << "次猜测：";
		cin >> guess;
		if (guess > answer)
		{
			cout << "大了" << endl << endl;
		}
		if (guess < answer)
		{
			cout << "小了" << endl << endl;
		}
		if (guess == answer)
		{
			break;
		}
	}
	clear_screen();
	cout << "太棒了，猜测正确！" << endl;
	cout << "统计信息：" << endl;
	cout << "正确答案是" << answer << "，您总共猜测了" << score << "次。" << endl;
	save_score(answer, score);
}

//查询成绩
void read_score()
{
	ifstream in("./CaishuReload2_Data/Score.txt");
	string line;
	if (in) //有该文件
	{
		while (getline(in, line)) //line中不包括每行的换行符
		{
			cout << line << endl;
		}
	}
	else //没有该文件
	{
		cout << "成绩读取失败，也许还没有记录的成绩呢？" << endl;
	}
}

//主菜单（无多平台支持：没有getch函数）
void main_menu()
{
	cout << "+------------------------+" << endl;
	cout << "|欢迎来到猜数 - 重制版2！|" << endl;
	cout << "|请选择您的游戏模式：    |" << endl;
	cout << "|1.经典模式（可选择范围）|" << endl;
	cout << "|2.查询记录的游戏成绩    |" << endl;
	cout << "+------------------------+" << endl;
	cout << "请输入想玩的游戏模式的序号：";
	char mode = _getch();
	clear_screen();
	if (mode == '1')
	{
		game_mode_1();
	}
	else if (mode == '2')
	{
		read_score();
	}
}

//主函数
int main()
{
#ifdef _WIN32
	system("title 猜数 - 重制版2 // By CJYKK");
	system("color 17");
#endif
	main_menu();
	system("pause");
}