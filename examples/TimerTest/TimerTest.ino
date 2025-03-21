/* vim: set ts=4 sw=4 :
** $Id: TimerTest.ino,v 1.3 2025/03/21 12:53:53 hharms Exp $
** (c) 2025 digitalhippie
**
** Test program for PrecisionTimer library
** 
** This file is part of the PrecisionTimer Arduino library.
** Copyright: (c) 2025 Henrik Harms
** https://github.com/digitalhippie0/PrecisionTimer
**
** The PrecisionTimer Arduino library is free software: you can redistribute it and/or modify it under 
** the terms of the GNU General Public License as published by the Free 
** Software Foundation, either version 3 of the License, or (at your option) 
** any later version.
**
** The PrecisionTimer Arduino library is distributed in the hope that it will be useful, 
** but WITHOUT ANY WARRANTY; without even the implied warranty of 
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
** Public License for more details.
**
** You should have received a copy of the GNU General Public License along 
** with the PrecisionTimer Arduino library. If not, see <https://www.gnu.org/licenses/>. 
*/

#include <PrecisionTimer.h>

void setup( void) {
	PrecisionTimer myTimer;

	Serial.begin( 115200);
	delay( 1500);
	Serial.println( "**********************************");

	// simple usage:
	myTimer.start();
	delay( 20);
	myTimer.stop();
	
	Serial.print( "delay( 20); took ");
	Serial.print( myTimer.print());
	Serial.println( " sec");
	Serial.println();

	// continue counting:
	myTimer.start();
	delay( 1000);
	myTimer.stop();
	
	Serial.print( "delay( 1000) without reset makes a total of ");
	Serial.print( myTimer.print());
	Serial.println( " sec");
	Serial.println();

	// set the timer back to 0:
	myTimer.reset();
	
	Serial.print( "reset yields ");
	Serial.print( myTimer.print());
	Serial.println( " sec");
	Serial.println();

	// just time a "second":
	myTimer.start();
	delay( 1000);
	myTimer.stop();
	
	Serial.print( "delay( 1000) with reset makes a total of ");
	Serial.print( myTimer.print());
	Serial.println( " sec");
	Serial.println();
	myTimer.reset();
	
	// timing a loop from the outside:
	Serial.println( "loop test 1 (around the loop):");
	myTimer.start();	
	for ( int i=0; i<10; i++) {
		Serial.print( i);
		Serial.print( " ");
		delay( 500);
	}
	myTimer.stop();
	Serial.println( " - elapsed: ");
	Serial.print( myTimer.print());
	Serial.println( " sec");
	Serial.println();
	
	// timing a loop from the inside:
	Serial.println( "loop test 2 (inside of the loop):");
	myTimer.reset();
	for ( int i=0; i<10; i++) {
		myTimer.start();	
		Serial.print( i);
		Serial.print( " ");
		delay( 500);
		myTimer.stop();
	}
	Serial.println( " - elapsed: ");
	Serial.print( myTimer.print());
	Serial.println( " sec");
	Serial.println();
	
	// timing a loop, just the workload:
	Serial.println( "loop test 3 (workload w/o delay):");
	myTimer.reset();
	for ( int i=0; i<10; i++) {
		myTimer.start();	
		Serial.print( i);
		Serial.print( " ");
		myTimer.stop();
		delay( 500);
	}
	Serial.println( " - elapsed: ");
	Serial.print( myTimer.print());
	Serial.println( " sec");
	Serial.println();

	// you may have as many timers as you need:
	PrecisionTimer PrintStatements, DelayStatements, Total;

	Serial.println( "multiple timer test:");
	Total.start();
	for ( int i=0; i<10; i++) {
		PrintStatements.start();	
		Serial.print( i);
		Serial.print( " ");
		PrintStatements.stop();	
		DelayStatements.start();
		delay( 500);
		DelayStatements.stop();
	}
	Total.stop();
	Serial.println( "");
	Serial.print( "Total time: ");
	Serial.print( Total.print());
	Serial.print( " sec, print statements: ");
	Serial.print( PrintStatements.print());
	Serial.print( " sec, delay statements: ");
	Serial.println( DelayStatements.print());
	Serial.println();

	// testing a delay loop based on gettimeofday()
	// this is to verify the library itself
	myTimer.reset();
	Serial.print( "a real delay loop with 10 secs: ");
	struct timeval timer;					
	gettimeofday( &timer, NULL); // needed to break out of loop
	uint32_t start_tv_sec = timer.tv_sec;
	uint32_t start_tv_usec = timer.tv_usec;;

	myTimer.start();
	for( ;;) { // now test for a second+9
		gettimeofday( &timer, NULL);
		if( timer.tv_sec > (start_tv_sec+9) && timer.tv_usec > start_tv_usec ) { 
			myTimer.stop();
			break; 
		}
	}
	Serial.print( myTimer.print());
	Serial.println( " sec");
	Serial.println();
}

void loop( void) { }
