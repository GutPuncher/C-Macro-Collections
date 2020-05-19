/**
 * macro_collections.h
 *
 * Creation Date: 11/02/2019
 *
 * Authors:
 * Leonardo Vencovsky (https://github.com/LeoVen)
 *
 */

#ifndef CMC_MACRO_COLLECTIONS_H
#define CMC_MACRO_COLLECTIONS_H

#define CMC_CONCAT_(C, T) CMC_WRAPGEN_##C##_##T

#define CMC_CONCAT(C, T) CMC_CONCAT_(C, T)

#define CMC_COLLECTION_GENERATE(C, PFX, SNAME, K, V)    \
    CMC_COLLECTION_GENERATE_HEADER(C, PFX, SNAME, K, V) \
    CMC_COLLECTION_GENERATE_SOURCE(C, PFX, SNAME, K, V)

#define CMC_COLLECTION_GENERATE_HEADER(C, PFX, SNAME, K, V) \
    CMC_CONCAT(C, HEADER)(PFX, SNAME, K, V)

#define CMC_COLLECTION_GENERATE_SOURCE(C, PFX, SNAME, K, V) \
    CMC_CONCAT(C, SOURCE)(PFX, SNAME, K, V)

#include "cor/core.h"         /* Added in 17/03/2020 */
#include "cor/flags.h"        /* Added in 14/05/2020 */
#include "cor/hashtable.h"    /* Added in 17/03/2020 */

#include "cmc/bitset.h"       /* Added in 30/04/2020 */
#include "cmc/deque.h"        /* Added in 20/03/2019 */
#include "cmc/hashbidimap.h"  /* Added in 26/09/2019 */
#include "cmc/hashmap.h"      /* Added in 03/04/2019 */
#include "cmc/hashmultimap.h" /* Added in 26/04/2019 */
#include "cmc/hashmultiset.h" /* Added in 10/04/2019 */
#include "cmc/hashset.h"      /* Added in 01/04/2019 */
#include "cmc/heap.h"         /* Added in 25/03/2019 */
#include "cmc/intervalheap.h" /* Added in 06/07/2019 */
#include "cmc/linkedlist.h"   /* Added in 22/03/2019 */
#include "cmc/list.h"         /* Added in 12/02/2019 */
#include "cmc/queue.h"        /* Added in 15/02/2019 */
#include "cmc/sortedlist.h"   /* Added in 17/09/2019 */
#include "cmc/stack.h"        /* Added in 14/02/2019 */
#include "cmc/treemap.h"      /* Added in 28/03/2019 */
#include "cmc/treeset.h"      /* Added in 27/03/2019 */

#include "sac/queue.h"
#include "sac/stack.h"

#include "utl/assert.h"       /* Added in 27/06/2019 */
#include "utl/foreach.h"      /* Added in 25/02/2019 */
#include "utl/futils.h"       /* Added in 15/04/2020 */
#include "utl/log.h"          /* Added in 21/06/2019 */
#include "utl/mutex.h"        /* Added in 14/05/2020 */
#include "utl/test.h"         /* Added in 26/06/2019 */
#include "utl/thread.h"       /* Added in 14/05/2020 */
#include "utl/timer.h"        /* Added in 12/04/2019 */

#endif /* CMC_MACRO_COLLECTIONS_H */
