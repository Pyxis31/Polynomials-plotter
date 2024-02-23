// Evite que poly.h soit inclus plusieurs fois
#ifndef POLY_H
#define POLY_H

/**********************************************
 ********** Directives d'inclusions ***********
 **********************************************
*/

// * Des Headers système *
#include <gtk/gtk.h>

// * Des Headers d'application *

    
/**********************************************
 ********* Définition des structures **********
 **********************************************
*/
typedef struct ParamFnc_np ParamFnc_np; // Structure de pointeurs pour les paramètres de certaines fonctions
struct ParamFnc_np
{
	gpointer pData1;
	gpointer pData2;
	gpointer pData3;
};

    
/**********************************************
 ********* Prototypes des fonctions ***********
 **********************************************
*/
// Fonctions callback
G_MODULE_EXPORT void on_window1_destroy(GtkWidget* pWidget, gpointer pData);
G_MODULE_EXPORT void on_hscale1_value_changed(GtkWidget* pWidget, gpointer pData);
G_MODULE_EXPORT void on_window1_map_event(GtkWidget* pWidget, gpointer pData);
G_MODULE_EXPORT void on_drawingarea1_expose_event(GtkWidget* pWidget, gpointer pData);
G_MODULE_EXPORT void on_hscale2_value_changed(GtkWidget* pWidget, gpointer pData);
G_MODULE_EXPORT void on_imagemenuitem10_button_press_event(GtkWidget* pWidget, gpointer pData);
G_MODULE_EXPORT void on_menuitem6_activate(GtkWidget* pWidget, gpointer pData);
G_MODULE_EXPORT void on_menuitem7_activate(GtkWidget* pWidget, gpointer pData);
G_MODULE_EXPORT void on_checkbutton_Vitesse_toggled(GtkWidget* pWidget, gpointer pData);
G_MODULE_EXPORT void on_checkbutton_Accel_toggled(GtkWidget* pWidget, gpointer pData);
G_MODULE_EXPORT void on_checkbutton_Position_toggled(GtkWidget* pWidget, gpointer pData);
G_MODULE_EXPORT void on_radiobutton_Poly3_toggled(GtkWidget* pWidget, gpointer pData);
G_MODULE_EXPORT void on_hscale3_value_changed(GtkWidget* pWidget, gpointer pData);
G_MODULE_EXPORT void on_hscale4_value_changed(GtkWidget* pWidget, gpointer pData);
G_MODULE_EXPORT void on_droite_clicked(GtkWidget* pWidget, gpointer pData);

// Fonctions applicatives
void fPoly(gdouble v0,gdouble v1,gdouble a0,gdouble a1);

#endif
