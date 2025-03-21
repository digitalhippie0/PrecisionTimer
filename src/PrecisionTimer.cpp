/* vim: set ts=4 sw=4 :
** $Id: PrecisionTimer.cpp,v 1.3 2025/03/21 12:53:53 hharms Exp $
**
** PrecisionTimer.cpp
** Implements a high precision timer for the Arduino platform
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
**
*/

#include <cstdio>
#include <Arduino.h>
#include "PrecisionTimer.h"
#include <sys/time.h>

void PrecisionTimer::start( void) {
	gettimeofday( &_pt_start, NULL);
}

void PrecisionTimer::stop( void) {
	gettimeofday( &_pt_stop, NULL);
	_PrecisionTimer.tv_sec += PT_MICROS * ( _pt_stop.tv_sec  - _pt_start.tv_sec);
	_PrecisionTimer.tv_sec += ( _pt_stop.tv_usec  - _pt_start.tv_usec);
}

void PrecisionTimer::reset( void) {
	_PrecisionTimer.tv_sec  = 0;
	_PrecisionTimer.tv_usec = 0;
}

String PrecisionTimer::print( void) {
	char format[16];
	char buffer[64];

	// complicated integer maths is more durable than floats
	uint32_t secs = (uint32_t) ( _PrecisionTimer.tv_sec / PT_MICROS);
	uint32_t usec = (uint32_t) ( _PrecisionTimer.tv_sec - (secs * PT_MICROS) );
	int8_t _pt_precision = log10( PT_MICROS) - log10( PT_MICROS / PT_PRECISION);
	usec = usec / (PT_MICROS / PT_PRECISION);

	sprintf( format, "%%d.%%0%dd", _pt_precision); 
	sprintf( buffer, format, secs, usec); 
	return String( buffer);
}
