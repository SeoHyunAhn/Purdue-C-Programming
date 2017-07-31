#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include <vector>
#include <string>
#include <string.h>
#include "IRCClient.h"
#include "talk-client.h"
#include <cairo.h>

#include <stdlib.h>
#include <time.h>


using namespace std;
GtkListStore * list_rooms;
GtkListStore * list_users;
GtkListStore * list_message;

GtkWidget *usernameEntry;
GtkWidget *passwordEntry;
GtkWidget *roomNameEntry;
GtkWidget *messageEntry;
char * message=NULL;


//--------------------------------------------------------------------------------
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

static void create_account_add_user( GtkWidget *checkbutton,
                                  GtkWidget *entry )
{
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY (usernameEntry));
    user=strdup((char *)entry_text);
    printf("user %s\n", user);
    entry_text = gtk_entry_get_text (GTK_ENTRY (passwordEntry));
    password=strdup((char *)entry_text);
    printf("password %s\n", password);
    
    add_user();
    /*if(!strcmp(response, "OK\r\n")){
        g_signal_connect(G_OBJECT(creatAccountB_window), "destroy",
                         G_CALLBACK(gtk_main_quit), NULL);
    }*/
}
static void check_user_and_password(GtkWidget *checkbutton,
                                    GtkWidget *entry )
{
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY (usernameEntry));
    user=strdup((char *)entry_text);
    printf("user %s\n", user);
    entry_text = gtk_entry_get_text (GTK_ENTRY (passwordEntry));
    password=strdup((char *)entry_text);
    printf("password %s\n", password);
    check_password();
    
}
static void create_Room( GtkWidget *checkbutton,
                        GtkWidget *entry ){
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY (roomNameEntry));
    roomName=strdup((char *)entry_text);
    
    create_room();
}

static void enter_Room(GtkWidget *checkbutton,
                                    GtkWidget *entry){
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY (roomNameEntry));
    roomName=strdup((char *)entry_text);
    enter_room();
    char* msg = (char *)malloc(sizeof(char) * 500);
    strcpy(msg, user);
    strcat(msg, " User has entered the room\r\n");
    send_message(msg);
}
void leaveRoombutton_clicked(GtkWidget *checkbutton,
                             GtkWidget *entry){
    char* msg = (char *)malloc(sizeof(char) * 500);
    strcpy(msg, user);
    strcat(msg, " User has left the room\r\n");
    send_message(msg);
    leave_room();
}

void send_button_clicked(GtkWidget *checkbutton, GtkWidget *entry){
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY (messageEntry));
    message=(char *)malloc(sizeof(char) * 500);
    strcpy(message, (char *)entry_text);
    
    if (message!=NULL && message!="" && message!="\n") {
        send_message(message);
    }
}

//=======================================================

void creatAccountbutton_clicked(GtkWidget *widget, gpointer data) {
    
    GtkWidget *creatAccountB_window;
    GtkWidget *vbox, *hbox;
    
    GtkWidget *cancelbutton;
    GtkWidget *createaccountB;
    GtkWidget * loginB;
    GtkWidget *check;
    gint tmp_pos;
    
   // gtk_init (&argc, &argv);
    
    /* create a new window */
    creatAccountB_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (creatAccountB_window), 200, 200);
    gtk_window_set_title (GTK_WINDOW (creatAccountB_window), "GTK Entry");
    g_signal_connect (creatAccountB_window, "destroy",
                      G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (creatAccountB_window, "delete-event",
                              G_CALLBACK (gtk_widget_destroy),
                              creatAccountB_window);
    
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (creatAccountB_window), vbox);
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
    gtk_editable_insert_text (GTK_EDITABLE (passwordEntry), "password ", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (passwordEntry),
                                0, GTK_ENTRY (passwordEntry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), passwordEntry, TRUE, TRUE, 0);
    gtk_widget_show (passwordEntry);
    
    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_widget_show (hbox);
    check = gtk_check_button_new_with_label ("Visible");
    gtk_box_pack_start (GTK_BOX (hbox), check, TRUE, TRUE, 0);
    g_signal_connect (check, "toggled",
                      G_CALLBACK (entry_toggle_visibility), passwordEntry);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), TRUE);
    gtk_widget_show (check);
    
    cancelbutton = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
    g_signal_connect_swapped (cancelbutton, "clicked",
                              G_CALLBACK (gtk_widget_destroy),
                              creatAccountB_window);
    gtk_box_pack_start (GTK_BOX (vbox), cancelbutton, TRUE, TRUE, 0);
    gtk_widget_set_can_default (cancelbutton, TRUE);
    gtk_widget_grab_default (cancelbutton);
    gtk_widget_show (cancelbutton);
    
    createaccountB = gtk_button_new_with_label("Create Account");
    g_signal_connect_swapped (createaccountB, "clicked",
                              G_CALLBACK (create_account_add_user), //이부분을 고피면 될거에요 이부분이 function부분이니까
                              creatAccountB_window);
    gtk_box_pack_start (GTK_BOX (vbox), createaccountB, TRUE, TRUE, 0);
    gtk_widget_set_can_default (createaccountB, TRUE);
    gtk_widget_grab_default (createaccountB);
    gtk_widget_show (createaccountB);
    
    loginB = gtk_button_new_with_label("Login");
    g_signal_connect_swapped (loginB, "clicked",
                              G_CALLBACK (check_user_and_password), //이부분을 고피면 될거에요 이부분이 function부분이니까
                              creatAccountB_window);
    gtk_box_pack_start (GTK_BOX (vbox), loginB, TRUE, TRUE, 0);
    gtk_widget_set_can_default (loginB, TRUE);
    gtk_widget_grab_default (loginB);
    gtk_widget_show (loginB);
    
    gtk_widget_show (creatAccountB_window);
    
    gtk_main();
    
}
//===============================================================================
//CREATE ROOM

void creatRoombutton_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *creatRoomB_window;
    GtkWidget *vbox, *hbox;
    
    GtkWidget *cancelbutton;
    GtkWidget *createRoomB;
    GtkWidget *check;
    gint tmp_pos;
    
    // gtk_init (&argc, &argv);
    
    /* create a new window */
    creatRoomB_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (creatRoomB_window), 200, 200);
    gtk_window_set_title (GTK_WINDOW (creatRoomB_window), "GTK Entry");
    g_signal_connect (creatRoomB_window, "destroy",
                      G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (creatRoomB_window, "delete-event",
                              G_CALLBACK (gtk_widget_destroy),
                              creatRoomB_window);
    
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (creatRoomB_window), vbox);
    gtk_widget_show (vbox);
    
    roomNameEntry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (roomNameEntry), 50);
    g_signal_connect (roomNameEntry, "activate",
                      G_CALLBACK (enter_callback),
                      roomNameEntry);
    gtk_entry_set_text (GTK_ENTRY (roomNameEntry), "Type");
    tmp_pos = GTK_ENTRY (roomNameEntry)->text_length;
    gtk_editable_insert_text (GTK_EDITABLE (roomNameEntry), " RoomName", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (roomNameEntry),
                                0, GTK_ENTRY (roomNameEntry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), roomNameEntry, TRUE, TRUE, 0);
    gtk_widget_show (roomNameEntry);
    
    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_widget_show (hbox);
    
    cancelbutton = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
    g_signal_connect_swapped (cancelbutton, "clicked",
                              G_CALLBACK (gtk_widget_destroy),
                              creatRoomB_window);
    gtk_box_pack_start (GTK_BOX (vbox), cancelbutton, TRUE, TRUE, 0);
    gtk_widget_set_can_default (cancelbutton, TRUE);
    gtk_widget_grab_default (cancelbutton);
    gtk_widget_show (cancelbutton);
    
    createRoomB = gtk_button_new_with_label("Create Room");
    g_signal_connect_swapped (createRoomB, "clicked",
                              G_CALLBACK (create_Room), //이부분을 고피면 될거에요 이부분이 function부분이니까
                              createRoomB);
    gtk_box_pack_start (GTK_BOX (vbox), createRoomB, TRUE, TRUE, 0);
    gtk_widget_set_can_default (createRoomB, TRUE);
    gtk_widget_grab_default (createRoomB);
    gtk_widget_show (createRoomB);
    
    gtk_widget_show (creatRoomB_window);
    
    gtk_main();
    
}

//ENTER ROOM
void enterRoombutton_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *creatRoomB_window;
    GtkWidget *vbox, *hbox;
    
    GtkWidget *cancelbutton;
    GtkWidget *createRoomB;
    GtkWidget *check;
    gint tmp_pos;
    
    // gtk_init (&argc, &argv);
    
    /* create a new window */
    creatRoomB_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (creatRoomB_window), 200, 200);
    gtk_window_set_title (GTK_WINDOW (creatRoomB_window), "GTK Entry");
    g_signal_connect (creatRoomB_window, "destroy",
                      G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (creatRoomB_window, "delete-event",
                              G_CALLBACK (gtk_widget_destroy),
                              creatRoomB_window);
    
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (creatRoomB_window), vbox);
    gtk_widget_show (vbox);
    
    roomNameEntry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (roomNameEntry), 50);
    g_signal_connect (roomNameEntry, "activate",
                      G_CALLBACK (enter_callback),
                      roomNameEntry);
    gtk_entry_set_text (GTK_ENTRY (roomNameEntry), "Type");
    tmp_pos = GTK_ENTRY (roomNameEntry)->text_length;
    gtk_editable_insert_text (GTK_EDITABLE (roomNameEntry), " RoomName", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (roomNameEntry),
                                0, GTK_ENTRY (roomNameEntry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), roomNameEntry, TRUE, TRUE, 0);
    gtk_widget_show (roomNameEntry);
    
    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_widget_show (hbox);
    
    cancelbutton = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
    g_signal_connect_swapped (cancelbutton, "clicked",
                              G_CALLBACK (gtk_widget_destroy),
                              creatRoomB_window);
    gtk_box_pack_start (GTK_BOX (vbox), cancelbutton, TRUE, TRUE, 0);
    gtk_widget_set_can_default (cancelbutton, TRUE);
    gtk_widget_grab_default (cancelbutton);
    gtk_widget_show (cancelbutton);
    
    createRoomB = gtk_button_new_with_label("Enter Room");
    g_signal_connect_swapped (createRoomB, "clicked",
                              G_CALLBACK (enter_Room), //이부분을 고피면 될거에요 이부분이 function부분이니까
                              createRoomB);
    gtk_box_pack_start (GTK_BOX (vbox), createRoomB, TRUE, TRUE, 0);
    gtk_widget_set_can_default (createRoomB, TRUE);
    gtk_widget_grab_default (createRoomB);
    gtk_widget_show (createRoomB);
    
    gtk_widget_show (creatRoomB_window);
    
    gtk_main();
    
}

//===============================================================================

void update_list_rooms() {
    GtkTreeIter iter;
    int i;
    if (roomName==NULL ) {
        return;
    }
    print_room();
    if (strcmp(response, "DENIED\r\n") && strcmp(response, "ERROR (Wrong password)\r\n)") &&strcmp(response, "UNKOWN COMMAND\r\n")&& strcmp(response, "ERROR (User not in room)\r\n")&& strcmp(response, "")) {
        gchar * msg = (gchar*) response;
        gtk_list_store_clear(GTK_LIST_STORE(list_rooms));
        gtk_list_store_append (GTK_LIST_STORE (list_rooms), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_rooms),
                            &iter,
                            0, msg,
                            -1);
        
    }
    
    /* Add some messages to the window
    for (i = 0; i < int(roomList.size()); i++) {
        gchar *msg = g_strdup_printf ("%s", roomList[i].c_str());
        gtk_list_store_append (GTK_LIST_STORE (list_rooms), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_rooms),
                            &iter,
                            0, msg,
                            -1);
        g_free (msg);
    }*/
}

void update_list_users(){
    GtkTreeIter iter;
    int i;
    if (roomName==NULL || userinRoom.empty()) {
        return;
    }
    print_users_in_room();
    if (strcmp(response, "DENIED\r\n") && strcmp(response, "ERROR (Wrong password)\r\n)")&& strcmp(response, "ERROR (User not in room)\r\n")) {
        gchar * msg = (gchar*) response;
        gtk_list_store_clear(GTK_LIST_STORE(list_users));
        gtk_list_store_append (GTK_LIST_STORE (list_users), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_users),
                            &iter,
                            0, msg,
                            -1);
        
    }
    /* Add some messages to the window
    for (i = 0; i < int(userinRoom.size()); i++) {
        gchar *msg = g_strdup_printf ("%s", userinRoom[i].c_str());
        gtk_list_store_append (GTK_LIST_STORE (list_users), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_users),
                            &iter,
                            0, msg,
                            -1);
        g_free (msg);
    }*/
}
void update_list_message(){
    GtkTreeIter iter;
    int i;
    if (roomName==NULL && message == NULL) {
        return;
    }
    get_messages(1);
    if (strcmp(response, "DENIED\r\n") && strcmp(response, "ERROR (Wrong password)\r\n)") && strcmp(response, "ERROR (User not in room)\r\n") && strcmp(response, "NO-NEW-MESSAGES\r\n")) {
        gchar * msg = (gchar*) response;
        gtk_list_store_clear(GTK_LIST_STORE(list_message));
        gtk_list_store_append (GTK_LIST_STORE (list_message), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_message),
                            &iter,
                            0, msg,
                            -1);
        
    }
    /* Add some messages to the window
    for (i = 0; i < int(getmessages.size()); i++) {
        gchar *msg = g_strdup_printf ("%s", getmessages[i].c_str());
        gtk_list_store_append (GTK_LIST_STORE (list_message), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_message),
                            &iter,
                            0, msg,
                            -1);
        g_free (msg);
    }*/
}

/* Create the list of "messages" */
static GtkWidget *create_list( const char * titleColumn, GtkListStore *model )
{
    GtkWidget *scrolled_window;
    GtkWidget *tree_view;
    //GtkListStore *model;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;
    
    int i;
    
    /* Create a new scrolled window, with scrollbars only if needed */
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    
    //model = gtk_list_store_new (1, G_TYPE_STRING);
    tree_view = gtk_tree_view_new ();
    gtk_container_add (GTK_CONTAINER (scrolled_window), tree_view);
    gtk_tree_view_set_model (GTK_TREE_VIEW (tree_view), GTK_TREE_MODEL (model));
    gtk_widget_show (tree_view);
    
    cell = gtk_cell_renderer_text_new ();
    
    column = gtk_tree_view_column_new_with_attributes (titleColumn,
                                                       cell,
                                                       "text", 0,
                                                       NULL);
    
    gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view),
                                 GTK_TREE_VIEW_COLUMN (column));
    
    return scrolled_window;
}

/* Add some text to our text widget - this is a callback that is invoked
 when our window is realized. We could also force our window to be
 realized with gtk_widget_realize, but it would have to be part of
 a hierarchy first */

static void insert_text( GtkTextBuffer *buffer, const char * initialText )
{
    GtkTextIter iter;
    
    gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);
    gtk_text_buffer_insert (buffer, &iter, initialText,-1);
}

/* Create a scrolled text area that displays a "message" */
static GtkWidget *create_text( const char * initialText )
{
    GtkWidget *scrolled_window;
    GtkWidget *view;
    GtkTextBuffer *buffer;
    
    view = gtk_text_view_new ();
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
    
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    
    gtk_container_add (GTK_CONTAINER (scrolled_window), view);
    insert_text (buffer, initialText);
    
    gtk_widget_show_all (scrolled_window);
    
    return scrolled_window;
}
static gboolean
time_handler(GtkWidget *widget)
{
    //printf("Printing for handler\n");
   // if (!roomList.empty()) {
        //print_room();
        update_list_rooms();
        //print_users_in_room();
    //}
    //if (!userinRoom.empty()) {
       // print_users_in_room();
        update_list_users();
    //}
    //if (!getmessages.empty()) {
      //  get_messages(1);
        update_list_message();
    //}
    return TRUE;
}


int main( int   argc,
         char *argv[] )
{
    GtkWidget *window;
    GtkWidget *listRoom;
    
    GtkWidget *listUser;
    GtkWidget *listMsg;
    GtkWidget *messages;
    GtkWidget *myMessage;
  
    
    char line[MAX_MESSAGE_LEN+1];
    
    if (argc < 5) {
        printUsage();
    }
    
    host = argv[1];
    sport = argv[2];
    user = argv[3];
    password = argv[4];
    
    printf("\nStarting talk-client %s %s %s %s\n", host, sport, user, password);
    
    // Convert port to number
    sscanf(sport, "%d", &port);
    
    //add_user();
    
    //-------------------------------------------------------------------
    gtk_init (&argc, &argv);
    GdkColor color;
    gdk_color_parse ("#149AC1", &color);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Paned Windows");
    g_signal_connect (window, "destroy",
                      G_CALLBACK (gtk_main_quit), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (GTK_WIDGET (window), 450, 400);
    gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);
    
    // Create a table to place the widgets. Use a 7x4 Grid (7 rows x 4 columns)
    GtkWidget *table = gtk_table_new (10, 4, TRUE);
    gtk_container_add (GTK_CONTAINER (window), table);
    gtk_table_set_row_spacings(GTK_TABLE (table), 5);
    gtk_table_set_col_spacings(GTK_TABLE (table), 5);
    gtk_widget_show (table);
    
    // Add list of rooms. Use columns 0 to 4 (exclusive) and rows 0 to 4 (exclusive)
    list_rooms = gtk_list_store_new (1, G_TYPE_STRING);
    update_list_rooms();
    listRoom = create_list ("Rooms", list_rooms);
    gtk_table_attach_defaults (GTK_TABLE (table), listRoom, 2, 4, 0, 2);
    gtk_widget_show (listRoom);
    
    //Add user
    list_users = gtk_list_store_new (1, G_TYPE_STRING);
    update_list_users();
    listUser = create_list ("Users", list_users);
    gtk_table_attach_defaults (GTK_TABLE (table), listUser, 0, 2, 0, 2);
    gtk_widget_show (listUser);
    
    // Add messages text. Use columns 0 to 4 (exclusive) and rows 4 to 7 (exclusive)
    list_message =gtk_list_store_new (1, G_TYPE_STRING);
    update_list_message();
    listMsg = create_list ("Message", list_message);
    gtk_table_attach_defaults (GTK_TABLE (table), listMsg, 0, 4, 2, 5);
    gtk_widget_show (listMsg);
    
    //messages = create_text ("Peter: Hi how are you\nMary: I am fine, thanks and you?\nPeter: Fine thanks.\n");
    //gtk_table_attach_defaults (GTK_TABLE (table), messages, 0, 4, 2, 5);
    gtk_widget_show (listMsg);
    
    
    // Add messages text. Use columns 0 to 4 (exclusive) and rows 4 to 7 (exclusive)
    
    messageEntry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (messageEntry), 50);
    g_signal_connect (messageEntry, "activate",
                      G_CALLBACK (enter_callback),
                      messageEntry);
    gtk_entry_set_text (GTK_ENTRY (messageEntry), "I am fine, thanks and you?\n");
     gtk_editable_select_region (GTK_EDITABLE (messageEntry),
                                0, GTK_ENTRY (messageEntry)->text_length);
    //gtk_box_pack_start (GTK_BOX (vbox), messageEntry, TRUE, TRUE, 0);
    gtk_table_attach_defaults (GTK_TABLE (table), messageEntry, 0, 4, 5, 7);
    
    gtk_widget_show (messageEntry);
    
    
    
    // Add send button. Use columns 0 to 1 (exclusive) and rows 4 to 7 (exclusive)
    GtkWidget *send_button = gtk_button_new_with_label ("Send");
    gtk_table_attach_defaults(GTK_TABLE (table), send_button, 0, 1, 7, 8);
    g_signal_connect_swapped (send_button, "clicked",
                              G_CALLBACK (send_button_clicked),
                              window);
    
    
    gtk_widget_show (send_button);
    
    //Login
    //Add create user
    GtkWidget *createUser_Button = gtk_button_new_with_label ("Creat Account");
    gtk_table_attach_defaults(GTK_TABLE (table), createUser_Button, 1, 2, 7, 8);
    g_signal_connect_swapped (createUser_Button, "clicked",
                              G_CALLBACK (creatAccountbutton_clicked),
                              window);
    gtk_widget_show (createUser_Button);
    
    //Add create room
    GtkWidget *createRoom_button = gtk_button_new_with_label ("Create Room");
    gtk_table_attach_defaults(GTK_TABLE (table), createRoom_button, 2, 3, 7, 8);
    g_signal_connect_swapped (createRoom_button, "clicked",
                              G_CALLBACK (creatRoombutton_clicked),
                              window);
    gtk_widget_show (createRoom_button);
    
    //Add enter room
    GtkWidget *enterRoom_button = gtk_button_new_with_label ("Enter Room");
    gtk_table_attach_defaults(GTK_TABLE (table), enterRoom_button, 3, 4, 7, 8);
    g_signal_connect_swapped (enterRoom_button, "clicked",
                              G_CALLBACK (enterRoombutton_clicked),
                              window);
    gtk_widget_show (enterRoom_button);
    
    //Add enter room
    GtkWidget *leaveRoom_button = gtk_button_new_with_label ("Leave Room");
    gtk_table_attach_defaults(GTK_TABLE (table), leaveRoom_button, 0, 1,8, 9);
    g_signal_connect_swapped (leaveRoom_button, "clicked",
                              G_CALLBACK (leaveRoombutton_clicked),
                              window);
    gtk_widget_show (leaveRoom_button);
    //while (true) {
    g_timeout_add(5000, (GSourceFunc) time_handler, (gpointer) table);
    g_timeout_add(5000, (GSourceFunc) time_handler, (gpointer) window);
    time_handler(window);
    gtk_widget_show (table);
    gtk_widget_show (window);
    gtk_main ();
    //}
    
    return 0;
}
