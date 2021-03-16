import Data.List 
import Debug.Trace

------PATTERN MATCHING-----
fib :: Int -> Int
fib 0 = 0
fib 1 = 1
fib n = fib (n-2) + fib (n-1)

sumL :: [Int] -> Int
sumL [] = 0
sumL (x:xs) = x + sumL xs

--sumP :: (Int, Int) -> Int
sumP (x,y) = x + y

--ordered :: [Int] -> Bool
ordered [] = True
ordered [x] = True
ordered (x:xs@(y:rest)) = x <= y && ordered xs

--ordered2 :: [Int] -> Bool
ordered2 (x:xs@(y:rest)) = x <= y && ordered2 xs
ordered2 _ = True

--nu funcționează
--eq x x = True -- dă eroare Conflicting definitions for `x'
--eq _ _ = False

------COMPUNERE DE FUNCȚII-----
--myLast :: [a] -> a
myLast = head . reverse -- myLast [1..5] = 5
myMin :: Ord a => [a] -> a
myMin = head . sort     -- myMin [2,4,1,2,3,6,2] = 1
myMax :: Ord a => [a] -> a
myMax = myLast . sort   -- myMax [2,4,1,2,3,6,2] = 6

------OPERATORUL $-----
--de încercat în terminal [(1,2),(3,4),(5,6),(7,8)]
--take 4 $ filter (odd . fst) $ zip [1..] [2..]

------EXPRESII CONDIȚIONALE-----
--uglySum :: [Int] -> Int
uglySum l = if null l then 0 
                      else head l + uglySum (tail l)
							 
--myTranspose :: [[a]] -> [[a]]
myTranspose matrix = case (head matrix) of
	[] -> []
	_ -> map head matrix : myTranspose (map tail matrix)
	
--allEqual :: Eq a => a -> a-> a-> Bool
allEqual a b c
	| a==b = b==c
	| otherwise = False 
	
------LEGARE LOCALĂ------
myFoldl :: (b -> a -> b) -> b -> [a] -> b
myFoldl f acc [] = acc
myFoldl f acc (x:xs) = 
	let 
		newAcc = f acc x -- în Haskell, funcția lui foldl primește acc ca parametru stâng
	in myFoldl f newAcc xs

myFoldr :: (a -> b -> b) -> b -> [a] -> b
myFoldr f acc [] = acc 
myFoldr f acc (x:xs) = f x rightResult
	where rightResult = myFoldr f acc xs 
	
exwhere = a + b + c + d
	where
	a = 2+5
	(b, c) = head (zip [1..] [2..])
	d = f 5
		where f = (+1)
	

------EVALUARE LENEȘĂ------
f x = trace "x" 2*x
g x = f 2 + f 2 -- se evaluează de 2 ori la apelul g 5
h x = x*x*x     -- evaluare leneșă la apelul h (f 2)

------FLUXURI------
naturals = let loop n = n : loop (n+1) in loop 0
ones = 1 : ones
fibonacci = 0 : 1 : zipWith (+) fibonacci (tail fibonacci)
evens = filter even naturals

test1 = let loop n = (1/n) : loop (n+1) in loop 1
test2 = 1 : zipWith (*) test1 (tail test1)

------LIST COMPREHENSIONS------
lc1 = [ (x,y,z) | x<-[1..3], y<-[1..4], x<y, let z = x+y, odd z ]
fibo = 0 : 1 : [ x+y | (x,y) <- zip fibo (tail fibo) ]
mapLC f l = [ f x | x<-l ]
filterLC p l = [ x | x<-l, p x ]

qsort [] = []
qsort (x:xs) = 
	qsort [ y | y<-xs, y<=x] ++
	[x] ++
	qsort [ y | y<-xs, y>x]
	
------CONSTRUCTORI DE TIP------
a :: (,) Bool Char -- normal era (Bool, Char), scriem așa pentru a observa comportamentul de funcție al constructorilor de tip
a = (True, 'a')
b :: [] Int -- normal era [Int]
b = [1,2,3]
c :: (->) Int Int -- normal era Int -> Int
c = (+1)

------TIPURI DEFINITE DE UTILIZATOR------
data RH = Pos | Neg                -- doar constructori nulari
data ABO = O | A | B | ABO         -- doar constructori nulari
data BloodType = BloodType ABO RH  -- constructor extern

data Natural = Zero | Succ Natural -- constructor nular și constructor intern
							deriving Show -- face posibilă afișarea valorilor tipului
unu = Succ Zero
doi = Succ unu
trei = Succ doi		

addN :: Natural -> Natural -> Natural -- arată exact ca axiomele
addN Zero n = n
addN (Succ m) n = Succ (addN m n)					

------TIPURI PARAMETRIZATE------
--findMaxEvenSum :: [[Int]] -> Maybe Int
findMaxEvenSum [] = Nothing
findMaxEvenSum (l:ls)
	| even lsum = case findMaxEvenSum ls of
							Just s -> Just (max lsum s)
							_ -> Just lsum
	| otherwise = findMaxEvenSum ls
		where lsum = sumL l
		
------EXPRESII DE TIP------
--wrongMyMap :: (a -> b) -> [a] -> [b]
wrongMyMap f [] = []
wrongMyMap f (x:xs) = f (f x) : wrongMyMap f xs

myMap :: (a -> b) -> [a] -> [b]
myMap f [] = []
myMap f (x:xs) = f x : myMap f xs







	