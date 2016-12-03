#pragma once

#define LOCK_DELAY 50
#define BETWEEN_STATE_DELAY 1000
#define LOCK_PIN  30
#define LOCK_SENSOR_PIN 10

#define KEY_HOLDER_PIN 15

#define KEYBOX_STATUS_PIN 3



#define CONTROL_TIMEOUT 5000
#define WAITING_FOR_CLOSE_TIMEOUT 10000

#define BUZZER_PIN 2

#define TABLE_SIZE 4096

#define  RFID_RC522_RST_PIN 5
#define  RFID_RC522_SDA_PIN 53

#define LCD_CELS 16
#define LCD_ROWS 2

enum class State {
  IDLE,
  OPENING,
  WAITING_FOR_OPEN,
  ERROR,
  OPEN,
  WAITING_FOR_CLOSE,
  CLOSED,
  CONTROL,
  REJECT,
  ADD_CARD,
  RESET,
  LOCKED
};
