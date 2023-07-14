#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define HDR_SZ 20

int is_little_endian() {
   /* TODO: return 1 if machine is little endian, 0 if not */ 
   int num = 1;
   int *pnum = &num;
   char *p = (char *)pnum;
   
   return (int) *p;
}

unsigned int get_length(char *hdr) {
   /* TODO: extract Total length field*/
   unsigned *pnum = (unsigned *)hdr;
   unsigned num = *pnum;
   num = num >> 24;

   return num;
}

unsigned int get_ip(char *hdr, int option) {
    /* TODO: extract Source IP if option is 0 and 
             Destination IP if option is 1 */
    unsigned *pnum = (unsigned *)hdr;

    if (!option) {
        pnum += 3;
    } else {
        pnum += 4;
    }

    unsigned num = *pnum;
    num = num << 24 | num >> 24 | ((num >> 16) << 24 ) >> 16 | ((num << 16) >> 24) << 16; 
    
    return num;
}

char *format_ip(unsigned int ip_int) {
    /* TODO: return IP in the form A.B.C.D (dotted decimal notation) */
    unsigned a = ip_int >> 24;
    unsigned b = (ip_int << 8) >> 24;
    unsigned c = (ip_int << 16) >> 24;
    unsigned d = (ip_int << 24) >> 24;

    char* a_str = malloc(sizeof(char) * 3);
    char* b_str = malloc(sizeof(char) * 3);
    char* c_str = malloc(sizeof(char) * 3);
    char* d_str = malloc(sizeof(char) * 3);

    sprintf(a_str, "%d", a);
    sprintf(b_str, "%d", b);
    sprintf(c_str, "%d", c);
    sprintf(d_str, "%d", d);

    char *ip_str = malloc(sizeof(char) * 16);
    snprintf(ip_str, sizeof(char) * 16, "%s.%s.%s.%s", a_str, b_str, c_str, d_str);

    free(a_str);
    free(b_str);
    free(c_str);
    free(d_str);

    return ip_str;
}

int is_checksum_valid(char *hdr) {
    /* TODO: if checksum valid, return 1; else return 0; */
    
}

int get_protocol(char *hdr) {
    /* TODO: return the 8 bit protocol number as an integer */
    int *p = (int *)hdr;
    p += 2;
    int num = *p;
    num = (num << 16) >> 24;

    return num;
} 

int get_version(char *hdr) {
    /* TODO: returns the 4 bit version number as an integer */
    int *p = (int *)hdr;
    int num = *p;
    num = (num << 24) >> 28;

    return num;
} 

char get_flags(char *hdr, int pos) {
    /* TODO: returns the 1 bit (corresponding to the pos)
             from the flags field */

    hdr += 6;
    char c = *hdr;
    c = (c << pos) >> 7;

    return c;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    char *hdr;
    unsigned int n;
 
    /* TODO: Read the contents of the file into hdr */
    hdr = malloc(sizeof(char) * 21);
    FILE *fp = fopen(argv[1], "rb");
    n = fread(hdr, 1, 20, fp);

    /* TODO: Store the number of bytes read into n */

    /* DO NOT MODIFY BELOW THIS LINE */

   printf("read %u bytes\n", n);
   if (is_little_endian()) { 
	printf("Machine is little endian\n");
   } else {
   	printf("Machine is big endian\n");
	exit(1);
   }
   unsigned int len = get_length(hdr);
   printf("total length: %u bytes (0x%x)\n", len, len);

   if (is_checksum_valid(hdr)) {
       printf("checksum is valid\n");
   } else {
       printf("checksum is not valid\n");
   }

   printf("protocol: 0x%x\n", get_protocol(hdr));

   printf("version: %u\n", get_version(hdr));

   printf("flag: 0x%x%x%x\n", get_flags(hdr, 0),
         get_flags(hdr, 1), get_flags(hdr, 2));

   // get source ip
   unsigned int sip = get_ip(hdr, 0);
   printf("source ip: %u (0x%x)\n", sip, sip);   
   char *sip_formatted = format_ip(sip);
   printf("formatted: %s\n",sip_formatted);
   free(sip_formatted);

   // get dest ip
   unsigned int dip = get_ip(hdr, 1);
   printf("destination ip: %u (0x%x)\n", dip, dip); 
   char *dip_formatted = format_ip(dip);
   printf("formatted: %s\n",dip_formatted);
   free(dip_formatted);    

   free(hdr);
   return 0;

}
