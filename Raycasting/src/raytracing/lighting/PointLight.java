package raytracing.lighting;

import math.Vector3;

public class PointLight extends Light {
    float intensity;

    public PointLight(Vector3 position, float intensity){
        super(position);
        this.intensity = intensity;
    }

    public float calculateLightIntensity(Vector3 point, Vector3 normal){
        float distance = Vector3.sub(position, point).length();

        return intensity/(distance * distance);
    }

    public Vector3 getShadowCheckVector(Vector3 point){
        return Vector3.sub(position, point);
    }

    public float getIntensity() {
        return intensity;
    }

    public void setIntensity(float intensity) {
        this.intensity = intensity;
    }
}
