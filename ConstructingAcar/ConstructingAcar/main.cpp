#include<iostream>
using namespace std;

#define delimiter "\n---------------------------\n"

/*
	TODO:
	1. Вынести классы Tank и Engine в отдельные файлы;
	2. Написать класс Car, научить машину заводить и останавливать двигатель,
	   а также расходовать топливо, когда двигатель заведен.
*/

class Tank
{
	unsigned int volume;
	double fuel;
public:
	int get_volume()const
	{
		return volume;
	}
	double get_fuel()const
	{
		return this->fuel;
	}
private:
	void set_volume(unsigned int volume)
	{
		if (volume >= 20 && volume <= 60)
			this->volume = volume;
		else
			throw exception("Error: bad tank volume");
	}
public:
	void fill(double fuel)
	{
		if (fuel >= 0 && fuel <= volume)
			this->fuel = fuel;
		else if (fuel > volume)
			this->fuel = volume;
		else throw exception("Error: No benzin in Ukraine");
		cout << "Filling..." << endl;
	}

	//			Constructors:
	Tank(int volume = 40) :volume(volume >= 20 && volume <= 60 ? volume : 40), fuel(0)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	~Tank()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	void info()
	{
		cout << "Volume:\t" << volume << " liters;\n";
		cout << "Fuel:\t" << fuel << " liters;\n";
	}
};

class Engine
{
	double volume;		//объем двигателя
	unsigned int power;	//мощность
	double consumption;	//расход топлива
	bool started;	//состояние - запущен/остановлен
public:
	double get_volume()const
	{
		return volume;
	}
	unsigned int get_power()const
	{
		return power;
	}
	double get_consumption()const
	{
		return consumption*10000;
	}
	bool is_started() const
	{
		return this->started;
	}
	//			Constructors:
	Engine(double volume, unsigned int power, double consumption)
	{
		if (volume >= 1 && volume <= 8)
			this->volume = volume;
		else
			throw exception("Error: Bad engine volume");
		if (power < 1000)
			this->power = power;
		else
			throw exception("Error: Bad engine power");
		if (consumption >= 3 && consumption <= 20)
			this->consumption = consumption/10000;
		else
			throw exception("Error:Bad consumption");
		this->started = false;
		cout << "EConstructor:\t" << this << endl;
	}
	~Engine()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	//			Methods:
	void start()
	{
		started = true;
	}
	void stop()
	{
		started = false;
	}

	void info()
	{
		cout << "Volume:\t" << volume << " liters;\n";
		cout << "Power:\t" << power << " hp;\n";
		cout << "Consumption:\t" << consumption * 10000 << " l/100km;\n";
		cout << (started ? "Started:" : "Stopped") << "\t" << endl;
	} 
};

void main()
{
	setlocale(LC_ALL, "");
	try
	{
		Tank tank(500);
		tank.info();
		tank.fill(20);
		tank.info();
		cout << delimiter << endl;
		Engine engine(3, 300, 15);
		engine.info();
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
}