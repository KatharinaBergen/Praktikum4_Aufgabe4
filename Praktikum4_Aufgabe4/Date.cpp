/*
   Author: Kat Bergen
   v01 25.6.2020

	cpp for Date class

	PAD1 P4A4
 */

#include "Date.h"
#include "MyError.h"


 // Konstruktoren
Date::Date() : year{ 2020 }, month{ Date::Month::Jun }, day{ 29 }
{}
Date::Date(int y, Month m, int d) : year{ y }, month{ m }, day{ d }
{ }

bool Date::check() const
{
	bool isLeap{ isLeapYear() };

	if (year > 2020) return false;
	else if (month < 1 || month > 12) return false;
	else if (day < 1) return false;
	else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31) return false;
	else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
	else if (month == 2 && isLeap == false && day > 28) return false;
	else if (month == 2 && isLeap == true && day > 29) return false;
	else return true;
}

bool Date::isLeapYear() const
{
	/*Ein Jahr ist ein Schaltjahr, wenn die Jahreszahl restlos durch 4 teilbar ist.
	Ein Jahr ist kein Schaltjahr, wenn es durch 4 und 100 restlos teilbar ist.
	Ein Jahr ist ein Schaltjahr, wenn es sowohl durch 4, durch 100 und durch 400 teilbar ist*/

	bool first{ year % 4 == 0 };
	bool second{ year % 4 == 0 && year % 100 == 0 };
	bool third{ year % 4 == 0 && year % 100 == 0 && year % 400 == 0 };

	bool result{ false };

	if (first) result = true;
	if (result && second) result = false;
	if (!result && third) result = true;

	return result;
}

int Date::getDay() const
{
	return day;
}

Date::Month Date::getMonth() const
{
	return month;
}

std::string Date::getMonthString(int& month) const
{
	std::vector<std::string> validMonths{ "Jan", "Feb", "Mrz", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez" };

	return validMonths[month];
}

int Date::getYear() const
{
	return year;
}

int Date::compareToDate(const Date& other) const
{
	if (other.year == year && other.month == month && other.day == day) return 0;
	else if (other.year > year) return -1;
	else if (other.year == year && other.month > month) return -1;
	else if (other.year == year && other.month == month && other.day > day) return -1;
	else if (other.year < year) return 1;
	else if (other.year == year && other.month < month) return 1;
	else if (other.year == year && other.month == month && other.day < day) return 1;

	else return -99; //error
}

// auch schreibender Zugriff:
void Date::change_days(const int& amountOfDays)
{
	int month_{ month };

	// decrement
	if (amountOfDays < 0)
	{
		if (day > 1)
		{
			day -= 1;
			change_days(amountOfDays + 1);
		}
		else if (month > 1 && day == 1)
		{
			month = operator--(month);
			day = maxDay();
			change_days(amountOfDays + 1);
		}
		else if (month == 1 && day == 1)
		{
			year -= 1;
			month = operator--(month);
			day = maxDay();
			change_days(amountOfDays + 1);
		}
	}

	// increment
	else if (amountOfDays > 0)
	{
		if (day < maxDay())
		{
			day += 1;
			change_days(amountOfDays - 1);
		}
		else if (month < 12 && day == maxDay())
		{
			month = operator++(month);
			day = 1;
			change_days(amountOfDays - 1);
		}
		else if (month == 12 && day == maxDay())
		{
			year += 1;
			month = operator++(month);
			day = 1;
			change_days(amountOfDays - 1);
		}
	}

	else; //else amount of days is 0 and nothing to be done.
}

int Date::maxDay() const
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) return 31;
	else if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
	else if (month == 2 && isLeapYear() == false) return 28;
	else if (month == 2 && isLeapYear() == true) return 29;

	//else error
}

Date::Month& operator++(Date::Month& mon)
{ // Praefix Inkrement Operator ++ ueberladen (KEIN Klassenmember)
	mon = (mon == Date::Dez) ? Date::Jan : Date::Month(mon + 1);
	return mon;
}

Date::Month& operator--(Date::Month& mon)
{ // Praefix Inkrement Operator -- ueberladen (KEIN Klassenmember)
	mon = (mon == Date::Jan) ? Date::Dez : Date::Month(mon - 1);
	return mon;
}

ostream& operator<<(ostream& os, const Date& d)
{ // Stream Insertion Operator << ueberladen (KEIN Klassenmember)
	int month{ d.getMonth() };
	return os << d.getYear() << '-' << d.getMonthString(month) << '-' << std::setfill('0') << std::setw(2) << d.getDay() << std::endl;
}

std::vector<int> run_test(std::vector<Date> inputDates, std::vector<bool> isLeap, std::vector<bool> checkedDatedIs, std::vector<int> dateIncrement, std::vector<Date> expectedDates)
{
	std::vector<int> failedTests{};
	for (int i{ 0 }; i < inputDates.size(); i++)
	{
		bool passedTest{ true };
		Date testDate{ inputDates.at(i) };

		if (testDate.isLeapYear() == isLeap.at(i)) ; //check isLeapYear() function
		else passedTest = false;

		if (passedTest == true)						//check check() function
		{
			if (testDate.check() == checkedDatedIs.at(i)); 
			else passedTest = false;
		}

		if (passedTest == true)								//check change_days() function
		{
			testDate.change_days(dateIncrement.at(i));
			if (testDate.compareToDate(expectedDates.at(i)) == 0) ;
			else passedTest = false;
		}

		if (passedTest == false) failedTests.push_back(i);
	}

	return failedTests;
}

void testDateClass()
{
	std::vector<Date> inputDates{};
	std::vector<bool> isLeap{};
	std::vector<bool> checkedDatedIs{};
	std::vector<int> dateIncrement{};
	std::vector<Date> expectedDates{};

	Date in1{ 2019, Date::Month::Jun, 20 }; //Date 1 to be tested
	inputDates.push_back(in1);
	isLeap.push_back(false);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(3);
	Date exp1{ 2019, Date::Month::Jun, 23 };
	expectedDates.push_back(exp1);

	Date in2{ 2020, Date::Month::Jun, 20 }; //Date 2 to be tested
	inputDates.push_back(in2);
	isLeap.push_back(true);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(-3);
	Date exp2{ 2020, Date::Month::Jun, 17 };
	expectedDates.push_back(exp2);

	Date in3{ 2020, Date::Month::Jun, 20 }; //Date 3 to be tested
	inputDates.push_back(in3);
	isLeap.push_back(true);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(20);
	Date exp3{ 2020, Date::Month::Jul, 10 };
	expectedDates.push_back(exp3);

	Date in4{ 2020, Date::Month::Jun, 20 }; //Date 4 to be tested
	inputDates.push_back(in4);
	isLeap.push_back(true);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(-25);
	Date exp4{ 2020, Date::Month::Mai, 26 };
	expectedDates.push_back(exp4);

	Date in5{ 2020, Date::Month::Feb, 29 }; //Date 5 to be tested
	inputDates.push_back(in5);
	isLeap.push_back(true);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(2);
	Date exp5{ 2020, Date::Month::Mrz, 2};
	expectedDates.push_back(exp5);

	Date in6{ 2019, Date::Month::Feb, 29 }; //Date 6 to be tested
	inputDates.push_back(in6);
	isLeap.push_back(false);
	checkedDatedIs.push_back(false);
	dateIncrement.push_back(0);
	Date exp6{ 2019, Date::Month::Feb, 29 };
	expectedDates.push_back(exp6);

	Date in7{ 2019, Date::Month::Feb, 28 }; //Date 7 to be tested
	inputDates.push_back(in7);
	isLeap.push_back(false);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(1);
	Date exp7{ 2019, Date::Month::Mrz, 1 };
	expectedDates.push_back(exp7);

	Date in8{ 2019, Date::Month::Mrz, 2 }; //Date 8 to be tested
	inputDates.push_back(in8);
	isLeap.push_back(false);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(-3);
	Date exp8{ 2019, Date::Month::Feb, 27 };
	expectedDates.push_back(exp8);

	Date in9{ 2019, Date::Month::Jan, 2 }; //Date 9 to be tested
	inputDates.push_back(in9);
	isLeap.push_back(false);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(-5);
	Date exp9{ 2018, Date::Month::Dez, 28 };
	expectedDates.push_back(exp9);

	Date in10{ 2019, Date::Month::Dez, 20 }; //Date 10 to be tested
	inputDates.push_back(in10);
	isLeap.push_back(false);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(20);
	Date exp10{ 2020, Date::Month::Jan, 9 };
	expectedDates.push_back(exp10);

	Date in11{ 2019, Date::Month::Dez, 20 }; //Date 11 to be tested
	inputDates.push_back(in11);
	isLeap.push_back(false);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(300);
	Date exp11{ 2020, Date::Month::Okt, 15 };
	expectedDates.push_back(exp11);

	Date in12{ 2019, Date::Month::Dez, 20 }; //Date 12 to be tested
	inputDates.push_back(in12);
	isLeap.push_back(false);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(-2000);
	Date exp12{ 2014, Date::Month::Jun, 29 };
	expectedDates.push_back(exp12);

	Date in13{ 2000, Date::Month::Dez, 20 }; //Date 13 to be tested
	inputDates.push_back(in13);
	isLeap.push_back(true);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(1500);
	Date exp13{ 2005, Date::Month::Jan, 28 };
	expectedDates.push_back(exp13);

	Date in14{ 2000, Date::Month::Dez, 20 }; //Date 14 to be tested
	inputDates.push_back(in14);
	isLeap.push_back(true);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(-1500);
	Date exp14{ 1996, Date::Month::Nov, 11 };
	expectedDates.push_back(exp14);

	Date in15{ 2000, Date::Month::Dez, 50 }; //Date 15 to be tested
	inputDates.push_back(in15);
	isLeap.push_back(true);
	checkedDatedIs.push_back(false);
	dateIncrement.push_back(0);
	Date exp15{ 2000, Date::Month::Dez, 50 };
	expectedDates.push_back(exp15);

	Date in16{ 2021, Date::Month::Dez, 50 }; //Date 16 to be tested
	inputDates.push_back(in16);
	isLeap.push_back(false);
	checkedDatedIs.push_back(false);
	dateIncrement.push_back(0);
	Date exp16{ 2021, Date::Month::Dez, 50 };
	expectedDates.push_back(exp16);

	Date in17{ 0001, Date::Month::Jan, 2 }; //Date 17 to be tested
	inputDates.push_back(in17);
	isLeap.push_back(false);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(0);
	Date exp17{ 0001, Date::Month::Jan, 2 };
	expectedDates.push_back(exp17);

	Date in18{ 0001, Date::Month::Jan, 2 }; //Date 18 to be tested
	inputDates.push_back(in18);
	isLeap.push_back(false);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(-2);
	Date exp18{ 0000, Date::Month::Dez, 31 };
	expectedDates.push_back(exp18);

	Date in19{ 0000, Date::Month::Jan, 2 }; //Date 19 to be tested
	inputDates.push_back(in19);
	isLeap.push_back(true);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(-2);
	Date exp19{ -0001, Date::Month::Dez, 31 };
	expectedDates.push_back(exp19);

	Date in20{ 1000, Date::Month::Jan, 2 }; //Date 20 to be tested
	inputDates.push_back(in20);
	isLeap.push_back(false);
	checkedDatedIs.push_back(true);
	dateIncrement.push_back(-2);
	Date exp20{ 999, Date::Month::Dez, 31 };
	expectedDates.push_back(exp20);

	std::vector<int> failedTests{ run_test(inputDates, isLeap, checkedDatedIs, dateIncrement, expectedDates) };

	for (int i{ 0 }; i < failedTests.size(); i++)
	{
		std::cout << "Test number " << failedTests.at(i) << " has failed.";
	}

	if (failedTests.empty()) std::cout << "All tests were successful." << std::endl;

}

