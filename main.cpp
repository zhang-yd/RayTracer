

#include <iostream> 
#include <vector> 

#include "pt.hpp" 


void show_usage()
{
	glog->info("Ray Tracer project "); 
	glog->info("	current version: ", "v.1.1"); 
	glog->info("	created in ", 2019, "/", 12, "/", 19); 
}


void scene1()
{
	const int width = 600, height = 400; 
	// const int width = 1024, height = 720; 
	const vec3f bg = vec3f(50, 200, 240); 
	const std::string file_name = "render"; 
	const int sampler_size = 4; 

	PerspectiveCamera camera(PI/3.0, width, height, vec3f(0,0,0), vec3f(0, 0, -1), vec3f(0, 1, 0)); 	

	std::shared_ptr<SceneMgr> scn = std::make_shared<SceneMgr>(bg, camera); 

	// 
	std::shared_ptr<Light> lg1 = std::make_shared<SpotLight>(vec3f( 30, 50, -25), vec3f(1.8, 1.8, 1.8)); 
	std::shared_ptr<Light> lg2 = std::make_shared<SpotLight>(vec3f( 30, 20,  30), vec3f(1.7, 1.7, 1.7)); 

	scn->add_light(lg1.get()); 
	scn->add_light(lg2.get()); 

	Material      ivory(0.6,  0.2, 0.1, 0.1, vec3f(102.0, 102.0, 90.0), 1.0,  50.);
    Material      glass(0.0,  0.2, 0.1, 0.7, vec3f(155.0, 180.0, 200.0), 1.5,  125.);
    Material red_rubber(0.9,  0.1, 0.1, 0.1, vec3f(75.0, 20.0, 20.0), 1.0,  10.);
    Material     mirror(0.0, 6.0, 0.8, 0.0, vec3f(255.0, 255.0, 255.0), 1.0,  1425.);

	// 
	std::shared_ptr<Object> ob1 = std::make_shared<Sphere>(vec3f(-3, 0, -11), 2, ivory); 
	std::shared_ptr<Object> ob2 = std::make_shared<Sphere>(vec3f(-1.0, -1.5, -7), 2, glass); 
	std::shared_ptr<Object> ob3 = std::make_shared<Sphere>(vec3f(7, 5, -13), 4,  mirror); 
	std::shared_ptr<Object> ob4 = std::make_shared<Sphere>(vec3f(-7, 5, -13), 3.6, red_rubber); 

	scn->add_object(ob1.get()); 
	scn->add_object(ob2.get()); 
	scn->add_object(ob3.get()); 
	scn->add_object(ob4.get()); 

	std::shared_ptr<Sampler> sp = std::make_shared<Sampler>(sampler_size); 

	RTRacer rt = RTRacer(scn.get(), sp.get(), file_name, width, height); 
	rt.set_mode(RTRacer::SAVE_TYPE::PNG); 
	rt.render(); 

	glog->info("render finished"); 
}


int main()
{
	show_usage(); 
	scene1();   
	return 0; 
}






