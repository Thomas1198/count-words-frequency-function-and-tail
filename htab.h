/**
* @date 16. 4. 2018
* @file htab.h
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


struct htab_listitem {
    char *key;  /// dynamic string
    unsigned long data; /// times appeared
    struct htab_listitem *next;
};

typedef struct htab_t {
    size_t size;  ///act size
    size_t arr_size; ///max size
    struct htab_listitem *htab_arr[]; /// array with pointers on the items
} htab_t;


/**
 * @brief Hash function
 * @param str string to hash
 * @return hash
*/
unsigned int htab_hash_function(const char *str);


/**
 * @brief Initiate table
 * @param size size of table
 * @return pointer to table or NULL
*/
htab_t *htab_init(size_t size);


/**
 * @brief Creates new table and initialize with data of the second table (second table will remain empty, but allocated)
 * @param newsize size of the new table
 * @param t pointer to the table second
 * @return pointer to the new table
*/
htab_t *htab_move(unsigned long new_size, htab_t *t2);


/**
 * @param t pointer to the table
 * @returns actual size of the table
*/
size_t htab_size(htab_t *t);


/**
 * @param t pointer to the table
 * @returns max size of the table
*/
unsigned long htab_bucket_count(htab_t *t);


/**
 * @brief Finds item with key and if its not in the table it will add it
 * @param t pointer to the table
 * @param key key of the item to remove
 * @return pointer to the item or NULL
*/
struct htab_listitem *htab_lookup_add(htab_t *t, const char *key);


/**
 * @brief Finds item with key
 * @param t pointer to the table
 * @param key key of the item to remove
 * @return the found item or NULL
*/
struct htab_listitem *htab_find(htab_t *t, const char *key);


/**
 * @brief Calls function for every item
 * @param t pointer to the table
 * @param function pointer to the function
*/
void htab_foreach(htab_t *t, void (*function)(const char *, unsigned long));


/**
 * @brief Finds and removes item
 * @param t pointer to the table
 * @param key key of the item to remove
 * @return true if found false if not
*/
bool htab_remove(htab_t *t, const char *key);


/**
 * @brief Removes all items from the table
 * @param table pointer to the table
*/
void htab_clear(htab_t *t);


/**
 * @brief Destructor of the table
 * @param t pointer to the table
*/
void htab_free(htab_t *t);
