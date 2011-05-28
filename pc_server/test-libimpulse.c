/*
 *
 *+  Copyright (c) 2009 Ian Halpern
 *@  http://impulse.ian-halpern.com
 *
 *   This file is part of Impulse.
 *
 *   Impulse is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Impulse is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Impulse.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "Impulse.h"
#include <stdio.h>

int main( ) {

	im_start( );
	int i;
	double j = 0.0f;
	while ( 1 ) {
		usleep( 1000000 / 30 );
		double *array = im_getSnapshot( IM_NOFFT );
		j = 0.0f;
		for ( i = 0; i < 256; i+=32 ){
			 j += array[i];
			//printf( "j = %i", j);			
	
				
		}
		j/8;
		
		for(int k = (int) (j*50); k > 0; k--){
			printf( "#");
		}
		printf( "\n");		
		fflush( stdout );
	}
	im_stop( );

	return 0;
}
