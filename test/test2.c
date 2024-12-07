/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herizrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:08:45 by herizrak          #+#    #+#             */
/*   Updated: 2024/11/23 14:09:05 by herizrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100
#define LINE_SIZE 100
#define MAX_LINE 29

typedef struct {
    long number;
    char *value;
} Ligne;

int ft_strlen(char *str) {
    int len = 0;
    while (str[len])
        len++;
    return len;
}

void ft_str_copy(char *dest, char *src) {
    while (*src)
        *dest++ = *src++;
    *dest = '\0';
}

void clean_str(char *str, int *cle, char *value) {
    int i = 0;
    while (*str && *str == ' ')
        str++;
    *cle = atoi(str);
    while (*str && *str != ' ')
        str++;
    while (*str && *str == ' ')
        str++;
    while (*str) {
        value[i++] = *str++;
    }
    value[i] = '\0';
}

int read_numbers_into_dict(Ligne *dict_centaine) {
    int fd, size, index = 0;
    char texte[BUFFER_SIZE], ligne[LINE_SIZE];

    fd = open("numbers.dict", O_RDONLY);
    if (fd < 0) {
        write(2, "Error opening file\n", 19);
        return -1;
    }

    memset(texte, 0, sizeof(texte));
    while ((size = read(fd, texte, BUFFER_SIZE - 1)) > 0) {
        texte[size] = '\0'; 
        char *line = strtok(texte, "\n");
        while (line && index < MAX_LINE) {
            int cle;
            clean_str(line, &cle, ligne);
            dict_centaine[index].number = cle;
            dict_centaine[index].value = malloc(ft_strlen(ligne) + 1);
            if (!dict_centaine[index].value) {
                write(2, "Memory allocation error\n", 24);
                close(fd);
                return -1;
            }
            ft_str_copy(dict_centaine[index].value, ligne);
            index++;
            line = strtok(NULL, "\n");
        }
        memset(texte, 0, sizeof(texte));
    }

    close(fd);
    return index;
}
#include <stdio.h>
int main() {
    Ligne dict_centaine[MAX_LINE];
    int count = read_numbers_into_dict(dict_centaine);

    if (count < 0) {
        write(2, "Error reading file\n", 19);
        return 1;
    }
    printf("%s",dict_centaine[15].value);
    for (int i = 0; i < count; i++) {
        free(dict_centaine[i].value);
    }
    return 0;
}
