; This is a comment

(declare-var data int); 

(declare-thread one thread0)
(invoke-parameters one repeated 1 priority 1)
(end-thread one)
(declare-thread two thread1)
(invoke-parameters two repeated 1 priority 1)
(end-thread two)

(post-condition all (assert(= data 84)))
;(post-condition all (assert(= data 42)))

