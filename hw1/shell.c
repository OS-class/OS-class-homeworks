#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

#include "tokenizer.h"

/* Convenience macro to silence compiler warnings about unused function parameters. */
#define unused __attribute__((unused))

/* Whether the shell is connected to an actual terminal or not. */
bool shell_is_interactive;

/* File descriptor for the shell input */
int shell_terminal;

/* Terminal mode settings for the shell */
struct termios shell_tmodes;

/* Process group id for the shell */
pid_t shell_pgid;

int cmd_exit(struct tokens *tokens);
int cmd_help(struct tokens *tokens);
int cmd_cd(struct tokens *tokens);
int cmd_pwd(struct tokens *tokens);

/* Built-in command functions take token array (see parse.h) and return int */
typedef int cmd_fun_t(struct tokens *tokens);

/* Built-in command struct and lookup table */
typedef struct fun_desc {
  cmd_fun_t *fun;
  char *cmd;
  char *doc;
} fun_desc_t;

fun_desc_t cmd_table[] = {
  {cmd_help, "?", "show this help menu"},
  {cmd_exit, "exit", "exit the command shell"},
  {cmd_cd, "cd", "change the directory"},
  {cmd_pwd, "pwd", "print working directory"}
};


/* Prints a helpful description for the given command */
int cmd_help(unused struct tokens *tokens) {
  for (unsigned int i = 0; i < sizeof(cmd_table) / sizeof(fun_desc_t); i++)
    printf("%s - %s\n", cmd_table[i].cmd, cmd_table[i].doc);
  return 1;
}

/* Exits this shell */
int cmd_exit(unused struct tokens *tokens) {
  exit(0);
}

int cmd_cd(unused struct tokens *tokens) {
  // error with dereferencing
  if(tokens_get_length(tokens) >= 2) {
    chdir(tokens_get_token(tokens, 1));
    return 1;
  }
  else return -1;
}

int cmd_pwd(unused struct tokens *tokens) {
  char current[1024];
  getcwd(current, sizeof(current));
  printf("%s\n", current);
  return 1;
}

/* Looks up the built-in command, if it exists. */
int lookup(char cmd[]) {
  for (unsigned int i = 0; i < sizeof(cmd_table) / sizeof(fun_desc_t); i++)
    if (cmd && (strcmp(cmd_table[i].cmd, cmd) == 0))
      return i;
  return -1;
}
/*
void signal_handler(int sign_num) {
  exit(0);
}
*/
/* Intialization procedures for this shell */
void init_shell() {
  /* Our shell is connected to standard input. */
  shell_terminal = STDIN_FILENO;

  /* Check if we are running interactively */
  shell_is_interactive = isatty(shell_terminal);

  if (shell_is_interactive) {
    /* If the shell is not currently in the foreground, we must pause the shell until it becomes a
     * foreground process. We use SIGTTIN to pause the shell. When the shell gets moved to the
     * foreground, we'll receive a SIGCONT. */
    while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
      kill(-shell_pgid, SIGTTIN);

    /* Saves the shell's process id */
    shell_pgid = getpid();

    /* Take control of the terminal */
    tcsetpgrp(shell_terminal, shell_pgid);

    /* Save the current termios to a variable, so it can be restored later. */
    tcgetattr(shell_terminal, &shell_tmodes);
  }
}

int main(unused int argc, unused char *argv[]) {
  
  signal(SIGINT, signal_handler);

  init_shell();

  static char line[4096];
  int line_num = 0;

  /* Please only print shell prompts when standard input is not a tty */
  if (shell_is_interactive)
    fprintf(stdout, "%d: ", line_num);

  while (fgets(line, 4096, stdin)) {
    /* Split our line into words. */
    struct tokens *tokens = tokenize(line);
    int fundex = lookup(tokens_get_token(tokens, 0));
    int tokens_len = tokens_get_length(tokens), status, wait_process = 1;

    if(tokens_get_token(tokens, (size_t)(tokens_get_length(tokens)-1))[0] == '&') {
      wait_process = 0;
      tokens_len -= 1;
    }

    if (fundex >= 0) {
      cmd_table[fundex].fun(tokens);
    } 
    else {
      /* REPLACE this to run commands as programs. */
      if(tokens_len >= 1) {
        pid_t pid = fork();
        if(pid == -1) {
          fprintf(stderr, "can't create child process");
        }
        else if(pid == 0) {
          char *argv[50 + 2];
          for(size_t i = 0; i < (50 <= tokens_len ? 50 : tokens_len); ++i) {
            argv[i] = tokens_get_token(tokens, i);
          }
          argv[(50 <= tokens_len ? 50 : tokens_len)] = NULL;

          if(tokens_len == 3 && argv[1][0] == '>') {
            int out;
            if((out = open(argv[2], O_RDWR|O_CREAT|O_APPEND)) == -1)  
              fprintf(stderr, "cannot access file");
            else 
              dup2(out, 1); // maybe some errors here (duplicate problems)
            argv[1] = NULL;

          }
          if(tokens_len == 3 && argv[1][0] == '<') {
            int in;
            if((in = open(argv[2], O_RDONLY|S_IRUSR)) == -1)
              fprintf(stderr, "cannot access file");
            else
              dup2(in, 0); // also maybe some errors here (duplicate problems)
            argv[1] = NULL;
          }
          
          if(access(argv[0], F_OK) != -1 && access(argv[0], X_OK) != -1) {
            execv(argv[0], argv);
          }
          else {
              char *env = getenv("PATH");
              char *temp;
              while( (temp = strsep(&env, ":")) != NULL ) {
                  char temp_pd[1024];  //why we cant make it pointer 
                  strcpy(temp_pd, temp); 
                  strcat(temp_pd, "/");
                  strcat(temp_pd , argv[0]);
                  if(access(temp_pd, F_OK) != -1 && access(temp_pd, X_OK) != -1) {
                    strcpy(argv[0], temp_pd);
                    execv(temp_pd, argv);
                  }
              }
          }
          _exit(0); // exit child process
        }
        else {
          if(wait_process != 0) {
            wait(&status); // wait child process
          } 
        }
      }
      else 
        fprintf(stdout, "This shell doesn't know how to run programs.\n");
    }

    if (shell_is_interactive)
      /* Please only print shell prompts when standard input is not a tty */
      fprintf(stdout, "%d: ", ++line_num);

    /* Clean up memory */
    tokens_destroy(tokens);
  }

  return 0;
}