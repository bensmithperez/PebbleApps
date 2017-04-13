/* -------------------------------------- *
 * Subte Buenos Aires (pebble)            *
 * v0.6                                   *
 *										  *
 * main.c <-- menu principal 			  *
 *										  *
 * Benjamin Smith                         *
 * -------------------------------------- */

#include <pebble.h>
#include "dialog_message_window_estado.h"
Window* window;
MenuLayer *menu_layer;

static StatusBarLayer *s_status_bar;//como estoy usando sdk3 tengo que agregar la "status bar"

// -- TODAS MIS STRINGS --
//estados... (de 100 para evitar crashes)
char textoEstadoLineaA[100] = "Cargando...";
char textoEstadoLineaB[100] = "Cargando...";
char textoEstadoLineaC[100] = "Cargando...";
char textoEstadoLineaD[100] = "Cargando...";
char textoEstadoLineaE[100] = "Cargando...";
char textoEstadoLineaH[100] = "Cargando...";
char textoEstadoLineaP[100] = "Cargando...";
char textoEstadoLineaU[100] = "Cargando...";

//titulos...
char textoTituloLineaA[8] = "Linea A";
char textoTituloLineaB[8] = "Linea B";
char textoTituloLineaC[8] = "Linea C";
char textoTituloLineaD[8] = "Linea D";
char textoTituloLineaE[8] = "Linea E";
char textoTituloLineaH[8] = "Linea H";
char textoTituloLineaP[8] = "Linea P";
char textoTituloLineaU[8] = "Linea U";

//coso para las keys del json
enum 
{
	KEY_LINEAA = 0,
	KEY_LINEAB = 1,
	KEY_LINEAC = 2,
	KEY_LINEAD = 3,
	KEY_LINEAE = 4,
	KEY_LINEAH = 5,
	KEY_LINEAP = 6,
	KEY_LINEAU = 7,
};

// -- COSOS PARA CUANDO RECIBO UN MENSAJE --
void process_tuple(Tuple *t)
{
	//tomo la key
	int key = t->key;

	//tomo el current string value (el mensaje del json)
	char string_value[100];
	strcpy(string_value, t->value->cstring);

	//decido que hacer 
	switch(key) 
	{
		case KEY_LINEAA:
			snprintf(textoEstadoLineaA, sizeof(textoEstadoLineaA), "%s", string_value);
			break;
		case KEY_LINEAB:
			snprintf(textoEstadoLineaB, sizeof(textoEstadoLineaB), "%s", string_value);
			break;
		case KEY_LINEAC:
			snprintf(textoEstadoLineaC, sizeof(textoEstadoLineaC), "%s", string_value);
			break;
		case KEY_LINEAD:
			snprintf(textoEstadoLineaD, sizeof(textoEstadoLineaD), "%s", string_value);
			break;
		case KEY_LINEAE:
			snprintf(textoEstadoLineaE, sizeof(textoEstadoLineaE), "%s", string_value);
			break;
		case KEY_LINEAH:
			snprintf(textoEstadoLineaH, sizeof(textoEstadoLineaH), "%s", string_value);
			break;
		case KEY_LINEAP:
			snprintf(textoEstadoLineaP, sizeof(textoEstadoLineaP), "%s", string_value);
			break;
		case KEY_LINEAU:
			snprintf(textoEstadoLineaU, sizeof(textoEstadoLineaU), "%s", string_value);
			break;
	}
}

static void in_received_handler(DictionaryIterator *iter, void *context)
{
	(void) context;
	 
	//obtengo data
	Tuple *t = dict_read_first(iter);
	while(t != NULL)
	{
		process_tuple(t);
		 
		//el siguiente
		t = dict_read_next(iter);
	}
	
	menu_layer_reload_data(menu_layer); //para que se actualice el menu
}

// -- COSOS PARA CREAR EL MENU -- 
void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
	switch(cell_index->row)
	{
		case 0:
			menu_cell_basic_draw(ctx, cell_layer, textoTituloLineaA, textoEstadoLineaA, NULL);
		    break;
		case 1:
			menu_cell_basic_draw(ctx, cell_layer, textoTituloLineaB, textoEstadoLineaB, NULL);
		    break;
		case 2:
			menu_cell_basic_draw(ctx, cell_layer, textoTituloLineaC, textoEstadoLineaC, NULL);
		    break;
		case 3:
			menu_cell_basic_draw(ctx, cell_layer, textoTituloLineaD, textoEstadoLineaD, NULL);
		    break;
		case 4:
			menu_cell_basic_draw(ctx, cell_layer, textoTituloLineaE, textoEstadoLineaE, NULL);
		    break;
		case 5:
			menu_cell_basic_draw(ctx, cell_layer, textoTituloLineaH, textoEstadoLineaH, NULL);
		    break;
		case 6:
			menu_cell_basic_draw(ctx, cell_layer, textoTituloLineaP, textoEstadoLineaP, NULL);
		    break;
		case 7:
			menu_cell_basic_draw(ctx, cell_layer, textoTituloLineaU, textoEstadoLineaU, NULL);
    		break;
	}
}

uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
	return 8;
}

void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{ 
	int which = cell_index->row; // que fila?

	char textTitulo[8];
	char textEstado[100];

	switch(which)
	{
		case 0:
			strcpy(textTitulo, textoTituloLineaA);
			strcpy(textEstado, textoEstadoLineaA);
		break;
		case 1:
			strcpy(textTitulo, textoTituloLineaB);
			strcpy(textEstado, textoEstadoLineaB);
		break;
		case 2:
			strcpy(textTitulo, textoTituloLineaC);
			strcpy(textEstado, textoEstadoLineaC);
		break;
		case 3:
			strcpy(textTitulo, textoTituloLineaD);
			strcpy(textEstado, textoEstadoLineaD);
		break;
		case 4:
			strcpy(textTitulo, textoTituloLineaE);
			strcpy(textEstado, textoEstadoLineaE);
		break;
		case 5:
			strcpy(textTitulo, textoTituloLineaH);
			strcpy(textEstado, textoEstadoLineaH);
		break;
		case 6:
			strcpy(textTitulo, textoTituloLineaP);
			strcpy(textEstado, textoEstadoLineaP);
		break;
		case 7:
			strcpy(textTitulo, textoTituloLineaU);
			strcpy(textEstado, textoEstadoLineaU);
		break;
	}	 		

	dialog_message_window_estado_push(textTitulo,textEstado); //vamos a ver...
}

// -- COSOS PARA CARGAR LA PANTALLA PRINCIPAL --
void window_load(Window *window)
{
	//coso para hora 
	Layer *window_layer = window_get_root_layer(window);
	//creo menu (puse 0,14 para dejar espacio para la status bar)
	menu_layer = menu_layer_create(GRect(0, PBL_IF_ROUND_ELSE(0, 14),PBL_IF_ROUND_ELSE(180, 144), PBL_IF_ROUND_ELSE(180-16,168-16)));

	//para clicks...
	menu_layer_set_click_config_onto_window(menu_layer, window);

	//todos los callbacks del menu...
	MenuLayerCallbacks callbacks = 
	{
		.draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
		.get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
		.select_click = (MenuLayerSelectCallback) select_click_callback
	};
	menu_layer_set_callbacks(menu_layer, NULL, callbacks);
	//agrego el menu a la window
	layer_add_child(window_get_root_layer(window), menu_layer_get_layer(menu_layer));
	//para la status bar (lo pongo hasta el final para que quede arriba de las otras  layers)
	s_status_bar = status_bar_layer_create();
	layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar));
}
// ------------------------------------------------------
void window_unload(Window *window)
{
 //por ahora creo que no va nada aca...
}

void init()
{
	window = window_create();
	WindowHandlers handlers = 
	{
		.load = window_load,
		.unload = window_unload
	};
	//-----------------------------------------
	//cosos para comunicarme con el celu
	app_message_register_inbox_received(in_received_handler);
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());  
	//-----------------------------------------  
	window_set_window_handlers(window, (WindowHandlers) handlers);
	window_stack_push(window, true);
}

void deinit()
{
	menu_layer_destroy(menu_layer);
	status_bar_layer_destroy(s_status_bar);
	window_destroy(window);
}

int main(void)
{
	init();
	app_event_loop();
	deinit();
}