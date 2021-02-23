#include <stdlib.h>
#include "btree.h"

bt_Node* bt_create() {
	bt_Node* nodePtr = malloc(sizeof(bt_Node));
	if (nodePtr == NULL) {
		return NULL;
	}
	nodePtr->parent = NULL;
	nodePtr->left = NULL;
	nodePtr->right = NULL;
	nodePtr->value = NULL;
	return nodePtr;
}

bt_Node* bt_get_root(bt_Node* nodePtr) {
	if (nodePtr == NULL) {
		return NULL;
	}
	if (nodePtr->parent != NULL) {
		return bt_get_root(nodePtr->parent);
	}
	return nodePtr;
}

bt_Node* bt_insert_left(bt_Node* nodePtr) {
	if (nodePtr == NULL) {
		return NULL;
	}
	bt_Node* newNodePtr = bt_create();
	newNodePtr->left = nodePtr->left;
	newNodePtr->parent = nodePtr;
	if (nodePtr->left != NULL) {
		nodePtr->left->parent = newNodePtr;
	}
	nodePtr->left = newNodePtr;
	return newNodePtr;
}

bt_Node* bt_insert_right(bt_Node* nodePtr) {
	if (nodePtr == NULL) {
		return NULL;
	}
	bt_Node* newNodePtr = bt_create();
	newNodePtr->right = nodePtr->right;
	newNodePtr->parent = nodePtr;
	if (nodePtr->right != NULL) {
		nodePtr->right->parent = newNodePtr;
	}
	nodePtr->right = newNodePtr;
	return newNodePtr;
}

bool bt_delete(bt_Node* nodePtr) {
	if (nodePtr == NULL || (nodePtr->left != NULL && nodePtr->right != NULL)) {
		return false;
	}
	bt_Node* childPtr = nodePtr->left;
	if (childPtr == NULL) {
		childPtr = nodePtr->right;
	}
	if (childPtr != NULL) {
		childPtr->parent = nodePtr->parent;
	}
	if (nodePtr->parent->left == nodePtr) {
		nodePtr->parent->left = childPtr;
	} else {
		nodePtr->parent->right = childPtr;
	}
	free(nodePtr);
	return true;
}

unsigned int bt_node_count(bt_Node* nodePtr) {
	if (nodePtr == NULL) {
		return 0;
	}
	unsigned int counter = 0;
	counter += bt_node_count(nodePtr->left);
	counter += bt_node_count(nodePtr->right);
	counter += nodePtr->left != NULL;
	counter += nodePtr->right != NULL;
	return counter;
}
