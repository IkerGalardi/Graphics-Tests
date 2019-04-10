package raytracing.shapes;

import math.Vector3;
import raytracing.Ray;

public class Sphere extends GeometricShape {
    private float radius;

    public Sphere(Vector3 position, float radius){
        super(position);
        this.radius = radius;
    }

    @Override
    public Vector3 intersect(Ray ray){
        Vector3 intersectionData;
        Vector3 o = Vector3.sub(ray.getOrigin(), position);
        Vector3 d = ray.getDirection();

        // The coefficients of the equation that needs to be solved to get t: ax² + bx + c
        float a = Vector3.dot(d, d);
        float b = 2 * Vector3.dot(o, d); // o.getX() * d.getX() + o.getY() * d.getY() + o.getZ() * d.getZ()
        float c = Vector3.dot(o, o) - (radius * radius);//o.getX() * o.getX() + o.getY() * o.getY() + o.getZ() * o.getZ() - (radius * radius);
        System.out.println("a = " + a + ", b = " + b + ", c = " + c);

        float inSqrt = b * b - 4 * a * c;
        System.out.println("sqrt of " + inSqrt);
        if(inSqrt == 0){
            intersectionData = ray.getPositionOnRay(-b/(2 * a));
        } else if(inSqrt > 0){
            float tPlus = (-b + (float)Math.sqrt(inSqrt))/(2 * a); System.out.println("t_1 = " + tPlus);
            float tNeg = (-b - (float)Math.sqrt(inSqrt))/(2 * a); System.out.println("t_2 = " + tNeg);
            float t = Math.min(tPlus, tNeg);
            System.out.println("t = " + t);
            intersectionData = ray.getPositionOnRay(t);
        } else { // inSqrt < 0
            intersectionData = Vector3.zero();
        }

        return intersectionData;
    }

    public float getRadius() { return radius; }
    public void setRadius(float radius) { this.radius = radius; }
}
