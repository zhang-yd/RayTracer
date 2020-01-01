
cmake_minimum_required(VERSION 2.8)

# project(RTdemo) 
# aux_source_directory(. DIR_SRCS) 
# add_executable(RTdemo ${DIR_SRCS})


project(RayTracer)

FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
	message("OPENMP FOUND")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(SOURCE_FILES
	main.cpp 
	rtracer.cpp  
	scene.cpp 
	intersect.cpp  
	light.cpp  
	object.cpp 
	material.cpp 
	camera.cpp 
	sampler.cpp 
	ray.cpp  
	vector.cpp 
	util.cpp 
	log.cpp 
	lodepng.cpp
	global.cpp 
	)

add_executable(RayTracer ${SOURCE_FILES})




