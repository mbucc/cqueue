/*
 * Copyright (c) 2014 Mark Bucciarelli <mkbucc@gmail.com>
 * All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */



#include <stdio.h>
#include <stdlib.h>

#include "../queue.h"

SLIST_HEAD(head, entry);


// The SLIST_ENTRY macro "list-enables" the structure.
//
// At first, I thought `SLIST_ENTRY(entry)` is the list of nodes.
// It's not.
// It stores the pointer
// (singular for an SLIST)
// that lets the struct participate
// in the list.
//
// The `children` struct points to the list of child nodes.
struct entry {
	int	id;
	struct head children;
	SLIST_ENTRY(entry) links;
};


// Add `n` new nodes to the given list.
// Insert each new node at the start of the list.
void
addnodes(struct head *h, int n)
{
	struct entry	*np = 0;

	for (int i = 0; i < n; i++) {
		np = calloc(1, sizeof(struct entry));
		np->id = i;
		SLIST_INIT(&np->children);
		SLIST_INSERT_HEAD(h, np, links);
	}
}

// Print tree structure to stdout.
void
dumptree(struct head *h, int depth)
{
	struct entry	*np = 0;

	SLIST_FOREACH(np, h, links) {
		for (int i = 0; i < depth; i++)
			printf("    ");
		printf("%d\n", np->id);
		dumptree(&np->children, depth + 1);
	}
}

int
main(int argc, char **argv)
{
	struct head	root;

	SLIST_INIT(&root);

	addnodes(&root, 2);

	addnodes(&SLIST_FIRST(&root)->children, 4);

	addnodes(&SLIST_NEXT(SLIST_FIRST(&root), links)->children, 2);

	// dumptree output:
	//
	//		1
	//		    3
	//		    2
	//		    1
	//		    0
	//		0
	//		    1
	//		    0
	dumptree(&root, 0);

	/* free_tree(&root); */
}
