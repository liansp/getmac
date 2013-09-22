#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
/*
 * make a true rand
 */
static unsigned int new_rand ()
{
        int fd;
        unsigned int n = 0;

        fd = open ("/dev/urandom", O_RDONLY);
        if (fd > 0){
                read (fd, &n, sizeof (n));
        }
        close (fd);

        return n;
}
/*
 * change rand number to char
 */
static unsigned char randomchar(void)
{
        unsigned int rand;
        unsigned char a;

        a =(unsigned char)new_rand();
        if (a < 'A')
                a = a % 10 + 48;
        else if (a < 'F')
                a = a % 6 + 65;
        else if (a < 'a' || a > 'f')
                a = a % 6 + 97;

        return a;
}
/*
 * product one mac addr
 */
static void product_one_mac(void)
{
        char mac[18]={'0','0',};
        int i;
        /*set mac addr */
        for (i=3; i<17; i++){
                usleep(10);
                mac[i] = randomchar();
        }
        mac[2] = mac[5] = mac[8] = mac[11] = mac[14] = ':';
        mac[17] = '\0';

        printf("%s\n", mac);
}
/*
 * main function
 * usge: 
 *   ./tools num
 *           num product max mac item
 */
int main(int argc, char *argv[])
{
        int i;

        if(argc == 1){
                product_one_mac();
                return 0;
        }
        for(i = 0; i < atoi(argv[1]); i++)
                product_one_mac();

        return 0;
}
