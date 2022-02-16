#!/bin/bash

rm log*

 counter=1
 until [ $counter -gt 41 ]
 do
 echo $counter
     (time ./test1 < "./in/test$counter.in") 2>&1 | tee /dev/null | tail -2 | head -1 >> log-dinic
     (time ./test2 < "./in/test$counter.in") 2>&1 | tee /dev/null | tail -2 | head -1 >> log-edm
     (time ./test3 < "./in/test$counter.in") 2>&1 | tee /dev/null | tail -2 | head -1 >> log-grredy
     ((counter++))
 done

# counter=0
# until [ $counter -gt 52 ]
# do
#      if [[ $counter -gt 9 && $counter -lt 17 || $counter == 40 || $counter == 23 || $counter == 28 ]];
#      then   echo "skip"
#      else
#      ./sqrt < "./in/test$counter.in" >  "./out/test$counter-sqrt.out"
#      fi
#     ./segment < "./in/test$counter.in" # >  "./out/test$counter-seg.out"
#      ./sparse < "./in/test$counter.in" >  "./out/test$counter.out"
#     ((counter++))
# done

# counter=0
# until [ $counter -gt 52 ]
# do
# # diff "./out/test$counter-sqrt.out"  "./out/test$counter.out"
# # diff "./out/test$counter-seg.out"  "./out/test$counter.out"
# ((counter++))
# done
