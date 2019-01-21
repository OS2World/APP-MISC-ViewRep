PROGRAM: ViewRep
LICENSE: BSD 3-Clause
AUTHOR: Jay Schwartz / Elipse Limited

VIEWREP is a presentation manager program. It will display standard input and give the user the option of printing the file or just viewing via scoll bars. If the file contains embedded PCL printer codes they will be removed for display purposes but reinserted for printing. If, for example, you have a printer file called "myfile" you can send its contents to VIEWREP as follows:

viewrep < myfile

VIEWREP accepts optional parameters to direct the printout to a file or device other than LPT1 (the default). Use - or / followed by the device name. Or use + of @ followed by the name of a valid print queue. All other parameters will show in the title bar. 