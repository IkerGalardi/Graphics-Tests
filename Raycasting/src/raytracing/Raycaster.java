package raytracing;

import math.Vector3;
import raytracing.lighting.Light;
import raytracing.shading.PhongShading;
import raytracing.shapes.GeometricShape;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.util.ArrayList;

public class Raycaster {
    private ArrayList<GeometricShape> shapes;
    private ArrayList<Light> lights;

    private BufferedImage render;
    private PhongShading shader;

    private int width, height;
    private float fov;



    public Raycaster(int width, int height, float fov){
        this.width = width;
        this.height = height;
        this.fov = fov;

        shapes = new ArrayList<>();
        lights = new ArrayList<>();

        render = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
        shader = new PhongShading();
    }

    public void addShape(GeometricShape shape){
        shapes.add(shape);
    }
    public void addLight(Light light) { lights.add(light); }

    public void renderBackground(){
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                render.setRGB(i, j, Color.BLUE.getRGB());
            }
        }
    }

    public void renderShapes(){
        shader.setupShader(lights, shapes);

        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                float lastMinimumDepth = Float.MAX_VALUE;
                Ray ray = new Ray(Vector3.zero(), getRayDirection(i, j, Vector3.zero(), fov, width, height));

                // Test intersection with all the shapes of the scene
                for(GeometricShape shape : shapes){
                    // Intersect and get the data and check if there is a hit
                    IntersectionData intersectionData = shape.intersect(ray);
                    if(intersectionData.getHasHit() && intersectionData.getDepth() < lastMinimumDepth){
                        // There is a hit! calculate the pixel and set last depth and Prepare the shader to render
                        Vector3 hitPosition = ray.getPositionOnRay(intersectionData.getDepth());
                        shader.setAttributes(shape.getNormal(hitPosition), hitPosition, shape.getColor());
                        // Set the pixel color and set the depth test new value
                        render.setRGB(i, j, shader.calculateColor().getRGB());
                        lastMinimumDepth = intersectionData.getDepth();
                    }
                }
                System.out.println("(" + i + ", " + j +")" + " pixel calculated");
            }
        }
    }

    public BufferedImage getRenderResult() { return render; }

    private Vector3 getRayDirection(int x, int y, Vector3 origin, float fov, int width, int height){
        // Calculate the pixel position in world space
        Vector3 pixelPosition = new Vector3(0,0,-1);
        pixelPosition.setX(((2 * x - width) * (float)Math.tan(fov))/(width));
        pixelPosition.setY(-((2 * y - height) * (float)Math.tan((width/height) * fov))/(height));

        // Calculate the direction to the pixel
        return Vector3.sub(pixelPosition, origin);
    }

}
