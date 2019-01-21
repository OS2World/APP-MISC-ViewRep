/* $title:      'QUEUE.C ===== Add & delete items from queue=====' */
/* $subtitle:   'Elipse Ltd.  [jms]          Revised: 1995 May 11' */


#include <stdlib.h>
#include <string.h>

typedef struct escape
    {
    char *str;
    struct escape *next;
    } ESC;

static ESC *head = NULL;
static ESC *tail = NULL;


/* INIT_QUEUE ===== Set pointers to NULL ===== $pageif:6 */

void init_queue( void )
    {                                   /* init_queue */
    head = tail = NULL;
    }                                   /* init_queue */


/* ENQUEUE ===== Add string to end of queue ===== $pageif:6 */

int enqueue( const char *buf )
    {                                   /* enqueue */
    ESC *new = malloc( sizeof( ESC ) );
    if ( new != NULL )
        {
        new->next = NULL;
        new->str = strdup( buf );
        if ( new->str != NULL )
            {
            if ( tail == NULL )
                head = tail = new;
            else
                {
                tail->next = new;
                tail = new;
                }
            return 1;                   /* success */
            }
        }
    return 0;                           /* failure */
    }                                   /* enqueue */


/* DEQUEUE ===== Remove and return string ===== $pageif:6 */

char *dequeue( char *buf )
    {                                   /* dequeue */
    *buf = '\0';
    if ( head != NULL )
        {
        ESC *temp = head->next;
        if ( head->str != NULL )
            {
            strcpy( buf, head->str );
            free( head->str );
            head->str = NULL;
            }
        free( head );
        head = temp;
        if ( head == NULL )
            tail = NULL;
        }
    return buf;                         /* with data or without */
    }                                   /* dequeue */
