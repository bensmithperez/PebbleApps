/* -------------------------------------- *
 * Slider Controls (pebble)               *
 * v0.8                                   *
 *                                        *
 * main.c                                 *
 *                                        *
 * Benjamin Smith                         *
 * -------------------------------------- */

#include <pebble.h>

static Window *s_main_window;

static Layer *window_layer;
static Layer *s_background_layer;
static Layer *s_cHora_layer;
static Layer *s_cMin_layer;
static Layer *s_cBat_layer;

static uint16_t x1 = 24;
static uint16_t x2 = 72;
static uint16_t x3 = 120;
static uint16_t yI = 0;
static uint16_t yF = 168;
static uint16_t yI2 = 12;
static uint16_t yF2 = 156;
static uint16_t yF3 = 156;
static uint16_t radius = 14;

int hora = 0;
int min = 0;
int bateria = 0;

static void background_update_proc(Layer *layer, GContext *ctx) {
  // Custom drawing happens here!
  // Set the line color
  graphics_context_set_stroke_color(ctx, PBL_IF_COLOR_ELSE(GColorRed, GColorWhite));

  // Set the fill color
  graphics_context_set_fill_color(ctx, PBL_IF_COLOR_ELSE(GColorRed, GColorWhite));
    
    // Set the stroke width (must be an odd integer value)
  graphics_context_set_stroke_width(ctx, 3);

  // Disable antialiasing (enabled by default where available)
  graphics_context_set_antialiased(ctx, false);

  GPoint l1Start = GPoint(x1, yI);
  GPoint l1End = GPoint(x1, yF);
  GPoint l2Start = GPoint(x2, yI);
  GPoint l2End = GPoint(x2, yF);
  GPoint l3Start = GPoint(x3, yI);
  GPoint l3End = GPoint(x3, yF);

  // Draw a line
  graphics_draw_line(ctx, l1Start, l1End);
  graphics_draw_line(ctx, l2Start, l2End);
  graphics_draw_line(ctx, l3Start, l3End);
}

static void hora_update_proc(Layer *layer, GContext *ctx) {
  // Set the line color
  graphics_context_set_stroke_color(ctx, GColorLightGray);

  // Set the fill color
  graphics_context_set_fill_color(ctx, GColorDarkGray);
    
  // Load the font
  GFont font = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  // Set the color
  graphics_context_set_text_color(ctx, GColorWhite);

  // Set the stroke width (must be an odd integer value)
  graphics_context_set_stroke_width(ctx, 3);

  // Disable antialiasing (enabled by default where available)
  graphics_context_set_antialiased(ctx, true);
    
  GPoint cir1 = GPoint(x1, (int)(((float)yF2-(((float)yF2/(float)12)*(float)hora)+(float)yI2)));

  // Draw the outline of a circle
  graphics_draw_circle(ctx, cir1, radius);

  // Fill a circle
  graphics_fill_circle(ctx, cir1, radius);

  char *text = "000";
  snprintf(text,sizeof(text),"%d",hora);

  // Determine a reduced bounding box
  GRect bounds = GRect(x1-radius, (int)(((float)yF2-(((float)yF2/(float)12)*(float)hora)+(float)yI2))-radius, radius*2, radius*2);

  // Draw the text
  graphics_draw_text(ctx, text, font, bounds, GTextOverflowModeWordWrap, 
                                            GTextAlignmentCenter, NULL);

}

static void min_update_proc(Layer *layer, GContext *ctx) {
  // Set the line color
  graphics_context_set_stroke_color(ctx, GColorLightGray);

  // Set the fill color
  graphics_context_set_fill_color(ctx, GColorDarkGray);

    // Load the font
  GFont font = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  // Set the color
  graphics_context_set_text_color(ctx, GColorWhite);

    // Set the stroke width (must be an odd integer value)
  graphics_context_set_stroke_width(ctx, 3);

  // Disable antialiasing (enabled by default where available)
  graphics_context_set_antialiased(ctx, true);

  GPoint cir2 = GPoint(16, (int)(((float)yF3-(((float)yF3/(float)60)*(float)min)+(float)yI2)));

  // Draw the outline of a circle
  graphics_draw_circle(ctx, cir2, radius);

  // Fill a circle
  graphics_fill_circle(ctx, cir2, radius);

  char *text = "000";
  snprintf(text,sizeof(text),"%d",min);

  // Determine a reduced bounding box
  GRect bounds = GRect(2, (int)(((float)yF3-(((float)yF3/(float)60)*(float)min)+(float)yI2))-radius, radius*2, radius*2);

  // Draw the text
  graphics_draw_text(ctx, text, font, bounds, GTextOverflowModeWordWrap, 
                                            GTextAlignmentCenter, NULL);
}

static void bat_update_proc(Layer *layer, GContext *ctx) {
  // Set the line color
  graphics_context_set_stroke_color(ctx, GColorLightGray);

  // Set the fill color
  graphics_context_set_fill_color(ctx, GColorDarkGray);

  // Load the font
  GFont font = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  // Set the color
  graphics_context_set_text_color(ctx, GColorWhite);
    
    // Set the stroke width (must be an odd integer value)
  graphics_context_set_stroke_width(ctx, 3);

  // Disable antialiasing (enabled by default where available)
  graphics_context_set_antialiased(ctx, true);

  GPoint cir3 = GPoint(16, (int)(((float)yF2-(((float)yF2/(float)100)*(float)bateria)+(float)yI2)));

  // Draw the outline of a circle
  graphics_draw_circle(ctx, cir3, radius);

  // Fill a circle
  graphics_fill_circle(ctx, cir3, radius);

  char *text = "000";
	if (bateria==100){
		text = ":)";
	} else {
		snprintf(text,sizeof(text),"%d",bateria);		
	}
  
  // Determine a reduced bounding box
  GRect bounds = GRect(1, (int)(((float)yF2-(((float)yF2/(float)100)*(float)bateria)+(float)yI2))-radius, radius*2, radius*2);

  // Draw the text
  graphics_draw_text(ctx, text, font, bounds, GTextOverflowModeWordWrap, 
                                            GTextAlignmentCenter, NULL);
}

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  char buffer[] = "00:00";
  // actualizo la hora...
  strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  hora = ((int)buffer[0]-48)*10 + ((int)buffer[1]-48);
  min = ((int)buffer[3]-48)*10 + ((int)buffer[4]-48);

  layer_mark_dirty(s_cHora_layer);
  layer_mark_dirty(s_cMin_layer);
}


static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void battery_callback(BatteryChargeState state) 
{
  // Record the new battery level
  bateria = state.charge_percent;
  layer_mark_dirty(s_cBat_layer);
}

static void update_ui(){
  // Adapt the layout based on any obstructions
  GRect full_bounds = layer_get_bounds(window_layer);
  GRect unobstructed_bounds = layer_get_unobstructed_bounds(window_layer);

  yF = unobstructed_bounds.size.h;
  yF2 = unobstructed_bounds.size.h-15;
  yF3 = unobstructed_bounds.size.h-28;

  layer_mark_dirty(s_background_layer);
  layer_mark_dirty(s_cHora_layer);
  layer_mark_dirty(s_cMin_layer);
  layer_mark_dirty(s_cBat_layer);

}

static void app_unobstructed_change(AnimationProgress progress, void *context) {
  update_ui();
}

static void main_window_load(Window *window) {
  window_layer = window_get_root_layer(window);

  // Subscribe to the change event
  UnobstructedAreaHandlers handlers = {
    .change = app_unobstructed_change
  };
  unobstructed_area_service_subscribe(handlers, NULL);

  // Get information about the Window
  GRect bounds = layer_get_bounds(window_layer);
  // Create canvas layer
  s_background_layer = layer_create(bounds);
  s_cHora_layer = layer_create(GRect(0,0,x1+radius+2,yF));
  s_cMin_layer = layer_create(GRect(x2-radius-2,0,x1+radius,yF));
  s_cBat_layer = layer_create(GRect(x3-radius-2,0,x1+radius,yF));

  window_set_background_color(window, GColorBlack);
    
    // Assign the custom drawing procedure
  layer_set_update_proc(s_background_layer, background_update_proc);
  layer_set_update_proc(s_cHora_layer, hora_update_proc);
  layer_set_update_proc(s_cMin_layer, min_update_proc);
  layer_set_update_proc(s_cBat_layer, bat_update_proc);

  // Add to Window
  layer_add_child(window_get_root_layer(window), s_background_layer);
  layer_add_child(window_get_root_layer(window), s_cHora_layer);
  layer_add_child(window_get_root_layer(window), s_cMin_layer);
  layer_add_child(window_get_root_layer(window), s_cBat_layer);
	battery_callback(battery_state_service_peek());

  update_ui();
}

static void main_window_unload(Window *window) {
  layer_destroy(s_background_layer);
  layer_destroy(s_cHora_layer);
  layer_destroy(s_cMin_layer);
  layer_destroy(s_cBat_layer);
  unobstructed_area_service_unsubscribe();
}

static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
	
		tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  update_time();
  //batería
  battery_state_service_subscribe(battery_callback);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
