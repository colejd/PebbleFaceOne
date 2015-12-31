#include "Weather.h"


static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  // Store incoming information
  static char temperature_buffer[8];
  static char conditions_buffer[32];
  static char weather_layer_buffer[32];
  
  // Read tuples for data
  Tuple *temp_tuple = dict_find(iterator, KEY_TEMPERATURE);
  Tuple *conditions_tuple = dict_find(iterator, KEY_CONDITIONS);
  
  // If all data is available, use it
  if(temp_tuple && conditions_tuple) {
    snprintf(temperature_buffer, sizeof(temperature_buffer), "%dF", (int)temp_tuple->value->int32);
    snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", conditions_tuple->value->cstring);
  }
  
  // Assemble full string and display
  snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s, %s", temperature_buffer, conditions_buffer);
  text_layer_set_text(text_layer_ref, weather_layer_buffer);
  
  char* icon = "\uf07b";
  if(strcmp(conditions_buffer, "Snow") == 0) icon = "\uf01b";
  else if(strcmp(conditions_buffer, "Mist") == 0) icon = "\uf014";
  else if(strcmp(conditions_buffer, "Rain") == 0) icon = "\uf019";
  else if(strcmp(conditions_buffer, "Shower Rain") == 0) icon = "\uf019";
  else if(strcmp(conditions_buffer, "Few Clouds") == 0) icon = "\uf041";
  else if(strcmp(conditions_buffer, "Scattered Clouds") == 0) icon = "\uf013";
  else if(strcmp(conditions_buffer, "Broken Clouds") == 0) icon = "\uf013";
  else if(strcmp(conditions_buffer, "Thunderstorm") == 0) icon = "\uf01e";
  else if(strcmp(conditions_buffer, "Clear Sky") == 0) icon = "\uf00d";
  text_layer_set_text(icon_layer_ref, icon);
  
  
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

void init_weather(TextLayer *text_layer, TextLayer *icon_layer){
  text_layer_ref = text_layer;
  icon_layer_ref = icon_layer;
  register_callbacks();
  // Open AppMessage
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void register_callbacks(){
  // Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
}