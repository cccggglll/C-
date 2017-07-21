#pragma once
#include<iostream>
#include<stdio.h>
#include<string>
#include<conio.h>
#include<fstream>
#include<iomanip>

using namespace std;

struct comm
{
	string name;
	float price;
	int amount;
};



class administrator
{
private:
	string password;//123456
	
public:
	
	int log_on();
	void modify_password();
	void modify_commodity();
};
class user
{
private:
	float money;
public:
	float pay();

};
class vending_machine
{
private:
	comm commodity[9];
	int number;
	administrator k;
	user a;
public:
	void k_password();

	void k_commodity();

	void k_logon();

	float a_pay();


	void standby_mode();
	void administrator_menu();
	void show_the_commodities();
	void choose_commodities();
	int payment(int n);
};
