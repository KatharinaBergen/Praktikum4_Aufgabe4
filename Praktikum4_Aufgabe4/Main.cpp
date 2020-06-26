/*
   Author: Kat Bergen
   v01 25.6.2020

    Mini Calender program to read in Dates, check date is valid and option to increment or decrement date by number of days.

    PAD1 P4A4
 */

#include <iostream>
#include "Date.h"
#include <string>
#include <vector>
#include <iomanip>  
using std::cout;

int main() try
{
    testDateClass();

    Date today{ 2020, Date::Month::Jun, 2 };
    operator<<(cout, today);
   
    return 0;
}

catch (Date::Invalid&)
{
    std::cerr << "Ausnahme: Datum ungueltig";
    return -3;
}

catch (std::exception& e)
{
    std::cerr << "Ausnahme: " << e.what();
    return -2;
}

catch (...)
{
    std::cerr << "Unbekannte Ausnahme";
    return -1;
}
