package source;

import math.Vector3;
import raytracing.IntersectionData;
import raytracing.Ray;
import raytracing.shapes.GeometricShape;
import raytracing.shapes.InfinitePlane;
import raytracing.shapes.Sphere;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

public class Main {

    public static Vector3 getRayDirection(int x, int y, Vector3 origin, float fov, int width, int height){
        // Calculate the pixel position in world space
        Vector3 pixelPosition = new Vector3(0,0,-1);
        pixelPosition.setX(((2 * x - width) * (float)Math.tan(fov))/(width));
        pixelPosition.setY(((2 * y - height) * (float)Math.tan((width/height) * fov))/(height));

        System.out.println("Pixel position = " + pixelPosition);

        // Calculate the direction to the pixel
        return Vector3.sub(pixelPosition, origin);
    }

    public static void main(String[] args) {
        final int WIDTH = 500;
        final int HEIGHT = 500;

        // Setup the image buffer
        BufferedImage bufferedImage = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_INT_RGB);

        ArrayList<GeometricShape> geometricShapes = new ArrayList<>();
        geometricShapes.add(new Sphere(new Vector3(0, 0, -40), Color.CYAN, 10));
        geometricShapes.add(new Sphere(new Vector3(2, 0, -10), Color.RED, 1.5f));
        geometricShapes.add(new Sphere(new Vector3(-2, 0, -15f), Color.GREEN, 1.2f));

        long startTime = System.currentTimeMillis();


        // Draw the sky first
        for(int i = 0; i < WIDTH; i++){
            for(int j = 0; j < HEIGHT; j++){
                bufferedImage.setRGB(i, j, Color.BLUE.getRGB());
            }
        }

        // Raycasting stuff
        for(int i = 0; i < WIDTH; i++){
            for(int j = 0; j < HEIGHT; j++){
                float lastMinimumDepth = Float.MAX_VALUE;
                Ray ray = new Ray(Vector3.zero(), getRayDirection(i, j, Vector3.zero(), 60, WIDTH, HEIGHT));

                // Test intersection with all the shapes of the scene
                for(GeometricShape shape : geometricShapes){
                    // Intersect and get the data and check if there is a hit
                    IntersectionData intersectionData = shape.intersect(ray);
                    if(intersectionData.getHasHit()){
                        // There is a hit! calculate the pixel and set last depth
                        if(intersectionData.getDepth() < lastMinimumDepth){
                            bufferedImage.setRGB(i, j, shape.getColor().getRGB());
                            lastMinimumDepth = intersectionData.getDepth();
                        } else {
                            System.out.println("Something in between");
                        }
                    }
                }
                System.out.println("(" + i + ", " + j +")" + " pixel calculated");
            }
        }

        System.out.println("Render finished!");
        long elapsed = System.currentTimeMillis() - startTime;
        System.out.println("Took " + ((float)elapsed/1000.0f) + " seconds to finish.");

        try{
            // write the image to the file
            File outputFile = new File("test.png");
            ImageIO.write(bufferedImage, "png", outputFile);
            System.out.println("Image written!");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
