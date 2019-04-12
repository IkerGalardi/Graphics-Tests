package raytracing;

import math.Vector3;

public class IntersectionData {
    private Vector3 hitPosition;
    private float depth;
    private boolean hasHit;

    public IntersectionData(Vector3 hitPosition, float depth, boolean hasHit){
        this.setHitPosition(hitPosition);
        this.setDepth(depth);
    }

    public void setHasHit(boolean hasHit) { this.hasHit = hasHit; }
    public boolean getHasHit() {return hasHit; }
    public Vector3 getHitPosition() {
        return hitPosition;
    }
    public void setHitPosition(Vector3 hitPosition) {
        this.hitPosition = hitPosition;
    }
    public float getDepth() {
        return depth;
    }
    public void setDepth(float depth) {
        this.depth = depth;
    }
}
