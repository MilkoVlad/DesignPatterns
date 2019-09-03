#include<iostream>
#include<string>
#include<memory>
using namespace std;

//Product:
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
	void open()
	{
		cout << "Основание:\t" << base << endl;
		cout << "Соус:\t" << sauce << endl;
		cout << "Начинка:\t" << topping << endl;
	}
};

class PizzaBuilder	//Abstract builder
{
protected:
	unique_ptr<Pizza> pizza;
public:
	virtual ~PizzaBuilder()
	{

	}

	Pizza* get_pizza()
	{
		return pizza.release();
	}

	void create_new_pizza()
	{
		pizza = make_unique<Pizza>();
	}

	virtual void build_base() = 0;
	virtual void build_sauce() = 0;
	virtual void build_topping() = 0;
};

class HawaiianPizzaBuilder :public PizzaBuilder
{
public:
	virtual void build_base()
	{
		this->pizza->set_base("белое");
	}
	virtual void build_sauce()
	{
		this->pizza->set_sauce(" томатный, не острый");
	}
	virtual void build_topping()
	{
		this->pizza->set_topping("курица с сыром, ананасами и кукурузой");
	}
};

class BBQPizzaBuilder :public PizzaBuilder
{
public:
	virtual void build_base()
	{
		this->pizza->set_base("black");
	}
	virtual void build_sauce()
	{
		this->pizza->set_sauce(" чумак для шашлыку ;-)");
	}
	virtual void build_topping()
	{
		this->pizza->set_topping("курица с сыром, салом(бекон), помидорками, и МАРИНОВАННЫМ ЛУКОМ");
	}
};

class MargaretBuilder :public PizzaBuilder
{
public:
	virtual void build_base()
	{
		this->pizza->set_base("white");
	}
	virtual void build_sauce()
	{
		this->pizza->set_sauce(" томатный ");
	}
	virtual void build_topping()
	{
		this->pizza->set_topping("О_О как, нет мяса???!!!!!!!! Одни помидоры, мацорелла и зелень");
	}
};

class Cook
{
	PizzaBuilder* builder;
public:
	void open_pizza()
	{
		builder->get_pizza()->open();
	}
	void make_pizza(PizzaBuilder* pb)
	{
		builder = pb;
		builder->create_new_pizza();
		builder->build_base();
		builder->build_sauce();
		builder->build_topping();
	}
};

void main()
{
	setlocale(LC_ALL, "");
	Cook cook;
	HawaiianPizzaBuilder hawaii_pb;
	BBQPizzaBuilder bbq_pb;
	MargaretBuilder margaret_pb;

	cook.make_pizza(&hawaii_pb);
	cook.open_pizza();

	cook.make_pizza(&bbq_pb);
	cook.open_pizza();
}