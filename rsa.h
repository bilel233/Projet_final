long extended_gcd(long a,long t,long *u, long *v);
//void generate_key_values(uint16_t e, uint16_t *p, uint16_t *q, uint32_t *n, uint32_t *phi);
//uint16_t gcd(uint16_t a, uint32_t b);
long* encrypt(char* chaine, long s, long n);
char* decrypt(long* crypted, int size,long u, long n);


