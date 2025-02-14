
// Imports.
#include <gtk/gtk.h>

// Functions declaration.
void on_open_clicked(GtkWidget *widget, gpointer text_view);
void on_save_clicked(GtkWidget *widget, gpointer text_view);


// Main function.
int main(int argc, char *argv[]) {
    gtk_init();
    
    GtkWidget *window, *vbox, *toolbar, *open_button, *save_button, *text_view, *scrolled_window;
    
    // Creating the window.
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Simple GTK Notepad");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);
    
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
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_append(GTK_BOX(vbox), scrolled_window);
    
    text_view = gtk_text_view_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), text_view);
    
    g_signal_connect(open_button, "clicked", G_CALLBACK(on_open_clicked), text_view);
    g_signal_connect(save_button, "clicked", G_CALLBACK(on_save_clicked), text_view);
    
    gtk_widget_set_visible(window, TRUE);
    gtk_window_present(GTK_WINDOW(window));
	    
    g_application_run(G_APPLICATION(app), argc, argv);
    
    return 0;
}

void on_open_clicked(GtkWidget *widget, gpointer text_view) {
    GtkWidget *dialog;
    GtkTextBuffer *buffer;
    gchar *filename;
    gchar *content;
    gsize length;
    GError *error = NULL;
    
    dialog = gtk_file_chooser_dialog_new("Open File", GTK_FILE_CHOOSER_ACTION_OPEN, GTK_WINDOW(widget), "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        GFile *file = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(dialog));
        filename = g_file_get_path(file);
        g_object_unref(file);

        if (g_file_get_contents(filename, &content, &length, &error)) {
            buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
            gtk_text_buffer_set_text(buffer, content, length);
            g_free(content);
        } else {
            g_printerr("Error opening file: %s\n", error->message);
            g_error_free(error);
        }
        g_free(filename);
    }
    gtk_window_destroy(GTK_WINDOW(dialog));
}

void on_save_clicked(GtkWidget *widget, gpointer text_view) {
    GtkWidget *dialog;
    GtkTextBuffer *buffer;
    GtkTextIter start, end;
    gchar *filename;
    gchar *content;
    
    dialog = gtk_file_chooser_dialog_new("Save File", GTK_FILE_CHOOSER_ACTION_SAVE, GTK_WINDOW(widget), "Cancel", GTK_RESPONSE_CANCEL, "Save", GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        GFile *file = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(dialog));
        filename = g_file_get_path(file);
        g_object_unref(file);

        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
        gtk_text_buffer_get_bounds(buffer, &start, &end);
        content = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        g_file_set_contents(filename, content, -1, NULL);
        g_free(content);
        g_free(filename);
    }
    gtk_window_destroy(GTK_WINDOW(dialog));
}
