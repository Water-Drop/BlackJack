#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

void shuffle(bool cards[52]);
int send_cards(bool cards[52]);
string print_card(int card_id);
double calculate_points(int own_cards[], int num_of_cards);
int determine_winner(int own_cards_player1[], int cards_of_player1, int own_cards_player2[], int cards_of_player2);


int main()
{
	bool cards[52];//所有牌的使用情况，false表示未使用，true表示已使用
	int cards_of_player1 = 0;//玩家拥有的牌的数量
	int cards_of_player2 = 0;//电脑拥有的牌的数量
	int own_cards_player1[22];//玩家拥有的牌（最极端情况需要22张牌）
	int own_cards_player2[22];//电脑拥有的牌
	string user_input;//记录用户的输入
	bool end_game_flag = false;
	while (true)
	{
		shuffle(cards);//洗牌
		cout << "欢迎来到21点游戏！\n";
		cards_of_player1 ++;//给玩家发两张牌
		own_cards_player1[0] = send_cards(cards);
		cards_of_player1 ++;
		own_cards_player1[1] = send_cards(cards);
		cout << "玩家获得牌： " << print_card(own_cards_player1[0]) << print_card(own_cards_player1[1]) << endl;
		cout << "现在的点数是：" << calculate_points(own_cards_player1, cards_of_player1) << endl;
		while (true)
		{
			cout << "是否继续要牌？（Y/N) \n";
			getline(cin, user_input);//读入用户的整行输入
			while (user_input != "Y" && user_input != "N" && user_input != "y" && user_input != "n")
			{
				cout << "您的输入有误，请重新输入！\n";
				cout << "是否继续要牌？（Y/N) \n";
				getline(cin, user_input);
			}
			if (user_input == "N" || user_input == "n")//玩家选择不继续要牌
			{
				break;//跳出循环
			}
			else//玩家选择继续要牌
			{
				cards_of_player1 ++;
				own_cards_player1[cards_of_player1 - 1] = send_cards(cards);
				cout << "继续要一张牌：";
				for (int i = 0 ; i < cards_of_player1; i++)
				{
					cout << print_card(own_cards_player1[i]);
				}
				cout << endl;
				cout << "现在的点数是：" << calculate_points(own_cards_player1, cards_of_player1) << endl;
				if (calculate_points(own_cards_player1, cards_of_player1) > 21)//如果点数大于21点，则输掉游戏
				{
					end_game_flag = true;
					cout << "玩家输掉了游戏!" << endl;
					cout << endl;
					break;
				}
			}
		}
		if (end_game_flag == false)//玩家不继续要牌，进入电脑阶段
		{
			cards_of_player2 ++;//给电脑发两张牌
			own_cards_player2[0] = send_cards(cards);
			cards_of_player2 ++;
			own_cards_player2[1] = send_cards(cards);
			cout << "电脑获得牌： " << print_card(own_cards_player2[0]) << print_card(own_cards_player2[1]) << endl;
			cout << "玩家的点数是：" << calculate_points(own_cards_player1, cards_of_player1) << '\t';
			cout << "电脑的点数是：" << calculate_points(own_cards_player2, cards_of_player2) << endl;
			while (true)
			{
				if (determine_winner(own_cards_player1, cards_of_player1, own_cards_player2, cards_of_player2) == -1)//电脑可以赢得游戏
				{
					cout << "玩家输掉了游戏" << endl;
					cout << endl;
					end_game_flag = true;
					break;
				}
				else if (abs(calculate_points(own_cards_player2, cards_of_player2) - 21) < 0.000001)//如果电脑得分已经达到21分，则不再要牌
				{
					if (determine_winner(own_cards_player1, cards_of_player1, own_cards_player2, cards_of_player2) == 0)
					{
						end_game_flag = true;
						cout << "双方平局" << endl;
						cout << endl;
						break;
					}
					else
					{
						end_game_flag = true;
						cout << "玩家赢得了游戏!" << endl;
						cout << endl;
						break;
					}
				}
				else//继续给电脑发牌
				{
					cards_of_player2 ++;
					own_cards_player2[cards_of_player2 - 1] = send_cards(cards);
					cout << "电脑要一张牌：";
					for (int i = 0 ; i < cards_of_player2; i++)
					{
						cout << print_card(own_cards_player2[i]);
					}
					cout << endl;
					cout << "玩家的点数是：" << calculate_points(own_cards_player1, cards_of_player1) << '\t';
					cout << "电脑的点数是：" << calculate_points(own_cards_player2, cards_of_player2) << endl;
					if (calculate_points(own_cards_player2, cards_of_player2) > 21)//如果电脑点数大于21点，则玩家赢得游戏
					{
						end_game_flag = true;
						cout << "玩家赢得了游戏!" << endl;
						cout << endl;
						break;
					}
				}

			}
			
		}
		cout << "再来一局？（Y/N) \n";
		getline(cin, user_input);//读入用户的整行输入
		while (user_input != "Y" && user_input != "N" && user_input != "y" && user_input != "n")
		{
			cout << "您的输入有误，请重新输入！\n";
			cout << "再来一局？（Y/N) \n";
			getline(cin, user_input);
		}
		if (user_input == "N" || user_input == "n")//玩家选择不继续游戏
		{
			cout << "感谢您的参与~！\n";
			break;//跳出循环
		}
		else//玩家选择重新开始一局游戏
		{
			cards_of_player1 = 0;
			cards_of_player2 = 0;
			end_game_flag = false;
			shuffle(cards);
		}
	}
	getchar();//使控制台界面停留
	return 0;
}


void shuffle(bool cards[52])//洗牌
{
	for (unsigned int i = 0; i < 52; i++)
	{
		cards[i] = false;//将每张牌都变成未使用状态
	}
};

int send_cards(bool cards[52])//发牌
{
	srand((unsigned)time(NULL));
	int tmp_card = rand() % 52;
	while (cards[tmp_card] == true)//如果随机出的数对应的牌被使用过，重新生成随机数
	{
		tmp_card = rand() % 52;
	}
	cards[tmp_card] = true;
	return tmp_card;
};

string print_card(int card_id)//显示牌号
{
	string rtn_str = "";
	int card_type = card_id / 13;
	int card = card_id % 13;
	switch (card_type)
	{
	case 0: 
		rtn_str += "红桃 "; break;
	case 1:
		rtn_str += "黑桃 "; break;
	case 2:
		rtn_str += "梅花 "; break;
	default:
		rtn_str += "方块 "; break;
	}
	switch (card)
	{
	case 0: 
		rtn_str += "A\t"; break;
	case 1:
		rtn_str += "2\t"; break;
	case 2:
		rtn_str += "3\t"; break;
	case 3: 
		rtn_str += "4\t"; break;
	case 4:
		rtn_str += "5\t"; break;
	case 5:
		rtn_str += "6\t"; break;
	case 6: 
		rtn_str += "7\t"; break;
	case 7:
		rtn_str += "8\t"; break;
	case 8:
		rtn_str += "9\t"; break;
	case 9: 
		rtn_str += "10\t"; break;
	case 10:
		rtn_str += "J\t"; break;
	case 11:
		rtn_str += "Q\t"; break;
	default:
		rtn_str += "K\t"; break;
	}
	return rtn_str;
};

double calculate_points(int own_cards[], int num_of_cards)
{
	double sum_points = 0;
	for (int i = 0; i < num_of_cards; i++)
	{
		int card_id = own_cards[i] % 13;//计算出牌对应的大小
		switch(card_id)
		{
		case 10: case 11: case 12: //J Q K 计算为0.5点
			sum_points += 0.5; break;
		default:
			sum_points = sum_points + card_id + 1;
		}
	}
	return sum_points;
};

int determine_winner(int own_cards_player1[], int cards_of_player1, int own_cards_player2[], int cards_of_player2)//判断输赢
{
	double points_of_player1 = calculate_points(own_cards_player1, cards_of_player1);
	double points_of_player2 = calculate_points(own_cards_player2, cards_of_player2);
	double small_number = 0.000001;
	if (abs(points_of_player1 - points_of_player2) < small_number) //得分相等
	{
		if (cards_of_player1 > cards_of_player2)//取牌数量更多的一方获胜
		{
			return 1;//Player1获胜
		}
		else if (cards_of_player2 > cards_of_player1)
		{
			return -1;//Player2获胜
		}
		else
		{
			return 0;//不分胜负
		}
	}
	else
	{
		if (points_of_player1 - points_of_player2 > 0)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
};