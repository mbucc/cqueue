/*
 * Copyright (c) 2014 Mark Bucciarelli <mkbucc@gmail.com>
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */



#include <stdio.h>
#include <stdlib.h>

#include "../queue.h"


// Macro expansions.
//
// For clarity, backslashes are right aligned.
int
main(int argc, char **argv)
{
	//
	//		struct listhead {                                      \		
	//			struct entry *slh_first;                           \
	//		} head;
	//
	SLIST_HEAD(listhead, entry) head; 

	//
	//		struct entry {
	//			int		id;         
	//			struct {                                           \
	//				struct entry *sle_next};                       \
	//			}	entries;
	//		} *n1, *n2, *np;
	//	
	struct entry {
		int	id;
		SLIST_ENTRY(entry) entries;
	} *n1, *n2, *np; 
	 
	//		((&head)->slh_first) = NULL;
	SLIST_INIT(&head);

	//		do {                                                   \
	//			(n1)->entries.sle_next = (&head)->slh_first;       \
	//			(&head)->slh_first = (n1);	                     \
	//		} while (0);
	n1 = malloc(sizeof(struct entry));
	n1->id = 1;
	SLIST_INSERT_HEAD(&head, n1, entries); 

	//		do {                                                   \
	//			(n2)->entries.sle_next = (n1)->entries.sle_next;   \
	//			(n1)->entries.sle_next = (n2);                     \
	//		} while (0);
	 
	n2 = malloc(sizeof(struct entry));
	n2->id = 2;
	SLIST_INSERT_AFTER(n1, n2, entries); 
	 
	//		for((np) = ((&head)->slh_first);                      \
	//			(np) != NULL;                                     \
	//			(np) = ((np)->entries.sle_next) )

	SLIST_FOREACH(np, &head, entries)
		printf("node id = %d\n", np->id);
	 
	//		while ( ! ( ((&head)->slh_first) == NULL ) ) {
	//			n1 = ((&head)->slh_first);
	//			(&head)->slh_first = (&head)->slh_first->entries.sle_next;
	//			free(n1);
	//		}
	while (!SLIST_EMPTY(&head)) {
		n1 = SLIST_FIRST(&head); 
		SLIST_REMOVE_HEAD(&head, entries); 
		free(n1); 
	}
}
