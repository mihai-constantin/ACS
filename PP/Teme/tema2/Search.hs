-- TEMA 2 | CONSTANTIN MIHAI | 321CD

{-# OPTIONS_GHC -Wall #-}
{-# LANGUAGE MultiParamTypeClasses #-}

module Search where

import ProblemState

import qualified Data.List as L
import Data.Maybe

{-
    Tipul unei nod utilizat în procesul de căutare. Recomandăm reținerea unor
    informații legate de:

    * stare;
    * acțiunea care a condus la această stare;
    * nodul părinte, prin explorarea căruia a fost obținut nodul curent;
    * adâncime
    * copiii, ce vor desemna stările învecinate
-}

data Node s a = Node
	{ myState :: s
	, myAction :: Maybe a
	, myParent :: Maybe (Node s a)
	, myDepth :: Int
	, myChildren :: [Node s a]
	} deriving (Eq, Ord, Show)

{-
    Întoarce starea stocată într-un nod.
-}

nodeState :: Node s a -> s
nodeState node = myState node

{-
    Generarea întregului spațiu al stărilor 
    Primește starea inițială și creează nodul corespunzător acestei stări, 
    având drept copii nodurile succesorilor stării curente.
-}

searchChildren :: (ProblemState s a) => s -> Int -> Node s a -> [Node s a] -> [Node s a]
searchChildren _myState _myDepth _node _children = 
	if length mySuccessors == 0
		then []
		else levelChildren ++ _children
	where
		newDepth = 1 + _myDepth
		levelChildren = map (\pair -> Node (snd pair) (Just $ fst pair) (Just _node) 
			newDepth (searchChildren (snd pair) newDepth (Node (snd pair) (Just $ fst pair) (Just _node) newDepth []) [])) 
			mySuccessors
		mySuccessors = successors _myState

createStateSpace :: (ProblemState s a) => s -> Node s a
createStateSpace _myState = root
	where
		root = Node _myState Nothing Nothing 0 _myChildren
		_myChildren = searchChildren _myState 0 root []

{-
    Ordonează întreg spațiul stărilor după euristica din ProblemState. 
    Puteți folosi `sortBy` din Data.List.
-}

orderStateSpace :: (ProblemState s a) => Node s a -> Node s a
orderStateSpace root = _newNode
	where
		_newNode = Node _myState _myAction _myParent _myDepth 
				(map (\node -> Node (myState node) (myAction node) (myParent node) (myDepth node) (map orderStateSpace (myChildren node))) _myOrderedChildren)

		_myState = myState root
		_myAction = myAction root
		_myParent = myParent root
		_myDepth = myDepth root

		_myOrderedChildren = L.sortBy _comp _myChildren
		_comp node1 node2 = compare (heuristic (myState node1)) (heuristic (myState node2))
		_myChildren = myChildren root

{-
    Întoarce lista nodurilor rezultate prin parcurgerea limitată în adâncime
    a spațiului stărilor, pornind de la nodul dat ca parametru.

    Pentru reținerea stărilor vizitate, recomandăm Data.Set. Constrângerea
    `Ord s` permite utilizarea tipului `Set`.
-}

limitedDfs :: (ProblemState s a, Ord s, Ord a)
           => Node s a    -- Nodul stării inițiale
           -> Int         -- Adâncimea maximă de explorare
           -> [Node s a]  -- Lista de noduri

limitedDfs root maxDepth = limitedDfsHelper root [] maxDepth

limitedDfsHelper :: (ProblemState s a, Ord s, Ord a)
	=> Node s a 	-- Nodul starii initiale
	-> [Node s a]	-- Lista de noduri
	-> Int 			-- Adâncimea maximă de explorare
	-> [Node s a]	-- Lista de noduri

-- Sursa de inspiratie: https://stackoverflow.com/questions/12739028/dfs-implementation-in-haskell
limitedDfsHelper current visited _myDepth =
    foldl (\_visited next -> if elem (myState next) _stateVisited then _visited else limitedDfsHelper next _visited _myDepth)
           (visited ++ [current]) _myChildren
    where
    	_stateVisited = map (\node -> myState node) visited

    	_myChildren = filter (\node -> myDepth node <= _myDepth) $ myChildren current

{-
	Creeaza o lista cu nodurile intermediare pana cand gasim un nod cu starea cautata, 
	i.e. isGoal $ myState node == True. Foloseste limitedDfs.	
-}
createNodes :: (ProblemState s a, Ord s, Ord a)
		=> Node s a
		-> Int
		-> [Node s a]

createNodes root maxDepth = 
	if lung == 0
		then current_solution ++ (createNodes root (maxDepth + 1))
		else current_solution
	where
		lung = length lst
		lst = filter (\node -> fst node) $ map (\node -> (isGoal (myState node), node)) current_solution
		current_solution = limitedDfs root maxDepth

{-
    Explorează în adâncime spațiul stărilor, utilizând adâncire iterativă,
    pentru determinarea primei stări finale întâlnite.

    Întoarce o perche între nodul cu prima stare finală întâlnită și numărul
    de stări nefinale vizitate până în acel moment.
-}

iterativeDeepening :: (ProblemState s a, Ord s, Ord a)
    => Node s a         -- Nodul stării inițiale
    -> (Node s a, Int)  -- (Nod cu prima stare finală,
                        --  număr de stări nefinale vizitate)

-- Sursa de inspiratie : https://stackoverflow.com/questions/4272791/how-to-find-the-index-of-an-element-in-a-list
iterativeDeepening root = (_myGoal, idxGoal)
	where
		idxGoal = fromJust $ L.elemIndex True lst
		lst = map (\node -> isGoal (myState node)) nodes
		nodes = createNodes root 0
		_myGoal = head $ filter (\node -> isGoal (myState node)) nodes

{-
    Pornind de la un nod, reface calea către nodul inițial, urmând legăturile
    către părinți.

    Întoarce o listă de perechi (acțiune, stare), care se încheie în starea
    finală, dar care EXCLUDE starea inițială.
-}

{-
	Determina parintele unui nod. 
	Intoarce nodul daca acesta nu are parinte.
-}

findParent :: Node s a -> Node s a
findParent node = 
	if isNothing $ myParent node
		then node
		else fromJust $ myParent node

stopIterate :: Node s a -> Bool
stopIterate node = 
	if isNothing $ myParent node
		then False
		else True

extractPath :: Node s a -> [(a, s)]
extractPath node = reverse $ map (\_node -> (fromJust $ myAction _node, myState _node)) finiteList
	where
		finiteList = takeWhile stopIterate infiniteList
		infiniteList = iterate findParent node
{-
    Pornind de la o stare inițială, se folosește de iterativeDeepening pentru 
    a găsi prima stare finală și reface calea către nodul inițial folosind 
    extractPath. 
  
    Întoarce o listă de perechi (acțiune, stare), care se încheie în starea
    finală, dar care EXCLUDE starea inițială.
-}

solve :: (ProblemState s a, Ord s, Ord a)
      => s          -- Starea inițială de la care se pornește 
      -> Bool       -- Dacă să folosească sau nu euristica dată 
      -> [(a, s)]   -- Lista perechilor
solve _myInitialState _heuristic = extractPath $ fst _myFinalState
	where
		_myInitialStateSpace = if _heuristic
							then orderStateSpace $ createStateSpace _myInitialState 
							else createStateSpace _myInitialState
		_myFinalState = iterativeDeepening _myInitialStateSpace

{-
    Poate fi utilizată pentru afișarea fiecărui element al unei liste
    pe o linie separată.
-}

printSpacedList :: Show a => [a] -> IO ()
printSpacedList = mapM_ (\a -> print a >> putStrLn (replicate 20 '*'))