#ModularPathFinding Changelog
##NOTE: I hardly ever remember what I add per version, so it may be inaccurate

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