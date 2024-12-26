#include "prompt.h"
#include <stdio.h>

// Terminale shell promptunu yazdıran fonksiyon
void print_prompt() {
    printf("> ");
    fflush(stdout); // Promptu hemen göster komutu
}
