          q
     (n,r,c,d,e)
      {int a=~-
       (1<<n)&
      ~(c|d|e),
    b,t=1;if(r-n)
      for(--t;b
        =a&-a
        ;a&=~
        b)t+=
        q(n,r
        +1,c|
       b,(d|b)
      >>1,(e|b)
    <<1);return t
   ;}main(){printf
("%d",q(8,0,0,0,0));}
