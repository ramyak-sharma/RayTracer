#pragma once
#include "common.h"
#include "hittable.h"

class camera
{
public:
    // Image
    int image_width = 100;
    double aspect_ratio = 1.0;
    int samples_per_pixel = 50;
    int max_depth=10;

    void render(const hittable& world)
    {
        initialize();
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog<<"\n"<< image_height-j <<' '<< std::flush;
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0,0,0);
                for (int sample = 0; sample<samples_per_pixel; sample++){
                    ray r =get_ray(i,j);
                    pixel_color+=ray_color(r,world,max_depth);
                }
                write_color(std::cout, pixel_color*pixel_sample_scale);
            }
        }

        std::clog<<"\nDone.\n";
    }

private:

    int    image_height;   // Rendered image height
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below
    double pixel_sample_scale;

    void initialize()
    {
        image_height = int(image_width/aspect_ratio);
        //making sure the height is atleast 1
        image_height = (image_height<1) ? 1 : image_height;
        
        pixel_sample_scale = 1.0/samples_per_pixel;

        center=point3(0,0,0);

        //Camera
        double focal_length=1.0;
        double viewport_height = 2.0;
        double viewport_width = viewport_height*(double(image_width)/image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        vec3 viewport_u(viewport_width,0,0);
        vec3 viewport_v(0,-viewport_height,0);
        
        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u/image_width;
        pixel_delta_v = viewport_v/image_height;

        //using basic vector addition
        vec3 viewport_upper_left = center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_ray(int i, int j)const
    {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.
        vec3 offset = sample_square();
        point3 pixel_sample =     pixel00_loc
                                + ((i + offset.x()) * pixel_delta_u)
                                + ((j + offset.y()) * pixel_delta_v);

        point3 ray_origin = center;
        vec3 ray_direction = pixel_sample-ray_origin;

        return ray(ray_origin, ray_direction);

    }

    vec3 sample_square() const
    {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    color ray_color(const ray& r, const hittable& world, int depth)
    {
        if(depth<=0)return color(0,0,0);
        hit_record rec;
        if(world.hit(r,interval(0.001,infinity),rec))
        {
            vec3 direction =  rec.normal+random_unit_vector();
            return 0.5*ray_color(ray(rec.p,direction), world, depth-1);
        }

        vec3 unit_direction = unit_vector(r.direction());
        double a = 0.1*(unit_direction.y() + 1);
        return (1-a)*color(1,1,1)+a*color(0.5,0.7,1);
    }

};