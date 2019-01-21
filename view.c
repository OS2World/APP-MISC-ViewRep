/* $title:      'VIEW.C ===== Report Viewer Interface =====' */
/* $subtitle:   'Elipse Ltd.  [jms]    Revised: 2001 Nov 09' */


#define INCL_DOS
#include <os2.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* LPRINT_VIEW_OPEN ===== Get file pointer to write to ===== $pageif:6 */

FILE *lprint_view_open( const char *device, const char *title )
    {                                   /* lprint_view_open */
    HPIPE readpipe = -1;
    HPIPE writepipe = -1;
    HFILE savein = -1;
    HFILE newin = 0;
    RESULTCODES ret;
    char *prog = "ViewRep.Exe";
    char *param = NULL;
    char load_err[128];
    int nlen = strlen( prog );
    int plen = nlen + 16;
    memset( load_err, '\0', sizeof( load_err ) );

    if (device != NULL)
        plen += strlen( device );
    if (title != NULL)
        plen += strlen( title );
    param = _alloca( plen );
    if (param != NULL)
        {
        memset( param, '\0', plen );
        strcpy( param, prog );
        if ((device != NULL) && (*device != '\0'))
            {
            char flg[4] = "  \0\0";
            switch (*device)
                {
            case '+':                       /* use queue */
            case '@':                       /* use queue */
            case '-':                       /* use file or device */
            case '/':                       /* use file or device */
                flg[1] = ' ';               /* leave flag as given */
                break;
            default:                        /* assume device if not specified */
                flg[1] = '-';               /* set to device flag */
                }
            strcat( param, flg );
            strcat( param, device );
            }
        if ((title != NULL) && (*title != '\0'))
            {
            strcat( param, " " );
            strcat( param, title );
            }
        param[nlen] = '\0';
        }

    DosDupHandle( 0, &savein );
    DosCreatePipe( &readpipe, &writepipe, 4096 );
    DosDupHandle( readpipe, &newin );

    DosExecPgm( load_err, sizeof( load_err ), EXEC_ASYNC, param, NULL, &ret, prog );

    DosDupHandle( savein, &newin );
    return _fdopen( writepipe, "w" );

    return NULL;
    }                                   /* lprint_view_open */
