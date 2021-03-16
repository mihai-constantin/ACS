-- TEMA 2 | CONSTANTIN MIHAI | 321CD

{-# OPTIONS_GHC -Wall #-}
{-# LANGUAGE EmptyDataDecls, MultiParamTypeClasses,
             TypeSynonymInstances, FlexibleInstances,
             InstanceSigs #-}


module Bloxorz where

import ProblemState

import qualified Data.List as L

import Data.Maybe

{-
    Caracterele ce vor fi printate pentru fiecare tip de obiect din joc 
    Puteți înlocui aceste caractere cu orice, în afară de '\n'.
-}

hardTile :: Char
hardTile = '▒'

softTile :: Char
softTile = '='

block :: Char
block = '▓'

switch :: Char
switch = '±'

emptySpace :: Char
emptySpace = ' '

winningTile :: Char
winningTile = '*'

{-
    Sinonim de tip de date pentru reprezetarea unei perechi (int, int)
    care va reține coordonatele de pe tabla jocului
-}

type Position = (Int, Int)

{-
    Direcțiile în care se poate mișcă blocul de pe tablă
-}

data Directions = North | South | West | East deriving (Show, Eq, Ord)

{-
    Tip de date care va reprezenta plăcile care alcătuiesc harta și switch-urile
-}

data Cell = HardCell | SoftCell | BlockCell | SwitchCell | EmptySpaceCell | WinningCell 
    deriving (Eq, Ord)

instance Show Cell where
    show HardCell = [hardTile]
    show SoftCell = [softTile]
    show BlockCell = [block]
    show SwitchCell = [switch]
    show EmptySpaceCell = [emptySpace]
    show WinningCell = [winningTile]

{-
    Tip de date pentru reprezentarea nivelului curent
-}

-- myMap - configuratia efectiva a hartii
-- myBlockPositions - lista de pozitii pe care se afla paralelipipedul (pot fi maxim 2), 
--                    precum si tipul de cell-uri pe care sta
-- mySwitchPositions - lista de perechi, retinand pentru fiecare switch pozitia sa, precum si o lista de pozitii 
--                     a cell-urilor pe care le poate activa / dezactiva

data Level = Lvl
    { myMap :: [[Cell]]
    , myBlockPositions :: [(Position, Cell)]
    , mySwitchPositions :: [(Position, [Position])]
    } deriving (Eq, Ord)

{-
    Instantiati Level pe Show. 

    Atenție! String-ul returnat va fi urmat și precedat de un rând nou. 
    În cazul în care jocul este câștigat, la sfârșitul stringului se va mai
    concatena mesajul "Congrats! You won!\n". 
    În cazul în care jocul este pierdut, se va mai concatena "Game Over\n". 
-}

-- iau cell-ul de la coordonatele (x, y) din matrice
getCharacter :: [[Cell]] -> Position -> Cell
getCharacter _myMap (x, y) = (!!) lst y
    where
        lst = (!!) _myMap x

-- Sursa de inspiratie: https://stackoverflow.com/questions/18691321/printing-a-2d-array-in-haskell
instance Show Level where
    show (Lvl _myMap _myBlockPositions _mySwitchPositions) = 
        if winGame (Lvl _myMap _myBlockPositions _mySwitchPositions)
            then "\n" ++ msg ++ "Congrats! You won!\n"
            else if lostGame (Lvl _myMap _myBlockPositions _mySwitchPositions)
                    then "\n" ++ msg ++ "Game Over\n"
                    else "\n" ++ msg
        where
            msg = unlines [concat [show (getCharacter _myMap (y, x))  | x <- [0 .. h]] | y <- [0 .. w]]
            w = (length _myMap - 1)
            h = (length $ (!!) _myMap 0) - 1

{-
    Primește coordonatele colțului din dreapta jos a hartii și poziția inițială a blocului.
    Întoarce un obiect de tip Level gol.
    Implicit, colțul din stânga sus este (0, 0).
-}

-- Sursa de inspiratie: https://stackoverflow.com/questions/12860798/haskell-how-to-create-a-matrix
createMap :: Position -> Position -> [[Cell]]
createMap (h, w) p = [[if (y, x) == p then BlockCell else EmptySpaceCell | x <- [0 .. w]] | y <- [0 .. h]]

emptyLevel :: Position -> Position -> Level
emptyLevel matrix_dim block_position = Lvl _myMap _myBlockPositions _mySwitchPositions
    where
        _myMap = createMap matrix_dim block_position
        _myBlockPositions = [(block_position, HardCell)]
        _mySwitchPositions = []

{-
    Adaugă o celulă de tip Tile în nivelul curent.
    Parametrul char descrie tipul de tile adăugat: 
        'H' pentru tile hard 
        'S' pentru tile soft 
        'W' pentru winning tile 
-}

-- Sursa de inspiratie: https://stackoverflow.com/questions/20156078/replacing-an-element-in-a-list-of-lists-in-haskell
-- Adauga pe harta actuala un cell la pozitia (x, y)
updateMatrix :: [[Cell]] -> Position -> Cell -> [[Cell]]
updateMatrix _oldMap (x, y) _myCell = _start ++ _updateRow ++ _end
    where
        _start = take x _oldMap
        _updateRow = [take y (_oldMap !! x) ++ [_myCell] ++ drop (y + 1) (_oldMap !! x)]
        _end = drop (x + 1) _oldMap

-- Adauga la pozitia data tipul de Cell corespunzator 
updateBlockPositions :: [(Position, Cell)] -> Position -> Cell -> [(Position, Cell)]
updateBlockPositions _oldBlockPositions (x, y) _myCell
    | lung == 1 = [(fst $ head _oldBlockPositions, _myCell)]
    | lung == 2 && (fst $ head _oldBlockPositions) == (x, y) = [(fst $ head _oldBlockPositions, _myCell), last _oldBlockPositions]
    | otherwise = [head _oldBlockPositions, (fst $ last _oldBlockPositions, _myCell)]
    where
        lung = length _oldBlockPositions

addTile :: Char -> Position -> Level -> Level
addTile cellType (x, y) current_lvl = Lvl _myMap _myBlockPositions _mySwitchPositions
    where
        _myBlockPos = map fst $ myBlockPositions current_lvl
        -- verific daca celula pe care vreau sa o adaug se afla sub paralelipiped
        _myMap = if elem (x, y) _myBlockPos then _oldMap else (updateMatrix _oldMap (x, y) _myCell)
        _myBlockPositions = 
            if elem (x, y) _myBlockPos 
                then (updateBlockPositions _oldBlockPositions (x, y) _myCell) 
                else _oldBlockPositions
        _mySwitchPositions = mySwitchPositions current_lvl
        _oldMap = myMap current_lvl
        _oldBlockPositions = myBlockPositions current_lvl
        _myCell = case cellType of
            'H' -> HardCell
            'S' -> SoftCell
            _ -> WinningCell

{-
    Adaugă o celulă de tip Swtich în nivelul curent.
    Va primi poziția acestuia și o listă de Position
    ce vor desemna pozițiile în care vor apărea sau 
    dispărea Hard Cells în momentul activării/dezactivării
    switch-ului.
-}

addSwitch :: Position -> [Position] -> Level -> Level
addSwitch switch_position switch_cells current_lvl = Lvl _myMap _myBlockPositions _mySwitchPositions
    where
        _myBlockPos = map fst $ myBlockPositions current_lvl -- lista cu pozitia (pozitiile) block-ului
        _myMap = if elem switch_position _myBlockPos then _oldMap else (updateMatrix _oldMap switch_position _myCell)
        _oldMap = myMap current_lvl
        _myBlockPositions = 
            if elem switch_position _myBlockPos 
                then (updateBlockPositions _oldBlockPositions switch_position _myCell)
                else _oldBlockPositions
        _oldBlockPositions = myBlockPositions current_lvl 
        _mySwitchPositions = _newEntry : _oldSwitchPositions
        _oldSwitchPositions = mySwitchPositions current_lvl
        _newEntry = (switch_position, switch_cells)
        _myCell = SwitchCell

{-
    === MOVEMENT ===
-}

{-
    Activate va verifica dacă mutarea blocului va activa o mecanică specifică. 
    În funcție de mecanica activată, vor avea loc modificări pe hartă. 
-}

activate :: Level -> Level
activate current_lvl = if testSwitch then _newLevel else current_lvl
    where
        _newLevel = Lvl _myMap _myBlockPositions _mySwitchPositions

        _myMap = _newMap1

        -- coordonatele paralelipipedului dreptunghic
        (x1, y1) = fst $ head _myBlockPositions
        (x2, y2) = fst $ last _myBlockPositions
        -- celulele care se afla sub paralelipipedul dreptunghic
        _myCell1 = snd $ head _myBlockPositions
        _myCell2 = snd $ last _myBlockPositions

        testSwitch = _myCell1 == SwitchCell || _myCell2 == SwitchCell

        -- lista de pozitii care vor fi activate / dezactivate de switch-ul de la pozitia (x1,y1)
        _myList1 = if _myCell1 == SwitchCell
                    then snd $ head $ filter (\pair -> fst pair == (x1, y1)) _mySwitchPositions
                    else []

        _newMap = case _myList1 == [] of
                True -> _oldMap
                _ -> if _myCellHeadList1 == EmptySpaceCell
                        then updateMatrix (updateMatrix _oldMap _headList1 HardCell) _lastList1 HardCell
                        else updateMatrix (updateMatrix _oldMap _headList1 EmptySpaceCell) _lastList1 EmptySpaceCell
                    where
                        _headList1 = head _myList1
                        _lastList1 = last _myList1
                        -- verific ce tip de celula e la pozitia _headList1
                        _myCellHeadList1 = getCharacter _oldMap _headList1

        -- lista de pozitii care vor fi activate / dezactivare de switch-ul de la pozitia (x2, y2)
        _myList2 = if _myCell2 == SwitchCell
                    then snd $ head $ filter (\pair -> fst pair == (x2,y2)) _mySwitchPositions
                    else []

        _newMap1 = case _myList2 == [] of
                    True -> _newMap
                    _ -> if _myCellHeadList2 == EmptySpaceCell
                            then updateMatrix (updateMatrix _newMap _headList2 HardCell) _lastList2 HardCell
                            else updateMatrix (updateMatrix _newMap _headList2 EmptySpaceCell) _lastList2 EmptySpaceCell
                        where
                            _headList2 = head _myList2
                            _lastList2 = last _myList2
                            -- verific ce tip de celula e la pozitia _headList2
                            _myCellHeadList2 = getCharacter _newMap _headList2
        
        _oldMap = myMap current_lvl
        _myBlockPositions = myBlockPositions current_lvl
        _mySwitchPositions = mySwitchPositions current_lvl

{-
    Mișcarea blocului în una din cele 4 direcții 
    Hint: Dacă jocul este deja câștigat sau pierdut, puteți lăsa nivelul neschimbat.
-}

moveNorthFirstCase :: Level -> Level
moveNorthFirstCase current_lvl = Lvl _myMap1 _myBlockPositions _mySwitchPositions
    where
        _myMap1 = updateMatrix _myMap (x, y) _myCell
        _myMap = updateMatrix (updateMatrix _oldMap (x - 2, y) BlockCell) (x - 1, y) BlockCell
        _myBlockPositions = [((x - 2, y), _myCell1), ((x - 1, y), _myCell2)]
        (x, y) = fst $ head _oldBlockPositions
        _myCell = snd $ head _oldBlockPositions
        _myCell1 = getCharacter _oldMap (x - 2, y)
        _myCell2 = getCharacter _oldMap (x - 1, y)
        _oldMap = myMap current_lvl
        _oldBlockPositions = myBlockPositions current_lvl
        _mySwitchPositions = mySwitchPositions current_lvl

moveNorthSecondCase :: Level -> Level
moveNorthSecondCase current_lvl = Lvl _myMap1 _myBlockPositions _mySwitchPositions
    where
        _myMap1 = updateMatrix (updateMatrix _myMap (x1 - 1, y1) BlockCell) (x2 - 1, y2) BlockCell
        _myMap = updateMatrix (updateMatrix _oldMap (x1, y1) _myCell1) (x2, y2) _myCell2
        _myBlockPositions = [((x1 - 1, y1), _myCell3), ((x2 - 1, y2), _myCell4)]
        -- coordonatele paralelipipedului dreptunghic
        (x1, y1) = fst $ head _oldBlockPositions
        (x2, y2) = fst $ last _oldBlockPositions
        -- celulele care se afla sub paralelipipedul dreptunghic
        _myCell1 = snd $ head _oldBlockPositions
        _myCell2 = snd $ last _oldBlockPositions
        -- tipurile de cell-uri pe care va sta paralelipipedul in noua pozitie
        _myCell3 = getCharacter _oldMap (x1 - 1, y1)
        _myCell4 = getCharacter _oldMap (x2 - 1, y2)
        _oldMap = myMap current_lvl
        _oldBlockPositions = myBlockPositions current_lvl
        _mySwitchPositions = mySwitchPositions current_lvl

moveNorthThirdCase :: Level -> Level
moveNorthThirdCase current_lvl = Lvl _myMap1 _myBlockPositions _mySwitchPositions
    where
        _myMap1 = updateMatrix _myMap (x, y) BlockCell
        _myMap = updateMatrix (updateMatrix _oldMap (x1, y1) _myCell1) (x2, y2) _myCell2
        
        _myBlockPositions = [((x, y), _myCell)]

        -- coordonatele paralelipipedului dreptunghic
        (x1, y1) = fst $ head _oldBlockPositions
        (x2, y2) = fst $ last _oldBlockPositions
        -- celulele care se afla sub paralelipipedul dreptunghic
        _myCell1 = snd $ head _oldBlockPositions
        _myCell2 = snd $ last _oldBlockPositions

        -- coordonatele noi ale paralelipipedului dreptunghic (in pozitie verticala)
        x = if x1 < x2 then x1 - 1 else x2 - 1
        y = y1
        _myCell = getCharacter _oldMap (x, y)

        _oldMap = myMap current_lvl
        _oldBlockPositions = myBlockPositions current_lvl
        _mySwitchPositions = mySwitchPositions current_lvl

moveNorth :: Level -> Level
moveNorth current_lvl = 
    case lung == 1 of
        True -> moveNorthFirstCase current_lvl
        _ -> if x1 == x2 && y2 == y1 + 1 then moveNorthSecondCase current_lvl else moveNorthThirdCase current_lvl
    where
        (x1, y1) = fst $ head _myBlockPositions
        (x2, y2) = fst $ last _myBlockPositions
        lung = length _myBlockPositions
        _myBlockPositions = myBlockPositions current_lvl

moveSouthFirstCase :: Level -> Level
moveSouthFirstCase current_lvl = Lvl _myMap1 _myBlockPositions _mySwitchPositions
    where
        _myMap1 = updateMatrix _myMap (x, y) _myCell
        _myMap = updateMatrix (updateMatrix _oldMap (x + 1, y) BlockCell) (x + 2, y) BlockCell        
        _myBlockPositions = [((x + 1, y), _myCell1), ((x + 2, y), _myCell2)]

        -- coordonatele paralelipipedului dreptunghic
        (x, y) = fst $ head _oldBlockPositions
        -- tipul de cell de sub paralelipipedul dreptunghic
        _myCell = snd $ head _oldBlockPositions

        -- tipurile de cell-uri pe care va sta paralelipipedul in pozitie orizontala
        _myCell1 = getCharacter _oldMap (x + 1, y)
        _myCell2 = getCharacter _oldMap (x + 2, y)

        _oldMap = myMap current_lvl
        _oldBlockPositions = myBlockPositions current_lvl
        _mySwitchPositions = mySwitchPositions current_lvl

moveSouthSecondCase :: Level -> Level
moveSouthSecondCase current_lvl = Lvl _myMap1 _myBlockPositions _mySwitchPositions
    where
        _myMap1 = updateMatrix (updateMatrix _myMap (x1 + 1, y1) BlockCell) (x2 + 1, y2) BlockCell
        _myMap = updateMatrix (updateMatrix _oldMap (x1, y1) _myCell1) (x2, y2) _myCell2
        _myBlockPositions = [((x1 + 1, y1), _myCell3), ((x2 + 1, y2), _myCell4)]
        -- coordonatele paralelipipedului dreptunghic
        (x1, y1) = fst $ head _oldBlockPositions
        (x2, y2) = fst $ last _oldBlockPositions
        -- celulele care se afla sub paralelipipedul dreptunghic
        _myCell1 = snd $ head _oldBlockPositions
        _myCell2 = snd $ last _oldBlockPositions
        -- tipurile de cell-uri pe care va sta paralelipipedul in noua pozitie
        _myCell3 = getCharacter _oldMap (x1 + 1, y1)
        _myCell4 = getCharacter _oldMap (x2 + 1, y2)
        _oldMap = myMap current_lvl
        _oldBlockPositions = myBlockPositions current_lvl
        _mySwitchPositions = mySwitchPositions current_lvl

moveSouthThirdCase :: Level -> Level
moveSouthThirdCase current_lvl = Lvl _myMap1 _myBlockPositions _mySwitchPositions
    where
        _myMap1 = updateMatrix _myMap (x, y) BlockCell
        _myMap = updateMatrix (updateMatrix _oldMap (x1, y1) _myCell1) (x2, y2) _myCell2
        _myBlockPositions = [((x, y), _myCell)]
        -- coordonatele paralelipipedului dreptunghic
        (x1, y1) = fst $ head _oldBlockPositions
        (x2, y2) = fst $ last _oldBlockPositions
        -- (x, y) - coordonatele unde va ajunge block-ul (ajunge in pozitie verticala)
        x = if x1 < x2 then x2 + 1 else x1 + 1
        y = y1
        -- celulele care se afla sub paralelipipedul dreptunghic
        _myCell1 = snd $ head _oldBlockPositions
        _myCell2 = snd $ last _oldBlockPositions
        -- ce o sa am sub paralelipipedul dreptunghic dupa ce o sa ajunga in pozitia verticala
        _myCell = getCharacter _oldMap (x, y)
        _oldMap = myMap current_lvl
        _oldBlockPositions = myBlockPositions current_lvl
        _mySwitchPositions = mySwitchPositions current_lvl

moveSouth :: Level -> Level
moveSouth current_lvl =
    case lung == 1 of
        True -> moveSouthFirstCase current_lvl
        _ -> if x1 == x2 && y2 == y1 + 1 then moveSouthSecondCase current_lvl else moveSouthThirdCase current_lvl
    where
        (x1, y1) = fst $ head _myBlockPositions
        (x2, y2) = fst $ last _myBlockPositions
        lung = length _myBlockPositions
        _myBlockPositions = myBlockPositions current_lvl

moveWestFirstCase :: Level -> Level
moveWestFirstCase current_lvl = Lvl _myMap1 _myBlockPositions _mySwitchPositions
    where
        _myMap1 = updateMatrix _myMap (x, y) _myCell
        _myMap = updateMatrix (updateMatrix _oldMap (x, y - 2) BlockCell) (x, y - 1) BlockCell
        _myBlockPositions = [((x, y - 2), _myCell1), ((x, y - 1), _myCell2)]
        -- coordonatele paralelipipedului dreptunghic
        (x, y) = fst $ head _oldBlockPositions
        -- tipul de cell pe care sta paralelipipedul dreptunghic in pozitie verticala
        _myCell = snd $ head _oldBlockPositions
        -- tipurile de cell-uri pe care va sta paralelipipedul in pozitie orizontala
        _myCell1 = getCharacter _oldMap (x, y - 2)
        _myCell2 = getCharacter _oldMap (x, y - 1)
        _oldMap = myMap current_lvl
        _oldBlockPositions = myBlockPositions current_lvl
        _mySwitchPositions = mySwitchPositions current_lvl

moveWestSecondCase :: Level -> Level
moveWestSecondCase current_lvl = Lvl _myMap1 _myBlockPositions _mySwitchPositions
    where
        _myMap1 = updateMatrix _myMap (x, y) BlockCell
        _myMap = updateMatrix (updateMatrix _oldMap (x1, y1) _myCell1) (x2, y2) _myCell2
        _myBlockPositions = [((x, y), _myCell)]
        -- coordonatele paralelipipedului dreptunghic
        (x1, y1) = fst $ head _oldBlockPositions
        (x2, y2) = fst $ last _oldBlockPositions
        -- tipurile de cell-uri pe care se afla paralelipipedul dreptunghic
        _myCell1 = snd $ head _oldBlockPositions
        _myCell2 = snd $ last _oldBlockPositions
        -- noile coordonate ale paralelipipedului dreptunghic din pozitie verticala
        y = if y1 < y2 then y1 - 1 else y2 - 1
        x = x1
        _myCell = getCharacter _oldMap (x, y)
        _oldMap = myMap current_lvl
        _oldBlockPositions = myBlockPositions current_lvl
        _mySwitchPositions = mySwitchPositions current_lvl

moveWestThirdCase :: Level -> Level
moveWestThirdCase current_lvl = Lvl _myMap1 _myBlockPositions _mySwitchPositions
    where
        _myMap1 = updateMatrix (updateMatrix _myMap (x1, y1 - 1) BlockCell) (x2, y2 - 1) BlockCell
        _myMap = updateMatrix (updateMatrix _oldMap (x1, y1) _myCell1) (x2, y2) _myCell2

        _myBlockPositions = [((x1, y1 - 1), _myCell3), ((x2, y2 - 1), _myCell4)]

        -- coordonatele paralelipipedului dreptunghic
        (x1, y1) = fst $ head _oldBlockPositions
        (x2, y2) = fst $ last _oldBlockPositions
        -- tipurile de cell-uri pe care se afla paralelipipedul dreptunghic
        _myCell1 = snd $ head _oldBlockPositions
        _myCell2 = snd $ last _oldBlockPositions

        -- tipurile de cell-uri pe care va sta paralelipipedul in noua pozitie
        _myCell3 = getCharacter _oldMap (x1, y1 - 1)
        _myCell4 = getCharacter _oldMap (x2, y2 - 1)

        _oldMap = myMap current_lvl
        _oldBlockPositions = myBlockPositions current_lvl
        _mySwitchPositions = mySwitchPositions current_lvl

moveWest :: Level -> Level
moveWest current_lvl =
    case lung == 1 of
        True -> moveWestFirstCase current_lvl
        _ -> if x1 == x2 && y2 == y1 + 1 then moveWestSecondCase current_lvl else moveWestThirdCase current_lvl
    where
        (x1, y1) = fst $ head _myBlockPositions
        (x2, y2) = fst $ last _myBlockPositions
        lung = length _myBlockPositions
        _myBlockPositions = myBlockPositions current_lvl

moveEastFirstCase :: Level -> Level
moveEastFirstCase current_lvl = Lvl _myMap1 _myBlockPositions _mySwitchPositions
    where
        _myMap1 = updateMatrix _myMap (x, y) _myCell
        _myMap = updateMatrix (updateMatrix _oldMap (x, y + 1) BlockCell) (x, y + 2) BlockCell
        _myBlockPositions = [((x, y + 1), _myCell1), ((x, y + 2), _myCell2)]
        -- coordonatele paralelipipedului dreptunghic
        (x, y) = fst $ head _oldBlockPositions
        -- tipul de cell pe care sta paralelipipedul dreptunghic in pozitie verticala
        _myCell = snd $ head _oldBlockPositions
        -- tipurile de cell-uri pe care va sta paralelipipedul in pozitie orizontala
        _myCell1 = getCharacter _oldMap (x, y + 1)
        _myCell2 = getCharacter _oldMap (x, y + 2)
        _oldMap = myMap current_lvl
        _oldBlockPositions = myBlockPositions current_lvl
        _mySwitchPositions = mySwitchPositions current_lvl

moveEastSecondCase :: Level -> Level
moveEastSecondCase current_lvl = Lvl _myMap1 _myBlockPositions _mySwitchPositions
    where
        _myMap1 = updateMatrix _myMap (x, y) BlockCell
        _myMap = updateMatrix (updateMatrix _oldMap (x1, y1) _myCell1) (x2, y2) _myCell2
        _myBlockPositions = [((x, y), _myCell)]

        -- coordonatele paralelipipedului dreptunghic
        (x1, y1) = fst $ head _oldBlockPositions
        (x2, y2) = fst $ last _oldBlockPositions
        -- tipurile de cell-uri pe care se afla paralelipipedul dreptunghic
        _myCell1 = snd $ head _oldBlockPositions
        _myCell2 = snd $ last _oldBlockPositions

        -- coordonatele viitoare ale paralelipipedului dreptunghic
        x = x1
        y = if y1 < y2 then y2 + 1 else y1 + 1
        _myCell = getCharacter _oldMap (x, y)

        _oldMap = myMap current_lvl
        _oldBlockPositions = myBlockPositions current_lvl
        _mySwitchPositions = mySwitchPositions current_lvl

moveEastThirdCase :: Level -> Level
moveEastThirdCase current_lvl = Lvl _myMap1 _myBlockPositions _mySwitchPositions
    where
        _myMap1 = updateMatrix (updateMatrix _myMap (x1, y1 + 1) BlockCell) (x2, y2 + 1) BlockCell
        _myMap = updateMatrix (updateMatrix _oldMap (x1, y1) _myCell1) (x2, y2) _myCell2

        _myBlockPositions = [((x1, y1 + 1), _myCell3), ((x2, y2 + 1), _myCell4)]

        -- coordonatele paralelipipedului dreptunghic
        (x1, y1) = fst $ head _oldBlockPositions
        (x2, y2) = fst $ last _oldBlockPositions

        -- tipurile de cell-uri pe care se afla paralelipipedul dreptunghic
        _myCell1 = snd $ head _oldBlockPositions
        _myCell2 = snd $ last _oldBlockPositions

         -- tipurile de cell-uri pe care va sta paralelipipedul in noua pozitie
        _myCell3 = getCharacter _oldMap (x1, y1 + 1)
        _myCell4 = getCharacter _oldMap (x2, y2 + 1)

        _oldMap = myMap current_lvl
        _oldBlockPositions = myBlockPositions current_lvl
        _mySwitchPositions = mySwitchPositions current_lvl

moveEast :: Level -> Level
moveEast current_lvl =
    case lung == 1 of
        True -> moveEastFirstCase current_lvl
        _ -> if x1 == x2 && y2 == y1 + 1 then moveEastSecondCase current_lvl else moveEastThirdCase current_lvl
    where
        (x1, y1) = fst $ head _myBlockPositions
        (x2, y2) = fst $ last _myBlockPositions
        lung = length _myBlockPositions
        _myBlockPositions = myBlockPositions current_lvl

move :: Directions -> Level -> Level
move direction current_lvl = 
    case direction of
        North -> activate $ moveNorth current_lvl
        South -> activate $ moveSouth current_lvl
        West -> activate $ moveWest current_lvl
        _ -> activate $ moveEast current_lvl

{-
    Va returna True dacă jocul nu este nici câștigat, nici pierdut.
    Este folosită în cadrul Interactive.
-}

winGame :: Level -> Bool
winGame current_lvl = if lung == 1 && _myCell == WinningCell then True else False
    where
        lung = length _myBlockPositions
        _myCell = snd $ head _myBlockPositions
        _myBlockPositions = myBlockPositions current_lvl

lostGame :: Level -> Bool
lostGame current_lvl = if testEmptyCellLose || testSoftLose then True else False
    where
        lung = length _myBlockPositions

        -- tipurile de cell-uri pe care se afla paralelipipedul dreptunghic
        _myCell1 = snd $ head _myBlockPositions
        _myCell2 = snd $ last _myBlockPositions

        -- blocul nu poate fi sustinut daca sub el se afla un EmptySpaceCell
        testEmptyCellLose = _myCell1 == EmptySpaceCell || _myCell2 == EmptySpaceCell
        -- blocul in pozitie verticala nu poate fi sustinut de un SoftCell
        testSoftLose = lung == 1 && _myCell1 == SoftCell

        _myBlockPositions = myBlockPositions current_lvl

continueGame :: Level -> Bool
continueGame current_lvl = if winGame current_lvl || lostGame current_lvl then False else True

{-
	Euristica este bazata pe distanta Manhattan intre pozitia block-ului si pozitia WinningCell.
-}

-- Functie manhattanDistance este preluata din lab8-doc.hs
manhattanDistance :: Position -> Position -> Int
manhattanDistance p1 p2 = difX + difY
  where
    difX = abs (x1 - x2)
    difY = abs (y1 - y2)
    (x1, y1) = p1
    (x2, y2) = p2

calculateScore :: Level -> Int
calculateScore current_lvl = manhattanDistance (x1, y1) (x2, y2)
	where
		-- o coordonata a paralelipipedului dreptunghic
        (x1, y1) = fst $ head $ myBlockPositions current_lvl
        -- (x2, y2) - coordonatele WinningCell
        row = (!!) _myMap x2
        lin2 = map (\node -> node == WinningCell) row
        idx2 = L.elemIndex True lin2
        y2 = if isNothing idx2 then y1 else fromJust idx2
        x2 = if isNothing idx then x1 else fromJust idx
        idx = L.elemIndex True lin
        lin = map (\lst -> elem WinningCell lst) _myMap 
        _myMap = myMap current_lvl

{-
    Instanțiați clasa `ProblemState` pentru jocul nostru. 
  
    Hint: Un level câștigat nu are succesori! 
    De asemenea, puteți ignora succesorii care 
    duc la pierderea unui level.
-}

instance ProblemState Level Directions where
    successors (Lvl _myMap _myBlockPositions _mySwitchPositions) = solution
        where
            moveNorthLevel = (North, move North current_lvl)
            moveSouthLevel = (South, move South current_lvl)
            moveWestLevel = (West, move West current_lvl)
            moveEastLevel = (East, move East current_lvl)

            lst = moveNorthLevel : moveSouthLevel : moveEastLevel : moveWestLevel : []

            -- verific daca current-lvl este un level castigator
            solution = case winGame current_lvl of
                        True -> []
                        _ -> filter (\pair -> (lostGame $ snd pair) == False) lst

            current_lvl = Lvl _myMap _myBlockPositions _mySwitchPositions

    isGoal = winGame

    heuristic = calculateScore
