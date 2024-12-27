#include "sequential_execution.h"
#include "pipeline_execution.h"
#include "background_processes.h"
#include "command_parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

// Girilen komutları sırayla çalıştırma fonksiyonu
void execute_sequential_commands(char *input) {
    char *commands[MAX_PIPES]; // Komut dizisi
    int command_count = 0; 

    char *command = strtok(input, ";"); // Komutları ; karakterine göre ayırır
    while (command != NULL && command_count < MAX_PIPES) {
        commands[command_count++] = command;
        command = strtok(NULL, ";");
    }

    for (int i = 0; i < command_count; i++) {
        if (strchr(commands[i], '|')) { // Komut içinde | varsa boru hattı olarak çalıştırır
            execute_pipeline(commands[i]);
        } else {
            char *args[MAX_ARGS]; // Argümanlar
            int background; // Arka plan bayrağı
            char *input_file, *output_file; // Giriş ve çıkış dosyaları

            parse_command(commands[i], args, &background, &input_file, &output_file); // Komutu ayrıştırır

            if (args[0] == NULL) { 
                continue;
            }

            if (strcmp(args[0], "quit") == 0) { // Quit komutu geldiyse işlemleri sonlandır
                while (background_processes != NULL) {
                    check_background_processes(); // Arka plan işlemlerini temizler
                    usleep(100000); 
                }
                exit(0);
            }

            pid_t pid = fork(); // Yeni işlem 
            if (pid < 0) {
                perror("fork failed"); // Hata durumunu yazdırır
                return;
            } else if (pid == 0) { // Çocuk işlem 
                if (input_file != NULL) { 
                    int fd_in = open(input_file, O_RDONLY);
                    if (fd_in < 0) {
                        perror("Input file not found");
                        exit(1);
                    }
                    dup2(fd_in, STDIN_FILENO); // Giriş dosyasını girişe yönlendirir
                    close(fd_in);
                }

                if (output_file != NULL) { 
                    int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd_out < 0) {
                        perror("Output file could not be opened");
                        exit(1);
                    }
                    dup2(fd_out, STDOUT_FILENO); // Çıkış dosyasını çıkışa yönlendirir
                    close(fd_out);
                }

                execvp(args[0], args); 
                perror("execvp failed"); 
                exit(1);
            } else {
                if (background) { // Arka plan işlemi
                    printf("[%d] started\n", pid);
                    fflush(stdout);
                } else {
                    wait(NULL); // Ana işlem çocuk işlemin tamamlanmasını bekler
                }
            }
        }
    }
}
