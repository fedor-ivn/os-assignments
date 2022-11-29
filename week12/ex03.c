#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

const char *INPUT_DEVICE =
    "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
const char *OUTPUT_FILENAME = "ex03.txt";

const char *PE_SHORTCUT_OUTPUT = "I passed the Exam!";
const char *CAP_SHORTCUT_OUTPUT = "Get some cappuccino!";
const char *FG_SHORTCUT_OUTPUT = "Firas, please do not decrease my grade :((((";

int main() {
    int device_fd = open(INPUT_DEVICE, O_RDONLY);
    FILE *output = fopen(OUTPUT_FILENAME, "w");

    printf("List of Shortcuts:\nP + E     --> %s\nC + A + P --> %s\nF + G     "
           "--> %s\n\n",
           PE_SHORTCUT_OUTPUT, CAP_SHORTCUT_OUTPUT, FG_SHORTCUT_OUTPUT);

    short p = 0, e = 0, c = 0, a = 0, f = 0, g = 0, count = 0;

    while (device_fd != -1) {
        struct input_event event;
        read(device_fd, &event, sizeof(struct input_event));
        switch (event.code) {
        case KEY_P:
            p = event.value;
            break;
        case KEY_E:
            e = event.value;
            break;
        case KEY_C:
            c = event.value;
            break;
        case KEY_A:
            a = event.value;
            break;
        case KEY_F:
            f = event.value;
            break;
        case KEY_G:
            g = event.value;
            break;
        default:
            if (event.value == 2) {
                break;
            }
            count += event.value ? 1 : -1;
            break;
        }

        bool other = count > 0;
        if (p && e && !c && !a && !f && !g && !other) {
            printf("%s\n", PE_SHORTCUT_OUTPUT);
            fprintf(output, "%s\n", PE_SHORTCUT_OUTPUT);
        }

        if (p && !e && c && a && !f && !g && !other) {
            printf("%s\n", CAP_SHORTCUT_OUTPUT);
            fprintf(output, "%s\n", CAP_SHORTCUT_OUTPUT);
        }

        if (!p && !e && !c && !a && f && g && !other) {
            printf("%s\n", FG_SHORTCUT_OUTPUT);
            fprintf(output, "%s\n", FG_SHORTCUT_OUTPUT);
        }

       fflush(output);
    }

    close(device_fd);
    fclose(output);

    return 0;
}
