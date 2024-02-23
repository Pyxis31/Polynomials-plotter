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
GtkWidget 	*pAbout,*pDrawingArea1,
			*pHscale1, *pHscale2, *pHscale3, *pHscale4,
			*pCheckbutton_Position, *pCheckbutton_Vitesse, *pCheckbutton_Accel,
			*pRadiobutton_Poly3, *pRadiobutton_Poly5,
			*pLabel_11,*pLabel_12;
			
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

	// *********** Fin de déclarations **************
	
	// Initialise les variables
	Poly_v0=0.0;	// Vitesse initiale nulle
	Poly_v1=0.0;	// Vitesse finale nulle
	Poly_a0=0.0;	// Accélération initiale nulle
	Poly_a1=0.0;	// Accélération finale nulle
	
	// Initialise les pointeurs des widgets de l'interface
	pAbout=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"aboutdialog1"));
	pDrawingArea1=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"drawingarea1"));
	pHscale1=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"hscale1"));
	pHscale2=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"hscale2"));
	pHscale3=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"hscale3"));
	pHscale4=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"hscale4"));
	pCheckbutton_Position=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"checkbutton_Position"));
	pCheckbutton_Vitesse=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"checkbutton_Vitesse"));
	pCheckbutton_Accel=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"checkbutton_Accel"));
	pRadiobutton_Poly3=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"radiobutton_Poly3"));
	pRadiobutton_Poly5=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"radiobutton_Poly5"));
	pLabel_11=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"label11"));
	pLabel_12=GTK_WIDGET(gtk_builder_get_object(pConstInterface,"label12"));

	// Configuration du widget hscale1
	gtk_scale_set_digits (GTK_SCALE(pHscale1), 2) ; // Nombre de chiffres après la virgule
	gtk_range_set_range (GTK_RANGE(pHscale1), 0.0, 2.0) ; // Limites haute et basse
	gtk_range_set_increments (GTK_RANGE(pHscale1), 0.01, 0.1) ; // Valeur d'incrémentation des flèches et des touches pageUp/PageDown
	gtk_range_set_value (GTK_RANGE(pHscale1), 0.0) ; // Valeur par défaut
	
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


// Bouton droite
G_MODULE_EXPORT void on_droite_clicked(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************

	// *********** Fin de déclarations **************
	
	gtk_range_set_value(GTK_RANGE(pHscale1),1.0);
	gtk_range_set_value(GTK_RANGE(pHscale2),1.0);
}


// Le curseur hscale1 bouge
G_MODULE_EXPORT void on_hscale1_value_changed(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************
	gdouble dHscale1Value;
	// *********** Fin de déclarations **************
	
	// Modifie le coéficient v0 du Poly en fonction de la position du curseur
	dHscale1Value=gtk_range_get_value(GTK_RANGE(pHscale1));
	Poly_v0=dHscale1Value;
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);
}
	
	
// Le curseur hscale2 bouge
G_MODULE_EXPORT void on_hscale2_value_changed(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************
	gdouble dHscale2Value;
	// *********** Fin de déclarations **************

	// Modifie le coéficient v1 du Poly en fonction de la position du curseur
	dHscale2Value=gtk_range_get_value(GTK_RANGE(pHscale2));
	Poly_v1=dHscale2Value;
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);
}
	
	
// Le curseur hscale3 bouge
G_MODULE_EXPORT void on_hscale3_value_changed(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************
	gdouble dHscale3Value;
	// *********** Fin de déclarations **************

	// Modifie le coéficient a0 du Poly en fonction de la position du curseur
	dHscale3Value=gtk_range_get_value(GTK_RANGE(pHscale3));
	Poly_a0=dHscale3Value;
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);
}
	
	
// Le curseur hscale4 bouge
G_MODULE_EXPORT void on_hscale4_value_changed(GtkWidget* pWidget, gpointer pData)
{
	// *********** Déclarations locales *************
	gdouble dHscale4Value;
	// *********** Fin de déclarations **************

	// Modifie le coéficient a1 du Poly en fonction de la position du curseur
	dHscale4Value=gtk_range_get_value(GTK_RANGE(pHscale4));
	Poly_a1=dHscale4Value;
    fPoly(Poly_v0,Poly_v1,Poly_a0,Poly_a1);
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


// Le bouton radio Poly3 change d'état
G_MODULE_EXPORT void on_radiobutton_Poly3_toggled(GtkWidget* pWidget, gpointer pData)
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
		gdouble yAxisCoef;
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
		
		// Affichage des repères
		cairo_set_font_size(pCairoEnv1, 10);
		cairo_move_to(pCairoEnv1,-7,(-yLengh/2)+8);
		cairo_show_text(pCairoEnv1, "6 Y(esclave)");
		cairo_move_to(pCairoEnv1,-7,-2);
		cairo_show_text(pCairoEnv1, "0");
		cairo_move_to(pCairoEnv1,xLengh-52,-2);
		cairo_show_text(pCairoEnv1, "X(maître)");
				 
		// Calcul des coéfficients suivant le type de polynôme et affichage des coéfficients directeurs
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly3)))
			{
			a=-2.0+v0+v1;
			b=3.0-2.0*v0-v1;
			c=v0;
			d=0.0;
			gtk_widget_hide(pHscale3); // Cache les curseurs a0 et a1
			gtk_widget_hide(pHscale4);
			
			gtk_label_set_text(GTK_LABEL(pLabel_11),"Cv = 1.5");
			gtk_label_set_text(GTK_LABEL(pLabel_12),"Ca = 6.0");
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
			
			gtk_label_set_text(GTK_LABEL(pLabel_11),"Cv = 1.9");
			gtk_label_set_text(GTK_LABEL(pLabel_12),"Ca = 5.8");
			}
						
		// Abscisses dans le domaine [0;1]
		xAxisCoef=1.0/(xLengh-10);
		
		// Ordonnées dans le domaine [0;6] pour les vitesses et les accélérations
		yAxisCoef=(yLengh/2)/6;
		
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
		
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly3)))
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
	
		// Calcule
		while ((x[0]<=xLengh-10)&(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pCheckbutton_Vitesse))))
		{
		x[0] = x[2];
		x[1] = x[0] + 1;
		x[2] = x[1] + 1;

		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly3)))
			{
			// Calcule une série de trois points suivant la dérivée du polynôme 3
			yV[0] = yAxisCoef*(3*a*pow(xAxisCoef*x[0],2)+2*b*xAxisCoef*x[0]+c);
			yV[1] = yAxisCoef*(3*a*pow(xAxisCoef*x[1],2)+2*b*xAxisCoef*x[1]+c);
			yV[2] = yAxisCoef*(3*a*pow(xAxisCoef*x[2],2)+2*b*xAxisCoef*x[2]+c);
			}
		else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly5)))
			{
			// Calcule une série de trois points suivant la dérivée du polynôme 5
			yV[0] = yAxisCoef*(5*a*pow(xAxisCoef*x[0],4)+4*b*pow(xAxisCoef*x[0],3)+3*c*pow(xAxisCoef*x[0],2)+2*d*xAxisCoef*x[0]+e);
			yV[1] = yAxisCoef*(5*a*pow(xAxisCoef*x[1],4)+4*b*pow(xAxisCoef*x[1],3)+3*c*pow(xAxisCoef*x[1],2)+2*d*xAxisCoef*x[1]+e);
			yV[2] = yAxisCoef*(5*a*pow(xAxisCoef*x[2],4)+4*b*pow(xAxisCoef*x[2],3)+3*c*pow(xAxisCoef*x[2],2)+2*d*xAxisCoef*x[2]+e);
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
	
		// Calcule
		while ((x[0]<=xLengh-10)&(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pCheckbutton_Accel))))
		{
		x[0] = x[2];
		x[1] = x[0] + 1;
		x[2] = x[1] + 1;
		
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly3)))
			// Calcule une série de trois points suivant la double dérivée du polynôme 3
			{
			yA[0] = yAxisCoef*(6*a*xAxisCoef*x[0]+2*b);
			yA[1] = yAxisCoef*(6*a*xAxisCoef*x[1]+2*b);
			yA[2] = yAxisCoef*(6*a*xAxisCoef*x[2]+2*b);
			}
		else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pRadiobutton_Poly5)))
			{
			// Calcule une série de trois points suivant la double dérivée du polynôme 5
			yA[0] = yAxisCoef*(20*a*pow(xAxisCoef*x[0],3)+12*b*pow(xAxisCoef*x[0],2)+6*c*xAxisCoef*x[0]+2*d);
			yA[1] = yAxisCoef*(20*a*pow(xAxisCoef*x[1],3)+12*b*pow(xAxisCoef*x[1],2)+6*c*xAxisCoef*x[1]+2*d);
			yA[2] = yAxisCoef*(20*a*pow(xAxisCoef*x[2],3)+12*b*pow(xAxisCoef*x[2],2)+6*c*xAxisCoef*x[2]+2*d);
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

