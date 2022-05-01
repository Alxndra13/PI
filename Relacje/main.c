#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 1000
#define MAX_RANGE 1000

typedef struct {
    int first;
    int second;
} pair;

int cmpfunc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int cmpf(const void* p1, const void* p2) {
    if ((*(pair*)p1).first == (*(pair*)p2).first)
        return (*(pair*)p1).second - (*(pair*)p2).second;
    return (*(pair*)p1).first - (*(pair*)p2).first;
}

int cmp(pair p1, pair p2) {
    if (p1.first == p2.first)
        return p1.second - p2.second;
    return p1.first - p2.first;
}

// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(pair* relation, int size) {
    int X[size << 1];
    for (int i = 0; i < size; ++i) {
        X[i] = relation[i].first;
        X[size + i] = relation[i].second;
    }
    for (int i = 0; i < (size << 1); ++i) {
        for (int j = 0; j < (size << 1); ++j) {
            int x = X[i], y = X[j], rel = 0;
            for (int k = 0; k < size; ++k) {
                if ((relation[k].first == x && relation[k].second == y) ||
                    (relation[k].first == y && relation[k].second == x)) {
                    rel = 1;
                }
            }
            if (!rel)
                return 0;
        }
    }
    return 1;
}

// Add pair to existing relation if not already there
int add_relation(pair* relation, int size, pair current) {
    for (int i = 0; i < size; ++i) {
        if (relation[i].first == current.first &&
            relation[i].second == current.second) {
            return size;
        }
    }
    relation[size] = current;
    return size + 1;
}

// Case 1:
// The relation R is reflexive if xRx for every x in X
int is_reflexive(pair* relation, int size) {
    for (int i = 0; i < size; ++i) {
        int lhs = relation[i].first, lhs_ok = 0;
        int rhs = relation[i].second, rhs_ok = 0;
        for (int j = 0; j < size; ++j) {
            if (relation[j].first == lhs && relation[j].second == lhs)
                lhs_ok = 1;
            if (relation[j].first == rhs && relation[j].second == rhs)
                rhs_ok = 1;
            if (lhs_ok && rhs_ok)
                break;
        }
        if (!lhs_ok || !rhs_ok)
            return 0;
    }
    return 1;
}
// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(pair* relation, int size) {
    for (int i = 0; i < size; ++i) {
        if (relation[i].first == relation[i].second) {
            return 0;
        }
    }
    return 1;
}
// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(pair* relation, int size) {
    for (int i = 0; i < size; ++i) {
        int lhs = relation[i].first;
        int rhs = relation[i].second;
        int ok = 0;
        for (int j = 0; j < size; ++j) {
            if (relation[j].first == rhs && relation[j].second == lhs) {
                ok = 1;
                break;
            }
        }
        if (!ok)
            return 0;
    }
    return 1;
}
// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(pair* relation, int size) {
    for (int i = 0; i < size; ++i) {
        int lhs = relation[i].first;
        int rhs = relation[i].second;
        if (lhs == rhs)
            continue;
        for (int j = 0; j < size; ++j) {
            if (relation[j].first == rhs && relation[j].second == lhs)
                return 0;
        }
    }
    return 1;
}
// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(pair* relation, int size) {
    for (int i = 0; i < size; ++i) {
        int lhs = relation[i].first;
        int rhs = relation[i].second;
        for (int j = 0; j < size; ++j) {
            if (relation[j].first == rhs && relation[j].second == lhs)
                return 0;
        }
    }
    return 1;
}
// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(pair* relation, int size) {
    for (int i = 0; i < size; ++i) {
        int x = relation[i].first;
        int y = relation[i].second;
        int match = 0;
        for (int j = 0; j < size; ++j) {
            if (relation[j].first == y) {
                int z = relation[j].second;
                for (int k = 0; k < size; ++k) {
                    if (relation[k].first == x && relation[k].second == z) {
                        match = 1;
                    }
                }
                if (!match)
                    return 0;
            }
        }
    }
    return 1;
}

// Case 2:
// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(pair* relation, int size) {
    if (!is_reflexive(relation, size))
        return 0;
    if (!is_antisymmetric(relation, size))
        return 0;
    if (!is_transitive(relation, size))
        return 0;
    return 1;
}
// A total order relation is a partial order relation that is connected
int is_total_order(pair* relation, int size) {
    if (!is_partial_order(relation, size))
        return 0;
    if (!is_connected(relation, size))
        return 0;
    return 1;
}

int in_relation(pair* relation, int size, int x, int y) {
    for (int i = 0; i < size; ++i) {
        if (relation[i].first == x && relation[i].second == y)
            return 1;
    }
    return 0;
}

int find_max_elements(pair* relation, int size, int* max_elements) {
    int X[size << 1];
    for (int i = 0; i < size; ++i) {
        X[i] = relation[i].first;
        X[size + i] = relation[i].second;
    }
    int iter = 0;
    for (int i = 0; i < (size << 1); ++i) {
        int possible_max_element = X[i];
        int possible = 1;
        for (int j = 0; j < (size << 1); ++j) {
            if (X[j] != possible_max_element &&
                in_relation(relation, size, possible_max_element, X[j])) {
                possible = 0;
                break;
            }
        }
        if (possible) {
            int insert = 1;
            for (int ii = 0; ii < iter; ++ii) {
                if (max_elements[ii] == possible_max_element) {
                    insert = 0;
                    break;
                }
            }
            if (insert) {
                max_elements[iter] = possible_max_element;
                ++iter;
            }
        }
    }
    qsort(max_elements, iter, sizeof(int), cmpfunc);
    return iter;
}

int find_min_elements(pair* relation, int size, int* min_elements) {
    int X[size << 1];
    for (int i = 0; i < size; ++i) {
        X[i] = relation[i].first;
        X[size + i] = relation[i].second;
    }
    int iter = 0;
    for (int i = 0; i < (size << 1); ++i) {
        int possible_min_element = X[i];
        int possible = 1;
        for (int j = 0; j < (size << 1); ++j) {
            if (X[j] != possible_min_element &&
                in_relation(relation, size, X[j], possible_min_element)) {
                possible = 0;
                break;
            }
        }
        if (possible) {
            int insert = 1;
            for (int ii = 0; ii < iter; ++ii) {
                if (min_elements[ii] == possible_min_element) {
                    insert = 0;
                    break;
                }
            }
            if (insert) {
                min_elements[iter] = possible_min_element;
                ++iter;
            }
        }
    }
    qsort(min_elements, iter, sizeof(int), cmpfunc);
    return iter;
}
int get_domain(pair* relation, int size, int* domain) {
    int X[size << 1];
    for (int i = 0; i < size; ++i) {
        X[i] = relation[i].first;
        X[size + i] = relation[i].second;
    }
    qsort(X, (size << 1), sizeof(int), cmpfunc);
    domain[0] = X[0];
    int iter = 1;
    for (int i = 1; i < (size << 1); ++i) {
        if (X[i] != X[i - 1]) {
            domain[iter] = X[i];
            ++iter;
        }
    }
    return iter;
}

// Case 3:
int composition(pair* relation1,
                int size1,
                pair* relation2,
                int size2,
                pair* comp_relation) {
    pair relation[MAX_REL_SIZE];
    int iter = 0;
    for (int i = 0; i < size1; ++i) {
        for (int j = 0; j < size2; ++j) {
            if (relation2[j].first == relation1[i].second) {
                pair p;
                p.first = relation1[i].first;
                p.second = relation2[j].second;
                relation[iter] = p;
                ++iter;
            }
        }
    }
    qsort(relation, iter, sizeof(pair), cmpf);
    int res = 1;
    for (int i = 1; i < iter; ++i) {
        if (relation[i].first != relation[i - 1].first ||
            relation[i].second != relation[i - 1].second) {
            ++res;
        }
    }
    return res;
}

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair* relation) {
    int size = 0, n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        pair current;
        scanf("%d%d", &current.first, &current.second);
        size = add_relation(relation, size, current);
    }
    return size;
}

void print_int_array(int* array, int n) {
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(void) {
    int to_do;
    pair relation[MAX_REL_SIZE];
    pair relation_2[MAX_REL_SIZE];
    pair comp_relation[MAX_REL_SIZE];
    int domain[MAX_REL_SIZE];

    scanf("%d", &to_do);
    int size = read_relation(relation);
    int ordered, size_2, n_domain;

    switch (to_do) {
        case 1:
            printf("%d ", is_reflexive(relation, size));
            printf("%d ", is_irreflexive(relation, size));
            printf("%d ", is_symmetric(relation, size));
            printf("%d ", is_antisymmetric(relation, size));
            printf("%d ", is_asymmetric(relation, size));
            printf("%d\n", is_transitive(relation, size));
            break;
        case 2:
            ordered = is_partial_order(relation, size);
            n_domain = get_domain(relation, size, domain);
            printf("%d %d\n", ordered, is_total_order(relation, size));
            print_int_array(domain, n_domain);
            if (!ordered)
                break;
            int max_elements[MAX_REL_SIZE];
            int min_elements[MAX_REL_SIZE];
            int no_max_elements = find_max_elements(relation, size, max_elements);
            int no_min_elements = find_min_elements(relation, size, min_elements);
            print_int_array(max_elements, no_max_elements);
            print_int_array(min_elements, no_min_elements);
            break;
        case 3:
            size_2 = read_relation(relation_2);
            printf("%d\n",
                   composition(relation, size, relation_2, size_2, comp_relation));
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    return 0;
}