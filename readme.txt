AI for Games Project by L. Andrew Spencer 2017


I. USE
---------

Controls:
HOLD LEFT MOUSE BUTTON	: Blue tanks move towards cursor if possible
F			: Toggle showing FPS
B			: Toggle showing behaviours
N			: Toggle showing tank paths
M			: Toggle showing map nodes
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

DECISION MAKING TECHNIQUES:

Tanks are controlled using a behaviour tree. Each tank has its own instance of the behaviour tree, so that selector 
and sequence behaviors can store pending behaviours.
After checking that the tank is actually a tank, the following behaviours are tried in order, and the first to 
succeed is the selected behaviour.

Death
A question behaviour, isDead, is used to check if the tank is dead. If so, the tank waits until it's been dead 
for three seconds and respawns.

Flee Danger
The tank checks its neighbours (tanks within a certain distance) and compares the number of friendly and enemy 
tanks. If outnumbered by a great enough proportion (3 to 2), the tank flees from the enemy tanks.

Attack Enemy
The tank tries to attack its target, returning success if it is within range and still alive. If so, there is a 
20% chance of killing the target, and the tank tries to match velocities with it so as to remain in firing range.

Refuel
The tank checks if it's fuel is too low. This is defined as being under 25% of max fuel, but could be changed to 
a heuristic estimating fuel required to return to base (or another fuel supply). If so, one of two behaviours is 
selected. If the tank is already at its base, the Refuel behavious starts, and continues running until the tank 
has enough fuel. This is to avoid the tank getting stuck repeatedly refueling just enough to leave, and immediately 
returning.
If not, the tank pathfinds to its base, and follows that path.

Go To Mouse Cursor
This behavior first checks the tank is on the Blue team, controlled by the player. If so, and the player is holding 
the mouse button on a reachable location, the tank pathfinds to that location. This controls all blue tanks not 
performing some earlier behaviour.

Chase Target
The tank checks if the enemy is close enough and if so pursues it.

Flock and Wander
If no other behaviours succeeded, the tank first applies steering forces to flock with friendly tanks. A Wandering 
force is also added to the tank, so if flocking doesn't use all its force, the tank will move around randomly.


PATHFINDING TECHNIQUES:

Pathfinding uses the A* algorithm. The game world is divided into a grid of nodes, which are open, difficult, or 
impassable. Nodes that aren't impassable are connected to their neighbours, with the cost of an edge depending on 
the node's types, and whether it's a diagonal or horizontal connection. Diagonally adjacent nodes are not connected 
if an impassable node is between them.

A straight line distance heuristic is used, however the pathfinding method can be passed another heuristic as an 
argument.

When a tank follows a path, it moves towards the node on top of the stack until it is reached, then seeks the 
next node, and on reaching the final node moves towards its goal location within that node.

The main limitation to pathfinding is that steering around other tanks has not been fully implemented. A tank can 
get stuck in a traffic jam, or be blocked by an immobile or dead tank. 


STEERING BEHAVIOURS:

This application uses weighted truncated running sum to combine steering forces. Each update, based on the behaviours 
called, various steering forces are added to a vector (with a weight), and added together until the running total 
has a greater magnitude than the maximum total. 

Regardless of behaviours, by default the tanks have steering forces to stay in bounds and avoid impassable terrain. 
Avoiding terrain is done through casting a ray ahead of the tank, and checking if it touches impassable terrain. If 
so, based on what side of the terrain square it hit, a force is applied to the tank moving it away from the square.
Most behaviours add one or two other forces to the tank. For instance, the GoToBase and MoveToHeldMouse behaviours 
add a seek or arrival force to follow a path, and a small separation force to keep the tanks apart.

The combined Flock and Wander behaviour adds four forces in total to the tank. Flocking adds separation, alignment, 
and cohesion forces to the tanks. Wander is added after these, giving it a lower priority.

One limitation with the forces is the Separation Force calculates the repulsion force as the sum of the displacement 
from each other neighbour. This means that a tank far away from the others will experience a much stronger repulsion.
Another repulsion force, which decreases with distance, could be useful, although it would probably be more 
expensive.


III. ATTRIBUTIONS
--------------

Tank sprites from "Top Down Painted Tanks" by Irina Mir
Available at https://opengameart.org/content/top-down-painted-tanks
Used under CC BY 3.0 license https://creativecommons.org/licenses/by/3.0/