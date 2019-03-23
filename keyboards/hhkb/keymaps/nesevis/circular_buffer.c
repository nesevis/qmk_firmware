// Q ? Tab
#include <stdarg.h>
#include "quantum.h"
#include "circular_buffer.h"

#define CIRCULAR_BUFFER_SIZE 2

uint8_t list[CIRCULAR_BUFFER_SIZE] = { KC_TRNS, KC_TRNS };

void circular_buffer_add(uint8_t key_code) {
  for (int i = CIRCULAR_BUFFER_SIZE - 1; i > 0; i--) {
    list[i - 1] = list[i];
  }
  list[CIRCULAR_BUFFER_SIZE - 1] = key_code;
}

bool circular_buffer_matches(int num_args, ...) {
  va_list arguments;
  va_start(arguments, num_args);

  bool match = true;
  for (int x = 0; x < CIRCULAR_BUFFER_SIZE; x++) {
    uint8_t match_kc = va_arg(arguments, int);
    if (match_kc != list[x]) {
      match = false;
      break;
    }
  }
  va_end(arguments);
  return match;
}


