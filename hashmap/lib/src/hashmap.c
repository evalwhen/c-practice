#include "hashmap.h"
#include <assert.h>
// 通过线性探测（linear probing) 实现 hashmap

static int hash_code(MapKey key);
static int hash_value(HashMap m, MapKey key);
static int find_slot(HashMap m, int h, MapKey k);

HashMap new_hashmap() {
  HashMap m;

  // TODO: 或许这里应该使用指针数组。
  m._data = (MapEntry*) malloc(DEFAULT_CAPACITY * sizeof(MapEntry));

  if (m._data == NULL) {
    return NULL;
  }

  memset(m.data, NULL, DEFAULT_CAPACITY * sizeof(MapEntry*));

  m._capacity = DEFAULT_CAPACITY;
  // 使用 Multiply-Add-and-Divide 限制 key hash 值在 0 至 capacity 区间内均匀分布,减少碰撞。
  m._prime = get_next_prime_larger_than(capacity);
  m._rand_a = randint(0, m._prime);
  m._rand_b = randint(0, m._prime);
  m._size = 0;

  return m;
}

void add(HashMap m, MapKey k, MapValue v) {
  int j = find_slot(m, hash_value(k), k);

  // k 已经存在，更新其v
  if (j > 0) {
    m._data[j]->value = v;
  } else {
    MapEntry entry;
    entry.key = k;
    entry.value = v;

    m._data[-(j+1)] = entry;

    // TODO: 需要增大capacity, 如果 size / capacity 小于0.5
  }
}

bool get(HashMap m, MapKey k, MapValue* v) {
  int j = find_slot(m, hash_value(k), k);

  if (j < 0) {
    return false;
  } else {
    assert(m._data[j]->key == k);
    *v = m._data[j]->value;
    return true
  }
}


bool is_prime(int n) {

  for int i = 2; i < n; i++ {
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

static int array_index(HashMap m, MapKey key) {

  return ((m._rand_a * hash_code(key) + m._rand_b) % m._prime) % m._capacity;
}

static int find_slot(HashMap m, int h, MapKey k) {
  int j;
  j = h;

  int slot = -1;

  do {
    if (m._data[j] == NULL || m._data[j] == SENTINEL ) {
      if (slot == -1) {
        slot = j;
      }
      if (m._data[j] == NULL) {
        break;
      }
    } else {
      if (m._data[j]->key == k) {
        return j;
      }
    }

    j = (j+1) % m._capacity;

  } while(j != h);

  return -(slot + 1);
}
