#pragma once
#include<iostream>
#include<string>
#include"clsDate.h"

using namespace std;

class clsPeriod
{
private:
	
	clsDate StartDate;
	clsDate EndDate;

	enum enComparingDate { eBefore = -1, eEqual = 0, eAfter = 1 };

public:
	//clsPeriod()
	//{
	//	clsDate()
	//}

	short ReadNumber(string Message)
	{
		short Number;
		cout << Message << endl;
		cin >> Number;
		return Number;
	}

	static clsDate ReadDate()
	{
		clsDate cDate;
		clsPeriod cPeriod;

		cDate.Day = cPeriod.ReadNumber("Please enter day : ");
		cDate.Month = cPeriod.ReadNumber("Please enter Month : ");
		cDate.Year = cPeriod.ReadNumber("Please enter year : ");

		return cDate;
	}

	void PeriodStart()
	{
		StartDate = ReadDate();
	}

	void PeriodEnd()
	{
		EndDate = ReadDate();
	};

	static bool IsPeriodOverLap(clsPeriod sPeriod1, clsPeriod sPeriod2)
	{
		if (
			clsDate::ComparingDateAndDate2(sPeriod1.EndDate, sPeriod2.StartDate) == enComparingDate::eBefore
			||
			clsDate::ComparingDateAndDate2(sPeriod1.StartDate, sPeriod2.EndDate) == enComparingDate::eAfter
			)
			return false;

		else
			return true;
	}

	bool IsPeriodOverLap(clsPeriod sPeriod)
	{
		return IsPeriodOverLap(*this, sPeriod);
	}

	static int PeriodLength(clsPeriod sPeriod, bool IncludingEndDate = false)
	{
		return clsDate::GetDifferenceInDaysBetweenTwoDates(sPeriod.StartDate, sPeriod.EndDate, IncludingEndDate);
	}

	int PeriodLength(bool IncludingEndDate = false)
	{
		return PeriodLength(*this, IncludingEndDate);
	}

	static bool IsDateExistInPeriod(clsPeriod Period, clsDate sDate)
	{
		return !((clsDate::ComparingDateAndDate2(sDate, Period.StartDate) == enComparingDate::eBefore)
			|| (clsDate::ComparingDateAndDate2(sDate, Period.EndDate)) == enComparingDate::eAfter);
		//	return false;
		//else
		//	return true;
	}

	bool IsDateExistInPeriod(clsDate cDate)
	{
		return IsDateExistInPeriod(*this, cDate);
	}

	static short DaysOverlapCounter(clsPeriod Period1, clsPeriod Period2)
	{
		int LengthPeriod1 = PeriodLength(Period1);
		int LengthPeriod2 = PeriodLength(Period2);
		clsPeriod copyPeriod1, copyPeriod2;
		short OverlapCounter = 0;

		if (!IsPeriodOverLap(Period1, Period2))
			return 0;

		if (LengthPeriod1 < LengthPeriod2)
		{
			while (clsDate::IsDateBeforeDate2(Period1.StartDate ,Period1.EndDate))
			{
				if (IsDateExistInPeriod(Period1, Period2.StartDate))
					OverlapCounter++;
				copyPeriod1.StartDate.IncreasingDateOneDay();
			}
		}
		else
		{
			while (clsDate::IsDateBeforeDate2(Period1.StartDate, Period2.EndDate))
			{
				if (IsDateExistInPeriod(Period2, Period1.StartDate))
					OverlapCounter++;
				copyPeriod2.StartDate.IncreasingDateOneDay();
			}
		}
		return OverlapCounter;
	}

	short DaysOverlapCounter(clsPeriod Period2)
	{
		return DaysOverlapCounter(*this, Period2);
	}
};

