#ifndef DATABASE_H
#define DATABASE_H

#include "Arduino.h"
#include "config.h"
#include <EDB.h>
#include <EEPROM.h>
#include "card.h"

extern EDB db;

void writer(unsigned long address, byte data);
byte reader(unsigned long address);


void configureDatabase();

bool truncateDatabase();

bool findCardInAuthorizedCards(CardUID card);

void printError(EDB_Status err);

bool addCardToAuthorizedList(CardUID card);

#endif
