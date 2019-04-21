package raytracing.shapes;

import math.Vector3;
import raytracing.FloatColor;
import raytracing.IntersectionData;
import raytracing.Ray;

public abstract class GeometricShape {
    Vector3 position;
    FloatColor color;

    public GeometricShape(Vector3 position, FloatColor color){
        this.position = position;
        this.color = color;
    }

    public abstract IntersectionData intersect(Ray ray);
    public abstract Vector3 getNormal(Vector3 point);

    public void setPosition(Vector3 position) { this.position = position; }
    public Vector3 getPosition() { return position; }
    public FloatColor getColor() { return color; }
}
