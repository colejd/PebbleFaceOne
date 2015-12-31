#pragma once
#include <pebble.h>

void init_weather(TextLayer *text_layer, TextLayer *icon_layer);
static void register_callbacks();

static void inbox_received_callback(DictionaryIterator *iterator, void *context);
static void inbox_dropped_callback(AppMessageResult reason, void *context);
static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context);
static void outbox_sent_callback(DictionaryIterator *iterator, void *context);

enum {
  KEY_TEMPERATURE = 0,
  KEY_CONDITIONS = 1
};

TextLayer *text_layer_ref;
TextLayer *icon_layer_ref;