/**
 * treemap.h
 *
 * Creation Date: 28/03/2019
 *
 * Authors:
 * Leonardo Vencovsky (https://github.com/LeoVen)
 *
 */

/**
 * TreeMap
 *
 * A TreeMap is an implementation of a Map that keeps its keys sorted. Like a
 * Map, it has only unique keys. This implementation uses a balanced binary
 * tree called AVL Tree that uses the height of nodes to keep its keys balanced.
 */

#ifndef CMC_TREEMAP_H
#define CMC_TREEMAP_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../utl/cmc_string.h"

/* to_string format */
static const char *cmc_string_fmt_treemap = "%s at %p { root:%p, count:%" PRIuMAX ", cmp:%p }";

#define CMC_GENERATE_TREEMAP(PFX, SNAME, K, V)    \
    CMC_GENERATE_TREEMAP_HEADER(PFX, SNAME, K, V) \
    CMC_GENERATE_TREEMAP_SOURCE(PFX, SNAME, K, V)

#define CMC_WRAPGEN_TREEMAP_HEADER(PFX, SNAME, K, V) \
    CMC_GENERATE_TREEMAP_HEADER(PFX, SNAME, K, V)

#define CMC_WRAPGEN_TREEMAP_SOURCE(PFX, SNAME, K, V) \
    CMC_GENERATE_TREEMAP_SOURCE(PFX, SNAME, K, V)

/* HEADER ********************************************************************/
#define CMC_GENERATE_TREEMAP_HEADER(PFX, SNAME, K, V)                                   \
                                                                                        \
    /* Treemap Structure */                                                             \
    typedef struct SNAME##_s                                                            \
    {                                                                                   \
        /* Root node */                                                                 \
        struct SNAME##_node_s *root;                                                    \
                                                                                        \
        /* Current amount of keys */                                                    \
        size_t count;                                                                   \
                                                                                        \
        /* Key comparison function */                                                   \
        int (*cmp)(K, K);                                                               \
                                                                                        \
        /* Function that returns an iterator to the start of the treemap */             \
        struct SNAME##_iter_s (*it_start)(struct SNAME##_s *);                          \
                                                                                        \
        /* Function that returns an iterator to the end of the treemap */               \
        struct SNAME##_iter_s (*it_end)(struct SNAME##_s *);                            \
                                                                                        \
    } SNAME, *SNAME##_ptr;                                                              \
                                                                                        \
    /* Treemap Node */                                                                  \
    typedef struct SNAME##_node_s                                                       \
    {                                                                                   \
        /* Node Key */                                                                  \
        K key;                                                                          \
                                                                                        \
        /* Node Value */                                                                \
        V value;                                                                        \
                                                                                        \
        /* Node height used by the AVL tree to keep it strictly balanced */             \
        unsigned char height;                                                           \
                                                                                        \
        /* Right child node or subtree */                                               \
        struct SNAME##_node_s *right;                                                   \
                                                                                        \
        /* Left child node or subtree */                                                \
        struct SNAME##_node_s *left;                                                    \
                                                                                        \
        /* Parent node */                                                               \
        struct SNAME##_node_s *parent;                                                  \
                                                                                        \
    } SNAME##_node, *SNAME##_node_ptr;                                                  \
                                                                                        \
    /* Treemap Iterator */                                                              \
    typedef struct SNAME##_iter_s                                                       \
    {                                                                                   \
        /* Target treemap */                                                            \
        struct SNAME##_s *target;                                                       \
                                                                                        \
        /* Cursor's current node */                                                     \
        struct SNAME##_node_s *cursor;                                                  \
                                                                                        \
        /* The first node in the iteration */                                           \
        struct SNAME##_node_s *first;                                                   \
                                                                                        \
        /* The last node in the iteration */                                            \
        struct SNAME##_node_s *last;                                                    \
                                                                                        \
        /* Keeps track of relative index to the iteration of elements */                \
        size_t index;                                                                   \
                                                                                        \
        /* If the iterator has reached the start of the iteration */                    \
        bool start;                                                                     \
                                                                                        \
        /* If the iterator has reached the end of the iteration */                      \
        bool end;                                                                       \
                                                                                        \
    } SNAME##_iter, *SNAME##_iter_ptr;                                                  \
                                                                                        \
    /* Collection Functions */                                                          \
    /* Collection Allocation and Deallocation */                                        \
    SNAME *PFX##_new(int (*compare)(K, K));                                             \
    void PFX##_clear(SNAME *_map_, void (*deallocator)(K, V));                          \
    void PFX##_free(SNAME *_map_, void (*deallocator)(K, V));                           \
    /* Collection Input and Output */                                                   \
    bool PFX##_insert(SNAME *_map_, K key, V value);                                    \
    bool PFX##_update(SNAME *_map_, K key, V new_value, V *old_value);                  \
    bool PFX##_remove(SNAME *_map_, K key, V *out_value);                               \
    /* Element Access */                                                                \
    bool PFX##_max(SNAME *_map_, K *key, V *value);                                     \
    bool PFX##_min(SNAME *_map_, K *key, V *value);                                     \
    V PFX##_get(SNAME *_map_, K key);                                                   \
    V *PFX##_get_ref(SNAME *_map_, K key);                                              \
    /* Collection State */                                                              \
    bool PFX##_contains(SNAME *_map_, K key);                                           \
    bool PFX##_empty(SNAME *_map_);                                                     \
    size_t PFX##_count(SNAME *_map_);                                                   \
    /* Collection Utility */                                                            \
    SNAME *PFX##_copy_of(SNAME *_map_, K (*key_copy_func)(K), V (*value_copy_func)(V)); \
    bool PFX##_equals(SNAME *_map1_, SNAME *_map2_, int (*value_comparator)(V, V));     \
    cmc_string PFX##_to_string(SNAME *_map_);                                           \
                                                                                        \
    /* Iterator Functions */                                                            \
    /* Iterator Allocation and Deallocation */                                          \
    SNAME##_iter *PFX##_iter_new(SNAME *target);                                        \
    void PFX##_iter_free(SNAME##_iter *iter);                                           \
    /* Iterator Initialization */                                                       \
    void PFX##_iter_init(SNAME##_iter *iter, SNAME *target);                            \
    /* Iterator State */                                                                \
    bool PFX##_iter_start(SNAME##_iter *iter);                                          \
    bool PFX##_iter_end(SNAME##_iter *iter);                                            \
    /* Iterator Movement */                                                             \
    void PFX##_iter_to_start(SNAME##_iter *iter);                                       \
    void PFX##_iter_to_end(SNAME##_iter *iter);                                         \
    bool PFX##_iter_next(SNAME##_iter *iter);                                           \
    bool PFX##_iter_prev(SNAME##_iter *iter);                                           \
    bool PFX##_iter_advance(SNAME##_iter *iter, size_t steps);                          \
    bool PFX##_iter_rewind(SNAME##_iter *iter, size_t steps);                           \
    bool PFX##_iter_go_to(SNAME##_iter *iter, size_t index);                            \
    /* Iterator Access */                                                               \
    K PFX##_iter_key(SNAME##_iter *iter);                                               \
    V PFX##_iter_value(SNAME##_iter *iter);                                             \
    V *PFX##_iter_rvalue(SNAME##_iter *iter);                                           \
    size_t PFX##_iter_index(SNAME##_iter *iter);                                        \
                                                                                        \
    /* Default Key */                                                                   \
    static inline K PFX##_impl_default_key(void)                                        \
    {                                                                                   \
        K _empty_key_;                                                                  \
                                                                                        \
        memset(&_empty_key_, 0, sizeof(K));                                             \
                                                                                        \
        return _empty_key_;                                                             \
    }                                                                                   \
                                                                                        \
    /* Default Value */                                                                 \
    static inline V PFX##_impl_default_value(void)                                      \
    {                                                                                   \
        V _empty_value_;                                                                \
                                                                                        \
        memset(&_empty_value_, 0, sizeof(V));                                           \
                                                                                        \
        return _empty_value_;                                                           \
    }                                                                                   \
                                                                                        \
/* SOURCE ********************************************************************/
#define CMC_GENERATE_TREEMAP_SOURCE(PFX, SNAME, K, V)                                        \
                                                                                             \
    /* Implementation Detail Functions */                                                    \
    static SNAME##_node *PFX##_impl_new_node(K key, V value);                                \
    static SNAME##_node *PFX##_impl_get_node(SNAME *_map_, K key);                           \
    static unsigned char PFX##_impl_h(SNAME##_node *node);                                   \
    static unsigned char PFX##_impl_hupdate(SNAME##_node *node);                             \
    static void PFX##_impl_rotate_right(SNAME##_node **Z);                                   \
    static void PFX##_impl_rotate_left(SNAME##_node **Z);                                    \
    static void PFX##_impl_rebalance(SNAME *_map_, SNAME##_node *node);                      \
    static SNAME##_iter PFX##_impl_it_start(SNAME *_map_);                                   \
    static SNAME##_iter PFX##_impl_it_end(SNAME *_map_);                                     \
                                                                                             \
    SNAME *PFX##_new(int (*compare)(K, K))                                                   \
    {                                                                                        \
        SNAME *_map_ = malloc(sizeof(SNAME));                                                \
                                                                                             \
        if (!_map_)                                                                          \
            return NULL;                                                                     \
                                                                                             \
        _map_->count = 0;                                                                    \
        _map_->root = NULL;                                                                  \
        _map_->cmp = compare;                                                                \
                                                                                             \
        _map_->it_start = PFX##_impl_it_start;                                               \
        _map_->it_end = PFX##_impl_it_end;                                                   \
                                                                                             \
        return _map_;                                                                        \
    }                                                                                        \
                                                                                             \
    void PFX##_clear(SNAME *_map_, void (*deallocator)(K, V))                                \
    {                                                                                        \
        SNAME##_node *scan = _map_->root;                                                    \
        SNAME##_node *up = NULL;                                                             \
                                                                                             \
        while (scan != NULL)                                                                 \
        {                                                                                    \
            if (scan->left != NULL)                                                          \
            {                                                                                \
                SNAME##_node *left = scan->left;                                             \
                                                                                             \
                scan->left = up;                                                             \
                up = scan;                                                                   \
                scan = left;                                                                 \
            }                                                                                \
            else if (scan->right != NULL)                                                    \
            {                                                                                \
                SNAME##_node *right = scan->right;                                           \
                                                                                             \
                scan->left = up;                                                             \
                scan->right = NULL;                                                          \
                up = scan;                                                                   \
                scan = right;                                                                \
            }                                                                                \
            else                                                                             \
            {                                                                                \
                if (up == NULL)                                                              \
                {                                                                            \
                    if (deallocator)                                                         \
                        deallocator(scan->key, scan->value);                                 \
                                                                                             \
                    free(scan);                                                              \
                    scan = NULL;                                                             \
                }                                                                            \
                                                                                             \
                while (up != NULL)                                                           \
                {                                                                            \
                    if (deallocator)                                                         \
                        deallocator(scan->key, scan->value);                                 \
                                                                                             \
                    free(scan);                                                              \
                                                                                             \
                    if (up->right != NULL)                                                   \
                    {                                                                        \
                        scan = up->right;                                                    \
                        up->right = NULL;                                                    \
                        break;                                                               \
                    }                                                                        \
                    else                                                                     \
                    {                                                                        \
                        scan = up;                                                           \
                        up = up->left;                                                       \
                    }                                                                        \
                }                                                                            \
            }                                                                                \
        }                                                                                    \
                                                                                             \
        _map_->count = 0;                                                                    \
        _map_->root = NULL;                                                                  \
    }                                                                                        \
                                                                                             \
    void PFX##_free(SNAME *_map_, void (*deallocator)(K, V))                                 \
    {                                                                                        \
        PFX##_clear(_map_, deallocator);                                                     \
                                                                                             \
        free(_map_);                                                                         \
    }                                                                                        \
                                                                                             \
    bool PFX##_insert(SNAME *_map_, K key, V value)                                          \
    {                                                                                        \
        if (PFX##_empty(_map_))                                                              \
        {                                                                                    \
            _map_->root = PFX##_impl_new_node(key, value);                                   \
                                                                                             \
            if (!_map_->root)                                                                \
                return false;                                                                \
        }                                                                                    \
        else                                                                                 \
        {                                                                                    \
            SNAME##_node *scan = _map_->root;                                                \
            SNAME##_node *parent = scan;                                                     \
                                                                                             \
            while (scan != NULL)                                                             \
            {                                                                                \
                parent = scan;                                                               \
                                                                                             \
                if (_map_->cmp(scan->key, key) > 0)                                          \
                    scan = scan->left;                                                       \
                else if (_map_->cmp(scan->key, key) < 0)                                     \
                    scan = scan->right;                                                      \
                else                                                                         \
                    return false;                                                            \
            }                                                                                \
                                                                                             \
            SNAME##_node *node;                                                              \
                                                                                             \
            if (_map_->cmp(parent->key, key) > 0)                                            \
            {                                                                                \
                parent->left = PFX##_impl_new_node(key, value);                              \
                                                                                             \
                if (!parent->left)                                                           \
                    return false;                                                            \
                                                                                             \
                parent->left->parent = parent;                                               \
                node = parent->left;                                                         \
            }                                                                                \
            else                                                                             \
            {                                                                                \
                parent->right = PFX##_impl_new_node(key, value);                             \
                                                                                             \
                if (!parent->right)                                                          \
                    return false;                                                            \
                                                                                             \
                parent->right->parent = parent;                                              \
                node = parent->right;                                                        \
            }                                                                                \
                                                                                             \
            PFX##_impl_rebalance(_map_, node);                                               \
        }                                                                                    \
                                                                                             \
        _map_->count++;                                                                      \
                                                                                             \
        return true;                                                                         \
    }                                                                                        \
                                                                                             \
    bool PFX##_update(SNAME *_map_, K key, V new_value, V *old_value)                        \
    {                                                                                        \
        SNAME##_node *node = PFX##_impl_get_node(_map_, key);                                \
                                                                                             \
        if (!node)                                                                           \
            return false;                                                                    \
                                                                                             \
        if (old_value)                                                                       \
            *old_value = node->value;                                                        \
                                                                                             \
        node->value = new_value;                                                             \
                                                                                             \
        return true;                                                                         \
    }                                                                                        \
                                                                                             \
    bool PFX##_remove(SNAME *_map_, K key, V *out_value)                                     \
    {                                                                                        \
        SNAME##_node *node = PFX##_impl_get_node(_map_, key);                                \
                                                                                             \
        if (!node)                                                                           \
            return false;                                                                    \
                                                                                             \
        if (out_value)                                                                       \
            *out_value = node->value;                                                        \
                                                                                             \
        SNAME##_node *temp = NULL, *unbalanced = NULL;                                       \
                                                                                             \
        bool is_root = node->parent == NULL;                                                 \
                                                                                             \
        if (node->left == NULL && node->right == NULL)                                       \
        {                                                                                    \
            if (is_root)                                                                     \
                _map_->root = NULL;                                                          \
            else                                                                             \
            {                                                                                \
                unbalanced = node->parent;                                                   \
                                                                                             \
                if (node->parent->right == node)                                             \
                    node->parent->right = NULL;                                              \
                else                                                                         \
                    node->parent->left = NULL;                                               \
            }                                                                                \
                                                                                             \
            free(node);                                                                      \
        }                                                                                    \
        else if (node->left == NULL)                                                         \
        {                                                                                    \
            if (is_root)                                                                     \
            {                                                                                \
                _map_->root = node->right;                                                   \
                _map_->root->parent = NULL;                                                  \
            }                                                                                \
            else                                                                             \
            {                                                                                \
                unbalanced = node->parent;                                                   \
                                                                                             \
                node->right->parent = node->parent;                                          \
                                                                                             \
                if (node->parent->right == node)                                             \
                    node->parent->right = node->right;                                       \
                else                                                                         \
                    node->parent->left = node->right;                                        \
            }                                                                                \
                                                                                             \
            free(node);                                                                      \
        }                                                                                    \
        else if (node->right == NULL)                                                        \
        {                                                                                    \
            if (is_root)                                                                     \
            {                                                                                \
                _map_->root = node->left;                                                    \
                _map_->root->parent = NULL;                                                  \
            }                                                                                \
            else                                                                             \
            {                                                                                \
                unbalanced = node->parent;                                                   \
                                                                                             \
                node->left->parent = node->parent;                                           \
                                                                                             \
                if (node->parent->right == node)                                             \
                    node->parent->right = node->left;                                        \
                else                                                                         \
                    node->parent->left = node->left;                                         \
            }                                                                                \
                                                                                             \
            free(node);                                                                      \
        }                                                                                    \
        else                                                                                 \
        {                                                                                    \
            temp = node->right;                                                              \
            while (temp->left != NULL)                                                       \
                temp = temp->left;                                                           \
                                                                                             \
            K temp_key = temp->key;                                                          \
            V temp_val = temp->value;                                                        \
                                                                                             \
            unbalanced = temp->parent;                                                       \
                                                                                             \
            if (temp->left == NULL && temp->right == NULL)                                   \
            {                                                                                \
                if (temp->parent->right == temp)                                             \
                    temp->parent->right = NULL;                                              \
                else                                                                         \
                    temp->parent->left = NULL;                                               \
            }                                                                                \
            else if (temp->left == NULL)                                                     \
            {                                                                                \
                temp->right->parent = temp->parent;                                          \
                                                                                             \
                if (temp->parent->right == temp)                                             \
                    temp->parent->right = temp->right;                                       \
                else                                                                         \
                    temp->parent->left = temp->right;                                        \
            }                                                                                \
            else if (temp->right == NULL)                                                    \
            {                                                                                \
                temp->left->parent = temp->parent;                                           \
                                                                                             \
                if (temp->parent->right == temp)                                             \
                    temp->parent->right = temp->left;                                        \
                else                                                                         \
                    temp->parent->left = temp->left;                                         \
            }                                                                                \
                                                                                             \
            free(temp);                                                                      \
                                                                                             \
            node->key = temp_key;                                                            \
            node->value = temp_val;                                                          \
        }                                                                                    \
                                                                                             \
        if (unbalanced != NULL)                                                              \
            PFX##_impl_rebalance(_map_, unbalanced);                                         \
                                                                                             \
        _map_->count--;                                                                      \
                                                                                             \
        if (_map_->count == 0)                                                               \
            _map_->root = NULL;                                                              \
                                                                                             \
        return true;                                                                         \
    }                                                                                        \
                                                                                             \
    bool PFX##_max(SNAME *_map_, K *key, V *value)                                           \
    {                                                                                        \
        if (PFX##_empty(_map_))                                                              \
            return false;                                                                    \
                                                                                             \
        SNAME##_node *scan = _map_->root;                                                    \
                                                                                             \
        while (scan->right != NULL)                                                          \
            scan = scan->right;                                                              \
                                                                                             \
        *key = scan->key;                                                                    \
        *value = scan->value;                                                                \
                                                                                             \
        return true;                                                                         \
    }                                                                                        \
                                                                                             \
    bool PFX##_min(SNAME *_map_, K *key, V *value)                                           \
    {                                                                                        \
        if (PFX##_empty(_map_))                                                              \
            return false;                                                                    \
                                                                                             \
        SNAME##_node *scan = _map_->root;                                                    \
                                                                                             \
        while (scan->left != NULL)                                                           \
            scan = scan->left;                                                               \
                                                                                             \
        *key = scan->key;                                                                    \
        *value = scan->value;                                                                \
                                                                                             \
        return true;                                                                         \
    }                                                                                        \
                                                                                             \
    V PFX##_get(SNAME *_map_, K key)                                                         \
    {                                                                                        \
        SNAME##_node *node = PFX##_impl_get_node(_map_, key);                                \
                                                                                             \
        if (!node)                                                                           \
            return PFX##_impl_default_value();                                               \
                                                                                             \
        return node->value;                                                                  \
    }                                                                                        \
                                                                                             \
    V *PFX##_get_ref(SNAME *_map_, K key)                                                    \
    {                                                                                        \
        SNAME##_node *node = PFX##_impl_get_node(_map_, key);                                \
                                                                                             \
        if (!node)                                                                           \
            return NULL;                                                                     \
                                                                                             \
        return &(node->value);                                                               \
    }                                                                                        \
                                                                                             \
    bool PFX##_contains(SNAME *_map_, K key)                                                 \
    {                                                                                        \
        SNAME##_node *scan = _map_->root;                                                    \
                                                                                             \
        while (scan != NULL)                                                                 \
        {                                                                                    \
            if (_map_->cmp(scan->key, key) > 0)                                              \
                scan = scan->left;                                                           \
            else if (_map_->cmp(scan->key, key) < 0)                                         \
                scan = scan->right;                                                          \
            else                                                                             \
                return true;                                                                 \
        }                                                                                    \
                                                                                             \
        return false;                                                                        \
    }                                                                                        \
                                                                                             \
    bool PFX##_empty(SNAME *_map_)                                                           \
    {                                                                                        \
        return _map_->count == 0;                                                            \
    }                                                                                        \
                                                                                             \
    size_t PFX##_count(SNAME *_map_)                                                         \
    {                                                                                        \
        return _map_->count;                                                                 \
    }                                                                                        \
                                                                                             \
    SNAME *PFX##_copy_of(SNAME *_map_, K (*key_copy_func)(K), V (*value_copy_func)(V))       \
    {                                                                                        \
        SNAME *result = PFX##_new(_map_->cmp);                                               \
                                                                                             \
        if (!result)                                                                         \
            return NULL;                                                                     \
                                                                                             \
        SNAME##_iter iter;                                                                   \
        PFX##_iter_init(&iter, _map_);                                                       \
                                                                                             \
        if (!PFX##_empty(_map_))                                                             \
        {                                                                                    \
            for (PFX##_iter_to_start(&iter); !PFX##_iter_end(&iter); PFX##_iter_next(&iter)) \
            {                                                                                \
                K key = PFX##_iter_key(&iter);                                               \
                V value = PFX##_iter_value(&iter);                                           \
                                                                                             \
                if (key_copy_func)                                                           \
                    key = key_copy_func(key);                                                \
                if (value_copy_func)                                                         \
                    value = value_copy_func(value);                                          \
                                                                                             \
                PFX##_insert(result, key, value);                                            \
            }                                                                                \
        }                                                                                    \
                                                                                             \
        return result;                                                                       \
    }                                                                                        \
                                                                                             \
    bool PFX##_equals(SNAME *_map1_, SNAME *_map2_, int (*value_comparator)(V, V))           \
    {                                                                                        \
        if (PFX##_count(_map1_) != PFX##_count(_map2_))                                      \
            return false;                                                                    \
                                                                                             \
        SNAME##_iter iter;                                                                   \
        PFX##_iter_init(&iter, _map1_);                                                      \
                                                                                             \
        for (PFX##_iter_to_start(&iter); !PFX##_iter_end(&iter); PFX##_iter_next(&iter))     \
        {                                                                                    \
            SNAME##_node *node = PFX##_impl_get_node(_map2_, PFX##_iter_key(&iter));         \
                                                                                             \
            if (node == NULL)                                                                \
                return false;                                                                \
                                                                                             \
            if (value_comparator)                                                            \
            {                                                                                \
                if (value_comparator(node->value, PFX##_iter_value(&iter)) != 0)             \
                    return false;                                                            \
            }                                                                                \
        }                                                                                    \
                                                                                             \
        return true;                                                                         \
    }                                                                                        \
                                                                                             \
    cmc_string PFX##_to_string(SNAME *_map_)                                                 \
    {                                                                                        \
        cmc_string str;                                                                      \
        SNAME *m_ = _map_;                                                                   \
        const char *name = #SNAME;                                                           \
                                                                                             \
        snprintf(str.s, cmc_string_len, cmc_string_fmt_treemap,                              \
                 name, m_, m_->root, m_->count, m_->cmp);                                    \
                                                                                             \
        return str;                                                                          \
    }                                                                                        \
                                                                                             \
    SNAME##_iter *PFX##_iter_new(SNAME *target)                                              \
    {                                                                                        \
        SNAME##_iter *iter = malloc(sizeof(SNAME##_iter));                                   \
                                                                                             \
        if (!iter)                                                                           \
            return NULL;                                                                     \
                                                                                             \
        PFX##_iter_init(iter, target);                                                       \
                                                                                             \
        return iter;                                                                         \
    }                                                                                        \
                                                                                             \
    void PFX##_iter_free(SNAME##_iter *iter)                                                 \
    {                                                                                        \
        free(iter);                                                                          \
    }                                                                                        \
                                                                                             \
    void PFX##_iter_init(SNAME##_iter *iter, SNAME *target)                                  \
    {                                                                                        \
        memset(iter, 0, sizeof(SNAME##_iter));                                               \
                                                                                             \
        iter->target = target;                                                               \
        iter->start = true;                                                                  \
        iter->end = PFX##_empty(target);                                                     \
                                                                                             \
        iter->cursor = target->root;                                                         \
                                                                                             \
        if (!PFX##_empty(target))                                                            \
        {                                                                                    \
            while (iter->cursor->left != NULL)                                               \
                iter->cursor = iter->cursor->left;                                           \
                                                                                             \
            iter->first = iter->cursor;                                                      \
                                                                                             \
            iter->last = target->root;                                                       \
            while (iter->last->right != NULL)                                                \
                iter->last = iter->last->right;                                              \
        }                                                                                    \
    }                                                                                        \
                                                                                             \
    bool PFX##_iter_start(SNAME##_iter *iter)                                                \
    {                                                                                        \
        return PFX##_empty(iter->target) || iter->start;                                     \
    }                                                                                        \
                                                                                             \
    bool PFX##_iter_end(SNAME##_iter *iter)                                                  \
    {                                                                                        \
        return PFX##_empty(iter->target) || iter->end;                                       \
    }                                                                                        \
                                                                                             \
    void PFX##_iter_to_start(SNAME##_iter *iter)                                             \
    {                                                                                        \
        if (!PFX##_empty(iter->target))                                                      \
        {                                                                                    \
            iter->index = 0;                                                                 \
            iter->start = true;                                                              \
            iter->end = PFX##_empty(iter->target);                                           \
            iter->cursor = iter->first;                                                      \
        }                                                                                    \
    }                                                                                        \
                                                                                             \
    void PFX##_iter_to_end(SNAME##_iter *iter)                                               \
    {                                                                                        \
        if (!PFX##_empty(iter->target))                                                      \
        {                                                                                    \
            iter->index = iter->target->count - 1;                                           \
            iter->start = PFX##_empty(iter->target);                                         \
            iter->end = true;                                                                \
            iter->cursor = iter->last;                                                       \
        }                                                                                    \
    }                                                                                        \
                                                                                             \
    bool PFX##_iter_next(SNAME##_iter *iter)                                                 \
    {                                                                                        \
        if (iter->end)                                                                       \
            return false;                                                                    \
                                                                                             \
        if (iter->cursor == iter->last)                                                      \
        {                                                                                    \
            iter->end = true;                                                                \
            return false;                                                                    \
        }                                                                                    \
                                                                                             \
        iter->start = PFX##_empty(iter->target);                                             \
                                                                                             \
        if (iter->cursor->right != NULL)                                                     \
        {                                                                                    \
            iter->cursor = iter->cursor->right;                                              \
                                                                                             \
            while (iter->cursor->left != NULL)                                               \
                iter->cursor = iter->cursor->left;                                           \
                                                                                             \
            iter->index++;                                                                   \
                                                                                             \
            return true;                                                                     \
        }                                                                                    \
                                                                                             \
        while (true)                                                                         \
        {                                                                                    \
            if (iter->cursor->parent->left == iter->cursor)                                  \
            {                                                                                \
                iter->cursor = iter->cursor->parent;                                         \
                                                                                             \
                iter->index++;                                                               \
                                                                                             \
                return true;                                                                 \
            }                                                                                \
                                                                                             \
            iter->cursor = iter->cursor->parent;                                             \
        }                                                                                    \
    }                                                                                        \
                                                                                             \
    bool PFX##_iter_prev(SNAME##_iter *iter)                                                 \
    {                                                                                        \
        if (iter->start)                                                                     \
            return false;                                                                    \
                                                                                             \
        if (iter->cursor == iter->first)                                                     \
        {                                                                                    \
            iter->start = true;                                                              \
            return false;                                                                    \
        }                                                                                    \
                                                                                             \
        iter->end = PFX##_empty(iter->target);                                               \
                                                                                             \
        if (iter->cursor->left != NULL)                                                      \
        {                                                                                    \
            iter->cursor = iter->cursor->left;                                               \
                                                                                             \
            while (iter->cursor->right != NULL)                                              \
                iter->cursor = iter->cursor->right;                                          \
                                                                                             \
            iter->index--;                                                                   \
                                                                                             \
            return true;                                                                     \
        }                                                                                    \
                                                                                             \
        while (true)                                                                         \
        {                                                                                    \
            if (iter->cursor->parent->right == iter->cursor)                                 \
            {                                                                                \
                iter->cursor = iter->cursor->parent;                                         \
                                                                                             \
                iter->index--;                                                               \
                                                                                             \
                return true;                                                                 \
            }                                                                                \
                                                                                             \
            iter->cursor = iter->cursor->parent;                                             \
        }                                                                                    \
    }                                                                                        \
                                                                                             \
    /* Returns true only if the iterator moved */                                            \
    bool PFX##_iter_advance(SNAME##_iter *iter, size_t steps)                                \
    {                                                                                        \
        if (iter->end)                                                                       \
            return false;                                                                    \
                                                                                             \
        if (iter->cursor == iter->last)                                                      \
        {                                                                                    \
            iter->end = true;                                                                \
            return false;                                                                    \
        }                                                                                    \
                                                                                             \
        if (steps == 0 || iter->index + steps >= PFX##_count(iter->target))                  \
            return false;                                                                    \
                                                                                             \
        iter->index += steps;                                                                \
                                                                                             \
        for (size_t i = 0; i < steps; i++)                                                   \
            PFX##_iter_next(iter);                                                           \
                                                                                             \
        return true;                                                                         \
    }                                                                                        \
                                                                                             \
    /* Returns true only if the iterator moved */                                            \
    bool PFX##_iter_rewind(SNAME##_iter *iter, size_t steps)                                 \
    {                                                                                        \
        if (iter->start)                                                                     \
            return false;                                                                    \
                                                                                             \
        if (iter->cursor == iter->first)                                                     \
        {                                                                                    \
            iter->start = true;                                                              \
            return false;                                                                    \
        }                                                                                    \
                                                                                             \
        if (steps == 0 || iter->index < steps)                                               \
            return false;                                                                    \
                                                                                             \
        iter->index -= steps;                                                                \
                                                                                             \
        for (size_t i = 0; i < steps; i++)                                                   \
            PFX##_iter_prev(iter);                                                           \
                                                                                             \
        return true;                                                                         \
    }                                                                                        \
                                                                                             \
    /* Returns true only if the iterator was able to be positioned at the given index */     \
    bool PFX##_iter_go_to(SNAME##_iter *iter, size_t index)                                  \
    {                                                                                        \
        if (index >= PFX##_count(iter->target))                                              \
            return false;                                                                    \
                                                                                             \
        if (iter->index > index)                                                             \
            return PFX##_iter_rewind(iter, iter->index - index);                             \
        else if (iter->index < index)                                                        \
            return PFX##_iter_advance(iter, index - iter->index);                            \
                                                                                             \
        return true;                                                                         \
    }                                                                                        \
                                                                                             \
    K PFX##_iter_key(SNAME##_iter *iter)                                                     \
    {                                                                                        \
        if (PFX##_empty(iter->target))                                                       \
            return PFX##_impl_default_key();                                                 \
                                                                                             \
        return iter->cursor->key;                                                            \
    }                                                                                        \
                                                                                             \
    V PFX##_iter_value(SNAME##_iter *iter)                                                   \
    {                                                                                        \
        if (PFX##_empty(iter->target))                                                       \
            return PFX##_impl_default_value();                                               \
                                                                                             \
        return iter->cursor->value;                                                          \
    }                                                                                        \
                                                                                             \
    V *PFX##_iter_rvalue(SNAME##_iter *iter)                                                 \
    {                                                                                        \
        if (PFX##_empty(iter->target))                                                       \
            return NULL;                                                                     \
                                                                                             \
        return &(iter->cursor->value);                                                       \
    }                                                                                        \
                                                                                             \
    size_t PFX##_iter_index(SNAME##_iter *iter)                                              \
    {                                                                                        \
        return iter->index;                                                                  \
    }                                                                                        \
                                                                                             \
    static SNAME##_node *PFX##_impl_new_node(K key, V value)                                 \
    {                                                                                        \
        SNAME##_node *node = malloc(sizeof(SNAME##_node));                                   \
                                                                                             \
        if (!node)                                                                           \
            return NULL;                                                                     \
                                                                                             \
        node->key = key;                                                                     \
        node->value = value;                                                                 \
        node->right = NULL;                                                                  \
        node->left = NULL;                                                                   \
        node->parent = NULL;                                                                 \
        node->height = 0;                                                                    \
                                                                                             \
        return node;                                                                         \
    }                                                                                        \
                                                                                             \
    static SNAME##_node *PFX##_impl_get_node(SNAME *_map_, K key)                            \
    {                                                                                        \
        if (PFX##_empty(_map_))                                                              \
            return NULL;                                                                     \
                                                                                             \
        SNAME##_node *scan = _map_->root;                                                    \
                                                                                             \
        while (scan != NULL)                                                                 \
        {                                                                                    \
            if (_map_->cmp(scan->key, key) > 0)                                              \
                scan = scan->left;                                                           \
            else if (_map_->cmp(scan->key, key) < 0)                                         \
                scan = scan->right;                                                          \
            else                                                                             \
                return scan;                                                                 \
        }                                                                                    \
                                                                                             \
        return NULL;                                                                         \
    }                                                                                        \
                                                                                             \
    static unsigned char PFX##_impl_h(SNAME##_node *node)                                    \
    {                                                                                        \
        if (node == NULL)                                                                    \
            return 0;                                                                        \
                                                                                             \
        return node->height;                                                                 \
    }                                                                                        \
                                                                                             \
    static unsigned char PFX##_impl_hupdate(SNAME##_node *node)                              \
    {                                                                                        \
        if (node == NULL)                                                                    \
            return 0;                                                                        \
                                                                                             \
        unsigned char h_l = PFX##_impl_h(node->left);                                        \
        unsigned char h_r = PFX##_impl_h(node->right);                                       \
                                                                                             \
        return 1 + (h_l > h_r ? h_l : h_r);                                                  \
    }                                                                                        \
                                                                                             \
    static void PFX##_impl_rotate_right(SNAME##_node **Z)                                    \
    {                                                                                        \
        SNAME##_node *root = *Z;                                                             \
        SNAME##_node *new_root = root->left;                                                 \
                                                                                             \
        if (root->parent != NULL)                                                            \
        {                                                                                    \
            if (root->parent->left == root)                                                  \
                root->parent->left = new_root;                                               \
            else                                                                             \
                root->parent->right = new_root;                                              \
        }                                                                                    \
                                                                                             \
        new_root->parent = root->parent;                                                     \
                                                                                             \
        root->parent = new_root;                                                             \
        root->left = new_root->right;                                                        \
                                                                                             \
        if (root->left)                                                                      \
            root->left->parent = root;                                                       \
                                                                                             \
        new_root->right = root;                                                              \
                                                                                             \
        root->height = PFX##_impl_hupdate(root);                                             \
        new_root->height = PFX##_impl_hupdate(new_root);                                     \
                                                                                             \
        *Z = new_root;                                                                       \
    }                                                                                        \
                                                                                             \
    static void PFX##_impl_rotate_left(SNAME##_node **Z)                                     \
    {                                                                                        \
        SNAME##_node *root = *Z;                                                             \
        SNAME##_node *new_root = root->right;                                                \
                                                                                             \
        if (root->parent != NULL)                                                            \
        {                                                                                    \
            if (root->parent->right == root)                                                 \
                root->parent->right = new_root;                                              \
            else                                                                             \
                root->parent->left = new_root;                                               \
        }                                                                                    \
                                                                                             \
        new_root->parent = root->parent;                                                     \
                                                                                             \
        root->parent = new_root;                                                             \
        root->right = new_root->left;                                                        \
                                                                                             \
        if (root->right)                                                                     \
            root->right->parent = root;                                                      \
                                                                                             \
        new_root->left = root;                                                               \
                                                                                             \
        root->height = PFX##_impl_hupdate(root);                                             \
        new_root->height = PFX##_impl_hupdate(new_root);                                     \
                                                                                             \
        *Z = new_root;                                                                       \
    }                                                                                        \
                                                                                             \
    static void PFX##_impl_rebalance(SNAME *_map_, SNAME##_node *node)                       \
    {                                                                                        \
        SNAME##_node *scan = node, *child = NULL;                                            \
                                                                                             \
        int balance;                                                                         \
        bool is_root = false;                                                                \
                                                                                             \
        while (scan != NULL)                                                                 \
        {                                                                                    \
            if (scan->parent == NULL)                                                        \
                is_root = true;                                                              \
                                                                                             \
            scan->height = PFX##_impl_hupdate(scan);                                         \
            balance = PFX##_impl_h(scan->right) - PFX##_impl_h(scan->left);                  \
                                                                                             \
            if (balance >= 2)                                                                \
            {                                                                                \
                child = scan->right;                                                         \
                                                                                             \
                if (PFX##_impl_h(child->right) < PFX##_impl_h(child->left))                  \
                    PFX##_impl_rotate_right(&(scan->right));                                 \
                                                                                             \
                PFX##_impl_rotate_left(&scan);                                               \
            }                                                                                \
            else if (balance <= -2)                                                          \
            {                                                                                \
                child = scan->left;                                                          \
                                                                                             \
                if (PFX##_impl_h(child->left) < PFX##_impl_h(child->right))                  \
                    PFX##_impl_rotate_left(&(scan->left));                                   \
                                                                                             \
                PFX##_impl_rotate_right(&scan);                                              \
            }                                                                                \
                                                                                             \
            if (is_root)                                                                     \
            {                                                                                \
                _map_->root = scan;                                                          \
                is_root = false;                                                             \
            }                                                                                \
                                                                                             \
            scan = scan->parent;                                                             \
        }                                                                                    \
    }                                                                                        \
                                                                                             \
    static SNAME##_iter PFX##_impl_it_start(SNAME *_map_)                                    \
    {                                                                                        \
        SNAME##_iter iter;                                                                   \
                                                                                             \
        PFX##_iter_init(&iter, _map_);                                                       \
                                                                                             \
        return iter;                                                                         \
    }                                                                                        \
                                                                                             \
    static SNAME##_iter PFX##_impl_it_end(SNAME *_map_)                                      \
    {                                                                                        \
        SNAME##_iter iter;                                                                   \
                                                                                             \
        PFX##_iter_init(&iter, _map_);                                                       \
        PFX##_iter_to_end(&iter);                                                            \
                                                                                             \
        return iter;                                                                         \
    }

#endif /* CMC_TREEMAP_H */
