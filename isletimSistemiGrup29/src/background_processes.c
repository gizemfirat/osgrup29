#include "background_processes.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

BackgroundProcess *background_processes = NULL; // Arka plan işlemleri listesi

// Yeni bir arka plan işlemini listeye ekler
void add_background_process(pid_t pid) {
    BackgroundProcess *new_process = (BackgroundProcess *)malloc(sizeof(BackgroundProcess));
    new_process->pid = pid; // İşlem kimliği kaydedildi
    new_process->next = background_processes; // Listeye eklendi
    background_processes = new_process; // Liste güncellendi
}

// Bir arka plan işlemini listeden çıkarma fonksiyonu
void remove_background_process(pid_t pid) {
    BackgroundProcess **current = &background_processes;
    while (*current) {
        if ((*current)->pid == pid) {
            BackgroundProcess *to_free = *current; // Kaldırılacak süreç
            *current = (*current)->next; // Liste güncellendi
            free(to_free); // Belleği serbest bırakır
            return;
        }
        current = &((*current)->next); 
    }
}

// Tamamlanan işlemleri kontrol edip temizleyen fonksiyon
void check_background_processes() {
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) { // Çocuk işlemler için beklemeyi engelleyen bir kontrol yapar
        printf("[%d] retval: %d\n", pid, WEXITSTATUS(status)); // Çıkış durumunu yazar
        fflush(stdout); // Çıktının hemen görüntülenmesini sağlar
        remove_background_process(pid); // Tamamlanan işlem listeden kaldırılır
    }
}
