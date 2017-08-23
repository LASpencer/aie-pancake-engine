AI for Games Project by L. Andrew Spencer 2017


I. USE
---------

Controls:
HOLD LEFT MOUSE BUTTON	: Blue tanks move towards cursor if possible
F			: Toggle showing FPS
P			: Toggle showing tank paths
N			: Toggle showing map nodes
B			: Toggle showing behaviours
ESC			: Quit game
`(Grave key)		: Toggle showing hitboxes

Tank paths are shown as purple lines. If the tank isn't performing a behaviour that uses 
pathfinding, these will show the last path used

Behaviours are shown for a specific tank which has a behaviour tree containing logged nodes,
showing text based on the behaviours tried that frame. The nodes are shown in the order they
returned a result. Success is indicated by blue text, failure by red text, and a running behaviour
by green text.
The tank being followed is highlighted with a purple circle.

Tanks will move around the map. If they get close enough to an enemy tank, they will fire at it, with a
chance of killing the other tank. Moving uses fuel, which is replenished by returning to the tank's base.
If a tank runs out of fuel, it will be unable to move, and eventually dies. Dead tanks respawn at their base.

The map contains green open squares, yellow difficult squares (with slower movement) and red impassable squares.

II. DESIGN
-----------


III. ATTRIBUTIONS
--------------

Tank sprites from "Top Down Painted Tanks" by Irina Mir
Available at https://opengameart.org/content/top-down-painted-tanks
Used under CC BY 3.0 license https://creativecommons.org/licenses/by/3.0/