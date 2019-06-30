/*
** EPITECH PROJECT, 2017
** struct.h
** File description:
** struct declaration file
*/

#ifndef MAIN_H_
    #define MAIN_H_

    #define UNUSED __attribute__((unused))
    #define OKAY "200 Command okay.\n"
    #define LOG "220 Service ready for new user.\n"
    #define USER "331 User name okay, need password.\n"
    #define PASS "230 User logged in, proceed.\n"
    #define CWD "250 Requested file action okay, completed.\n"
    #define CDUP "200 Command okay.\n"
    #define QUIT "221 Service closing control connection.\n"
    #define DELE "250 Requested file action okay, completed.\n"
    #define HELP "214 Help message.\n"
    #define RETR "150 File status okay; about to open data connection.\n"
    #define STOR "125 125 Data connection already open; transfer starting.\n"
    #define END_DATA "226 Closing data connection.\n"
    #define ERR501 "501 Syntax error in parameters or arguments.\n"
    #define ERR530 "530 Not logged in.\n"
    #define ERR500 "500 Syntax error, command unrecognized.\n"
    #define ERR431 "431 No such directory.\n"
    #define ERR550 "550 Requested action not taken.\n"
    #define ERR421 "421 Service not available, closing control connection.\n"
    #define ERR425 "425 Can't open data connection.\n"

    #include <stdio.h>
    #include <errno.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netdb.h>
    #include <arpa/inet.h>
    #include <dirent.h>
    #include <stdio.h>
    #include <string.h>
    #include <ctype.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    typedef struct client_s {
        char *cmd;
        int fd;
        int port;
        char *username;
        char *password;
        char *path;
        int status;
        struct sockaddr_in clientname;
        int data_port;
        int fd_port;
        int fd_port_client;
        struct sockaddr_in data_sock_addr;
        char *adress_port;
        struct client_s *next;
    } client_t;

    typedef struct server_s {
        int port;
        char *path;
        int status;
        fd_set read_fd_set;
        fd_set active_fd_set;
        struct sockaddr_in addr;
        client_t *head;
    } server_t;

    typedef struct command_s {
        char *cmd;
        int (*cmd_name)(char **arr, client_t *client, server_t* server);
    } command_t;

    int user(char **arr, client_t *client, server_t* server);
    int pass(char **arr, client_t *client, server_t* server);
    int cwd(char **arr, client_t *client, server_t* server);
    int cdup(char **arr, client_t *client, server_t* server);
    int quit(char **arr, client_t *client, server_t* server);
    int dele(UNUSED char **arr, client_t *client, server_t* server);
    int pasv(UNUSED char **arr, client_t *client, server_t* server);
    int port(char **arr, client_t *client, server_t* server);
    int noop(UNUSED char **arr, client_t *client, server_t* server);
    int pwd(char **arr, client_t *client, server_t* server);
    int help(char **arr, client_t *client, server_t* server);
    int retr(char **arr, client_t *client, server_t* server);
    int stor(char **arr, client_t *client, server_t* server);
    int list(char **arr, client_t *client, server_t* server);
    int error_handling_argv(int ac);
    int error_handling_port(char *port);
    int is_operator(char c, char **operators);
    void pass_key(char *str, int *ct, char **operators);
    void pass_key_len(char *str, int *ct, char **operators, int *len);
    char *my_getline(FILE *stream);
    char *my_getline_file(FILE *stream);
    client_t *fill_client(client_t* head, char *path, int fd);
    int pointer_fct(char **arr, client_t *client, server_t* server);
    int client_side(int sock, server_t* server);
    client_t *which_client(int fd, client_t *head, int mode);
    client_t *free_client_quit(client_t *head, fd_set *active_fd_set);
    server_t *init_server(int port, char *path);
    int data_socket(server_t* server, client_t *client);
    int server(server_t* server);
    int is_fd_data_sock(int fd, client_t *client);
    int accept_client(int fd_sock, server_t* server,
    client_t *client, int mode);
    void kill_data_sock(client_t *client, fd_set *active_fd_set);
    char **word_array(char *str, char **operators);
    char *my_strcat(char *dest, char const *src);
    char *int_to_char(int nb);

#endif
