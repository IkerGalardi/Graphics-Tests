package source;

import math.Vector3;
import raytracing.FloatColor;
import raytracing.Lighting.DirectionalLight;
import raytracing.Raycaster;
import raytracing.shapes.Sphere;

import javax.imageio.ImageIO;
import java.io.File;
import java.io.IOException;

public class Main {


    public static void main(String[] args) {
        Raycaster raycaster = new Raycaster(500, 500, 60);

        raycaster.addShape(new Sphere(new Vector3(0, 0, -40),   new FloatColor(0, 1, 1),  10));
        raycaster.addShape(new Sphere(new Vector3(2, 0, -10),   new FloatColor(1, 0, 0),      1.5f));
        raycaster.addShape(new Sphere(new Vector3(-2, 0, -15f), new FloatColor(0, 1, 0),      1.2f));

        raycaster.addLight(new DirectionalLight(Vector3.zero(), new Vector3(0, -1, 0), 0.7f));

        long startTime = System.currentTimeMillis();

        raycaster.renderBackground();
        raycaster.renderShapes();

        System.out.println("Render finished!");
        long elapsed = System.currentTimeMillis() - startTime;
        System.out.println("Took " + ((float)elapsed/1000.0f) + " seconds to finish.");

        try{
            // write the image to the file
            File outputFile = new File("test.png");
            ImageIO.write(raycaster.getRenderResult(), "png", outputFile);
            System.out.println("Image written!");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
