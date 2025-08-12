#include "comandos.h"



void show_Settings_Comando(float h_view_lo, float h_view_hi, float v_view_lo, float v_view_hi,
                   int float_precision, int integral_steps, bool draw_axis, 
                   bool erase_plots, bool draw_connected_dots) {

	printf("h_view_lo: %f\n", h_view_lo);
	printf("h_view_hi: %f\n", h_view_hi);
	printf("v_view_lo: %f\n", v_view_lo);
	printf("v_view_hi: %f\n", v_view_hi);
	printf("float_precision: %d\n", float_precision);
	printf("integral_steps: %d\n", integral_steps);
	printf("Draw Axis: %s\n", draw_axis ? "ON" : "OFF");
	printf("Erase Plots: %s\n", erase_plots ? "ON" : "OFF");
	printf("Connect Dots: %s\n", draw_connected_dots ? "ON" : "OFF");

}



void matriz_Error() {
	printf("ERROR: Matrix limits out of boundaries.\n");
}



void show_About_Comando() {
	printf("+---------------------------------+\n");
    printf("|     Ana Paula B. Pereira        |\n");
    printf("|          202200560210           |\n");
    printf("+---------------------------------+\n\n");
}