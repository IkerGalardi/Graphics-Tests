package raytracing.shapes;

import math.Vector3;
import raytracing.IntersectionData;
import raytracing.Ray;

import java.awt.*;

public class Sphere extends GeometricShape {
    private float radius;

    public Sphere(Vector3 position, Color color, float radius){
        super(position, color);
        this.radius = radius;
    }

    @Override
    public IntersectionData intersect(Ray ray) {
        IntersectionData intersectionData = new IntersectionData(Vector3.zero(), Float.MAX_VALUE, false);
        Vector3 o = Vector3.sub(ray.getOrigin(), position);
        Vector3 d = ray.getDirection();

        // The coefficients of the equation that needs to be solved to get t: ax² + bx + c
        float a = Vector3.dot(d, d);
        float b = 2 * Vector3.dot(o, d); // 2 * (o.getX() * d.getX() + o.getY() * d.getY() + o.getZ() * d.getZ())
        float c = Vector3.dot(o, o) - (radius * radius);//o.getX() * o.getX() + o.getY() * o.getY() + o.getZ() * o.getZ() - (radius * radius);

        float inSqrt = b * b - 4 * a * c;
        if(inSqrt == 0){
            float t = -b/(2 * a);
            intersectionData.setHitPosition(ray.getPositionOnRay(t));
            intersectionData.setDepth(t);
            intersectionData.setHasHit(true);
        } else if(inSqrt > 0){
            float tPlus = (-b + (float)Math.sqrt(inSqrt))/(2 * a);
            float tNeg = (-b - (float)Math.sqrt(inSqrt))/(2 * a);
            float t = Math.min(tPlus, tNeg);
            intersectionData.setHitPosition(ray.getPositionOnRay(t));
            intersectionData.setDepth(t);
            intersectionData.setHasHit(true);
        } else {
            intersectionData.setHasHit(false);
            intersectionData.setDepth(Float.MAX_VALUE);
            intersectionData.setHitPosition(new Vector3(Float.MAX_VALUE, Float.MAX_VALUE, Float.MAX_VALUE));

        }

        return intersectionData;
    }

    public float getRadius() { return radius; }
    public void setRadius(float radius) { this.radius = radius; }
}
