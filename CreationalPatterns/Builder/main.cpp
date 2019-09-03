#include<iostream>
#include<string>
#include<memory>
using namespace std;

class Pizza
{
	string base;
	string sauce;
	string topping;	//начинка
public:
	void set_base(const string& base)
	{
		this->base = base;
	}
	void set_sauce(const string& sauce)
	{
		this->sauce = sauce;
	}
	void set_topping(const string& topping)
	{
		this->topping = topping;
	}
};

void main()
{
	
}