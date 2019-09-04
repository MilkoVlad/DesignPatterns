#include<iostream>
#include<string>
#include<memory>
#include<unordered_map>
using namespace std;

class Record //Plyer
{
public:
	virtual ~Record()
	{

	}
	virtual void info() = 0;
	virtual unique_ptr<Record> clone() = 0;
};

class CarRecord :public Record
{
	string m_car_name;
	int m_id;
public:
	CarRecord(const string& m_car_name, int m_id): m_car_name(m_car_name), m_id(m_id)
	{

	}
	~CarRecord()
	{

	}
	void info()
	{
		cout << "Car record:\n" 
			<< "Name:\t " << m_car_name 
			<< "Number:\t" << this << endl;
	}
	unique_ptr<Record> clone()
	{
		return make_unique<CarRecord>(*this);
	}
};

class BikeRecord :public Record
{
	string name;
	int id;
public:
	BikeRecord (const string& name, int id): name(name), id(id)
	{

	}
	~BikeRecord()
	{

	}
	void info()
	{
		cout << "Bike record:\n"
			<< "Name:\t " << name
			<< "Number:\t" << this << endl;
	}
	unique_ptr<Record> clone()
	{
		return make_unique<BikeRecord>(*this);
	}
};

class PersonalRecord :public Record
{
	string name;
	int id;
public:
	PersonalRecord(const string& name, int id): name(name), id(id)
	{

	}
	~PersonalRecord()
	{

	}
	void info()
	{
		cout << "Personal record:\n"
			<< "Name:\t " << name
			<< "Number:\t" << this << endl;
	}
	unique_ptr<Record> clone()
	{
		return make_unique<PersonalRecord>(*this);
	}
};

enum RecordType
{
	CAR,
	BIKE,
	PERSONAL
};

class RecordFactory
{
	unordered_map<RecordType, unique_ptr<Record>, hash<int>>records;
public:
	RecordFactory()
	{
		records[CAR] = make_unique<CarRecord>("Audi RS6 ", 123);
		records[BIKE] = make_unique<BikeRecord>("Harley Davitson ", 666);
		records[PERSONAL] = make_unique<PersonalRecord>("Vasiliy ", 777);
	}

	unique_ptr<Record> CreateRecord(RecordType type)
	{
		return records[type]->clone();
	}
};



void main()
{
	setlocale(LC_ALL, "ru");
	RecordFactory factory;
	unique_ptr<Record> record[] =
	{
		factory.CreateRecord(CAR),
		factory.CreateRecord(BIKE),
		factory.CreateRecord(PERSONAL),
		factory.CreateRecord(BIKE)
	};

	for (int i = 0; i < sizeof(record)/sizeof(unique_ptr<Record>); i++)
	{
		record[i]->info();
	}
}





