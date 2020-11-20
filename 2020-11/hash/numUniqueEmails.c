// LeetCode Problem 929
// Runtime: 12 ms (67.74%)
// Memory Usage: 6.9 MB (83.87%)

#include <stdio.h>
#define MAX 96

typedef struct {
    unsigned long local, domain;
} emailhash;

unsigned long djb2(char *str) {
    unsigned long hash = 5381UL;
    char c;
    while (c = *str++) hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    return hash;
}

void resolve(char **s, emailhash *t, int n) {
    char l[MAX], d[MAX], *p;
    int x;
    for (int i = 0; i < n; i++) {
        p = s[i];
        x = 0;
        while (*p != '@' && *p != '+') {
            if (*p != '.') l[x++] = *p;
            p++;
        }
        l[x] = '\0';
        while (*(p++) != '@') continue;
        x = 0;
        while (d[x++] = *(++p)) continue;
        t[i].local = djb2(l);
        t[i].domain = djb2(d);
    }
}

int locateUnique(emailhash *u, emailhash *cmp, int c) {
    if (!c) return -1;
    for (int i = 0; i < c; i++) {
        if ((u[i].local == cmp->local) &&
            (u[i].domain == cmp->domain)) {
            return i;
        }
    }
    return -1;
}

int countUnique(emailhash *x, int n) {
    for (int i = 1; i < n; i++) {
        if ((locateUnique(x, x + i, i)) != -1) {
            x[i--] = x[--n];
        }
    }
    return n;
}

int numUniqueEmails(char **words, int wordsSize) {
    emailhash x[wordsSize];
    resolve(words, x, wordsSize);
    return countUnique(x, wordsSize);
}

int main(void) {
    char *testcase[100] = {"j+ezsorqlmc@rfpycgjuf.com", "j+k+ri+rigt.ad@rfpycgjuf.com", "hfmeqzk.isx+i@fiidmdrsu.com", "j+p+h+d+d+p+z.j.k.g@rfpycgjuf.com", "zygekdy.l.w+s@snh.owpyu.com", "j+m.l+ia+qdgv+w@rfpycgjuf.com", "r+hwbjwefkp@wcjaki.n.com", "zygekdy.l.w+d@snh.owpyu.com", "bizdm+sz.f.a.k@il.cjjlp.com", "hfmeqzk.isx+t@fiidmdrsu.com", "hfmeqzk.isx+i@fiidmdrsu.com", "bizdm+f+j+m.l.l@il.cjjlp.com", "zygekdy.l.w+g@snh.owpyu.com", "r+evgvxmksf@wcjaki.n.com", "hfmeqzk.isx+h@fiidmdrsu.com", "bizdm+lov+cy@il.cjjlp.com", "hfmeqzk.isx+o@fiidmdrsu.com", "bizdm+hs+qao@il.cjjlp.com", "r+v+z+rcuznrj@wcjaki.n.com", "j+r.kn+h.w.a.h+bh@rfpycgjuf.com", "hfmeqzk.isx+t@fiidmdrsu.com", "hfmeqzk.isx+a@fiidmdrsu.com", "zygekdy.l.w+o@snh.owpyu.com", "zygekdy.l.w+i@snh.owpyu.com", "r+vy.u.y+f.er+aw@wcjaki.n.com", "zygekdy.l.w+c@snh.owpyu.com", "bizdm+wztzg@il.cjjlp.com", "j+h.fwbsr+chp@rfpycgjuf.com", "zygekdy.l.w+s@snh.owpyu.com", "zygekdy.l.w+d@snh.owpyu.com", "bizdm+qq.o.q+p@il.cjjlp.com", "zygekdy.l.w+o@snh.owpyu.com", "j+c+zqbq+h.dyt@rfpycgjuf.com", "r+hl.b.i+fz.hz.t@wcjaki.n.com", "r+cbabpf.k+w+e@wcjaki.n.com"};
    printf("%d", numUniqueEmails(testcase, 35));  // result is 5
    return 0;
}
