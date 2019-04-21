package math;

public class Vector3 {
    private float x;
    private float y;
    private float z;

    public Vector3(float x, float y, float z){
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public static boolean equals(Vector3 left, Vector3 right){
        return left.x == right.x && left.y == right.y && left.z == right.z;
    }

    public float length(){
        return (float) Math.sqrt(x*x + y*y + z*z);
    }

    public Vector3 normalized(){
        float length = this.length();
        return new Vector3(this.x / length, this.y / length, this.z / length);
    }

    public static Vector3 zero(){
        return new Vector3(0,0,0);
    }

    public static Vector3 add(Vector3 left, Vector3 right){
        return new Vector3(left.x + right.x, left.y + right.y, left.z + right.z);
    }
    public static Vector3 sub(Vector3 left, Vector3 right){
        return new Vector3(left.x - right.x, left.y - right.y, left.z - right.z);
    }
    public static Vector3 mul(Vector3 vector, float scalar){
        return new Vector3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
    }

    public static Vector3 negative(Vector3 vector){
        return new Vector3(-vector.getX(), -vector.getY(), -vector.getZ());
    }

    public static float dot(Vector3 left, Vector3 right){
        return left.x * right.x + left.y * right.y + left.z * right.z;
    }

    public float getX() {
        return x;
    }

    public void setX(float x) {
        this.x = x;
    }

    public float getY() {
        return y;
    }

    public void setY(float y) {
        this.y = y;
    }

    public float getZ() {
        return z;
    }

    public void setZ(float z) {
        this.z = z;
    }

    public String toString(){
        return "(" + x + ", " + y + ", " + z + ")";
    }
}
