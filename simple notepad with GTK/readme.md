
# Simple notepad made using GTK
This is a simple text editor made using GTK.
It can open a text file and display its contents.
You can edit the contents and save it back to the text file.

**How to compile:**
gcc $(pkg-config --cflags gtk4) -o notepad main.c $(pkg-config --libs gtk4)