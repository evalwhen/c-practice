#include "hashmap.h"
#include <assert.h>
#include <string.h>
// 通过线性探测（linear probing) 实现 hashmap

const MapEntry SENTINEL = {~0, ~0};
const MapEntry NULL_ENTRY = {0, 0};

static int hash_code(MapKey key);
static int hash_value(HashMap m, MapKey key);
static int find_slot(HashMap m, int h, MapKey k);
static bool is_equal_entry(MapEntry a, MapEntry b);
static void resize(HashMap m);

HashMap new_hashmap() {
  HashMap m;

  // TODO: 或许这里应该使用指针数组。
  m = (HashMap ) malloc(sizeof(struct _hashMap));
  if (m == NULL) {
    return NULL;
  }

  m->_data = (MapEntry*) malloc(DEFAULT_CAPACITY * sizeof(MapEntry));

  if (m->_data == NULL) {
    return NULL;
  }

  memset(m->_data, 0, DEFAULT_CAPACITY * sizeof(MapEntry*));

  m->_capacity = DEFAULT_CAPACITY;
  // 使用 Multiply-Add-and-Divide 限制 key hash 值在 0 至 capacity 区间内均匀分布,减少碰撞。
  m->_prime = get_next_prime_larger_than(m->_capacity);
  m->_rand_a = randint(0, m->_prime);
  m->_rand_b = randint(0, m->_prime);
  m->_size = 0;

  return m;
}

void destruct_hashmap(HashMap h) {
  if (h == NULL) {
    return;
  } else {
    if (h->_data != NULL) {
      free(h->_data);
    }
    free(h);
  }
}

size_t entry_size(HashMap m) {
  return m->_size;
}

void add(HashMap m, MapKey k, MapValue v) {
  int j = find_slot(m, hash_value(m, k), k);

  // k 已经存在，更新其v
  if (j > 0) {
    m->_data[j].value = v;
  } else {
    MapEntry entry;
    entry.key = k;
    entry.value = v;

    m->_data[-(j+1)] = entry;
    m->_size += 1;

    // 增大capacity, 如果 size / capacity 小于0.5
    if (m->_size > (m->_capacity / 2)) {
      resize(m);
    }
  }
}

MapValue get(HashMap m, MapKey k) {
  int j = find_slot(m, hash_value(m, k), k);

  if (j < 0) {
    return 0;
  } else {
    assert(m->_data[j].key == k);
    return m->_data[j].value;
  }
}

bool exists(HashMap m, MapKey k) {
  int j = find_slot(m, hash_value(m, k), k);

  if (j < 0) {
    return false;
  } else {

    return true;
  }
}

bool remove_key(HashMap m, MapKey k) {

  int j = find_slot(m, hash_value(m, k), k);

  if (j < 0) {

    return false;
  } else {

    m->_data[j] = SENTINEL;
    m->_size -= 1;

    return true;
  }
}



bool is_prime(int n) {

  for (int i = 2; i < n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

int get_next_prime_larger_than(int n) {
  while(++n) {
    if (is_prime(n)) {
      return n;
    }
  }

  return n+1;
}

uint32_t randint (uint32_t a, uint32_t b)
{
  uint32_t range;
  uint32_t r, max;

  /*
   * We want a number in the range a..b.
   */
  range = b - a + 1;

  /*
   * Discard top random numbers for uniform distribution in this range, by
   * removing the remainder.
   */
  max = RAND_MAX;
  if (range < RAND_MAX) {
    max -= (RAND_MAX % range);
  }

  do {
    r = rand();
  } while (r >= max);


  // if (RAND_MAX * RAND_MAX < INT_MAX)

  //    if (b > RAND_MAX) {
  //	r += RAND_MAX * rand();
  //    }

  r %= range;

  return (a + r);
}

static int hash_code(MapKey key) {

  return key;
}

static int hash_value(HashMap m, MapKey key) {

  return ((m->_rand_a * hash_code(key) + m->_rand_b) % m->_prime) % m->_capacity;
}

/*
  线性探测通过将冲突的 key 存放(put)在相邻连续的区域来方便查找(get)。

  也就是说,key是如何放入的就如何取出。

  查找一个key是否存在，只需要在这段连续的区域上遍历直到连续性结束（找到一个 NULL)。

  删除key的操作不能简单的将kye占据的位置置为 NULL, 这会破坏连续性,导致其后的元素找不到。
  因此可以用一个哨兵值来作为标记，在遍历时跳过该位置。但要将其作为可用存储空间。
 */
static int find_slot(HashMap m, int h, MapKey k) {
  int j;
  j = h;

  int slot = -1;

  do {
    if (is_equal_entry(m->_data[j], NULL_ENTRY) || is_equal_entry(m->_data[j], SENTINEL)) {
      if (slot == -1) {
        slot = j;
      }
      if (is_equal_entry(m->_data[j], NULL_ENTRY)) {
        break;
      }
    } else {
      if (m->_data[j].key == k) {
        return j;
      }
    }

    j = (j+1) % m->_capacity;

  } while(j != h);

  return -(slot + 1);
}

static bool is_equal_entry(MapEntry a, MapEntry b) {
  return (a.key == b.key && a.value == b.value);
}


static void resize(HashMap m) {

  MapEntry* data;

  data = (MapEntry* ) malloc(2 * m->_capacity * sizeof(MapEntry));
  if (NULL == data) {
    return;
  }

  memmove(data, m->_data, m->_capacity * sizeof(MapEntry));

  m->_capacity = 2 * m->_capacity;
  m->_data = data;

  return;
}
