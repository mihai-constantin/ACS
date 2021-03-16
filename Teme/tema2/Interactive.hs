import System.IO

import Control.Monad.State

import Bloxorz

import Levels

import Search

import Control.Concurrent

import qualified System.Process as SP

{-
    Setați workingOs la una dintre valorile 
    Windows, Linux, în funcție de sistemul 
    de operare pe care lucrați.
-}

workingOs :: Os
workingOs = Linux

data Os = Windows | Linux
    deriving (Show, Eq)

{-
    Primește ca parametru nivelul pe care să-l joace.
    În timpul execuției, introduceți direcția urmată 
    de enter.
-}

play :: Level -> IO Level
play = execStateT init_cli

init_cli = do
    lift cls
    lift $ hSetEcho stdin False

    x <- get
    lift $ putStr (show x)

    lift printInstructions
    loop_play

    lift $ hSetEcho stdin True
    lift cls

loop_play = do
    x <- get

    lift $ hSetEcho stdin False
    
    ch <- lift $ getLine

    
    lift cls

    case ch of
                "w" -> put (move North x)
                "s" -> put (move South x)
                "a" -> put (move West x)
                "d" -> put (move East x)
                "q" -> return()
                _ -> put x

    newX <- get
    lift $ putStr (show newX)

    lift printInstructions

    if ch /= "q" && (continueGame newX) then loop_play else return()

{-
    Primește ca parametru nivelul pe care să-l rezolve 
    și un Bool care va desemna dacă folosește sau nu euristica .
-}

visualize :: Level -> Bool -> IO [Level]
visualize level useHeuristic = execStateT loop_visualize
                                $ level :(map snd (solve level useHeuristic))

loop_visualize = do
    x <- get
    put (tail x)

    lift cls
    lift $ putStr (show (head x))
    lift $ threadDelay 500000
    if length x == 1 then return () else loop_visualize

cls = do
    case workingOs of
        Linux -> SP.system "clear"
        Windows -> SP.system "cls"

printInstructions = do
    putStr "Use w to move North\n\
                    \Use s to move South\n\
                    \Use a to move West\n\
                    \Use d to move East\n\
                    \Use q to exit...\n"