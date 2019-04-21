package raytracing;

import java.awt.*;

public class FloatColor
{
    private float r;
    private float g;
    private float b;

    public FloatColor(float r, float g, float b){
        this.r = r;
        this.g = g;
        this.b = b;
    }

    public static FloatColor add(FloatColor l, FloatColor r){
        return new FloatColor(l.getR() + r.getR(), l.getG() + r.getG(), l.getB() + r.getB());
    }

    public static FloatColor sub(FloatColor l, FloatColor r){
        return new FloatColor(l.getR() - r.getR(), l.getG() - r.getG(), l.getB() - r.getB());
    }

    public static FloatColor mul(float l, FloatColor r){
        return new FloatColor(l * r.getR(), l * r.getG(), l * r.getB());
    }

    public static FloatColor mul(FloatColor l, FloatColor r){
        return new FloatColor(l.getR() * r.getR(), l.getG() * r.getG(), l.getB() * r.getB());
    }

    public float getR() {
        return r;
    }

    public void setR(float r) {
        this.r = r;
    }

    public float getG() {
        return g;
    }

    public void setG(float g) {
        this.g = g;
    }

    public float getB() {
        return b;
    }

    public void setB(float b) {
        this.b = b;
    }

    public Color toColor(){
        int red = (int)(r * 255);
        int green = (int)(g * 255);
        int blue = (int)(b * 255);

        return new Color(red, green, blue);
    }
}
