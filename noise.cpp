#include "noise.h"//// notes in the melody:

int melody[1][8] = {{
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4}
};
//
//// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[1][8] = {{
    4, 8, 1, 4, 4, 4, 4, 4}
};

void makeNoise(int type) {
    for (int thisNote = 0; thisNote < 8; thisNote++) {
        int noteDuration = 1000 / noteDurations[type][thisNote];
        tone(BUZZER_PIN, melody[type][thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(BUZZER_PIN);
    }
}

