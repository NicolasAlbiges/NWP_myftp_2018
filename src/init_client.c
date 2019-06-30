/*
** EPITECH PROJECT, 2019
** init_client.c
** File description:
** myftp
*/

#include "main.h"

void free_client(client_t *head, fd_set *active_fd_set)
{
    if (head == NULL)
        return;
    kill_data_sock(head, active_fd_set);
    FD_CLR(head->fd, active_fd_set);
    close(head->fd);
    free(head);
}

client_t *free_client_quit_list(client_t *head, fd_set *active_fd_set)
{
    client_t *tmp = head;
    client_t *new = head;

    while (tmp->next != NULL) {
        if (tmp->next->status == 1 && tmp->next->next == NULL) {
            free_client(tmp->next, active_fd_set);
            tmp->next = NULL;
            return (tmp);
        }
        if (tmp->next->status == 1 && tmp->next->next != NULL) {
            new = tmp->next->next;
            free_client(tmp->next, active_fd_set);
            tmp->next = new;
            return (tmp);
        }
        tmp = tmp->next;
    }
    return (head);
}

client_t *free_client_quit(client_t *head, fd_set *active_fd_set)
{
    client_t *tmp = head;

    if (head == NULL || (head->status == 1 && head->next == NULL)) {
        free_client(head, active_fd_set);
        return (NULL);
    }
    if (head->status == 1 && head->next != NULL) {
            tmp = head->next;
            free_client(head, active_fd_set);
            return (tmp);
    }
    return (free_client_quit_list(head, active_fd_set));
}

client_t *create_client(char *path, int fd)
{
    client_t* new_node = malloc(sizeof(client_t));

    new_node->cmd = NULL;
    new_node->fd = fd;
    new_node->username = "NOPE";
    new_node->password = "NOPE";
    new_node->path = strdup(path);
    new_node->status = -1;
    new_node->port = 0;
    new_node->data_port = 0;
    new_node->fd_port = -1;
    new_node->fd_port_client = -1;
    new_node->adress_port = NULL;
    new_node->next = NULL;
    return (new_node);
}

client_t *fill_client(client_t* head, char *path, int fd)
{
    client_t* tmp = head;

    if (head == NULL) {
        return (create_client(path, fd));
    }
    while (head->next != NULL)
        head = head->next;
    head->next = create_client(path, fd);
    head = tmp;
    return (head);
}