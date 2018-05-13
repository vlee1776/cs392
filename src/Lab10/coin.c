#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

GtkWidget *image2;
GtkWidget *button_box;
GtkWidget *image1;
GtkWidget *button;
static void callback(GtkWidget *widget, gpointer data){
	g_print("Flip");
	g_object_ref(image1);
	g_object_ref(image2);
	int random= rand()%2;
	if (random==1){
		gtk_button_set_label((GtkButton*)button,"tail");
		gtk_button_set_image((GtkButton*)button,image1);
	//	gtk_image_set_from_file((GtkImage*)image1, "head.jpg");	
	}
	else{	
		gtk_button_set_label((GtkButton*)button,"head");
		gtk_button_set_image((GtkButton*)button,image2);
	//	gtk_image_set_from_file((GtkImage*)image1, "tail.jpg");	
	}
}


int main(int argc , char *argv[]){

	GtkWidget *window;
	//GtkWidget *button_box;
	
	gtk_init(&argc, &argv);
	window=gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW (window), "Coin flip");
	gtk_window_set_default_size(GTK_WINDOW(window),200,200);
	button_box=gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	image1= gtk_image_new_from_file ("tail.jpg");	
	image2= gtk_image_new_from_file ("head.jpg");
	gtk_container_add(GTK_CONTAINER(window),button_box);
	button= gtk_button_new_with_label("Press");
	gtk_button_new_with_label("tail.jpg");
	g_signal_connect(button, "clicked", G_CALLBACK (callback), (gpointer)"button");
	gtk_container_add(GTK_CONTAINER (button_box),button);
	
	gtk_button_set_always_show_image((GtkButton*)button,TRUE);
	gtk_container_add(GTK_CONTAINER (button_box),image1);
//	gtk_container_add(GTK_CONTAINER (button_box),image2);
	gtk_widget_show(window);
	gtk_widget_show(button_box);
	gtk_widget_show(button);
	//gtk_widget_show(image1);
	gtk_main();
	return 0;	
}
		

