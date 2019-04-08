package raytracing;

import math.Vector3;

public class Ray {

    private Vector3 origin;
    private Vector3 direction;

    Ray(Vector3 origin, Vector3 direction){
        this.origin = origin;
        this.direction = direction.normalized();
    }

    public Vector3 getPositionOnRay(float t){
        return Vector3.add(origin, Vector3.mul(direction, t));
    }

    public Vector3 getOrigin() { return origin; }
    public Vector3 getDirection() { return direction; }
}
