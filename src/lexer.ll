/* -*-C++-*- */

%option noyywrap

%{

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

#include <string.h>

#include "parser.h"

#define YY_NO_UNPUT

int linecount = 1;
%}

digit	[0-9]
number	"-"?{digit}+("."{digit}+)?
name	[_a-zA-Z]+

%%
"//"[^\n]*\n 	{ linecount++; } /* ignore comments, but count line */

abs             return KEY_ABS;
acos            return KEY_ACOS;
acosh           return KEY_ACOSH;
asin            return KEY_ASIN;
asinh           return KEY_ASINH;
background	return KEY_BACKGROUND;
blue		return KEY_BLUE;
camera		return KEY_CAMERA;
color		return KEY_COLOR;
colour		return KEY_COLOR;
diffuse		return KEY_DIFFUSE;
disc            return KEY_DISC;
equator		return KEY_EQUATOR;
finish		return KEY_FINISH;
green		return KEY_GREEN;
image_map	return KEY_IMAGE;
light_source	return KEY_LIGHT;
location	return KEY_LOCATION;
look_at		return KEY_LOOK;
pigment		return KEY_PIGMENT;
plane		return KEY_PLANE;
plane_point	return KEY_PLANEPNT;
pole		return KEY_POLE;
ppm		return KEY_PPM;
red		return KEY_RED;
reflection	return KEY_REFLECTION;
rgb		return KEY_RGB;
sky		return KEY_SKY;
sphere		return KEY_SPHERE;
triangle	return KEY_TRIANGLE;
triangle_point	return KEY_TRIANGLEPNT;
x               return KEY_X;
y               return KEY_Y;
z               return KEY_Z;

"{"		return LBRACE;
"}"		return RBRACE;
"<"		return LANGLE;
">"		return RANGLE;
"("             return LPAREN;
")"             return RPAREN;
","		return COMMA;
"+"             return PLUS;
"-"             return MINUS;
"*"             return TIMES;
"/"             return DIVIDED;
"."             return DOT;

{number}	{ yylval.value = atof(yytext); return NUMBER; }
\"[^\"]*\"	{ yylval.string = strdup(yytext+1);
		  yylval.string[strlen(yytext+1)-1] = '\0';
	          return STRING;
		}

{name}		return NAME;
\n 		{ linecount++; }
[ \t\r]		;

.		return UNCAUGHT;
%%
