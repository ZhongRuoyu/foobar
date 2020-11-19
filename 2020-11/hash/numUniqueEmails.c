// LeetCode Problem 929
// Runtime 8ms (96.77%)
// Memory Usage 6.8 MB (96.77%)

#include <stdio.h>

unsigned long getHash(char *str) {
    unsigned long hash = 5381UL;
    while (*str != '@' && *str != '+') {
        if (*str != '.') hash = ((hash << 5) + hash) + *str;
        str++;
    }
    while (*str != '@') str++;
    while (*str) {
        hash = ((hash << 5) + hash) + *(str++);
    }
    return hash;
}  // djb2 hash (for unique addresses)

int locateUnique(unsigned long *list, unsigned long *cmp, int c) {
    if (!c) return -1;
    for (int i = 0; i < c; i++) {
        if (list[i] == *cmp) {
            return i;
        }
    }
    return -1;
}

int countUnique(unsigned long *x, int c) {
    for (int i = 1; i < c; i++) {
        if ((locateUnique(x, x + i, i)) != -1) {
            x[i--] = x[--c];
        }
    }
    return c;
}

int numUniqueEmails(char **words, int wordsSize) {
    unsigned long hash[wordsSize];
    for (int i = 0; i < wordsSize; i++) {
        hash[i] = getHash(words[i]);
    }
    return countUnique(hash, wordsSize);
}

int main(void) {
    char *testcase[100] = {"j+ezsorqlmc@rfpycgjuf.com", "j+k+ri+rigt.ad@rfpycgjuf.com", "hfmeqzk.isx+i@fiidmdrsu.com", "j+p+h+d+d+p+z.j.k.g@rfpycgjuf.com", "zygekdy.l.w+s@snh.owpyu.com", "j+m.l+ia+qdgv+w@rfpycgjuf.com", "r+hwbjwefkp@wcjaki.n.com", "zygekdy.l.w+d@snh.owpyu.com", "bizdm+sz.f.a.k@il.cjjlp.com", "hfmeqzk.isx+t@fiidmdrsu.com", "hfmeqzk.isx+i@fiidmdrsu.com", "bizdm+f+j+m.l.l@il.cjjlp.com", "zygekdy.l.w+g@snh.owpyu.com", "r+evgvxmksf@wcjaki.n.com", "hfmeqzk.isx+h@fiidmdrsu.com", "bizdm+lov+cy@il.cjjlp.com", "hfmeqzk.isx+o@fiidmdrsu.com", "bizdm+hs+qao@il.cjjlp.com", "r+v+z+rcuznrj@wcjaki.n.com", "j+r.kn+h.w.a.h+bh@rfpycgjuf.com", "hfmeqzk.isx+t@fiidmdrsu.com", "hfmeqzk.isx+a@fiidmdrsu.com", "zygekdy.l.w+o@snh.owpyu.com", "zygekdy.l.w+i@snh.owpyu.com", "r+vy.u.y+f.er+aw@wcjaki.n.com", "zygekdy.l.w+c@snh.owpyu.com", "bizdm+wztzg@il.cjjlp.com", "j+h.fwbsr+chp@rfpycgjuf.com", "zygekdy.l.w+s@snh.owpyu.com", "zygekdy.l.w+d@snh.owpyu.com", "bizdm+qq.o.q+p@il.cjjlp.com", "zygekdy.l.w+o@snh.owpyu.com", "j+c+zqbq+h.dyt@rfpycgjuf.com", "r+hl.b.i+fz.hz.t@wcjaki.n.com", "r+cbabpf.k+w+e@wcjaki.n.com"};
    printf("%d", numUniqueEmails(testcase, 35));  // result is 5
    return 0;
}
