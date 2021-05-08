/**********************************************
 ********** Directives d'inclusions ***********
 **********************************************
*/
    
// * Des Headers système *

       
// * Des Headers d'application *
#include "audio.h"
	

/**********************************************
 *********** Déclarations globales ************
 **********************************************
*/
 
// pConstInterface vient d'un autre fichier source   
extern GtkBuilder* pConstInterface;

// Pointeurs des widgets de l'interface


// Variables


/**********************************************
 ************ Fonctions callback **************
 **********************************************
*/

// Test
G_MODULE_EXPORT void on_button_play_clicked(GtkWidget* pWidget, gpointer pData)
{
	gtk_main_quit();
}


	
/**********************************************
 ********** Fonctions Applicatives ************
 **********************************************
*/

// Fonction ...

