//=============================================================================================
// Framework for the ray tracing homework
// ---------------------------------------------------------------------------------------------
// Name    :
// Neptun :
//=============================================================================================

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if defined(__APPLE__)
#include <GLUT/GLUT.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#else
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#endif

#include <GL/glew.h>		// must be downloaded
#include <GL/freeglut.h>	// must be downloaded unless you have an Apple
#include "MathUtils/Matrix.h"
#include "Materials/Color.h"
#include "Utils/Scene.h"

#endif

const unsigned int windowWidth = 600, windowHeight = 600;

// OpenGL major and minor versions
int majorVersion = 3, minorVersion = 3;

void getErrorInfo( unsigned int handle ) {
    int logLen;
    glGetShaderiv( handle, GL_INFO_LOG_LENGTH, &logLen );
    if( logLen > 0 ){
        char *log = new char[logLen];
        int written;
        glGetShaderInfoLog( handle, logLen, &written, log );
        printf( "Shader log:\n%s", log );
        delete[] log;
    }
}

// check if shader could be compiled
void checkShader( unsigned int shader, char *message ) {
    int OK;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &OK );
    if( !OK ){
        printf( "%s!\n", message );
        getErrorInfo( shader );
    }
}

// check if shader could be linked
void checkLinking( unsigned int program ) {
    int OK;
    glGetProgramiv( program, GL_LINK_STATUS, &OK );
    if( !OK ){
        printf( "Failed to link shader program!\n" );
        getErrorInfo( program );
    }
}

// vertex shader in GLSL
const char *vertexSource = R"(
	#version 330
    precision highp float;

	layout(location = 0) in vec2 vertexPosition;	// Attrib Array 0

	out vec2 texcoord;

	void main() {
		texcoord = (vertexPosition + vec2(1, 1))/2;							// -1,1 to 0,1
		gl_Position = vec4(vertexPosition.x, vertexPosition.y, 0, 1); 		// transform to clipping space
	}
)";

// fragment shader in GLSL
const char *fragmentSource = R"(
	#version 330
    precision highp float;

	uniform sampler2D textureUnit;
	in  vec2 texcoord;			// interpolated texture coordinates

	out vec4 fragmentColor;		// output that goes to the raster memory as told by glBindFragDataLocation

	void main() {
		fragmentColor = texture(textureUnit, texcoord);
	}
)";

// handle of the shader program
unsigned int shaderProgram;

class FullScreenTexturedQuad {
    unsigned int vao, textureId;    // vertex array object id and texture id
    Color *m_image;
public:
    void Create( Color image[windowWidth * windowHeight] ) {
        glGenVertexArrays( 1, &vao );    // create 1 vertex array object
        glBindVertexArray( vao );        // make it active

        unsigned int vbo;        // vertex buffer objects
        glGenBuffers( 1, &vbo );    // Generate 1 vertex buffer objects

        // vertex coordinates: vbo[0] -> Attrib Array 0 -> vertexPosition of the vertex shader
        glBindBuffer( GL_ARRAY_BUFFER, vbo ); // make it active, it is an array
        static float vertexCoords[] = {-1, -1, 1, -1, -1, 1,
                                       1, -1, 1, 1, -1, 1};    // two triangles forming a quad
        glBufferData( GL_ARRAY_BUFFER, sizeof( vertexCoords ), vertexCoords,
                      GL_STATIC_DRAW );       // copy to that part of the memory which is not modified
        // Map Attribute Array 0 to the current bound vertex buffer (vbo[0])
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, NULL );     // stride and offset: it is tightly packed

        // Create objects by setting up their vertex data on the GPU
        glGenTextures( 1, &textureId );                // id generation
        glBindTexture( GL_TEXTURE_2D, textureId );    // binding

        m_image = image;
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, windowWidth, windowHeight, 0, GL_RGB, GL_FLOAT, image ); // To GPU
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST ); // sampling
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    }

    void Draw() {
        glBindVertexArray( vao );    // make the vao and its vbos active playing the role of the data source
        int location = glGetUniformLocation( shaderProgram, "textureUnit" );
        if( location >= 0 ){
            glUniform1i( location, 0 );        // texture sampling unit is TEXTURE0
            glActiveTexture( GL_TEXTURE0 );
            glBindTexture( GL_TEXTURE_2D, textureId );    // connect the texture to the sampler
            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, windowWidth, windowHeight, 0, GL_RGB, GL_FLOAT, m_image ); // To GPU
        }
        glDrawArrays( GL_TRIANGLES, 0, 6 );    // draw two triangles forming a quad
    }
};

// The virtual world: single quad
FullScreenTexturedQuad fullScreenTexturedQuad;

Color background[windowWidth * windowHeight];    // The image, which stores the ray tracing result


// Initialization, create an OpenGL context
void onInitialization() {
    glViewport( 0, 0, windowWidth, windowHeight );



    // Ray tracing fills the image called background
    for( int x = 0; x < windowWidth; x++ ){
        for( int y = 0; y < windowHeight; y++ ){
            background[y * windowWidth + x] = Color((float) x / windowWidth, (float) y / windowHeight, 0 );
        }
    }

    Vector eye( 0, 15, 29 );
    Vector lookat( 0, 11, 20 );
    Camera cam = Camera( eye, lookat, Vector( 0, 1, -1 ), Number((int) windowWidth ), Number((int) windowHeight ));
    Scene s( cam, windowWidth, windowHeight, background );
    s.build();
    s.render();

    fullScreenTexturedQuad.Create( background );

    // Create vertex shader from string
    unsigned int vertexShader = glCreateShader( GL_VERTEX_SHADER );
    if( !vertexShader ){
        printf( "Error in vertex shader creation\n" );
        exit( 1 );
    }
    glShaderSource( vertexShader, 1, &vertexSource, NULL );
    glCompileShader( vertexShader );
    checkShader( vertexShader, "Vertex shader error" );

    // Create fragment shader from string
    unsigned int fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    if( !fragmentShader ){
        printf( "Error in fragment shader creation\n" );
        exit( 1 );
    }
    glShaderSource( fragmentShader, 1, &fragmentSource, NULL );
    glCompileShader( fragmentShader );
    checkShader( fragmentShader, "Fragment shader error" );

    // Attach shaders to a single program
    shaderProgram = glCreateProgram();
    if( !shaderProgram ){
        printf( "Error in shader program creation\n" );
        exit( 1 );
    }
    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );

    // Connect the fragmentColor to the frame buffer memory
    glBindFragDataLocation( shaderProgram, 0, "fragmentColor" );    // fragmentColor goes to the frame buffer memory

    // program packaging
    glLinkProgram( shaderProgram );
    checkLinking( shaderProgram );
    // make this program run
    glUseProgram( shaderProgram );
}

void onExit() {
    glDeleteProgram( shaderProgram );
    printf( "exit" );
}

// Window has become invalid: Redraw
void onDisplay() {
    fullScreenTexturedQuad.Draw();
    glutSwapBuffers();                                    // exchange the two buffers
}

// Key of ASCII code pressed
void onKeyboard( unsigned char key, int pX, int pY ) {
    if( key == 'd' ) glutPostRedisplay();         // if d, invalidate display, i.e. redraw
}

// Key of ASCII code released
void onKeyboardUp( unsigned char key, int pX, int pY ) {

}

// Mouse click event
void onMouse( int button, int state, int pX, int pY ) {
    if( button == GLUT_LEFT_BUTTON &&
        state == GLUT_DOWN ){  // GLUT_LEFT_BUTTON / GLUT_RIGHT_BUTTON and GLUT_DOWN / GLUT_UP
    }
}

// Move mouse with key pressed
void onMouseMotion( int pX, int pY ) {
}

// Idle event indicating that some time elapsed: do animation here
void onIdle() {
    long time = glutGet( GLUT_ELAPSED_TIME ); // elapsed time since the start of the program
}

int main( int argc, char *argv[] ) {
    glutInit( &argc, argv );
#if !defined(__APPLE__)
    glutInitContextVersion( majorVersion, minorVersion );
#endif
    glutInitWindowSize( windowWidth,
                        windowHeight );                // Application window is initially of resolution 600x600
    glutInitWindowPosition( 100, 100 );                            // Relative location of the application window
#if defined(__APPLE__)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);  // 8 bit R,G,B,A + double buffer + depth buffer
#else
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
#endif
    glutCreateWindow( argv[0] );

#if !defined(__APPLE__)
    glewExperimental = true;    // magic
    glewInit();
#endif

    printf( "GL Vendor    : %s\n", glGetString( GL_VENDOR ));
    printf( "GL Renderer  : %s\n", glGetString( GL_RENDERER ));
    printf( "GL Version (string)  : %s\n", glGetString( GL_VERSION ));
    glGetIntegerv( GL_MAJOR_VERSION, &majorVersion );
    glGetIntegerv( GL_MINOR_VERSION, &minorVersion );
    printf( "GL Version (integer) : %d.%d\n", majorVersion, minorVersion );
    printf( "GLSL Version : %s\n", glGetString( GL_SHADING_LANGUAGE_VERSION ));

    onInitialization();

    glutDisplayFunc( onDisplay );                // Register event handlers
    glutMouseFunc( onMouse );
    glutIdleFunc( onIdle );
    glutKeyboardFunc( onKeyboard );
    glutKeyboardUpFunc( onKeyboardUp );
    glutMotionFunc( onMouseMotion );

    glutMainLoop();
    onExit();
    return 1;
}
