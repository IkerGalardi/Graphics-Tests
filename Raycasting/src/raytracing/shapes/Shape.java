package raytracing.shapes;

import jdk.jshell.spi.ExecutionControl;
import math.Vector3;
import raytracing.IntersectionData;
import raytracing.Ray;

public class Shape {
    Vector3 position;

    public IntersectionData intersect(Ray ray) throws  ExecutionControl.NotImplementedException{
        throw new ExecutionControl.NotImplementedException("Intersection method not implemented");
    }

    public void setPosition(Vector3 position) { this.position = position; }
    public Vector3 getPosition() { return position; }
}
