typedef struct key  {
    long m;// represente ou bien la cle privee ou bien la cle publique
    long n;
}KEY;

void init_key(KEY* key, long val, long n);