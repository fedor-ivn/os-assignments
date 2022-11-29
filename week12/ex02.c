#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

const char *INPUT_DEVICE =
    "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
const char *OUTPUT_FILENAME = "ex02.txt";

int main() {
    int device_fd = open(INPUT_DEVICE, O_RDONLY);
    FILE *output = fopen(OUTPUT_FILENAME, "w");

    while (device_fd != -1) {
        struct input_event event;
        read(device_fd, &event, sizeof(struct input_event));
        if (event.code != KEY_RESERVED) {
            switch (event.value) {
            case 0:
                printf("RELEASED 0x00%x (%d)\n", event.code, event.code);
                fprintf(output, "RELEASED 0x00%x (%d)\n", event.code,
                        event.code);
                break;
            case 1:
                printf("PRESSED 0x00%x (%d)\n", event.code, event.code);
                fprintf(output, "PRESSED 0x00%x (%d)\n", event.code,
                        event.code);
                break;
            }
        }
        fflush(output);
    }

    close(device_fd);
    fclose(output);

    return 0;
}
