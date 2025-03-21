/* vim: set ts=4 sw=4 :
** $Id: PrecisionTimer.h,v 1.3 2025/03/21 12:53:53 hharms Exp $
**
** PrecisionTimer.h
** Implements a high precision timer for the Arduino platform
** which will measure down to 10^-5 sec pretty accurately and 10^-6 with very little error
**
** 	instantiate like so:
** 		PrecisionTimer myTimer;
**
**	usage:
**		myTimer.start();
**		myTimer.stop();
**		Serial.print( myTimer.print());
**		myTimer.reset();
**
**	change PT_PRECISION to match your level of precision (see below)
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

#include <Arduino.h>
#include <sys/time.h>

#ifndef __PRECISION_TIMER
#define __PRECISION_TIMER

#define PT_MICROS		1000000LL	// defined by the millis from our platform (arduino, esp32)
//#define PT_PRECISION	1000LL		// lower precision
//#define PT_PRECISION	10000LL		// must be multiple of 10 - we need the log10 later on
#define PT_PRECISION	100000LL	// higher precision

class PrecisionTimer {
	private:
	struct timeval _pt_start;
	struct timeval _pt_stop;

	typedef struct _structPrecisionTimer {
		uint64_t tv_sec  = 0;
		uint32_t tv_usec = 0;
	};
	_structPrecisionTimer _PrecisionTimer;

	public:
		PrecisionTimer() {
			// first measure time to aquire time, we need to subtract this from the results
			struct timeval now, then;
			gettimeofday( &now, NULL);
			gettimeofday( &then, NULL);

			// second, set all variables to zero;
			_pt_start.tv_sec    = 0;
			_pt_start.tv_usec   = 0;
			_pt_stop.tv_sec     = 0;
			_pt_stop.tv_usec    = 0;
			_PrecisionTimer.tv_sec  = 0;
			_PrecisionTimer.tv_usec = 0;
		}

		void start( void);
		void stop( void);
		void reset( void);
		String print( void);
};
#endif
