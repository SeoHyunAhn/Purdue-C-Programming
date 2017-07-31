#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

static void enter_callback( GtkWidget *widget,
                            GtkWidget *entry )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}

static void entry_toggle_editable( GtkWidget *checkbutton,
                                   GtkWidget *entry )
{
  gtk_editable_set_editable (GTK_EDITABLE (entry),
                             GTK_TOGGLE_BUTTON (checkbutton)->active);
}

static void entry_toggle_visibility( GtkWidget *checkbutton,
                                     GtkWidget *entry )
{
  gtk_entry_set_visibility (GTK_ENTRY (entry),
			    GTK_TOGGLE_BUTTON (checkbutton)->active);
}

int main( int   argc,
          char *argv[] )
{

    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *usernameEntry;
    GtkWidget *passwordEntry;
    GtkWidget *cancelbutton;
    GtkWidget *createaccountB;
    GtkWidget *check;
    gint tmp_pos;
    
    gtk_init (&argc, &argv);
    
    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 200, 200);
    gtk_window_set_title (GTK_WINDOW (window), "GTK Entry");
    g_signal_connect (window, "destroy",
                      G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (window, "delete-event",
                              G_CALLBACK (gtk_widget_destroy),
                              window);
    
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);
    
    usernameEntry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (usernameEntry), 50);
    g_signal_connect (usernameEntry, "activate",
                      G_CALLBACK (enter_callback),
                      usernameEntry);
    gtk_entry_set_text (GTK_ENTRY (usernameEntry), "Type");
    tmp_pos = GTK_ENTRY (usernameEntry)->text_length;
    gtk_editable_insert_text (GTK_EDITABLE (usernameEntry), " username", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (usernameEntry),
                                0, GTK_ENTRY (usernameEntry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), usernameEntry, TRUE, TRUE, 0);
    gtk_widget_show (usernameEntry);
    
    passwordEntry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (passwordEntry), 50);
    g_signal_connect (passwordEntry, "activate",
                      G_CALLBACK (enter_callback),
                      passwordEntry);
    gtk_entry_set_text (GTK_ENTRY (passwordEntry), "Type ");
    tmp_pos = GTK_ENTRY (passwordEntry)->text_length;
    gtk_editable_insert_text (GTK_EDITABLE (passwordEntry), "password username", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (passwordEntry),
                                0, GTK_ENTRY (passwordEntry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), passwordEntry, TRUE, TRUE, 0);
    gtk_widget_show (passwordEntry);
    
    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_widget_show (hbox);
    
    /* check = gtk_check_button_new_with_label ("Editable");
     gtk_box_pack_start (GTK_BOX (hbox), check, TRUE, TRUE, 0);
     g_signal_connect (check, "toggled",
     G_CALLBACK (entry_toggle_editable), entry);
     gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), TRUE);
     gtk_widget_show (check);*/
    
    check = gtk_check_button_new_with_label ("Visible");
    gtk_box_pack_start (GTK_BOX (hbox), check, TRUE, TRUE, 0);
    g_signal_connect (check, "toggled",
                      G_CALLBACK (entry_toggle_visibility), passwordEntry);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), TRUE);
    gtk_widget_show (check);
    
    cancelbutton = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
    g_signal_connect_swapped (cancelbutton, "clicked",
                              G_CALLBACK (gtk_widget_destroy),
                              window);
    gtk_box_pack_start (GTK_BOX (vbox), cancelbutton, TRUE, TRUE, 0);
    gtk_widget_set_can_default (cancelbutton, TRUE);
    gtk_widget_grab_default (cancelbutton);
    gtk_widget_show (cancelbutton);
    
    createaccountB = gtk_button_new_with_label("Create Account");
    g_signal_connect_swapped (createaccountB, "clicked",
                              G_CALLBACK (gtk_widget_destroy), //이부분을 고피면 될거에요 이부분이 function부분이니까
                              window);
    gtk_box_pack_start (GTK_BOX (vbox), createaccountB, TRUE, TRUE, 0);
    gtk_widget_set_can_default (createaccountB, TRUE);
    gtk_widget_grab_default (createaccountB);
    gtk_widget_show (createaccountB);
    
    gtk_widget_show (window);
    
    gtk_main();
    
}
