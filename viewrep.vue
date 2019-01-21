=======Description of ORC FILE:ViewRep.orc
  Created by GpfTools v1.0 8-2-1998 12:17

=======General Window Structure

  ----Window Structure by Parent
  DESKTOP
   MainWindow("Report Pre...") (Menu)  (Actions) 

  ----Window Structure by Owner
  DESKTOP
   MainWindow("Report Pre...") (Menu)  (Actions) 


=======------------------


========([C-H-] )  Design G P F

  Design      :   G P F
  Copyright   :   (C) 1995, 1998 Elipse Limied
  Task List Name:  Report Preview     Level  :          1.1
  Subsystem   :   
  DB Name     :   No DBM
  Main Source :   ViewRep
  Main Thread :   MainTask
  Help


========(       )    Help for Design G P F

  Help for Design : G P F
  MsgInfo  :      
  Title  :        Report Preview
  Index  :        


  :lines align=center.
  :hp2. REPORT PREVIEW :ehp2.
  :elines.
  :p.
  This is a preview of your printed report.
  se the scroll bars to view the entire document.
  :p.
  Select PRINT for a hard copy.
  Select EXIT when done.
  :sl compact.
  :li.
  :li. Author:
  :li.     Jay Schwartz
  :li.     Elipse Limited
  :li.     6 Ava Road
  :li.     Toronto, Canada M5P 1X9
  :li.
  :li.     Voice/Fax (416) 483-5200
  :li.     Internet www.elipse.com
  :esl.

=======------------------


========([<No>] )  Window MainWindow

  Window  :       MainWindow          Source  :         ViewRep
  Parent  :       <None>              Thread  :         MainTask
  Owner  :        <None>              Frame Pres :      <None>
  Title :         Report Preview      Client Pres :     PresParamsAppWkSpace
                                      Icon(BitMap):     Document
  X Y Cx Cy :     5  6  372  196
  Actions
  Menu

Gpf  Styles  : 
  AdjustSize
  IsMainWindow
Window Styles: 
  ClipSiblings
  SaveBits  SyncPaint
Class  Styles: 
  TitleBar
  SysMmenu  AppMenu
  SizeBorder
  MinButton  MaxButton
  ShellPosition
Used in:
Is Parent of: listBox ListBox
Is Owner of : listBox ListBox

========(     )  Actions of Window MainWindow

ACTION-LIST for Window MainWindow("Report Pre...")
   On Init Window
      Action:User Function (UserFunction view_fill) 
      Action:User Function (UserFunction view_title) 
      Action:User Function (UserFunction prof_make_siz_pos) 
   On Destroy Window
      Action:User Function (UserFunction prof_save_siz_pos) 
-----------------------------------------
   ACTION-LIST for MenuItem ActionExit("~Exit")
      On COMMAND
         Action:Quit Application
-----------------------------------------
   ACTION-LIST for listBox ListBox
      On Click
         Action:Reset Selection
-----------------------------------------
   ACTION-LIST for MenuItem ActionPrint("~Print")
      On COMMAND
         Action:Menu Disable
         Action:Menu Disable (MenuItem ActionExit("~Exit")) 
         Action:User Function (UserFunction view_print) 
-----------------------------------------
======ORPHANS (Have No Explicit Actions)========


========(     )  Menu of Window MainWindow

[<No>]  ActionExit("~Exit") (Actions) 
[<No>]  ActionPrint("~Print") (Actions) 


========([<No>] )    MenuItem ActionExit

  Menu Item  :    ActionExit
  Text  :         ~Exit
  In Window :     MainWindow("Report Pre...")
  Presentation :  <None>
  Icon(BitMap) :  <None>
  Actions

Item Styles: 
  Text
Item Attributes: 
PullDowns:
Used in:Actions of MenuItem ActionPrint("~Print");

========(     )  Actions of MenuItem ActionExit

ACTION-LIST for MenuItem ActionExit("~Exit")
   On COMMAND
      Action:Quit Application
-----------------------------------------


========([<No>] )    MenuItem ActionPrint

  Menu Item  :    ActionPrint
  Text  :         ~Print
  In Window :     MainWindow("Report Pre...")
  Presentation :  <None>
  Icon(BitMap) :  <None>
  Actions

Item Styles: 
  Text
Item Attributes: 
  Disabled
PullDowns:
Used in:Actions of MenuItem ActionPrint("~Print");

========(     )  Actions of MenuItem ActionPrint

ACTION-LIST for MenuItem ActionPrint("~Print")
   On COMMAND
      Action:Menu Disable
      Action:Menu Disable (MenuItem ActionExit("~Exit")) 
      Action:User Function (UserFunction view_print) 
-----------------------------------------


========([<No>] ) listBox ListBox

  listBox :       ListBox
  Owner :         MainWindow("Report Pre...")
  Text  :         
  Association:    NULL  
  Presentation :  PresParamsMono
  Icon(BitMap) :  <None>
  Icon(BitMap) :  <None>
  X Y Cx Cy :     0  0  368  174
  Actions

Styles  : 
  Visible
  Group  TabStop 
  NoAdjustPos
  HorzScroll 
SubControls:
Used in:Actions of listBox ListBox;

========(     )  Actions of listBox ListBox

ACTION-LIST for listBox ListBox
   On Click
      Action:Reset Selection
-----------------------------------------


=======------------------


=======MessageBox Objects
 This section describes MessageBox Objects
          MsgPrintDone("Printing i...")   - never used
          MsgPrintFailed("Printing f...")   - never used
  There are 2 unused MessageBox Objects of a total of 2


========([<No>] )  MsgBox MsgPrintDone

  Message Box:    MsgPrintDone
  Buttons: OK
  Icon   : AsteriskIcon
  Styles : 
  Moveable
  ---------Text-------
  Printing is complete.

Used in : 

========([<No>] )  MsgBox MsgPrintFailed

  Message Box:    MsgPrintFailed
  Buttons: OK
  Icon   : HandIcon
  Styles : 
  Moveable
  ---------Text-------
  Printing failed. Verify that the print destination (device, file or queue) was correctly specified.

Used in : 

=======Icon/Bitmap/Pointer Objects
 This section describes Icon/Bitmap/Pointer Objects
          Document
  There are 0 unused Icon/Bitmap/Pointer Objects of a total of 1


========(       )  Icon Document

  
  IsIcon          Document
  File Name:      DOC2
  Path     :      D:\DEVELOP\VIEWREP

USED 
As Icon in Windows  : Window MainWindow("Report Pre...")
As Icon in Menu     :
As Icon1 in Controls:
As Icon2 in Controls:

=======Presentation Objects
 This section describes Presentation Objects
          PresParamsDialogBox   - never used
          PresParamsAppWkSpace
          PresParamsWindow   - never used
          PresParamsPushButton   - never used
          PresParamsMono
  There are 3 unused Presentation Objects of a total of 5


========(       )  PresParam PresParamsDialogBox

  Presentation:   PresParamsDialogBox
  Font Name   :   NULL
  ForegrColor     : DEFAULT
  BackgrColor     : SYSCLR_DIALOGBACKGROUND
  HiliteFgColor   : DEFAULT
  HiliteBgColor   : DEFAULT
  DisableFgColor  : DEFAULT
  DisableBgColor  : SYSCLR_DIALOGBACKGROUND

Used As Client presentation in Windows:
Used As Frame presentation in Windows :
Used As presentation in Controls:
Used As presentation in Menu & Popup:

========(       )  PresParam PresParamsAppWkSpace

  Presentation:   PresParamsAppWkSpace
  Font Name   :   NULL
  ForegrColor     : DEFAULT
  BackgrColor     : SYSCLR_APPWORKSPACE
  HiliteFgColor   : DEFAULT
  HiliteBgColor   : DEFAULT
  DisableFgColor  : DEFAULT
  DisableBgColor  : DEFAULT

Used As Client presentation in Windows: Window MainWindow("Report Pre...")
Used As Frame presentation in Windows :
Used As presentation in Controls:
Used As presentation in Menu & Popup:

========(       )  PresParam PresParamsWindow

  Presentation:   PresParamsWindow
  Font Name   :   NULL
  ForegrColor     : DEFAULT
  BackgrColor     : SYSCLR_WINDOW
  HiliteFgColor   : DEFAULT
  HiliteBgColor   : DEFAULT
  DisableFgColor  : DEFAULT
  DisableBgColor  : DEFAULT

Used As Client presentation in Windows:
Used As Frame presentation in Windows :
Used As presentation in Controls:
Used As presentation in Menu & Popup:

========(       )  PresParam PresParamsPushButton

  Presentation:   PresParamsPushButton
  Font Name   :   NULL
  ForegrColor     : DEFAULT
  BackgrColor     : SYSCLR_BUTTONMIDDLE
  HiliteFgColor   : DEFAULT
  HiliteBgColor   : DEFAULT
  DisableFgColor  : DEFAULT
  DisableBgColor  : DEFAULT

Used As Client presentation in Windows:
Used As Frame presentation in Windows :
Used As presentation in Controls:
Used As presentation in Menu & Popup:

========(       )  PresParam PresParamsMono

  Presentation:   PresParamsMono
  Font Name   :   8.Courier
  ForegrColor     : DARKBLUE
  BackgrColor     : WHITE
  HiliteFgColor   : DARKBLUE
  HiliteBgColor   : WHITE
  DisableFgColor  : DEFAULT
  DisableBgColor  : DEFAULT

Used As Client presentation in Windows:
Used As Frame presentation in Windows :
Used As presentation in Controls: listBox ListBox
Used As presentation in Menu & Popup:

=======User Function Objects
 This section describes User Function Objects
          view_fill
          view_print
          view_title
          prof_make_siz_pos
          prof_save_siz_pos
  There are 0 unused User Function Objects of a total of 5


========(       )  UserFunction view_fill

  User Function:  view_fill
  -------Text-------
  	view_fill( pGpfParms );

Used in :Actions of Window MainWindow("Report Pre...");

========(       )  UserFunction view_print

  User Function:  view_print
  -------Text-------
  	view_print( pGpfParms );

Used in :Actions of MenuItem ActionPrint("~Print");

========(       )  UserFunction view_title

  User Function:  view_title
  -------Text-------
  	view_title( pGpfParms );

Used in :Actions of Window MainWindow("Report Pre...");

========(       )  UserFunction prof_make_siz_pos

  User Function:  prof_make_siz_pos
  -------Text-------
  	prof_make_siz_pos( pGpfParms );

Used in :Actions of Window MainWindow("Report Pre...");

========(       )  UserFunction prof_save_siz_pos

  User Function:  prof_save_siz_pos
  -------Text-------
  	prof_save_siz_pos( pGpfParms );

Used in :Actions of Window MainWindow("Report Pre...");

=======User Control Objects
 This section describes User Control Objects
  There are no User Control Objects in this application


=======Source Names
 This section describes Source Names
          ViewRep


========(       )  SourceName ViewRep

  Source:         ViewRep

Used by Windows:  Window MainWindow("Report Pre...")

=======Thread Names
 This section describes Thread Names
          MainTask


========(       )  Thread MainTask

  Thread:         MainTask

For Windows:  Window MainWindow("Report Pre...")
=====End of Description======