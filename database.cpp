#include "database.h"
#include "config.h"
#include <EEPROM.h>
#include "card.h"
EDB db(&writer, &reader);
void writer(unsigned long address, byte data) {
  EEPROM.write(address, data);
};
byte reader(unsigned long address) {
  return EEPROM.read(address);
};
void setupDatabase() {
  if (db.open(0) != EDB_OK) {
    db.create(0, TABLE_SIZE, (unsigned int) sizeof(CardUID));
  }
}
bool truncateDatabase() {
  db.clear();
  return true;
}
bool findCardInAuthorizedCards(CardUID card) {
  CardUID selectedCardFromDB;
  for (int recno = 1; recno <= db.count(); recno++)
  {
    EDB_Status result = db.readRec(recno, EDB_REC selectedCardFromDB);
    if (result == EDB_OK)    {
      if (card ==  selectedCardFromDB) {
        return true;
      }
    }
    else {
      printError(result);
      return false;
    }
  }
  return false;
};
void printError(EDB_Status error){
  switch (error)  {
    case EDB_OUT_OF_RANGE:
      break;
    case EDB_TABLE_FULL:
      break;
    case EDB_OK:
    default:
      break;
  }
}
bool addCardToAuthorizedList(CardUID card) {
  EDB_Status result = db.appendRec( EDB_REC card);
  if (result != EDB_OK) {
    printError(result);
    return false;
  }
  return true;
};
