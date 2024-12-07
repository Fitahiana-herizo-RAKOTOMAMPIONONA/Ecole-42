/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herizrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 06:15:19 by herizrak          #+#    #+#             */
/*   Updated: 2024/11/23 08:33:40 by herizrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

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
    int i = 0;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
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
        value[i] = *str;
        i++;
        str++;
    }
    value[i] = '\0';
}

void print_numbers(int nbr) {
    int fd;
    int size;
    int index = 0;
    int i;
    char texte[BUFFER_SIZE];
    char ligne[LINE_SIZE];
    Ligne *dict_centaine = malloc(MAX_LINE * sizeof(Ligne));

    if (!dict_centaine) {
        write(2, "Memory allocation error\n", 24);
        return;
    }
    fd = open("numbers.dict", O_RDONLY);
    if (fd < 0) {
        write(2, "Error opening file\n", 19);
        free(dict_centaine);
        return;
    }

    while ((size = read(fd, texte, BUFFER_SIZE - 1)) > 0) {
        texte[size] = '\0';
        i = 0;

        while (texte[i] && index < MAX_LINE) {
            int cle;

            if (texte[i] == '\n' || texte[i] == '\0') {
                clean_str(texte, &cle, ligne);
                dict_centaine[index].number = cle;
                dict_centaine[index].value = malloc(ft_strlen(ligne) + 1);
                if (!dict_centaine[index].value) {
                    write(2, "Memory allocation error\n", 24);
                    close(fd);
                    free(dict_centaine);
                    return;
                }
                ft_str_copy(dict_centaine[index].value, ligne);
                index++;
            }
            i++;
        }
    }

    close(fd);
    for (int j = 0; j < index; j++) {
        printf("%ld: %s\n", dict_centaine[j].number, dict_centaine[j].value);
        free(dict_centaine[j].value);
    }
    free(dict_centaine);
}

int main(int argc, char *argv[]) {
    int i = 0;

    if (argc == 2)
        i = atoi(argv[1]);
    else {
        write(2, "Usage: ./main <number>\n", 23);
        return 1;
    }

    print_numbers(i);
    return 0;
}
