#include <gtk/gtk.h>

#include "smtk-app.h"
#include "smtk-app-win.h"
#include "smtk-keys-win.h"

struct _SmtkAppWin {
	GtkApplicationWindow parent_instance;
	GtkWidget *keys_win_switch;
	GtkWidget *keys_win;
};
G_DEFINE_TYPE(SmtkAppWin, smtk_app_win, GTK_TYPE_APPLICATION_WINDOW)

// See <https://mail.gnome.org/archives/networkmanager-list/2010-October/msg00129.html>.
// notify of property have one more argument for property
// in the middle of instance and object.
static void smtk_app_win_on_switch_active(SmtkAppWin *win, GParamSpec *prop, GtkSwitch *keys_win_switch)
{
	// g_print("%s\n", g_type_name(G_TYPE_FROM_INSTANCE(keys_win_switch)));

	if (gtk_switch_get_active(GTK_SWITCH(win->keys_win_switch))) {
		if (win->keys_win == NULL) {
			win->keys_win = smtk_keys_win_new();
			gtk_window_present(GTK_WINDOW(win->keys_win));
		}
	} else {
		if (win->keys_win != NULL) {
			gtk_widget_destroy(GTK_WIDGET(win->keys_win));
			win->keys_win = NULL;
		}
	}
}

static void smtk_app_win_init(SmtkAppWin *win)
{
	// GtkWidget *switch_label = gtk_label_new(_("Start"));
	// gtk_widget_set_hexpand(switch_label, FALSE);
	// gtk_widget_set_parent(switch_label, GTK_WIDGET(win));
	// win->canvas_switch = gtk_switch_new();
	// gtk_widget_set_hexpand(win->canvas_switch, FALSE);
	// // In GTK4 we can just add children here.
	// gtk_widget_set_parent(win->canvas_switch, GTK_WIDGET(win));

	gtk_widget_init_template(GTK_WIDGET(win));
}

// static void smtk_app_win_dispose(GObject *object)
// {
// 	SmtkAppWin *win = SMTK_APP_WIN(object);
//
// 	g_clear_pointer(&win->canvas_switch, gtk_widget_unparent);
//
// 	G_OBJECT_CLASS(smtk_app_win_parent_class)->dispose(object);
// }

static void smtk_app_win_class_init(SmtkAppWinClass *win_class)
{
	// // In GTK4, we need to free children which is added in code in dispose.
	// G_OBJECT_CLASS(win_class)->dispose = smtk_app_win_dispose;

	// // In GTK4, we need to set a layout manager to add childrens in code.
	// gtk_widget_class_set_layout_manager_type(GTK_WIDGET_CLASS(win_class),
	// 					 GTK_TYPE_BOX_LAYOUT);

	gtk_widget_class_set_template_from_resource(
		GTK_WIDGET_CLASS(win_class),
		"/one/alynx/showmethekey/smtk-app-win.ui");
	gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(win_class), SmtkAppWin, keys_win_switch);
	gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(win_class), smtk_app_win_on_switch_active);
}

GtkWidget *smtk_app_win_new(SmtkApp *app)
{
	return g_object_new(SMTK_TYPE_APP_WIN, "application", app, NULL);
}

GtkWidget *smtk_app_win_get_keys_win_switch(SmtkAppWin *win)
{
	return win->keys_win_switch;
}