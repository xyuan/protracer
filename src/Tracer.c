/*
 * This file is part of Protracer
 *
 * Protracer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Protracer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Protracer.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


/*************************************************************************\     
|  File: Tracer.c                                                         |
|                                                                         |
|  This is the main file for the tracer                                   |
|                                                                         |
\*************************************************************************/

#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "config.h"

#include "Scalar.h"

#include "Bitmap.h"
#include "PPMFile.h"
#include "Error.h"
/*#include "Timer.h"*/
#include "World.h"

#include "ObjectMods.h"
#include "Finish.h"
#include "SphereOptions.h"

#include "Parameters.h"

#include "Baseparse.h"


#define XPIX_MASK 0x1
#define YPIX_MASK 0x2
#define WIDTH_MASK 0x4
#define HEIGHT_MASK 0x8

void printWelcomeMessage( void )
{
    fprintf( stderr, "********************************************\n" );
    fprintf( stderr, "* "PACKAGE" "VERSION"                            *\n");
    fprintf( stderr, "* Who knew nice code could be this fast... *\n" );
    fprintf( stderr, "********************************************\n\n" );
    fflush( stderr );

}

World parse(FILE *input, scalar zoom, long xpix, long ypix, scalar width,
	    scalar height)
{
    extern int yyparse();

    extern FILE        *yyin;
    extern Parameters  global_parameters;
    extern ObjectList  global_objectList; 
    extern LightList   global_lightList;
    extern Color       global_background;
    extern Camera      global_camera;
    World the_world;

    global_parameters = Parameters_create(zoom, width, height, xpix, ypix );
    global_objectList = ObjectList_createEmpty();
    global_lightList = LightList_createEmpty();

    global_background = DEFAULT_BACKGROUND;

    yyin = input;
    yyparse();
    
    the_world = World_create( global_objectList,
                              global_lightList,
                              global_camera,
                              global_background);
    
    return the_world;
}

Bitmap trace( World w, int xpix, int ypix, int reflectionDepth,
              bool noShadowNoReflection )
{
    int x,y;
    
    Bitmap bm = Bitmap_create( xpix, ypix );

    for( y = 0 ; y < ypix ; y++ )
    {
        for( x = 0 ; x < xpix ; x++ )
        {
            Bitmap_setColorAt( bm, World_colorOfPixel( w, x, y,
                                                       reflectionDepth,
                                                       noShadowNoReflection ),
                               x, y );
        }
        fprintf( stderr, "%d%%\r", (int)((scalar)y/(scalar)ypix * 100) );
    }
    return bm;
}
     
static void usage(void)
{
  fprintf(stderr, PACKAGE"\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "   usage: "PACKAGE" [options] [input file]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "   -q, --no-shadows                          "
	  "no shadows or Reflecions will be"
	  "                                                used\n");
  fprintf(stderr, "   -r, --reflection-depth=REFLECTION_DEPTH   "
	  "set the reflection depth\n");
  fprintf(stderr, "   -z, --zoom-factor=ZOOM                    "
	  "set zoom factor\n");
  fprintf(stderr, "   -x, --x-pixels=X_PIX                      "
	  "set the pixel width of the\n"
	  "                                             resulting image\n");
  fprintf(stderr, "   -y, --y-pixels=Y_PIX                      "
	  "set the pixel height of the\n"
	  "                                             resulting image\n");
  fprintf(stderr, "   -w, --width=WIDTH                         "
	  "set picture width\n");
  fprintf(stderr, "   -e, --height                              "
	  "set picture height\n");
  fprintf(stderr, "   -o, --output=FILE                         "
	  "set output file\n");
  fprintf(stderr, "   -h, --help                                "
	  "print this help\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "If no input file is given, input is read from stdin.\n");
  fprintf(stderr, "Likewise, if no output file is given, output "
	  "(in PPM format) is written to\nstdout\n");
}

int main( int argc, char **argv )
{
    int c;
    extern char *optarg;
    int  opt_ind = 0;
    bool        noShadowNoReflection = FALSE;
    scalar      zoom = 1.0;
    long        xpix = 240;
    long        ypix = 240;
    scalar      width = 1.0;
    scalar      height = 1.0;
    char        flagsSet = 0;
    char        numFlagsSet = 0;
    long        errflg = 0;
    long        reflectionDepth = 5;

    World       the_world;
    Bitmap      result;
    PPMFile     ppm_out;
    char        *out_file = NULL;
    FILE        *in_file;

    static struct option long_options[] =
      {
	{"no-shadows", no_argument, 0, 'q'},
	{"reflection-depth", required_argument, 0, 'r'},
	{"zoom-value", required_argument, 0, 'z'},
	{"x-pixels", required_argument, 0, 'x'},
	{"y-pixels", required_argument, 0, 'y'},
	{"width", required_argument, 0, 'w'},
	{"height", required_argument, 0, 'e'},
	{"output-file", required_argument, 0, 'o'},
	{"help", no_argument, 0, 'h'},
	{0, 0, 0, 0}
      };

    while ((c = getopt_long(argc, argv, "qhr:z:x:y:w:e:o:", long_options,
			    &opt_ind) ) != EOF )
    {
      switch( c ) 
	{
	    case 'q':
		noShadowNoReflection = TRUE;
		fprintf( stderr, "- No Shadows or Reflecions will be used\n" );
		break;
	    case 'r':
                reflectionDepth = atol( optarg );
		fprintf( stderr, "- reflectionDepth = %ld\n", atol( optarg ) );
                break;
	    case 'z':
		zoom = atof( optarg );
		fprintf( stderr, "- Zoom value = %f\n", atof( optarg ) );
                break;		
	    case 'x':
		xpix = atol( optarg );
		fprintf( stderr, "- xpix = %ld\n", atol( optarg ) );
		flagsSet |= XPIX_MASK;
		numFlagsSet++;
                break;		
	    case 'y':
		ypix = atol( optarg );
		fprintf( stderr, "- ypix = %ld\n", atol( optarg ) );
		flagsSet |= YPIX_MASK;
		numFlagsSet++;
                break;		
	    case 'w':
		width = atof( optarg );
		fprintf( stderr, "- width = %ld\n", atol( optarg ) );
		flagsSet |= WIDTH_MASK;
		numFlagsSet++;
                break;		
	    case 'e':
		height = atof( optarg );
		fprintf( stderr, "- height = %ld\n", atol( optarg ) );
		flagsSet |= HEIGHT_MASK;
		numFlagsSet++;
                break;
	    case 'o':
	        out_file = strdup(optarg);
		break;
	    case 'h':
		errflg++;
		break;
	}
    }
    
    if( errflg > 0 ) /* Any errors in commandline? */
    {
      usage();
      exit(0);
    }

    /* Welcome Message. */
    printWelcomeMessage();
    
    /* Check if only three args, if so calculate the last one. */
    if( numFlagsSet == 3 )
    {
	if( !(flagsSet & XPIX_MASK) )
	{
	    xpix = width / height * ypix;
	    fprintf( stderr, "Calculated xpix = %ld\n", xpix );
	}
	else if( !(flagsSet & YPIX_MASK) )
	{
	    ypix = height / width * xpix;
	    fprintf( stderr, "Calculated ypix = %ld\n", ypix );
	}
	else if( !(flagsSet & WIDTH_MASK) )
	{
	    width = (height * xpix) / ypix;
	    fprintf( stderr, "Calculated width = %f\n", width );
	}
	else if( !(flagsSet & HEIGHT_MASK) )
	{
	    height = (width * ypix) / xpix;
	    fprintf( stderr, "Calculated height = %f\n", height );
	}
    }
    
    /* open in file */
    if (argv[optind] != NULL) {
      in_file = fopen(argv[optind], "r");
    } else {
      in_file = stdin;
    }

    the_world = parse(in_file, zoom, xpix, ypix, width, height );
 
    /* Start the tracing */
    
    result = trace( the_world, xpix, ypix, reflectionDepth,
                    noShadowNoReflection );

    /*timeExpired = Timer_getMilliseconds();*/ /* Stop timer. */
    fprintf( stderr, "100%% - done!\n" );

    if (out_file != NULL)
      ppm_out = PPMFile_openOut(out_file, PPM_BINARY );
    else
      ppm_out = PPMFile_openStdOut(PPM_BINARY);

    PPMFile_writeBitmap( ppm_out, result );
    
    return( 0 ); /* Success */
}
