#include "signal_handling.h"
#include "background_processes.h"
#include <signal.h>

//Çocuk işlemi tamamlandı sinyalidir
void sigchld_handler(int signum) {
    check_background_processes(); // Biten  arka plan işlemlerini kontrol eder ve temizler
}