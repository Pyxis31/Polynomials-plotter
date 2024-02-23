/********************************************
 *			 APPLICATION DE TEST			*
 *		  F.SIMON 2016 - v1.01 2024	   		*
 ********************************************
*/
    
    
/**********************************************
 ********** Directives d'inclusions ***********
 **********************************************
*/
    
// * Des Headers système *
#include <stdlib.h>
#include <gtk/gtk.h>
       
// * Des Headers d'application *
    
    
/**********************************************
 *********** Déclarations globales ************
 **********************************************
*/
    
//	Pointeur de type "classe créateur d'interface GTK" --> l'interface est décrite dans un fichier XML produit par GLADE
GtkBuilder* pConstInterface;
	
       
/**********************************************
 ******************* Main *********************
 **********************************************
*
* Fonction principale "main", appelée au lancement de l'exécutable
* argc = quantité de chaînes de caractères non nulles dans le tableau argv
* argv = tableau de chaînes de caractères transmises par le système
* La première chaîne contient le chemin d'accès de l'exécutable
* Les suivantes contiennent les éventuels arguments passés en mode console
*/

int main(int argc, char *argv[]) 
{	
	// 	Applique le thème contenu dans le fichier gtkrc
	gtk_rc_parse("gtkrc");
		
	// 	Initialisation de la librairie GTK : récupère les arguments de la fonction main
	gtk_init(&argc, &argv);
    
	// *********** Déclarations locales *************
	GtkWidget* pMaFenetre = NULL; // Type "classe de base GTK" contenant la fenêtre "window1" (nom venant de GLADE)
	// *********** Fin de déclarations **************

	/* 	Cette fonction "new" est un constructeur (comme en C++),
	 * 	elle fournit l'adresse d'un nouvel objet (instance) de type gtk_builder
	 */
	pConstInterface = gtk_builder_new();
      
	/* 	Cette fonction fournit le fichier XML à l'objet pConstInterface,
	 *	puis l'objet analyse le fichier afin de créer l'ensemble des widgets (fenêtres, menus, boutons, etc.) de l'interface graphique
	 */	
	gtk_builder_add_from_file(pConstInterface,"Polynomial_plotter.glade",NULL); 

	/* 	Cette fonction récupère la référence (le pointeur) du widget fenêtre "window1" contenu dans l'objet pConstInterface
	 *	Remarque : La macro GTK_WIDGET transtype (elle "cast") le GObject renvoyé par la fonction vers un type GtkWidget
	 */
	pMaFenetre = GTK_WIDGET(gtk_builder_get_object(pConstInterface,"window1")); 

	/* 	Cette fonction recherche dans la table de symboles d'application (voir callbacks.c)
	 *  une fonction callback portant le nom de l'événement venant de se produire.
	 * 	Ce nom est défini dans GLADE, précisément dans l'onglet "signaux" des propriétés de l'objet (bouton, etc.)
	 */     
	gtk_builder_connect_signals(pConstInterface,NULL);

	// 	Cette fonction affiche le contenu de pMaFenetre (fenêtre "Accueil")
	gtk_widget_show_all(pMaFenetre); 

	//	Cette fonction appelle la boucle principale de GTK
	gtk_main();

	// 	Réponse de la fonction "main" au système
	return EXIT_SUCCESS;
}
