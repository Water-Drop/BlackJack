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
	bool cards[52];//�����Ƶ�ʹ�������false��ʾδʹ�ã�true��ʾ��ʹ��
	int cards_of_player1 = 0;//���ӵ�е��Ƶ�����
	int cards_of_player2 = 0;//����ӵ�е��Ƶ�����
	int own_cards_player1[22];//���ӵ�е��ƣ���������Ҫ22���ƣ�
	int own_cards_player2[22];//����ӵ�е���
	string user_input;//��¼�û�������
	bool end_game_flag = false;
	while (true)
	{
		shuffle(cards);//ϴ��
		cout << "��ӭ����21����Ϸ��\n";
		cards_of_player1 ++;//����ҷ�������
		own_cards_player1[0] = send_cards(cards);
		cards_of_player1 ++;
		own_cards_player1[1] = send_cards(cards);
		cout << "��һ���ƣ� " << print_card(own_cards_player1[0]) << print_card(own_cards_player1[1]) << endl;
		cout << "���ڵĵ����ǣ�" << calculate_points(own_cards_player1, cards_of_player1) << endl;
		while (true)
		{
			cout << "�Ƿ����Ҫ�ƣ���Y/N) \n";
			getline(cin, user_input);//�����û�����������
			while (user_input != "Y" && user_input != "N" && user_input != "y" && user_input != "n")
			{
				cout << "���������������������룡\n";
				cout << "�Ƿ����Ҫ�ƣ���Y/N) \n";
				getline(cin, user_input);
			}
			if (user_input == "N" || user_input == "n")//���ѡ�񲻼���Ҫ��
			{
				break;//����ѭ��
			}
			else//���ѡ�����Ҫ��
			{
				cards_of_player1 ++;
				own_cards_player1[cards_of_player1 - 1] = send_cards(cards);
				cout << "����Ҫһ���ƣ�";
				for (int i = 0 ; i < cards_of_player1; i++)
				{
					cout << print_card(own_cards_player1[i]);
				}
				cout << endl;
				cout << "���ڵĵ����ǣ�" << calculate_points(own_cards_player1, cards_of_player1) << endl;
				if (calculate_points(own_cards_player1, cards_of_player1) > 21)//�����������21�㣬�������Ϸ
				{
					end_game_flag = true;
					cout << "����������Ϸ!" << endl;
					cout << endl;
					break;
				}
			}
		}
		if (end_game_flag == false)//��Ҳ�����Ҫ�ƣ�������Խ׶�
		{
			cards_of_player2 ++;//�����Է�������
			own_cards_player2[0] = send_cards(cards);
			cards_of_player2 ++;
			own_cards_player2[1] = send_cards(cards);
			cout << "���Ի���ƣ� " << print_card(own_cards_player2[0]) << print_card(own_cards_player2[1]) << endl;
			cout << "��ҵĵ����ǣ�" << calculate_points(own_cards_player1, cards_of_player1) << '\t';
			cout << "���Եĵ����ǣ�" << calculate_points(own_cards_player2, cards_of_player2) << endl;
			while (true)
			{
				if (determine_winner(own_cards_player1, cards_of_player1, own_cards_player2, cards_of_player2) == -1)//���Կ���Ӯ����Ϸ
				{
					cout << "����������Ϸ" << endl;
					cout << endl;
					end_game_flag = true;
					break;
				}
				else if (abs(calculate_points(own_cards_player2, cards_of_player2) - 21) < 0.000001)//������Ե÷��Ѿ��ﵽ21�֣�����Ҫ��
				{
					if (determine_winner(own_cards_player1, cards_of_player1, own_cards_player2, cards_of_player2) == 0)
					{
						end_game_flag = true;
						cout << "˫��ƽ��" << endl;
						cout << endl;
						break;
					}
					else
					{
						end_game_flag = true;
						cout << "���Ӯ������Ϸ!" << endl;
						cout << endl;
						break;
					}
				}
				else//���������Է���
				{
					cards_of_player2 ++;
					own_cards_player2[cards_of_player2 - 1] = send_cards(cards);
					cout << "����Ҫһ���ƣ�";
					for (int i = 0 ; i < cards_of_player2; i++)
					{
						cout << print_card(own_cards_player2[i]);
					}
					cout << endl;
					cout << "��ҵĵ����ǣ�" << calculate_points(own_cards_player1, cards_of_player1) << '\t';
					cout << "���Եĵ����ǣ�" << calculate_points(own_cards_player2, cards_of_player2) << endl;
					if (calculate_points(own_cards_player2, cards_of_player2) > 21)//������Ե�������21�㣬�����Ӯ����Ϸ
					{
						end_game_flag = true;
						cout << "���Ӯ������Ϸ!" << endl;
						cout << endl;
						break;
					}
				}

			}
			
		}
		cout << "����һ�֣���Y/N) \n";
		getline(cin, user_input);//�����û�����������
		while (user_input != "Y" && user_input != "N" && user_input != "y" && user_input != "n")
		{
			cout << "���������������������룡\n";
			cout << "����һ�֣���Y/N) \n";
			getline(cin, user_input);
		}
		if (user_input == "N" || user_input == "n")//���ѡ�񲻼�����Ϸ
		{
			cout << "��л���Ĳ���~��\n";
			break;//����ѭ��
		}
		else//���ѡ�����¿�ʼһ����Ϸ
		{
			cards_of_player1 = 0;
			cards_of_player2 = 0;
			end_game_flag = false;
			shuffle(cards);
		}
	}
	getchar();//ʹ����̨����ͣ��
	return 0;
}


void shuffle(bool cards[52])//ϴ��
{
	for (unsigned int i = 0; i < 52; i++)
	{
		cards[i] = false;//��ÿ���ƶ����δʹ��״̬
	}
};

int send_cards(bool cards[52])//����
{
	srand((unsigned)time(NULL));
	int tmp_card = rand() % 52;
	while (cards[tmp_card] == true)//��������������Ӧ���Ʊ�ʹ�ù����������������
	{
		tmp_card = rand() % 52;
	}
	cards[tmp_card] = true;
	return tmp_card;
};

string print_card(int card_id)//��ʾ�ƺ�
{
	string rtn_str = "";
	int card_type = card_id / 13;
	int card = card_id % 13;
	switch (card_type)
	{
	case 0: 
		rtn_str += "���� "; break;
	case 1:
		rtn_str += "���� "; break;
	case 2:
		rtn_str += "÷�� "; break;
	default:
		rtn_str += "���� "; break;
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
		int card_id = own_cards[i] % 13;//������ƶ�Ӧ�Ĵ�С
		switch(card_id)
		{
		case 10: case 11: case 12: //J Q K ����Ϊ0.5��
			sum_points += 0.5; break;
		default:
			sum_points = sum_points + card_id + 1;
		}
	}
	return sum_points;
};

int determine_winner(int own_cards_player1[], int cards_of_player1, int own_cards_player2[], int cards_of_player2)//�ж���Ӯ
{
	double points_of_player1 = calculate_points(own_cards_player1, cards_of_player1);
	double points_of_player2 = calculate_points(own_cards_player2, cards_of_player2);
	double small_number = 0.000001;
	if (abs(points_of_player1 - points_of_player2) < small_number) //�÷����
	{
		if (cards_of_player1 > cards_of_player2)//ȡ�����������һ����ʤ
		{
			return 1;//Player1��ʤ
		}
		else if (cards_of_player2 > cards_of_player1)
		{
			return -1;//Player2��ʤ
		}
		else
		{
			return 0;//����ʤ��
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