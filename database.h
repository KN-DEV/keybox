#pragma once
#include "Arduino.h"
#include "config.h"
#include "card.h"
#include <EDB.h>
#include <EEPROM.h>
extern EDB db;
void writer(unsigned long address, byte data);
byte reader(unsigned long address);
void setupDatabase();
bool truncateDatabase();
bool findCardInAuthorizedCards(CardUID card);
void printError(EDB_Status err);
bool addCardToAuthorizedList(CardUID card);

