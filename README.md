Class BulletManager - it's multithreading manager of calculating flight paths of bullets with the ricochets.
The walls are defined in the list of segments that contain the coordinates of two points on the two-dimensional space.
After hitting a bullet in the wall, the wall is destroyed (removed from the list).
Function Update (calculating flight paths) is called from the main thread, the function Fire (add bullets in a list for later calculation) - from random threads.
