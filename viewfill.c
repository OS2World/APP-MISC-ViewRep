/* $title:      'ViewFill.C ===== List Box Report Program =====' */
/* $subtitle:   'Elipse Ltd.  [jms]        Revised: 2001 Nov 09' */


#define INCL_WINDIALOGS         /*   Dialog boxes                     */
#define INCL_WINLISTBOXES       /*   List box controls                */
#define INCL_WINWINDOWMGR       /*   General window management        */
#define INCL_WINMESSAGEMGR      /*   Message management               */
#define INCL_WINSWITCHLIST      /*   Window list access               */
#include <os2.h>                /* Presentation Manager include file  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#ifdef DEBUG
#include <errormgr.h>           /* Error Manager defines & functions */
#endif
#include "viewrep.Ids"
#include "viewrep.Ext"
#include "viewrep.h"
#include "viewout.h"
#include "profile.h"
#include "queue.h"

#define LINELEN     1536
#define STACKSIZE   32768
#define ESCLEN      128
#define ESCAPE      '\x1b'
#define MARKER      '\xff'
#define OPEN_BAR    '\xc6'
#define CLOSE_BAR   '\xb5'
#define HOR_LINE    '\xcd'

extern long Argc;
extern char **Argv;

static HWND in_hwnd = (HWND) 0;
static HWND out_hwnd = (HWND) 0;
static char title[512];
static char outdev[260];
static int  qflag = 0;

static void view_title_sub( HWND hwnd, const char *new_name );
static void view_fill_sub( void *dummy );
static void view_print_sub( void *dummy );
static char *squeeze( char *dst, char *src );
static char *absorb( char *dst, char *src );
static void make_line( char *line, int maxlen );


/* VIEW_TITLE ===== List box ===== $pageif:6 */

void view_title( PGPFPARMS pGpfParms )
    {                                   /* view_title */ 
    memset( title, '\0', sizeof( title ) );
    memset( outdev, '\0', sizeof( outdev ) );
    strcpy( outdev, "PRN" );            /* default */
    qflag = 0;
    
 printf( "in view_title\n" );
 
    if (Argc > 1)
        {
        int i;
        for (i = 1;  i < Argc;  ++i)
            {
            switch (*Argv[i])
                {
            case '/':
            case '-':
                strcpy( outdev, ++Argv[i] );    /* printer device name */
                qflag = 0;
                break;
            case '@':
            case '+':
                strcpy( outdev, ++Argv[i] );    /* printer queue name */
                qflag = 1;
                break;
            default:
                strcat( title, Argv[i] );       /* add to title string */
                strcat( title, " " );
                }
            }
        }

    if (*title > ' ')
        {
        GpfSetTextTitleBar( pGpfParms->hwnd, title );
        view_title_sub( pGpfParms->hwnd, title );
        }
    }                                   /* view_title */ 


/* VIEW_TITLE_SUB ===== List box ===== $pageif:6 */

static void view_title_sub( HWND hwnd, const char *new_name )
    {                                   /* view_title_sub */
    HSWITCH hswitch;                    /* task-list entry handle */
    SWCNTRL swctl;                      /* switch-control data */
    PID pid;                            /* process id */
    HAB hab;                            /* anchor-block handle */
    HWND hwndFrame;                     /* frame handle */

 printf( "in view_title_sub\n" );

    hwndFrame = GpfGetHwndFrame( hwnd );
    hab = WinQueryAnchorBlock( hwndFrame );         /* gets anchor block */
    WinQueryWindowProcess( hwndFrame, &pid, NULL ); /* gets pid */

    /* initialize switch structure */
    swctl.hwnd = hwndFrame;             /* window handle */
    swctl.hwndIcon = NULLHANDLE;        /* icon handle */
    swctl.hprog = NULLHANDLE;           /* program handle */
    swctl.idProcess = pid;              /* process identifier */
    swctl.idSession = 0;                /* session identifier */
    swctl.uchVisibility = SWL_VISIBLE;  /* visibility */
    swctl.fbJump = SWL_JUMPABLE;        /* jump indicator */
    swctl.szSwtitle[0] = 0;             /* program name */

    hswitch = WinCreateSwitchEntry( hab, &swctl );
    strcpy( swctl.szSwtitle, new_name );
    WinChangeSwitchEntry( hswitch, &swctl );
    }                                   /* view_title_sub */ 


/* VIEW_FILL ===== List box ===== $pageif:6 */

void view_fill( PGPFPARMS pGpfParms )
    {                                   /* view_fill */
    
 printf( "in view_fill\n" );
 
    in_hwnd = pGpfParms->hwnd;
    _beginthread( view_fill_sub, NULL, STACKSIZE, NULL );
    }                                   /* view_fill */ 


/* VIEW_FILL_SUB ===== List box ===== $pageif:6 */

static void view_fill_sub( void *dummy )
    {                                   /* view_fill_sub */ 
    int maxlen = 50;
    char rawbuf[LINELEN], buf[LINELEN];
    HAB hab = WinInitialize( 0 );           /* Anchor Block  for thread */
    HMQ hmq = WinCreateMsgQueue( hab, 0 );  /* Message Queue for thread */

    WinCancelShutdown( hmq, TRUE );
    memset( rawbuf, '\0', sizeof( rawbuf ) );
    memset( buf, '\0', sizeof( buf ) );
    init_queue( );

    while (gets( rawbuf ))
        {
        char *p;
        int currlen;
        squeeze( buf, rawbuf );
        p = strchr( buf, '\f' );
        currlen = strlen( buf );
        if (currlen > maxlen)
            maxlen = currlen;
        if (p == NULL)                  /* show single line */
            WinSendDlgItemMsg( in_hwnd, ID_LISTBOX, LM_INSERTITEM, MPFROM2SHORT( LIT_END, 0 ), MPFROMP( buf ) );
        else
            {                           /* show page break */
            char line[LINELEN];
            make_line( line, maxlen );
            *p++ = '\0';
            WinSendDlgItemMsg( in_hwnd, ID_LISTBOX, LM_INSERTITEM, MPFROM2SHORT( LIT_END, 0 ), MPFROMP( buf ) );
            WinSendDlgItemMsg( in_hwnd, ID_LISTBOX, LM_INSERTITEM, MPFROM2SHORT( LIT_END, 0 ), MPFROMP( line ) );
            WinSendDlgItemMsg( in_hwnd, ID_LISTBOX, LM_INSERTITEM, MPFROM2SHORT( LIT_END, 0 ), MPFROMP( p ) );
            }
        }

    GpfMenuGray( in_hwnd, ID_ACTIONPRINT, FALSE );  /* enable print */
    GpfMenuGray( in_hwnd, ID_ACTIONEXIT,  FALSE );  /* enable exit */
    WinDestroyMsgQueue( hmq );          /* Message Queue for thread */
    in_hwnd = (HWND) 0;
    }                                   /* view_fill_sub */


/* VIEW_PRINT ===== List box ===== $pageif:6 */

void view_print( PGPFPARMS pGpfParms )
    {                                   /* view_print */ 
    
 printf( "in view_print\n" );
 
    out_hwnd = pGpfParms->hwnd;
    _beginthread( view_print_sub, NULL, STACKSIZE, NULL );
    }                                   /* view_print */ 


/* VIEW_PRINT_SUB ===== List box ===== $pageif:6 */

static void view_print_sub( void *dummy )
    {                                   /* view_print_sub */ 
    short n;
    HAB hab = WinInitialize( 0 );           /* Anchor Block  for thread */
    HMQ hmq = WinCreateMsgQueue( hab, 0 );  /* Message Queue for thread */

    WinCancelShutdown( hmq, TRUE );
    n = (short) WinSendDlgItemMsg( out_hwnd, ID_LISTBOX, LM_QUERYITEMCOUNT, (MPARAM) NULL, (MPARAM) NULL );
    if (n > 0)
        {
        if (out_open( qflag, outdev, title ))
            {
            char rawbuf[LINELEN], buf[LINELEN];
            short i;
            memset( buf, '\0', sizeof( buf ) );
            for ( i = 0;  i < n;  ++i )
                {
                WinSendDlgItemMsg( out_hwnd, ID_LISTBOX, LM_QUERYITEMTEXT, MPFROM2SHORT( i, sizeof( buf ) ), rawbuf );
                if ((rawbuf[0] == OPEN_BAR) && (rawbuf[1] == HOR_LINE))
                    out_page( );
                else
                    {
                    absorb( buf, rawbuf );
                    out_string( buf );
                    }
                }
            out_close( );
            GpfSendMsg( ID_MSGPRINTDONE );
            }
        else
            GpfSendMsg( ID_MSGPRINTFAILED );
        }

    GpfMenuGray( out_hwnd, ID_ACTIONPRINT, FALSE );  /* enable print */
    GpfMenuGray( out_hwnd, ID_ACTIONEXIT,  FALSE );  /* enable exit */
    WinDestroyMsgQueue( hmq );          /* Message Queue for thread */
    out_hwnd = (HWND) 0;
    }                                   /* view_print_sub */


/* SQUEEZE ===== Remove escape sequences ===== $pageif:6 */

static char *squeeze( char *dst, char *src )
    {                                   /* squeeze */
    const static char append[] = { MARKER, '\0', '\0' };
    char *p;
    *dst = '\0';

    while ( (p = strchr( src, ESCAPE )) != NULL )
        {
        char str[ESCLEN], *q;
        memset( str, '\0', sizeof (str) );
        q = str;
        *p++ = '\0';
        strcat( dst, src );
        strcat( dst, append );
        while (*p > ' ')
            {
            *q = *p;
            if ( isupper( *q ) || (*q == '@') || (*q == '=') )
                break;
            ++p;
            ++q;
            }
        *(++q) = '\0';
        enqueue( str );
        src = p + 1;
        }
    strcat( dst, src );
    return dst;
    }                                   /* squeeze */


/* ABSORB ===== Replace escape sequences ===== $pageif:6 */

static char *absorb( char *dst, char *src )
    {                                   /* absorb */
    const static char append[] = { ESCAPE, '\0', '\0' };
    char *p;
    *dst = '\0';

    while ( (p = strchr( src, MARKER )) != NULL )
        {
        char str[ESCLEN];
        memset( str, '\0', sizeof (str) );
        *p++ = '\0';
        strcat( dst, src );
        strcat( dst, append );
        strcat( dst, dequeue( str ) );
        src = p;
        }
    strcat( dst, src );
    return dst;
    }                                   /* absorb */


/* MAKE_LINE ===== Construct viewable line ===== $pageif:6 */

static void make_line( char *line, int maxlen )
    {                                   /* make_line */
    int i;
    line[0] = OPEN_BAR;
    for( i = 1;  i < maxlen - 1;  ++i )
        line[i] = HOR_LINE;
    line[maxlen-1] = CLOSE_BAR;
    line[maxlen] = '\0';
    }                                   /* make_line */
