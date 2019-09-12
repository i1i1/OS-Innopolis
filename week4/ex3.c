#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define VECTOR_IMPLEMENTATION
#include "vector.h"


struct cmd {
    char *cmd;
    char **args;

    int bg;
};


int eof = 0;


struct cmd *
cmd_scan()
{
    struct cmd *cmd = malloc(sizeof(*cmd));
    int c;

    if (!cmd || eof)
        return NULL;

    *cmd = (struct cmd) { NULL, NULL, 0 };

    while ((c = getchar()) != EOF && isspace(c))
        /* skip */;

    if (c == EOF) {
        eof = 1;
        free(cmd);
        return NULL;
    }

    do {
        vector_push(&cmd->cmd, (char)c);
    } while ((c = getchar()) != EOF && !isspace(c));

    vector_push(&cmd->cmd, '\0');

    if (c == EOF) {
        eof = 1;
        return cmd;
    }

    if (c == '\n')
        return cmd;

    for (;;) {
        char *arg = NULL;

        while ((c = getchar()) != EOF && isblank(c))
            /* skip */;

        if (c == EOF) {
            eof = 1;
            return cmd;
        }

        if (c == '\n')
            return cmd;

        do {
            vector_push(&arg, (char)c);
        } while ((c = getchar()) != EOF && !isspace(c));

        if (c == EOF) {
            eof = 1;
            return cmd;
        }

        vector_push(&arg, '\0');
        vector_push(&cmd->args, arg);

        if (c == '\n')
            return cmd;
    }
}

struct cmd *
cmd_new()
{
    struct cmd *cmd = cmd_scan();
    int nargs = vector_nmemb(&cmd->args);

    if (cmd == NULL)
        return NULL;

    if (nargs > 0 && strcmp(cmd->args[nargs-1], "&") == 0) {
        cmd->bg = 1;
        vector_free(&(cmd->args[nargs-1]));
        vector_pop(&cmd->args);
    }

    return cmd;
}

void
cmd_free(struct cmd *cmd)
{
    for (int i = 0; i < (int)vector_nmemb(&cmd->args); i++) {
        char *vec = cmd->args[i];
        vector_free(&vec);
    }

    vector_free(&(cmd->args));
    vector_free(&(cmd->cmd));
    free(cmd);
}

void
vector_push_first(char ***vec, char *v)
{
    vector_push(vec, NULL);

    for (int i = (int)vector_nmemb(vec)-1; i > 0; i--)
        (*vec)[i] = (*vec)[i-1];

    (*vec)[0] = v;
}

void
cmd_exec(struct cmd *cmd)
{
    int pid;

    vector_push_first(&cmd->args, cmd->cmd);
    vector_push(&cmd->args, NULL);

    if ((pid = fork()) == 0) {
        execv(cmd->cmd, cmd->args);
        exit(1);
    } else if (pid == -1) {
        exit(1);
    } else {
        int status;

        if (!cmd->bg)
            waitpid(pid, &status, 0);
    }
}

int
main(void)
{
    struct cmd *cmd;

    for (;;) {
        //if (istty())
            printf("%s", getenv("PS1"));

        if ((cmd = cmd_new()) == NULL)
            break;

        cmd_exec(cmd);
        cmd_free(cmd);
        cmd = NULL;
    }

    return eof ? 0 : 1;
}

