#include "card.h"
#include "database.h"
#include "noise.h"

MFRC522 mfrc522(RFID_RC522_SDA_PIN, RFID_RC522_RST_PIN);
CardUID cardUID;

bool operator==(const CardUID& lhs, const CardUID& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
};

bool isMasterCard(CardUID card) {
    return card == MASTER_CARD;
};

bool isResetCard(CardUID card) {
    return card == RESET_CARD;
}

bool isLockCard(CardUID card) {
    return card == LOCK_CARD;
}

bool isThereAnyCardNearReader() {
    return mfrc522.PICC_IsNewCardPresent();
}

bool isCardScaned() {
    return isThereAnyCardNearReader() && readCard();
};
bool readCard() {
    if (mfrc522.PICC_ReadCardSerial()) {
        switch(mfrc522.uid.size ) {
        case 4:
            cardUID.first = (uint32_t) (mfrc522.uid.uidByte[0] << 24) |
                            (uint32_t) (mfrc522.uid.uidByte[1] << 16) |
                            (uint32_t) (mfrc522.uid.uidByte[2] << 8) |
                            (uint32_t) mfrc522.uid.uidByte[3];
            cardUID.second = 0;
            break;
        case 7:
            cardUID.first = (uint32_t) (mfrc522.uid.uidByte[0] << 24) |
                            (uint32_t) (mfrc522.uid.uidByte[1] << 16) |
                            (uint32_t) (mfrc522.uid.uidByte[2] << 8) |
                            (uint32_t) mfrc522.uid.uidByte[3];

            cardUID.second =(uint32_t) (mfrc522.uid.uidByte[4] << 16) |
                            (uint32_t) (mfrc522.uid.uidByte[5] << 8) |
                            (uint32_t) mfrc522.uid.uidByte[6];
            break;

        default:
            return false;
        }
        return true;
    } else {
        return false;
    }
}

Card checkCard(CardUID card) {
    if (isMasterCard(card)) {
        return Card::MASTER;
    }
    if (isResetCard(card)) {
        return Card::RESET;
    }
    if (isLockCard(card)) {
        return Card::LOCK;
    }
    if (findCardInAuthorizedCards(card)) {
        return Card::AUTHORIZED;
    } else {
        makeNoise(State::ERROR);
        return Card::UNKNOWN;
    }
};

void setupRFID() {
    SPI.begin();
    mfrc522.PCD_Init();
}

