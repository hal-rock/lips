(def pi 3)

(def ** '((x y) 
  (if (= y 0) 
    1 
    (* x (** x (- y 1))))))

(def circum '((r) 
  (* 2 r pi)))

(def area '((r) 
  (* pi (** r 2))))
