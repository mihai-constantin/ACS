{-# OPTIONS_GHC -Wall #-}
{-# LANGUAGE MultiParamTypeClasses #-}

module BloxorzTest where

import Levels

import TestPP

import Bloxorz

import Search

import ProblemState

import qualified Data.Map.Strict as M

import Control.Arrow (second, (&&&))

import Control.Monad (foldM, liftM2)

import Data.Function (on)

import Data.List

newtype Tree = Tree { getTree :: Int } 
    deriving (Eq, Ord, Show)

instance ProblemState Tree Int where
    successors (Tree n)
        | n == 2    = [(1, Tree 4), (2, Tree 6)]  -- 4 instead of 5 => cycle
        | otherwise = [(1, Tree $ 2 * n + 1), (2, Tree $ 2 * n + 2)]

    isGoal (Tree n) = n == 13

testAddObject :: TestPP ()
testAddObject = tests 1 5
  [ testString "emptyLevel (1, 1) (0, 0)" 1 (translateChars 
                                                "\n▓ \n\
                                                   \  \n") $
            show $ emptyLevel (1, 1) (0, 0)
  , testString "addTile 'H' (1, 1)\n\t\
            \emptyLevel (1, 1) (1, 0)" 1 (translateChars 
                                                "\n  \n\
                                                  \▓▒\n") $
            show $ addTile 'H' (1, 1) $
              emptyLevel (1, 1) (1, 0)
  , testString "addTile 'S' (1, 0)\n\t\
            \emptyLevel (1, 1) (0, 1)" 1 (translateChars 
                                                "\n ▓\n\
                                                   \= \n") $
            show $ addTile 'S' (1, 0) $
              emptyLevel (1, 1) (0, 1)
  , testString "addTile 'H' (1, 1)\n\t\
            \emptyLevel (1, 1) (1, 1)" 1 (translateChars 
                                                "\n  \n\
                                                   \ ▓\n") $
            show $ addTile 'H' (1, 1) $
              emptyLevel (1, 1) (1, 1)
  , testString "addTile 'W' (0, 0)\n\t\
            \emptyLevel (1, 1) (1, 1)" 1 (translateChars 
                                                "\n* \n\
                                                  \ ▓\n") $
            show $ addTile 'W' (0, 0) $
              emptyLevel (1, 1) (1, 1)
  , testString "addSwitch (1, 0) [(1, 1), (0, 1)]\n\t\
            \emptyLevel (1, 1) (0, 0)" 1 (translateChars 
                                                "\n▓ \n\
                                                  \± \n") $
            show $ addSwitch (1, 0) [(1, 1), (0, 1)] $
              emptyLevel (1, 1) (0, 0)
  , testString "addTile 'W' (0, 2)\n\t\
            \addTile 'H' (0, 0)\n\t\
            \addTile 'H' (1, 0)\n\t\
            \addTile 'H' (2, 0)\n\t\
            \addTile 'H' (3, 0)\n\t\
            \addTile 'S' (3, 1)\n\t\
            \addTile 'S' (3, 2)\n\t\
            \addTile 'H' (2, 2)\n\t\
            \addTile 'H' (1, 2)\n\t\
            \addSwitch (2, 1) [(1, 0), (2, 0)]\n\t\
            \emptyLevel (3, 2) (0, 0)" 1 (translateChars 
                                                "\n▓ *\n\
                                                  \▒ ▒\n\
                                                  \▒±▒\n\
                                                  \▒==\n") $
            show $
            addTile 'W' (0, 2) $
            addTile 'H' (0, 0) $
            addTile 'H' (1, 0) $
            addTile 'H' (2, 0) $
            addTile 'H' (3, 0) $
            addTile 'S' (3, 1) $
            addTile 'S' (3, 2) $
            addTile 'H' (2, 2) $
            addTile 'H' (1, 2) $
            addSwitch (2, 1) [(1, 0), (2, 0)] $
            emptyLevel (3, 2) (0, 0)
  ]

testShowLevels :: TestPP()
testShowLevels = tests 2 15
  [ testString "show level0" 1 (translateChars 
                              "\n         \n\
                                \         \n\
                                \  ▒▒▒▓▒▒*\n\
                                \         \n\
                                \         \n") $
            show level0
  , testString "show level1" 1 (translateChars 
                            "\n              \n\
                              \              \n\
                              \  ▒▒▒         \n\
                              \  ▒▓▒▒▒▒      \n\
                              \  ▒▒▒▒▒▒▒▒▒   \n\
                              \   ▒▒▒▒▒▒▒▒▒  \n\
                              \       ▒▒*▒▒  \n\
                              \        ▒▒▒   \n\
                              \              \n\
                              \              \n") $
            show level1
  , testString "show level2" 1 (translateChars 
                              "\n                    \n\
                                \                    \n\
                                \        ▒▒▒▒▒▒▒     \n\
                                \  ▒▒▒▒  ▒▒▒  ▒▒     \n\
                                \  ▒▒▒▒▒▒▒▒▒  ▒▒▒▒   \n\
                                \  ▒▓▒▒       ▒▒*▒   \n\
                                \  ▒▒▒▒       ▒▒▒▒   \n\
                                \              ▒▒▒   \n\
                                \                    \n\
                                \                    \n") $
            show level2
  , testString "show level3" 1 (translateChars 
                              "\n                   \n\
                                \                   \n\
                                \     =======       \n\
                                \     =======       \n\
                                \  ▒▒▒▒     ▒▒▒     \n\
                                \  ▒▒▒       ▒▒     \n\
                                \  ▒▒▒       ▒▒     \n\
                                \  ▒▓▒  ▒▒▒▒=====   \n\
                                \  ▒▒▒  ▒▒▒▒=====   \n\
                                \       ▒*▒  ==▒=   \n\
                                \       ▒▒▒  ====   \n\
                                \                   \n\
                                \                   \n") $
            show level3
  , testString "show level4" 1 (translateChars 
                              "\n                \n\
                                \                \n\
                                \   ▒▒▒▒  ▒▒▒▒   \n\
                                \   ▓▒▒▒  ▒*▒▒   \n\
                                \   ▒▒▒▒  ▒▒▒▒   \n\
                                \     ▒▒▒==▒▒▒   \n\
                                \        ▒▒▒▒    \n\
                                \                \n\
                                \                \n\
                                \                \n") $
            show level4
  , testString "show level5" 1 (translateChars 
                              "\n                   \n\
                                \                   \n\
                                \             ▒▒▒▒  \n\
                                \   ▒▒▒▒  ▒±▒▒▒▒▓▒  \n\
                                \   ▒▒▒▒       ▒▒▒  \n\
                                \   ▒▒▒▒            \n\
                                \   ▒▒▒▒            \n\
                                \     ▒▒▒±▒  ▒▒▒    \n\
                                \            ▒▒▒▒±  \n\
                                \  ▒▒▒       ▒▒▒▒▒  \n\
                                \  ▒*▒▒▒  ▒▒▒▒▒▒    \n\
                                \  ▒▒▒▒             \n\
                                \                   \n\
                                \                   \n\
                                \                   \n") $
            show level5
  , testString "show level6" 1 (translateChars 
                              "\n                \n\
                                \                \n\
                                \  *▒▒▒      ▓   \n\
                                \     ▒     ▒▒   \n\
                                \     ▒     ▒▒   \n\
                                \     ▒▒▒▒▒ ▒    \n\
                                \           ▒    \n\
                                \           ▒    \n\
                                \      ±▒▒▒▒▒    \n\
                                \                \n\
                                \                \n\
                                \                \n") $
            show level6
  ]

testMove :: TestPP()
testMove = tests 3 5
  [ testString "move North testLevel0" 1 (translateChars 
                                         "\n▒▒▓▒▒\n\
                                           \▒▒▓▒▒\n\
                                           \▒▒▒▒▒\n\
                                           \▒▒▒▒▒\n\
                                           \▒▒▒▒▒\n") $
    show $ move North testLevel0
  , testString "move South testLevel0" 1 (translateChars 
                                         "\n▒▒▒▒▒\n\
                                           \▒▒▒▒▒\n\
                                           \▒▒▒▒▒\n\
                                           \▒▒▓▒▒\n\
                                           \▒▒▓▒▒\n") $
    show $ move South testLevel0
  , testString "move West testLevel0" 1 (translateChars 
                                        "\n▒▒▒▒▒\n\
                                          \▒▒▒▒▒\n\
                                          \▓▓▒▒▒\n\
                                          \▒▒▒▒▒\n\
                                          \▒▒▒▒▒\n") $
    show $ move West testLevel0
  , testString "move East testLevel0" 1 (translateChars 
                                        "\n▒▒▒▒▒\n\
                                          \▒▒▒▒▒\n\
                                          \▒▒▒▓▓\n\
                                          \▒▒▒▒▒\n\
                                          \▒▒▒▒▒\n") $
    show $ move East testLevel0
  , testString "move North $ move East testLevel0" 1 (translateChars 
                                                     "\n▒▒▒▒▒\n\
                                                       \▒▒▒▓▓\n\
                                                       \▒▒▒▒▒\n\
                                                       \▒▒▒▒▒\n\
                                                       \▒▒▒▒▒\n") $
    show $ move North $ move East $ testLevel0
  , testString "move East $ move North $ move West $ move South testLevel0" 1 (translateChars 
                                                                              "\n▒▒▒▒▒\n\
                                                                                \▒▒▒▒▒\n\
                                                                                \▒▒▓▓▒\n\
                                                                                \▒▒▒▒▒\n\
                                                                                \▒▒▒▒▒\n") $
    show $ move East $ move North $ move West $ move South testLevel0
  ]

testActivate :: TestPP()
testActivate = tests 4 10
  [ testString "Test Soft Lose" 1 (translateChars 
                                  "\n         \n\
                                    \         \n\
                                    \  ▓▒▒▒±▒ \n\
                                    \  *=▒▒   \n\
                                    \         \n\
                                    \         \n"++
                                    "Game Over\n") $
    show $ move West $ move West testActivateLevel
  , testString "Test Soft Win" 1 (translateChars 
                                "\n         \n\
                                  \         \n\
                                  \  =▒▒▒±▒ \n\
                                  \  *▓▓▒   \n\
                                  \         \n\
                                  \         \n") $
    show $ move South $ move West testActivateLevel
  , testString "Test Switch Activate" 1 (translateChars 
                                        "\n         \n\
                                          \         \n\
                                          \  =▒▒▒▓▓ \n\
                                          \  *=▒▒▒  \n\
                                          \         \n\
                                          \         \n") $
    show $ move East testActivateLevel
  , testString "Test Switch Activate-Deactivate" 1  (translateChars 
                                                    "\n         \n\
                                                      \         \n\
                                                      \  =▒▒▒▓▓ \n\
                                                      \  *=▒▒   \n\
                                                      \         \n\
                                                      \         \n") $
    show $ move East $ move West $ move East testActivateLevel
  , testString "Test Switch Activate-Deactivate-Activate" 1 (translateChars 
                                                            "\n         \n\
                                                              \         \n\
                                                              \  =▒▒▒▓▓ \n\
                                                              \  *=▒▒▒  \n\
                                                              \         \n\
                                                              \         \n") $
    show $ move East $ move West $
                move East $ move West $ move East testActivateLevel
  , testString "Test Win" 1 (translateChars 
                          "\n         \n\
                            \         \n\
                            \  =▒▒▒±▒ \n\
                            \  ▓=▒▒   \n\
                            \         \n\
                            \         \n"++
                            "Congrats! You won!\n") $
    show $ move West $ move South $ move West testActivateLevel
  , testString "Test Lose" 1 (translateChars 
                           "\n         \n\
                             \         \n\
                             \  =▒▒▒±▒ \n\
                             \  *=▒▓   \n\
                             \     ▓   \n\
                             \         \n"++
                             "Game Over\n") $
    show $ move South testActivateLevel
  ]

testLimitedDfs :: TestPP ()
testLimitedDfs = tests 4 15
    [ testVal "limitedDfs.Tree.0" 1 [0] $ listTo 0
    , testVal "limitedDfs.Tree.1" 1 [0, 1, 2] $ listTo 1
    , testVal "limitedDfs.Tree.2" 1 [0, 1, 3, 4, 2, 6] $ listTo 2
    , testVal "limitedDfs.Tree.3" 1 [0, 1, 3, 7, 8, 4, 9, 10, 2, 6, 13, 14] $
          listTo 3
    ]
  where
    listTo = map (getTree . nodeState) . limitedDfs  (createStateSpace (Tree 0))

testIterativeDeepening :: TestPP ()
testIterativeDeepening = tests 5 10
    [ testVal "iterativeDeepening.Tree.state" 1 (Tree 13) $ nodeState node
    , testVal "iterativeDeepening.Tree.number" 1 20 $ number
    ]
  where
    (node, number) = iterativeDeepening $ createStateSpace (Tree 0)

testExtractPath :: TestPP ()
testExtractPath = tests 6 10
    [ testVal "extractPath.Tree" 1 [(2, 2), (2, 6), (1, 13)] $
          map (second getTree) $ extractPath node
    ]
  where
    (node, _) = iterativeDeepening $ createStateSpace (Tree 0)

testSuccessors :: TestPP()
testSuccessors = tests 7 10
  [ testVal "successors testLevel0" 1 [(East, (translateChars 
                                              "\n▒▒▒▒▒\n\
                                                \▒▒▒▒▒\n\
                                                \▒▒▒▓▓\n\
                                                \▒▒▒▒▒\n\
                                                \▒▒▒▒▒\n") )
                                      ,(West, (translateChars 
                                                "\n▒▒▒▒▒\n\
                                                  \▒▒▒▒▒\n\
                                                  \▓▓▒▒▒\n\
                                                  \▒▒▒▒▒\n\
                                                  \▒▒▒▒▒\n") )
                                      ,(South, (translateChars
                                                "\n▒▒▒▒▒\n\
                                                  \▒▒▒▒▒\n\
                                                  \▒▒▒▒▒\n\
                                                  \▒▒▓▒▒\n\
                                                  \▒▒▓▒▒\n") )
                                      ,(North, (translateChars 
                                              "\n▒▒▓▒▒\n\
                                                \▒▒▓▒▒\n\
                                                \▒▒▒▒▒\n\
                                              	\▒▒▒▒▒\n\
                                              	\▒▒▒▒▒\n") )]
            $ map (second show) $ sortBy (flip compare `on` fst) $ successors testLevel0
  , testVal "successors level0" 1 [(East, (translateChars 
                                          "\n         \n\
                                            \         \n\
                                            \  ▒▒▒▒▓▓*\n\
                                            \         \n\
                                            \         \n") )
                                  ,(West, (translateChars 
                                          "\n         \n\
                                            \         \n\
                                            \  ▒▓▓▒▒▒*\n\
                                            \         \n\
                                            \         \n") ) 
                                  ] 
            $ map (second show) $ sortBy (flip compare `on` fst) $ successors level0

  ]

testIsGoal :: TestPP()
testIsGoal = tests 8 10
  [ testCond "isGoal.level0.0" 1 $ not $ isGoal $ movesLevel0 !! 0
  , testCond "isGoal.level0.1" 1 $ not $ isGoal $ movesLevel0 !! 1
  , testCond "isGoal.level0.2" 1 $ isGoal $ movesLevel0 !! 2
  , testCond "isGoal.testActivateLevel.0" 1 $ not $ isGoal $ movesTestActivateLevel !! 0
  , testCond "isGoal.testActivateLevel.1" 1 $ not $ isGoal $ movesTestActivateLevel !! 1
  , testCond "isGoal.testActivateLevel.2" 1 $ isGoal $ movesTestActivateLevel !! 3
  , testCond "isGoal.softTileBreakTestActivateLevel" 1 $ not $ isGoal $ softTileBreak
  , testCond "isGoal.fallOffMapTestActivateLevel" 1 $ not $ isGoal $ move North testActivateLevel
  ]
  where
    movesLevel0 = moveMany [East, East] level0
    movesTestActivateLevel = moveMany [West, South, West] testActivateLevel
    softTileBreak = move West $ move West testActivateLevel

testSolve :: TestPP()
testSolve = tests 9 10
  [ testCond "solve.level0" 1 $ isSolution level0 $ getSolution level0
  , testCond "solve.level1" 1 $ isSolution level1 $ getSolution level1
  , testCond "solve.level2" 1 $ isSolution level2 $ getSolution level2
  , testCond "solve.level3" 1 $ isSolution level3 $ getSolution level3
  , testCond "solve.level4" 1 $ isSolution level4 $ getSolution level4
  , testCond "solve.level5" 1 $ isSolution level5 $ getSolution level5
  , testCond "solve.level6" 1 $ isSolution level6 $ getSolution level6
  ]
  where
    getSolution = flip solve False

testHeuristic :: TestPP ()
testHeuristic = tests 10 20
    [ testCond "euristic works on at least 1 level" 1 $ length filtered >= 1
    , testCond "euristic works on at least 2 levels" 1 $ length filtered >= 2
    , testCond "euristic works on at least 3 levels" 1 $ length filtered >= 3
    ]
      where
          filtered = filter (liftM2 (>) fst snd) numbers
          numbers = map (snd . iterativeDeepening . createStateSpace  &&& snd . iterativeDeepening . orderStateSpace . createStateSpace) levels
          levels = [level1, level2, level3, level4, level5, level6]

moveMany :: [Directions] -> Level -> [Level]
moveMany positions level = out
  where
    out = level : zipWith move positions out

isSolution :: Level -> [(Directions, Level)] -> Bool
isSolution level path = isValidPath && null rest
  where
    isValidPath = foldM (\from (pos, to) ->
                             if move pos from == to then Just to else Nothing)
                        level path /= Nothing
    (_, _ : rest) = break (isGoal . snd) path

asciiMap :: M.Map Char Char
asciiMap = M.fromList [ ('▒', hardTile)
                      , ('=', softTile)
                      , ('▓', block)
                      , ('±', switch)
                      , (' ', emptySpace)
                      , ('*', winningTile)
                      ]

translateChars :: String -> String
translateChars = map (\x -> M.findWithDefault x x asciiMap)

main :: IO ()
main = runTestPP $ sequence_ [ testAddObject
                             , testShowLevels
                             , testMove
                             , testActivate
                             , testLimitedDfs
                             , testIterativeDeepening
                             , testExtractPath
                             , testSuccessors
                             , testIsGoal
                             , testSolve
                             , testHeuristic
                             ]
