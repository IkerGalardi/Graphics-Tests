package raytracing;

import math.Vector3;

public class Ray {

    private Vector3 origin;
    private Vector3 direction;

    public Ray(Vector3 origin, Vector3 direction){
        this.origin = origin;
        this.direction = direction.normalized();
    }

    public Vector3 getPositionOnRay(float t){
        if(t < 0){
            System.out.println("Negative t");
            return Vector3.zero();
        }
        return Vector3.add(origin, Vector3.mul(direction, t));
    }

    public Vector3 getOrigin() { return origin; }
    public Vector3 getDirection() { return direction; }

    public String toString(){
        return "Origin: " + origin.toString() + "; Direction: " + direction.toString();
    }
}
