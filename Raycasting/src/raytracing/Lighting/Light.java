package raytracing.Lighting;

import math.Vector3;

public abstract class Light {
    private Vector3 position;

    public Light(Vector3 pos){
        this.position = pos;
    }

    public abstract float calculateLightIntensity(Vector3 point, Vector3 normal);
    public abstract Vector3 getShadowCheckVector(Vector3 point);
}
