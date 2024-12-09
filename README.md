### Display a cubic bezier curve

Goal : adding N points evenly spaced on a curve

#### Step 1 : Estimation of the length of the bezier curve
- Compute each points for the bezier curve, get the length between a point and the older one, and sum with what we have. Call the length L

#### Step 2 : Adding the spaced points
- Recompute the bezier curve, withkeeping track of the length of the current point and the oldest point. When we have the length wich is more than L/N, we add a point
