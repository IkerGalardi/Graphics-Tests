package raytracing.shapes;

import math.Vector3;
import raytracing.IntersectionData;
import raytracing.Ray;

import java.awt.*;
import java.util.Vector;

public class InfinitePlane extends GeometricShape {
    Vector3 normal;

    public InfinitePlane(Vector3 position, Color color, Vector3 normal){
        super(position, color);
        this.normal = normal;
    }

    public IntersectionData intersect(Ray ray){
        IntersectionData intersectionData = new IntersectionData(Vector3.zero(), Float.MAX_VALUE, false);
        if(Vector3.dot(ray.getDirection(), normal) != 0){
            // There is an intersection, calculate and return it
            Vector3 dir = ray.getDirection();
            Vector3 origin = ray.getOrigin();

            intersectionData.setDepth(Vector3.dot(Vector3.sub(position, origin), normal)/(Vector3.dot(normal, dir)));
            intersectionData.setHitPosition(ray.getPositionOnRay(intersectionData.getDepth()));
            intersectionData.setHasHit(true);
        }
        return intersectionData;
    }
}
