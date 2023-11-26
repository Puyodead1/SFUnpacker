// This file was taken from Observer (https://github.com/lazyhamster/Observer)

#ifndef Decompress_h__
#define Decompress_h__

#include "Streams.h"

bool Explode(AStream* inStream, uint32_t inSize, AStream* outStream, uint32_t* outSize, uint32_t* outCrc);
bool Unstore(AStream* inStream, uint32_t inSize, AStream* outStream, uint32_t* outCrc);
bool LzmaDecomp(AStream* inStream, uint32_t inSize, AStream* outStream, uint32_t* outSize, uint32_t* outCrc);
bool Lzma2Decomp(AStream* inStream, uint32_t inSize, AStream* outStream, uint32_t* outSize, uint32_t* outCrc);

#endif // Decompress_h__