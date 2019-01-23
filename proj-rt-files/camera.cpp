#include "camera.h"
#include <iostream>
using namespace std;
Camera::Camera()
    :colors(0)
{
}

Camera::~Camera()
{
    delete[] colors;
}

void Camera::Position_And_Aim_Camera(const vec3& position_input,
    const vec3& look_at_point,const vec3& pseudo_up_vector)
{
    position=position_input;
    look_vector=(look_at_point-position).normalized();
    horizontal_vector=cross(look_vector,pseudo_up_vector).normalized();
    vertical_vector=cross(horizontal_vector,look_vector).normalized();
}

void Camera::Focus_Camera(double focal_distance,double aspect_ratio,
    double field_of_view)
{
    film_position=position+look_vector*focal_distance;
    double width=2.0*focal_distance*tan(.5*field_of_view);
    double height=width/aspect_ratio;
    image_size=vec2(width,height);
}

void Camera::Set_Resolution(const ivec2& number_pixels_input)
{
    number_pixels=number_pixels_input;
    if(colors) delete[] colors;
    colors=new Pixel[number_pixels[0]*number_pixels[1]];
    min=-0.5*image_size;
    max=0.5*image_size;
    pixel_size = image_size/vec2(number_pixels);
}

// Find the world position of the input pixel
vec3 Camera::World_Position(const ivec2& pixel_index)
{

   	vec3 result;
	vec2 cells = Cell_Center(pixel_index);
    //TODO;
    	vec3 horzCx;
    	vec3 vertCy;			
    	horzCx[0] = (horizontal_vector[0] * cells[0]);
    	horzCx[1] = (horizontal_vector[1] * cells[0]);
    	horzCx[2] = (horizontal_vector[2] * cells[0]);
    	vertCy[0] = (vertical_vector[0] * cells[1]);
    	vertCy[1] = (vertical_vector[1] * cells[1]);
    	vertCy[2] = (vertical_vector[2] * cells[1]);
    	
	cout << endl;
	cout << "horizontal_vector = " << horzCx << endl;
	cout << "vertical_vector = " << vertCy << endl;
	cout << endl;	
	result = (film_position + horzCx + vertCy);
    	cout << "worlpos = " << result << endl;
	return result;
}
