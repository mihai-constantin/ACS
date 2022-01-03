{-# OPTIONS_GHC -Wall #-}
{-# LANGUAGE MultiParamTypeClasses, FunctionalDependencies #-}

module ProblemState where

{-
    Expune funcțiile necesare construirii spațiului stărilor, pentru o problemă
    oarecare.

    `s` și `a` reprezintă tipurile stărilor, respectiv acțiunilor
    care transformă o stare în alta.

    Sintaxa `s -> a` din antetul clasei semnifică faptul că `s` îl determină
    în mod unic pe `a`.
-}

class ProblemState s a | s -> a where
    
    {-
        Pentru starea curentă, furnizează lista perechilor
        (acțiune, stare următoare).
    -}

    successors :: s -> [(a, s)]

    {-
        Întoarce `True` dacă starea curentă este finală.
    -}

    isGoal :: s -> Bool

    {-
        Întoarce o distanță estimată a stării curente față de starea finală.
        Cu cât distanța este mai mică, cu atât starea este mai preferabilă.
    -}

    heuristic :: s -> Int
    heuristic = const 0
