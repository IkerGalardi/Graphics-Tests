package raytracing;

import math.Vector3;

public class IntersectionData {
    private boolean hasIntersected;
    private Vector3 hitPosition;

    public IntersectionData() {}
    public IntersectionData(boolean hasIntersected, Vector3 hitPosition){
        this.hasIntersected = hasIntersected;
        this.hitPosition = hitPosition;
    }

    public void setHasIntersected(boolean hasIntersected) { this.hasIntersected = hasIntersected;}
    public void setHitPosition(Vector3 hitPosition) { this.hitPosition = hitPosition; }
    public boolean getHasIntersected() { return hasIntersected; }
    public Vector3 getHitPosition() { return hitPosition; }
}
