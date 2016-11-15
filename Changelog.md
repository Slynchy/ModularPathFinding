#ModularPathFinding Changelog
##NOTE: I hardly ever remember what I add per version, so beware of inaccuracies

#### v0.7.0
- Fixed discrepancies with Breadth-First and Depth-First
- Added Doxygen documentation

#### v0.6.0
- Added AStar Epsilon
	+ Does not yet support configurable secondary heuristics

#### v0.5.0
- Re-added AStar algorithm
- Improved base class to have more common functionality/variables
- Added support for dynamic obstructions to AStar
	+ Pending addition to other algos

#### v0.3.0
- Added Best-First algorithm
- Removed AStar algorithm, pending a rewrite

#### v0.2.0
- Added Depth-First algorithm
- Massively improved existing algorithms to be real-time
- Added DungeonGenerator sample

#### v0.1.1
- Fixed bug with AStar/Breadth-First algorithms going to negative co-ordinates (out of bounds)
- Added automatic node-map generation to Breadth-First (for just getting a path to somewhere, i.e. dungeon crawler corridor generation)
	+ Still supply an empty node map as parameter (std::vector<std::vector<NODE*>> node_map)

#### v0.1.0
- First commit
- Has the following algorithms:
	+ Regular A* (non-weighted)
	+ Breadth-First