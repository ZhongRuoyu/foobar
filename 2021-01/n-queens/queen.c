          q
    (n,t,r,c,d,e)
      {if(r-n){
       int a=(
       (1<<n)-
       1)&(~(c
      |d|e)),b;
     while(a)b=a
       &-a,a&=
        a-1,t
        =q(n,
        t,r+1
        ,c|b,
        (d|b)
       >>1,(e|
       b)<<1);}
       else++t;
      return t;}
    main(){printf(
"%d",q(8,0,0,0,0,0));}
