#pragma once
#ifndef __DLIST_H__
#define __DLIST_H__

#include "../common/common.h"

#define LIST_MAX_LEN 1024

/// @struct node_t
/// @brief 이중연결리스트의 구성 요소인 노드 구조체 
typedef struct node_s node_t;
struct node_s{
    /// 사용자 정의 데이터 
    int data;
    /// 이전 노드 객체 
    struct node_s *prev;
    /// 다음 노드 객체 
    struct node_s *next;
};

/// @struct dlist_t
/// @brief 이중연결리스트를 관리하는 구조체 
typedef struct dlist_s dlist_t;
struct dlist_s{
    /// 이중연결리스트 길이 
    int length;
    /// 리스트 첫 번째 노드 객체 (dummy) 
    node_t *head;
    /// 리스트 마지막 노드 객체 (dummy) 
    node_t *tail;
};

dlist_t* dlist_create();
void dlist_init( dlist_t *list);
void dlist_destroy( dlist_t *list);
int dlist_add_node( dlist_t *list, int data);
node_t* dlist_find_node_by_data( dlist_t *list, int data);
node_t* dlist_find_node_by_node( dlist_t *list, node_t *node);
int dlist_find_node_data_by_node( dlist_t *list, node_t *target);
int dlist_delete_node_by_data( dlist_t *list, int data);
int dlist_delete_node_by_node( dlist_t *list, node_t *node);
int dlist_print_all( dlist_t *list);

#endif
