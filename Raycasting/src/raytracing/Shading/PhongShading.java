package raytracing.Shading;

import math.Vector3;
import raytracing.FloatColor;
import raytracing.Lighting.Light;

import java.awt.*;
import java.util.ArrayList;

public class PhongShading extends Shader{

    private ArrayList<Light> lights;

    Vector3 normal, position;
    FloatColor objectColor;

    public void setAttributes(Vector3 normal, Vector3 position, FloatColor objectColor){
        this.normal = normal;
        this.position = position;
        this.objectColor = objectColor;
    }

    @Override
    public Color calculateColor() {
        float intensity = calculateIntensityInPoint();
        FloatColor color = FloatColor.mul(intensity, objectColor);
        return color.toColor();
    }

    private float calculateIntensityInPoint(){
        float intensity = 0.0f;
        for (Light light : lights) {
            intensity += light.calculateLightIntensity(position);
        }

        return Math.min(1, intensity);
    }
}
