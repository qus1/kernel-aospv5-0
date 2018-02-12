#ifndef SYS_COMPAT_RSA_VERIFY_H_
#define SYS_COMPAT_RSA_VERIFY_H_

//#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct HASH_CTX;  // forward decl

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef signed long long int64_t;

typedef struct HASH_VTAB {
  void (* const init)(struct HASH_CTX*);
  void (* const update)(struct HASH_CTX*, const void*, int);
  const uint8_t* (* const final)(struct HASH_CTX*);
  const uint8_t* (* const hash)(const void*, int, uint8_t*);
  int size;
} HASH_VTAB;

typedef struct HASH_CTX {
  const HASH_VTAB * f;
  uint64_t count;
  uint8_t buf[64];
  uint32_t state[8];  // upto SHA2
} HASH_CTX;

#define HASH_init(ctx) (ctx)->f->init(ctx)
#define HASH_update(ctx, data, len) (ctx)->f->update(ctx, data, len)
#define HASH_final(ctx) (ctx)->f->final(ctx)
#define HASH_hash(data, len, digest) (ctx)->f->hash(data, len, digest)
#define HASH_size(ctx) (ctx)->f->size

typedef HASH_CTX SHA_CTX;

void SHA_init(SHA_CTX* ctx);
void SHA_update(SHA_CTX* ctx, const void* data, int len);
const uint8_t* SHA_final(SHA_CTX* ctx);

// Convenience method. Returns digest address.
// NOTE: *digest needs to hold SHA_DIGEST_SIZE bytes.
const uint8_t* SHA_hash(const void* data, int len, uint8_t* digest);

#define SHA_DIGEST_SIZE 20

typedef HASH_CTX SHA256_CTX;

void SHA256_init(SHA256_CTX* ctx);
void SHA256_update(SHA256_CTX* ctx, const void* data, int len);
const uint8_t* SHA256_final(SHA256_CTX* ctx);

// Convenience method. Returns digest address.
const uint8_t* SHA256_hash(const void* data, int len, uint8_t* digest);

#define SHA256_DIGEST_SIZE 32

#define RSANUMBYTES 256           /* 2048 bit key length */
#define RSANUMWORDS (RSANUMBYTES / sizeof(uint32_t))

typedef struct RSAPublicKey {
    int len;                  /* Length of n[] in number of uint32_t */
    uint32_t n0inv;           /* -1 / n[0] mod 2^32 */
    uint32_t n[RSANUMWORDS];  /* modulus as little endian array */
    uint32_t rr[RSANUMWORDS]; /* R^2 as little endian array */
    int exponent;             /* 3 or 65537 */
} RSAPublicKey;

int RSA_verify(const RSAPublicKey *key,
               const uint8_t* signature,
               const int len,
               const uint8_t* hash,
               const int hash_len);

int verify_sig(uint8_t *rsa_data, uint8_t *rand_data);

static uint32_t pub_key_n[64] =   {3002473447U,179648323U,936724521U,3832874451U,2389573967U,
                        1709461230U,4226662187U,3138036193U,769831716U,1230647012U,
                        4268956124U,1119254298U,525310122U,4111771082U,2068979672U,
                        2603226744U,1868922376U,1473543244U,873735907U,2231472425U,
                        2761007170U,2751249780U,3927618991U,513270618U,2835995120U,
                        599062825U,1867765503U,795448992U,1251178192U,2841710589U,
                        1624807280U,3547814812U,1050370811U,2579107919U,234548240U,
                        1744225285U,4025240844U,582932829U,1998567788U,1453067099U,
                        976556346U,3461761633U,4207487490U,98371619U,3892589060U,
                        2011255471U,3267141020U,4173932396U,2506942541U,4267774936U,
                        1437986440U,942120263U,2268199664U,1787560496U,1209446229U,
                        1480000386U,3101554169U,3439321102U,2727877944U,3400823171U,
                        1460981511U,3987455265U,1173832790U,3468724401U};
static uint32_t pub_key_rr[64] =  {3233720911U,280736147U,1793564899U,776942115U,3596998322U,
                        2210984536U,2287582765U,2251024198U,2140963330U,641914191U,
                        4289055795U,56196880U,1299107937U,3939717426U,521560261U,
                        2708648109U,3574186570U,853606388U,3548860714U,1048391002U,
                        2489982697U,2109013835U,1948877486U,1735225133U,691137923U,
                        1389701989U,2784633831U,535606155U,368271781U,188220674U,
                        1373602536U,2520000934U,2666936173U,1861484295U,3964899703U,
                        2926511998U,256383315U,3587588928U,141481090U,497666934U,
                        2040971907U,181562407U,3613171303U,2666074259U,1313098052U,
                        3863719572U,1112958797U,1867587326U,3542356337U,873942392U,
                        1594383321U,1638256492U,853803690U,3306003020U,87427526U,
                        59510733U,565387286U,514692754U,3874340299U,3919144861U,
                        2177105590U,708613882U,2530331648U,478504149U};

#ifdef __cplusplus
}
#endif // __cplusplus

#endif   //SYS_COMPAT_RSA_VERIFY_H_
