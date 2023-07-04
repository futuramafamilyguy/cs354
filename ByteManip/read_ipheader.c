#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define HDR_SZ 20

int is_little_endian() {
   /* TODO: return 1 if machine is little endian, 0 if not */ 
}

unsigned int get_length(char *hdr) {
   /* TODO: extract Total length field*/
}

unsigned int get_ip(char *hdr, int option) {
    /* TODO: extract Source IP if option is 0 and 
             Destination IP if option is 1 */
}

char *format_ip(unsigned int ip_int) {
    /* TODO: return IP in the form A.B.C.D (dotted decimal notation) */
}

int is_checksum_valid(char *hdr) {
    /* TODO: if checksum valid, return 1; else return 0; */
}

int get_protocol(char *hdr) {
    /* TODO: return the 8 bit protocol number as an integer */
} 

int get_version(char *hdr) {
    /* TODO: returns the 4 bit version number as an integer */
} 

char get_flags(char *hdr, int pos) {
    /* TODO: returns the 1 bit (corresponding to the pos)
             from the flags field */
}


int main(int argc, char *argv[]) {
    char *hdr;
    unsigned int n;
 
    /* TODO: Read the contents of the file into hdr */
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
