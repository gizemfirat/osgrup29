#include "sequential_execution.h"
#include "prompt.h"
#include "signal_handling.h"
#include "background_processes.h"
#include "command_parsing.h"
#include "pipeline_execution.h"
#include <stdio.h>
#include <signal.h>

#define MAX_INPUT 1024 


int main() {
    char input[MAX_INPUT]; // Kullanıcı girdisi için bir dizi 

    struct sigaction sa; // SIGCHLD sinyali için bir işleyici
    sa.sa_handler = sigchld_handler; 
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP; 
    sigaction(SIGCHLD, &sa, NULL); 

    while (1) {
        print_prompt(); 
        if (fgets(input, MAX_INPUT, stdin) == NULL) { 
            break; // Girdi alınmadığında döngü sonlanır
        }
        execute_sequential_commands(input); // Komutlar çalıştırılır
    }

    return 0; 
}