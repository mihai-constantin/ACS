
-- TIPURI DE DATE UTILIZATOR

-- type
type Age = Int
type Name = (String, String)

-- newtype
newtype Person = Person (Name, Age) deriving Show
fc :: Person
fc = Person (("Mihai", "Constantin"), 21)

-- tipuri enumerate
data Dice = S1 | S2 | S3 | S4 | S5 | S6

-- tipuri inregistrare
data Person2 = Person2 {name :: Name, age :: Age} deriving Show
fc2 :: Person2
fc2 = Person2 ("Constantin", "Stefania") 27
nume_pers = name fc2

-- tipuri recursive -> specificam cel putin un constructor intern
data Natural = Zero | Succ Natural deriving Show

-- data IntList = Nil | Cons Int IntList deriving Show

-- tipuri parametrizate
data List a = Nil | Cons a (List a) deriving Show
lst1 = Cons 1 $ Cons 2.5 $ Cons 4 Nil
lst2 = Cons "Hello" $ Cons "world!" Nil

-- laborator
type Point = (Int, Int)
p :: Point
p = (2, 3)