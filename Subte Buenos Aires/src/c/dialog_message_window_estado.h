/* -------------------------------------- *
 * Subte Buenos Aires (pebble)            *
 * v0.6                                   *
 *										  *
 * dialog_message_window_estado.h		  *
 *										  *
 * al hacer click en un item del menu     *
 * vengo aquí							  *
 *										  *
 * Benjamin Smith                         *
 * -------------------------------------- */

#pragma once

#include <pebble.h>

Window* estado_window;

TextLayer* title_text_layer;
TextLayer* estado_text_layer;
 
char textTituloEstado[8];
char textEstadoEstado[100];

/* Load all Window sub-elements */
void estado_window_load(Window *estado_window)
{
	//set both text layers
	title_text_layer = text_layer_create(GRect(0, 0, PBL_IF_ROUND_ELSE(180,144), 34));
	estado_text_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(20,0),34,PBL_IF_ROUND_ELSE(160,144),168-34));
	
	//config titulo
	text_layer_set_font(title_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
	text_layer_set_background_color(title_text_layer, GColorBlack);
	text_layer_set_text_color(title_text_layer, GColorWhite);
	#if defined(PBL_ROUND)
	text_layer_set_text_alignment(title_text_layer,GTextAlignmentCenter);
	#endif

	//config estado
	text_layer_set_font(estado_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
	text_layer_set_background_color(estado_text_layer, GColorClear);
	text_layer_set_text_color(estado_text_layer, GColorBlack);

	layer_add_child(window_get_root_layer(estado_window), (Layer*) title_text_layer);
	text_layer_set_text(title_text_layer, textTituloEstado);

	layer_add_child(window_get_root_layer(estado_window), (Layer*) estado_text_layer);
	text_layer_set_text(estado_text_layer, textEstadoEstado);
}
 
/* Un-load all Window sub-elements */
void estado_window_unload(Window *window)
{
	text_layer_destroy(title_text_layer);
	text_layer_destroy(estado_text_layer);
	window_destroy(window);
	estado_window = NULL;
}

void dialog_message_window_estado_push(char* textTituloLocal,char* textEstadoLocal) {
	strcpy(textTituloEstado,textTituloLocal);
	strcpy(textEstadoEstado,textEstadoLocal);
	if(!estado_window) 
	{
		estado_window = window_create();
		window_set_background_color(estado_window, GColorWhite);
		window_set_window_handlers(estado_window, (WindowHandlers) 
	{
		.load = estado_window_load,
		.unload = estado_window_unload,        
	});
	}
	window_stack_push(estado_window, true);
}