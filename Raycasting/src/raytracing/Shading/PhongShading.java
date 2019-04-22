package raytracing.Shading;

import math.Vector3;
import raytracing.FloatColor;
import raytracing.IntersectionData;
import raytracing.Lighting.Light;
import raytracing.Ray;
import raytracing.shapes.GeometricShape;

import java.awt.*;
import java.util.ArrayList;

public class PhongShading extends Shader{

    private ArrayList<Light> lights;
    private ArrayList<GeometricShape> geometricShapes;

    Vector3 normal, position;
    FloatColor objectColor;

    public void setAttributes(Vector3 normal, Vector3 position, FloatColor objectColor){
        this.normal = normal;
        this.position = position;
        this.objectColor = objectColor;
    }

    public void setupShader(ArrayList<Light> lights, ArrayList<GeometricShape> geometricShapes) {
        this.lights = lights;
        this.geometricShapes = geometricShapes;
    }

    @Override
    public Color calculateColor() {
        float intensity = calculateIntensityInPoint();
        FloatColor color = FloatColor.mul(intensity, objectColor);
        System.out.println("(" + color.getR() + ", " + color.getG() + ", " + color.getB() +")");
        System.out.println(color.toColor().toString());
        return color.toColor();
    }

    private float calculateIntensityInPoint(){
        float intensity = 0.1f;
        for (Light light : lights) {
            // Check if there is any shadow, if not add the intensity
            Vector3 checkVector = light.getShadowCheckVector(position);
            if(isShadow(new Ray(position, checkVector))){
                System.out.println("true");
                intensity += light.calculateLightIntensity(position, normal);
            }
        }

        System.out.println("intensity: " + intensity);
        return Math.min(1, intensity);
    }

    private boolean isShadow(Ray ray){
        boolean isShadow = true;
        for(GeometricShape shape : geometricShapes){
            IntersectionData intersectionData = shape.intersect(ray);
            isShadow = isShadow && intersectionData.getHasHit();
        }

        return !isShadow;
    }
}
