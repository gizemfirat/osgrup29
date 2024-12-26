#include "command_parsing.h"
#include <string.h>
#include <stdio.h>

// Kullanıcıdan alınan komut girişini ayrıştıran fonksiyondur
void parse_command(char *input, char **args, int *background, char **input_file, char **output_file) {
    *background = 0; // Arka plan bayrağı
    *input_file = NULL; // Giriş dosyası
    *output_file = NULL; // Çıkış dosyası
    //null yapılarak işaretçiler sıfırlandı


    int arg_count = 0;
    char *token = strtok(input, " \t\n"); // Komutu boşluk tab veya yeni satıra göre parçalar

    while (token != NULL && arg_count < MAX_ARGS - 1) {
        if (strcmp(token, "&") == 0) { // Eğer & bulunursa bu komutun arka planda çalışacağını gösterir
            *background = 1;
            break;
        } else if (strcmp(token, "<") == 0) { // Giriş yönlendirmesini ayrıştırır
            token = strtok(NULL, " \t\n");
            if (token != NULL) {
                *input_file = token; // Giriş dosyasını belirler
            }
        } else if (strcmp(token, ">") == 0) { // Çıkış yönlendirmesini ayrıştırır
            token = strtok(NULL, " \t\n");
            if (token != NULL) {
                *output_file = token; // Çıkış dosyasını belirler
            }
        } else { // Argümanı argümanlar listesine ekler
            args[arg_count++] = token;
        }
        token = strtok(NULL, " \t\n"); 
    }
    args[arg_count] = NULL; 
}