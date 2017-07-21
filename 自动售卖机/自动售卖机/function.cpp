#include<iostream>
#include<stdio.h>
#include<string>
#include<conio.h>
#include<fstream>
#include<iomanip>
#include"head.h"
using namespace std;
void vending_machine::k_password()
{
	k.modify_password();
	system("cls");
	administrator_menu();
}
void vending_machine::k_commodity()
{
	k.modify_commodity();
	system("cls");
	administrator_menu();
}
void vending_machine::k_logon()
{
	int r = k.log_on();
	if (r == 1)
	{
		system("cls");
		administrator_menu();
	}
	if (r == 2)
	{
		system("cls");
		standby_mode();
	}
}
float vending_machine::a_pay()
{
	float u = a.pay();
	return u;
}
void vending_machine::standby_mode()
{
	cout << "--CGL ¤Î Vending Machine--" << endl;
	cout << "Welcome to use me, new or old friend!" << endl;
	cout << endl << "If you wanna buy something, please press '1'." << endl;
	cout << endl << "If you are a administrator, please press '2' to log on." << endl;
	cout << endl << "If you wanna power me off, please press '0'" << endl;
	cout << endl;
	int d = 0;
	char a;
	while (d == 0)
	{
		a = _getch();
		if (a == '1')
		{
			d = 1;
			system("cls");
			show_the_commodities();
		}
		else if (a == '2')
		{
			d = 1;
			system("cls");
			k_logon();
		}
		else if (a == '0')
		{
			cout << "Byebye" << endl;
			return;
		}
		else
		{
			cout << "Sorry! Please press a correct character, I'm too stupid to recognize it." << endl;
		}
	}
}
void vending_machine::administrator_menu()
{
	cout << "Hello! Dear administrator! What would you like to do? " << endl << endl;
	cout << "1. Modify the password                2. Modify the commodity or price " << endl;
	cout << "3. Go back" << endl;
	int g = 0;
	while (g == 0)
	{
		char w;
		w = _getch();
		switch (w)
		{
		case '1':
		{
			g = 1;
			system("cls");
			k_password();
			break;
		}
		case '2':
		{
			g = 1;
			system("cls");
			k_commodity();
			break;
		}
		case '3':
		{
			g = 1;
			system("cls");
			standby_mode();
			break;
		}
		default:
		{
			cout << "Sorry! Please press a correct character, I'm too stupid to recognize it." << endl;
			break;
		}
		}
	}
}
void vending_machine::show_the_commodities()
{
	ifstream infile("commodities.txt", ios::in | ios::_Nocreate);
	if (!infile)
	{
		cout << "Open error!" << endl;
		exit(1);
	}
	for (int i = 0; i < 9; i++)
	{
		infile >> commodity[i].name >> commodity[i].price >> commodity[i].amount;
	}
	infile.close();
	printf("NO  name   price amount\n");
	for (int i = 0; i < 9; i ++)
	{
		
		cout << i+1 << setw(10) << commodity[i].name << setw(4) << commodity[i].price << setw(4) << commodity[i].amount << endl;
		
	}
	choose_commodities();
}
void vending_machine::choose_commodities()
{
	cout << "Please press what you want. " << endl;
	cout << "Press '0' to back. " << endl;
	char i;
	number = 1;
	i = _getch();
	switch (i)
	{
	case '1':number = 0;
		break;
	case '2':number = 1;
		break;
	case '3':number = 2;
		break;
	case '4':number = 3;
		break;
	case '5':number = 4;
		break;
	case '6':number = 5;
		break;
	case '7':number = 6;
		break;
	case '8':number = 7;
		break;
	case '9':number = 8;
		break;
	case '0':
		standby_mode();
		return;
	}
	payment(number);
}
int vending_machine::payment(int n)
{
	if (commodity[n].amount == 0)
	{
		system("cls");
		cout << "Sorry!¡¡There is no " << commodity[n].name << endl;
		show_the_commodities();
	}
	else
	{
		printf("You need to pay %.1f yuan.\n", commodity[n].price);
		float b = a_pay();
		int p = 0;
		while (b < commodity[n].price&&p == 0)
		{
			printf("You still need to pay %.1f yuan\n", commodity[n].price - b);
			cout << "If you want to drop the deal, please input 0 yuan." << endl;
			float c = a_pay();
			if (c == 0)
			{
				p = 1;
				system("cls");
				standby_mode();
			}
			else
			{
				b += c;
				if (b > commodity[n].price)
				{
					cout << "This is the balance. " << endl;
					cout << b - commodity[n].price << endl;
				}

				commodity[n].amount -= 1;
				ofstream outfile("commodities.txt", ios::out);
				if (!outfile)
				{
					cout << "Open error!" << endl;
					exit(1);
				}
				for (int i = 0; i < 9; i++)
				{
					outfile << commodity[i].name << " " << commodity[i].price << " " << commodity[i].amount << endl;
				}
				outfile.close();
				int z = 0;
				while (z == 0)
				{
					cout << "Great! Please press '1' to get your drink. " << endl;
					char t;
					t = _getch();
					if (t == '1')
					{
						z = 1;
						cout << "This is your drink! Have a nice day! " << endl;
						cout << "Would you like to buy something else? " << endl;
						int m = 0;
						while (m == 0)
						{
							cout << "1.Yes    2.No	" << endl;
							char y;
							y = _getch();
							if (y == '1')
							{
								m = 1;
								show_the_commodities();
							}
							else if (y == '2')
							{
								m = 1;
								cout << "OK. Byebye!" << endl;
								return 0;
							}
							else
								cout << "Sorry! Please press a correct character, I'm too stupid to recognize it." << endl;
						}
					}
					else
						cout << "Sorry! Please press a correct character, I'm too stupid to recognize it." << endl;
				}
			}
		}
	}
}
float user::pay()
{
	cin >> money;
	float a = money;
	return a;
}
int administrator::log_on()
{
	ifstream infile("password.txt", ios::in | ios::_Nocreate);
	if (!infile)
	{
		cout << "Open error!" << endl;
		exit(1);
	}

	infile >> password;
	infile.close();
	int q = 0;
	while (q == 0)
	{
		cout << "Please input your password. " << endl;
		string a;
		cin >> a;
		if (a != password)
		{
			cout << "Your password is wrong. " << endl;
			cout << "Would you like to try again? " << endl;
			int x = 0;
			while (x == 0)
			{
				cout << "1.Yes    2.No" << endl;
				char i;
				i = _getch();
				if (i == '2')
				{
					x = 1;
					q = 1;
					return 2;
				}
				if (i == '1')
				{
					x = 1;
					q = 0;
				}
				else
				{
					cout << "Sorry! Please press a correct character, I'm too stupid to recognize it." << endl;
				}
			}
		}
		if (a == password)
		{
			q = 1;
			return 1;
		}
	}
}
void administrator::modify_password()
{
	string s;
	int i = 0;
	while (i == 0)
	{
		cout << "Please input the new password: " << endl;
		cin >> s;
		cout << "The new password is " << s << endl;
		cout << "Are ypu sure? " << endl;
		int b = 0;
		while (b == 0)
		{
			cout << "1. Yes   2. No " << endl;
			char p;
			p = _getch();
			if (p == '2')
			{	
				b = 1;
				i = 0;
			}
			if (p == '1')
			{
				b = 1;
				i = 1;
			}
			else
			{
				cout << "Sorry! Please press a correct character, I'm too stupid to recognize it." << endl;
			}
		}
	}
	ofstream outfile("password.txt", ios::out);
	if (!outfile)
	{
		cout << "Open error!" << endl;
		exit(1);
	}
	outfile << s;
	outfile.close();
	cout << "Modify successfully!" << endl;
	int h = 0;
	while (h == 0)
	{
		cout << "Please press '1' to go back. " << endl;
		char u;
		u = _getch();
		if (u == '1')
		{
			h = 1;
			return;
		}
		else
			cout << "Sorry! Please press a correct character, I'm too stupid to recognize it." << endl;
	}
}
void administrator::modify_commodity()
{
	comm b[9];
	ifstream infile("commodities.txt", ios::in | ios::_Nocreate);
	if (!infile)
	{
		cout << "Open error!" << endl;
		exit(1);
	}
	for (int i = 0; i < 9; i++)
	{
		infile >> b[i].name >> b[i].price >> b[i].amount;
	}
	infile.close();
	cout << "Which commodity would you like to modify? " << endl;
	cout << "Press '0' to go back." << endl;
	printf("NO  name   price amount\n");
	for (int i = 0; i < 9; i ++)
	{
		cout << i+1 << setw(10) << b[i].name << setw(4) << b[i].price << setw(4) << b[i].amount << endl;
	}
	
	char k;
	int number = 1;
	k = _getch();
	switch (k)
	{
	case '1':number = 0;
		break;
	case '2':number = 1;
		break;
	case '3':number = 2;
		break;
	case '4':number = 3;
		break;
	case '5':number = 4;
		break;
	case '6':number = 5;
		break;
	case '7':number = 6;
		break;
	case '8':number = 7;
		break;
	case '9':number = 8;
		break;
	case '0':
	{
		return;
	}
	}
	printf("This commodity's original information is \n");
	cout << "   name  price  amount" << endl;
	cout << setw(9) << b[number].name << setw(4) << b[number].price << setw(5) << b[number].amount << endl;
	cout << "Please input the new information. " << endl;
	cout << "name   price   amount" << endl;
	cin >> b[number].name >> b[number].price >> b[number].amount;
	ofstream outfile("commodities.txt", ios::out);
	if (!outfile)
	{
		cout << "Open error!" << endl;
		exit(1);
	}
	for (int i = 0; i < 9; i++)
	{
		outfile << b[i].name << " " << b[i].price << " " << b[i].amount << endl;
	}
	outfile.close();
	cout << "Modifly successfully" << endl;
	printf("NO  name   price amount\n");
	for (int i = 0; i < 9; i++)
	{
		cout << setw(9) << b[i].name << setw(4) << b[i].price << setw(4) << b[i].amount << endl;
	}
	int j = 0;
	while (j == 0)
	{
		cout << "Please press '1' to go back. " << endl;
		char u;
		u = _getch();
		if (u == '1')
		{
			j = 1;
			return;
		}
		else
		{
			cout << "Sorry! Please press a correct character, I'm too stupid to recognize it." << endl;
		}
	}
}
