#include<windows.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.1416

static float    sky_r   = 0.53;
static float    sky_g   = 0.94;
static float    sky_b   = 0.89;

static float    moon_r   = 1.0;
static float    moon_g   = 1.0;
static float    moon_b   = 1.0;
static float    moon_t   = 0.0;

static int      sky_mode= 1;

static float sun_tx	= -10.0;
static float sun_ty	= 40.0;

static float moon_tx	= 20.0;
static float moon_ty	= 40.0;

static float cloud_tx	= -60.0;
static float cloud_ty	= 35.0;

static GLfloat spin     = 0.0;

static float ship_tx    =   33.0;
static float ship_ty    =   -4.0;

static float ship_smoke_tx1    =   2.5;
static float ship_smoke_ty1    =   26.0;

static float ship_smoke_tx2    =   8.5;
static float ship_smoke_ty2    =   26.0;

static float ship_smoke_t    =   1.0;


void init(){
    glClearColor(1.0f,1.0f,1.0f,0.0f);
    glOrtho(-50,50,-50,50,-50,50);
}

void sky(){
    glBegin(GL_QUADS);
        glColor3d(sky_r,sky_g,sky_b);
        glVertex2d(-50,20);
        glVertex2d(50,20);
        glVertex2d(50,50);
        glVertex2d(-50,50);
    glEnd();
}

void change_sky(){
    if(sky_mode==1){
        sky_r   -= 0.0001;
        sky_g   -= 0.0001;
        sky_b   -= 0.0001;
        sun_ty  -= 0.008;
        moon_t  += 0.0002;
        if(sky_r<=0.0 && sky_g<=0.0 && sky_b<=0.0){
            sky_mode    = 2;
            sky_r       = 0.0;
            sky_g       = 0.0;
            sky_b       = 0.0;
            moon_t      = 1.0;
        }
    }
    if(sky_mode==2){
        sky_r   += 0.0001;
        sky_g   += 0.0002;
        sky_b   += 0.0002;
        moon_t  -= 0.0009;
        if(sun_ty <= 40){
            sun_ty  += 0.016;
        }

        if(sky_r>=0.53 && sky_g>=0.94 && sky_b>=0.89){
            sky_mode    = 1;
            sky_r       = 0.53;
            sky_g       = 0.94;
            sky_b       = 0.89;
            moon_t      = 0.0;
        }
    }

}

void circle(float radius_x, float radius_y){
	int i = 0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 0; i < 100; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
		}

	glEnd();
}

void sun(){
    glTranslated(sun_tx,sun_ty,0);
    glColor3d(0.90,0.80,0.20);
    circle(6,7);
}
void moon(){
    glTranslated(moon_tx,moon_ty,0);
    glColor4d(moon_r,moon_g,moon_b,moon_t);
    circle(5,6);
}
void cloud1(){
    glPushMatrix();
    glScaled(.8,.7,1);
    glTranslated(cloud_tx,cloud_ty,0);

    glPushMatrix();
    glColor3d(196/256.0f, 193/256.0f, 151/256.0f);
    glTranslated(10,15,0);
    circle(6,6);
    glTranslated(5,5,0);
    circle(6,6);
     glTranslated(5,-5,0);
    circle(6,6);
    glPopMatrix();

    //......thunder draw....
    glPushMatrix();
    glTranslated(15,14,0);
    glBegin(GL_POLYGON);
        glColor3d(0.93,0.89,0.04);
        glVertex2d(2,0);
        glVertex2d(0,0);
        glVertex2d(-3,4);
        glVertex2d(-1,5);
        glVertex2d(0,2);
        glVertex2d(2,2.4);
        glVertex2d(5,-4);
    glEnd();
    glPopMatrix();


    glPopMatrix();
}

void move_cloude(){
    cloud_tx += 0.002;
    if(cloud_tx > 50.0)
        cloud_tx = -60.0;
}

void river(){
    glBegin(GL_QUADS);
        glColor3d(0.30,0.70,0.99);
        glVertex2d(-50,-10);
        glVertex2d(50,-10);
        glColor3d(0.66,0.80,0.91);
        glVertex2d(50,20);
        glVertex2d(-50,20);
    glEnd();
}

void ground(){
    glBegin(GL_QUADS);
        glColor3d(0.13,0.93,0.14);
        glVertex2d(-50,-50);
        glVertex2d(50,-50);
        glColor3d(0.33,0.99,0.34);
        glVertex2d(50,-10);
        glVertex2d(-50,-10);
    glEnd();
}

void house(){
//.....center body...........
    glBegin(GL_POLYGON);
        glColor3f(255/256.0f, 51/256.0f, 133/256.0f);
        glVertex2d(0,0);
        glVertex2d(-9.5,-6);
        glVertex2d(-9.5,-30);
        glVertex2d(9.5,-30);
        glVertex2d(9.5,-6);
    glEnd();
//.........house   stair.........
    glBegin(GL_QUADS);
        glColor3f(38/256.0f, 115/256.0f, 77/256.0f);
        glVertex2d(-11,-30);
        glVertex2d(11,-30);
        glVertex2d(11,-35);
        glVertex2d(-11,-35);
    glEnd();
//..................
    glBegin(GL_QUADS);
        glColor3f(134/256.0f,45/256.0f,45/256.0f);
        glVertex2d(4,0);
        glVertex2d(4,6);
        glVertex2d(7,6);
        glVertex2d(7,-2);

        glColor3f(128/256.0f,0/256.0f,0/256.0f);
        glVertex2d(3.5,6);
        glVertex2d(3.5,7);
        glVertex2d(7.5,7);
        glVertex2d(7.5,6);

    glEnd();
//....................
    glBegin(GL_POLYGON);
        glColor3f(77/256.0f,51/256.0f,51/256.0f);
        glVertex2d(0,0);
        glVertex2d(-10.5,-7.5);
        glVertex2d(-15,-7.5);
        glVertex2d(0,4.5);
        glVertex2d(15,-7.5);
        glVertex2d(10.5,-7.5);
    glEnd();

//............Door.....

    glPushMatrix();
    glTranslated(1,-29,0);
    glScaled(2,4.5,1);
    glColor3f(255/256.0f, 173/256.0f, 51/256.0f);
    glBegin(GL_QUADS);
        glVertex2d(0,0);
        glVertex2d(0,4);
        glVertex2d(4,4);
        glVertex2d(4,0);
//........border frame...........
        glColor3f(0,0,0);
        glVertex2d(0,0);
        glVertex2d(0,4);
        glVertex2d(0.05,4);
        glVertex2d(0.05,0);

        glColor3f(0,0,0);
        glVertex2d(0,4);
        glVertex2d(4,4);
        glVertex2d(4,3.95);
        glVertex2d(0,3.95);

        glColor3f(0,0,0);
        glVertex2d(4,0);
        glVertex2d(4,4);
        glVertex2d(3.95,4);
        glVertex2d(3.95,0);

        glColor3f(0,0,0);
        glVertex2d(0,0);
        glVertex2d(4,0);
        glVertex2d(4,0.05);
        glVertex2d(0,0.05);

        glColor3f(153/256.0f,51/256.0f,51/256.0f);
        glVertex2d(3.5,1.4);
        glVertex2d(3.2,1.4);
        glVertex2d(3.2,1.8);
        glVertex2d(3.5,1.8);

    glEnd();
    glPopMatrix();
//............door glass......
    glPushMatrix();
    glTranslated(2,-20,0);
    glScaled(1.5,1.8,1);
    glColor4f(0/256.0f, 204/256.0f, 204/256.0f,0.9);
    glBegin(GL_QUADS);
        glVertex2d(0,0);
        glVertex2d(0,4);
        glVertex2d(4,4);
        glVertex2d(4,0);

        glColor3f(0,0,0);
        glVertex2d(0,2);
        glVertex2d(0,2.1);
        glVertex2d(4,2.1);
        glVertex2d(4,2);

        glColor3f(0,0,0);
        glVertex2d(2.1,0);
        glVertex2d(2,0);
        glVertex2d(2,4);
        glVertex2d(2.1,4);
//..........border
        glColor3f(0,0,0);
        glVertex2d(0,0);
        glVertex2d(0,4);
        glVertex2d(0.1,4);
        glVertex2d(0.1,0);

        glColor3f(0,0,0);
        glVertex2d(0,4);
        glVertex2d(4,4);
        glVertex2d(4,3.9);
        glVertex2d(0,3.9);

        glColor3f(0,0,0);
        glVertex2d(4,0);
        glVertex2d(4,4);
        glVertex2d(3.9,4);
        glVertex2d(3.9,0);

        glColor3f(0,0,0);
        glVertex2d(0,0);
        glVertex2d(4,0);
        glVertex2d(4,0.1);
        glVertex2d(0,0.1);
    glEnd();
    glPopMatrix();

//.......windows.....

    glPushMatrix();
    glTranslated(-9,-21,0);
    glScaled(2,2.4,1);
    glColor3f(198/256.0f, 255/256.0f, 26/256.0f);
    glBegin(GL_QUADS);
        glVertex2d(0,0);
        glVertex2d(0,4);
        glVertex2d(4,4);
        glVertex2d(4,0);
    glEnd();
    glPopMatrix();
//..........windows glass

    glPushMatrix();
    glTranslated(-8,-20,0);
    glScaled(1.5,1.8,1);
    glColor4f(0/256.0f, 204/256.0f, 204/256.0f,0.9);
    glBegin(GL_QUADS);
        glVertex2d(0,0);
        glVertex2d(0,4);
        glVertex2d(4,4);
        glVertex2d(4,0);

        glColor3f(0,0,0);
        glVertex2d(0,2);
        glVertex2d(0,2.1);
        glVertex2d(4,2.1);
        glVertex2d(4,2);

        glColor3f(0,0,0);
        glVertex2d(2.1,0);
        glVertex2d(2,0);
        glVertex2d(2,4);
        glVertex2d(2.1,4);
//..........border frame ......
        glColor3f(0,0,0);
        glVertex2d(0,0);
        glVertex2d(0,4);
        glVertex2d(0.1,4);
        glVertex2d(0.1,0);

        glColor3f(0,0,0);
        glVertex2d(0,4);
        glVertex2d(4,4);
        glVertex2d(4,3.9);
        glVertex2d(0,3.9);

        glColor3f(0,0,0);
        glVertex2d(4,0);
        glVertex2d(4,4);
        glVertex2d(3.9,4);
        glVertex2d(3.9,0);

        glColor3f(0,0,0);
        glVertex2d(0,0);
        glVertex2d(4,0);
        glVertex2d(4,0.1);
        glVertex2d(0,0.1);
    glEnd();
    glPopMatrix();
   }

void grass_texture(){
    glPushMatrix();
    glScaled(0.8,1.2,1);
    glTranslated(-68,-54,0);
    glPushMatrix();
    glColor3d(0/256.0f, 102/256.0f, 34/256.0f);
    glTranslated(10,15,0);
    circle(6,6);
    glTranslated(5,5,0);
    circle(6,6);
    glTranslated(5,-5,0);
    circle(6,6);
    glPopMatrix();
    glPopMatrix();

}

void move_spin_right(void){
    spin=spin-0.09;
    if(spin < 0)
        spin=360.0;
    glutPostRedisplay();
}

void move_spin_left(void){
    spin=spin+0.09;
    if(spin > 360)
        spin=0;
    glutPostRedisplay();
}

void windmill(){

//.......windmill stand............

    glPushMatrix();
    glTranslated(0,0,0);
    glScaled(2,6,1);
    glColor3f(77/256.0f, 77/256.0f, 0/256.0f);
    glBegin(GL_POLYGON);
        glVertex2d(0,0);
        glVertex2d(-1,-5);
        glVertex2d(1,-5);
    glEnd();
    glPopMatrix();

//.......windmill fans.....
    glPushMatrix();
    glRotated(spin,0,0,1);
    glColor3f(0/256.0f, 102/256.0f, 102/256.0f);
    glBegin(GL_POLYGON);

        glVertex2d(0.5,0.5);

        glVertex2d(10,5);
        glVertex2d(9,10);

        glVertex2d(0.5,1);
        glVertex2d(-0.5,1);

        glVertex2d(-9,10);
        glVertex2d(-10,5);

        glVertex2d(-0.5,0.5);
        glVertex2d(-0.5,-1);

        glVertex2d(-10,-5);
        glVertex2d(-9,-10);

        glVertex2d(-0.5,-1);
        glVertex2d(0.5,-1);

        glVertex2d(9,-10);
        glVertex2d(10,-5);

        glVertex2d(0.5,-0.5);
    glEnd();
    glPopMatrix();
//...........windmill center........
    glPushMatrix();
    glTranslated(0,0,0);
    glColor3f(255/256.0f, 153/256.0f, 0/256.0f);
        circle(2,2);
    glPopMatrix();
}

void move_ship(void){

    ship_tx         -=0.008;
    ship_smoke_ty1   +=0.005;
    ship_smoke_ty2   +=0.005;
    ship_smoke_t    -=0.0005;

    if(ship_tx < -65.0){
        ship_tx  =  33.0;
    }
    if(ship_smoke_ty1 > 33.0){
        ship_smoke_ty1 = 26.0;
        ship_smoke_ty2 = 26.0;
        ship_smoke_t  = 1.0;
    }
    glutPostRedisplay();
}

void ship(){
    glPushMatrix();
    glTranslated(ship_tx,ship_ty,0);

//........ship bottom..........
    glPushMatrix();
    glBegin(GL_POLYGON);
        glColor3f(32/256.0f,64/256.0f,96/256.0f);
        glVertex2d(11,0);
        glVertex2d(-11,0);
        glVertex2d(-15,12);
        glVertex2d(15,12);
    glEnd();
    glPopMatrix();
//..........ship top..........
    glPushMatrix();
    glBegin(GL_POLYGON);
        glColor3f(255/256.0f, 51/256.0f, 51/256.0f);
        glVertex2d(-11,12);
        glVertex2d(-11,20);
        glVertex2d(0,20);
        glVertex2d(0,15);
        glVertex2d(11,15);
        glVertex2d(11,12);
    glEnd();
    glPopMatrix();
//.........ship glass..........
    glPushMatrix();
    glTranslated(-8,16,0);
    glColor4f(230/256.0f, 255/256.0f, 255/256.0f,0.9f);
        circle(1.5,2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3,16,0);
    glColor4f(230/256.0f, 255/256.0f, 255/256.0f,0.9f);
        circle(1.5,2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(9,5,0);
    glColor4f(230/256.0f, 255/256.0f, 255/256.0f,0.9f);
        circle(1.5,2);
    glPopMatrix();
//........ship smoke1..........
    glPushMatrix();
    glTranslated(ship_smoke_tx1,ship_smoke_ty1,0);
    glColor4f(0.54f,0.54f,0.34f,ship_smoke_t);
        circle(1,1.5);
    glPopMatrix();
//........ship smoke2..........
    glPushMatrix();
    glTranslated(ship_smoke_tx2,ship_smoke_ty2,0);
    glColor4f(0.54f,0.54f,0.34f,ship_smoke_t);
        circle(1,1.5);
    glPopMatrix();

//..........ship pillar........
    glPushMatrix();
    glTranslated(1,15,0);
    glScaled(1,3,1);
    glColor3f(71/256.0f, 107/256.0f, 107/256.0f);
        glBegin(GL_QUADS);
            glVertex2d(0,0);
            glVertex2d(0,4);
            glVertex2d(3,4);
            glVertex2d(3,0);
        glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,27,0);
    glScaled(1.6,.2,1);
    glColor3f(71/256.0f, 107/256.0f, 107/256.0f);
        glBegin(GL_QUADS);
            glVertex2d(0,0);
            glVertex2d(0,4);
            glVertex2d(3,4);
            glVertex2d(3,0);
        glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(7,15,0);
    glScaled(1,3,1);
    glColor3f(71/256.0f, 107/256.0f, 107/256.0f);
        glBegin(GL_QUADS);
            glVertex2d(0,0);
            glVertex2d(0,4);
            glVertex2d(3,4);
            glVertex2d(3,0);
        glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(6,27,0);
    glScaled(1.6,.2,1);
    glColor3f(71/256.0f, 107/256.0f, 107/256.0f);
        glBegin(GL_QUADS);
            glVertex2d(0,0);
            glVertex2d(0,4);
            glVertex2d(3,4);
            glVertex2d(3,0);
        glEnd();
    glPopMatrix();

    glPopMatrix();
}

void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
        sky();
        moon();
    glPopMatrix();

    glPushMatrix();
        change_sky();
        sun();
    glPopMatrix();
    glutPostRedisplay();

    glPushMatrix();
        cloud1();
        move_cloude();
    glPopMatrix();
    glutPostRedisplay();

    glPushMatrix();
        river();
        ship();
    glPopMatrix();


    glPushMatrix();
        ground();
    glPopMatrix();

        grass_texture();
    glPushMatrix();
    glTranslated(-28,-15,0);
        house();
    glPopMatrix();

    glPushMatrix();
    glTranslated(25,-19.5,0);
        windmill();
    glPopMatrix();

    glFlush();
}

void my_mouse(int button, int state, int x, int y){


   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(move_spin_left);
         break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
			glutIdleFunc(move_spin_right);
         break;

      default:
         break;
   }
}
void my_keyboard(unsigned char key,int x,int y){
    switch (key){
    case 'r':
        glutIdleFunc(move_ship);
        break;
    case 'p':
        glutIdleFunc(NULL);
        break;
    case 's':
        glutIdleFunc(NULL);
        break;
    default:
        glutIdleFunc(move_ship);
        break;
    }
}

int main(){
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200,650);
    glutInitWindowPosition(50,10);
    glutCreateWindow("Test Code");
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    init();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(my_mouse);
    glutKeyboardFunc(my_keyboard);
    glutMainLoop();
    return 0;
}
