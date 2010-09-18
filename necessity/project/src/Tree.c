#include "Tree.h"
#include "Thing.h"

#if 0
/* TODO: finish this */
/* this is really going to be an AVL tree */

typedef struct TNode_t * TNode;
typedef struct TNode_t
{
	/* traditional: */
	TNode parent;
	TNode right;
	TNode left;
	Thing thing;
	/* additions for self balancing */
	int balance; /* balance factor */
	uint height;
};

/* getters */
static TNode GetRightTNode  (TNode node) { return(node->right); }
static TNode GetLeftTNode   (TNode node) { return(node->left); }
static TNode GetParentTNode (TNode node) { return(node->parent); }
Thing GetThingTNode(TNode node) { return(node->thing); }

static int   GetBalanceTnode(TNode node) { return(node->balance); }
static uint  GetHeightTnode (TNode node) { return(node->height); }

/* setters */

/* setters rerturn the TNode so that you can chain assignments */
static TNode SetRightTNode(TNode self, TNode R) 
{
	self->right = R;
	return(self);
}

static TNode SetLeftTNode(TNode self, TNode L) 
{
	self->left = L;
	return(self); 
}

static TNode SetParentTNode(TNode self, TNode P) 
{
	self->parent = P;
	return(self);
}

static TNode SetThingTNode(TNode self, Thing T)
{
	self->thing = T;
	return(self);

static TNode SetBalanceTNode(TNode self, int bal) 
{ 
	self->balance = bal;
	return(self);
}

static TNode SetHeightTNode(TNode self, uint hi)
{
	self->height = hi;
	return(self);
}

/* Tree --------------------------------------------------------------------- */

typedef struct Tree_t * Tree;
typedef struct Tree_t
{
	TNode root;
	uint size;
	uint depth
};

/* getters */
TNode GetTreeRoot (Tree tree) { return(tree->root); }
uint  GetTreeSize (Tree tree) { return(tree->size); }
uint  GetTreeDepth(Tree tree) { return(tree->depth); }

/* setters */




Tree NewTree()
{

};

#endif



