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

int calc_amt( const int day,const int total_days ){
	int retval{day},intermediate{day};
	
	for( int i{0}; i<total_days; ++i )
		retval+=(++intermediate);

	return retval;
}

int is_number( std::string& value ){
	for( auto character: value )
		if( !std::isdigit( character ) ) return EXIT_FAILURE;
	
	return EXIT_SUCCESS;
}

int main( int argc,char *argv[] ) {
	using std::string;

	/***************************************************************
	 * Without values print details on how to use program and exit.
	 **************************************************************/

	if( argc < 3 ){
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

	if( is_number( str_current ) || is_number( str_total ) ){
		std::cout << "Error: values must be type integer.\n";
		return EXIT_FAILURE;
	}

	int \
	current_day	{ std::stoi( str_current ) },
	days		{ std::stoi( str_total ) },
	total		{ calc_amt( current_day,days ) },
	total_overall	{ calc_amt( 0,current_day ) };

	/***************************************************************
	 * Reuse days var. for checking final day value.
	 **************************************************************/

	days+=current_day;

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

	std::cout << std::fixed << std::setprecision(2) \
		<< "\e[0mBetween days \e[0;96m" << current_day \
		<< "\e[0m and \e[0;96m" << days \
		<< "\e[0m you will need \e[0;92m£" \
		<< static_cast< float >( total*0.01 ) \
		<< "\e[0m in your current account.\n" \
		<< "Giving you a total of \e[0;95m£" \
		<< static_cast< float >( total_overall*0.01 ) \
		<< "\e[0m saved since day 1!\n";

	return EXIT_SUCCESS;
}
