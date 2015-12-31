#pragma once
#include <pebble.h>
#include "Weather.h"

static void init();
static void deinit();
static void main_window_load(Window *window);
static void main_window_unload(Window *window);
static void tick_handler(struct tm *tick_time, TimeUnits units_changed);
static void update_time();


static Window *s_main_window;

static TextLayer *s_time_layer;
static GFont s_time_font;

static TextLayer *s_weather_layer;
static GFont s_weather_font;

static TextLayer *s_weather_icon_layer;
static GFont s_weather_icon_font;
