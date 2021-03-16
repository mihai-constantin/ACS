import Data.Foldable

type Age = Int
type Name = (String,String) 
names :: [Name] 
names = [("Frederic","Chopin"), ("Antonio", "Vivaldi"), ("Maurice", "Ravel")]

newtype Person = Person (Name, Age) deriving Show
fc :: Person
fc = Person (("Frederic","Chopin"), 209)

data Dice = S1 | S2 | S3 | S4 | S5 | S6 deriving (Eq, Ord, Enum)

data Person2 = Person2 {name :: Name, age :: Age} deriving (Read, Show)
fc2 :: Person2
fc2 = Person2 ("Frederic","Chopin") 209
composer = name fc2

data Natural = Zero | Succ Natural deriving Show
--data IntList = Nil | Cons Int IntList deriving Show

data List a = Nil | Cons a (List a) deriving Show
lst1 = Cons 1 $ Cons 2.5 $ Cons 4 Nil -- :t lst1 => lst1 :: List Double
lst2 = Cons "Hello " $ Cons "world!" Nil

myElem _ [] = False
myElem a (x:xs) = a == x || myElem a xs

--myElem2 :: (a -> b -> Bool) -> a -> [b] -> Bool
myElem2 :: (a -> a -> Bool) -> a -> [a] -> Bool
myElem2 _ _ [] = False
myElem2 eq a (x:xs) = eq a x || myElem2 eq a xs

instance Show Dice where
	show S1 = "[·]"
	show S2 = "[:]"
	show S3 = "[·:]"
	show S4 = "[::]"
	show S5 = "[:·:]"
	show S6 = "[:::]"
	
class Valuable a where
	value :: a -> Int
	
instance Valuable Dice where
	value S1 = 1
	value S2 = 2
	value S3 = 3
	value S4 = 4
	value S5 = 5
	value S6 = 6
	
--rollSum :: (Dice, Dice) -> Int
rollSum :: (Valuable a, Valuable b) => (a, b) -> Int
rollSum (x, y) = value x + value y

myLen lst
	| lst == [] = 0
	| otherwise = 1 + myLen (tail lst)
	
myLen2 lst
	| null lst = 0
	| otherwise = 1 + myLen2 (tail lst)
	
class Container t where
	contents :: t a -> [a]
	
instance Container [] where
	contents = id

	
instance Container List where
	contents Nil = []
	contents (Cons a lst) = a : contents lst


ex1 = fmap (+1) (Just 5)
ex2 = fmap (+1) (+1) 2
ex3 = fmap (+1) (1,2)
ex4 = Data.Foldable.foldl (+) 10 (1,2)

{-
eq :: a -> a -> Bool
eq x y = x == y
-}

{-
eq :: (Eq a, Eq b) => a -> b -> Bool
eq x y = x == y
-}	