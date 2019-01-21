/* $title:      'QUEUE.H ===== Add & delete items from queue=====' */
/* $subtitle:   'Elipse Ltd.  [jms]          Revised: 1995 May 11' */


#ifndef QUEUE_H
#define QUEUE_H 1

void init_queue( void );
int enqueue( const char *buf );
char *dequeue( char *buf );

#endif
