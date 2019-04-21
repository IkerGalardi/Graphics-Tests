package raytracing.Lighting;

import math.Vector3;

public class DirectionalLight extends Light {
    private Vector3 direction;
    private float intensity;

    public DirectionalLight(Vector3 position, Vector3 direction, float intensity){
        super(position);
        this.direction = direction.normalized();
        this.intensity = intensity;
    }

    @Override
    public float calculateLightIntensity(Vector3 point) {
        return Math.abs(Math.min(1, intensity)); // Clamp the value between 0 and 1
    }

    @Override
    public Vector3 getShadowCheckVector(Vector3 point) {
        return Vector3.negative(direction);
    }

    public Vector3 getDirection() {
        return direction;
    }

    public void setDirection(Vector3 direction) {
        this.direction = direction;
    }

    public float getIntensity() {
        return intensity;
    }

    public void setIntensity(float intensity) {
        this.intensity = intensity;
    }
}
