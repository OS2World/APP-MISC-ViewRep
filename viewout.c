/* $title:      'ViewOut.C ===== Output to device or queue =====' */
/* $subtitle:   'Elipse Ltd.  [jms]         Revised: 2001 Nov 09' */


#define INCL_SPL
#define INCL_SPLDOSPRINT
#define INCL_BASE
#define INCL_SPLERRORS
#define INCL_DOSERRORS

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "viewout.h"

static int qflag = 0;
static HSPL hspl = (HSPL) 0;
static FILE *fpr = NULL;

static char *qdriver( char *qname );
static HSPL qopen( char *qname, char *driver, char *title );
static unsigned long qclose( void );


/* OUT_OPEN ===== Prepare for output ===== $pageif:6 */

int out_open( int use_queue, char *name, char *title )
    {                                   /* out_open */
    
 printf( "in out_open\n" );

    hspl = (HSPL) 0;
    fpr = NULL;
    qflag = use_queue;
    if (qflag)
        {
        char *drivname = qdriver( name );
        if (drivname != NULL)
            {
            hspl = qopen( name, drivname, title);
            if (hspl != (HSPL) 0)
                return 1;               /* success */
            }
        }
    else
        fpr = fopen( name, "w" );
        if (fpr != NULL)
            return 1;                   /* success */
    return 0;                           /* failure */
    }                                   /* out_open */


/* OUT_CLOSE ===== Finish up ==== $pageif:6 */

void out_close( void )
    {                                   /* out_close */
    
 printf( "in out_close\n" );
 
    if (qflag)
        qclose( );
    else
        fclose( fpr );
    hspl = (HSPL) 0;
    fpr = NULL;
    }                                   /* out_close */


/* OUT_PAGE ===== Note page break ===== $pageif:6 */

void out_page( void )
    {                                   /* out_page */
    if (qflag)
        SplQmWrite( hspl, 1, "\f" );
    else
        fputc( '\f', fpr );
    }                                   /* out_page */


/* OUT_STRING ===== Single line of output ===== $pageif:6 */

void out_string( char *str )
    {                                   /* out_string */
    if (qflag)
        {
        SplQmWrite( hspl, strlen( str ), str );
        SplQmWrite( hspl, 2, (PVOID) "\r\n" );
        }
    else
        fprintf( fpr, "%s\n", str );
    }                                   /* out_string */


/* QDRIVER ===== Return driver name for queue ===== $pageif:6 */

static char *qdriver( char *qname )
    {                                   /* qdriver */
    static char driver_name[256];
    ULONG splerr = 0L;
    ULONG szbuf = 0L;
    ULONG szneeded = 0L;
    PVOID bufr = NULL;
    PPRQINFO3 prq3;
    memset( driver_name, '\0', sizeof( driver_name ) );

    splerr = SplQueryQueue( NULL, qname, 3L, (PVOID) NULL, 0L, &szneeded );

    if (splerr == NERR_QNotFound)
        return NULL;
    if ((splerr != NERR_BufTooSmall) && (splerr != ERROR_MORE_DATA))
        return NULL;

    if ((szneeded > 0) && ((bufr = _alloca( szneeded )) != NULL))
        {
        szbuf = szneeded;
        splerr = SplQueryQueue( NULL, qname, 3L, bufr, szbuf, &szneeded );
        prq3 = (PPRQINFO3) bufr;
        strncpy( driver_name, prq3->pszDriverName, sizeof( driver_name ) );
        }
    return driver_name;
    }                                   /* qdriver */


/* QOPEN ===== Body of program ===== $pageif:6 */

static HSPL qopen( char *qname, char *driver, char *title )
    {                                   /* qopen */
    HSPL tspl;                          /* Temporary spool handle */
    PDEVOPENSTRUC pdata;                /* Pointer to a DEVOPENSTRUC structure */
    pdata = _alloca( sizeof( DEVOPENSTRUC ) );  /* Allocate memory for pdata */
    if (pdata != NULL)
        {                                       /* Initialize elements of pdata */
        pdata->pszLogAddress      = qname;
        pdata->pszDriverName      = driver;
        pdata->pdriv              = NULL;
        pdata->pszDataType        = "PM_Q_RAW";
        pdata->pszComment         = title;
        pdata->pszQueueProcName   = NULL;
        pdata->pszQueueProcParams = NULL;
        pdata->pszSpoolerParams   = NULL;
        pdata->pszNetworkParams   = NULL;

        tspl = SplQmOpen( "*", 4L, (PQMOPENDATA) pdata );
        if (tspl != (HSPL) 0)
            if (SplQmStartDoc( tspl, title ))
                return tspl; 
        }
    return (HSPL) 0;
    }                                   /* qopen */


/* QCLOSE ===== Close the queue spool ===== $pageif:6 */

static unsigned long qclose( void )
    {                                   /* qclose */
    ULONG jobid = SplQmEndDoc( hspl );
    SplQmClose( hspl );
    return jobid;
    }                                   /* qclose */
