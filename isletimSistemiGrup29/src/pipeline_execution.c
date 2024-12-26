#include "pipeline_execution.h"
#include "command_parsing.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// Boru hattı (pipeline) komutlarını çalıştıran fonksiyon
void execute_pipeline(char *pipeline) {
    char *commands[MAX_PIPES]; // Boru hattındaki komutlar tutulur
    int pipe_count = 0;

    char *command = strtok(pipeline, "|"); // Komutları | karakterine göre ayırır
    while (command != NULL && pipe_count < MAX_PIPES) {
        commands[pipe_count++] = command;
        command = strtok(NULL, "|");
    }

    int pipes[MAX_PIPES - 1][2]; // // Borular için giriş/çıkış tanımlayıcılarını
    for (int i = 0; i < pipe_count - 1; i++) {
        if (pipe(pipes[i]) == -1) { // Boru hattı oluşturur
            perror("pipe failed"); 
            return;
        }
    }

    for (int i = 0; i < pipe_count; i++) {
        pid_t pid = fork(); // Yeni işlem oluşturur
        if (pid < 0) {
            perror("fork failed");
            return;
        }

        if (pid == 0) { // Çocuk işlem için
            if (i > 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO); // Önceki borudan giriş alır
            }

            if (i < pipe_count - 1) {
                dup2(pipes[i][1], STDOUT_FILENO); // Sonraki boruya çıkış gönderir
            }

            for (int j = 0; j < pipe_count - 1; j++) {
                close(pipes[j][0]); // Boru hatlarının okuma ucunu kapatır
                close(pipes[j][1]); // Boru hatlarının yazma ucunu kapatır
            }

            char *args[MAX_ARGS]; // Argümanlar tutulur
            int background;
            char *input_file, *output_file;
            parse_command(commands[i], args, &background, &input_file, &output_file); // Komutu ayrıştırır
            execvp(args[0], args); // Komutu çalıştırır
            perror("execvp failed"); 
            exit(1);
        }
    }

    for (int i = 0; i < pipe_count - 1; i++) {
        close(pipes[i][0]); 
        close(pipes[i][1]);
    }

    for (int i = 0; i < pipe_count; i++) {
        wait(NULL); // Tüm çocuk işlemlerin tamamlanmasını bekler
    }
}
