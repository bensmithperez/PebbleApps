/* -------------------------------------- *
 * Rellotge de Texte  		          	  *
 * v0.5                                   *
 * Benjamin Smith                         *
 * -------------------------------------- */

#include <pebble.h>
#include "gbitmap_color_palette_manipulator.h"
 
static Window* screen;
static Layer *window_layer;
TextLayer *text_layer_hora;
TextLayer *text_layer_union;
TextLayer *text_layer_50;
TextLayer *text_layer_min;
TextLayer *text_layer_minP;
TextLayer *text_layer_bateria;

static int s_battery_level;

char text_hora[7];
char text_union[12];
char text_minutos[10];
char text_bateria[4];

int hora_actual, min_actual;
  
GColor bg_color;
GColor fg_color;
bool txt_centered;

static BitmapLayer *s_bt_icon_layer;
static GBitmap *s_bt_icon_bitmap;

static const uint8_t text_layer_hora_offset_top_percent = 2;
static const uint8_t text_layer_union_offset_top_percent = 32;
static const uint8_t text_layer_50_offset_top_percent = 37;
static const uint8_t text_layer_min_offset_top_percent = 59;
static const uint8_t text_layer_minP_offset_top_percent = 64;

uint8_t relative_pixel(uint8_t percent, uint8_t max) {
  return (max * percent) / 100;
}

void choose_hour(int hora)
{
	if (min_actual == 15)
	{
		strcpy(text_hora,"Un");
	} 
	else if (min_actual == 30)
	{
		strcpy(text_hora,"Dos");
	} 
	else if (min_actual == 45)
	{
		strcpy(text_hora,"Tres");
	} 
	else 
	{
		switch(hora)
		{
			case 1: 
				strcpy(text_hora,"Una");
			break;
			case 2: 
				strcpy(text_hora,"Dues");
			break;
			case 3: 
				strcpy(text_hora,"Tres");
			break;
			case 4: 
				strcpy(text_hora,"Quatre");
			break;
			case 5: 
				strcpy(text_hora,"Cinc");
			break;
			case 6: 
				strcpy(text_hora,"Sis");
			break;
			case 7: 
				strcpy(text_hora,"Set");
			break;
			case 8: 
				strcpy(text_hora,"Vuit");
			break;
			case 9: 
				strcpy(text_hora,"Nou");
			break;
			case 10: 
				strcpy(text_hora,"Deu");
			break;
			case 11: 
				strcpy(text_hora,"Onze");
			break;
			case 12: 
				strcpy(text_hora,"Dotze");
			break;
		}
	}
}

void choose_union(int min)
{
	if (min == 0)
	{
		strcpy(text_union," en");
	} 
	else if (min == 15)
	{
		if (hora_actual == 12 || hora_actual == 10)
		{
			strcpy(text_union,"quart d'");
		} 
		else 
		{
			strcpy(text_union,"quart de");
		}
	} 
	else if (min == 30 || min == 45)
	{
		strcpy(text_union,"quarts de");
	} 
	else if (min > 20 && min < 30)
	{
		strcpy(text_union,"i vint-i");
	} 
	else if (min > 30 && min < 40)
	{
		strcpy(text_union,"i trenta");
	} 
	else if ((min > 40 && min < 45) || (min > 45 && min < 50))
	{
		strcpy(text_union,"i quaranta");
	} 
	else if (min > 50 && min <= 59)
	{
		strcpy(text_union,"i cinquanta");
	} 
	else 
	{
		strcpy(text_union,"i");
	}
}

void choose_minutos(int min)
{
	if (min == 0)
	{
		strcpy(text_minutos,"punt");
	} 
	else if (min == 1)
	{
		strcpy(text_minutos,"un");
	} 
	else if ((min > 1 && min <= 4) || (min >= 21 && min <= 24) || (min >= 31 && min <= 34) || (min >= 41 && min <= 44) || (min >= 51 && min <= 54))
	{
		switch (min%10)
			{
				case 1:
					strcpy(text_minutos,"u");
				break;
				case 2:
					strcpy(text_minutos,"dos");
				break;
				case 3:
					strcpy(text_minutos,"tres");
				break;
				case 4:
					strcpy(text_minutos,"quatre");
				break;
			}
	} 
	else if ((min >= 6 && min <= 9) || (min >= 26 && min <= 29) || (min >= 36 && min <= 39) || (min >= 46 && min <= 49) || (min >= 56 && min <= 59))
	{
		switch (min%10)
		{
			case 6:
				strcpy(text_minutos,"sis");
			break;
			case 7:
				strcpy(text_minutos,"set");
			break;
			case 8:
				strcpy(text_minutos,"vuit");
			break;
			case 9:
				strcpy(text_minutos,"nou");
			break;
		}	
	} 
	else if (min >= 11 && min <= 14)
	{
		switch (min)
		{
			case 11:
				strcpy(text_minutos,"onze");
			break;
			case 12:
				strcpy(text_minutos,"dotze");
			break;
			case 13:
				strcpy(text_minutos,"tretze");
			break;
			case 14:
				strcpy(text_minutos,"catorze");
			break;
		}
	}
	else if (min == 5 || min == 25 || min == 35 || min == 55)
	{
		strcpy(text_minutos, "cinc");
	} 
	else if (min == 15 || min == 30 || min == 45)
	{
		switch (hora_actual)
		{
			case 1:
				strcpy(text_minutos,"dues");
			break;
			case 2:
				strcpy(text_minutos,"tres");
			break;
			case 3:
				strcpy(text_minutos,"quatre");
			break;
			case 4:
				strcpy(text_minutos,"cinc");
			break;
			case 5:
				strcpy(text_minutos,"sis");
			break;
			case 6:
				strcpy(text_minutos,"set");
			break;
			case 7:
				strcpy(text_minutos,"vuit");
			break;
			case 8:
				strcpy(text_minutos,"nou");
			break;
			case 9:
				strcpy(text_minutos,"deu");
			break;
			case 10:
				strcpy(text_minutos,"onze");
			break;
			case 11:
				strcpy(text_minutos,"dotze");
			break;
			case 12:
				strcpy(text_minutos,"una");
			break;
		}
	} 
	else 
	{
		switch(min)
		{
			case 16:
				strcpy(text_minutos,"setze");
			break;
			case 17:
				strcpy(text_minutos,"disset");
			break;
			case 18:
				strcpy(text_minutos,"divuit");
			break;
			case 19:
				strcpy(text_minutos,"dinou");
			break;
			case 20:
				strcpy(text_minutos,"vint");
			break;
			case 40:
				strcpy(text_minutos,"quaranta");
			break;
			case 50:
				strcpy(text_minutos,"cinquanta");
			break;
			case 10:
				strcpy(text_minutos,"deu");
			break;
			case 11:
				strcpy(text_minutos,"onze");
			break;
			case 12:
				strcpy(text_minutos,"dotze");
			break;
			case 13:
				strcpy(text_minutos,"tretze");
			break;
			case 14:
				strcpy(text_minutos,"catorze");
			break;
		}
	}
}

//RELOOOOOJ
char buffer[] = "00:00";

void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{
    //actualizo la hora...
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
	hora_actual = ((int)buffer[0]-48)*10 + ((int)buffer[1]-48);
    min_actual = ((int)buffer[3]-48)*10 + ((int)buffer[4]-48);
	 
	//hora_actual = 10;
	//min_actual = 15;
	
	choose_hour(hora_actual);
	choose_union(min_actual);
	choose_minutos(min_actual);

	// -- LAS AGREGO --
	//hora
	text_layer_set_text(text_layer_hora, text_hora);

	//union (con patch 50) <-- cambia el tamaño de la letra para cuarenti y cincuenti
	if ((min_actual == 30) || (min_actual == 15) || (min_actual == 45)){
		if ((hora_actual > 0 && hora_actual < 10) || (hora_actual > 10 && hora_actual < 13)){
			text_layer_set_text(text_layer_union, "");
			text_layer_set_text(text_layer_50, text_union);
		} else {
			text_layer_set_text(text_layer_50, "");
			text_layer_set_text(text_layer_union, text_union);
		}
	} else if ((min_actual > 40 && min_actual < 45) || (min_actual > 45 && min_actual < 50) || (min_actual > 50 && min_actual < 60))
	{
		text_layer_set_text(text_layer_union, "");
		text_layer_set_text(text_layer_50, text_union); 
	} 
	else 
	{
		text_layer_set_text(text_layer_50, "");
		text_layer_set_text(text_layer_union, text_union);
	}
	
	//patch minutos muy grandes...
	if (min_actual == 40 || min_actual == 50)
	{
		text_layer_set_text(text_layer_min, "");
		text_layer_set_text(text_layer_minP, text_minutos); 
	} 
	else 
	{
		text_layer_set_text(text_layer_minP, "");
		text_layer_set_text(text_layer_min, text_minutos);
	}
}

// BATERIAAAA
static void battery_callback(BatteryChargeState state) 
{
	// Record the new battery level
	s_battery_level = state.charge_percent;
	snprintf(text_bateria,sizeof(text_bateria),"%d",s_battery_level);
	text_layer_set_text(text_layer_bateria, text_bateria);
}

// BLUETOOTHHHHHH
static void bluetooth_callback(bool connected) {
  // Show icon if disconnected
  layer_set_hidden(bitmap_layer_get_layer(s_bt_icon_layer), connected);

  if(!connected) {
    // Issue a vibrating alert
    vibes_double_pulse();
  }
}

static void updateUi(void){
	  // Adapt the layout based on any obstructions
  GRect full_bounds = layer_get_bounds(window_layer);
  GRect unobstructed_bounds = layer_get_unobstructed_bounds(window_layer);

  if (!grect_equal(&full_bounds, &unobstructed_bounds)) {
    // Screen is obstructed
    layer_set_hidden(bitmap_layer_get_layer(s_bt_icon_layer), true);
    layer_set_hidden(text_layer_get_layer(text_layer_bateria),true);
  } else {
    // Screen is unobstructed
    layer_set_hidden(text_layer_get_layer(text_layer_bateria), false);
	layer_set_hidden(bitmap_layer_get_layer(s_bt_icon_layer), connection_service_peek_pebble_app_connection());
  }

  GRect hora_frame = layer_get_frame(text_layer_get_layer(text_layer_hora));
  hora_frame.origin.y = relative_pixel(text_layer_hora_offset_top_percent, unobstructed_bounds.size.h);
  layer_set_frame(text_layer_get_layer(text_layer_hora), hora_frame);

    GRect union_frame = layer_get_frame(text_layer_get_layer(text_layer_union));
  union_frame.origin.y = relative_pixel(text_layer_union_offset_top_percent, unobstructed_bounds.size.h);
  layer_set_frame(text_layer_get_layer(text_layer_union), union_frame);

    GRect s_50_frame = layer_get_frame(text_layer_get_layer(text_layer_50));
  s_50_frame.origin.y = relative_pixel(text_layer_50_offset_top_percent, unobstructed_bounds.size.h);
  layer_set_frame(text_layer_get_layer(text_layer_50), s_50_frame);

    GRect min_frame = layer_get_frame(text_layer_get_layer(text_layer_min));
  min_frame.origin.y = relative_pixel(text_layer_min_offset_top_percent, unobstructed_bounds.size.h);
  layer_set_frame(text_layer_get_layer(text_layer_min), min_frame);

GRect minP_frame = layer_get_frame(text_layer_get_layer(text_layer_minP));
  minP_frame.origin.y = relative_pixel(text_layer_minP_offset_top_percent, unobstructed_bounds.size.h);
  layer_set_frame(text_layer_get_layer(text_layer_minP), minP_frame);
}

static void app_unobstructed_change(AnimationProgress progress, void *context) {
updateUi();
}

void window_load(Window *screen)
{
	window_layer = window_get_root_layer(screen);

	// Subscribe to the change event
  UnobstructedAreaHandlers handlers = {
    .change = app_unobstructed_change
  };
  unobstructed_area_service_subscribe(handlers, NULL);

	// dejo el fondo blanco
	window_set_background_color(screen, bg_color);

	//coso bluetooth
	// Create the Bluetooth icon GBitmap
	s_bt_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_ICON);

	// Create the BitmapLayer to display the GBitmap
	s_bt_icon_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(80,105), 2, 15, 15));
	bitmap_layer_set_bitmap(s_bt_icon_layer, s_bt_icon_bitmap);
	#ifdef PBL_COLOR
	bitmap_layer_set_compositing_mode(s_bt_icon_layer, GCompOpSet);
	gbitmap_fill_all_except(GColorClear , fg_color, false, s_bt_icon_bitmap, s_bt_icon_layer);
	#endif
	layer_add_child(window_get_root_layer(screen), bitmap_layer_get_layer(s_bt_icon_layer));
	
	// -- CREO LAS TEXTURAS DE TEXTO... --
	text_layer_hora = text_layer_create(GRect(0, 10, PBL_IF_ROUND_ELSE(180,144), 60));
	text_layer_union = text_layer_create(GRect(0, 50, PBL_IF_ROUND_ELSE(180,144), 100));
	text_layer_50 = text_layer_create(GRect(0, 60, PBL_IF_ROUND_ELSE(180,144), 110));
	text_layer_min = text_layer_create(GRect(0, 90, PBL_IF_ROUND_ELSE(180,144), 140));
	text_layer_minP = text_layer_create(GRect(0, 100, PBL_IF_ROUND_ELSE(180,144), 140));
	text_layer_bateria = text_layer_create(GRect(PBL_IF_ROUND_ELSE(80, 125), PBL_IF_ROUND_ELSE(160,0), 30, 40));

	#ifdef PBL_PLATFORM_CHALK
		text_layer_set_text_alignment(text_layer_hora, GTextAlignmentCenter);
	text_layer_set_text_alignment(text_layer_union, GTextAlignmentCenter);
	text_layer_set_text_alignment(text_layer_50, GTextAlignmentCenter);
	text_layer_set_text_alignment(text_layer_min, GTextAlignmentCenter);
	text_layer_set_text_alignment(text_layer_minP, GTextAlignmentCenter);
	#endif
	
	// -- CARACTERISTICAS DE LAS TEXTURAS --
	//cosas de la bateria
	text_layer_set_font(text_layer_bateria, fonts_get_system_font(FONT_KEY_GOTHIC_14));
	text_layer_set_background_color(text_layer_bateria, GColorClear);
	text_layer_set_text_color(text_layer_bateria, fg_color);

	//cosas de hora
	text_layer_set_font(text_layer_hora, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
	text_layer_set_background_color(text_layer_hora, GColorClear);
	text_layer_set_text_color(text_layer_hora, fg_color);
	if (txt_centered)
	{
		text_layer_set_text_alignment(text_layer_hora, GTextAlignmentCenter);
	}

	//cosas de union
	text_layer_set_font(text_layer_union, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
	text_layer_set_background_color(text_layer_union, GColorClear);
	text_layer_set_text_color(text_layer_union, fg_color);
	if (txt_centered)
	{
		text_layer_set_text_alignment(text_layer_union, GTextAlignmentCenter);
	}

	//patch para los cincuenti
	text_layer_set_font(text_layer_50, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_background_color(text_layer_50, GColorClear);
	text_layer_set_text_color(text_layer_50, fg_color);
	if (txt_centered)
	{
		text_layer_set_text_alignment(text_layer_50, GTextAlignmentCenter);
	}

	//cosas de min
	text_layer_set_font(text_layer_min, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
	text_layer_set_background_color(text_layer_min, GColorClear);
	text_layer_set_text_color(text_layer_min, fg_color);
	if (txt_centered)
	{
		text_layer_set_text_alignment(text_layer_min, GTextAlignmentCenter);
	}
	
	//patch cosas de min muy largas
	text_layer_set_font(text_layer_minP, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_background_color(text_layer_minP, GColorClear);
	text_layer_set_text_color(text_layer_minP, fg_color);
	if (txt_centered)
	{
		text_layer_set_text_alignment(text_layer_minP, GTextAlignmentCenter);
	}
	//-------------------------------------

	// -- LAS AGREGO --  
	//hora
	text_layer_set_text(text_layer_hora, text_hora);
	layer_add_child(window_get_root_layer(screen), (Layer*) text_layer_hora);

	//union
	text_layer_set_text(text_layer_union, text_union);
	layer_add_child(window_get_root_layer(screen), (Layer*) text_layer_union);

	//PATCH 50
	text_layer_set_text(text_layer_50, text_union);
	layer_add_child(window_get_root_layer(screen), (Layer*) text_layer_50);

	//min
	text_layer_set_text(text_layer_min, text_minutos);
	layer_add_child(window_get_root_layer(screen), (Layer*) text_layer_min);

	//patch cosas de min muy largas
	text_layer_set_text(text_layer_minP, text_minutos);
	layer_add_child(window_get_root_layer(screen), (Layer*) text_layer_minP);
	
	//bateria
	text_layer_set_text(text_layer_bateria, text_bateria);
	layer_add_child(window_get_root_layer(screen), (Layer*) text_layer_bateria);

	 //-------------------------------------
	//Get a time structure so that the face doesn't start blank
	struct tm *t;
	time_t temp;
	temp = time(NULL);
	t = localtime(&temp);



	//Manually call the tick handler when the window is loading
	tick_handler(t, MINUTE_UNIT);
	battery_callback(battery_state_service_peek());
	bluetooth_callback(connection_service_peek_pebble_app_connection());
	//-------------------------------------
	updateUi();
}

void window_unload(Window *screen)
{
	gbitmap_destroy(s_bt_icon_bitmap);
	bitmap_layer_destroy(s_bt_icon_layer);
	text_layer_destroy(text_layer_hora);
	text_layer_destroy(text_layer_union);
	text_layer_destroy(text_layer_50);
	text_layer_destroy(text_layer_min);
	text_layer_destroy(text_layer_minP);
	text_layer_destroy(text_layer_bateria);
	unobstructed_area_service_unsubscribe();
// 	tick_timer_service_unsubscribe();
  
}

static void inbox_received_callback(DictionaryIterator *iter, void *context) {
	// Read color preferences
  
	Tuple *bg_color_t = dict_find(iter, MESSAGE_KEY_BackgroundColor);
  	if(bg_color_t) {
	    bg_color = GColorFromHEX(bg_color_t->value->int32);
		window_set_background_color(screen, bg_color);
  	}

	Tuple *fg_color_t = dict_find(iter, MESSAGE_KEY_ForegroundColor);
  	if(fg_color_t) {
    	fg_color = GColorFromHEX(fg_color_t->value->int32);
		text_layer_set_text_color(text_layer_bateria, fg_color);
		text_layer_set_text_color(text_layer_min, fg_color);
		text_layer_set_text_color(text_layer_minP, fg_color);
		text_layer_set_text_color(text_layer_50, fg_color);
		text_layer_set_text_color(text_layer_union, fg_color);
		text_layer_set_text_color(text_layer_hora, fg_color);
		#ifdef PBL_COLOR
		gbitmap_fill_all_except(GColorClear , fg_color, false, s_bt_icon_bitmap, s_bt_icon_layer);
		#endif
  	}  
	
	Tuple *txt_centered_t = dict_find(iter, MESSAGE_KEY_TextCentered);
  	if(txt_centered_t) {
	    txt_centered = txt_centered_t->value->int32 == 1;
		if (txt_centered){
			text_layer_set_text_alignment(text_layer_hora, GTextAlignmentCenter);
			text_layer_set_text_alignment(text_layer_union, GTextAlignmentCenter);
			text_layer_set_text_alignment(text_layer_50, GTextAlignmentCenter);
			text_layer_set_text_alignment(text_layer_min, GTextAlignmentCenter);
			text_layer_set_text_alignment(text_layer_minP, GTextAlignmentCenter);
		} else {
			text_layer_set_text_alignment(text_layer_hora, GTextAlignmentLeft);
			text_layer_set_text_alignment(text_layer_union, GTextAlignmentLeft);
			text_layer_set_text_alignment(text_layer_50, GTextAlignmentLeft);
			text_layer_set_text_alignment(text_layer_min, GTextAlignmentLeft);
			text_layer_set_text_alignment(text_layer_minP, GTextAlignmentLeft);
		}
  	}
}

void init()
{
	if(persist_exists(MESSAGE_KEY_BackgroundColor)){
    	bg_color.argb = persist_read_int(MESSAGE_KEY_BackgroundColor);
  	} else {
		bg_color = GColorWhite;
	}
	
	if(persist_exists(MESSAGE_KEY_ForegroundColor)){
    	fg_color.argb = persist_read_int(MESSAGE_KEY_ForegroundColor);
  	} else {
		fg_color = GColorBlack;
	}
	
	if(persist_exists(MESSAGE_KEY_TextCentered)){
    	txt_centered = persist_read_bool(MESSAGE_KEY_TextCentered);
  	}
	
	// Register to be notified about inbox received events
	app_message_register_inbox_received(inbox_received_callback);
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
	
	screen = window_create();

	WindowHandlers handlers = 
	{
	    .load = window_load,
	    .unload = window_unload
	};
	
	window_set_window_handlers(screen, (WindowHandlers) handlers);
	//hora
	tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler) tick_handler);
	//batería
	battery_state_service_subscribe(battery_callback);
	//bluetooth
	connection_service_subscribe((ConnectionHandlers)
	{
		.pebble_app_connection_handler = bluetooth_callback
	});
	window_stack_push(screen, true);
}
 
void deinit()
{
	persist_write_int(MESSAGE_KEY_BackgroundColor, bg_color.argb);
	persist_write_int(MESSAGE_KEY_ForegroundColor, fg_color.argb);
	persist_write_bool(MESSAGE_KEY_TextCentered, txt_centered);
	window_destroy(screen);
}
 
int main(void)
{
    init();
    app_event_loop();
    deinit();
}