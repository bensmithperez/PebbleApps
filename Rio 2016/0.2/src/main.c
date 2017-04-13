#include "pebble.h"

static BitmapLayer *logo_image_layer;
static GBitmap *logo_image;

Window *window;
static TextLayer *s_time_layer;
static TextLayer *team_layer;
TextLayer *text_layer_bateria;

static int s_battery_level;

char text_equipo[10];	
char text_bateria[5];

#ifdef PBL_COLOR
GColor time_color;
GColor team_color;
#endif

bool show_battery;

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  // Write the current hours and minutes into a buffer
  static char s_buffer[8];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                          "%H:%M" : "%I:%M", tick_time);

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, s_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

// BATERIAAAA
static void battery_callback(BatteryChargeState state) 
{
	if (show_battery){
	// Record the new battery level
	s_battery_level = state.charge_percent;
	snprintf(text_bateria,sizeof(text_bateria),"%d%%",s_battery_level);
	text_layer_set_text(text_layer_bateria, text_bateria);
	} else {
		strcpy(text_bateria,"");
		text_layer_set_text(text_layer_bateria, text_bateria);
	}
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  //aca iba la imagen
	logo_image_layer = bitmap_layer_create(bounds);
	
  logo_image = gbitmap_create_with_resource(RESOURCE_ID_RINGS);
	
  bitmap_layer_set_compositing_mode(logo_image_layer, GCompOpAssign);
  bitmap_layer_set_bitmap(logo_image_layer, logo_image);
  bitmap_layer_set_alignment(logo_image_layer, GAlignCenter);
	
	layer_add_child(window_layer, bitmap_layer_get_layer(logo_image_layer));
   // Create the TextLayer with specific bounds
  s_time_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(15, 15), bounds.size.w, 50));
	text_layer_bateria = text_layer_create(GRect(PBL_IF_ROUND_ELSE(80,120), 0, 30, 40));
	
		// -- CARACTERISTICAS DE LAS TEXTURAS --
	
	
  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  #ifdef PBL_COLOR
  text_layer_set_text_color(s_time_layer, time_color);
  #endif	

		//cosas de la bateria
		text_layer_set_font(text_layer_bateria, fonts_get_system_font(FONT_KEY_GOTHIC_14));
		text_layer_set_background_color(text_layer_bateria, GColorClear);
		#ifdef PBL_COLOR
		text_layer_set_text_color(text_layer_bateria, time_color);
		#endif

	
team_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(60, 65), bounds.size.w, 50));
  text_layer_set_background_color(team_layer, GColorClear);
  text_layer_set_text_color(team_layer, GColorBlack);
  text_layer_set_text(team_layer, text_equipo);
  text_layer_set_font(team_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text_alignment(team_layer, GTextAlignmentCenter);
#ifdef PBL_COLOR	
  text_layer_set_text_color(team_layer, team_color);
#endif
	
		//bateria
		text_layer_set_text(text_layer_bateria, text_bateria);
		layer_add_child(window_get_root_layer(window), (Layer*) text_layer_bateria);
		// Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  layer_add_child(window_layer, text_layer_get_layer(team_layer));	
	
		battery_callback(battery_state_service_peek());

}

static void window_unload(Window *window) {
  gbitmap_destroy(logo_image);
  bitmap_layer_destroy(logo_image_layer);

  // Destroy TextLayer
  text_layer_destroy(s_time_layer);
	text_layer_destroy(team_layer);
	text_layer_destroy(text_layer_bateria);
}

static void inbox_received_callback(DictionaryIterator *iter, void *context) {
	// Read color preferences
  
	Tuple *equipo_t = dict_find(iter, MESSAGE_KEY_PaisElegido);
  	if(equipo_t) {
		char* cod = equipo_t->value->cstring;
		snprintf(text_equipo, sizeof(text_equipo), "TEAM %s", cod);
		text_layer_set_text(team_layer, text_equipo);		
  	}
	#ifdef PBL_COLOR
	Tuple *time_color_t = dict_find(iter, MESSAGE_KEY_TimeColor);
  	if(time_color_t) {
	    time_color = GColorFromHEX(time_color_t->value->int32);
		text_layer_set_text_color(s_time_layer, time_color);
  	}

	Tuple *team_color_t = dict_find(iter, MESSAGE_KEY_TeamColor);
  	if(team_color_t) {
    	team_color = GColorFromHEX(team_color_t->value->int32);
		text_layer_set_text_color(team_layer, team_color);
  	}  
	#endif
	
	Tuple *show_battery_t = dict_find(iter, MESSAGE_KEY_ShowBattery);
  	if(show_battery_t) {
	    show_battery = show_battery_t->value->int32 == 1;		
	}
	battery_callback(battery_state_service_peek());
			
}

static void init(void) {
	
	if(persist_exists(MESSAGE_KEY_PaisElegido)){
		char buffer[10];
    	persist_read_string(MESSAGE_KEY_PaisElegido, buffer, sizeof(buffer));
		strcpy(text_equipo,buffer);
  	}
	
	#ifdef PBL_COLOR
	if(persist_exists(MESSAGE_KEY_TimeColor)){
    	time_color.argb = persist_read_int(MESSAGE_KEY_TimeColor);
  	} else {
		time_color = GColorBlack;
	}
	
	if(persist_exists(MESSAGE_KEY_TeamColor)){
    	team_color.argb = persist_read_int(MESSAGE_KEY_TeamColor);
  	} else {
		team_color = GColorBlack;
	}
	#endif
	
	if(persist_exists(MESSAGE_KEY_ShowBattery)){
    	show_battery = persist_read_bool(MESSAGE_KEY_ShowBattery);
  	}
	
	// Register to be notified about inbox received events
	app_message_register_inbox_received(inbox_received_callback);
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  
  const bool animated = false;
  window_stack_push(window, animated);

  // Make sure the time is displayed from the start
  update_time();

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
	if (show_battery){
	//batería
	battery_state_service_subscribe(battery_callback);
	}
}

static void deinit(void) {
	
	persist_write_string(MESSAGE_KEY_PaisElegido, text_equipo);
	#ifdef PBL_COLOR
	persist_write_int(MESSAGE_KEY_TimeColor, time_color.argb);
	persist_write_int(MESSAGE_KEY_TeamColor, team_color.argb);
	#endif
	persist_write_bool(MESSAGE_KEY_ShowBattery, show_battery);
	
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}