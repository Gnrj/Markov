#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_STRING 1002

typedef struct Command Command;

struct Command {
    char fisrt_str[SIZE_OF_STRING];
    char arrow[4];
    char second_str[SIZE_OF_STRING];
};

void replace_string(char* string, char* target, char* replacement) {
    int string_len = strlen(string);
    int target_len = strlen(target);
    int replacement_len = strlen(replacement);

    char* position = strstr(string, target);
    memmove(position + replacement_len, position + target_len, strlen(position + target_len) + 1);
    memcpy(position, replacement, replacement_len);

    string[string_len - target_len + replacement_len] = '\0';
}

int change_string(char* string, Command* all_commands, int all_commands_len, int check) {
    int end_change = 1;

    int cnt = 1;

    while (end_change) {
        for (int i = 0; i < all_commands_len; i++) {
            if (strcmp(all_commands[i].fisrt_str, "_") == 0) {

                if (strlen(string) + strlen(all_commands[i].second_str) >= SIZE_OF_STRING) {
                    printf("Buffer overflow\n");

                    return 1;
                }

                if (check > 0) {
                    printf("%d) %s -> ", cnt, string);
                }

                strcat(string, all_commands[i].second_str);

                if (check > 0) {
                    printf("%s;\n", string);

                    printf("%s -> %s\n\n", all_commands[i].fisrt_str, all_commands[i].second_str);

                    cnt++;

                    if (check == 2) {
                        char nop[10];

                        printf("Enter next to continue: ");
                        scanf("%s", nop);
                    }
                }

                break;
            }

            if (strstr(string, all_commands[i].fisrt_str) != NULL) {

                if (strlen(string) + strlen(all_commands[i].second_str) - strlen(all_commands[i].fisrt_str) >= SIZE_OF_STRING) {
                    printf("Buffer overflow\n");

                    return 1;
                }

                if (check > 0) {
                    printf("%d) %s %s ", cnt, string, all_commands[i].arrow);
                }

                if (strcmp(all_commands[i].second_str, "_") == 0) {
                    char s_help[] = "";
                    replace_string(string, all_commands[i].fisrt_str, s_help);
                } else {
                    replace_string(string, all_commands[i].fisrt_str, all_commands[i].second_str);
                }

                if (strcmp(all_commands[i].arrow, "|->") == 0) {
                    end_change = 0;
                }

                if (check > 0) {
                    printf("%s;\n", string);

                    printf("%s %s %s\n\n", all_commands[i].fisrt_str, all_commands[i].arrow, all_commands[i].second_str);

                    cnt++;

                    if (check == 2) {
                        char nop[10];

                        printf("Enter next to continue: ");
                        scanf("%s", nop);
                    }
                }

                break;
            }
        }

        int all = 1;

        for (int i = 0; i < all_commands_len; i++) {
            if (strstr(string, all_commands[i].fisrt_str) != NULL) {
                all = 0;
                break;
            }

            if (strcmp(all_commands[i].fisrt_str, "_") == 0) {
                all = 0;
                break;
            }
        }

        if (all == 1) {
            end_change = 0;
        }
    }

    while (strstr(string, "_") != NULL) {
        char s1_help[] = "";
        char s2_help[] = "_";
        replace_string(string, s2_help, s1_help);
    }

    printf("Change string: %s\n", string);

    return 0;
}

int main(void) {

    Command* all_commands = (Command*)malloc(sizeof(Command) * 20);

    int all_commands_len = 20;

    int cnt_commands = 0;

    printf("Please, enter all commands you want to use. Use -> or |->. Space = _\n");
    printf("When you end, please enter: That is end.\n");
    printf("Max size of one string is 100 symbols\n");

    int end_stdin = 1;

    while (end_stdin != 0) {
        scanf("%s %s %s", all_commands[cnt_commands].fisrt_str,
              all_commands[cnt_commands].arrow, all_commands[cnt_commands].second_str);

        end_stdin = strcmp(all_commands[cnt_commands].arrow, "is");

        cnt_commands++;

        if (cnt_commands >= all_commands_len) {
            all_commands_len <<= 1;

            all_commands = (Command*)realloc(all_commands, all_commands_len);
        }
    }

    all_commands_len = cnt_commands - 1;

    printf("If you want detailed check, please enter 2.\n");
    printf("If you want fast check, please enter 1.\n");
    printf("If you don't want check, please enter 0.\n");

    int check;
    scanf("%d", &check);

    printf("Please, enter text you want to change. Please, don't use spaces. To stop enter text, enter stop\n");
    printf("Max size 100 symbols\n");
    printf("Enter string: ");

    char string[SIZE_OF_STRING * SIZE_OF_STRING];
    scanf("%s", string);

    while (strcmp(string, "stop") != 0) {
        int errors = change_string(string, all_commands, all_commands_len, check);

        if (errors)
            return 0;

        printf("Enter string or stop to end: ");
        scanf("%s", string);
    }

    return 0;
}