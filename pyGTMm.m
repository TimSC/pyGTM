   w "^pyGTMm"
   q
set(ref,val) ;
   s @ref=val
   q
get(ref,val) ;
   s val=@ref
   q
kil(ref) ;
   k @ref
   q
tst(ref) ;
   i '$d(^d) s ^d=0
   s ^d=^d+1
   i '$d(^d(ref)) s ^d(ref)=0
   e  s ^d(ref)=1+^d(ref)
   q
sts(ref,val) ;
   i '$d(^d(ref)) s ^d(ref)=0
   s val=ref
   q
ord(ref,key,newKey) ; Order through a global
   s newKey=$o(@ref@(key))
   q




