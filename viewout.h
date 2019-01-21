/* $title:      'ViewOut.H ===== Output to device or queue =====' */
/* $subtitle:   'Elipse Ltd.  [jms]         Revised: 1998 Jul 30' */


#ifndef VIEWOUT_H
#define VIEWOUT_H 1

int out_open( int use_queue, char *name, char *title );
void out_close( void );
void out_page( void );
void out_string( char *str );

#endif

