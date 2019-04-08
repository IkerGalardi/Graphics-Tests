package raytracing.shapes;

import jdk.jshell.spi.ExecutionControl;
import math.Vector3;
import raytracing.IntersectionData;
import raytracing.Ray;

public class Sphere extends Shape {
    private float radius;

    @Override
    public IntersectionData intersect(Ray ray) throws ExecutionControl.NotImplementedException {
        IntersectionData intersectionData = new IntersectionData();

        // The coefficient of the extended sphere equation: ax² + bx + c = 0
        float a = Vector3.dot(ray.getDirection(), ray.getDirection());
        float b = Vector3.dot(ray.getDirection(), Vector3.sub(ray.getOrigin(), position));
        float c = Vector3.dot(Vector3.sub(ray.getOrigin(), position), Vector3.sub(ray.getOrigin(), position));

        // Try to solve the equation and set the intersection data (get the minimum positive "t"
        float inSqrt =  b * b - 4 * a * c;
        if (inSqrt < 0){ // No solution to the equation
            intersectionData.setHasIntersected(false);
        } else if (inSqrt > 0){ // Two solutions (take the smallest positive)
            float t = (float)Math.min((b + Math.sqrt(inSqrt)) / (2 * a), (b - Math.sqrt(inSqrt)) / (2 * a));

            if (t > 0){
                intersectionData.setHasIntersected(true);
                intersectionData.setHitPosition(ray.getPositionOnRay(t));
            }else{
                intersectionData.setHasIntersected(false);
            }
        } else{ // Just one solution, add if its positive
            float t = -b / (2 * a);
            if (t > 0){
                intersectionData.setHasIntersected(true);
                intersectionData.setHitPosition(ray.getPositionOnRay(t));
            }else{
                intersectionData.setHasIntersected(false);
            }
        }

        return intersectionData;
    }

    public float getRadius() { return radius; }
    public void setRadius(float radius) { this.radius = radius; }
}
