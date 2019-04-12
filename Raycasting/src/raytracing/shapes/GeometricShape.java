package raytracing.shapes;

import math.Vector3;
import raytracing.IntersectionData;
import raytracing.Ray;

import java.awt.*;

public abstract class GeometricShape {
    Vector3 position;
    Color color;

    public GeometricShape(Vector3 position, Color color){
        this.position = position;
        this.color = color;
    }

    public abstract IntersectionData intersect(Ray ray);

    public void setPosition(Vector3 position) { this.position = position; }
    public Vector3 getPosition() { return position; }
    public Color getColor() { return color; }
}
