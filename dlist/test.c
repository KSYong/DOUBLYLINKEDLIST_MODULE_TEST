#include "dlist.h"

int main( int argc, char **argv){
    printf("---- @ dlist test @ ----\n\n");

    int rv;
    node_t *node;
    dlist_t *list;

    list = dlist_create();
    if( list == NULL){
        printf("    | ! test : Failed to create list!\n");
        return 0;
    }

    rv = dlist_add_node( list, 1);
    if( rv < NORMAL){
        printf("    | ! Failed to add node in list\n");
        return rv;
    }
    else{
        printf("    | @ Success to add node in list (data : 1)\n");
    }
    
    node = dlist_find_node_by_data( list, 1);
    if( node == NULL){
        printf("    | ! Failed to find node by data\n");
        return OBJECT_ERR;
    }
    else{
        printf("    | @ Success to find node by data(data : 1)\n");
    }

    node = dlist_find_node_by_node( list, node);
    if( node == NULL){
        printf("    | ! Failed to find node by node\n");
        return OBJECT_ERR;
    }
    else{
        printf("    | @ Success to find node by node\n");
    }

    rv = dlist_find_node_data_by_node( list, node);
    if( rv < NORMAL){
        printf("    | ! Failed to find node data by node\n");
        return rv;
    }
    else{
        printf("    | @ Success to find node data by node (data : %d)\n", rv);
    }

    rv = dlist_delete_node_by_data( list, 1);
    if( rv < NORMAL){
        printf("    | ! Failed to delete node by data\n");
        return rv;
    }
    else{
        printf("    | @ Success to delete node by data(data : 1)\n");
    }

    rv = dlist_add_node( list, 2);
    if( rv < NORMAL){
        printf("    | ! Failed to add ndoe in list\n");
        return rv;
    }
    else{
        printf("    | @ Success to add node by data(data : 2)\n");
    }
    
    rv = dlist_delete_node_by_node( list, node);
    if( rv < NORMAL){
        printf("    | ! Failed to delete node by node\n");
        return rv;
    }
    else{
        printf("    | @ Success to delete node by node)\n");
    }
    
    dlist_add_node( list, 1);
    dlist_add_node( list, 2);
    dlist_add_node( list, 3);

    rv = dlist_print_all( list);
    if( rv < NORMAL){
        printf("    | ! Failed to print all\n");
        return rv;
    }
    else{
        printf("    | @ Success to print all\n");
    }

    dlist_destroy( list);

    printf("\n  test end\n\n");
}
    




