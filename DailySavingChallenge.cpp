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

#define ABSOLUTE_ARGS 3

#ifndef START_DAY
	#define START_DAY 0
#endif
#ifndef START_MONTH
	#define START_MONTH 0
#endif

constexpr int month[12]{
	31,	/* Jan */
	28,	/* Feb */
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
	int dd,mm;
};

/***********************************************************************
 * Func.:	normalise_date
 * Desc.:	Translate challenge day to dd/mm.
 **********************************************************************/
 
compact_date normalise_date( const int dd ){
	int day{ dd },i{0};
	while( i < 12 ){
		day-=month[i];
		if( day <= month[i++] ) break;
	}

	/***************************************************************
	 * Offset 'i' (month) to account for 0-index array and round
	 * to nearest month if greater than December.
	 **************************************************************/

	i=(i++)>12?i-12:i;

	return compact_date{ day,i };
}

/***********************************************************************
 * Func.:	normalise_date
 * Desc.:	Translate date to challenge days' consequtive number.
 **********************************************************************/

int normalise_date( const int dd,const int mm ){
	int ma{dd};

	for( int i{0};i<mm;++i )
		ma+=month[i];

	return ma;
}

/***********************************************************************
 * Func.:	get_month_name
 * Desc.:	Get month name from integer value.
 **********************************************************************/

std::string get_month_name( const int mm ){
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
 * Func.:	is_number
 * Desc.:	Is every char in numerical range?
 **********************************************************************/
 
int is_number( std::string& value ){
	for( auto character: value )
		if( !std::isdigit( character ) ) return EXIT_FAILURE;
	
	return EXIT_SUCCESS;
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
			<< " <challenge-day> <number-of-days>\n";
		return EXIT_FAILURE;
	}

	string \
	str_current	{ argv[1] },
	str_total	{ argv[2] };

	/***************************************************************
	 * Check that user has used numerals.
	 **************************************************************/

	if( EXIT_FAILURE \
	==( is_number( str_current ) || is_number( str_total ) ) ){
		std::cout << "Error: values must be type integer.\n";
		return EXIT_FAILURE;
	}

	/***************************************************************
	 * Reuse days var. for checking final day value.
	 **************************************************************/

	int \
	current_day	{ std::stoi( str_current ) },
	days		{ std::stoi( str_total ) },
	total		{ calc_amt( current_day,days ) },
	total_overall	{ calc_amt( 0,( days+=current_day ) ) };

	/***************************************************************
	 * The challenge doesn't go on for more than a year;
	 * check dates will align.
	 **************************************************************/

	if( current_day > 365 || days > 365 \
	|| current_day < 0 || days < 0 ){
		std::cout << "Error: days cannot exceed a year.\n";
		return EXIT_FAILURE;
	}

	/***************************************************************
	 * Output values to console.
	 **************************************************************/

	int		start_day{ normalise_date( START_DAY,START_MONTH ) };
	compact_date	ddmm{ normalise_date( days+start_day ) },
			cddmm{ normalise_date( current_day+start_day ) };

	std::cout << std::fixed << std::setprecision( 2 ) \
		<< "\e[0mBetween \e[0;96m" \
		<< cddmm.dd << get_day_part( cddmm.dd ) << " " \
		<< get_month_name( cddmm.mm ) << "\e[0m and \e[0;96m" \
		<< ddmm.dd << get_day_part( ddmm.dd ) \
		<< " " << get_month_name( ddmm.mm ) << "\e[0;96m" \
		<< "\e[0m you will need \e[0;92m£" \
		<< static_cast< float >( total*0.01 ) \
		<< "\e[0m in your current account.\n" \
		<< "Giving you a total of \e[0;97m\e[42m £" \
		<< static_cast< float >( total_overall*0.01 ) \
		<< " \e[0m saved altogether!\n";

	return EXIT_SUCCESS;
}
