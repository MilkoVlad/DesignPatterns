#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;

#define delimiter "\n---------------------------\n"

/*
	TODO:
	1. Вынести классы Tank и Engine в отдельные файлы;
	2. Написать класс Car, научить машину заводить и останавливать двигатель,
	   а также расходовать топливо, когда двигатель заведен.
*/

/*
	ternary operator:
	condition ? code1 : code2;
	condition1 ? code1 : condition2 ? code2 : condition3 ? code3 : default_code;
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
	double fuel_level()const
	{
		return this->fuel;
	}
	double get_fuel(double consumption_per_second)
	{
		fuel -= consumption_per_second;
		if (fuel < 0)fuel = 0;
		return fuel;
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
	Tank(int volume = 40) :volume(volume >= 20 && volume <= 90 ? volume : 40), fuel(0)
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
		return consumption;
	}
	double consumption_per_second() const
	{
		return consumption / 10000;
	}
	bool is_started() const
	{
		return this->started;
	}
	bool is_stopped() const
	{
		return !this->started;
	}
	//			Constructors:
	Engine(double volume = 2.0, unsigned int power = 210, double consumption = 8)
	{
		if (volume >= 1 && volume <= 8)
			this->volume = volume;
		else
			throw exception("Error: Bad engine volume");
		if (power < 1000)
			this->power = power;
		else
			throw exception("Error: Bad engine power");
		if (consumption >= 3 && consumption <= 50)
			this->consumption = consumption;
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
		cout << "Consumption:\t" << consumption << " l/100km;\n";
		cout << (started ? "Started:" : "Stopped") << "\t" << endl;
	}


};

class Car
{
	Tank tank;
	Engine engine;
	bool started;	//Заведена/остановлена
	unsigned int speed;
	unsigned int max_speed;
	unsigned int acceleration;
public:
	const Tank& get_tank() const
	{
		return tank;
	}
	const Engine& get_engine() const
	{
		return engine;
	}
	bool is_started() const
	{
		return started;
	}
	//			Constructors:
	Car
	(
		const Engine& engine, const Tank& tank,
		unsigned int max_speed, unsigned int acceleration
	)
	{
		this->engine = engine;
		this->tank = tank;
		this->speed = 0;
		this->max_speed = max_speed;
		this->acceleration = acceleration;
		cout << "CConstroctor:\t" << this << endl;
	}
	~Car()
	{
		cout << "CDestroctor:\t" << this << endl;
	}

	void fill(double fuel)
	{
		tank.fill(fuel);
	}

	void start()
	{
		if (tank.fuel_level() > 0)
		{
			engine.start();
			idle();
		}
		else
		{
			cout << "No fuel" << endl;
		}
	}

	void stop()
	{
		engine.stop();
	}

	void idle()
	{
		//Холостой ход двигателя.
		char key;
		if (!engine.is_started()) return;
		while (tank.fuel_level() > 0 || speed > 0/* && engine.is_started()*/)
		{
			if (engine.is_started())tank.get_fuel(engine.consumption_per_second());
			Sleep(1000);
			if (tank.fuel_level() <= 0)engine.stop();
			if (kbhit())
			{
				key = getch();
				switch (key)
				{
				case 13:
					if (engine.is_started())
						engine.stop();
					if (engine.is_stopped())
						engine.start();
					//status();
					//return;
					break;
				case 27: return;
				case 'w': speed_up(); break;
				case 's': breaking(5); break;
				case ' ': breaking(20); break;
				}
				cout << (int)key << endl;
			}
			status();
			if (speed > 0)speed--;
		}
	}

	void speed_up()
	{
		if (engine.is_started() && speed < max_speed)speed += acceleration;
	}

	void breaking(int deceleration)
	{
		if (speed > 0 && speed <= max_speed)speed -= deceleration;
		if (speed< 0 || speed > max_speed)speed = 0;
	}

	void status() const
	{
		system("CLS");
		cout << "Fuel:\t" << tank.fuel_level() << " liters.\n";
		cout << "Engine " << (engine.is_started() ? "started" : "stopped") << endl;
		cout << "Speed:\t" << speed << " km/h." << endl;
		if (tank.fuel_level() < 5)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 0x0F);
			cout << "Мало топлива, заправьтесь!!!" << endl;
			SetConsoleTextAttribute(hConsole, 0x0A);
		}
		//cout << "\n----------------------------------------\n";
	}

	void info()
	{
		cout << "Engine:\n";
		engine.info();
		cout << "Tank:\n";
		tank.info();
	}
};

void main()
{
	setlocale(LC_ALL, "");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 0x0A);
	try
	{
		/*Tank tank(500);
		tank.info();
		tank.fill(20);
		tank.info();
		cout << delimiter << endl;
		Engine engine(3, 300, 15);
		engine.info();*/

		Car audi(Engine(2.0, 240, 40), Tank(70), 250, 20);
		audi.fill(5.01);
		//audi.info();
		//audi.start();

		char key = 0;
		do
		{
			key = getch();
			switch (key)
			{
			case 13: audi.start(); break;
			case 'w':audi.speed_up(); break;
				/*case 's':
				case ' ':audi.breaking(10); break;*/
			}
		} while (key != 27);
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
}