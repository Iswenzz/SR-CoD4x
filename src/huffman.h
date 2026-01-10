#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include "msg.h"

#define NYT HMAX /* NYT = Not Yet Transmitted */
#define INTERNAL_NODE (HMAX + 1)

typedef struct nodetype
{
	struct nodetype *left, *right, *parent; /* tree structure */
											//	struct  nodetype *next, *prev; /* doubly-linked list */
											//	struct  nodetype **head; /* highest ranked node in block */
	int weight;
	int symbol; // 0x10
				//	struct  nodetype *next, *prev; /* doubly-linked list */
				//	struct  nodetype **head; /* highest ranked node in block */

} node_t; // Length: 20

#define HMAX 256 /* Maximum symbol */

typedef struct
{
	int blocNode;
	int blocPtrs;

	node_t* tree;
	node_t* loc[HMAX + 1];
	node_t** freelist;

	node_t nodeList[768];
	node_t* nodePtrs[768];

} huff_t;
/* size 19476*/

int MSG_ReadBitsCompress(const byte* input, int readsize, byte* outputBuf, int outputBufsize);
int MSG_WriteBitsCompress(const byte* datasrc, byte* buffdest, int bytecount);
void Huffman_InitMain();

#endif
