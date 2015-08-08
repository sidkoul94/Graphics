#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define ANGLE 0.3
#define SCALE 0.9
#define RAND 0.06


// declaring variables
GLfloat angles = 0.0f;
GLfloat red=0.0,green=0.0,blue=0.0;
struct Points{
	GLfloat x ;
	GLfloat y ;
	GLfloat z ;
    };
Points p[10000];
bool left = true;
bool day = false;
GLfloat hangle = 0.0 , anglee = 0.0f;
GLfloat delta = 0.0;

GLfloat iangles = 0.0f;
GLfloat idelta = 0.0f;
GLfloat pers = 45.0f  ;
bool b = true;
bool direction = true;
int flag =1;

// for camera operations
// angle of rotation for the camera direction
float angle = 0.0f;
float angley = 0.0f;
// actual vector representing the camera's direction
float lx=0.0f,lz=-2.0f , ly = 0.0f;

// XZ position of the camera
float x=0.0f, z=20.0f , y = 1.0f;

// the key states. These variables will be zero
// when no key is being presses
float deltaAngle = 0.0f;
float deltaAngley = 0.0f;
float deltaMove = 0;
float deltaMoveConstant = 0.5f;
float distance = 0.0f;
int xOrigin = -1;
int yOrigin = -1;

// initialization 
void init(){
           for(int i = 0 ; i < 1000 ; i++){                      // Front
		    p[i].x = rand()%100 - 80 ;
		    p[i].y = rand()%500  ;
		    if(p[i].y < 100)
			p[i].y = rand()%100 - 50 ;
		    p[i].z = rand()%200- 200 ;
	}
	    
	    for(int i = 1000 ; i < 2000; i++){                      // Back
		    p[i].x = rand()%100 - 80 ;
		    p[i].y = rand()%500;
		    if(p[i].y < 100)
			p[i].y = rand()%100 - 50 ;
		    p[i].z = rand()%200  ;
	    }	    
	
	  for(int i = 2000 ; i < 3000; i++){                     // Left
		    p[i].x = rand()%100 - 200 ;
		    p[i].y = rand()%500 ;
		    if(p[i].y < 100)
			p[i].y = rand()%100 - 50 ;
		    p[i].z = rand()%200 -100 ;
	    }	
	    
	     for(int i = 3000 ; i < 4000; i++){                   // Right
		    p[i].x = rand()%100 ;
		    p[i].y = rand()%500 ;
		    if(p[i].y < 100)
			p[i].y = rand()%100 - 50 ;
		    p[i].z = rand()%200  - 100;
	    }	
	   
	 
    }

// to draw a tree
float myrand(float R)
{
   return (2 * R * rand()) / RAND_MAX - R;
}

void tree(float x1, float y1, float length1, float angle1, int depth)
{
   if (depth > 0)
   {
      // Draw line segment
      float x2 = x1 + length1 * cos(angle1);
      float y2 = y1 + length1 * sin(angle1);
      glVertex2f(x1, y1);
      glVertex2f(x2, y2);

      // Make two recursive calls
      float length2 = length1 * (SCALE + myrand(RAND));
      float angle2 = angle1 + ANGLE + myrand(RAND);
      tree(x2, y2, length2, angle2, depth-1);
      length2 = length1 * (SCALE + myrand(RAND));
      angle2 = angle1 - ANGLE + myrand(RAND);
      tree(x2, y2, length2, angle2, depth-1);
   }
}

void drawtree(){
	
	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_LINES);
	    tree(0, -80, 20, 1.5, 10);
	glEnd();
    }
// to draw statue

void drawstatue2(){
	glPushMatrix();
	glTranslatef(0,6,0);
	glPushMatrix();
	glRotatef(iangles,0,1,0);
	glColor3f(0.0,0.0,0.0);
	glutWireCube(2.0);
	glPopMatrix();
	glRotatef(iangles,1,0,0);
	glColor3f(1.0,0.84,0.0);
	glutWireSphere(4.0,10,12);
	glPopMatrix();
    }

void drawStatue(){
	glPushMatrix();
	glTranslatef(0,2,-9);
	drawstatue2();
	glColor3f(0.0,0.0,0.0);
	glRotatef(45,0,1,0);
	glutSolidCube(5.0);
	glPopMatrix();
    }
    
// to draw baton
void drawHalfSphere(int scaley, int scalex, GLfloat r) {
    int i, j;
    GLfloat v[scalex*scaley][3];

    for (i=0; i<scalex; ++i) {
	for (j=0; j<scaley; ++j) {
	    v[i*scaley+j][0]=r*cos(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
	    v[i*scaley+j][1]=r*sin(i*M_PI/(2*scalex));
	    v[i*scaley+j][2]=r*sin(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
	}
    }

    glBegin(GL_QUADS);
    for (i=0; i<scalex-1; ++i) {
	for (j=0; j<scaley; ++j) {
	    glVertex3fv(v[i*scaley+j]);
	    glVertex3fv(v[i*scaley+(j+1)%scaley]);
	    glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
	    glVertex3fv(v[(i+1)*scaley+j]);
	}
    }
    glEnd();
} 
 
 void drawBaton(double x , double z){
	glPushMatrix();
	glTranslatef(x,0,z);
	glColor3f(0.0,0.0,1.0);
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glTranslatef(0.0,2.0,0.0);
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic,0.1f,0.1f,3.0f,32,32);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	drawHalfSphere(25.0,25.0,0.5);
	glPopMatrix();
	
	
	glColor3f(1.0,1.0,0.0);
	glTranslatef(0.0,0.0,0.0);
	glRotatef(iangles, 0.0f, 1.0f, 0.0f);
	glutWireSphere(0.5,12,12);
	glPopMatrix();
     }
     
 // to draw a castle           
 void drawWall(){
	glPushMatrix();
	glTranslatef(-1.15,1.0,0.0);
	glScalef(2.0,2.0,0.2);
	glutSolidCube(1.0f);
	glPopMatrix();
	
	
	glPushMatrix();
	glTranslatef(1.15,1.0,0.0);
	glScalef(2.0,2.0,0.2);
	glutSolidCube(1.0f);
	glPopMatrix();
	
	
	glPushMatrix();
	glTranslatef(0,2.50,0.0);
	glScalef(4.0,4,0.2);
	glutSolidCube(1.0f);
	glPopMatrix();
     }

void drawCastle(){
	// draw wall
	glPushMatrix();
	
	glColor3f(0.803,0.521,0.247);
	glPushMatrix();
	glScalef(30,10,10);
	drawWall();
	glPopMatrix();
	
	glColor3f(0.501,0.0,0.0);
	glPushMatrix();
	glTranslatef(-50,0,-30);
	glRotatef(90,0,1,0);
	glScalef(20,10,10);
	drawWall();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(50,0,-30);
	glRotatef(90,0,1,0);
	glScalef(20,10,10);
	drawWall();
	glPopMatrix();
	
	
	
	
	glColor3f(0.501,0.0,0.0);
	glPushMatrix();
	glTranslatef(0,0,-60);
	glScalef(30,10,10);
	drawWall();
	glPopMatrix();
	
	
	
	
	glPopMatrix();
    }
// to draw rolling ball
void rollingball(int x , int y , int z ,double dx , double dz){
	glPushMatrix();
	glTranslatef(dx, 1.5 , dz);
	glRotatef(iangles , x,y,z);
	glutWireSphere(2.0f,10,15);
	glPopMatrix();
    }

// to draw house
void drawRoof(){
	glBegin(GL_TRIANGLE_FAN);
    glColor4f(0, 1, 1, 0.2);
    glVertex3f(0, 3.4, 0);
    glVertex3f(-1.8, 0, -1.8);
    glVertex3f(-1.8, 0, 1.8);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(1.8, 0, 1.8);
    glVertex3f(1.8, 0, -1.8);
    glVertex3f(-1.8, 0, -1.8);
  glEnd();
    }    

void house(){
	glColor3f(1.0,0.0,0.0);
	glutSolidCube(2.5f);
	glColor3f(0.0,0.0,1.0);
	glTranslatef(0.1,-0.7,1.1);
	glutSolidCube(1.0f);
    } 

void drawhouse(int x , int z){
	glPushMatrix();
	glTranslatef(x,1.6,z);
	glRotatef(hangle,0,1,0);
	glScalef(1.0,1.0,1.0);
	glPushMatrix();
	glTranslatef(0.0,-0.5,0.0);
	house();
	glPopMatrix();
	drawRoof();
	glPopMatrix();
	
    }



void pressKey(int key, int xx, int yy) {

       switch (key) {
             case GLUT_KEY_UP : deltaMove = deltaMoveConstant; break;
             case GLUT_KEY_DOWN : deltaMove = -deltaMoveConstant; break;
	     
       }
} 
void releaseKey(int key, int x, int y) { 	

        switch (key) {
             case GLUT_KEY_UP :
             case GLUT_KEY_DOWN : deltaMove = 0;break;
        }
} 
void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}
void assert(){
	
	if((iangles += 0.5f) > 360.0f)
	    iangles = 0;
    }
    
void assertDistance(){
	if(direction){
	    distance += 0.01f;
	    if(distance > 10.0f)
		direction = false ;
	}
	else {
	    distance -= 0.01f;
	    if(distance < -10.0f)
		direction = true ;
	}	
    }
    
void drawstring(float x,float y,float z,char *string){
	 char *c;
	glPushMatrix();
        glRasterPos3f(x,y,z);
        for (char *p = string; *p; p++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);

	glPopMatrix();	
}

void rotcubes(float x , float y , float z,float size){
	glPushMatrix();
	glRotatef(iangles,x,y,z);
	glutSolidCube(size);
	glPopMatrix();
    }

void rotSphere(float size){
	
	glPushMatrix();
	glRotatef(iangles,0,1,0);
	glutWireSphere(size,11,15);
	glPopMatrix();
    }

void loadline(){
	
	glPushMatrix();
	glRotatef(iangles,0,0,1);
	
	glRotatef(iangles,0,1,0);
	glutSolidCube(0.5f);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(-iangles,0,0,1);
	glTranslatef(0.0,2.5,0.0);
	glRotatef(-iangles,0,1,0);
	glutWireSphere(0.5f,10,11);
	glPopMatrix();
    }

void display5(void){
	
	
	if (deltaMove)
		computePos(deltaMove);

	if(red > 0.0 && green > 0.0 && blue > 0.0 && day)
	{
		glClearColor(red,green, blue,1.0);
		red-=0.0002;
		green-=0.0002;
		blue-=0.0002;
		
	}
	else 
	    day = false;
	
	if(red < 0.749 && blue < 0.847 && green < 0.847 && !day ){
	   
	    glClearColor(red,green,blue,1.0);
	    red+= 0.0002     ;
	    green += 0.00022616822;
	    blue += 0.00022616822;
	}
	else 
	    day = true;
	
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, 2.5f, z,
			x + lx, ly+ 2.5f ,  z+lz,
			0.0f, 1.0f,  0.0f);

	// Draw ground

	//glRotatef(anglee,0,0,1);
	glColor3f(0.0f, 0.5f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

        // draw Castle
	glPushMatrix();
	glTranslatef(0,0,15);
	drawCastle();
	glPopMatrix();
	
	// draw pointer
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0,0.0,0.0);
	glScalef(0.01,0.01,2);
	glutWireSphere(0.1,10,12);
	glPopMatrix();
	
	
	// draw House
	glPushMatrix();
	drawhouse(10.5,-15.0);
	drawhouse(-10.5 , -15.0);
	drawhouse(10.5,-5.0);
	drawhouse(-10.5 , -5.0);
	glPopMatrix(); 
	
	
	// draw statue 
	drawStatue();
	
	// draw baton
	glPushMatrix();
	glTranslatef(0,0,-10);
	drawBaton(-10,0);
	drawBaton(10,0);
	drawBaton(0,-10);
	drawBaton(0,10);
	glPopMatrix();
	
	
	
	// drawStars
	glPushMatrix();
	glColor3f(1.0,1.0,1.0)  ;
	glPointSize(1.0);
	glTranslatef(0,0,delta);
	glBegin(GL_POINTS);
	for(int i = 0 ; i < 4000 ; i++ )
            glVertex3f(p[i].x,p[i].y,p[i].z);
	glEnd();   
	glPopMatrix();
	
	assertDistance();
	
    }
void display4(void){
	if (deltaMove)
		computePos(deltaMove);

	if(red > 0.0 && green > 0.0 && blue > 0.0 && day)
	{
		glClearColor(red,green, blue,1.0);
		red-=0.002;
		green-=0.002;
		blue-=0.002;
		
	}
	else 
	    day = false;
	
	if(red < 0.749 && !day ){
	   
	    glClearColor(red,green,blue,1.0);
	    red+= 0.002     ;
	    green += 0.0022616822;
	    blue += 0.0022616822;
	}
	else 
	    day = true;
	
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, 1.0f, z,
			x + lx, ly + y ,  z + lz,
			0.0f, 1.0f,  0.0f);

// Draw ground

	glColor3f(0.87f, 0.72f, 0.529f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

// Draw 36 trees

	for(int i = -3; i < 3; i++){
		
		for(int j=-3; j < 3; j++) {
                     glPushMatrix();
                     glTranslatef(i*10.0,1.8,j * 10.0);
		     glRotatef(anglee +i*j,0,0,1);
		     glScalef(0.02,0.02,0.02);
                     drawtree();
                     glPopMatrix();
		     
		     
                    		     
               }
	      
	}      
	       
	
	
	// drawBall1
	glPushMatrix();
	glColor3f(0.5,0,0);
	glTranslatef(0.0,0.0,20.0);
	rollingball(0,0,1 ,distance, 0.0);
	glPopMatrix();
	
	// drawBall2
	glPushMatrix();
	glTranslatef(20.0,0.0,0.0);
	rollingball(1,0,0 ,0.0, -distance);
	glPopMatrix();
	
	// drawBall3
	glPushMatrix();
	glTranslatef(0.0,0.0,-20.0);
	rollingball(0,0,1 ,-distance,0.0 );
	glPopMatrix();
	
	// drawBall4
	glPushMatrix();
	glTranslatef(-20.0,0.0,0.0);
	rollingball(1,0,0 ,0.0, distance);
	glPopMatrix();
	
	
	// drawHouse 
	glPushMatrix();
	drawhouse(2.5,-15.0);
	drawhouse(-2.5 , -15.0);
	glPopMatrix(); 
	
	// drawStars
	glPushMatrix();
	glColor3f(1.0,1.0,1.0)  ;
	glPointSize(1.0);
	glTranslatef(0,0,delta);
	glBegin(GL_POINTS);
	for(int i = 0 ; i < 4000 ; i++ )
            glVertex3f(p[i].x,p[i].y,p[i].z);
	glEnd();   
	glPopMatrix();
	
	if(left)
	    anglee -= 0.1f;
	else
	    anglee += 0.1f;
	
	if(left){
	    if(anglee < -3.0f)
		left = false;
	}
	else if(anglee > 3.0f)
		left = true;
		
       // glFlush();
	assertDistance();
	//glutSwapBuffers();
    }
void display3(void){
	
	glClearColor(0.2,0.2,0.2,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0,1.0,1.0);
	gluLookAt(0.0,0.0,2.0,0.0,0.0,0.0,0.0,1.0,0.0);
	
	glPushMatrix();
	glClearColor(0.4,0.7,0.0,1.0);    //for background
	glColor3f(1.0,1.0,1.0);
	drawstring(-1.35,0.7,0.0,"3D WORLD RULES AND TIPS..!!");
	
	glPushMatrix();
	glTranslatef(-1.0,0.15,0);
	rotSphere(0.5);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.5,0.15,0);
	rotSphere(0.05);
	glPopMatrix();
	drawstring(-0.4,0.15,0.0,"DRAG WHILE PRESSING THE LEFT MOUSE BUTTON ");
	drawstring(-0.4,0.10,0.0,"TO CHANGE THE CAMERA VIEW");
	
	glPushMatrix();
	glTranslatef(-0.55,0.3,0);
	rotSphere(0.05);
	glPopMatrix();
	drawstring(-0.45,0.3,0.0,"USE THE UP ARROW KEY TO MOVE FORWARD ");
	
	glPushMatrix();
	glTranslatef(-0.6,0.45,0);
	rotSphere(0.05);
	glPopMatrix();
	drawstring(-0.5,0.45,0.0,"USE THE DOWN ARROW KEY TO MOVE BACKWARDS ");
	glPopMatrix();
	
    }
    
void display2(void){
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0,1.0,1.0);
	gluLookAt(0.0,0.0,10.0,0.0,0.0,0.0,0.0,1.0,0.0);
	
	glPushMatrix();
	glTranslatef(-2.0,1.0,0);
	rotcubes(0.5,0.5,0.5,0.2);
	glPopMatrix();
	drawstring(-1.5,0.9,0,"[T]OWARDS VIRTUAL WORLD");
	
	glPushMatrix();
	glTranslatef(-2.0,0.0,0);
	rotcubes(0.1,0.3,0.8,0.2);
	glPopMatrix();
	drawstring(-1.5,-0.1,0,"[H]ELP");
	
	glPushMatrix();
	glTranslatef(-2.0,-1.0,0);
	rotcubes(0.6,0.7,0.9,0.2);
	glPopMatrix();
	drawstring(-1.5,-1.1,0,"[E]XIT");
	
	//glFlush();
	//glutSwapBuffers();
	
    }

void display1(void){
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0,0.0,1.0 + idelta,0.0,0.0,0.0,0.0,1.0,0.0);
	glColor3f(0.0,0.0,0.0);
	rotSphere(2.0);
	loadline();
	drawstring(-5.5,0.0,3.0,"COMPUTER GRAPHICS PROJECT ON")   ;
	drawstring(-5.5,-0.3,3.0,"VIRTUAL REALITY")   ;
	drawstring(-5.5,-1.6,3.0,"PRESENTED BY -")   ;
	drawstring(-5.5,-1.9,3.0,"SHRIDHAR MISHRA")   ;
	drawstring(-5.5,-2.2,3.0,"SIDDANTH KOUL")   ;
	drawstring(-2.0,2.5,3.0,"WELCOME TO THE \n VIRTUAL REALITY");
	if(b)
	    drawstring(2.5,0.0,3.0,"LOADING.....");
	else {
	glColor3f(0.0,0.0,0.0);
	drawstring(2.5,0.0,3.0,"LOADING COMPLETED..!!");
	drawstring(2.5,-0.3,3.0,"PRESS ANY KEY TO CONTINUE");
	}
	
	glFlush();
	
	//glutSwapBuffers();
	
	if(idelta < 10.0f) 
	    idelta += 0.005f ;
	
	
	   
    }

void mouseMove(int x, int y) { 	

         // this will only be true when the left button is down
          
	 if (xOrigin >= 0) 
           {
		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;
                deltaAngley = (y - yOrigin) * 0.001f;
		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
		ly = -sin(angley + deltaAngley);
	}
}
void mouseButton(int button, int state, int x, int y) {
        
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			angley += deltaAngley;
			xOrigin = -1;
			yOrigin = -1;
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
			yOrigin = y;
		}
	}
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(pers, ratio, 0.1f, 1000.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void){
	
	if(flag == 1)
	    display1();
	else if(flag == 2)
	    display2() ;
	else if(flag == 3)
	    display3();
	else if(flag == 4)
	    display5();
	else if(flag == 5)
	    display4();
	assert();
	glFlush();
    }

void keys(unsigned char key ,int x , int y){
	if(key == 'e' || key == 'E')
	    exit(0);
	
	if(key == 13){
	    
	   flag = 2;
	   renderScene();
	}
	
	if(key == 'h' || key == 'H'){
	    flag =3;
	    renderScene();
	}    
	
	if(key == 't' || key == 'T'){
	    flag = 4;
	    renderScene();
	}
	
	if(key == 'y' || key == 'Y'){
	    flag = 5;
	    renderScene();
	}      
	
	
    }

void update(int n){
	
	b = false;
	

    }


int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH| GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	// timer func
	glutTimerFunc(10000,update,0);
	
	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	glutFullScreen();
	init();
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
    
    
    
    

