{-# OPTIONS_GHC -Wall #-}

module Levels where

import Bloxorz

testActivateLevel :: Level
testActivateLevel = withWinningTile
    where
      empty = emptyLevel (5, 8) (2, 5)
      onlyHard = foldr (\x y-> addTile 'H' x y)
        empty [ (2, 3), (2, 4), (2, 5), (2, 7), (3, 4), (3, 5)
              ]
      withSoft = addTile 'S' (2, 2) $ addTile 'S' (3, 3) onlyHard
      withButton = addSwitch (2, 6) [(3, 6)] withSoft
      withWinningTile = addTile 'W' (3, 2) withButton

testLevel0 :: Level
testLevel0 = onlyHard
    where
        empty = emptyLevel (4, 4) (2, 2)
        onlyHard = foldr (\x y-> addTile 'H' x y)
          empty [ (x, y) | x <- [0..4], y <- [0..4]]


level0 :: Level
level0 = withWinningTile
    where
        empty = emptyLevel (4, 8) (2, 5)
        onlyHard = foldr (\x y-> addTile 'H' x y)
          empty [ (2, 2), (2, 3), (2, 4), (2, 5), (2, 6), (2, 7)
                ]
        withWinningTile = addTile 'W' (2, 8) onlyHard


level1 :: Level
level1 = withWinningTile
    where
        empty = emptyLevel (9, 13) (3, 3)
        onlyHard = foldr (\x y-> addTile 'H' x y)
          empty [ (2, 2), (2, 3), (2, 4)
                , (3, 2), (3, 3), (3, 4), (3, 5), (3, 6), (3, 7)
                , (4, 2), (4, 3), (4, 4), (4, 5), (4, 6), (4, 7)
                , (4, 8), (4, 9), (4, 10)
                , (5, 3), (5, 4), (5, 5), (5, 6), (5, 7)
                , (5, 8), (5, 9), (5, 10), (5, 11)
                , (6, 7), (6, 8), (6, 10), (6, 11)
                , (7, 8) , (7, 9), (7, 10)
                ]
        withWinningTile = addTile 'W' (6, 9) onlyHard

level2 :: Level
level2 = withWinningTile
    where
        empty = emptyLevel (9, 19) (5, 3)
        onlyHard = foldr (\x y-> addTile 'H' x y)
          empty [ (3, 2), (3, 3), (3, 4), (3, 5)
                , (4, 2), (4, 3), (4, 4), (4, 5)
                , (5, 2), (5, 3), (5, 4), (5, 5)
                , (6, 2), (6, 3), (6, 4), (6, 5)
                , (4, 6), (4, 7)
                , (4, 8), (4, 9), (4, 10)
                , (3, 8), (3, 9), (3, 10)
                , (2, 8), (2, 9), (2, 10)
                , (2, 11), (2, 12)
                , (2, 13), (2, 14)
                , (3, 13), (3, 14)
                , (4, 13), (4, 14), (4, 15), (4, 16)
                , (5, 13), (5, 14), {- (5, 15),-} (5, 16)
                , (6, 13), (6, 14), (6, 15), (6, 16)
                , (7, 14), (7, 15), (7, 16)
                ]
        withWinningTile = addTile 'W' (5, 15) onlyHard

level3 :: Level
level3 = withWinningTile
    where
        empty = (emptyLevel (12, 18) (7, 3))
        onlyHard = foldr (\x y-> addTile 'H' x y) empty
         [ (4, 2), (4, 3), (4, 4), (4, 5)
         , (5, 2), (5, 3), (5, 4)
         , (6, 2), (6, 3), (6, 4)
         , (7, 2), (7, 3), (7, 4)
         , (8, 2), (8, 3), (8, 4)
         , (4, 11), (4, 12), (4, 13)
         , (5, 12), (5, 13)
         , (6, 12), (6, 13)
         , (9, 14)
         , (7, 7), (7, 8), (7, 9), (7, 10)
         , (8, 7), (8, 8), (8, 9), (8, 10)
         , (9, 7), {- (9, 8), -} (9, 9)
         , (10, 7), (10, 8), (10, 9)
         ]
        withSoft = foldr (\x y -> addTile 'S' x y) onlyHard
         [ (3, 5), (3, 6), (3, 7), (3, 8), (3, 9), (3, 10)
         , (3, 11)
         , (2, 5), (2, 6), (2, 7), (2, 8), (2, 9), (2, 10)
         , (2, 11)
         , (7, 11), (7, 12), (7, 13), (7, 14), (7, 15)
         , (8, 11), (8, 12), (8, 13), (8, 14), (8, 15)
         , (9, 12), (9, 13), (9, 15)
         , (10, 12), (10, 13), (10, 14), (10, 15)
         ]
        withWinningTile = addTile 'W' (9, 8) withSoft

level4 :: Level
level4 = withWinningTile
    where
        empty = (emptyLevel (9, 15) (3, 3))
        onlyHard = foldr (\x y-> addTile 'H' x y) empty
         [ (2, 3), (2, 4), (2, 5), (2, 6)
         , (3, 4), (3, 5), (3, 6), (3, 3)
         , (4, 4), (4, 5), (4, 6), (4, 3)
         , (5, 6), (5, 7), (5, 10), (5, 5)
         , (6, 9), (6, 10), (6, 11), (6, 8)
         , (5, 11), (5, 12)
         , (4, 9), (4, 10), (4, 11), (4, 12)
         , (3, 9), (3, 10), (3, 11), (3, 12)
         , (2, 9), (2, 10), (2, 11), (2, 12)
         ]
        withSoft = foldr (\x y -> addTile 'S' x y) onlyHard [ (5, 8), (5, 9) ]
        withWinningTile = addTile 'W' (3, 10) withSoft

level5 :: Level
level5 = withWinningTile
    where
        empty = (emptyLevel (14, 18) (3, 15))
        onlyHard = foldr (\x y-> addTile 'H' x y) empty
         [ (2, 13), (2, 14), (2, 15), (2, 16)
         , (3, 13), (3, 14), (3, 15), (3, 16)
         , (4, 14), (4, 15), (4, 16)
         , (3, 12), (3, 11), (3, 9)
         , (3, 3), (3, 4), (3, 5), (3, 6)
         , (4, 3), (4, 4), (4, 5), (4, 6)
         , (5, 3), (5, 4), (5, 5), (5, 6)
         , (6, 3), (6, 4), (6, 5), (6, 6)
         , (7, 5), (7, 6)
         , (7, 7), (7, 9)
         , (7, 12), (7, 13), (7, 14)
         , (8, 12), (8, 13), (8, 14), (8, 15)
         , (9, 12), (9, 13), (9, 14), (9, 15), (9, 16)
         , (10, 12), (10, 13), (10, 14)
         , (10, 11), (10, 10), (10, 9), (10, 6)
         , (10, 5), (10, 4), (10, 2)
         , (9, 2), (9, 3), (9, 4)
         , (11, 2), (11, 3), (11, 4), (11, 5)
         ]
        withButton = foldr (\(p, posx) acc -> addSwitch p posx acc ) onlyHard
          [ ((3, 10), [(3, 7), (3, 8)])
          , ((7, 8), [(7, 10), (7, 11)])
          , ((8, 16), [(10, 7), (10, 8)])
          ]
        withWinningTile = addTile 'W' (10, 3) withButton

level6 :: Level
level6 = withWinningTile
    where
        empty = (emptyLevel (11, 15) (2, 12))
        onlyHard = foldr (\x y-> addTile 'H' x y) empty
         [ {- (2, 2), -} (2, 3), (2, 4), (2, 5)
         , (3, 5), (4, 5), (5, 5)
         , (5, 6), (5, 7), (5, 8), (5, 9)
         , {- (8, 6), -} (8, 7), (8, 8), (8, 9), (8, 10), (8, 11)
         , (7, 11), (6, 11), (5, 11)
         , (4, 11), (4, 12), (3, 11), (3, 12)
         , (2, 12)
         ]
        withButton = foldr (\(p, posx) acc -> addSwitch p posx acc ) onlyHard
          [ ((8, 6), [(7, 8), (6, 8)]) ]
        withWinningTile = addTile 'W' (2, 2) withButton

levelx :: Level
levelx = withButton
    where
        empty = (emptyLevel (9, 15) (3, 3))
        onlyHard = foldr (\x y-> addTile 'H' x y) empty
         [ (2, 3), (2, 4), (2, 5), (2, 6)
         , (3, 4), (3, 5), (3, 6), (3, 3)
         , (4, 4), (4, 5), (4, 6), (4, 3)
         , (5, 6), (5, 7), (5, 10), (5, 5)
         , (6, 9), (6, 10), (6, 11), (6, 8)
         , (5, 11), (5, 12)
         , (4, 9), (4, 10), (4, 11), (4, 12)
         , (3, 9), (3, 10), (3, 11), (3, 12)
         , (2, 9), (2, 10), (2, 11), (2, 12)
         ]
        withSoft = foldr (\x y -> addTile 'S' x y) onlyHard [ (5, 8), (5, 9) ]
        withWinningTile = addTile 'W' (3, 10) withSoft
        withButton = addSwitch (2, 4) [(2, 7), (2, 8), (3, 7), (3, 8)] withWinningTile
