#ifndef ZENOCRYPT
#define ZENOCRYPT
#include <stdint.h>
#include <stdlib.h>
#ifdef __cplusplus
namespace archivist{
#endif

struct zeno_cipher
{
	double* content;
	size_t length;
	size_t size;
};

typedef struct zeno_cipher zeno_cipher;

zeno_cipher* crypt16(
	double* data,
	size_t data_sz,
	float* key,
	float* salt,
	size_t key_sz
);

int16_t* decrypt16(
	zeno_cipher* data,
	float* key,
	float* salt,
	size_t key_sz
);

zeno_cipher* add16(
	zeno_cipher* data,
	size_t position,
	int16_t value,
	float* key,
	float* salt,
	size_t key_sz
);

zeno_cipher* multiply16(
	zeno_cipher* data,
	size_t position,
	double value,
	float* key,
	float* salt,
	size_t key_sz
);

#ifdef __cplusplus
}
#endif

#endif