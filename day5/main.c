#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1024
#define CONST_MIN(a,b) ((a)<(b)?(a):(b))
#define CONST_MAX(a,b) ((a)>(b)?(a):(b))

typedef struct range {
    long a, b;
} range;

bool overlaps(range r1, range r2) {
    if (r2.a >= r1.a && r2.a <= r1.b)
        return true;
    if (r2.b >= r1.a && r2.b <= r1.b)
        return true;
    if (r1.a >= r2.a && r1.a <= r2.b)
        return true;
    if (r1.b >= r2.a && r1.b <= r2.b)
        return true;
    return false;
}

int exists(range r1, range *ranges, int length) {
    int n = 0;
    for (int i = 0; i < length; ++i) {
        if (r1.a == ranges[i].a && r1.b == ranges[i].b)
            n++;
    }
    return n;
}

range inner(range r1, range r2) {
    return (range){CONST_MIN(r1.a, r2.a),CONST_MAX(r1.b, r2.b)};
}

int main(void) {
    FILE *input = fopen("input", "r");
    char buf[MAX_LEN];
    int i = 0, j = 0, n = 0, m = 0, fresh = 0, new_ranges_nbr = 0;
    while (fgets(buf,MAX_LEN, input) && buf[0] != '\n')
        n++;
    while (fgets(buf,MAX_LEN, input))
        m++;
    range *ranges = calloc(n, sizeof(range));
    range *new_ranges = calloc(n, sizeof(range));
    long *products = calloc(m, sizeof(long));
    rewind(input);
    while (fgets(buf,MAX_LEN, input) && buf[0] != '\n') {
        const char *buf_range1 = strtok(buf, "-");
        const char *buf_range2 = strtok(nullptr, "-");
        ranges[i] = (range){strtol(buf_range1, nullptr, 10), strtol(buf_range2, nullptr, 10)};
        i++;
    }
    while (fgets(buf,MAX_LEN, input)) {
        products[j] = strtol(buf, nullptr, 10);
        j++;
    }
    for (int k = 0; k < m; k++) {
        bool flag = false;
        for (int l = 0; l < n; l++) {
            if (products[k] >= ranges[l].a && products[k] <= ranges[l].b) {
                flag = true;
                break;
            }
        }
        if (flag)
            fresh++;
        printf("%ld is %s\n", products[k], flag ? "Fresh" : "Spoiled");
    }
    printf("Nbr of Fresh products: %d\n", fresh);
    bool flag;
    do {
        flag = false;
        for (int l = 0; l < n; l++)
            for (int o = 0; o < n; o++) {
                if (overlaps(ranges[l], ranges[o]) && !(ranges[l].a == ranges[o].a && ranges[l].b == ranges[o].b)) {
                    if (l == o || ranges[o].a == 0)
                        continue;
                    range innersec = inner(ranges[l], ranges[o]);
                    ranges[o] = innersec;
                    ranges[l] = innersec;
                    flag = true;
                }
            }
    } while (flag);
    for (int u = 0; u < n; ++u) {
        if (!exists(ranges[u], new_ranges, new_ranges_nbr)) {
            new_ranges[new_ranges_nbr++] = ranges[u];
        }
    }
    long part2 = 0;
    for (int u = 0; u < new_ranges_nbr; ++u) {
        printf("[%ld --> %ld]. Occurs: %d\n", new_ranges[u].a, new_ranges[u].b, exists(new_ranges[u], new_ranges, new_ranges_nbr));
        part2+= new_ranges[u].b - new_ranges[u].a +1;
    }
    printf("Part2: %ld\n",part2);
    return 0;
}
