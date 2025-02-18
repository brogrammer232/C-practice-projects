
// Imports.
#include <gtk/gtk.h>


// Global variables.
GtkWidget *text_view;
gchar *FILENAME;


// Functions declaration.
static void activate(GtkApplication *app, gpointer user_data);
static void on_file_selected(GObject *object, GAsyncResult *res,
    gpointer user_data);
static void on_open_clicked(GtkWidget *widget, gpointer text_view);
static void on_save_clicked(GtkWidget *widget, gpointer text_view);
static void on_save_clicked2(GtkWidget *widget, gpointer text_view);
static void on_save_file_selected(GObject *object, GAsyncResult *res,
    gpointer user_data);


// Main function.
int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.notepad", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    g_free(FILENAME);

    return status;
}


// Functions definition.
static void activate(GtkApplication *app, gpointer user_data) {
    // Variables.
    GtkWidget *window, *vbox, *toolbar, *open_button, *save_button,
              *scrolled_window;


    // Creating the window.
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Simple GTK Notepad");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(
        window, "destroy", G_CALLBACK(gtk_window_close), NULL);


    // Working on the layout.
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(vbox), toolbar);

    open_button = gtk_button_new_with_label("Open");
    save_button = gtk_button_new_with_label("Save");
    gtk_box_append(GTK_BOX(toolbar), open_button);
    gtk_box_append(GTK_BOX(toolbar), save_button);

    scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_append(GTK_BOX(vbox), scrolled_window);

    text_view = gtk_text_view_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window),
        text_view);

    // Handling expansion.
    gtk_widget_set_vexpand(vbox, TRUE);
    gtk_widget_set_vexpand(scrolled_window, TRUE);
    gtk_widget_set_vexpand(text_view, TRUE);
    gtk_widget_set_size_request(text_view, 600, 400);
    gtk_widget_set_size_request(scrolled_window, 600, 400);

    g_signal_connect(open_button, "clicked", G_CALLBACK(on_open_clicked),
        text_view);
    // g_signal_connect(save_button, "clicked", G_CALLBACK(on_save_clicked),
    //     text_view);
    g_signal_connect(save_button, "clicked", G_CALLBACK(on_save_clicked2),
        text_view);


    // Making the window visible.
    gtk_window_present(GTK_WINDOW(window));
}


static void on_file_selected(GObject *object, GAsyncResult *res,
    gpointer user_data) {
    /* This function runs after interaction with the dialog opened when
    "open" is clicked. */
    GtkFileDialog *dialog = GTK_FILE_DIALOG(object);
    GFile *file;
    gchar *filename;
    GtkTextBuffer *buffer;
    gchar *content;
    gsize length;
    GError *error = NULL;

    file = gtk_file_dialog_open_finish(dialog, res, NULL);
    if (file) {
        filename = g_file_get_path(file);
        FILENAME = g_strdup(filename);

        if (g_file_get_contents(filename, &content, &length, &error)) {
            buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
            gtk_text_buffer_set_text(buffer, content, length);
            g_free(content);
        }
        else {
            g_printerr("Error opening file: %s\n", error->message);
            g_error_free(error);
        }

        g_free(filename);
        g_object_unref(file);
    }

    gtk_window_destroy(GTK_WINDOW(dialog));
}


static void on_open_clicked(GtkWidget *widget, gpointer text_view) {
    /* This function runs when the "open" button is clicked. */
    GtkFileDialog *dialog;

    dialog = gtk_file_dialog_new();
    gtk_file_dialog_open(dialog, GTK_WINDOW(widget), NULL,
        on_file_selected, NULL);
}


// static void on_save_clicked(GtkWidget *widget, gpointer text_view) {
//     /* This function runs when the "save" button is clicked. */
//     GtkFileDialog *dialog;
//     dialog = gtk_file_dialog_new();
//     gtk_file_dialog_save(dialog, GTK_WINDOW(widget), NULL,
//         on_save_file_selected, NULL);
// }


static void on_save_clicked2(GtkWidget *widget, gpointer text_view) {
    /* This function saves the currently opened file. */
    GtkTextBuffer *buffer;
    GtkTextIter start, end;
    gchar *content;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    content = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    g_file_set_contents(FILENAME, content, -1, NULL);
    
    g_free(content);
}


// static void on_save_file_selected(GObject *object, GAsyncResult *res,
//     gpointer user_data) {
//     /* This function saves the file contents. */
//     GtkFileDialog *dialog = GTK_FILE_DIALOG(object);
//     GFile *file;
//     gchar *filename;
//     GtkTextBuffer *buffer;
//     gchar *content;
//     GtkTextIter start, end;

//     file = gtk_file_dialog_open_finish(dialog, res, NULL);
//     if (file) {
//         filename = g_file_get_path(file);

//         buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
//         gtk_text_buffer_get_bounds(buffer, &start, &end);
//         content = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
//         g_file_set_contents(filename, content, -1, NULL);
//         g_free(filename);
//         g_free(content);
//     }
//     gtk_window_destroy(GTK_WINDOW(dialog));
// }