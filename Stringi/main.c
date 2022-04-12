#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// consider chars from [FIRST_CHAR, LAST_CHAR)
#define FIRST_CHAR 33
#define LAST_CHAR 127
#define MAX_CHARS (LAST_CHAR - FIRST_CHAR)
#define MAX_DIGRAMS (LAST_CHAR - FIRST_CHAR) * (LAST_CHAR - FIRST_CHAR)

#define NEWLINE '\n'
#define IN_WORD 1

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2

int count[MAX_DIGRAMS] = {0};

// function to be used as comparator to qsort (compares counters and thes sorts
// alphabetically when equal)
int cmp(const void *a, const void *b) {
    int va = *(int *) a;
    int vb = *(int *) b;
    if (count[va] == count[vb]) return va - vb; // sort alphabetically if counts equal
    return count[vb] - count[va];
}

// function to be used as comparator to qsort for digrams (compares counters and
// thes sorts alphabetically when equal)
int cmp_di(const void *a, const void *b) {
    int va = *(int *) a;
    int vb = *(int *) b;
    // sort according to second char if counts and the first char equal
    if (count[va] == count[vb] && va / MAX_CHARS == vb / MAX_CHARS) return va % MAX_CHARS - vb % MAX_CHARS;
    // sort according to first char if counts equal
    if (count[va] == count[vb]) return va / MAX_CHARS - vb / MAX_CHARS;
    return count[vb] - count[va];
}

// count number of lines (nl), number of words (nw) and number of characters
// (nc) in the text read from stdin
void wc(int *nl, int *nw, int *nc) {
    int nl_tmp = 0;
    int nw_tmp = 0;
    int nc_tmp = 0;
    char line[128];
    int k;
    while (fgets(line, 128, stdin)) {
        nl_tmp += 1;
        int i = 0;
        int flag = 0;
        while (line[i] != NEWLINE) {
            flag = 0;
            k = (int) line[i];
            nc_tmp += 1;
            if (k >= FIRST_CHAR && k <= LAST_CHAR)
                flag = 1;
            if (i > 0)
                if ((line[i - 1] >= FIRST_CHAR && line[i - 1] <= LAST_CHAR) &&
                    (line[i] > LAST_CHAR || line[i] < FIRST_CHAR))
                    nw_tmp++;
            i++;
        }
        if (flag == 1)nw_tmp++;

    }
    *nl = nl_tmp;
    *nw = nw_tmp;
    nc_tmp += nl_tmp;
    *nc = nc_tmp;

}

// count how many times each character from [FIRST_CHAR, LAST_CHAR) occurs
// in the text read from stdin. Sort chars according to their respective
// cardinalities (decreasing order). Set n_char and cnt to the char_no - th char
// in the sorted list and its cardinality respectively
void char_count(int char_no, int *n_char, int *cnt) {
    char line[128];
    int tab[MAX_CHARS];
    int h = 0;
    for (int i = 0; i < MAX_CHARS; i++) tab[i] = 0;
    while (fgets(line, 128, stdin)) {
        int i = 0;
        while (line[i] != NEWLINE) {
            if ((int) line[i] >= FIRST_CHAR && (int) line[i] <= LAST_CHAR)
                tab[(int) line[i] - FIRST_CHAR]++;
            i++;
        }
    }
    for (int i = 0; i < MAX_CHARS; i++) {
        h = 0;
        for (int j = 0; j < MAX_CHARS; j++) {
            if (i != j) {
                if (tab[i] < tab[j])h++;
                if (tab[i] == tab[j]) {
                    if (i > j)h++;
                }
            }

        }
        if (h == char_no - 1) {
            *n_char = (char) (i + FIRST_CHAR);
            *cnt = tab[i];
            break;
        }
    }

}

// count how many times each digram (a pair of characters, from [FIRST_CHAR,
// LAST_CHAR) each) occurs in the text read from stdin. Sort digrams according
// to their respective cardinalities (decreasing order). Set digram[0] and
// digram[1] to the first and the second char in the digram_no - th digram_char
// in the sorted list. Set digram[2] to its cardinality.
void digram_count(int digram_no, int digram[]) {
    char line[128];
    int h = 0;
    int tab[MAX_CHARS][MAX_CHARS];
    for (int i = 0; i < MAX_CHARS; i++)
        for (int j = 0; j < MAX_CHARS; j++)tab[i][j] = 0;

    while (fgets(line, 128, stdin)) {
        int i = 1;
        if (line[0] != NEWLINE) {
            while (line[i] != NEWLINE) {
                if ((int) line[i] >= FIRST_CHAR && (int) line[i] <= LAST_CHAR) {
                    if ((int) line[i - 1] >= FIRST_CHAR && (int) line[i - 1] <= LAST_CHAR) {
                        tab[(int) line[i - 1] - FIRST_CHAR][(int) line[i] - FIRST_CHAR]++;
                    }
                }
                i++;
            }

        }
    }
    for (int i = 0; i < MAX_CHARS; i++) {
        for (int j = 0; j < MAX_CHARS; j++) {
            h = 0;
            for (int k = 0; k < MAX_CHARS; k++) {
                for (int l = 0; l < MAX_CHARS; l++) {
                    if (tab[i][j] < tab[k][l])h++;
                    if (tab[i][j] == tab[k][l]) {
                        if (k < i)h++;
                        else if (k == i && l < j)h++;
                    }


                }
            }
            if (h == digram_no - 1) {
                digram[0] = i + FIRST_CHAR;
                digram[1] = j + FIRST_CHAR;
                digram[2] = tab[i][j];
            }
        }
    }


}

// Count block and line comments in the text read from stdin. Set
// line_comment_counter and block_comment_counter accordingly
void find_comments(int *line_comment_counter, int *block_comment_counter) {
    int l = 0, b = 0, st = 0, i;
    char line[128];
    while (fgets(line, 128, stdin)) {
        i = 1;
        if (line[0] != NEWLINE) {
            while (line[i] != NEWLINE) {
                if (st == 1) {
                    if (line[i - 1] == '*' && line[i] == '/') {
                        st = 0;
                        b++;
                    }
                }
                if (st == 0) {
                    if (line[i] == '/' && line[i - 1] == '/') {
                        l++;
                        line[i + 1] = NEWLINE;
                    }
                    if (line[i - 1] == '/' && line[i] == '*') {
                        st = 1;
                        if (line[i + 1] != NEWLINE)i++;
                    }
                }
                i++;
            }
        }
    }
    *line_comment_counter = l;
    *block_comment_counter = b;


}


#define MAX_LINE 128

int read_line() {
    char line[MAX_LINE];
    int n;

    fgets(line, MAX_LINE, stdin); // to get the whole line
    sscanf(line, "%d", &n);
    return n;
}

int main(void) {
    int to_do;
    int nl, nw, nc, char_no, n_char, cnt;
    int line_comment_counter, block_comment_counter;
    int digram[3];

    to_do = read_line();
    switch (to_do) {
        case 1: // wc()
            wc(&nl, &nw, &nc);
            printf("%d %d %d\n", nl, nw, nc);
            break;
        case 2: // char_count()
            char_no = read_line();
            char_count(char_no, &n_char, &cnt);
            printf("%c %d\n", n_char, cnt);
            break;
        case 3: // digram_count()
            char_no = read_line();
            digram_count(char_no, digram);
            int i = printf("%c%c %d\n", digram[0], digram[1], digram[2]);
            break;
        case 4:
            find_comments(&line_comment_counter, &block_comment_counter);
            printf("%d %d\n", block_comment_counter, line_comment_counter);
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    return 0;
}