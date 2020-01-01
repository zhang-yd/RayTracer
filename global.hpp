
#ifndef _GLOBAL_HEAD_ 
#define _GLOBAL_HEAD_ 

#include <string> 

#define DEBUG_MODE false  



// ==========================================
// project global setting 
#define PI 3.1415926 

const int MAX_TRACER_DEPTH = 4; 

const float POSITIVE_FLOAT_ZERO = 1e-6; 

const float MAX_DISTANCE = 1e6; 

const std::string PNG_DEFAULT_NAME = "test.png"; 



// ==========================================
// utility 
const int PNG_DEFAULT_WIDTH  = 400; 
const int PNG_DEFAULT_HEIGHT = 600; 

const float INIT_RATE = 0.25; 


// ==========================================
// scene 
const float SCENE_MINOR = 1e-3; 


// ==========================================
// LOG 
const int CUR_LOG_LEVEL = 1; 


#endif //  _GLOBAL_HEAD_ 
