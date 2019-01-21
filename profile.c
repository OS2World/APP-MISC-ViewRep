/* $title:      'PROFILE.C ===== INI file read/write functions =====' */
/* $subtitle:   'Elipse Ltd.  [jms]             Revised: 2001 Nov 09' */


#define INCL_WINSHELLDATA
#define INCL_WINWINDOWMGR
#include <os2.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef DEBUG
#include <errormgr.h>           /* Error Manager defines & functions */
#endif

#include "ViewRep.Ext"
#include "profile.h"

static void prof_open( HAB hab );
static int prof_read_int( char *applic, char *keyval, int intval );
static void prof_save_int( char *applic, char *keyval, int intval );
static char *path_from_env( const char *defval, const char *envar[] );

static char *window_name = "ViewRep";
static HINI hini = (HINI) 0;


/* PROF_OPEN ===== In correct directory ===== $pageif:6 */

static void prof_open( HAB hab )
    {                                   /* prof_open */
    static const char *envar[] = { "VIEWINI", "TEMP", "TMP", NULL, NULL };
    char filename[260];
    memset( filename, '\0', sizeof( filename ) );
    strcpy( filename, path_from_env( "", envar ) );
    strcat( filename, window_name );
    strcat( filename, ".ini" );
    hini = PrfOpenProfile( hab, filename );
    }                                   /* prof_open */


/* PROF_READ_INT ===== Read and return integer value ===== $pageif:6 */

static int prof_read_int( char *applic, char *keyval, int intval )
    {                                   /* prof_read_int */
    if (hini != (HINI) 0)
        return (int) PrfQueryProfileInt( hini, applic, keyval, (long) intval );
    else
        return intval;
    }                                   /* prof_read_int */


/* PROF_SAVE_INT ===== Read and return integer value ===== $pageif:6 */

static void prof_save_int( char *applic, char *keyval, int intval )
    {                                   /* prof_save_int */
    if (hini != (HINI) 0)
        {
        char buf[32];
        sprintf( buf, "%d\0", intval );
        PrfWriteProfileString( hini, applic, keyval, buf );
        }
    }                                   /* prof_save_int */


/* PROF_MAKE_SIZ_POS ===== Set window size and positon ===== $pageif:6 */

void prof_make_siz_pos( PGPFPARMS pGpfParms )
    {                                   /* prof_make_siz_pos */
    prof_open( pGpfParms->hab );
    if (hini != (HINI) 0)
        {
        int xp = prof_read_int( window_name, "Xposition", -1 );
        int yp = prof_read_int( window_name, "Yposition", -1 );
        int xs = prof_read_int( window_name, "Xsize", -1 );
        int ys = prof_read_int( window_name, "Ysize", -1 );
        if ((xp > 0) && (yp > 0) && (xs > 0) && (ys > 0))
            WinSetWindowPos( GpfGetHwndFrame( pGpfParms->hwnd ), HWND_TOP, xp, yp, xs, ys, SWP_MOVE | SWP_SIZE );
        PrfCloseProfile( hini );
        hini = (HINI) 0;
        }
    }                                   /* prof_make_siz_pos */


/* PROF_SAVE_SIZ_POS ===== Save window size and positon ===== $pageif:6 */

void prof_save_siz_pos( PGPFPARMS pGpfParms )
    {                                   /* prof_save_siz_pos */
    prof_open( pGpfParms->hab );
    if (hini != (HINI) 0)
        {
        SWP swp;
        WinQueryWindowPos( GpfGetHwndFrame( pGpfParms->hwnd ), &swp );
        prof_save_int( window_name, "Xposition", (int) swp.x );
        prof_save_int( window_name, "Yposition", (int) swp.y );
        prof_save_int( window_name, "Xsize", (int) swp.cx );
        prof_save_int( window_name, "Ysize", (int) swp.cy );
        PrfCloseProfile( hini );
        hini = (HINI) 0;
        }
    }                                   /* prof_save_siz_pos */


/* PATH_FROM_ENV ===== Return path from env list or default ===== $pageif:6 */

static char *path_from_env( const char *defval, const char *envar[] )
    {                                   /* path_from_env */
    static char path[260];
    char onevar[128];
    char *p = NULL;
    int i = 0;
    memset( path, '\0', sizeof (path) );
    memset( onevar, '\0', sizeof (onevar) );

    while ( envar[i] != NULL )
        {
        strcpy( onevar, envar[i++] );
        p = getenv( strupr( onevar ) );
        if ( p != NULL )
            break;
        }
    if ( p != NULL )
        strcpy( path, p );
    else
        if ( defval != NULL )
            strcpy( path, defval );

    i = strlen( path );
    if ( i > 0 )
        {
        p = &path[i];
        if ( *(p - 1) != '\\' )
            *p = '\\';
        }
    return path;
    }                                   /* path_from_env */
