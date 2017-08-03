/*
  bubblebabble.c: licensed under BSD-License, see below.
 */

/*
 * fingerprint_bubblebabble() from openssh-portable/sshkey.c:
 *
 * Copyright (c) 2000, 2001 Markus Friedl.  All rights reserved.
 * Copyright (c) 2008 Alexander von Gernler.  All rights reserved.
 * Copyright (c) 2010,2011 Damien Miller.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

static char *
fingerprint_bubblebabble(u_char *dgst_raw, size_t dgst_raw_len)
{
        char vowels[] = { 'a', 'e', 'i', 'o', 'u', 'y' };
        char consonants[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'k', 'l', 'm',
            'n', 'p', 'r', 's', 't', 'v', 'z', 'x' };
        u_int i, j = 0, rounds, seed = 1;
        char *retval;

        rounds = (dgst_raw_len / 2) + 1;
        if ((retval = calloc(rounds, 6)) == NULL)
                return NULL;
        retval[j++] = 'x';
        for (i = 0; i < rounds; i++) {
                u_int idx0, idx1, idx2, idx3, idx4;
                if ((i + 1 < rounds) || (dgst_raw_len % 2 != 0)) {
                        idx0 = (((((u_int)(dgst_raw[2 * i])) >> 6) & 3) +
                            seed) % 6;
                        idx1 = (((u_int)(dgst_raw[2 * i])) >> 2) & 15;
                        idx2 = ((((u_int)(dgst_raw[2 * i])) & 3) +
                            (seed / 6)) % 6;
                        retval[j++] = vowels[idx0];
                        retval[j++] = consonants[idx1];
                        retval[j++] = vowels[idx2];
                        if ((i + 1) < rounds) {
                                idx3 = (((u_int)(dgst_raw[(2 * i) + 1])) >> 4) & 15;
                                idx4 = (((u_int)(dgst_raw[(2 * i) + 1]))) & 15;
                                retval[j++] = consonants[idx3];
                                retval[j++] = '-';
                                retval[j++] = consonants[idx4];
                                seed = ((seed * 5) +
                                    ((((u_int)(dgst_raw[2 * i])) * 7) +
                                    ((u_int)(dgst_raw[(2 * i) + 1])))) % 36;
                        }
                } else {
                        idx0 = seed % 6;
                        idx1 = 16;
                        idx2 = seed / 6;
                        retval[j++] = vowels[idx0];
                        retval[j++] = consonants[idx1];
                        retval[j++] = vowels[idx2];
                }
        }
        retval[j++] = 'x';
        retval[j++] = '\0';
        return retval;
}


int main(int argc, char **argv) {
  FILE *input;
  u_char digest[1024];
  size_t digestlen;
  char *hash;
  int out = 1;
  
  if(argc < 2) {
    input = stdin;
  }
  else {
    if((input = fopen(argv[1], "rb")) == NULL) {
      fprintf(stderr, "oops, could not open file!\n");
      goto done;
    }
  }

  digestlen = fread(digest, 1, 1024, input);

  if(digestlen > 0) {
    hash = fingerprint_bubblebabble(digest, digestlen);
    fprintf(stdout, "%s\n", hash);
    free(hash);
    out = 0;
  }
  else {
    fprintf(stderr, "oops, could not calculate bubbles!\n");
    goto done;
  }

 done:
  return out;  
}
