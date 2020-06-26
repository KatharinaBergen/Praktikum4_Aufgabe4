/*
   Author: Kat Bergen
   v01 25.6.2020

    header for Date class

    PAD1 P4A4
 */

#ifndef G7_DATE_H
#define G7_DATE_H

#include <iostream>
using std::ostream;
#include <iomanip>
#include <vector>
#include <string>


class Date
{
public:
    class Invalid {}; // zeigt Ausnahmen an
    enum Month { Jan = 1, Feb, Mrz, Apr, Mai, Jun, Jul, Aug, Sep, Okt, Nov, Dez }; // symbol. Konstanten für die Monate
 
    Date(); // Standardkonstruktor
    Date(int y, Month m, int d); // Konstruktor
    
    // nur lesender Zugriff (const):
    int compareToDate(const Date&) const;
    bool isLeapYear() const; //Methode liefert Leap year true or false
    bool check() const; // Methode, liefert true bei gueltigem Datum
    int maxDay() const;    
    int getDay() const;
    Date::Month getMonth() const;
    std::string getMonthString(int& month) const;
    int getYear() const;
    
    
    // auch schreibender Zugriff:
    void change_days(const int&);

private:
    int    year; // Jahr
    Month  month; // Monat
    int    day; // Tag
    
};


std::vector<int> run_test(std::vector<Date> inputDates, std::vector<bool> isLeap, std::vector<bool> checkedDatedIs, std::vector<int> dateIncrement, std::vector<Date> expectedDates);
void testDateClass();

Date::Month& operator++(Date::Month&); // Praefix Inkrement Operator ++ ueberladen
Date::Month& operator--(Date::Month&); // Praefix Inkrement Operator -- ueberladen
ostream& operator<<(ostream&, const Date&);

#endif // G7_DATE_H
