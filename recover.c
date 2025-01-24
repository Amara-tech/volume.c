#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t byte;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("No memory Card\n");
        return 1;
    }
    FILE *card;
    card = fopen(argv[1], "r");
    byte buffer[512];
    int count = 0;
    while (fread(buffer, sizeof(byte), 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (count == 0)
            {
                char filename[8];
                sprintf(filename, "%03i.jpg", count);
                FILE *img = fopen(filename, "w");
                do
                {
                    fwrite(buffer, sizeof(byte), 512, img);
                }
                while (!(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
                         (buffer[3] & 0xf0) == 0xe0));
                fclose(img);
            }
            else
            {
                char filename[8];
                sprintf(filename, "%03i.jpg", count);
                FILE *img = fopen(filename, "w");
                do
                {
                    fwrite(buffer, sizeof(byte), 512, img);
                }
                while (!(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
                         (buffer[3] & 0xf0) == 0xe0));
                fclose(img);
            }
            count++;
        }
    }
    fclose(card);
}
