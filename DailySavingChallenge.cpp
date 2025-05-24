/*
 * DailySavingChallenge
 * Copyright (C) 2025 David A. Cummings
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <ctime>
#include <cstdint>

#define ABSOLUTE_ARGS 3

#ifndef START_DAY
	#define START_DAY 0
#endif
#ifndef START_MONTH
	#define START_MONTH 0
#endif

enum MONTH{
	JAN=0,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC,UND
};

int month[12]{
	31,	/* Jan */
	28,	/* Feb (Non-leap Year) */
	31,	/* Mar */
	30,	/* Apr */
	31,	/* May */
	30,	/* Jun */
	31,	/* Jul */
	31,	/* Aug */
	30,	/* Sep */
	31,	/* Oct */
	30,	/* Nov */
	31	/* Dec */
};

struct compact_date{
	int dd;
	int mm;
};

/***********************************************************************
 * Func.:	get_current_year
 * Desc.:	Get current year from system
 **********************************************************************/
 
int get_current_year(){
	std::time_t timestamp{ std::time( nullptr) };
	struct tm datetime = *localtime( &timestamp );

	return datetime.tm_year+1900;
}

/***********************************************************************
 * Func.:	is_leap_year
 * Desc.:	Adjust months if challenge is over a leap year.
 **********************************************************************/

int is_leap_year( int year ){
	if( !( ( year % 4 ) && (year % 100 ) )
	|| !( ( year % 100 ) && (year % 400 ) ) ) return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

/***********************************************************************
 * Func.:	normalise_date
 * Desc.:	Translate challenge day to dd/mm.
 **********************************************************************/

compact_date normalise_date( const int dd ){
	int day{ dd },i{0};

	while( day > month[ i ] ){
		if( day <= month[i] ) break;
		else day-=month[i];

		i=i>=DEC?JAN:++i;
	}

	/***************************************************************
	 * Offset 'i' (month) to account for 0-index array and round
	 * to nearest month if greater than December.
	 **************************************************************/

	return compact_date{ day,++i };
}

/***********************************************************************
 * Func.:	normalise_date
 * Desc.:	Translate date to challenge days' consequtive number.
 **********************************************************************/

int normalise_date( const int dd,const int mm ){
	int day_no{dd};

	for( int i{0};i<mm;++i )
		day_no+=month[i];

	return day_no;
}

/***********************************************************************
 * Func.:	normalise_date
 * Desc.:	Translate date to challenge days' consequtive number.
 **********************************************************************/

int normalise_date( const compact_date date ){
	int day_no{date.dd};

	for( int i{0};i<date.mm;++i )
		day_no+=month[i];

	return day_no;
}

/***********************************************************************
 * Func.:	get_month
 * Desc.:	Get month name from integer value.
 **********************************************************************/

std::string get_month( const int mm ){
	switch( mm ){
		case 1: return "January";
		case 2: return "February";
		case 3: return "March";
		case 4: return "April";
		case 5: return "May";
		case 6: return "June";
		case 7: return "July";
		case 8: return "August";
		case 9: return "September";
		case 10: return "October";
		case 11: return "November";
		case 12: return "December";
	}
	
	return "Undecimber";
}

/***********************************************************************
 * Func.:	get_month
 * Desc.:	Get month enum from string value.
 **********************************************************************/

MONTH get_month( const std::string mn ){
	if( "JAN" == mn ) return JAN;
	if( "FEB" == mn ) return FEB;
	if( "MAR" == mn ) return MAR;
	if( "APR" == mn ) return APR;
	if( "MAY" == mn ) return MAY;
	if( "JUN" == mn ) return JUN;
	if( "JUL" == mn ) return JUL;
	if( "AUG" == mn ) return AUG;
	if( "SEP" == mn ) return SEP;
	if( "OCT" == mn ) return OCT;
	if( "NOV" == mn ) return NOV;
	if( "DEC" == mn ) return DEC;

	return UND;
}

/***********************************************************************
 * Func.:	get_day_part
 * Desc.:	Find days' ordinal suffix.
 **********************************************************************/

std::string get_day_part( const int dd ){
	switch( dd ){
		case 1:
		case 21:
		case 31:
			return "st";
		case 2:
		case 22:
			return "nd";
		case 3:
		case 23:
			return "rd";
	}
	
	return "th";
}

/***********************************************************************
 * Func.:	normalise_date
 * Desc.:	Translate date to challenge days' consequtive number.
 **********************************************************************/

compact_date normalise_date( std::string str ){
	if( str.size() < 4 || str.size() > 5 ) return compact_date{ 0,UND };

	std::string d{ str.substr( 0,str.length()-3 ) };
	std::string m{ str.substr( str.length()-3,str.length() ) };

	int mi{ get_month( m ) };
	int di{ std::stoi( d ) };

	if( di > month[ mi ] ) return compact_date{ 0,UND };

	return compact_date{ di,mi };
}

/***********************************************************************
 * Func.:	calc_amt
 * Desc.:	Calculate o(2n+1)
 **********************************************************************/

int calc_amt( const int day,const int total_days ){
	int retval{day},intermediate{day};
	
	for( int i{0}; i<total_days; ++i )
		retval+=(++intermediate);

	return retval;
}

/***********************************************************************
 * Func.:	get_arg
 * Desc.:	Find arguement number.
 **********************************************************************/

int get_arg( int &argc, char *argv[],std::string strv ){
	for( int i{ 0 };i<argc; ++i ){
		if( std::string( argv[ i ] )==strv ) return i;
	}
	
	return EXIT_SUCCESS;
}

/***********************************************************************
 * Func.:	is_number
 * Desc.:	Is every char in numerical range?
 **********************************************************************/
 
int is_number( std::string& value ){
	for( auto character: value )
		if( !std::isdigit( character ) ) return EXIT_FAILURE;
	
	return EXIT_SUCCESS;
}

/***********************************************************************
 * Func.:	is_date
 * Desc.:	Check string is valid date format.
 **********************************************************************/
 
int is_date( std::string& value ){
	compact_date tdate{ normalise_date( value ) };

	if( tdate.mm==UND ) return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

/***********************************************************************
 * Func.:	as_currency
 * Desc.:	Format integer to currency and return as text.
 **********************************************************************/
 
std::string as_currency( int v ){
	std::stringstream retstr;
	retstr << std::fixed << std::setprecision( 2 ) \
	<< static_cast< float >( v*0.01 );

	return retstr.str();
}

/***********************************************************************
 * Func.:	as_written_date
 * Desc.:	Format compact_date type to written date.
 **********************************************************************/
 
std::string as_written_date( compact_date v ){
	std::stringstream retstr;
	retstr << v.dd << get_day_part( v.dd ) << ' ' \
	<< get_month( v.mm );

	return retstr.str();
}

/***********************************************************************
 * Hangar.
 **********************************************************************/
 
int main( int argc,char *argv[] ) {
	using std::string;

	/***************************************************************
	 * Without values print details on how to use program and exit.
	 **************************************************************/

	if( argc < ABSOLUTE_ARGS ){
		std::cout << "Usage: " << argv[0] \
			<< " <challenge-day> <number-of-days>\n" \
			<< "Parameters can be either: \n"
			<< "Integral where the first parameter is " \
			<< "the first number of days and the second " \
			<< "how many days you want to calculate." \
			<< "Or, presented as a date format DDMMM " \
			<< "e.g 26JAN.\n";
		return EXIT_FAILURE;
	}

	string \
	str_current	{ argv[1] },
	str_total	{ argv[2] };

	int \
	current_day,
	duration;

	/***************************************************************
	 * Validate first passed argument.
	 **************************************************************/

	if( EXIT_SUCCESS==is_number( str_current ) ){
		current_day=std::stoi( str_current );
		std::cout << current_day << '\n';
	}
	else
	if( EXIT_SUCCESS==is_date( str_current ) ){
		current_day=normalise_date( normalise_date( str_current ) );
		current_day-=START_DAY;
	}
	else{
		std::cout << "Error: incompatible date type on 1st param.\n";
		return EXIT_FAILURE;
	}

	/***************************************************************
	 * Validate second passed argument.
	 **************************************************************/

	if( EXIT_SUCCESS==is_number( str_total ) )
		duration=std::stoi( str_total );
	else
	if( EXIT_SUCCESS==is_date( str_total ) ){
		duration=normalise_date( normalise_date( str_total ) );
		duration-=current_day+START_DAY;
	}
	else{
		std::cout << "Error: incompatible date type on 2nd param.\n";
		return EXIT_FAILURE;
	}

	int year_length{ 365+is_leap_year( get_current_year() ) };

	if( duration < 0 ) duration+=year_length;

	/***************************************************************
	 * Reuse days var. for checking final day value.
	 **************************************************************/

	int \
	total_days	{ duration+current_day },
	total		{ calc_amt( current_day+1,duration ) },
	total_overall	{ calc_amt( 1,( total_days ) ) };

	/***************************************************************
	 * The challenge doesn't go on for more than a year;
	 * check dates will align.
	 **************************************************************/

	if( current_day > year_length || total_days > year_length \
	|| current_day < 0 || total_days < 0 ){
		std::cout << "Error: days cannot exceed a year.\n";
		return EXIT_FAILURE;
	}

	/***************************************************************
	 * Align dates by offsetting the challenge days with a beginning
	 * date (use a timeline.)
	 **************************************************************/

	int \
	start_day{ normalise_date( START_DAY,START_MONTH ) };

	total_days+=start_day;
	current_day+=start_day;

	/***************************************************************
	 * Check and adjust dates and duration for leap years.
	 **************************************************************/

	const int leap_day{ normalise_date( 29,FEB ) };

	if( current_day<leap_day && total_days>leap_day \
	&& is_leap_year( get_current_year() ) ){
		++duration;
		++month[ FEB ];
	}

	if( current_day>=leap_day && total_days>leap_day \
	&& is_leap_year( get_current_year()+1 ) ){
		++month[ FEB ];
	}

	const compact_date \
	ddmm{ normalise_date( total_days ) },
	cddmm{ normalise_date( current_day ) };

	/***************************************************************
	 * Output values to console.
	 **************************************************************/

	std::cout << "\e[0mBetween \e[0;96m" \
		<< as_written_date( cddmm ) << "\e[0m and \e[0;96m" \
		<< as_written_date( ddmm ) << "\e[0;96m" \
		<< "\e[0m you will need \e[0;92m£" \
		<< as_currency( total ) \
		<< "\e[0m in your current account.\n" \
		<< "Giving you a total of \e[0;97m\e[42m £" \
		<< as_currency( total_overall ) \
		<< " \e[0m saved altogether!\n";

	return EXIT_SUCCESS;
}
