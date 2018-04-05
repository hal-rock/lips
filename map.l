(def map '((p x) 
  (if (eq? x '()) 
    '() 
    (cons (p (car x)) (map p (cdr x))))))

(def sum '((lst) 
  (if (eq? '() lst) 
    0 
    (+ (car lst) (sum (cdr lst))))))

(def n '((1 2 3) (4 5 6)))

(display (sum (map sum n)))
