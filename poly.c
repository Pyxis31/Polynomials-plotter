/**********************************************
 ********** Directives d'inclusions ***********
 **********************************************
*/
    
// * Des Headers système *
#include <stdio.h>	// sprintf, FILE, fopen, fclose
#include <stdlib.h>	// atoi
#include <string.h>	// strlen, strcmp
#include <ctype.h>	// isdigit
#include <windows.h> // ShellExecute
#include <shellapi.h> // ShellExecute
#include <cairo.h> // cairo_move, cairo_line, cairo_stroke, etc.
#include <math.h> // pow, etc.
       
// * Des Headers d'application *
#include "poly.h"
	

/**********************************************
 *********** Déclarations globales ************
 **********************************************
*/

// pConstInterface vient d'un autre fichier source   
extern GtkBuilder* pConstInterface;

// Pointeurs des widgets de l'interface
GtkWidget 	*pHscale1, *pEntry_nombre1, *pEntry_nombre2, *pSpinbutton1,
			*pAbout, *pFilechooserdialog1, *pFilefilter1, *pLabel_limites_I,
			*pLabel_message, *pDrawingArea1, *pHscale2, *pLabel_DimRep,
			*pCheckbutton_Vitesse, *pRadiobutton_Poly5, *pCheckbutton_Accel,
			*pCheckbutton_Position, *pCheckbutton_PleinEcran, *pColorbutton_P,
			*pHscale3, *pHscale4, *pRadiobutton_Poly2, *pRadiobutton_Poly3;
			
// Variables
static gdouble Poly_v0, Poly_v1, Poly_a0, Poly_a1;
			
/**********************************************
 ************ Fonctions callback **************
 **********************************************
*
* Ces fonctions sont liées à des événements (button click, etc.)
* Remarque : la macro G_MODULE_EXPORT exporte la fonction associée dans une table de symboles d'application au moment de la compilation
* Cette table est en suite surveillée par le "gtk_builder_connect_signals" du main.c
*
*/

// Evénement produit à l'ouverture de la fenêtre principale
G_MODULE_EXPORT void on_window1_map_event(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************
	ParamFnc_np sPfCompareLimites;
	// *********** Fin de déclarations **************
		
	// Initialise les variables
	Poly_v0=0.0;	// Vitesse initiale nulle
	Poly_v1=0.0;	// Vitesse finale nulle
	Poly_a0=0.0;	// Accélération initiale nulle
	Poly_a1=0.0;	// Accélération finale nulle
	
	// Initialise les pointeurs des widgets de l'interface
	pHscale1=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"hscale1"));
	pSpinbutton1=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"spinbutton1"));
	pEntry_nombre1=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"entry_nombre1"));
	pEntry_nombre2=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"entry_nombre2"));
	pAbout=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"aboutdialog1"));
	pFilechooserdialog1=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"filechooserdialog1"));
	pFilefilter1=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"filefilter1"));
	pLabel_limites_I=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"label_limites_I"));
	pLabel_message=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"label_message"));
	pDrawingArea1=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"drawingarea1"));
	pHscale2=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"hscale2"));
	pLabel_DimRep=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"label_DimRep"));
	pCheckbutton_Vitesse=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"checkbutton_Vitesse"));
	pCheckbutton_Accel=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"checkbutton_Accel"));
	pCheckbutton_Position=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"checkbutton_Position"));
	pRadiobutton_Poly5=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"radiobutton_Poly5"));
	pCheckbutton_PleinEcran=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"checkbutton_PleinEcran"));
	pColorbutton_P=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"colorbutton_P"));
	pHscale3=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"hscale3"));
	pHscale4=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"hscale4"));
	pRadiobutton_Poly2=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"radiobutton_Poly2"));
	pRadiobutton_Poly3=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"radiobutton_Poly3"));

	// Configuration du widget hscale1
	gtk_scale_set_digits (GTK_SCALE(pHscale1), 2) ; // Nombre de chiffres après la virgule
	gtk_range_set_range (GTK_RANGE(pHscale1), 0.0, 2.0) ; // Limites haute et basse
	gtk_range_set_increments (GTK_RANGE(pHscale1), 0.01, 0.1) ; // Valeur d'incrémentation des flèches et des touches pageUp/PageDown
	gtk_range_set_value (GTK_RANGE(pHscale1), 0.0) ; // Valeur par défaut
	
	// Configuration du widget spinbutton1
	gtk_spin_button_set_digits (GTK_SPIN_BUTTON(pSpinbutton1), 2) ; // Nombre de chiffres après la virgule
	gtk_spin_button_set_range (GTK_SPIN_BUTTON(pSpinbutton1), 0.0, 2.0) ; // Limites haute et basse
	gtk_spin_button_set_increments (GTK_SPIN_BUTTON(pSpinbutton1), 0.01, 0.1) ; // Valeur d'incrémentation des flèches et des touches pageUp/PageDown
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(pSpinbutton1), 0.0) ; // Valeur par défaut
	
	// Compare la valeur d'intensité à deux limites
	sPfCompareLimites.pData1=pHscale1; // Passe le pointeur du Widget hscale1 à la fonction
	fCompareLimites(&sPfCompareLimites); // Comparaison
	
	// Configuration du widget hscale2
	gtk_scale_set_digits (GTK_SCALE(pHscale2), 2) ; // Nombre de chiffres après la virgule
	gtk_range_set_range (GTK_RANGE(pHscale2), 0.0, 2.0) ; // Limites haute et basse
	gtk_range_set_increments (GTK_RANGE(pHscale2), 0.01, 0.1) ; // Valeur d'incrémentation des flèches et des touches pageUp/PageDown
	gtk_range_set_value (GTK_RANGE(pHscale1), 0.0) ; // Valeur par défaut
	
	// Configuration du widget hscale3
	gtk_scale_set_digits (GTK_SCALE(pHscale3), 2) ; // Nombre de chiffres après la virgule
	gtk_range_set_range (GTK_RANGE(pHscale3), 0.0, 2.0) ; // Limites haute et basse
	gtk_range_set_increments (GTK_RANGE(pHscale3), 0.01, 0.1) ; // Valeur d'incrémentation des flèches et des touches pageUp/PageDown
	gtk_range_set_value (GTK_RANGE(pHscale3), 0.0) ; // Valeur par défaut
	
	// Configuration du widget hscale4
	gtk_scale_set_digits (GTK_SCALE(pHscale4), 2) ; // Nombre de chiffres après la virgule
	gtk_range_set_range (GTK_RANGE(pHscale4), 0.0, 2.0) ; // Limites haute et basse
	gtk_range_set_increments (GTK_RANGE(pHscale4), 0.01, 0.1) ; // Valeur d'incrémentation des flèches et des touches pageUp/PageDown
	gtk_range_set_value (GTK_RANGE(pHscale4), 0.0) ; // Valeur par défaut
	}
	
	
// Bouton de fermeture
G_MODULE_EXPORT void on_window1_destroy(GtkWidget* pWidget, gpointer pData)
{
	// Interruption de la boucle principale de GTK
	gtk_main_quit();
}


// Bouton d'appel de la fenêtre à propos
G_MODULE_EXPORT void on_imagemenuitem10_button_press_event(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************

	// *********** Fin de déclarations **************
	
	// Affiche (show) le widget et bloc l'exécution du programme dans l'attente d'une réponse
	gtk_dialog_run(GTK_DIALOG(pAbout));
	
	/*
	 * Dès que la fonction gtk_dialog_run sort de sa boucle récursive,
	 * cette fonction cache le widget mais ne le détruit pas
	 */
	gtk_widget_hide(pAbout);
}


// Bouton d'addition
G_MODULE_EXPORT void on_button_addition_clicked(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************
	gint iN1,iN2,iN3;
	gchar pMessage[128]="";
	const gchar *pS1,*pS2;
	// *********** Fin de déclarations **************
	
	// Récupèrent le contenu alphanumérique des zones de saisie
	pS1=gtk_entry_get_text(GTK_ENTRY(pEntry_nombre1));
	pS2=gtk_entry_get_text(GTK_ENTRY(pEntry_nombre2));
	
	// Calcul à condition que les champs soient des entiers
	
	if (!strcmp(pS1,"")||!strcmp(pS2,""))
		{
		sprintf(pMessage,"Champ(s) vide(s)");
		}
	else if (!fIsInteger(pS1)||!fIsInteger(pS2))
			{
			sprintf(pMessage,"Format(s) erroné(s)");
			}
	else
		{
		iN1=atoi(pS1) ;
		iN2=atoi(pS2) ;
		iN3=iN1+iN2 ;
		sprintf(pMessage,"Résultat : %d",iN3);
		}

	// Affiche le résultat
	fMessage(pMessage);
}
	
	
// Le curseur hscale1 bouge
G_MODULE_EXPORT void on_hscale1_value_changed(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************
	gdouble dHscale1Value;
	ParamFnc_np sPfCompareLimites;
	// *********** Fin de déclarations **************
	
	// Copie la valeur du hscale1 dans le spinbutton1
	dHscale1Value=gtk_range_get_value(GTK_RANGE(pHscale1));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(pSpinbutton1),dHscale1Value);
	
	// Modifie le coéficient v0 du Poly en fonction de la position du curseur
	Poly_v0=dHscale1Value;
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);

	// Compare la valeur d'intensité à deux limites
	sPfCompareLimites.pData1=pHscale1; // Passe le pointeur du Widget hscale1 à la fonction
	fCompareLimites(&sPfCompareLimites); // Comparaison
}
	
	
// Le curseur hscale2 bouge
G_MODULE_EXPORT void on_hscale2_value_changed(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************
	gdouble dHscale2Value;
	// *********** Fin de déclarations **************
	
	// Copie la valeur du hscale1 dans le spinbutton1
	dHscale2Value=gtk_range_get_value(GTK_RANGE(pHscale2));

	// Modifie le coéficient v1 du Poly en fonction de la position du curseur
	Poly_v1=dHscale2Value;
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);
}
	
	
// Le curseur hscale3 bouge
G_MODULE_EXPORT void on_hscale3_value_changed(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************
	gdouble dHscale3Value;
	// *********** Fin de déclarations **************
	
	// Copie la valeur du hscale3 dans le spinbutton3
	dHscale3Value=gtk_range_get_value(GTK_RANGE(pHscale3));

	// Modifie le coéficient a0 du Poly en fonction de la position du curseur
	Poly_a0=dHscale3Value;
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);
}
	
	
// Le curseur hscale4 bouge
G_MODULE_EXPORT void on_hscale4_value_changed(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************
	gdouble dHscale4Value;
	// *********** Fin de déclarations **************
	
	// Copie la valeur du hscale4 dans le spinbutton1
	dHscale4Value=gtk_range_get_value(GTK_RANGE(pHscale4));

	// Modifie le coéficient a1 du Poly en fonction de la position du curseur
	Poly_a1=dHscale4Value;
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);
}


// La roue codeuse bouge
G_MODULE_EXPORT void on_spinbutton1_value_changed(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************
	gdouble dSpinbutton1Value;
	// *********** Fin de déclarations **************

	// Copie la valeur du spinbutton1 dans le hscale1
	dSpinbutton1Value=gtk_spin_button_get_value(GTK_SPIN_BUTTON(pSpinbutton1));
	gtk_range_set_value(GTK_RANGE(pHscale1),dSpinbutton1Value);
}
	
	
// Exportation des données
G_MODULE_EXPORT void on_menuitem7_activate(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************
	const gchar *pS1,*pS2;
	gchar* pFilename;
	gdouble dHscale1Value;
	FILE* pDatasStreamOut;
	gchar pMessage[128]="";
	// *********** Fin de déclarations **************

	// Récupèrent le contenu alphanumérique des zones de saisie
	pS1=gtk_entry_get_text(GTK_ENTRY(pEntry_nombre1));
	pS2=gtk_entry_get_text(GTK_ENTRY(pEntry_nombre2));
	
	// Récupère le contenu du hscale1
	dHscale1Value=gtk_range_get_value(GTK_RANGE(pHscale1));
	
	// Ajoute un filtre basé sur le type MIME text/plain
    gtk_file_filter_add_mime_type(GTK_FILE_FILTER(pFilefilter1),"text/plain");
    
	// Affiche (show) le widget et bloc l'exécution du programme dans l'attente d'une réponse
	gtk_dialog_run(GTK_DIALOG(pFilechooserdialog1));
		
	/*
	 * Dès que la fonction gtk_dialog_run sort de sa boucle récursive,
	 * cette fonction cache le widget mais ne le détruit pas
	 */
	gtk_widget_hide(pFilechooserdialog1);
	
	// Récupèrent le nom du fichier
	pFilename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pFilechooserdialog1));

	// Ecrit le fichier
	if (pFilename!=NULL)
		{
		pDatasStreamOut=fopen(pFilename,"w");
		fprintf(pDatasStreamOut,"%d %d %3.1f",atoi(pS1),atoi(pS2),dHscale1Value);
		fclose(pDatasStreamOut);
		}
		else
			{
			// Message à afficher : Erreur d'ouverture du fichier
			sprintf(pMessage,"Aucun fichier sélectionné !");
			fMessage(pMessage);
			}	
}	


// Importation des données
G_MODULE_EXPORT void on_menuitem6_activate(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************
	const gchar *pS1,*pS2;
	gchar* pFilename;
	gdouble dHscale1Value;
	FILE* pDatasStreamIn;
	gchar pMessage[128]="";
	// *********** Fin de déclarations **************
	
	// Ajoute un filtre basé sur le type MIME text/plain
    gtk_file_filter_add_mime_type(GTK_FILE_FILTER(pFilefilter1),"text/plain");
    
	// Affiche (show) le widget et bloc l'exécution du programme dans l'attente d'une réponse
	gtk_dialog_run(GTK_DIALOG(pFilechooserdialog1));
		
	/*
	 * Dès que la fonction gtk_dialog_run sort de sa boucle récursive,
	 * cette fonction cache le widget mais ne le détruit pas
	 */
	gtk_widget_hide(pFilechooserdialog1);
	
	// Récupèrent le nom du fichier
	pFilename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pFilechooserdialog1));

	// Lit le fichier
	if (pFilename!=NULL)
		{
		pDatasStreamIn=fopen(pFilename,"r");
		fscanf (pDatasStreamIn, "%hhu %hhu %hhu", &pS1, &pS2, &dHscale1Value);
		//fprintf(pDatasStreamOut,"%d %d %3.1f",atoi(pS1),atoi(pS2),dHscale1Value);
		fclose(pDatasStreamIn);
		}
		else
		{
		// Message à afficher : Erreur d'ouverture du fichier
		sprintf(pMessage,"Aucun fichier sélectionné !");
		fMessage(pMessage);
		}	
}


// Lien Internet
G_MODULE_EXPORT void on_linkbutton1_clicked(GtkWidget* pWidget, gpointer pData)
{
ShellExecute(NULL, "open", "http://www.google.fr", NULL, NULL, SW_SHOWNORMAL);
}


// La case à cocher Position change d'état
G_MODULE_EXPORT void on_checkbutton_Position_toggled(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************

	// *********** Fin de déclarations **************
	
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);
}


// La case à cocher Vitesse change d'état
G_MODULE_EXPORT void on_checkbutton_Vitesse_toggled(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************

	// *********** Fin de déclarations **************
	
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);
}


// La case à cocher Accélération change d'état
G_MODULE_EXPORT void on_checkbutton_Accel_toggled(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************

	// *********** Fin de déclarations **************
	
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);
}


// Le bouton radio Poly2 change d'état
G_MODULE_EXPORT void on_radiobutton_Poly2_toggled(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************

	// *********** Fin de déclarations **************
	
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);
}


// Le bouton radio Poly3 change d'état
G_MODULE_EXPORT void on_radiobutton_Poly3_toggled(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************

	// *********** Fin de déclarations **************
	
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);
}


// Le bouton radio Poly5 change d'état
G_MODULE_EXPORT void on_radiobutton_Poly5_toggled(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************

	// *********** Fin de déclarations **************
	
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);
}


// La case à cocher normalisation (plein écran) change d'état
G_MODULE_EXPORT void on_checkbutton_PleinEcran_toggled(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************

	// *********** Fin de déclarations **************
	
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);
}


// Zone de dessin DrawingArea1 exposée
G_MODULE_EXPORT void on_drawingarea1_expose_event(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************

	// *********** Fin de déclarations **************
	
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);
}

	
/**********************************************
 ********** Fonctions Applicatives ************
 **********************************************
*/
	
// Vérifie si la saisie est un entier
gchar fIsInteger(const gchar* pSaisie)
{
	// *********** Déclarations locales *************	
	gint iLoop ;
	gint iResult=1;
	// *********** Fin de déclarations **************
	
	// La boucle for parcourt la chaîne et s'arrête dès qu'un caractère non numérique est détecté
	for (iLoop=0 ; iLoop<strlen(pSaisie) && iResult ; iLoop++)
		{
		if (!isdigit(pSaisie[iLoop]))
			{
			iResult=0;
			}
		}
	// Retourne 1 si c'est un entier	
	return iResult;
}
	
	
// Compare la valeur d'intensité à deux limites
void fCompareLimites(ParamFnc_np* sPfCompareLimites)
{
	// *********** Déclarations locales *************	
	gdouble dHscale1Value;
	// *********** Fin de déclarations **************
	
	// Récupère la valeur du hscale1
	dHscale1Value=gtk_range_get_value(GTK_RANGE(sPfCompareLimites->pData1));
	
	// Compare et affiche les messages correspondants
	if (dHscale1Value>0.1 && dHscale1Value<1.9)
		{
		/* Valeur nominale
		 * On convertit le texte en caractères unicode UTF8 (pour la librairie pango) puis on le formate avec des balises <span>
		 * La concaténation permet d'incorporer le texte de manière dynamique si nécessaire
		 */
        gtk_label_set_markup(GTK_LABEL(pLabel_limites_I),
        g_locale_to_utf8(g_strconcat("<span face=\"Comic Sans MS\" foreground=\"#12FE01\" size=\"medium\"><b>","Vnom","</b></span>",NULL),
        -1, NULL, NULL, NULL));
		}
	else if (dHscale1Value<=0.1)
		{
		// Seuil bas !
        gtk_label_set_markup(GTK_LABEL(pLabel_limites_I),
        g_locale_to_utf8(g_strconcat("<span face=\"Comic Sans MS\" foreground=\"#FE0101\" size=\"medium\"><b>","Vinf 0,1","</b></span>",NULL),
        -1, NULL, NULL, NULL));
		}
		// Seuil Haut !
	else if (dHscale1Value>=1.9)
		{
        gtk_label_set_markup(GTK_LABEL(pLabel_limites_I),
        g_locale_to_utf8(g_strconcat("<span face=\"Comic Sans MS\" foreground=\"#FE0101\" size=\"medium\"><b>","Vsup 1,9","</b></span>",NULL),
        -1, NULL, NULL, NULL));
		}
}

// Affiche un message
void fMessage(gchar* pMessage)
{	
	// *********** Déclarations locales *************

	// *********** Fin de déclarations **************
	
	// Affiche le message	
	gtk_label_set_text(GTK_LABEL(pLabel_message),pMessage);
}


// Dessine un polynôme
void fPoly(gdouble v0,gdouble v1,gdouble a0,gdouble a1)
{
		// *********** Déclarations locales *************
		GdkWindow* pLowLayerWin1;			
		cairo_t* pCairoEnv1;
		gdouble a=0.0;
		gdouble b=0.0;
		gdouble c=0.0;
		gdouble d=0.0;
		gdouble e=0.0;
		gdouble f=0.0;
		gdouble x[3]={0.0};
		gdouble y[3]={0.0};
		gdouble yV[3]={0.0};
		gdouble yA[3]={0.0};
		gint xLengh=0;
		gint yLengh=0;
		gdouble xAxisCoef;
		gchar pAffDimRep[100]="";
		gdouble CoefPleinEcran=0.0;
		gdouble dashes[]={10.0,	// Grand trait plein
						2.0,	// Vide
						2.0,	// Petit trait plein
						2.0		// Vide
						};
		gint ndash =sizeof(dashes)/sizeof(dashes[0]);
		// *********** Fin de déclarations **************
		
		// Récupère le pointeur de la fenêtre de bas niveau GDK dans la zone de dessin
		pLowLayerWin1=gtk_widget_get_window(pDrawingArea1);
	
		// Crée un environnement CAIRO dans cette fenêtre pour dessiner
		pCairoEnv1=gdk_cairo_create(pLowLayerWin1);
		
		// Récupère les dimensions de la fenêtre GDK
		xLengh=gdk_window_get_width(pLowLayerWin1); // Taille des abscisses
		yLengh=gdk_window_get_height(pLowLayerWin1); // Taille des ordonnées
	
		// Fond
		cairo_set_source_rgb(pCairoEnv1, 0.29, 0.30, 0.31); // Couleur
		cairo_rectangle(pCairoEnv1,0,0,xLengh,yLengh); // Dimensions
		cairo_fill(pCairoEnv1); // Remplissage
		
		// Décalage d'origines du repère
		cairo_translate(pCairoEnv1,10,yLengh/2); // Origine des ordonnées au centre, origine des abscisses à +10 pixels
		
		// Axes des abscisses et des ordonnées en traits mixtes
		cairo_set_dash(pCairoEnv1,dashes,ndash,-50.0); // Définition du trait mixte
		cairo_set_source_rgb(pCairoEnv1,1.0,1.0,1.0); // Couleur
		cairo_set_line_width(pCairoEnv1,0.5); // Epaisseur
		cairo_move_to(pCairoEnv1,-10,0); // Point de départ axe des abscisses
		cairo_line_to(pCairoEnv1,xLengh,0.0); // Point d'arrivée
		cairo_move_to(pCairoEnv1,0,-yLengh/2); // Point de départ axe des ordonnées
		cairo_line_to(pCairoEnv1,0,yLengh/2); // Point d'arrivée
		cairo_stroke(pCairoEnv1); // Dessine		
		cairo_set_dash(pCairoEnv1,dashes,0,-50.0); // Annule la définition du trait mixte
		
		// Affichage des unités
		cairo_set_font_size(pCairoEnv1, 10);
		cairo_move_to(pCairoEnv1,-7,(-yLengh/2)+8);// Unité X+
		cairo_show_text(pCairoEnv1, "1");
		cairo_move_to(pCairoEnv1,-7,-2);// Origine
		cairo_show_text(pCairoEnv1, "0");
		cairo_move_to(pCairoEnv1,-10,(yLengh/2)-1);// Unité X-
		cairo_show_text(pCairoEnv1, "-1");
		cairo_move_to(pCairoEnv1,xLengh-15,-2);// Unité Y+
		cairo_show_text(pCairoEnv1, "1");
				 
		// Calcul des coéfficients suivant le type de polynôme
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly2)))
			{
			a=v1-v0;
			b=v0;
			c=0.0;
			gtk_widget_hide(pHscale3); // Cache les curseurs a0 et a1
			gtk_widget_hide(pHscale4);
			}
		else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly3)))
			{
			a=-2.0+v0+v1;
			b=3.0-2.0*v0-v1;
			c=v0;
			d=0.0;
			gtk_widget_hide(pHscale3); // Cache les curseurs a0 et a1
			gtk_widget_hide(pHscale4);
			}
		else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly5)))
			{
			a=6.0-3.0*(v0+v1)+((a1-a0)/2.0);
			b=-15.0+8.0*v0+7.0*v1+(3.0*a0/2.0)-a1;
			c=10.0-6.0*v0-4.0*v1-(3.0*a0/2.0)+(a1/2.0);
			d=a0/2.0;
			e=v0;
			f=0.0;
			gtk_widget_show(pHscale3); // Affiche les curseurs a0 et a1
			gtk_widget_show(pHscale4);
			}
					
		// Affiche les dimensions et les coéfficients
		sprintf(pAffDimRep,"Abscisses = %i px\nOrdonnées = %i px\n\na = %f\nb = %f\nc = %f\nd = %f\ne = %f\nf = %f",xLengh,yLengh,a,b,c,d,e,f);
		gtk_label_set_text(GTK_LABEL(pLabel_DimRep),pAffDimRep);
			
		// Calcule les fonctions en parcourant les abscisses dans le domaine [0;1]
		xAxisCoef=1.0/(xLengh-10); // Domaine [0;1]
		
		// POSITION
		// Point de départ du tracé
		cairo_move_to(pCairoEnv1,0,0);
		
		// Initialisation
		x[0]=0.0;		
		x[1]=0.0;
		x[2]=0.0;
		
		// Calcule
		while ((x[0]<=xLengh-10)&(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pCheckbutton_Position))))
		{
		x[0] = x[2];
		x[1] = x[0] + 1;
		x[2] = x[1] + 1;
		
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly2)))
			// Calcule une série de trois points suivant un polynôme 2
			{
			y[0] = yLengh/2*(0.5*a*pow(xAxisCoef*x[0],2)+b*xAxisCoef*x[0]+c);
			y[1] = yLengh/2*(0.5*a*pow(xAxisCoef*x[1],2)+b*xAxisCoef*x[1]+c);
			y[2] = yLengh/2*(0.5*a*pow(xAxisCoef*x[2],2)+b*xAxisCoef*x[2]+c);
			}
		else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly3)))
			{
			// Calcule une série de trois points suivant un polynôme 3
			y[0] = yLengh/2*(a*pow(xAxisCoef*x[0],3)+b*pow(xAxisCoef*x[0],2)+c*xAxisCoef*x[0]+d);
			y[1] = yLengh/2*(a*pow(xAxisCoef*x[1],3)+b*pow(xAxisCoef*x[1],2)+c*xAxisCoef*x[1]+d);
			y[2] = yLengh/2*(a*pow(xAxisCoef*x[2],3)+b*pow(xAxisCoef*x[2],2)+c*xAxisCoef*x[2]+d);
			}
		else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly5)))
			{
			// Calcule une série de trois points suivant un polynôme 5
			y[0] = yLengh/2*(a*pow(xAxisCoef*x[0],5)+b*pow(xAxisCoef*x[0],4)+c*pow(xAxisCoef*x[0],3)+d*pow(xAxisCoef*x[0],2)+e*xAxisCoef*x[0]+f);
			y[1] = yLengh/2*(a*pow(xAxisCoef*x[1],5)+b*pow(xAxisCoef*x[1],4)+c*pow(xAxisCoef*x[1],3)+d*pow(xAxisCoef*x[1],2)+e*xAxisCoef*x[1]+f);
			y[2] = yLengh/2*(a*pow(xAxisCoef*x[2],5)+b*pow(xAxisCoef*x[2],4)+c*pow(xAxisCoef*x[2],3)+d*pow(xAxisCoef*x[2],2)+e*xAxisCoef*x[2]+f);
			}
 
		// Calcule une spline passant par ces trois points
		cairo_curve_to(pCairoEnv1,x[0],-y[0],x[1],-y[1],x[2],-y[2]);
		}
		
		// Style du tracé
		cairo_set_source_rgb(pCairoEnv1, 0.75, 0.74, 0.24); // Couleur
		cairo_set_line_width(pCairoEnv1, 1); // Epaisseur
		
		// Dessine la fonction complète
		cairo_stroke(pCairoEnv1);
			
		// VITESSE
		// Point de départ du tracé
		cairo_move_to(pCairoEnv1,0,0);
		
		// Initialisation
		x[0]=0.0;		
		x[1]=0.0;
		x[2]=0.0;
		
		// Amplitude normalisée (en plein écran) ou non
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pCheckbutton_PleinEcran)))
			{
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly2)))
				{
				CoefPleinEcran=2.0;
				}
				else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly3)))
				{
				CoefPleinEcran=1.5;
				}
				else if  (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly5)))
				{
				CoefPleinEcran=1.9;
				}	
			}
			else
			{
			CoefPleinEcran=1.0;
			}
		
		// Calcule
		while ((x[0]<=xLengh-10)&(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pCheckbutton_Vitesse))))
		{
		x[0] = x[2];
		x[1] = x[0] + 1;
		x[2] = x[1] + 1;

		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly2)))
			// Calcule une série de trois points suivant la dérivée du polynôme 2
			{
			yV[0] = (yLengh/2)/CoefPleinEcran*(a*xAxisCoef*x[0]+b);
			yV[1] = (yLengh/2)/CoefPleinEcran*(a*xAxisCoef*x[1]+b);
			yV[2] = (yLengh/2)/CoefPleinEcran*(a*xAxisCoef*x[2]+b);
			}
		else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly3)))
			{
			// Calcule une série de trois points suivant la dérivée du polynôme 3
			yV[0] = (yLengh/2)/CoefPleinEcran*(3*a*pow(xAxisCoef*x[0],2)+2*b*xAxisCoef*x[0]+c);
			yV[1] = (yLengh/2)/CoefPleinEcran*(3*a*pow(xAxisCoef*x[1],2)+2*b*xAxisCoef*x[1]+c);
			yV[2] = (yLengh/2)/CoefPleinEcran*(3*a*pow(xAxisCoef*x[2],2)+2*b*xAxisCoef*x[2]+c);
			}
		else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly5)))
			{
			// Calcule une série de trois points suivant la dérivée du polynôme 5
			yV[0] = (yLengh/2)/CoefPleinEcran*(5*a*pow(xAxisCoef*x[0],4)+4*b*pow(xAxisCoef*x[0],3)+3*c*pow(xAxisCoef*x[0],2)+2*d*xAxisCoef*x[0]+e);
			yV[1] = (yLengh/2)/CoefPleinEcran*(5*a*pow(xAxisCoef*x[1],4)+4*b*pow(xAxisCoef*x[1],3)+3*c*pow(xAxisCoef*x[1],2)+2*d*xAxisCoef*x[1]+e);
			yV[2] = (yLengh/2)/CoefPleinEcran*(5*a*pow(xAxisCoef*x[2],4)+4*b*pow(xAxisCoef*x[2],3)+3*c*pow(xAxisCoef*x[2],2)+2*d*xAxisCoef*x[2]+e);
			}
 
		// Calcule une spline passant par ces trois points
		cairo_curve_to(pCairoEnv1,x[0],-yV[0],x[1],-yV[1],x[2],-yV[2]);
		}
			
		// Style du tracé
		cairo_set_source_rgb(pCairoEnv1, 0.0, 1.0, 0.95); // Couleur
		cairo_set_line_width(pCairoEnv1, 1); // Epaisseur
		
		// Dessine la fonction complète
		cairo_stroke(pCairoEnv1);
			
		// ACCELERATION
		// Point de départ du tracé
		cairo_move_to(pCairoEnv1,0,0);
		
		// Initialisation
		x[0]=0.0;		
		x[1]=0.0;
		x[2]=0.0;			
		
		// Amplitude normalisée (en plein écran) ou non
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pCheckbutton_PleinEcran)))
			{
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly2)))
				{
				CoefPleinEcran=2.0;
				}
				else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly3)))
				{
				CoefPleinEcran=6.0;
				}
				else if  (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly5)))
				{
				CoefPleinEcran=5.8;
				}	
			}
			else
			{
			CoefPleinEcran=1.0;
			}
		
		// Calcule
		while ((x[0]<=xLengh-10)&(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pCheckbutton_Accel))))
		{
		x[0] = x[2];
		x[1] = x[0] + 1;
		x[2] = x[1] + 1;
		
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly2)))
			// Calcule une série de trois points suivant la double dérivée du polynôme 2
			{
			yA[0] = (yLengh/2)/CoefPleinEcran*a;
			yA[1] = (yLengh/2)/CoefPleinEcran*a;
			yA[2] = (yLengh/2)/CoefPleinEcran*a;
			}
		else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly3)))
			// Calcule une série de trois points suivant la double dérivée du polynôme 3
			{
			yA[0] = (yLengh/2)/CoefPleinEcran*(6*a*xAxisCoef*x[0]+2*b);
			yA[1] = (yLengh/2)/CoefPleinEcran*(6*a*xAxisCoef*x[1]+2*b);
			yA[2] = (yLengh/2)/CoefPleinEcran*(6*a*xAxisCoef*x[2]+2*b);
			}
		else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly5)))
			{
			// Calcule une série de trois points suivant la double dérivée du polynôme 5
			yA[0] = (yLengh/2)/CoefPleinEcran*(20*a*pow(xAxisCoef*x[0],3)+12*b*pow(xAxisCoef*x[0],2)+6*c*xAxisCoef*x[0]+2*d);
			yA[1] = (yLengh/2)/CoefPleinEcran*(20*a*pow(xAxisCoef*x[1],3)+12*b*pow(xAxisCoef*x[1],2)+6*c*xAxisCoef*x[1]+2*d);
			yA[2] = (yLengh/2)/CoefPleinEcran*(20*a*pow(xAxisCoef*x[2],3)+12*b*pow(xAxisCoef*x[2],2)+6*c*xAxisCoef*x[2]+2*d);
			}
 
		// Calcule une spline passant par ces trois points
		cairo_curve_to(pCairoEnv1,x[0],-yA[0],x[1],-yA[1],x[2],-yA[2]);
		}
			
		// Style du tracé
		cairo_set_source_rgb(pCairoEnv1, 0.0, 1.0, 0.0); // Couleur
		cairo_set_line_width(pCairoEnv1, 1); // Epaisseur
		
		// Dessine la fonction complète
		cairo_stroke(pCairoEnv1);
		
		// Libère la mémoire
		cairo_destroy(pCairoEnv1);
}

