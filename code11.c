/*
 * code11.c -- encoding for code11 (USD-8)
 *
 * Copyright (c) 1999 Alessandro Rubini (rubini@gnu.org)
 * Copyright (c) 1999 Prosa Srl. (prosa@prosa.it)
 * Copyright (c) 2005 Davide Bernini (dave@gnudd.com)
 * Copyright (c) 2010, 2011 Giuseppe Scrivano (gscrivano@gnu.org)
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "barcode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>


static char alphabet[] = "0123456789-";

static char *codeset[] =  {
    "111121", "211121", "121121",        /* 0     1     2 */
    "221111", "112121", "212111",        /* 3     4     5 */
    "122111", "111221", "211211",        /* 6     7     8 */
    "211111", "112111", "112211"         /* 9     -    SS */
};


#define START_STOP 11
#define HYPHEN       45    

/*
 * Check that the text can be encoded. Returns 0 or -1.
 */


int Barcode_11_verify(unsigned char *text)
{
    int i;
    char *chr = NULL;

    if (text[0] == '\0')
        return -1;
    
    for (i = 0; text[i]; i++) 
        if ((chr = strchr(alphabet, text[i])) == NULL) 
            return -1;
    
    return 0;
}


/*
 * The encoding functions fills the "partial" and "textinfo" fields.
 */

int Barcode_11_encode(struct Barcode_Item *bc)
{
    static char *text;
    static char *partial;  /* dynamic */
    static char *textinfo; /* dynamic */
    char *c = NULL, *textptr = NULL;
    int i, code, textpos, len = 0;
    int weight = 0;
    int c_checksum = 0, k_checksum = 0;
    
    if (bc->partial)
        free(bc->partial);
    
    if (bc->textinfo)
        free(bc->textinfo);
    
    bc->partial = bc->textinfo = NULL; /* safe */

    if ((bc->encoding == NULL))
        bc->encoding = strdup("code 11");

    if ((text = bc->ascii) == NULL) {
        bc->error = EINVAL;
        
        return -1;
    }
    
    if ((len = strlen(text)) == 0) {
         bc->error = EINVAL;
        
        return -1;
    }

    /* allocate space for 2 start-stop symbol and C checksum      
     * we need extra space for K checksum when len >= 10 */
    /*
    if ((partial = (char *)calloc(1, (len >= 10) ? ((len + 4) * 7) + 1 :
            ((len + 3) * 7) + 1)) == NULL) { 
        bc->error = errno;
        
        return -1;
    } 

    if ((textinfo = (char *)calloc(1, 10 * (len + 2))) == NULL) {
        bc->error = errno;
        free(partial);
    
        return -1;
    } */
    
    strcpy(partial, "0"); /*  no-extra-space-needed - see ps.c */
    
    strcat(partial, codeset[START_STOP]);
    
    textptr = textinfo;
    textpos = 7;
    
    for (i = 0; text[i]; i++) {
        if ((c = strchr(alphabet, text[i])) == NULL) {
            bc->error = EINVAL; /* impossible if text is verified */
            free(partial);
            free(textinfo);
    
            return -1;
        }
    
        code = c - alphabet;
        strcat(partial, codeset[code]);
           
        sprintf(textptr, "%i:7:%c ", textpos, text[i]);
                  
        textpos += 7; /* width of each code */
        textptr += strlen(textptr);
    }
    
    /* Add the checksum */
    if ((bc->flags & BARCODE_NO_CHECKSUM) == 0) {

        /* 
         * 'C' checksum weighting goes from 1 (right-most) up to 
         * 10 and then starts again at 1. 
         */
    
        for (i = 1; i <= len; i++) {
            weight = ((i - 1) % 10) + 1;
        
            if (text[len - i] == HYPHEN) 
                c_checksum += (10 * weight);
            else                 
                c_checksum += ((text[len - i] - 48) * weight);
        }
    
        strcat(partial, codeset[c_checksum % 11]);
    
        
        if (len >= 10 ) { /* Add K checksum */
            /*
             * The 'K' checksum weighting goes from 1 (right-most) up to only 9 
             * and then starts at 1 again.
             */

            for (i = 1; i <= len; i++) {
                /* last character is c_checksum */
                weight = ((i - 1) % 9) + (i < 9 ? 2 : 1);    
            
                if (text[len - i] == HYPHEN) 
                    k_checksum += (10 * weight);
                else                 
                    k_checksum += ((text[len - i] - 48) * weight);
            }

            /* add c_checksum to K - it's the last character so its weight is 1 */
            k_checksum += (c_checksum % 11);

            strcat(partial, codeset[k_checksum % 9]);
        }
    }
    
    /* end */
    
    strcat(partial, codeset[START_STOP]);

    bc->partial = partial;
    bc->textinfo = textinfo;

    return 0;
}
