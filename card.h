#ifndef CARD_H
#define CARD_H
#include "Arduino.h"

#include "config.h"
#include <SPI.h>
#include <MFRC522.h>




enum class Card {
    MASTER,
    UNKNOWN,
    AUTHORIZED,
    RESET,
    LOCK
};

struct CardUID {
    uint32_t first;
    uint32_t second;
};


extern MFRC522 mfrc522;
extern CardUID cardUID;

const CardUID  MASTER_CARD = {4294948834, 13952};
const CardUID  LOCK_CARD =  {22754, 13953};
const CardUID  RESET_CARD =  {9186, 13952};

bool operator==(const CardUID& lhs, const CardUID& rhs);

Card checkCard();
bool isMasterCard(CardUID card);

bool isResetCard(CardUID card) ;

bool isLockCard(CardUID card) ;

bool isThereAnyCardNearReader() ;

bool isCardScaned();

bool readCard();

void configureRFID();

#endif
