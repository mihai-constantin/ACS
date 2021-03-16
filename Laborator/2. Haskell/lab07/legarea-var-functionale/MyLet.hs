module MyLet where

import Data.List
import Data.Word
import Data.Bits
import Data.Char
import System.Random hiding (randoms)

p = let
		x = y + 1
		y = 2
		(z, t) = (2, 5)
		f n = n * y
	in (x + y, f 3, z + t)

-- naturals = iter 0
-- 	where
-- 		iter x = x : iter (x + 1)

-- naturals = [0 ..]

-- naturals = iterate (\x -> x + 1) 0

