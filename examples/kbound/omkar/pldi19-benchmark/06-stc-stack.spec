; This is a comment

(declare-var result1 int); 
(declare-var result2 int); 
(declare-var result3 int); 
(declare-var result4 int); 
(declare-var result5 int); 
(declare-var result6 int); 
(declare-var result7 int); 
(declare-var result8 int); 
(declare-var result9 int); 

(declare-thread one thread0)
(invoke-parameters one repeated 1 priority 1)
(end-thread one)

(declare-thread two thread1)
(invoke-parameters two repeated 1 priority 1)
(end-thread two)

(declare-thread three thread2)
(invoke-parameters three repeated 1 priority 1)
(end-thread three)

(post-condition all (assert (not (and (= result1 0) (= result2 0) (= result3 0) (= result4 0) (= result5 0) (= result6 0) (= result7 0) (= result8 0) (= result9 0) ) )))
;

