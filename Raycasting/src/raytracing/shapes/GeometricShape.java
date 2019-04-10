package raytracing.shapes;

import math.Vector3;
import raytracing.Ray;

public abstract class GeometricShape {
    Vector3 position;

    public GeometricShape(Vector3 position){
        this.position = position;
    }

    public abstract Vector3 intersect(Ray ray);

    public void setPosition(Vector3 position) { this.position = position; }
    public Vector3 getPosition() { return position; }
}
