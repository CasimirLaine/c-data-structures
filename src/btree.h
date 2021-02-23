#pragma once
#include <stdbool.h>

typedef struct bt_Node {
	struct bt_Node* parent;
	struct bt_Node* left;
	struct bt_Node* right;
	void* value;
} bt_Node;

bt_Node* bt_create();

bt_Node* bt_get_root(bt_Node*);

bt_Node* bt_insert_left(bt_Node*);

bt_Node* bt_insert_right(bt_Node*);

bool bt_delete(bt_Node*);

unsigned int bt_node_count(bt_Node*);
