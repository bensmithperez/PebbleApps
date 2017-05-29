/* -------------------------------------- *
 * Day/Night Analog                       *
 * v0.4                                   *
 * Benjamin Smith                         *
 * -------------------------------------- */

#include <pebble.h>

static Window *s_main_window;
static Layer *s_circles_layer_1;
static Layer *s_circles_layer_2;
static Layer *s_circles_layer_3;
static Layer *s_circles_layer_4;
static Layer *s_circles_layer_5;
static Layer *s_circles_layer_6;
static Layer *s_circles_layer_7;
static Layer *s_circles_layer_8;
static Layer *s_circles_layer_9;
static Layer *s_circles_layer_10;
static Layer *s_circles_layer_11;
static Layer *s_circles_layer_12;
static Layer *s_needle_hour_layer;
static Layer *s_needle_min_layer;

static Layer *window_layer;
GColor c_circle_1;
GColor c_circle_2;
GColor c_circle_3;
GColor c_circle_4;
GColor c_circle_5;
GColor c_circle_6;
GColor c_circle_7;
GColor c_circle_8;
GColor c_circle_9;
GColor c_circle_10;
GColor c_circle_11;
GColor c_circle_12;
GColor c_bg;
GColor c_needle_hour;
GColor c_needle_min;

GPoint ph1;
GPoint ph2;
GPoint ph3;
GPoint ph4;
GPoint ph5;
GPoint ph6;
GPoint ph7;
GPoint ph8;
GPoint ph9;
GPoint ph10;
GPoint ph11;
GPoint ph12;

int horaActual;
int minActual;
static int sWidth;
static int sHeight;
GPoint center;

static uint16_t radius = 7;
static uint16_t radius2 = 5;

static GPoint getPoint(int x1,int x2, int length){
  GPoint res;
  int32_t hourLength = sHeight/length+5;

  int32_t hour_angle = TRIG_MAX_ANGLE * x1 / x2;
    
  res.y = (-cos_lookup(hour_angle) * hourLength / TRIG_MAX_RATIO) + center.y;
  res.x = (sin_lookup(hour_angle) * hourLength / TRIG_MAX_RATIO) + center.x;

  return res;
}

static void s_circle_1_update(Layer *layer, GContext *ctx) {
  // Custom drawing happens here!
  // Set the fill color
  graphics_context_set_fill_color(ctx, c_circle_1);
    
    // Set the line color
  graphics_context_set_stroke_color(ctx, c_circle_1);

  // Set the stroke width (must be an odd integer value)
  graphics_context_set_stroke_width(ctx, 3);

  // Disable antialiasing (enabled by default where available)
  graphics_context_set_antialiased(ctx, true);

  //1
  // Draw the outline of a circle
  graphics_draw_circle(ctx, ph1, radius2);
  // Fill a circle
  graphics_fill_circle(ctx, ph1, radius2);
}

static void s_circle_2_update(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, c_circle_2);
  graphics_context_set_stroke_color(ctx, c_circle_2);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_context_set_antialiased(ctx, true);

  graphics_draw_circle(ctx, ph2, radius2);
  graphics_fill_circle(ctx, ph2, radius2);
}

static void s_circle_3_update(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, c_circle_3);
  graphics_context_set_stroke_color(ctx, c_circle_3);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_context_set_antialiased(ctx, true);

  graphics_draw_circle(ctx, ph3, radius);
  graphics_fill_circle(ctx, ph3, radius);
}
static void s_circle_4_update(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, c_circle_4);
  graphics_context_set_stroke_color(ctx, c_circle_4);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_context_set_antialiased(ctx, true);

  graphics_draw_circle(ctx, ph4, radius2);
  graphics_fill_circle(ctx, ph4, radius2);
}
static void s_circle_5_update(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, c_circle_5);
  graphics_context_set_stroke_color(ctx, c_circle_5);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_context_set_antialiased(ctx, true);

  graphics_draw_circle(ctx, ph5, radius2);
  graphics_fill_circle(ctx, ph5, radius2);
}
static void s_circle_6_update(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, c_circle_6);
  graphics_context_set_stroke_color(ctx, c_circle_6);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_context_set_antialiased(ctx, true);

  graphics_draw_circle(ctx, ph6, radius);
  graphics_fill_circle(ctx, ph6, radius);
}
static void s_circle_7_update(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, c_circle_7);
  graphics_context_set_stroke_color(ctx, c_circle_7);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_context_set_antialiased(ctx, true);

  graphics_draw_circle(ctx, ph7, radius2);
  graphics_fill_circle(ctx, ph7, radius2);
}
static void s_circle_8_update(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, c_circle_8);
  graphics_context_set_stroke_color(ctx, c_circle_8);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_context_set_antialiased(ctx, true);

  graphics_draw_circle(ctx, ph8, radius2);
  graphics_fill_circle(ctx, ph8, radius2);
}
static void s_circle_9_update(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, c_circle_9);
  graphics_context_set_stroke_color(ctx, c_circle_9);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_context_set_antialiased(ctx, true);

  graphics_draw_circle(ctx, ph9, radius);
  graphics_fill_circle(ctx, ph9, radius);
}
static void s_circle_10_update(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, c_circle_10);
  graphics_context_set_stroke_color(ctx, c_circle_10);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_context_set_antialiased(ctx, true);

  graphics_draw_circle(ctx, ph10, radius2);
  graphics_fill_circle(ctx, ph10, radius2);
}
static void s_circle_11_update(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, c_circle_11);
  graphics_context_set_stroke_color(ctx, c_circle_11);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_context_set_antialiased(ctx, true);

  graphics_draw_circle(ctx, ph11, radius2);
  graphics_fill_circle(ctx, ph11, radius2);
}
static void s_circle_12_update(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, c_circle_12);
  graphics_context_set_stroke_color(ctx, c_circle_12);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_context_set_antialiased(ctx, true);

  graphics_draw_circle(ctx, ph12, radius);
  graphics_fill_circle(ctx, ph12, radius);
}

static void needle_hour_update_proc(Layer *layer, GContext *ctx) {
  // Set the line color
  graphics_context_set_stroke_color(ctx, c_needle_hour);
  // Set the fill color
  graphics_context_set_fill_color(ctx, c_needle_hour);

  // Set the stroke width (must be an odd integer value)
  graphics_context_set_stroke_width(ctx, 3);
  // Disable antialiasing (enabled by default where available)
  graphics_context_set_antialiased(ctx, false);

  int puntoNuevo = (360 * (((horaActual % 12) * 6) + (minActual / 10))) / (12 * 6);

  GPoint p_hour = getPoint(puntoNuevo,360,6);

  // Draw a line
  graphics_draw_line(ctx, center, p_hour);
}

static void needle_min_update_proc(Layer *layer, GContext *ctx) {
  // Set the line color
  graphics_context_set_stroke_color(ctx, c_needle_min);
  // Set the fill color
  graphics_context_set_fill_color(ctx, c_needle_min);

  // Set the stroke width (must be an odd integer value)
  graphics_context_set_stroke_width(ctx, 3);
  // Disable antialiasing (enabled by default where available)
  graphics_context_set_antialiased(ctx, false);

  GPoint p_min = getPoint(minActual,60,4);

  // Draw a line
  graphics_draw_line(ctx, center, p_min);
}

static void choose_color(bool day){
  if (day){
    //7am-6pm
    c_circle_1 = GColorRajah;
    c_circle_2 = GColorOrange;
    c_circle_3 = GColorSunsetOrange;
    c_circle_4 = GColorRed;
    c_circle_5 = GColorDarkCandyAppleRed;
    c_circle_6 = GColorJazzberryJam;
    c_circle_7 = GColorBlueMoon;
    c_circle_8 = GColorVividCerulean;
    c_circle_9 = GColorCyan;
    c_circle_10 = GColorElectricBlue;
    c_circle_11 = GColorYellow;
    c_circle_12 = GColorChromeYellow;
    c_bg = GColorWhite;
    c_needle_min = GColorLightGray;
    c_needle_hour = GColorLightGray;
  } else {
    //7pm-6am
    c_circle_1 = GColorDarkGray;
    c_circle_2 = GColorLiberty;
    c_circle_3 = GColorVeryLightBlue;
    c_circle_4 = GColorLightGray;
    c_circle_5 = GColorCobaltBlue;
    c_circle_6 = GColorPictonBlue;
    c_circle_7 = GColorIndigo;
    c_circle_8 = GColorImperialPurple;
    c_circle_9 = GColorBulgarianRose;
    c_circle_10 = GColorDukeBlue;
    c_circle_11 = GColorOxfordBlue;
    c_circle_12 = GColorMidnightGreen;
    c_bg = GColorBlack;
    c_needle_min = GColorLightGray;
    c_needle_hour = GColorLightGray;
  }
}

static void update_ui(){
    // Adapt the layout based on any obstructions
  GRect full_bounds = layer_get_bounds(window_layer);
  GRect unobstructed_bounds = layer_get_unobstructed_bounds(window_layer);

  sWidth = unobstructed_bounds.size.w;
  sHeight = unobstructed_bounds.size.h;
  center = GPoint(sWidth/2,sHeight/2);

  ph1 = getPoint(1,12,3);
  ph2 = getPoint(2,12,3);
  ph3 = getPoint(3,12,3);
  ph4 = getPoint(4,12,3);
  ph5 = getPoint(5,12,3);
  ph6 = getPoint(6,12,3);
  ph7 = getPoint(7,12,3);
  ph8 = getPoint(8,12,3);
  ph9 = getPoint(9,12,3);
  ph10 = getPoint(10,12,3);
  ph11 = getPoint(11,12,3);
  ph12 = getPoint(12,12,3);

  window_set_background_color(s_main_window, c_bg);
  layer_mark_dirty(s_needle_min_layer);
  layer_mark_dirty(s_needle_hour_layer);
  layer_mark_dirty(s_circles_layer_1);
  layer_mark_dirty(s_circles_layer_2);
  layer_mark_dirty(s_circles_layer_3);
  layer_mark_dirty(s_circles_layer_4);
  layer_mark_dirty(s_circles_layer_5);
  layer_mark_dirty(s_circles_layer_6);
  layer_mark_dirty(s_circles_layer_7);
  layer_mark_dirty(s_circles_layer_8);
  layer_mark_dirty(s_circles_layer_9);
  layer_mark_dirty(s_circles_layer_10);
  layer_mark_dirty(s_circles_layer_11);
  layer_mark_dirty(s_circles_layer_12);
}

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  char buffer[] = "00:00";
  //actualizo la hora...
  strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  horaActual = ((int)buffer[0]-48)*10 + ((int)buffer[1]-48);
  minActual = ((int)buffer[3]-48)*10 + ((int)buffer[4]-48);

  if (horaActual>=7&&horaActual<=18){
    choose_color(true);
  } else {
    choose_color(false);
  }
  // Display this time on the TextLayer
  //text_layer_set_text(s_time_layer, s_buffer);
  if (horaActual==0){
    horaActual=12;
  } else if (horaActual>12){
    horaActual-=12;
  } 

  if (horaActual==6){
    update_ui();
  } else {
    layer_mark_dirty(s_needle_min_layer);
    layer_mark_dirty(s_needle_hour_layer);
  }
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
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

  GRect bounds = layer_get_bounds(window_layer);
  window_set_background_color(window, c_bg);
  // Create canvas layer
  s_circles_layer_1 = layer_create(bounds);
  s_circles_layer_2 = layer_create(bounds);
  s_circles_layer_3 = layer_create(bounds);
  s_circles_layer_4 = layer_create(bounds);
  s_circles_layer_5 = layer_create(bounds);
  s_circles_layer_6 = layer_create(bounds);
  s_circles_layer_7 = layer_create(bounds);
  s_circles_layer_8 = layer_create(bounds);
  s_circles_layer_9 = layer_create(bounds);
  s_circles_layer_10 = layer_create(bounds);
  s_circles_layer_11 = layer_create(bounds);
  s_circles_layer_12 = layer_create(bounds);
  s_needle_min_layer = layer_create(bounds);
  s_needle_hour_layer = layer_create(bounds);

    // Assign the custom drawing procedure
  layer_set_update_proc(s_circles_layer_1, s_circle_1_update);
  layer_set_update_proc(s_circles_layer_2, s_circle_2_update);
  layer_set_update_proc(s_circles_layer_3, s_circle_3_update);
  layer_set_update_proc(s_circles_layer_4, s_circle_4_update);
  layer_set_update_proc(s_circles_layer_5, s_circle_5_update);
  layer_set_update_proc(s_circles_layer_6, s_circle_6_update);
  layer_set_update_proc(s_circles_layer_7, s_circle_7_update);
  layer_set_update_proc(s_circles_layer_8, s_circle_8_update);
  layer_set_update_proc(s_circles_layer_9, s_circle_9_update);
  layer_set_update_proc(s_circles_layer_10, s_circle_10_update);
  layer_set_update_proc(s_circles_layer_11, s_circle_11_update);
  layer_set_update_proc(s_circles_layer_12, s_circle_12_update);
  layer_set_update_proc(s_needle_min_layer, needle_min_update_proc);
  layer_set_update_proc(s_needle_hour_layer, needle_hour_update_proc);
  // Add to Window
  layer_add_child(window_get_root_layer(window), s_circles_layer_1);
  layer_add_child(window_get_root_layer(window), s_circles_layer_2);
  layer_add_child(window_get_root_layer(window), s_circles_layer_3);
  layer_add_child(window_get_root_layer(window), s_circles_layer_4);
  layer_add_child(window_get_root_layer(window), s_circles_layer_5);
  layer_add_child(window_get_root_layer(window), s_circles_layer_6);
  layer_add_child(window_get_root_layer(window), s_circles_layer_7);
  layer_add_child(window_get_root_layer(window), s_circles_layer_8);
  layer_add_child(window_get_root_layer(window), s_circles_layer_9);
  layer_add_child(window_get_root_layer(window), s_circles_layer_10);
  layer_add_child(window_get_root_layer(window), s_circles_layer_11);
  layer_add_child(window_get_root_layer(window), s_circles_layer_12);
  layer_add_child(window_get_root_layer(window), s_needle_min_layer);
  layer_add_child(window_get_root_layer(window), s_needle_hour_layer);
}

static void main_window_unload(Window *window) {
  // Destroy TextLayer
  layer_destroy(s_circles_layer_1);
  layer_destroy(s_circles_layer_2);
  layer_destroy(s_circles_layer_3);
  layer_destroy(s_circles_layer_4);
  layer_destroy(s_circles_layer_5);
  layer_destroy(s_circles_layer_6);
  layer_destroy(s_circles_layer_7);
  layer_destroy(s_circles_layer_8);
  layer_destroy(s_circles_layer_9);
  layer_destroy(s_circles_layer_10);
  layer_destroy(s_circles_layer_11);
  layer_destroy(s_circles_layer_12);
  layer_destroy(s_needle_min_layer);
  layer_destroy(s_needle_hour_layer);

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
  update_ui();
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