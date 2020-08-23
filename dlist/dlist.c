#include "dlist.h"

//--------------------------------------------------

/**
 * @fn static node_t* node_create()
 * @brief 이중연결리스트를 구성할 노드 객체를 생성하는 함수
 * @return 생성된 노드 객체
 */
static node_t* node_create(){
    node_t *node = ( node_t*)malloc(sizeof(node_t));
    if( node == NULL){
        printf("    | ! Dlist : Failed to create node object in node_create\n");
        return OBJECT_ERR;
    }

    node->prev = NULL;
    node->next = NULL;
    node->data = NULL;

    return node;
}

/**
 * @fn static void node_destroy( node_t *target)
 * @brief 생성된 노드 객체를 삭제하는 함수
 * @return void
 * @param target 삭제할 노드 객체
 */
static void node_destroy( node_t *target){
    if( target == NULL){
        printf("    | ! Dlist : Failed to call node object in node_destroy\n");
        return OBJECT_ERR;
    }
    else{
        target->prev = NULL;
        target->next = NULL;
        target->data = NULL;

        memset( target, '\0', sizeof( target));
        free( target);
    }
}

//--------------------------------------------------

/**
 * @fn dlist_t* dlist_create()
 * @brief 이중연결 리스트 객체를 생성하는 함수
 * @return 생성된 리스트 객체
 */
dlist_t* dlist_create(){
    dlist_t *list = ( dlist_t*)malloc( sizeof( dlist_t));
    if( list == NULL){
        printf("    | ! Dlist : Failed to create list object in dlist_create\n");
        return OBJECT_ERR;
    }

    list->length = 0;

    list->head->data = NULL;
    list->head->prev = NULL;
    list->head->next = list->tail;

    list->tail->data = NULL;
    list->tail->prev = list->head;
    list->tail->next = NULL;

    return list;
}

/**
 * @fn void dlist_destroy( dlist_t *list)
 * @brief 생성된 리스트 객체와 리스트가 갖고 있는 모든 노드들을 삭제하는 함수
 * @return void
 * @param list 삭제할 리스트 객체
 */
void dlist_destroy( dlist_t *list){
    if( list){
        node_t *temp_node = list->head->next;
        node_t *delete_node = temp_node;
        node_t *tail = list->tail;

        while( temp_node != tail){
            temp_node = temp_node->next;
            dlist_delete_node_by_node( list, delete_node);
            delete_node = temp_node;
        }

        memset( list, '\0', sizeof( list));
        free( list);
    }
    else{
        printf("    | ! Dlist : Failed to call object in dlist_destroy\n");
        return OBJECT_ERR;
    }
}

/**
 * @fn int dlist_add_node( dlist_t *list, void* data)
 * @brief 이중연결리스트에 노드를 추가하는 함수
 * @return 에러 열거형 참고 
 * @param list 노드를 추가할 리스트 객체 
 * @param data 추가할 노드의 사용자 데이터
 */
int dlist_add_node( dlist_t *list, void* data){
    if( list){
        node_t* new_node = node_create();
        if( new_node == NULL){
            printf("    | ! Dlist : Failed to create node object in dlist_add_node\n");
            return CREATE_ERR;
        }

        if( list->head->next == list->tail){
            list->head->next = new_node;
            new_node->next = list->tail;
            new_node->prev = list->head;
            list->tail->prev = new_node;
        }
        else if( ( list->head->next != list->tail) && ( list->tail->prev != NULL)){
            node_t *prev_node = list->tail->prev;

            prev_node->next = new_node;
            new_node->prev = prev_node;

            list->tail->prev = new_node;
            new_node->next = list->tail;
        }
        else{
            printf("    | ! Dlist : unknown case in dlist_add_node\n");
            return UNKNOWN;
        }

        new_node->data = data;

        list->length++;

        return NORMAL;
    }
    else{
        printf("    | ! Dlist : Failed to call object in dlist_add_node\n");
        return OBJECT_ERR;
    }

}

/**
 * @fn node_t* dlist_find_node_by_data( dlist_t *list, void* data)
 * @brief 주어진 데이터와 일치하는 데이터를 갖는 노드를 찾는 함수 
 * @return 찾은 노드 객체
 * @param list 노드를 찾을 리스트 
 * @param data 주어진 데이터 
 */
node_t* dlist_find_node_by_data( dlist_t *list, void* data){
    if( list){
        node_t *head = list->head;
        node_t *temp_node = list->head->next;
        node_t *tail = list->tail;

        do{
            if( temp_node->data == data){
                return temp_node;
            }

            temp_node = temp_node->next;
        }while( temp_node->next != tail);

        return NO_MATCH;
    }
    else{
        printf("    | ! Dlist : Failed to call object in dlist_find_node_by_data\n");
        return OBJECT_ERR;
    }

}

/**
 * @fn node_t* dlist_find_node_by_node( dlist_t *list, node_t *target)
 * @brief 주어진 노드와 일치하는 노드를 찾는 함수 
 * @return 찾은 노드 객체
 * @param list 노드를 찾을 리스트
 * @param target 주어진 노드 
 */
node_t* dlist_find_node_by_node( dlist_t *list, node_t *target){
    if( list){
        node_t *head = list->head;
        node_t *temp_node = list->head->next;
        node_t *tail = list->tail;

        do{
            if( temp_node == target){
                return temp_node;
            }

            temp_node = temp_node->next;
        }while( temp_node->next != tail);

        return NO_MATCH;
    }
    else{
        printf("    | ! Dlist : Failed to call object in dlist_find_node_by_node\n");
        return OBJECT_ERR;
    }
}

/**
 * @fn int dlist_find_node_data_by_node( dlist_t *list, node_t *target)
 * @brief 주어진 노드와 일치하는 노드의 데이터를 찾는 함수
 * @return 찾은 데이터 
 * @param list 노드를 찾을 리스트
 * @param target 주어진 노드 
 */
void* dlist_find_node_data_by_node( dlist_t *list, node_t *target){
    if( list){
        node_t *head = list->head;
        node_t *temp_node = list->head->next;
        node_t *tail = list->tail;

        do{
            if( temp_node == target){
                return temp_node->data;
            }

            temp_node = temp_node->next;
        }while( temp_node->next != tail);

        return NO_MATCH;
    }
    else{
        printf("    | ! Dlist : Failed to call object in dlist_find_node_data_by_node\n");
        return OBJECT_ERR;
    }
}

/**
 * @fn int dlist_delete_node_by_data( dlist_t *list, void* data)
 * @brief 주어진 데이터와 일치하는 노드를 삭제하는 함수 
 * @return 에러 열거형 참고
 * @param list 삭제할 노드를 찾을 리스트
 * @param data 삭제할 노드의 데이터 
 */
int dlist_delete_node_by_data( dlist_t *list, void* data){
    if( list){
        node_t *head = list->head;
        node_t *temp_node = list->head->next;
        node_t *tail = list->tail;

        while( temp_node != tail){
            if( temp_node->data == data){
                if( temp_node->prev == head){
                    head->next = temp_node->next;
                    temp_node->next->prev = head;
                }
                else if( temp_node->next == tail){
                    tail->prev = temp_node->prev;
                    temp_node->prev->next = tail;
                }
                else{
                    temp_node->prev->next = temp_node->next;
                    temp_node->next->prev = temp_node->prev;
                }

                node_destroy( temp_node);

                list->length--;
                return NORMAL;
            }

            temp_node = temp_node->next;
        }

        return NO_MATCH;
    }
    else{
        printf("    | ! Dlist : Failed to call object in dlist_delete_node_by_data\n");
        return OBJECT_ERR;
    }
}

/**
 * @fn int dlist_delete_node_by_node( dlist_t *list, node_t *target)
 * @brief 주어진 노드와 일치하는 노드를 삭제하는 함수 
 * @return 에러 열거형 참고
 * @param list 삭제할 노드를 찾을 리스트
 * @param target 삭제할 노드
 */
int dlist_delete_node_by_node( dlist_t *list, node_t *target){
    if( list){
        node_t *head = list->head;
        node_t *temp_node = list->head->next;
        node_t *tail = list->tail;

        while( temp_node != tail){
            if( temp_node == target){
                if( temp_node->prev == head){
                    head->next = temp_node->next;
                    temp_node->next->prev = head;
                }
                else if( temp_node->next == tail){
                    tail->prev = temp_node->prev;
                    temp_node->prev->next = tail;
                }
                else{
                    temp_node->prev->next = temp_node->next;
                    temp_node->next->prev = temp_node->prev;
                }

                node_destroy( temp_node);

                list->length--;
                return NORMAL;
            }

            temp_node = temp_node->next;
        }

        return NO_MATCH;
    }
    else{
        printf("    | ! Dlist : Failed to call object in dlist_delete_node_by_node\n");
        return OBJECT_ERR;
    }
}

int dlist_get_list_length( dlist_t *list){
    if( list){
        return list->length;
    }
    else{
        printf("    | ! Dlist : Failed to call object in dlist_get_list_length\n");
        return OBJECT_ERR;
    }
}

/**
 * @fn int dlist_print_all( dlist_t *list)
 * @brief 이중연결리스트의 모든 노드 데이터들을 출력하는 함수
 * @return 에러 열거형 참고 
 * @param list 데이터들을 출력할 리스트 객체
 */
int dlist_print_all( dlist_t *list){
    if( list){
        node_t *head = list->head;
        node_t *temp_node = list->head->next;
        node_t *tail = list->tail;

        printf("    | @ Dlist print : ");
        if( temp_node != tail){
            do{
                printf("%d ", temp_node->data);

                temp_node = temp_node->next;
            }while( temp_node != tail);
        }

        printf("    | @ Dlist length : %d", dlist_get_list_length( list));

        printf("\n");

        return NORMAL;
    }
    else{
        printf("    | ! Dlist : Failed to call object in dlist_print_all\n");
        return OBJECT_ERR;
    }

}


