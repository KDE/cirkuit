/* Output from p2c, the Pascal-to-C translator */
/* From input file "dpic.p" */


/* dpic translator program.

   Copyright 1995-2008 J. D. Aplevich.  You may use or copy this
   file, but you may not sell it without permission.

   The p2c-dependent, debugging-dependent, and machine-dependent
   comment symbols are stripped out by the makefile or by p2c */



#include "p2c.h"
#include <time.h>


/*D,logD*/

/*X program dpic(input,output); X*/

/* exit label for parser errors      */

/* include dp0.h */
/* dp0.x */
/* Global definitions                                                 */

#define Version         "dpic version 08.Jun.08"

#define distmax         1e25
/*GH distmax = MaxReal; HG*/
#define mdistmax        (-distmax)
#define pi              3.1415926535897931
#define ln10            2.3025850929940459

/*UGH maxint = 2147483647; HGU*/

/* Parser constants                                                   */

#define next            1
#define kind            2
#define symb            3
#define err             4
#define rs              3
#define prod            4
#define lb              3

/* include parscst.i */
#define symbmax         241
#define prodmax         177
#define lrmax           4594
#define lxmax           457
/*B%include parscstB*/

/* include parscdc.i */
#define METAGOAL1       0
#define input1          1
#define input2          2
#define picture1        3
#define picture2        4
#define NL1             5
#define NL2             6
#define start1          7
#define start2          8
#define start3          9
#define elementlist1    10
#define elementlist2    11
#define elementlist3    12
#define term1           13
#define term2           14
#define term3           15
#define term4           16
#define element1        17
#define element2        18
#define element3        19
#define element4        20
#define element5        21
#define element6        22
#define element7        23
#define element8        24
#define element9        25
#define element10       26
#define element11       27
#define element12       28
#define element13       29
#define lbrace1         30
#define namedbox1       31
#define namedbox2       32
#define suffix1         33
#define suffix2         34
#define position1       35
#define position2       36
#define position3       37
#define position4       38
#define assignlist1     39
#define assignlist2     40
#define command1        41
#define command2        42
#define command3        43
#define command4        44
#define command5        45
#define command6        46
#define command7        47
#define command8        48
#define command9        49
#define command10       50
#define optnl1          51
#define optnl2          52
#define ifpart1         53
#define elsehead1       54
#define for1            55
#define for2            56
#define stringexpr1     57
#define stringexpr2     58
#define string1         59
#define string2         60
#define assignment1     61
#define assignment2     62
#define assignment3     63
#define assignment4     64
#define expression1     65
#define expression2     66
#define expression3     67
#define expression4     68
#define expression5     69
#define ifhead1         70
#define setlogic1       71
#define logexpr1        72
#define logexpr2        73
#define forhead1        74
#define forincr1        75
#define do1             76
#define do2             77
#define by1             78
#define by2             79
#define resetlist1      80
#define resetlist2      81
#define defhead1        82
#define defhead2        83
#define sprintf1        84
#define sprintf2        85
#define exprlist1       86
#define exprlist2       87
#define object1         88
#define object2         89
#define object3         90
#define object4         91
#define object5         92
#define object6         93
#define object7         94
#define object8         95
#define object9         96
#define object10        97
#define object11        98
#define object12        99
#define object13        100
#define object14        101
#define object15        102
#define object16        103
#define object17        104
#define object18        105
#define object19        106
#define object20        107
#define object21        108
#define object22        109
#define object23        110
#define object24        111
#define object25        112
#define object26        113
#define object27        114
#define object28        115
#define object29        116
#define openblock1      117
#define block1          118
#define block2          119
#define block3          120
#define block4          121
#define optexp1         122
#define optexp2         123
#define closeblock1     124
#define pair1           125
#define pair2           126
#define withobj1        127
#define withobj2        128
#define shift1          129
#define shift2          130
#define shift3          131
#define location1       132
#define location2       133
#define location3       134
#define location4       135
#define location5       136
#define place1          137
#define place2          138
#define place3          139
#define place4          140
#define place5          141
#define factor1         142
#define factor2         143
#define factor3         144
#define placename1      145
#define placename2      146
#define placename3      147
#define placename4      148
#define nth1            149
#define nth2            150
#define nth3            151
#define primobj1        152
#define primobj2        153
#define primobj3        154
#define primobj4        155
#define ncount1         156
#define ncount2         157
#define ncount3         158
#define logprod1        159
#define logprod2        160
#define logval1         161
#define logval2         162
#define primary1        163
#define primary2        164
#define primary3        165
#define primary4        166
#define primary5        167
#define primary6        168
#define primary7        169
#define primary8        170
#define primary9        171
#define primary10       172
#define primary11       173
#define primary12       174
#define primary13       175
#define primary14       176
#define primary15       177

/* include lxcst.h */
/*D XAND = 37; D*/
#define XBLOCK          27
#define XCOMMENT        43
#define XLcolrspec      139
#define XLcolour        140
#define XDOUBLEHEAD     152
#define XDc             100
#define XDe             96
#define XDend           99
#define XDn             94
#define XDne            90
#define XDnw            92
#define XDs             95
#define XDse            91
#define XDstart         98
#define XDsw            93
#define XDw             97
#define XEMPTY          2
#define XEND            47
#define XERROR          3
#define XFOR            85
#define XGG             107
#define XGT             5
#define XLBRACE         24
#define XLBRACKET       22
#define XLEFTHEAD       150
#define XLKWDS          45
#define XLL             106
#define XLT             4
#define XLabel          40
#define XLabove         147
#define XLabs           114
#define XLacos          115
#define XLarc           162
#define XLarcrad        168
#define XLarg           44
#define XLarrow         164
#define XLarrowhd       149
#define XLarrowhead     185
#define XLarrowht       169
#define XLarrowwid      170
#define XLasin          116
#define XLat            56
#define XLatan2         129
#define XLbelow         148
#define XLbox           159
#define XLboxht         171
#define XLboxrad        172
#define XLboxwid        173
#define XLccw           7
#define XLcenter        144
#define XLchop          61
#define XLcircle        160
#define XLcirclerad     174
#define XLcoloneq       31
#define XLcontinue      60
#define XLcorner        89
#define XLcos           117
#define XLcw            6
#define XLdashed        136
#define XLdashwid       175
#define XLdefine        80
#define XLdiameter      112
#define XLdirecton      153
#define XLdiveq         35
#define XLdo            86
#define XLdotted        135
#define XLdown          155
#define XLellipse       161
#define XLellipseht     176
#define XLellipsewid    177
#define XLelse          84
#define XLenvvar        167
#define XLeq            30
#define XLexp           118
#define XLexpe          119
#define XLfillval       186
#define XLfloat         38
#define XLfloor         127
#define XLfrom          54
#define XLfunc1         113
#define XLfunc2         128
#define XLheight        109
#define XLint           120
#define XLinvis         137
#define XLlastenv       190
#define XLlastsc        184
#define XLleft          157
#define XLline          163
#define XLlineht        178
#define XLlinethick     187
#define XLlinetype      133
#define XLlinewid       179
#define XLljust         145
#define XLlog           121
#define XLloge          122
#define XLlogic         101
#define XLmax           130
#define XLmaxpsht       188
#define XLmaxpswid      189
#define XLmin           131
#define XLminuseq       33
#define XLmove          165
#define XLmoveht        180
#define XLmovewid       181
#define XLmulteq        34
#define XLname          39
#define XLoutlined      141
#define XLparam         108
#define XLpath          138
#define XLpluseq        32
#define XLpmod          132
#define XLprimitiv      158
#define XLradius        111
#define XLremeq         36
#define XLright         156
#define XLrjust         146
#define XLscale         190
#define XLshaded        142
#define XLsign          123
#define XLsin           124
#define XLsolid         134
#define XLspline        166
#define XLsqrt          125
#define XLstring        42
#define XLtan           126
#define XLtextht        182
#define XLtextoffset    183
#define XLtextpos       143
#define XLtextwid       184
#define XLthen          59
#define XLto            55
#define XLtroff         41
#define XLundefine      81
#define XLup            154
#define XLwidth         110
#define XNL             15
#define XRBRACE         25
#define XRIGHTHEAD      151
#define XSEMICOLON      15
#define XSTAR           10
#define XSTART          46

/* Machine constants                                                  */
#define ordMINCH        0   /* first element of type character    */
/* last element of type character,
   newline, tab, CR, ETX              */

#define ordMAXCH        255
#define ordNL           10
#define ordTAB          9
#define ordCR           13
#define ordETX          3
/*B
    ordMAXCH = 255; ordNL = 37; ordTAB = 5; ordCR = 13; ordETX = 3 B*/

#define maxbval         16383
/* must be > CHBUFSIZ-2 */

/* Lexical parameters                                                 */
#define CHBUFSIZ        4095   /* size of chbuf arrays, input record */
#define FILENAMELEN     1024   /* max length of file names           */

/* Lalr machine parameters                                            */
#define STACKMAX        255   /* size of attstack and parsestack    */
#define REDUMAX         128   /* size of reduction buffer           */
#define ERRMAX          3   /* max no of error messages per line  */
#define MAXERRCOUNT     3   /* max no of errors before giving up  */


/* Lexical types                                                      */
typedef short chbufinx;

typedef uchar symbol;

typedef short lxinx;

typedef uchar production;

typedef Char chbufarray[CHBUFSIZ + 1];
typedef Char mstring[FILENAMELEN];

/* Environment variable index */
/*GH1HG*/
typedef uchar environx;


/* Lalr machine types                                                 */
typedef uchar stackinx;

typedef short redubufrange;

typedef struct reduelem {
  /* packed */
  /*D oldtop, D*/
  stackinx newtop;
  production prod_;
} reduelem;

/* Message types                                                      */
typedef char errmsginx;

#define TeX             0
#define tTeX            1
#define PSTricks        2
#define MFpic           3
#define MPost           4
#define PGF             5
#define PS              6
#define PSfrag          7
#define pict2e          8
#define xfig            9

/* Production types */
/*,PSmps*/

/* For storing names */

typedef struct nametype {
  /* packed */
  /* Sun compiler complains otherwise */
  Char *segmnt;
  chbufinx seginx, len;
  double val;
  struct nametype *next_;
} nametype;

/* Lexical input for loops and macros */

typedef struct fbuffer {
  Char *carray;
  int savedlen, readx, attrib;
  struct fbuffer *higherb, *prevb, *nextb;
} fbuffer;

/* Macro argument list pointer */

typedef struct arg {
  fbuffer *argbody;
  struct arg *higherb, *nextb;
} arg;

typedef struct postype {
  /* packed */
  double xpos, ypos;
} postype;

typedef double envarray[XLlastenv - XLenvvar];


/* maybe textp should be a primitivep to allow text to have the full
   properties of boxes */
/* To save some space:
   shadedp: box, circle, ellipse
   outlinep: box, circle, ellipse, line, arc, spline
   textp: not for block: maybe delete the vars pointer
   */

typedef struct primitive {
  nametype *name, *textp, *outlinep, *shadedp;
  struct primitive *parent, *son, *next_;
  postype aat;
  double lparam, lthick;
  int direction, spec, ptype;
  union {
    struct {
      double boxheight, boxwidth, boxfill, boxradius;
    } Ubox;
    struct {
      double blockheight, blockwidth;
      postype here;
      nametype *vars;
      double *env;
    } UEMPTY7;
    struct {
      double cfill, radius;
    } Ucircle;
    struct {
      double elheight, elwidth, efill;
    } Uellipse;
    struct {
      /* XLarc:( endpos.xpos,endpos.ypos: real );
                  endpos.xpos, endpos.ypos */
      postype endpos;
      double height, width, lfill, aradius;
      int atype;
    } Uline;
  } UU;
} primitive;

/* To force optimum dynamic storage of primitives: */

typedef struct XLboxprimitive {
  nametype *name, *textp, *outlinep, *shadedp;
  primitive *parent, *son, *next_;
  postype aat;
  double lparam, lthick;
  int direction, spec, ptype;
  union {
    struct {
      double boxheight, boxwidth, boxfill, boxradius;
    } Ubox;
  } UU;
} XLboxprimitive;

typedef struct XLcircleprimitive {
  nametype *name, *textp, *outlinep, *shadedp;
  primitive *parent, *son, *next_;
  postype aat;
  double lparam, lthick;
  int direction, spec, ptype;
  union {
    struct {
      double cfill, radius;
    } Ucircle;
  } UU;
} XLcircleprimitive;

typedef struct XLellipseprimitive {
  nametype *name, *textp, *outlinep, *shadedp;
  primitive *parent, *son, *next_;
  postype aat;
  double lparam, lthick;
  int direction, spec, ptype;
  union {
    struct {
      double elheight, elwidth, efill;
    } Uellipse;
  } UU;
} XLellipseprimitive;

typedef struct XLlineprimitive {
  nametype *name, *textp, *outlinep, *shadedp;
  primitive *parent, *son, *next_;
  postype aat;
  double lparam, lthick;
  int direction, spec, ptype;
  union {
    struct {
      postype endpos;
      double height, width, lfill, aradius;
      int atype;
    } Uline;
  } UU;
} XLlineprimitive;

typedef struct XLabelprimitive {
  nametype *name, *textp, *outlinep, *shadedp;
  primitive *parent, *son, *next_;
  postype aat;
  double lparam, lthick;
  int direction, spec, ptype;
} XLabelprimitive;

/* Attribute stack types                                              */

typedef struct attribute {
  chbufinx chbufx;
  int length;
  primitive *prim, *root;
  nametype *varname;
  double xval, yval, startchop, endchop;
  int lexval, state;
} attribute;

typedef attribute attstacktype[STACKMAX + 1];

/* Parser types */

typedef struct stackelm {
  stackinx link;
  int table;
} stackelm;

typedef stackelm tparsestack[STACKMAX + 1];


typedef struct _REC_errmsg {
  int no, col, symb_;
} _REC_errmsg;


/*BXdefXB*/
/* Machine-dependent characters                                       */
Char tabch, nlch, crch, etxch;

/* File names                                                         */
FILE *input, *output, *stderr_;   /*G asmname 'std_err'; G*/
FILE *copyin;   /*G asmname 'copy_in'; G*/
/*D log: text; D*/
/*DG asmname 'log_file'; GD*/

mstring infile;   /* name of current input file         */
/*X infile: string; X*/

boolean inputeof;   /* end of input flag                  */
int argct;   /* argument counter for options       */
char drawmode;   /* output conversion                  */
boolean safemode;   /* disable sh and copy                */
/*D oflag: integer; D*/

/* Lexical analyzer character buffer                                  */
Char *chbuf;
chbufinx chbufi, oldbufi;   /* character buffer index             */

/* Lexical variables                                                  */
Char ch;   /* current character                  */
short newsymb;   /* current lexical symbol             */
int inpic, lexsymb;
_REC_errmsg errmsg[ERRMAX + 1];
boolean inlogic;   /* set < to << in logical context     */
fbuffer *inbuf, *savebuf, *freebuf;

/* Error handling                                                     */
int errcount;   /* becomes nonzero when errors found  */
errmsginx errmp;   /* index of error messages in errmsg  */
int lineno;   /* current input line number          */

/* Production variables                                               */
attribute *attstack;
/*D stackhigh: integer;D*/
redubufrange reduinx, redutop;
reduelem redubuf[REDUMAX + REDUMAX + 1];   /* reduction buffer    */

double floatvalue;   /* numerical value of floats read     */
primitive *envblock;

double north, south, east, west;
    /* compass corners of a primitive     */
double xfheight;   /* for calculating xfig coordinates   */
Char *freeseg;   /* segment open to store strings      */
chbufinx freex;   /* next free location                 */
Char *tmpbuf;   /* buffer for snprintf or sprintf     */
double scale, fsc;   /* scale factor and final scale factor*/
int splcount, spltot;   /* spline depth counter               */
double lastfillval;   /* last-used fill density             */
double lastthick;   /* last-used line thickness           */
int printstate;   /* for passing output state info      */

/* Global tables for easy C conversion.
   Alternative: use run-time space    */
short lr[lrmax + 1]={
0,   5,1,   0,  0,   0,  10,6,   0, -1,  15,3620,1,   1,  1,
0,  20,1,  46,  7,  25, 500,2,  17,143,  30, 515,2, 167,163,
35, 505,2,  39,164,  40, 490,2,  38,165,  45, 415,2,   8,166,
50, 325,2,  82,170,  55, 315,2, 113,172,  60, 305,2, 128,173,
65, 285,2,  40,145,  70, 210,2,  89,139,  75, 205,2,  68,141,
80, 180,2,  70,151,  85, 175,2,  28,157,  90,  95,2,  24,158,
0,4325,4,   0,  7, 100, 630,1,  11,  2, 105, 575,1,  12, 67,
110, 500,1,  17,143, 115, 515,1, 167,163, 120, 505,1,  39,164,
125, 490,1,  38,165, 130, 415,1,   8,166, 135, 325,1,  82,170,
140, 315,1, 113,172, 145, 305,1, 128,173, 150, 285,1,  40,145,
155, 210,1,  89,139, 160, 205,1,  68,141, 165, 180,1,  70,151,
170, 175,1,  28,157,   0,  95,1,  24,158, 100, 630,1,  11,  2,
0,4285,3,   0,151,   0, 190,1,  69,  3, 195, 200,2,  70,150,
0,4330,4,   0,149,   0,4285,3,   2,150,   0, 300,3,   0,141,
215,1615,1,  63,  4, 220, 285,1,  40,145, 225, 180,1,  70,151,
165, 230,1,  38,156,   0, 185,3,   0,-156, 240, 275,1, 158,  5,
245, 270,1,  27,153, 250, 265,1,  42,154,   0, 255,1,  22,155,
0, 260,1,  23,  6,   0,4293,3,   1,155,   0,4293,3,   0,-154,
0,4293,3,   0,-153,   0,4293,3,   0,-152,   0,4261,3,   1,146,
290, 295,2,  22, 34,   0,3713,6,   0, 33, 100, 630,1,  11,  2,
0,4133,3,   0,-134,   0, 310,1,   8,  7, 100, 630,1,  11,  2,
0, 320,1,   8,  7, 100, 630,1,  11,  2,   0, 330,1,   8,  7,
95,1565,1,   9,  8, 340, 385,2, 108,169, 345, 360,2,  26,147,
350, 355,2,  89,138,   0,4335,4,   0,137,   0, 300,3,   1,138,
220, 375,1,  40,  9, 240, 275,1, 158,  5,   0,4261,3,   3,148,
290, 295,2,  22, 34,   0,4261,3,   3,147,   0,4317,3,   1,169,
395, 790,1,  72, 10, 400, 785,1,  73,168, 405, 795,1,  10,135,
0, 410,1,  13,136, 110, 500,1,  17, 11, 420, 630,1,  11, 12,
425, 575,1,  12, 67, 430,1230,1,  42, 59, 435,1160,1,  39, 61,
440,1125,1, 167, 63, 445, 545,1,  87, 84, 450, 500,1,  17,143,
455, 415,1,   8,132, 460, 490,1,  38,165, 465, 325,1,  82,170,
470, 315,1, 113,172, 475, 305,1, 128,173, 480, 210,1,  89,139,
485, 205,1,  68,141, 160, 285,1,  40,145, 495, 230,4,  69,156,
0,4340,4,   0,165, 115, 515,1, 167, 13, 290, 295,2,  22, 34,
0,4317,3,   1,164,   0,4317,3,   0,163,   0,4233,3,   1,143,
530, 535,2,  16,144,   0,4345,4,   0,142, 110, 500,1,  17, 11,
0,4233,3,   2,144,   0, 550,1,   8,  7,   0, 555,1,  42, 14,
560, 565,2,  20, 85,   0,4350,4,   0, 84, 100, 630,1,  11,  2,
0,3673,3,   0,-13, 110, 500,1,  17, 11, 585, 620,2,  10, 14,
590, 610,2,  13, 15, 595, 600,2,  14, 16,   0,4355,4,   0, 67,
110, 500,1,  17, 11,   0,3673,3,   2, 16, 110, 500,1,  17, 11,
0,3673,3,   2, 15, 110, 500,1,  17, 11,   0,3673,3,   2, 14,
110, 500,1,  17, 11, 640, 620,2,  10, 14, 645, 610,2,  13, 15,
650, 600,2,  14, 16,   0,4360,4,   0, 66, 660, 620,2,  10, 14,
665, 610,2,  13, 15, 670, 600,2,  14, 16,   0,4365,4,   0, 65,
680, 745,2,  20, 87, 685, 720,2,  11, 68, 690, 695,2,  12, 69,
0,4370,4,   0, 86, 110, 500,1,  17, 11, 705, 620,2,  10, 14,
710, 610,2,  13, 15, 715, 600,2,  14, 16,   0,4375,4,   0, 69,
110, 500,1,  17, 11, 730, 620,2,  10, 14, 735, 610,2,  13, 15,
740, 600,2,  14, 16,   0,4380,4,   0, 68, 100, 630,1,  11,  2,
0,4077,3,   2, 87,   0,1220,3,   4, 85, 765, 795,2,  10,135,
770, 410,2,  13,136, 775, 790,2,  72,167, 780, 785,2,  73,168,
0,4125,6,   0,129,   0,4317,3,   1,168,   0,4317,3,   1,-167,
110, 500,1,  17, 11,   0,4133,3,   2,135, 810,1005,2,  11,130,
815, 820,2,  12,131,   0,4385,4,   0,126, 825, 845,1,   8, 15,
830, 210,1,  89,139, 215, 205,1,  68,141, 840, 355,2,  89,138,
350, 360,2,  26,147, 850, 630,1,  11,  2, 855, 575,1,  12, 67,
860, 415,1,   8,132, 865, 210,1,  89,139, 870, 205,1,  68,141,
875, 500,1,  17,143, 880, 285,1,  40,145, 885, 515,1, 167,163,
890, 505,1,  39,164, 895, 490,1,  38,165, 900, 325,1,  82,170,
905, 315,1, 113,172, 160, 305,1, 128,173, 915,1060,1,  66, 16,
920,1025,1,  63, 37, 925, 960,1,   4, 38, 930, 940,1,  20,125,
935, 720,1,  11, 68,   0, 695,1,  12, 69, 100, 630,1,  11,  2,
950, 720,2,  11, 68, 955, 695,2,  12, 69,   0,4390,4,   0,125,
850, 630,1,  11,  2,   0,3741,3,   0,-35,   0, 975,1,  20, 17,
850, 630,1,  11,  2,   0, 985,1,   5, 18,   0,4125,6,   0,129,
995,1005,2,  11,130,1000, 820,2,  12,131,   0,4395,4,   0, 38,
825, 845,1,   8, 15,1015, 795,2,  10,135,1020, 410,2,  13,136,
0,4400,4,   0,130,   0,1030,1,  64, 19,   0,1035,1,  65, 20,
0,1040,1,  66, 21, 850, 630,1,  11,  2,   0,1050,1,  67, 22,
850, 630,1,  11,  2,   0,3741,3,   7, 37, 850, 630,1,  11,  2,
0,1070,1,  67, 22, 850, 630,1,  11,  2,   0,3741,3,   4, 36,
1085,1105,1,   9, 23,   0,1090,1,  20,133, 850, 630,1,  11,  2,
0,1100,1,   9, 24,   0,4133,3,   4,133,   0,4133,3,   2,132,
1115, 795,2,  10,135,1120, 410,2,  13,136,   0,4405,4,   0,131,
1130,1135,2,  30, 63,   0, 515,4,   0,163,1140, 630,1,  11,  2,
1145, 575,1,  12, 67,1150,1160,1,  39, 61,1155,1125,1, 167, 63,
120, 500,1,  17,143, 290, 295,2,  22, 34,1170,1175,2,  30, 61,
0, 510,4,   0,164,1140, 630,1,  11,  2,   0,3909,3,   3, 62,
1190, 720,2,  11, 68,1195, 695,2,  12, 69,   0,4410,4,   0, 61,
0,3909,3,   2, 64,1210, 720,2,  11, 68,1215, 695,2,  12, 69,
0,4415,4,   0, 63,   0,1225,1,   9, 24,   0,3901,3,   1,-60,
0,3901,3,   0, 59,1240,1245,2, 101,162,   0,4420,4,   0,159,
100, 630,1,  11,  2,1255, 720,2,  11, 68,1260, 695,2,  12, 69,
0,4425,4,   0,162,   0,3817,3,   0,-39,   0,3857,3,   0,-57,
1280,1285,2,  18,160,   0,4430,4,   0, 72, 100, 630,1,  11,  2,
1295, 720,2,  11, 68,1300, 695,2,  12, 69,   0,4435,4,   0,161,
1310,1245,2, 101,162,   0,4440,4,   0,160,1320,1420,2,   5,176,
1325,1350,2,   4,177,1330, 720,2,  11, 68,1335, 695,2,  12, 69,
1340,1060,2,  66, 36,1345,1025,2,  63, 37,1300, 940,2,  20,125,
1355, 630,1,  11,  2,1360, 575,1,  12, 67,1365, 500,1,  17,143,
1370, 415,1,   8,132,1375, 515,1, 167,163, 455, 505,1,  39,164,
1385,1415,1,   9, 25,1390, 720,1,  11, 68,1395, 695,1,  12, 69,
1400,1060,1,  66, 36,1405,1025,1,  63, 37,1410, 960,1,   4, 38,
0, 940,1,  20,125,   0,4317,3,   4,177, 100, 630,1,  11,  2,
930,1430,1,   9, 26,   0,4317,3,   4,176,1440,1475,1,   9, 23,
0,1445,1,  20, 40,1450,1460,1,  39, 27,   0,1455,1, 167, 63,
0,1135,1,  30, 28, 290, 295,2,  22, 34,   0,1175,1,  30, 28,
0,3817,3,   2, 40,   0,4317,3,   2,175,1485,1505,1, 101, 29,
0,1490,1,  11, 58,1495,1230,1,  42, 30,   0, 545,1,  87, 84,
0,3857,3,   2, 58,1495,1230,1,  42, 30,1485,1515,1,   9, 31,
0,4317,3,   4,174,1525,1545,1,   9, 32,   0,1530,1,  19, 73,
100, 630,1,  11,  2,1540,1285,2,  18,160,   0,4445,4,   0, 73,
0,4317,3,   2,166,   0,4133,3,   2,136, 930,1560,1,   9, 26,
0,4317,3,   3,171,   0,4317,3,   2,170, 930,1575,1,   9, 26,
0,4317,3,   3,172, 930,1585,1,  20, 33, 100, 630,1,  11,  2,
930,1595,1,   9, 26,   0,4317,3,   5,173, 930,1605,1,  23, 34,
0,3713,3,   2, 34,   0,4261,3,   1,145, 220, 285,1,  40,  9,
1625, 360,2,  26,147,   0,4450,4,   0,140,1635, 360,2,  26,147,
0,4455,4,   0,139, 930,1645,1,  29, 35,   0, 185,3,   2,157,
930,1655,1,  25, 36,   0, 185,3,   2,158,1665, 620,2,  10, 14,
1670, 610,2,  13, 15,1675, 600,2,  14, 16,1680, 500,2,  17,143,
1685, 515,2, 167,163,1690, 505,2,  39,164,1695, 490,2,  38,165,
1700, 415,2,   8,166,1705, 325,2,  82,170,1710, 315,2, 113,172,
1715, 305,2, 128,173,1720, 285,2,  40,145,1725, 210,2,  89,139,
1730, 205,2,  68,141,1735, 180,2,  70,151,1740, 175,2,  28,157,
1745,  95,2,  24,158,   0,4460,4,   0,  8,1755, 620,2,  10, 14,
1760, 610,2,  13, 15,1765, 600,2,  14, 16,   0,4465,4,   0,  9,
1775,1785,1,  15, 37,   0,1780,1,   3,  6,   0,3625,3,   0, -6,
0,3625,3,   0, -5,1795,3015,2,  40, 18,1800,3000,2, 153, 21,
1805,2995,2,  41, 22,1810,2920,2,  79, 28,1815,2905,2,  77, 29,
1820,2440,2,  74, 41,1825,2405,2,  76, 44,1830,2390,2,  78, 46,
1835,2375,2,  75, 47,1840,2320,2,  81, 49,1845,2980,6,  24, 30,
1850,2155,2,  60,116,1855,1460,2,  39, 61,1860,1455,2, 167, 63,
1865,2135,2,  80, 82,1870,2040,2,  85, 74,1875,1935,2, 158,118,
1880,2115,6,  83, 71,1885,1905,6,  22,117,1890,1905,6,  27,117,
1895,1230,2,  42, 59,1900, 545,2,  87, 84,   0,3645,6,   0, 10,
1910,1920,1,  22, 38,   0,1915,1,  27,121,   0,2290,3,   1,121,
1795,3015,2,  40, 18,1930,1490,2,  11, 58,   0,4470,4,   0,119,
1940, 630,2,  11, 66,1945, 575,2,  12, 67,1950, 500,2,  17,143,
1955, 515,2, 167,163,1960, 505,2,  39,164,1965, 490,2,  38,165,
1970, 415,2,   8,166,1975, 325,2,  82,170,1980, 315,2, 113,172,
1985, 305,2, 128,173,1990, 285,2,  40,145,1995, 210,2,  89,139,
2000, 205,2,  68,141,2005, 180,2,  70,151,2010, 175,2,  28,157,
2015,  95,2,  24,158,   0,4093,6,   0,122,2025, 720,2,  11, 68,
2030, 695,2,  12, 69,   0,4475,4,   0,123,   0,2290,3,   1,118,
1450,1460,1,  39, 27,1440,2050,1,  55, 39, 100, 630,1,  11,  2,
2060, 720,1,  11, 40,2065, 695,1,  12, 69,2070,2105,1,  86, 76,
0,2075,1,  58, 78,2080,2085,2,  10, 79,   0,4480,4,   0, 78,
0,2090,3,   1, 79, 100, 630,1,  11,  2, 930,2100,1,  86, 41,
0,2110,3,   2, 77,   0,2110,3,   0, 76,   0,2300,3,   4, 74,
0,2120,1,  83, 42, 100, 630,1,  11,  2,1525,2130,1,  59, 43,
0,2310,3,   3, 70,2140,2150,1,  39, 44,   0,2145,1,  40, 83,
0,2340,3,   1, 83,   0,2340,3,   1, 82,   0,4085,3,   0,116,
2165,2275,1,  89, 45,2170,2260,1,  98,112,2175,2245,1,  99,113,
2180,2200,1,  26,115,2185, 630,1,  11, 66,2190, 575,1,  12, 67,
865, 415,1,   8,132, 930, 940,1,  20, 33,   0,2205,1,  40, 46,
290, 295,2,  22, 34,2215,2220,2,  56,115,   0,4485,4,   0,128,
850, 630,1,  11,  2,   0,4085,3,   5,115,   0,2235,1,  56, 47,
850, 630,1,  11,  2,   0,4085,3,   3,114,   0,2250,1,  56, 47,
850, 630,1,  11,  2,   0,4085,3,   3,113,   0,2265,1,  56, 47,
850, 630,1,  11,  2,   0,4085,3,   3,112, 210,2280,1,  56, 48,
850, 630,1,  11,  2,   0,4085,3,   3,111,   0,4085,3,   0,-88,
1795,3015,2,  40, 18,   0,2305,1,  24, 49,1795,3015,2,  40, 18,
0,2315,1,  24, 49,1795,3015,2,  40, 18,2325,2335,1,  39, 44,
0,2330,1,  40, 50,   0,2990,3,   1, 50,   0,2990,3,   1, 49,
2345,1785,2,  15,  5,2350,1780,2,   3,  6,   0,3829,6,   0,-51,
0,3829,3,   0,-52,   0,2365,1,  24, 49,   0,2370,1,  25, 50,
0,2990,3,   3,-48,1495,1230,1,  42, 30,2385,1490,2,  11, 58,
0,4490,4,   0, 47,1495,1230,1,  42, 30,2400,1490,2,  11, 58,
0,4495,4,   0, 46,2410,2415,2, 167, 80,   0,4500,4,   0, 44,
0,2420,3,   0, 80,2425,2430,2,  20, 81,   0,4505,4,   0, 45,
0,2435,1, 167, 51,   0,2420,3,   2, 81,2445, 630,1,  11, 12,
2450, 575,1,  12, 67,2455,1230,1,  42, 59,2460, 500,1,  17,143,
2465, 415,1,   8,132,1370, 545,1,  87, 84,2475,1490,2,  11, 58,
0,4510,4,   0, 43,   0,2990,3,   1, 42,2490, 720,2,  11, 68,
2495, 695,2,  12, 69,2500,1060,2,  66, 36,2505,1025,2,  63, 37,
2510, 960,2,   4, 38,2515, 940,2,  20,125,   0,4515,4,   0, 41,
2525,2885,2,  48, 89,2530,2865,2,  49, 90,2535,2845,2,  50, 91,
2540,2825,2,  51, 92,2545,2805,2,  52, 93,2550,2785,2,  53, 94,
2555,2775,2, 153, 95,2560,2765,2,  58, 96,2565,2760,2,  59, 97,
2570,2750,2, 133, 98,2575,2740,2,  61, 99,2580,2730,2,  71,100,
2585,2725,2, 149,101,2590,2720,2,   6,102,2595,2715,2,   7,103,
2600,2710,2,  62,104,2605,2690,2,  54,106,2610,2680,2,  55,107,
2615,2670,2,  56,108,2620,2665,2, 143,109,2625,2650,2, 139,110,
2630,2645,2,  57,127,2635,1230,2,  42, 59,2640, 545,2,  87, 84,
0,4520,4,   0, 31,   0,2160,3,   1,-127,1495,1230,1,  42, 30,
2660,1490,2,  11, 58,   0,4525,4,   0,110,   0,4085,3,   1,109,
850, 630,1,  11,  2,   0,4085,3,   2,108, 850, 630,1,  11,  2,
0,4085,3,   2,107, 850, 630,1,  11,  2,   0,4085,3,   2,106,
2705,1490,2,  11, 58,   0,4530,4,   0,105,   0,4085,3,   1,104,
0,4085,3,   1,103,   0,4085,3,   1,102,   0,4085,3,   1,101,
1940, 630,2,  11, 66,   0,4085,3,   2,100,1940, 630,2,  11, 66,
0,4085,3,   2, 99,1940, 630,2,  11, 66,   0,4085,3,   2, 98,
0,4085,3,   1, 97, 850, 630,1,  11,  2,   0,4085,3,   2, 96,
1940, 630,2,  11, 66,   0,4085,3,   2, 95, 100, 630,1,  11,  2,
2795, 720,2,  11, 68,2800, 695,2,  12, 69,   0,4535,4,   0, 94,
100, 630,1,  11,  2,2815, 720,2,  11, 68,2820, 695,2,  12, 69,
0,4540,4,   0, 93, 100, 630,1,  11,  2,2835, 720,2,  11, 68,
2840, 695,2,  12, 69,   0,4545,4,   0, 92, 100, 630,1,  11,  2,
2855, 720,2,  11, 68,2860, 695,2,  12, 69,   0,4550,4,   0, 91,
100, 630,1,  11,  2,2875, 720,2,  11, 68,2880, 695,2,  12, 69,
0,4555,4,   0, 90, 100, 630,1,  11,  2,2895, 720,2,  11, 68,
2900, 695,2,  12, 69,   0,4560,4,   0, 89,1495,1230,1,  42, 30,
2915,1490,2,  11, 58,   0,4565,4,   0, 29,1495,1230,1,  42, 30,
2930,1490,2,  11, 58,   0,4570,4,   0, 28,2940,2950,1,  25, 52,
0,2945,1,  21, 75,   0,2295,3,   1, 75,   0,3701,3,   1,-27,
0,2960,1,  24, 49,1795,3015,2,  40, 18,2970,2975,2,  84, 54,
0,4575,4,   0, 25,   0,2955,3,   1, 54,   0,2985,1,  24, 49,
1795,3015,2,  40, 18,   0,3701,3,   0, 23,   0,3701,3,   0, 22,
0,3701,3,   0, 21,3010,1445,2,  20, 40,   0,4580,4,   0, 20,
290, 295,2,  22, 34,   0,3025,1,  21, 53,3030,2155,2,  60,116,
3035, 630,2,  11, 66,3040, 575,2,  12, 67,3045,1935,2, 158,118,
3050, 415,2,   8,132,3055,1905,6,  22,117,3060,1905,6,  27,117,
3065, 210,2,  89,139,3070, 205,2,  68,141,3075, 500,2,  17,143,
3080,1230,2,  42, 59,3085, 285,2,  40,145,3090, 515,2, 167,163,
3095, 505,2,  39,164,3100, 490,2,  38,165,3105, 325,2,  82,170,
3110, 315,2, 113,172,3115, 305,2, 128,173,3120, 545,2,  87, 84,
3125, 180,2,  70,151,3130, 175,2,  28,157,3135,  95,2,  24,158,
0,4585,4,   0, 18,3145,2885,2,  48, 89,3150,2865,2,  49, 90,
3155,2845,2,  50, 91,3160,2825,2,  51, 92,3165,2805,2,  52, 93,
3170,2785,2,  53, 94,3175,2775,2, 153, 95,3180,2765,2,  58, 96,
3185,2760,2,  59, 97,3190,2750,2, 133, 98,3195,2740,2,  61, 99,
3200,2730,2,  71,100,3205,2725,2, 149,101,3210,2720,2,   6,102,
3215,2715,2,   7,103,3220,2710,2,  62,104,3225,2690,2,  54,106,
3230,2680,2,  55,107,3235,2670,2,  56,108,3240,2665,2, 143,109,
3245,2650,2, 139,110,3250,2645,2,  57,127,3255,1230,2,  42, 59,
3260, 545,2,  87, 84,   0,4590,4,   0, 32,   0,3701,3,   3, 19,
0,3701,3,   0, 17,   0,3645,3,   0, 11,2345,1785,2,  15,  5,
3290,3015,2,  40, 18,3295,3000,2, 153, 21,3300,2995,2,  41, 22,
3305,2920,2,  79, 28,3310,2905,2,  77, 29,3315,2440,2,  74, 41,
3320,2405,2,  76, 44,3325,2390,2,  78, 46,3330,2375,2,  75, 47,
3335,2320,2,  81, 49,3340,2980,6,  24, 30,3345,2155,2,  60,116,
3350,1460,2,  39, 61,3355,1455,2, 167, 63,3360,2135,2,  80, 82,
3365,2040,2,  85, 74,3370,1935,2, 158,118,3375,2115,6,  83, 71,
3380,1905,6,  22,117,3385,1905,6,  27,117,3390,1230,2,  42, 59,
3395, 545,2,  87, 84,   0,2355,4,   0, 52,   0,3645,3,   2, 12,
0,3410,1,  25, 50,   0,3701,3,   4, 24,2345,1785,2,  15,  5,
0,3425,1,  25, 50,   0,3701,3,   4,-26,2345,1785,2,  15,  5,
0,3440,1,  25, 50,   0,2965,3,   4,-53,2345,1785,2,  15,  5,
0,2935,3,   3,-55,2345,1785,2,  15,  5,   0,2935,3,   2,-56,
2345,1785,2,  15,  5,   0,3475,3,   1,124,   0,3480,1,  23,  6,
0,2290,3,   3,120,1770,3605,1,  47, 54,3495,3600,2,  47,  4,
3500,3015,2,  40, 18,3505,3000,2, 153, 21,3510,2995,2,  41, 22,
3515,2920,2,  79, 28,3520,2905,2,  77, 29,3525,2440,2,  74, 41,
3530,2405,2,  76, 44,3535,2390,2,  78, 46,3540,2375,2,  75, 47,
3545,2320,2,  81, 49,3550,2980,6,  24, 30,3555,2155,2,  60,116,
3560,1460,2,  39, 61,3565,1455,2, 167, 63,3570,2135,2,  80, 82,
3575,2040,2,  85, 74,3580,1935,2, 158,118,3585,2115,6,  83, 71,
3590,1230,2,  42, 59,3595, 545,2,  87, 84,   0,1905,6,   0,117,
0,3610,3,   4,  4,   0,3610,3,   3,  3,1775,1785,1,  15, 37,
0,  10,3,   2,  2,   0,   0,0,   2,  0,3629,1790,5,1770    ,
3633,2355,5,2340    ,3637,3490,5,3485    ,3641,3615,5,3610    ,
0,3285,5,   0    ,3649,3465,5,1920    ,3653,3455,5,2295    ,
3657,3445,5,2305    ,3661,3430,5,2315    ,3665,3415,5,2960    ,
3669,3280,5,2985    ,   0,3485,5,   0    ,3677,1660,5,  20    ,
3681, 580,5, 575    ,3685, 635,5, 630    ,3689, 700,5, 695    ,
3693, 725,5, 720    ,3697,1750,5,1660    ,   0, 655,5,   0    ,
3705,3400,5,3285    ,3709,3400,5,3490    ,   0,3275,5,   0    ,
3717, 380,5, 375    ,3721, 510,5, 505    ,3725,1165,5,1160    ,
3729,1465,5,1460    ,3733,2210,5,2205    ,3737,3020,5,3015    ,
0,1610,5,   0    ,3745, 970,5, 960    ,3749, 980,5, 975    ,
3753,1045,5,1040    ,3757,1055,5,1050    ,3761,1065,5,1060    ,
3765,1075,5,1070    ,3769,1095,5,1090    ,3773, 970,5,1350    ,
3777,2225,5,2220    ,3781,2240,5,2235    ,3785,2255,5,2250    ,
3789,2270,5,2265    ,3793,2285,5,2280    ,3797,2480,5,2440    ,
3801,2675,5,2670    ,3805,2685,5,2680    ,3809,2695,5,2690    ,
3813,3265,5,3025    ,   0,1080,5,   0    ,3821,1435,5, 415    ,
3825,2045,5,2040    ,   0,3005,5,   0    ,3833,3405,5,3280    ,
3837,3420,5,3415    ,3841,3435,5,3430    ,3845,3450,5,3445    ,
3849,3460,5,3455    ,3853,3470,5,3465    ,   0,2360,5,   0    ,
3861,1480,5, 415    ,3865,1510,5,1505    ,3869,2380,5,2375    ,
3873,2395,5,2390    ,3877,2470,5,2440    ,3881,2700,5,2520    ,
3885,2655,5,2650    ,3889,2910,5,2905    ,3893,2925,5,2920    ,
3897,2700,5,3140    ,   0,1925,5,   0    ,3905,1500,5,1490    ,
0,1270,5,   0    ,3913,1200,5,1135    ,3917,1180,5,1175    ,
3921,1470,5,1445    ,   0,1265,5,   0    ,3929,1650,5,  95    ,
3933,1640,5, 175    ,3937,1600,5, 295    ,3941,1580,5, 310    ,
3945,1570,5, 320    ,3949,1555,5, 330    ,3953,1315,5, 415    ,
3957, 675,5, 565    ,3961, 675,5, 745    ,3965, 945,5, 940    ,
3969,1205,5,1135    ,3973,1185,5,1175    ,3977,1250,5,1245    ,
3981,1290,5,1285    ,3985,1380,5,1350    ,3989,1425,5,1420    ,
3993,1290,5,1530    ,3997,1590,5,1585    ,4001,2020,5,1935    ,
4005,2055,5,2050    ,4009,2095,5,2090    ,4013,1290,5,2120    ,
4017,2195,5,2160    ,4021,2485,5,2440    ,4025,2020,5,2730    ,
4029,2020,5,2740    ,4033,2020,5,2750    ,4037,2195,5,2765    ,
4041,2020,5,2775    ,4045,2790,5,2785    ,4049,2810,5,2805    ,
4053,2830,5,2825    ,4057,2850,5,2845    ,4061,2870,5,2865    ,
4065,2890,5,2885    ,   0, 910,5,   0    ,4073,2125,5,2120    ,
0,1520,5,   0    ,4081, 750,5, 745    ,   0, 755,5,   0    ,
4089,3140,5,3025    ,   0,2520,5,   0    ,4097,2735,5,2730    ,
4101,2745,5,2740    ,4105,2755,5,2750    ,4109,2780,5,2775    ,
0,2035,5,   0    ,4117,2230,5,2160    ,4121,2770,5,2765    ,
0, 965,5,   0    ,4129, 990,5, 985    ,   0, 805,5,   0    ,
4137, 760,5, 415    ,4141,1110,5, 820    ,4145, 760,5, 845    ,
4149, 760,5, 960    ,4153, 760,5, 975    ,4157,1010,5,1005    ,
4161, 760,5,1040    ,4165, 760,5,1050    ,4169, 760,5,1060    ,
4173, 760,5,1070    ,4177, 760,5,1090    ,4181, 760,5,1350    ,
4185, 760,5,2160    ,4189, 760,5,2220    ,4193, 760,5,2235    ,
4197, 760,5,2250    ,4201, 760,5,2265    ,4205, 760,5,2280    ,
4209, 760,5,2440    ,4213, 760,5,2670    ,4217, 760,5,2680    ,
4221, 760,5,2690    ,4225, 760,5,2765    ,4229, 760,5,3025    ,
0, 390,5,   0    ,4237,1550,5, 410    ,4241, 540,5, 535    ,
4245, 605,5, 600    ,4249, 615,5, 610    ,4253, 625,5, 620    ,
4257, 800,5, 795    ,   0, 570,5,   0    ,4265,1630,5, 210    ,
4269, 835,5, 820    ,4273, 835,5,1005    ,4277,1620,5,1615    ,
4281,1630,5,2275    ,   0, 335,5,   0    ,4289, 365,5, 360    ,
0, 235,5,   0    ,4297, 370,5, 365    ,   0, 280,5,   0    ,
4305,1535,5,1530    ,   0,1275,5,   0    ,4313,1305,5,1285    ,
0,1235,5,   0    ,4321, 520,5, 500    ,   0, 525,5,   0    ,
0,1770,3,   0,  7,   0,4285,3,   1,149,   0, 300,3,   0,137,
0,4317,3,   0,-165,   0,4233,3,   0,-142,   0,1220,3,   2, 84,
0,3925,3,   1, 67,   0,3925,3,   1, 66,   0,3925,3,   0,-65,
0,4077,3,   0, 86,   0,3925,3,   2, 69,   0,3925,3,   2, 68,
0,4113,3,   1,126,   0,4113,3,   2,125,   0,3741,3,   6, 38,
0,4125,3,   2,130,   0,4125,3,   2,131,   0,3909,3,   3, 61,
0,3909,3,   2, 63,   0,4301,3,   0,-159,   0,4309,3,   2,162,
0,4069,3,   0,-72,   0,4309,3,   0,161,   0,4301,3,   2,160,
0,4069,3,   2, 73,   0, 300,3,   2,140,   0, 300,3,   1,139,
0,1770,3,   1,  8,   0,1770,3,   2,  9,   0,2290,3,   0,119,
0,4093,3,   0,-123,   0,2090,3,   0,-78,   0,2160,3,   3,128,
0,2990,3,   1, 47,   0,2990,3,   1, 46,   0,2990,3,   0, 44,
0,2990,3,   1,-45,   0,2990,3,   1, 43,   0,2990,3,   1, 41,
0,3270,3,   0, 31,   0,4085,3,   2,110,   0,4085,3,   1,105,
0,4085,3,   2, 94,   0,4085,3,   2, 93,   0,4085,3,   2, 92,
0,4085,3,   2, 91,   0,4085,3,   2, 90,   0,4085,3,   2, 89,
0,3701,3,   1, 29,   0,3701,3,   1, 28,   0,3701,3,   0,-25,
0,3701,3,   0, 20,   0,3701,3,   2, 18,   0,3270,3,   3, 32

};
lxinx entryhp[ordMAXCH + 1]={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,
3,0,0,0,4,5,0,6,8,88,0,0,0,0,0,0,0,0,0,0,89,0,90,102,103,0,0,0,0,0,0,0,0,0,105,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,108,0,0,0,0,0,109,142,166,211,238,258,0,
275,281,0,0,291,317,336,337,345,0,355,375,413,441,0,449,0,0,0,0,457,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0};
lxinx lxhp[lxmax + 1]={
0,0,0,0,0,0,0,0,83,76,69,64,58,55,49,40,30,28,21,0,0,26,23,24,25,0,27,0,29,0,
0,37,34,0,35,36,0,38,39,0,45,42,43,44,0,46,47,48,0,0,52,0,53,54,0,56,57,0,60,
0,61,62,63,0,67,66,0,68,0,70,71,72,73,74,75,0,77,78,79,82,81,0,0,84,85,86,87,
0,0,0,101,0,0,94,95,96,97,98,99,100,0,0,0,0,0,106,107,0,0,138,136,135,120,118,
115,116,117,0,119,0,132,122,123,124,128,126,127,0,130,0,131,0,133,134,0,0,137,
0,140,0,141,0,158,145,0,155,147,154,152,150,151,0,153,0,0,156,157,0,164,160,
161,162,163,0,165,0,210,204,202,195,172,0,187,183,178,177,0,0,179,180,181,182,
0,184,185,186,0,188,193,190,191,192,0,194,0,196,197,198,199,200,201,0,203,0,
205,206,209,208,0,0,0,231,227,221,215,218,217,0,219,220,0,222,223,224,225,226,
0,228,229,230,0,232,233,237,235,236,0,0,246,245,241,244,243,0,0,0,249,248,0,
250,251,252,253,257,255,256,0,0,268,265,264,262,263,0,0,266,267,0,269,270,274,
272,273,0,0,277,0,278,279,280,0,0,283,0,285,286,287,288,289,290,0,315,313,301,
298,296,297,0,299,300,0,302,303,312,308,306,307,0,309,310,311,0,0,314,0,316,
0,328,327,320,321,322,326,324,325,0,0,0,329,330,331,335,333,334,0,0,0,0,339,
340,341,342,343,344,0,353,351,348,349,350,0,352,0,354,0,369,0,366,363,360,361,
362,0,364,365,0,367,368,0,372,371,0,373,374,0,411,407,403,400,397,388,386,383,
384,385,0,387,0,394,390,391,392,393,0,395,396,0,398,399,0,402,0,0,404,405,406,
0,408,409,410,0,412,0,440,427,418,417,0,426,420,421,422,423,424,425,0,0,428,
429,439,434,432,433,0,435,436,437,438,0,0,0,443,0,444,445,446,447,448,0,456,
451,454,453,0,455,0,0,0};
lxinx lxnp[lxmax + 1]={
0,0,0,0,0,0,7,0,9,10,11,12,13,14,15,16,17,18,19,20,0,22,0,0,0,0,0,0,0,0,31,32,
33,0,0,0,0,0,0,0,41,0,0,0,0,0,0,0,0,50,51,0,0,0,0,0,0,0,59,0,0,0,0,0,65,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,80,0,0,0,0,0,0,0,0,0,0,91,92,93,0,0,0,0,0,0,0,0,0,0,
104,0,0,0,0,0,110,111,112,113,114,0,0,0,0,0,0,121,0,0,0,125,0,0,0,129,0,0,0,
0,0,0,0,0,0,139,0,0,0,143,144,0,146,0,148,149,0,0,0,0,0,0,0,0,0,159,0,0,0,0,
0,0,0,167,168,169,170,171,0,173,174,175,176,0,0,0,0,0,0,0,0,0,0,0,0,189,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,207,0,0,0,0,212,213,214,0,216,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,234,0,0,0,0,239,240,0,242,0,0,0,0,247,0,0,0,0,0,0,254,0,0,
0,0,259,260,261,0,0,0,0,0,0,0,0,0,271,0,0,0,0,276,0,0,0,0,0,282,0,284,0,0,0,
0,0,0,0,292,293,294,295,0,0,0,0,0,0,0,0,304,305,0,0,0,0,0,0,0,0,0,0,0,0,318,
319,0,0,0,323,0,0,0,0,0,0,0,0,332,0,0,0,0,0,338,0,0,0,0,0,0,0,346,347,0,0,0,
0,0,0,0,0,356,357,358,359,0,0,0,0,0,0,0,0,0,0,370,0,0,0,0,0,376,377,378,379,
380,381,382,0,0,0,0,0,0,389,0,0,0,0,0,0,0,0,0,0,0,401,0,0,0,0,0,0,0,0,0,0,0,
0,414,415,416,0,0,419,0,0,0,0,0,0,0,0,0,0,430,431,0,0,0,0,0,0,0,0,0,0,442,0,
0,0,0,0,0,0,450,0,452,0,0,0,0,0,0};
symbol lxtv[lxmax + 1]={
0,103,36,18,34,32,33,151,95,100,0,96,0,97,94,96,95,94,97,72,73,0,0,110,0,110,
0,97,0,94,91,0,0,93,0,0,98,0,0,95,0,0,0,0,96,111,0,0,111,90,0,92,0,0,94,0,0,
97,0,109,0,0,0,109,0,0,99,0,96,0,0,112,0,0,0,112,0,0,0,0,0,100,100,0,95,0,0,
95,35,31,150,106,105,0,0,0,0,0,0,0,101,152,102,104,107,0,0,68,27,0,0,0,0,0,56,
0,0,129,0,116,162,0,0,164,0,0,0,170,0,169,0,185,0,0,168,67,0,115,0,114,0,147,
0,0,58,0,159,0,0,0,0,173,0,172,171,0,0,95,0,0,0,0,0,66,0,148,0,0,0,0,0,6,0,0,
0,0,117,75,0,0,0,0,60,0,0,0,79,0,140,0,140,0,140,0,140,0,0,0,160,0,0,174,0,61,
0,0,0,0,144,144,7,0,0,0,86,0,0,155,0,0,135,0,51,0,0,0,51,0,0,0,80,0,0,0,0,0,
175,136,0,0,0,0,118,119,77,99,0,0,84,0,0,0,161,0,0,0,177,176,0,0,0,0,0,54,85,
0,0,127,0,71,0,0,0,186,71,0,48,0,0,0,48,83,0,120,0,0,137,0,0,0,137,0,0,0,0,0,
121,122,0,0,145,0,163,0,0,0,0,179,0,0,0,187,178,0,157,0,70,0,0,0,0,165,0,0,0,
181,180,131,130,0,0,0,0,0,189,188,69,63,0,0,0,0,0,141,141,0,0,0,0,0,74,0,132,
0,138,0,69,0,0,0,0,0,146,0,0,156,0,0,76,50,0,82,0,0,50,0,0,78,0,0,0,0,69,0,0,
98,0,125,0,0,0,0,0,87,0,0,166,0,0,134,0,124,123,0,0,142,142,0,0,190,53,0,62,
0,0,69,55,94,64,0,0,52,0,0,0,52,59,0,0,0,0,0,0,184,0,0,0,0,183,182,126,0,154,
0,0,81,0,0,81,0,0,49,0,57,0,49,65,19};
symbol entrytv[ordMAXCH + 1]={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,42,43,44,
14,37,29,8,9,10,11,20,12,26,13,0,0,0,0,0,0,0,0,0,0,21,15,4,30,5,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,22,0,23,16,0,28,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
Char lxch[lxmax + 1]={
'0','=','=','&','=','=','=','>','b','c','d','e','h','l','n','r','s','t','w',
'x','y','e','i','d','t','h','s','t','o','p','e','o','t','w','a','r','t','u',
't','h','a','i','g','h','t','d','i','u','s','e','o','w','r','t','h','e','f',
't','e','t','i','g','h','t','a','n','d','s','t','i','a','m','e','t','e','r',
'e','n','t','e','r','e','r','o','t','t','o','m','=','=','-','<','=','c','o',
'm','p','a','r','e','>','>','=','=','>','e','r','e',']','b','c','n','r','s',
't','a','n','2','i','n','c','r','o','w','h','w','i','d','e','t','a','d','r',
'a','d','d','o','s','o','s','v','e','e','o','y','t','x','h','r','w','i','d',
'a','d','t','t','o','m','l','t','w','e','e','n','o','w','c','e','h','i','o',
'w','l','m','n','p','s','y','t','i','n','u','e','m','a','n','d','o','r','u',
'r','e','d','e','d','r','c','l','e','r','a','d','o','p','n','t','e','r','e',
'r','w','a','e','i','o','t','w','n','t','e','d','a','m','e','t','e','r','f',
'i','n','e','s','h','e','w','i','d','d','l','n','x','e','p','e','c','d','l',
's','e','i','p','s','e','h','w','i','d','t','i','l','o','r','o','m','r','o',
'o','r','l','l','e','v','a','l','d','e','t','i','g','h','t','f','n','t','v',
'i','s','i','b','l','e','a','e','i','j','o','g','e','u','s','t','n','e','h',
't','w','i','d','h','i','c','k','t','f','t','s','t','a','i','o','v','e','h',
'w','i','d','t','n','x','p','s','h','w','i','d','t','d','f','u','t','l','i',
'n','e','d','a','m','r','i','n','t','o','d','t','h','a','d','e','i','j','u',
's','t','g','h','t','s','e','t','d','n','d','i','u','s','a','c','h','i','o',
'p','q','t','a','r','t','r','t','l','r','i','n','t','f','i','n','e','l','i',
'd','g','n','n','a','d','e','d','a','l','e','d','m','e','a','e','h','o','p',
'e','i','c','k','n','e','s','s','n','x','t','h','o','w','i','d','f','f','s',
'e','t','t','n','n','p','d','e','f','i','n','e','a','i','d','t','h','t','h',
'y','|'};
/* integer debugging constants        */
/*D debuglevel, linesignal: integer; D*/
/*D trace: boolean; D*/
/* used for debugging the parser      */

/* Parser variables */
int oldsymb;   /* last lexical symbol                */
arg *macros, *args;   /* macro and macro argument list      */
stackinx stacktop, pseudotop, validtop, top;
stackelm *parsestack;   /* parse stack          */
boolean parsestop;   /* parser flags                       */
int startinx, lri, start;


/*--------------------------------------------------------------------*/

/* include dp1.z */
/*dp1.x---------------------------------------------------------------*/
int Ceil(double x);

int Floor(double x);

double Max(double x, double y);

double Min(double x, double y);

primitive *findenv(primitive *p);

arg *findmacro(arg *p, Char *chb, chbufinx inx, chbufinx length,
		      arg **last);

boolean isthen(primitive *pr);

double linlen(double x, double y);

int lspec(int n);

/*DGH function ordp(p:pointer): integer; forward; HGD*/
double principal(double x, double r);

void checkjust(nametype *tp, boolean *A, boolean *B, boolean *L,
		      boolean *R);

void consoleflush(void);

void copyleft(fbuffer *mac, fbuffer **buf);

void deletetree(primitive **p);

/*D; loc: integerD*/
void disposebufs(fbuffer **buf);

void drawtree(double n, double s, double e, double w, primitive *eb);

void fatal(int t);

void initnesw(void);

void markerror(int n);

void nesw(primitive *ptmp);

void newarg(arg **arg_);

void newbuf(fbuffer **buf);

void pointinput(nametype *txt);

void produce(stackinx newp, int p);

void readfor(fbuffer *p0, int attx, fbuffer **p2);

void skiptobrace(void);

/*D procedure snaptype(var iou: text; p: integer); forward; D*/
void wcoord(FILE **iou, double x, double y);

void wfloat(FILE **iou, double y);

void wpair(FILE **iou, double x, double y);

void wpos(postype pos);

/*D procedure wrbuf(p: fbufferp; job,r: integer); forward; D*/
void wstring(FILE **iou, nametype *p);

/* common to mpo and pgf: */
void controls(void);

void wrand(void);

void ddot(void);

void ddash(void);

void mpocorner(postype ctr, double x, double y, double r, double ct,
		      double st);


/*--------------------------------------------------------------------*/

/* include sysdep.h */
/*GH#include 'sysdep.h'HG*/

double principal(double x, double r)
{
  /* x,r: real): real */
  while (x > r)
    x += -r - r;
  while (x < -r)
    x += r + r;
  return x;
}


double Max(double x, double y)
{
  /* x,y: real): real */
  if (y > x)
    return y;
  else
    return x;
}


double Min(double x, double y)
{
  /* x,y: real): real */
  if (y < x)
    return y;
  else
    return x;
}


int Floor(double x)
{
  /* x: real): integer */
  if (x >= 0 || (long)x == x)
    return ((long)x);
  else
    return ((long)x - 1);
}


int Ceil(double x)
{
  /* x: real): integer */
  if (x < 0 || (long)x == x)
    return ((long)x);
  else
    return ((long)x + 1);
}


void consoleflush(void)
{
  /* causes immediate physical write to console, not
                               needed for most systems. */
  /*DUGHM; if debuglevel > 0 then flush(log) MHGUD*/
  fflush(stderr_);
  P_ioresult = 0;
}


void epilog(void)
{
  /* produce(0, 0); */
  /*D if debuglevel > 0 then writeln(log,'stackhigh=',stackhigh:1);D*/
  /* D writeln("stackhigh=",stackhigh:1); D */
}


void currentline(int *startlin)
{  /* Print out the current input line */
  int inx, j, lastinx;
  fbuffer *bf, *ba, *WITH;

  putc('\n', stderr_);
  consoleflush();
  bf = inbuf;
  ba = NULL;
  /*D if debuglevel > 0 then begin
     write(log,'currentline:'); wrbuf(bf,3,0) end; D*/
  while (bf != NULL) {
    WITH = bf;
    ba = bf;
    j = 0;
    if (bf->readx - 1 < bf->savedlen)
      inx = bf->readx - 1;
    else
      inx = bf->savedlen;
    while (inx > j) {
      if (WITH->carray[inx] == etxch || WITH->carray[inx] == tabch ||
	  WITH->carray[inx] == ' ' ||
	  WITH->carray[inx] == crch || WITH->carray[inx] == nlch)
	inx--;
      else
	j = inx;
    }
    /*D if debuglevel > 0 then write(log,'skipwhite inx=',inx:1); D*/
    if (bf == inbuf)
      lastinx = inx;
    j = 0;
    while (inx > j) {
      if (WITH->carray[inx] != nlch)
	inx--;
      else
	j = inx;
    }
    /*D if debuglevel > 0 then begin write(log,' skipnonwhite inx=',inx:1);
       if bf<>inbuf then wrbuf(bf,3,-inx) else writeln(log) end; D*/
    if (inx == 0)
      bf = WITH->prevb;
    else
      bf = NULL;
  }

  *startlin = inx;
  while (ba != NULL) {
    WITH = ba;
    if (ba == inbuf)
      j = lastinx;
    else
      j = WITH->savedlen;
    while (inx < j) {
      inx++;
      if (WITH->carray[inx] == nlch)
	putc('\n', stderr_);
      else if (WITH->carray[inx] != etxch)
	putc(WITH->carray[inx], stderr_);
    }
    if (ba == inbuf)
      ba = NULL;
    else
      ba = ba->nextb;
    inx = 0;
  }
  putc('\n', stderr_);
  consoleflush();
}


void fatal(int t)
{
  /* t: integer */
  int i;

  if (t != 0) {
    fprintf(stderr_, " *** dpic: ");
    currentline(&i);
  }
  switch (t) {

  case 0:
    /* blank case */
    break;

  case 1:
    fprintf(stderr_, "Input file not readable\n");
    break;

  case 3:
    fprintf(stderr_, "Maximum error count exceeded\n");
    break;

  case 4:
    fprintf(stderr_, "Character buffer overflow: \"CHBUFSIZ\" exceeded\n");
    break;

  case 5:
    fprintf(stderr_, "End of file encountered on input\n");
    break;

  case 6:
    fprintf(stderr_,
	    "Too many pending actions, const \"STACKMAX\" exceeded,\n");
    fprintf(stderr_, "possibly caused by infinite recursion.\n");
    break;

  case 7:
    fprintf(stderr_, "Input too complex, const \"REDUMAX\" exceeded\n");
    break;

  case 8:
    fprintf(stderr_, "Error recovery abandoned\n");
    /*D; 9: writeln(stderr,'Debug special exit') D*/
    break;
  }

  epilog();
  if (input != NULL) fclose(input);
  if (output != NULL) fclose(output);
  if (stderr_ != NULL) fclose(stderr_);
  /*DP2CC if (log_ != NULL) fclose(log_); */
  exit(EXIT_SUCCESS);

}


/*--------------------------------------------------------------------*/

/* include sysdep.h */
/*sysdep.x Required UNIX functions */

extern int access(Char *f, int n);

/*G asmname '_p_Access'; G*/

/*G asmname 'isatty'; G*/

/*G asmname 'time'; G*/
/*BXUGH real HGUXB*/

/*BXUGH real HGUXB*/

/*G asmname 'snprintf'; G*/

/*G asmname 'system'; G*/

/* These need tweaking for different operating systems:      */
#if defined(__MSDOS__) || defined(__CYGWIN32__) || defined(RAND) 
#undef random
#define random() rand()
#else
extern long random(void);
#endif

/*G asmname 'random'; G*/
#if defined(_POSIX_SOURCE) || defined(sun)
extern void srandom(unsigned s);
#elif defined(__MSDOS__) || defined(__CYGWIN32__) || defined(RAND) 
extern void srand(unsigned s);
#define srandom(x) srand((unsigned)(x))
#elif defined(mips)
#elif defined(__APPLE__)
#else
extern void srandom(int s);
#endif


/*G asmname 'srandom'; G*/

/*DUMBX function  ordp(var p:primitivep ): integer; external; XBMUD*/
/*-----------------------------------------------------------------*/

/* include dpic1.p */
/*BX segment dpic1; XB*/
/* onefile */
/* G module dpic1; G */

/* include dp0.h */
/*BXU#include 'dp0.h'UXB*/
/* onefile */
/* G#include 'dp0.h'G */

/* include dp1.h */
/*BXU#include 'dp1.h'UXB*/
/* onefile */
/* G#include 'dp1.h'G */

/* include sysdep.h */
/*BXU#include 'sysdep.h'UXB*/
/* onefile */
/* G#include 'sysdep.h'G */

/* Recursive routines: snaptree pexit neswrec shift treedraw scaleobj */

int bval(Char *buf)
{
  return (((int) buf[0]) << 7) + (int) buf[1] ;
}


void putbval(Char *buf, int n)
{
  /* D
    if debuglevel > 0 then writeln(log,'putbval[',ordp(buf):1,'](',n:1,')'); D */
  buf[0] = (Char)(n>>7); buf[1] = (Char)(n % 128);
}


void deletename(nametype **head)
{
  nametype *pn, *r;
  int j, FORLIM;

  while (*head != NULL) {
    pn = *head;
    r = pn;
    while (pn->next_ != NULL) {
      r = pn;
      pn = pn->next_;
    }
    r->next_ = NULL;
    if (pn == *head)
      *head = NULL;
    if (pn->segmnt != NULL) {
      if (bval(pn->segmnt) > 1) {
	j = bval(pn->segmnt);
	putbval(pn->segmnt, j - 1);
	if (pn->segmnt == freeseg && pn->seginx + pn->len == freex) {
	  freex = pn->seginx;
	  j = 3;
	  while (freex > j) {
	    if (pn->segmnt[freex - 1] == nlch)
	      freex--;
	    else
	      j = freex;
	  }
	} else {
	  FORLIM = pn->seginx + pn->len;
	  for (j = pn->seginx; j < FORLIM; j++)
	    pn->segmnt[j] = nlch;
	}
      } else if (pn->segmnt == freeseg) {
	Free(freeseg);
	freeseg = NULL;
      } else
	Free(pn->segmnt);
    }
    Free(pn);
  }
}


/*
procedure setvis(var specv: integer; nonz: integer);
begin
   specv := (specv div 32)*32 + nonz*16 + (specv mod 16)
   end; */

void setspec(int *specv, int svalue)
{
  *specv = ((*specv) >> 3) * 8 + svalue - XLlinetype;
  /* if svalue = XLsolid then
     specv := (specv div 32)*32 + 16 + (specv mod 16) */
}


void resetspec(int *specv, int svalue)
{
  *specv = 0;
  setspec(specv, svalue);
}


void setthen(int *specv)
{
  *specv = ((*specv) >> 4) * 16 + ((*specv) & 7) + 8;
}


/*DH function ordp(p:pointer): integer;
begin
   ordp := Integer(p)
   end; HD*/
/*DG function ordpGD*/
/* p:pointer */
/*DG: integer;
begin
   ordp := Integer(p)
   end; GD*/
/*D
procedure prtstval(st: integer);
begin
write(log,'state=',st:1);
if (st mod 4)<>0 then
case (st mod 4) of
   1: write(log,',XL','to');
   2: write(log,',XL','from');
   3: write(log,',XL','at');
   otherwise
   end;
if odd(st div 4) then write(log,',XL','chop');
if odd(st div 8) then write(log,',XL','directon')
end;

procedure snapname( chbu:chbufp; inx,ll:chbufinx);
var j: integer;
begin
write(log,' (',ordp(chbu):1,' inx=',inx:1,' len=',ll:1,')"');
if chbu = nil then write(log,'**nil string pointer**')
else for j := inx to inx+ll-1 do write(log,chbu^[j]);
write(log,'"'); flush(log)
end;

procedure snaptype D*/
/* var iou: text; p: integer */
/*D;
begin
   case p of
      XLbox: write(iou,'<box>');
      XBLOCK: write(iou,'<[]>');
      XLellipse: write(iou,'<ellipse>');
      XLcircle: write(iou,'<circle>');
      XLline: write(iou,'<line>');
      XLarrow: write(iou,'<arrow>');
      XLmove: write(iou,'<move>');
      XLspline: write(iou,'<spline>');
      XLarc: write(iou,'<arc>');
      XLstring: write(iou,'<<string>>');
      XLtroff: write(iou,'<<troff>>');
      XLabel: write(iou,'<<Label>>');
      otherwise write(iou,'Unknown type ',p:3)
      end;
   flush(iou)
   end;

procedure snaptree(pr: primitivep; indent: integer);
var i: integer;
begin
   while (pr <> nil) and (indent<=240) do with pr^ do begin
      snaptype(log,ptype);
      case ptype of
         XBLOCK: i := 4;
         XLbox,XLarc: i := 5;
         XLline,XLmove: i := 6;
         XLarrow: i := 7;
         XLcircle,XLspline: i := 8;
         XLellipse,XLtroff: i := 9;
         XLstring: i := 10;
         XLabel: i := 12;
         otherwise i := 3
         end;
      snaptree(next,indent+i);
      if son <> nil then begin
         writeln(log);
         write(log,' ':indent);
         end;
      pr := son
      end
   end;

procedure printtext(namptr: strptr);
begin
   while namptr <> nil do with namptr^ do begin
      write(log,' ');
      D*/
/*DBUMX wpair(log,ord(namptr),ord(next)); XMUBD*/
/*DGH wpair(log,ordp(namptr),ordp(next)); HGD*/
/*D
write(log,' val='); wfloat(log,val); flush(log);
snapname(segmnt,seginx,len);
namptr := next; writeln(log) end
   end;

procedure printobject(primp: primitivep);
var
   xx,yy: real;
begin
   if debuglevel = 0 then begin end
   else if primp = nil then writeln(log,'Object is nil')
   else while primp <> nil do with primp^ do begin
writeln(log,'Object(',ordp(primp):1,
          ') Parent(',ordp(parent):1,
          ') Son(',   ordp(son):1,
          ') Next(',  ordp(next):1, ')');
if name<>nil then begin write(log,' name: '); printtext(name) end;
if outlinep<>nil then begin
   write(log,' outline:'); printtext(outlinep) end;
if shadedp<>nil then begin
   write(log,' shaded:'); printtext(shadedp) end;
if textp<>nil then begin writeln(log); printtext(textp) end;
write(log,' aat'); wpair(log,aat.xpos,aat.ypos);
write(log,' lparam='); write(log,lparam:8);
write(log,' lthick='); write(log,lthick:8);
case direction of
   XLup: write(log,' <up>');
   XLdown: write(log,' <down>');
   XLleft: write(log,' <left>');
   XLright: write(log,' <right>');
   otherwise write(log,' dir =',direction:1)
   end;
write(log,' spec=',spec:1);
write(log,' type='); snaptype(log,ptype);
writeln(log,'(',ptype:1,')' );
flush(log);
case ptype of
   XLbox,XLstring: begin
      write(log,' boxfill='); wfloat(log,boxfill);
      write(log,' boxheight,boxwidth='); wpair(log,boxheight,boxwidth);
      write(log,' rad='); wfloat(log,boxradius) end;
   XBLOCK: begin
      write(log,' blockheight,blockwidth=');
      wpair(log,blockheight,blockwidth);
      write(log,' here='); wpair(log,here.xpos,here.ypos);
      write(log,' vars=');
         if vars = nil then write(log,'nil')
         D*/
/*DBUMX else write(log,ord(vars):1); XMUBD*/
/*DGH else write(log,ordp(vars):1); HGD*/
/*D
            write(log,' env=');
if env = nil then write(log,'nil')
D*/
/*DBUMX else write(log,ord(env):1) XMUBD*/
/*DGH else write(log,ordp(env):1) HGD*/
/*D
            end;
         XLcircle: begin
            write(log,' cfill,radius='); wpair(log,cfill,radius) end;
         XLellipse: begin
            write(log,' efill='); wfloat(log,efill);
            write(log,' elheight,elwidth='); wpair(log,elheight,elwidth) end;
         XLline,XLarrow,XLmove,XLspline: begin
            write(log,' endpos='); wpair(log,endpos.xpos,endpos.ypos);
            write(log,' height,width='); wpair(log,height,width);
            write(log,' lfill,aradius='); wpair(log,lfill,aradius);
            write(log,' atype=',atype:1)
            end;
         XLarc: begin
            write(log,' lspec=',lspec(spec):1);
            write(log,' lfill,aradius='); wpair(log,lfill,aradius);
            write(log,' (|','startangle|,|','arcangle|)(deg)=');
            wpair(log,endpos.xpos*180.0/pi,endpos.ypos*180.0/pi); writeln(log);
            write(log,' (from)=');
            wpair(log,aat.xpos+aradius*cos(endpos.xpos),
       aat.ypos+aradius*sin(endpos.xpos));
            write(log,' (to)=');
            xx := aat.xpos+aradius*cos(endpos.xpos+endpos.ypos);
            yy := aat.ypos+aradius*sin(endpos.xpos+endpos.ypos);
            wpair(log,xx,yy);
            writeln(log,' atype=',atype:1)
            end;
         XLtroff,XLabel: ;
         otherwise writeln(log,' Bad case in printobject; this cannot happen')
         end;
      writeln(log); flush(log);
      if ptype = XBLOCK then primp := nil
      else primp := son
      end;
   flush(log)
   end;
D*/

void deletetree(primitive **p)
{
  /* var p: primitivep */
  primitive *r, *WITH;

  if (*p != NULL)
    (*p)->parent = NULL;
  while (*p != NULL) {
    /*D if debuglevel > 0 then printobject(p); D*/
    while ((*p)->next_ != NULL || (*p)->son != NULL) {
      r = *p;
      if ((*p)->next_ != NULL) {
	*p = (*p)->next_;
	r->next_ = NULL;
      } else {
	*p = (*p)->son;
	r->son = NULL;
      }
      (*p)->parent = r;
      /*D; if debuglevel > 0 then printobject(p) D*/
    }
    r = (*p)->parent;
    /* D if debuglevel > 0 then begin write(log,'Deletetree:');
       printobject(p) end; D */
    deletename(&(*p)->shadedp);
    deletename(&(*p)->outlinep);
    deletename(&(*p)->textp);
    deletename(&(*p)->name);
    WITH = *p;
    switch (WITH->ptype) {

    case XLbox:
    case XLstring:
      Free(*p);
      break;

    case XBLOCK:
      deletename(&WITH->UU.UEMPTY7.vars);
      if (WITH->UU.UEMPTY7.env != NULL)
	Free(WITH->UU.UEMPTY7.env);
      Free(*p);
      break;

    case XLcircle:
      Free(*p);
      break;

    case XLellipse:
      Free(*p);
      break;

    case XLline:
    case XLarc:
    case XLarrow:
    case XLmove:
    case XLspline:
      Free(*p);
      break;

    case XLtroff:
    case XLabel:
      Free(*p);
      break;
    }
    *p = r;
  }
}


double datan(double y, double x)
{
  double r;

  /*D if debuglevel=2 then write(log,'datan(',y:8:4,',',x:8:4,')='); D*/
  if (x > 0.0) {
    r = atan(y / x);
    return r;
  }
  if (x < 0.0) {
    if (y >= 0.0)
      r = pi - atan(-(y / x));
    else
      r = atan(y / x) - pi;
    return r;
  }
  if (y > 0.0) {
    r = pi / 2;
    return r;
  }
  if (y < 0.0)
    r = pi / -2;
  else
    r = 0.0;
  /*D if debuglevel=2 then writeln(log,r:8:4); D*/
  return r;
}


void setangles(double *strtang, double *arcang, postype ctr, double xs,
		      double ys, double xf, double yf)
{
  double ra;   /* set arc angles given centre, start, end */

  *strtang = datan(ys - ctr.ypos, xs - ctr.xpos);
  ra = principal(datan(yf - ctr.ypos, xf - ctr.xpos) - *strtang, pi);
  if (ra < 0.0 && *arcang > 0.0)
    ra += 2.0 * pi;
  else if (ra > 0.0 && *arcang < 0.0)
    ra -= 2.0 * pi;
  *arcang = ra;
}


void eqop(double *x, int op, double y)
{
  switch (op) {

  case XLeq:
  case XLcoloneq:
    *x = y;
    break;

  case XLpluseq:
    *x += y;
    break;

  case XLminuseq:
    *x -= y;
    break;

  case XLmulteq:
    *x *= y;
    break;

  case XLdiveq:
    if (y == 0)
      markerror(852);
    else
      *x /= y;
    break;

  case XLremeq:
    if (y == 0)
      markerror(852);
    else {
      *x = (long)floor(*x + 0.5) % (long)floor(y + 0.5);
/* p2c: dpic.p, line 881:
 * Note: Using % for possibly-negative arguments [317] */
    }
    break;
  }
}


void setstval(int *st, int value)
{
  *st = value * 256 + ((*st) & 255);
}


int getstval(int st)
{
  return (st >> 8);
}


void setstflag(int *st, int value)
{
  switch (value) {

  case XEMPTY:
    *st = ((*st) >> 6) * 64;
    break;

  case XLto:
    *st = ((*st) >> 1) * 2 + 1;
    break;

  case XLfrom:
    *st = ((*st) >> 2) * 4 + ((*st) & 1) + 2;
    break;

  case XLat:
    *st = ((*st) >> 3) * 8 + ((*st) & 3) + 4;
    break;

  case XLradius:
    *st = ((*st) >> 4) * 16 + ((*st) & 7) + 8;
    break;

  case XLcw:
    *st = ((*st) >> 5) * 32 + ((*st) & 15) + 16;
    break;

  case XLccw:
    *st = ((*st) >> 6) * 64 + ((*st) & 31) + 32;
    break;

  case XLchop:
    *st = ((*st) >> 7) * 128 + ((*st) & 63) + 64;
    break;

  case XLdirecton:
    *st = ((*st) >> 8) * 256 + ((*st) & 127) + 128;
    break;
  }

}


boolean teststflag(int st, int value)
{
  boolean b;

  switch (value) {

  case XLto:
    b = st & 1;
    break;

  case XLfrom:
    b = (st >> 1) & 1;
    break;

  case XLat:
    b = (st >> 2) & 1;
    break;

  case XLradius:
    b = (st >> 3) & 1;
    break;

  case XLcw:
    b = (st >> 4) & 1;
    break;

  case XLccw:
    b = (st >> 5) & 1;
    break;

  case XLchop:
    b = (st >> 6) & 1;
    break;

  case XLdirecton:
    b = (st >> 7) & 1;
    break;

  default:
    b = false;
    break;
  }
  return b;
}


int eqstring(Char *seg1, chbufinx inx1, chbufinx len1, Char *seg2,
		    chbufinx inx2, chbufinx len2)
{
  int Result, i, j, k;

  /*D if debuglevel = 2 then begin
     write(log,' eqstring: '); if seg1 = nil then write(log,'first arg = nil')
     else snapname(seg1,inx1,len1);
     write(log,' '); if seg2 = nil then write(log,'2nd arg = nil')
     else snapname(seg2,inx2,len2); writeln(log) end; D*/
  if (seg1 == NULL || seg2 == NULL) {
    Result = SHORT_MAX;
    return k;
  }
  i = 0;
  k = 0;
  if (len1 < len2)
    j = len1;
  else
    j = len2;
  while (i < j) {
    /*D if debuglevel = 2 then
         write(log,'(',seg1^[inx1+i],seg2^[inx2+i],')'); D*/
    k = seg1[inx1 + i] - seg2[inx2 + i];
    if (k == 0)
      i++;
    else
      j = i;
  }
  if (k != 0)
    return k;
  if (len1 > len2)
    k = seg1[inx1 + i];
  else if (len1 < len2)
    k = -seg2[inx2 + i];
  /*D if debuglevel = 2 then if (seg1 = nil) or (seg2 = nil) then
     writeln(log,'eqstring: nil segment(s)')
     else writeln(log,'eqstring: i=',i:1,' j=',j:1,' eqstring=',k:1); D*/
  return k;
}


int cmpstring(primitive *p1, primitive *p2)
{
  if (p1 == NULL || p2 == NULL)
    return SHORT_MAX;
  else if (p1->textp == NULL && p2->textp == NULL)
    return SHORT_MAX;
  else if (p1->textp == NULL)
    return SHORT_MAX;
  else if (p2->textp == NULL)
    return (-SHORT_MAX);
  else
    return (eqstring(p1->textp->segmnt, p1->textp->seginx, p1->textp->len,
		     p2->textp->segmnt, p2->textp->seginx, p2->textp->len));
}


primitive *findplace(primitive *p, Char *chb, chbufinx inx,
			    chbufinx length)
{
  primitive *pj;
  nametype *WITH;

  pj = NULL;
  /*Dif debuglevel = 2 then begin
     write(log,'findplace:'); snapname(chb,inx,length); writeln(log)
     end; D*/
  while (p != pj) {   /*D begin printobject(p); D*/
    if (p->name == NULL)
      p = p->next_;
    else {
      WITH = p->name;
      if (eqstring(WITH->segmnt, WITH->seginx, WITH->len, chb, inx, length) == 0)
	pj = p;
      else
	p = p->next_;
    }
  }
  /*D end; D*/
  return p;
}


arg *findmacro(arg *p, Char *chb, chbufinx inx, chbufinx length,
		      arg **last)
{
  /*H( p:argp;
                       chb: chbufp; inx,length: chbufinx;
                       var last:argp )H*/
  arg *pj, *WITH;

  *last = NULL;
  pj = NULL;
  /*Dif debuglevel = 2 then begin
     write(log,'findmacro:'); snapname(chb,inx,length); writeln(log)
     end; D*/
  while (p != pj) {
    WITH = p;
    if (WITH->argbody == NULL) {
      *last = p;
      p = p->nextb;
    } else if (eqstring(WITH->argbody->carray, 1, -WITH->argbody->attrib, chb,
			inx, length) == 0)
      pj = p;
    else {
      *last = p;
      p = p->nextb;
    }
  }
  return p;
}


nametype *findname(nametype *p, Char *chb, chbufinx chbufx,
			  chbufinx length, nametype **last)
{
  nametype *pj, *WITH;

  *last = NULL;
  pj = NULL;
  while (p != pj) {
    WITH = p;
    if (eqstring(WITH->segmnt, WITH->seginx, WITH->len, chb, chbufx, length) == 0)
      pj = p;
    else {
      *last = p;
      p = p->next_;
    }
  }
  return p;
}


nametype *glfindname(primitive *eb, Char *chb, chbufinx chbufx,
			    chbufinx length, nametype **last)
{
  nametype *np;
  primitive *pp;
  int i;

  pp = NULL;
  np = NULL;
  while (eb != pp) {
    np = findname(eb->UU.UEMPTY7.vars, chb, chbufx, length, last);
    if (np != NULL)
      pp = eb;
    else
      eb = eb->parent;
  }
  if (eb != NULL)
    return np;
  fprintf(stderr_, "\nSearch failure for \"");
  for (i = chbufx; i < chbufx + length; i++)
    putc(chb[i], stderr_);
  fprintf(stderr_, "\"\n");
  markerror(851);
  return np;
}


void newstr(nametype **sp)
{
  nametype *WITH;

  *sp = Malloc(sizeof(nametype));
  WITH = *sp;
  WITH->segmnt = NULL;
  WITH->seginx = 0;
  WITH->len = 0;
  WITH->val = 0.0;
  WITH->next_ = NULL;
}


void addstring(Char **outbuf, nametype *sp, Char *srcbuf, chbufinx px,
		      chbufinx ll)
{
  int i, j;
  boolean newseg;
  int FORLIM;

  if (*outbuf == NULL || freex + ll - 1 > CHBUFSIZ)
    newseg = true;
  else if (bval(*outbuf) >= maxbval)
    newseg = true;
  else
    newseg = false;
  if (newseg) {
    *outbuf = Malloc(sizeof(chbufarray));
    putbval(*outbuf, 0);
    freex = 3;
  }
  /* for i := 0 to ll-1 do outbuf^[freex+i] := srcbuf^[px+i]; */
  j = px - freex;
  FORLIM = freex + ll;
  for (i = freex; i < FORLIM; i++)
    (*outbuf)[i] = srcbuf[j + i];
  sp->segmnt = *outbuf;
  sp->seginx = freex;
  sp->len = ll;
  putbval(*outbuf, bval(*outbuf) + 1);
  freex += ll;
  /*D; if debuglevel > 0 then begin write(log,
     'addstring: seginx= ', sp^.seginx:1, ' links= ', bval(outbuf):1 );
     snapname(srcbuf,px,ll);
     writeln( log ) end D*/
}


void copystr(Char **outbuf, nametype **sp, nametype *ip)
{
  if (ip != NULL) {
    newstr(sp);
    addstring(outbuf, *sp, ip->segmnt, ip->seginx, ip->len);
  }
}


void appendstring(nametype *sp, Char *buf, chbufinx px, chbufinx ll)
{
  int i, j;
  Char *tmpseg;
  int FORLIM;

  if (freex + ll - 1 > CHBUFSIZ) {
    tmpseg = Malloc(sizeof(chbufarray));
    FORLIM = sp->len + 2;
    for (i = 3; i <= FORLIM; i++)
      tmpseg[i] = freeseg[freex - sp->len + i - 3];
    putbval(freeseg, bval(freeseg) - 1);
    freeseg = tmpseg;
    freex = sp->len + 3;
    putbval(freeseg, 1);
    sp->segmnt = freeseg;
    sp->seginx = 3;
  }
  if (freex + ll - 1 > CHBUFSIZ) {
    markerror(866);
    return;
  }
  j = px - freex;
  FORLIM = freex + ll;
  /* for i := 0 to ll-1 do freeseg^[freex+i] := buf^[px+i]; */
  for (i = freex; i < FORLIM; i++)
    freeseg[i] = buf[j + i];
  sp->len += ll;
  freex += ll;
  /*D; if debuglevel > 0 then begin
     write ( log,'appendstring: seginx= ',sp^.seginx:1,' len= ',sp^.len:1);
     snapname(buf,px,ll); writeln( log )
     end D*/
}


int putstring(int ix, nametype *sp, Char *buf, chbufinx px,
		     chbufinx ll)
{
  if (ix <= 0)
    addstring(&freeseg, sp, buf, px, ll);
  else
    appendstring(sp, buf, px, ll);
  return (ix + 1);
}


double pheight(primitive *pr)
{
  double ph;

  if (pr == NULL) {
    ph = 0.0;
    return ph;
  }
  switch (pr->ptype) {

  case XLbox:
  case XLstring:
    ph = pr->UU.Ubox.boxheight;
    break;

  case XBLOCK:
    ph = pr->UU.UEMPTY7.blockheight;
    break;

  case XLellipse:
    ph = pr->UU.Uellipse.elheight;
    break;

  case XLcircle:
    ph = 2.0 * pr->UU.Ucircle.radius;
    break;

  case XLline:
  case XLarrow:
  case XLmove:
    ph = fabs(pr->UU.Uline.endpos.ypos - pr->aat.ypos);
    break;

  default:
    ph = 0.0;
    break;
  }
  return ph;
}


double pwidth(primitive *pr)
{
  double ph;

  if (pr == NULL) {
    ph = 0.0;
    return ph;
  }
  switch (pr->ptype) {

  case XLbox:
  case XLstring:
    ph = pr->UU.Ubox.boxwidth;
    break;

  case XBLOCK:
    ph = pr->UU.UEMPTY7.blockwidth;
    break;

  case XLellipse:
    ph = pr->UU.Uellipse.elwidth;
    break;

  case XLcircle:
    ph = 2.0 * pr->UU.Ucircle.radius;
    break;

  case XLline:
  case XLarrow:
  case XLmove:
    ph = fabs(pr->UU.Uline.endpos.xpos - pr->aat.xpos);
    break;

  default:
    ph = 0.0;
    break;
  }
  return ph;
}


void pexit(primitive *pr, postype *pe)
{
  if (pr == NULL) {
    pe->xpos = 0.0;
    pe->ypos = 0.0;
    return;
  }
  if (pr->ptype != XBLOCK && pr->son != NULL) {
    pexit(pr->son, pe);
    return;
  }
  *pe = pr->aat;
  switch (pr->ptype) {

  case XLbox:
  case XLstring:
    switch (pr->direction) {

    case XLup:
      pe->ypos = pr->aat.ypos + pr->UU.Ubox.boxheight * 0.5;
      break;

    case XLdown:
      pe->ypos = pr->aat.ypos - pr->UU.Ubox.boxheight * 0.5;
      break;

    case XLleft:
      pe->xpos = pr->aat.xpos - pr->UU.Ubox.boxwidth * 0.5;
      break;

    case XLright:
      pe->xpos = pr->aat.xpos + pr->UU.Ubox.boxwidth * 0.5;
      break;
    }
    break;

  case XBLOCK:
    switch (pr->direction) {

    case XLup:
      pe->ypos = pr->aat.ypos + pr->UU.UEMPTY7.blockheight * 0.5;
      break;

    case XLdown:
      pe->ypos = pr->aat.ypos - pr->UU.UEMPTY7.blockheight * 0.5;
      break;

    case XLleft:
      pe->xpos = pr->aat.xpos - pr->UU.UEMPTY7.blockwidth * 0.5;
      break;

    case XLright:
      pe->xpos = pr->aat.xpos + pr->UU.UEMPTY7.blockwidth * 0.5;
      break;
    }
    break;

  case XLcircle:
    switch (pr->direction) {

    case XLup:
      pe->ypos = pr->aat.ypos + pr->UU.Ucircle.radius;
      break;

    case XLdown:
      pe->ypos = pr->aat.ypos - pr->UU.Ucircle.radius;
      break;

    case XLleft:
      pe->xpos = pr->aat.xpos - pr->UU.Ucircle.radius;
      break;

    case XLright:
      pe->xpos = pr->aat.xpos + pr->UU.Ucircle.radius;
      break;
    }
    break;

  case XLellipse:
    switch (pr->direction) {

    case XLup:
      pe->ypos = pr->aat.ypos + pr->UU.Uellipse.elheight * 0.5;
      break;

    case XLdown:
      pe->ypos = pr->aat.ypos - pr->UU.Uellipse.elheight * 0.5;
      break;

    case XLleft:
      pe->xpos = pr->aat.xpos - pr->UU.Uellipse.elwidth * 0.5;
      break;

    case XLright:
      pe->xpos = pr->aat.xpos + pr->UU.Uellipse.elwidth * 0.5;
      break;
    }
    break;

  case XLarc:
    pe->xpos = pr->aat.xpos + pr->UU.Uline.aradius *
		 cos(pr->UU.Uline.endpos.xpos + pr->UU.Uline.endpos.ypos);
    pe->ypos = pr->aat.ypos + pr->UU.Uline.aradius *
		 sin(pr->UU.Uline.endpos.xpos + pr->UU.Uline.endpos.ypos);
    break;

  case XLline:
  case XLarrow:
  case XLmove:
  case XLspline:
    *pe = pr->UU.Uline.endpos;
    break;

  case XLabel:
  case XLtroff:
    /* blank case */
    break;
  }
}


void newprim(primitive **pr, int primtype, primitive *envblk)
{
  primitive *WITH;

  switch (primtype) {

  case XLbox:
  case XLstring:
    *pr = Malloc(sizeof(XLboxprimitive));
    break;

  case XBLOCK:
    *pr = Malloc(sizeof(primitive));
    break;

  case XLcircle:
    *pr = Malloc(sizeof(XLcircleprimitive));
    break;

  case XLellipse:
    *pr = Malloc(sizeof(XLellipseprimitive));
    break;

  case XLline:
  case XLarc:
  case XLarrow:
  case XLmove:
  case XLspline:
    *pr = Malloc(sizeof(XLlineprimitive));
    break;

  case XLabel:
  case XLtroff:
    *pr = Malloc(sizeof(XLabelprimitive));
    break;
  }
  WITH = *pr;
  WITH->name = NULL;
  WITH->textp = NULL;
  WITH->outlinep = NULL;
  WITH->shadedp = NULL;
  WITH->son = NULL;
  WITH->next_ = NULL;
  if (envblk == NULL) {
    WITH->parent = NULL;
    WITH->aat.xpos = 0.0;
    WITH->aat.ypos = 0.0;
    WITH->direction = XLright;
  } else {
    if (envblk->son == NULL)
      envblk->son = *pr;
    WITH->parent = envblk;
    WITH->aat = envblk->UU.UEMPTY7.here;
    WITH->direction = envblk->direction;
  }
  WITH->lparam = mdistmax;
  WITH->lthick = mdistmax;
  if (primtype == XLspline || primtype == XLarc || primtype == XLarrow ||
      primtype == XLline || primtype == XLellipse ||
      primtype == XLcircle || primtype == XLbox)
    resetspec(&WITH->spec, XLsolid);
  else
    resetspec(&WITH->spec, XLinvis);
  /* spec := 0;
  if primtype in [XLbox,XLcircle,XLellipse,XLline,XLarrow,XLarc,XLspline]
     then setvis(spec,1); */
  WITH->ptype = primtype;
  switch (primtype) {

  case XLbox:
  case XLstring:
    WITH->UU.Ubox.boxfill = -1.0;
    WITH->UU.Ubox.boxheight = 0.0;
    WITH->UU.Ubox.boxwidth = 0.0;
    WITH->UU.Ubox.boxradius = 0.0;
    break;

  case XBLOCK:
    WITH->UU.UEMPTY7.blockheight = 0.0;
    WITH->UU.UEMPTY7.blockwidth = 0.0;
    WITH->UU.UEMPTY7.here = WITH->aat;
    WITH->UU.UEMPTY7.vars = NULL;
    WITH->UU.UEMPTY7.env = NULL;
    break;

  case XLcircle:
    WITH->UU.Ucircle.cfill = -1.0;
    WITH->UU.Ucircle.radius = 0.0;
    break;

  case XLellipse:
    WITH->UU.Uellipse.efill = -1.0;
    WITH->UU.Uellipse.elheight = 0.0;
    WITH->UU.Uellipse.elwidth = 0.0;
    break;

  case XLline:
  case XLarrow:
  case XLmove:
  case XLarc:
  case XLspline:
    WITH->UU.Uline.endpos.xpos = 0.0;
    WITH->UU.Uline.endpos.ypos = 0.0;
    WITH->UU.Uline.height = 0.0;
    WITH->UU.Uline.width = 0.0;
    WITH->UU.Uline.lfill = -1.0;
    WITH->UU.Uline.aradius = mdistmax;
    WITH->UU.Uline.atype = XEMPTY;
    break;

  case XLabel:
  case XLtroff:
    /* blank case */
    break;
  }
}


void arcenddir(primitive *pr)
{
  if (pr->UU.Uline.endpos.ypos > 0.0) {
    switch (pr->direction) {

    case 0:
      /* blank case */
      break;

    case XLup:
      envblock->direction = XLleft;
      break;

    case XLdown:
      envblock->direction = XLright;
      break;

    case XLleft:
      envblock->direction = XLdown;
      break;

    case XLright:
      envblock->direction = XLup;
      break;
    }
    return;
  }
  switch (pr->direction) {

  case 0:
    /* blank case */
    break;

  case XLup:
    envblock->direction = XLright;
    break;

  case XLdown:
    envblock->direction = XLleft;
    break;

  case XLleft:
    envblock->direction = XLup;
    break;

  case XLright:
    envblock->direction = XLdown;
    break;
  }
}


void neswrec(primitive *ptm)
{
  while (ptm != NULL) {
    nesw(ptm);
    if (ptm->ptype != XBLOCK)
      neswrec(ptm->son);
    ptm = ptm->next_;
  }
}


void getnesw(primitive *ptm)
{
  initnesw();
  neswrec(ptm);
  if (south > north) {
    south = 0.0;
    north = 0.0;
  }
  if (west > east) {
    west = 0.0;
    east = 0.0;
  }
}


void shift(primitive *pr, double x, double y)
{
  primitive *WITH;

  while (pr != NULL) {
    WITH = pr;
    WITH->aat.xpos += x;
    WITH->aat.ypos += y;
    if (WITH->ptype == XLspline || WITH->ptype == XLmove ||
	WITH->ptype == XLarrow || WITH->ptype == XLline) {
      WITH->UU.Uline.endpos.xpos += x;
      WITH->UU.Uline.endpos.ypos += y;
    }
    if (WITH->son != NULL)
      shift(WITH->son, x, y);
    pr = WITH->next_;
  }
}


void scaleobj(primitive *pr, double s)
{
  primitive *WITH;

  while (pr != NULL) {
    WITH = pr;
    WITH->aat.xpos *= s;
    WITH->aat.ypos *= s;
    if (WITH->ptype == XLbox) {
      WITH->UU.Ubox.boxheight *= s;
      WITH->UU.Ubox.boxwidth *= s;
      WITH->UU.Ubox.boxradius *= s;
    } else if (WITH->ptype == XBLOCK) {
      WITH->UU.UEMPTY7.blockheight *= s;
      WITH->UU.UEMPTY7.blockwidth *= s;
    } else if (WITH->ptype == XLcircle)
      WITH->UU.Ucircle.radius *= s;
    else if (WITH->ptype == XLellipse) {
      WITH->UU.Uellipse.elheight *= s;
      WITH->UU.Uellipse.elwidth *= s;
    } else if (WITH->ptype == XLarc)
      WITH->UU.Uline.aradius *= s;
    else if (WITH->ptype == XLspline || WITH->ptype == XLmove ||
	     WITH->ptype == XLarrow || WITH->ptype == XLline) {
      WITH->UU.Uline.endpos.xpos *= s;
      WITH->UU.Uline.endpos.ypos *= s;
    }
    if (WITH->son != NULL)
      scaleobj(WITH->son, s);
    pr = WITH->next_;
  }
}


/*        corner(prim,<corner>,xval,yval);
                           Put the corner coordinates into xval,yval   */
void corner(primitive *pr, int lexv, double *x, double *y)
{
  primitive *pe;
  boolean sb;

  if (pr == NULL)
    return;
  /*D if debuglevel>0 then begin
     writeln(log,'ptype(',ordp(pr):1,'):',ptype:4,' lexval ',
     lexv); flush(log) end; D*/
  *x = pr->aat.xpos;
  *y = pr->aat.ypos;
  pe = pr;
  if (lexv == XEMPTY &&
      (pr->ptype == XLspline || pr->ptype == XLmove || pr->ptype == XLarrow ||
       pr->ptype == XLline)) {
    while (pe->son != NULL)
      pe = pe->son;
    *x = 0.5 * (pr->aat.xpos + pe->UU.Uline.endpos.xpos);
    *y = 0.5 * (pr->aat.ypos + pe->UU.Uline.endpos.ypos);
    return;
  }
  if (lexv == XEMPTY && pr->ptype != XLtroff)
    return;
  switch (pr->ptype) {

  case XLbox:
  case XLstring:
  case XBLOCK:
  case XLcircle:
  case XLellipse:
  case XLarc:
    *x = pr->aat.xpos;
    *y = pr->aat.ypos;
    initnesw();
    nesw(pr);
    /*Dif debuglevel>0 then writeln(log, 'lexval ',lexv);D*/
    if ((pr->ptype == XLarc || pr->ptype == XLcircle ||
	 pr->ptype == XLellipse || pr->ptype == XLbox) &&
	(lexv == XDnw || lexv == XDsw || lexv == XDse || lexv == XDne)) {
      switch (pr->ptype) {

      case XLbox:
	*y = Min(pr->UU.Ubox.boxradius, Min(fabs(pr->UU.Ubox.boxheight),
		     fabs(pr->UU.Ubox.boxwidth)) / 2) * (1 - 1 / sqrt(2.0));
	*x = pr->UU.Ubox.boxwidth / 2 - *y;
	*y = pr->UU.Ubox.boxheight / 2 - *y;
	break;

      case XLellipse:
	*x = pr->UU.Uellipse.elwidth * (0.5 / sqrt(2.0));
	*y = pr->UU.Uellipse.elheight * (0.5 / sqrt(2.0));
	break;

      case XLarc:
	*x = pr->UU.Uline.aradius / sqrt(2.0);
	*y = *x;
	break;

      case XLcircle:
	*x = pr->UU.Ucircle.radius / sqrt(2.0);
	*y = *x;
	break;
      }
      switch (lexv) {

      case XDne:
	/* blank case */
	break;

      case XDse:
	*y = -*y;
	break;

      case XDnw:
	*x = -*x;
	break;

      case XDsw:
	*x = -*x;
	*y = -*y;
	break;
      }
      *x = pr->aat.xpos + *x;
      *y = pr->aat.ypos + *y;
    } else if (pr->ptype == XLarc) {
      switch (lexv) {

      case XDn:
	*y = pr->aat.ypos + pr->UU.Uline.aradius;
	break;

      case XDs:
	*y = pr->aat.ypos - pr->UU.Uline.aradius;
	break;

      case XDe:
	*x = pr->aat.xpos + pr->UU.Uline.aradius;
	break;

      case XDw:
	*x = pr->aat.xpos - pr->UU.Uline.aradius;
	break;

      case XDc:
	/* blank case */
	break;

      case XDstart:
	*x = pr->aat.xpos + pr->UU.Uline.aradius * cos(pr->UU.Uline.endpos.xpos);
	*y = pr->aat.ypos + pr->UU.Uline.aradius * sin(pr->UU.Uline.endpos.xpos);
	break;

      case XDend:
	*x = pr->aat.xpos + pr->UU.Uline.aradius *
	       cos(pr->UU.Uline.endpos.xpos + pr->UU.Uline.endpos.ypos);
	*y = pr->aat.ypos + pr->UU.Uline.aradius *
	       sin(pr->UU.Uline.endpos.xpos + pr->UU.Uline.endpos.ypos);
	break;
      }
    } else {
      switch (lexv) {

      case XDn:
	*y = north;
	break;

      case XDs:
	*y = south;
	break;

      case XDe:
	*x = east;
	break;

      case XDw:
	*x = west;
	break;

      case XDne:
	*y = north;
	*x = east;
	break;

      case XDse:
	*y = south;
	*x = east;
	break;

      case XDsw:
	*y = south;
	*x = west;
	break;

      case XDnw:
	*y = north;
	*x = west;
	break;

      case XDc:
	*y = pr->aat.ypos;
	*x = pr->aat.xpos;
	break;

      case XDstart:
      case XDend:
	markerror(858);
	break;
      }
    }
    break;

  case XLline:
  case XLarrow:
  case XLmove:
  case XLspline:
    if (lexv != XDstart) {
      if (lexv == XDend) {
	while (pe->son != NULL)
	  pe = pe->son;
	*x = pe->UU.Uline.endpos.xpos;
	*y = pe->UU.Uline.endpos.ypos;
      } else if (lexv == XDc) {
	while (pe->son != NULL)
	  pe = pe->son;
	*x = 0.5 * (*x + pe->UU.Uline.endpos.xpos);
	*y = 0.5 * (*y + pe->UU.Uline.endpos.ypos);
      } else {
	do {
	  switch (lexv) {

	  case XDn:
	    sb = (pe->UU.Uline.endpos.ypos > *y);
	    break;

	  case XDs:
	    sb = (pe->UU.Uline.endpos.ypos < *y);
	    break;

	  case XDe:
	    sb = (pe->UU.Uline.endpos.xpos > *x);
	    break;

	  case XDw:
	    sb = (pe->UU.Uline.endpos.xpos < *x);
	    break;

	  case XDne:
	    sb = ((pe->UU.Uline.endpos.ypos > *y &&
		   pe->UU.Uline.endpos.xpos >= *x) ||
		  (pe->UU.Uline.endpos.ypos >= *y &&
		   pe->UU.Uline.endpos.xpos > *x));
	    break;

	  case XDse:
	    sb = ((pe->UU.Uline.endpos.ypos < *y &&
		   pe->UU.Uline.endpos.xpos >= *x) ||
		  (pe->UU.Uline.endpos.ypos <= *y &&
		   pe->UU.Uline.endpos.xpos > *x));
	    break;

	  case XDsw:
	    sb = ((pe->UU.Uline.endpos.ypos < *y &&
		   pe->UU.Uline.endpos.xpos <= *x) ||
		  (pe->UU.Uline.endpos.ypos <= *y &&
		   pe->UU.Uline.endpos.xpos < *x));
	    break;

	  case XDnw:
	    sb = ((pe->UU.Uline.endpos.ypos > *y &&
		   pe->UU.Uline.endpos.xpos <= *x) ||
		  (pe->UU.Uline.endpos.ypos >= *y &&
		   pe->UU.Uline.endpos.xpos < *x));
	    break;
	  }
	  if (sb) {
	    *x = pe->UU.Uline.endpos.xpos;
	    *y = pe->UU.Uline.endpos.ypos;
	  }
	  pe = pe->son;
	} while (pe != NULL);
      }
    }
    break;

  case XLabel:
    /* blank case */
    break;

  case XLtroff:
    markerror(858);
    break;
  }
  /*D; if debuglevel > 0 then begin write(log,'corner=');
      wpair(log,x,y); writeln(log) end D*/
}


primitive *nthprimobj(primitive *primp, int nth, int objtype)
{
  primitive *prp, *pp;
  int i;

  /*D if debuglevel = 2 then writeln(log,'nthprimobj nth=',nth:1,' type=',
     objtype:1); D*/
  prp = NULL;
  if (nth == 0) {
    while (primp != NULL) {
      /*D if debuglevel = 2 then begin
         printobject(primp);
         if primp^.ptype = objtype then begin
            prp := primp;
            writeln(log,'found') end;
         primp := primp^.next
         end
      else D*/
      if (primp->ptype == objtype)
	prp = primp;
      primp = primp->next_;
    }
    return prp;
  }
  if (nth < 0) {
    i = 0;
    pp = primp;
    while (pp != NULL) {
      if (pp->ptype == objtype)
	i++;
      pp = pp->next_;
    }
    nth += i + 1;
  }
  i = 0;
  /*D if debuglevel = 2 then write(log,' nth=',nth:1); D*/
  if (nth <= 0)
    return prp;
  while (primp != prp) {
    /*D if debuglevel = 2 then printobject(primp); D*/
    if (primp->ptype == objtype)
      i++;
    if (i == nth)
      prp = primp;
    else {
      primp = primp->next_;
      /*D;if (debuglevel = 2) and (i = nth) then writeln(log,'found') D*/
    }
  }
  return prp;
}


void resetenv(int envval, primitive *envbl)
{
  environx i, last;

  if (envbl == NULL)
    return;
  if (envval == 0) {
    envval = XLenvvar + 1;
    last = XLlastenv;
  } else
    last = envval;
  if (envbl->UU.UEMPTY7.env == NULL)
    envbl->UU.UEMPTY7.env = Malloc(sizeof(envarray));
  for (i = envval - 1; i < last; i++) {
    switch (i + 1) {

    case XLarcrad:   /* scaled environmental vars */
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.25;
      break;

    case XLarrowht:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.1;
      break;

    case XLarrowwid:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.05;
      break;

    case XLboxht:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.5;
      break;

    case XLboxrad:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.0;
      break;

    case XLboxwid:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.75;
      break;

    case XLcirclerad:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.25;
      break;

    case XLdashwid:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.1;
      break;

    case XLellipseht:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.5;
      break;

    case XLellipsewid:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.75;
      break;

    case XLlineht:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.5;
      break;

    case XLlinewid:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.5;
      break;

    case XLmoveht:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.5;
      break;

    case XLmovewid:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.5;
      break;

    case XLtextht:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.0;
      break;

    case XLtextoffset:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 2.5 / 72;   /*.27*/
      break;

    case XLtextwid:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.0;
      break;

    /* The following are unscaled */
    case XLarrowhead:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 2.0;
      break;

    case XLfillval:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.3;
      break;

    case XLlinethick:   /* points */
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 0.8;
      break;

    case XLmaxpsht:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 11.0;
      break;

    case XLmaxpswid:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 8.5;
      break;

    case XLscale:
      envbl->UU.UEMPTY7.env[i - XLenvvar] = 1.0;
      break;
    }
  }
}


void inheritenv(primitive *envbl)
{
  environx i;
  primitive *pr;

  pr = findenv(envbl);
  if (pr == NULL) {
    resetenv(0, envbl);
    return;
  }
  envbl->UU.UEMPTY7.env = Malloc(sizeof(envarray));
  for (i = XLenvvar; i < XLlastenv; i++)
    envbl->UU.UEMPTY7.env[i - XLenvvar] = pr->UU.UEMPTY7.env[i - XLenvvar];
}


void resetscale(double x, int opr, primitive *envbl)
{
  double r, s;
  int i;

  resetenv(0, envbl);
  r = envbl->UU.UEMPTY7.env[XLscale - XLenvvar - 1];
  eqop(&envbl->UU.UEMPTY7.env[XLscale - XLenvvar - 1], opr, x);
  s = envbl->UU.UEMPTY7.env[XLscale - XLenvvar - 1];
  if (r == 0.0)
    markerror(852);
  else
    s /= r;
  for (i = XLenvvar; i < XLlastsc; i++)
    eqop(&envbl->UU.UEMPTY7.env[i - XLenvvar], XLmulteq, s);
}


void inittwo(void)
{
  /* performed for each input diagram */
  freebuf = NULL;
  freeseg = NULL;
  freex = 0;

  lastfillval = mdistmax;
  lastthick = mdistmax;
  newprim(&envblock, XBLOCK, NULL);
  resetenv(0, envblock);
}


void deletebufs(fbuffer **p)
{
  fbuffer *q;

  while (*p != NULL) {
    q = (*p)->nextb;
    Free(*p);
    *p = q;
  }
}


double intpow(double x, int k)
{
  /* 0^(-k) does not occur */
  if (k == 0) {
    x = 1.0;   /* 0^0 returns 1.0 */
    return x;
  }
  if (x == 0.0 || k == 1)
    return x;
  if (k < 0) {
    x = intpow(1.0 / x, -k);
    return x;
  }
  if (k == 2) {
    x *= x;   /* common enough to test for it */
    return x;
  }
  if (k & 1)
    x *= intpow(x, k - 1);
  else {
    x = intpow(x, k >> 1);
    x *= x;
  }
  return x;
}


void getscale(double xv, double yv, primitive *lp, double *sfact,
		     double *xsc)
{
  /* .PS xv yv
     sfact = nominal scale factor set by scale = ...
     xsc = effective scale factor to achieve correct max picture size
     ie (size in inches)/(desired size in inches) */
  double gs;
  int erno;
  primitive *qp;

  erno = 0;
  gs = 1.0;
  *sfact = gs;
  if (lp != NULL) {
    if (lp->ptype == XBLOCK) {
      qp = findenv(lp);
      if (qp->UU.UEMPTY7.env[XLscale - XLenvvar - 1] > 0.0)
	*sfact = qp->UU.UEMPTY7.env[XLscale - XLenvvar - 1];
      /*D if debuglevel > 0 then begin write(log,'getscale: sfact=');
         wfloat(log,sfact); writeln(log) end; D*/
      if (east > west &&
	  (east - west) / *sfact > qp->UU.UEMPTY7.env[XLmaxpswid - XLenvvar - 1] &&
	  qp->UU.UEMPTY7.env[XLmaxpswid - XLenvvar - 1] > 0.0) {
	erno = 903;
	gs = (east - west) / qp->UU.UEMPTY7.env[XLmaxpswid - XLenvvar - 1];
      }
      if (north > south &&
	  (north - south) / *sfact > qp->UU.UEMPTY7.env[XLmaxpsht - XLenvvar - 1] &&
	  qp->UU.UEMPTY7.env[XLmaxpsht - XLenvvar - 1] > 0.0) {
	erno = 904;
	gs = Max(gs,
		 (north - south) / qp->UU.UEMPTY7.env[XLmaxpsht - XLenvvar - 1]);
      }
    }
  }
  if (xv > 0.0 && east > west) {
    erno = 0;
    gs = (east - west) / *sfact / xv;
  }
  if (yv > 0.0 && north > south &&
      (xv == 0.0 || (north - south) / gs > yv * *sfact)) {
    erno = 0;
    gs = (north - south) / *sfact / yv;
  }
  if (erno != 0)
    markerror(erno);
  /*D if debuglevel > 0 then begin write(log,' getscale=');
     wfloat(log,gs*sfact); writeln(log) end; D*/
  *xsc = gs * *sfact;
}


void addelem(primitive *prold, primitive *prnew)
{
  primitive *pp, *pq;

  if (prold == NULL || prnew == NULL)
    return;
  pp = prold;
  while (pp->next_ != NULL) {
    pq = prnew;   /* Refuse to make a loop: */
    while (pq->next_ != NULL) {
      if (pq->next_ == pp)
	pq->next_ = NULL;
      else
	pq = pq->next_;
    }
    pp = pp->next_;
  }
  /*D if debuglevel > 0 then begin
     write(log,'prev element:'); snaptype(log,pp^.ptype); writeln(log);
     writeln(log,' addelem snaptype done') end; D*/
  pp->next_ = prnew;
  /*D; if debuglevel > 0 then begin printobject(prnew);
     writeln(log,' addelem printobject done'); flush(log);
     snaptree(prold,0); writeln(log,' addelem done') end D*/
}


void copyprim(primitive *prin, primitive **prout)
{
  /* Needed because assignment of variant records is unreliable */
  int i;

  if (prin == NULL)
    return;
  newprim(prout, prin->ptype, NULL);
  (*prout)->name = prin->name;
  (*prout)->textp = prin->textp;
  (*prout)->outlinep = prin->outlinep;
  (*prout)->shadedp = prin->shadedp;
  (*prout)->parent = prin->parent;
  (*prout)->son = prin->son;
  (*prout)->next_ = prin->next_;
  (*prout)->aat = prin->aat;
  (*prout)->lparam = prin->lparam;
  (*prout)->lthick = prin->lthick;
  (*prout)->direction = prin->direction;
  (*prout)->spec = prin->spec;
  (*prout)->ptype = prin->ptype;
  switch (prin->ptype) {

  case XLbox:
  case XLstring:
    (*prout)->UU.Ubox.boxfill = prin->UU.Ubox.boxfill;
    (*prout)->UU.Ubox.boxheight = prin->UU.Ubox.boxheight;
    (*prout)->UU.Ubox.boxwidth = prin->UU.Ubox.boxwidth;
    (*prout)->UU.Ubox.boxradius = prin->UU.Ubox.boxradius;
    break;

  case XBLOCK:
    (*prout)->UU.UEMPTY7.blockheight = prin->UU.UEMPTY7.blockheight;
    (*prout)->UU.UEMPTY7.blockwidth = prin->UU.UEMPTY7.blockwidth;
    (*prout)->UU.UEMPTY7.here = prin->UU.UEMPTY7.here;
    (*prout)->UU.UEMPTY7.vars = prin->UU.UEMPTY7.vars;
    if (prin->UU.UEMPTY7.env != NULL) {
      (*prout)->UU.UEMPTY7.env = Malloc(sizeof(envarray));
      for (i = XLenvvar; i < XLlastenv; i++)
	(*prout)->UU.UEMPTY7.env[i - XLenvvar] = prin->UU.UEMPTY7.env[i - XLenvvar];
    }
    break;

  case XLcircle:
    (*prout)->UU.Ucircle.cfill = prin->UU.Ucircle.cfill;
    (*prout)->UU.Ucircle.radius = prin->UU.Ucircle.radius;
    break;

  case XLellipse:
    (*prout)->UU.Uellipse.efill = prin->UU.Uellipse.efill;
    (*prout)->UU.Uellipse.elheight = prin->UU.Uellipse.elheight;
    (*prout)->UU.Uellipse.elwidth = prin->UU.Uellipse.elwidth;
    break;

  case XLline:
  case XLarrow:
  case XLmove:
  case XLarc:
  case XLspline:
    (*prout)->UU.Uline.endpos = prin->UU.Uline.endpos;
    (*prout)->UU.Uline.height = prin->UU.Uline.height;
    (*prout)->UU.Uline.width = prin->UU.Uline.width;
    (*prout)->UU.Uline.lfill = prin->UU.Uline.lfill;
    (*prout)->UU.Uline.aradius = prin->UU.Uline.aradius;
    (*prout)->UU.Uline.atype = prin->UU.Uline.atype;
    break;

  case XLabel:
  case XLtroff:
    /* blank case */
    break;
  }
}


void deletestringbox(primitive **pr)
{
  primitive *prx;

  if (*pr != NULL) {
    if ((*pr)->parent != NULL) {
      if ((*pr)->parent->son == *pr)
	(*pr)->parent->son = NULL;
      else {  /* is the following ever reached? */
	prx = (*pr)->parent->son;
	while (prx->next_ != NULL && prx->next_ != *pr)
	  prx = prx->next_;
	prx->next_ = NULL;
      }
    }
  }
  deletetree(pr);
}


void marknotfound(Char *chb, chbufinx inx, chbufinx len)
{
  int i;

  markerror(855);
  fprintf(stderr_, "\nSearch failure for \"");
  for (i = inx; i < inx + len; i++)
    putc(chb[i], stderr_);
  fprintf(stderr_, "\"\n");
}


/*        addsuffix(chbuf,chbufx,length,attstack^[newp+1].xval); */
void addsuffix(Char *buf, chbufinx *inx, int *len, double suff)
{   /*DBUMX writeln(log,ord(buf),inx,len,' ',suff); XMUBD*/
  int i, j, FORLIM;

  /*D if debuglevel <> 0 then begin writeln(log,
     'addsuffix(buf: chbufp; var inx:chbufinx; var len:integer; suff: real)');
     D*/
  /*DGH writeln(log,ordp(buf),inx,len,' ',suff); HGD*/
  /*D
  snapname(buf,inx,len); writeln(log)
  end; D*/
  if (chbufi + *len - 1 > CHBUFSIZ)
    fatal(4);
  /* for i:=0 to len-1 do buf^[chbufi+i] := buf^[inx+i]; */
  j = *inx - chbufi;
  FORLIM = chbufi + *len;
  for (i = chbufi; i < FORLIM; i++)
    buf[i] = buf[j + i];
  i = (long)floor(suff + 0.5);
  if (i < 0) {
    (*len)++;
    i = -i;
  }
  do {
    (*len)++;
    i /= 10;
  } while (i != 0);
  *len += 2;
  if (chbufi + *len - 1 > CHBUFSIZ)
    fatal(4);
  buf[chbufi + *len - 1] = ']';
  j = *len - 2;
  i = (long)floor(suff + 0.5);
  if (i < 0)
    i = -i;
  do {
    buf[chbufi + j] = i % 10 + '0';
/* p2c: dpic.p, line 1726:
 * Note: Using % for possibly-negative arguments [317] */
    j--;
    i /= 10;
  } while (i != 0);
  if ((long)floor(suff + 0.5) < 0) {
    buf[chbufi + j] = '-';
    j--;
  }
  buf[chbufi + j] = '[';
  *inx = chbufi;
  /*D ; if debuglevel <> 0 then begin
     snapname(buf,inx,len); writeln(log) end D*/
}  /* addsuffix */


void appendthen(primitive **pr)
{
  primitive *prp;

  copyprim(*pr, &prp);
  prp->parent = *pr;
  prp->next_ = NULL;
  prp->name = NULL;
  prp->textp = NULL;
  prp->shadedp = NULL;
  if (prp->outlinep != NULL) {  /* We have to duplicate the stored string */
    newstr(&prp->outlinep);
    addstring(&freeseg, prp->outlinep, (*pr)->outlinep->segmnt,
	      (*pr)->outlinep->seginx, (*pr)->outlinep->len);
  }
  pexit(*pr, &prp->aat);
  (*pr)->son = prp;
  setthen(&prp->spec);
  *pr = prp;
}


void lineardir(primitive *pr, double dy, double dx, int *state)
{
  if (!(teststflag(*state, XLto) | teststflag(*state, XLdirecton)))
    pr->UU.Uline.endpos = pr->aat;
  switch (pr->direction) {

  case XLup:
    pr->UU.Uline.endpos.ypos += dy;
    break;

  case XLdown:
    pr->UU.Uline.endpos.ypos -= dy;
    break;

  case XLleft:
    pr->UU.Uline.endpos.xpos -= dx;
    break;

  case XLright:
    pr->UU.Uline.endpos.xpos += dx;
    break;
  }
  setstflag(state, XLdirecton);
}


boolean hasoutline(int lx, boolean warn)
{
  boolean hs;

  hs = (lx == XLspline || lx == XLarrow || lx == XLline || lx == XLarc ||
	lx == XLellipse || lx == XLcircle || lx == XLbox);
  if (!hs && warn)
    markerror(858);
  return hs;
}


boolean hasshade(int lx, boolean warn)
{
  boolean hs;

  hs = (lx == XLellipse || lx == XLcircle || lx == XLbox);
  if (!hs && warn)
    markerror(858);
  return hs;
}


/*                   This is the syntactic action routine. */
void produce(stackinx newp, int p)
{
  /* newp: stackinx; p: integer */
  Char lastc;
  nametype *lastn, *namptr;
  fbuffer *lastm;
  arg *macp, *lastp;
  primitive *primp, *prp, *eb;
  int i, j, k, kk, lj, ll, mm;
  double r, s, t, x1, y1, dx, dy, ts;
  boolean truth;
  attribute *WITH, *WITH1;
  primitive *WITH2;
  attribute *WITH3;
  nametype *WITH4;
  int FORLIM;
  fbuffer *WITH5;
  postype *WITH6;

  WITH = &attstack[newp];

  /*D with attstack^[newp] do if (debuglevel = 2) and (
     ((p >= block1) and (p <= block3)) or
     ((p > object1) and (p <= object23))
     or (p in [sprintf2,string2,element6,element12])) then printobject(prim);
  if debuglevel > 0 then with attstack^[newp] do
     if p in [ assignment1..assignment4,
               expression1,expression2,
               logprod2,
               logval2,
               expression2..expression5,
               term2..term4,
               factor2,factor3,
               primary1..primary12,primary14,primary15
               ] then begin
           write(log,'value='); wfloat(log,xval);
           writeln(log) end
     else if p in [position1..position3,
        location1,location2,shift2,shift3,place1..place3] then begin
        write(log,'location:');
        with attstack^[newp] do wpair(log,xval,yval);
        writeln(log); flush(log); end D*/
  /*D;if (linesignal > 0) and (p=input2) then begin
      writeln(stderr,'bottom:'); flush(stderr); end D*/
  /* D if (debuglevel > 0) then begin
        writeln('Production(newp=',newp:1,
                     ',lexval=',attstack^[newp].lexval:1,
                     ',prod=',p:1,')' )
        end; D */
  /*D if (debuglevel > 0) then begin
     writeln(log, 'Production(newp=',newp:1,
                  ',lexval=',attstack^[newp].lexval:1,
                  ',prod=',p:1,')' );
     flush(log)
     end; D*/
  /* Dwriteln('Produce Step 1, debuglevel=',debuglevel);
     writeln(log,'Produce Step 1'); D */
  switch (p) {

  case -2:
    inittwo();
    break;

  case -1:
    if (envblock != NULL)
      envblock->direction = XLright;
    inlogic = false;
    inbuf = NULL;
    break;

  /*  0   METAGOAL = input "<EOF>"   */

  case METAGOAL1:
    break;

  /*  1   input = "<EMPTY>"   */
  /*  2         | input picture NL   */
  case input1:
    break;

  case input2:
    /*D if debuglevel > 0 then writeln(log,'deletetree:');
        if linesignal > 0 then writeln(stderr,'deletetree:');flush(stderr);D*/
    deletetree(&envblock);

    /*D if debuglevel > 0 then writeln(log,'deletebufs:');
        if linesignal > 0 then writeln(stderr,'deletebufs:');flush(stderr);D*/
    deletebufs(&freebuf);

    /*D if debuglevel > 0 then writeln(log,'inittwo:');
        if linesignal > 0 then writeln(stderr,'inittwo:'); flush(stderr); D*/
    inittwo();

    if (envblock != NULL)
      envblock->direction = XLright;
    break;

  /*  3   picture = start NL elementlist "<END>"   */
  /*  4           | start NL elementlist NL "<END>"   */
  case picture1:
  case picture2:
    if (WITH->prim != NULL)
      attstack[newp + 2].prim = WITH->prim;
    WITH1 = &attstack[newp + 2];
    getnesw(WITH1->prim);
    /*D if debuglevel > 0 then begin
       writeln(log,' Global dimensions:');
       write(log,'(n,s)(e,w)=');
       wpair(log,north,south); wpair(log,east,west);
       writeln(log); flush(log)
       end; D*/
    if (envblock != NULL) {
      WITH2 = envblock;
      WITH2->aat.xpos = (east + west) * 0.5;
      WITH2->aat.ypos = (north + south) * 0.5;
      WITH2->UU.UEMPTY7.blockheight = north - south;
      WITH2->UU.UEMPTY7.blockwidth = east - west;
    }
    if (drawmode == xfig) {
      shift(envblock, -west, -south);
      north -= south;
      east -= west;
      west = 0.0;
      south = 0.0;
      xfheight = north;
      /*D; if debuglevel > 0 then begin flush(log);
         writeln(log,'After shift:');
         printobject( envblock );
         printobject( envblock^.son ); writeln(log); flush(log) end D*/
    }
    WITH3 = &attstack[newp];
    getscale(WITH3->xval, WITH3->yval, envblock, &scale, &fsc);
    /*D if debuglevel > 0 then begin
       with attstack^[newp] do if (xval > 0.0) and (east > west) then
          begin write( log,'fsc='); wfloat(log, fsc ); writeln(log) end;
       writeln(log,' ================='); flush(log) end; D*/
    drawtree(north, south, east, west, envblock);
    break;

  /*  5   NL = ["^M"]"<NL>"   */
  /*  6      | "<ERROR>"   */
  case NL1:
  case NL2:
    break;

  /*  7   start = "<START>"   */
  /*  8         | "<START>" term   */
  /*  9         | "<START>" term term   */
  case start1:
    break;

  /*D if debuglevel > 0 then begin writeln(log,'.PS');
     flush(log) end D*/
  case start2:
    WITH->xval = attstack[newp + 1].xval;
    break;

  case start3:
    WITH->xval = attstack[newp + 1].xval;
    WITH->yval = attstack[newp + 2].xval;
    break;

  /* 10   elementlist = "<EMPTY>"   */
  /* 11               | element   */
  /* 12               | elementlist NL element   */
  case elementlist1:
    WITH->state = 0;
    break;

  case elementlist2:
    WITH->state = 0;
    if (WITH->prim != NULL && WITH->lexval != XLcontinue) {
      i = newp - 1;
      j = 0;
      while (i > j) {
	if ((attstack[i].lexval == XFOR || attstack[i].lexval == XLBRACE ||
	     attstack[i].lexval == XSEMICOLON ||
	     attstack[i].lexval == XNL) && attstack[i].prim == NULL) {
	  /*repeat ,Xrepeat */
	  i--;
	  continue;
	}
	/*D if debuglevel > 0 then begin
	   writeln(log,' Elementlist2: newp= ',newp:1,
	      ', attstack^[',i:1,'].lexval= ',attstack^[i].lexval:1);
	   if attstack^[i].prim<>nil then begin
	      writeln(log,'attstack^[',i:1,'].prim= ');
	      snaptype(log,attstack^[i].prim^.ptype)
	      end
	   end; D*/
	j = i;
	/*D if debuglevel>0 then writeln(log,' Search ends at i=',i:1); D*/
	if (attstack[i].prim != NULL) {
	  addelem(attstack[i].prim, WITH->prim);
	  /*D if debuglevel > 0  then printobject(attstack^[i].prim); D*/
	  WITH->state = i - newp;
	  continue;
	}
	if (attstack[i].lexval == XLBRACKET) {
	  attstack[i + 1].prim = WITH->prim;
	  /*D if debuglevel > 0  then printobject(attstack^[i+1].prim); D*/
	  WITH->state = i - newp + 1;
	} else {
	  attstack[i].prim = WITH->prim;
	  /*D if debuglevel > 0  then printobject(attstack^[i].prim); D*/
	  WITH->state = i - newp;
	}
      }
    }
    break;

  /* 12               | elementlist NL element */
  case elementlist3:
    if (attstack[newp + 2].prim != NULL &&
	attstack[newp + 2].lexval != XLcontinue) {
      if (WITH->prim == NULL) {
	attstack[newp] = attstack[newp + 2];
	redubuf[reduinx + REDUMAX].prod_ = elementlist2;
	reduinx--;
      } else
	addelem(attstack[newp + WITH->state].prim, attstack[newp + 2].prim);
    }
    break;

  /* 13   term = factor   */
  /* 14        | term "*" factor   */
  /* 15        | term "/" factor   */
  /* 16        | term "%" factor   */
  case term1:
    break;

  case term2:
    WITH->xval *= attstack[newp + 2].xval;
    break;

  case term3:
    if (attstack[newp + 2].xval == 0.0) {
      markerror(852);
      WITH->xval = 0.0;
    } else
      WITH->xval /= attstack[newp + 2].xval;
    break;

  case term4:
    if (attstack[newp + 2].xval == 0.0) {
      markerror(852);
      WITH->xval = 0.0;
    } else {
      WITH->xval = (long)floor(WITH->xval + 0.5) %
		   (long)floor(attstack[newp + 2].xval + 0.5);
/* p2c: dpic.p, line 1964:
 * Note: Using % for possibly-negative arguments [317] */
    }
    break;

  /* 17   element = namedbox   */
  /* 18           | "<Label>" suffix ":"   */
  /* 19           | "<Label>" suffix ":" position   */
  /* 20           | assignlist   */
  /* 21           | "<directon>"   */
  /* 22           | "<troff>"   */
  /* 23           | command   */
  /* 24           | lbrace "lbrace" elementlist optnl "rbrace"   */
  /* 25           | ifpart   */
  /* 26           | elsehead "lbrace" elementlist optnl "rbrace"   */
  /* 27           | for "rbrace"   */
  /* 28           | "command" stringexpr   */
  /* 29           | "exec" stringexpr   */
  case element1:
    if (WITH->prim != NULL) {
      prp = WITH->prim;
      if (WITH->prim->ptype == XLspline || WITH->prim->ptype == XLmove ||
	  WITH->prim->ptype == XLarrow || WITH->prim->ptype == XLline) {
	if (WITH->startchop != 0.0) {
	  WITH2 = WITH->prim;
	  dx = WITH2->UU.Uline.endpos.xpos - WITH2->aat.xpos;
	  dy = WITH2->UU.Uline.endpos.ypos - WITH2->aat.ypos;
	  s = linlen(dx, dy);
	  /*D if debuglevel = 2 then begin
	     write(log,' element1 startchop='); wfloat(log,startchop);
	     write(log,' (dx,dy)='); wpair(log,dx,dy);
	     write(log,' s='); wfloat(log,s); writeln(log) end; D*/
	  if (s != 0.0) {
	    t = WITH->startchop / s;
	    WITH2->aat.xpos += t * dx;
	    WITH2->aat.ypos += t * dy;
	  }
	}
	while (prp->son != NULL)
	  prp = prp->son;
	if (WITH->endchop != 0.0) {
	  dx = prp->UU.Uline.endpos.xpos - prp->aat.xpos;
	  dy = prp->UU.Uline.endpos.ypos - prp->aat.ypos;
	  s = linlen(dx, dy);
	  /*D if debuglevel = 2 then begin
	     write(log,' element1 endchop='); wfloat(log,endchop);
	     write(log,' (dx,dy)='); wpair(log,dx,dy);
	     write(log,' s='); wfloat(log,s); writeln(log) end; D*/
	  if (s != 0.0) {
	    t = WITH->endchop / s;
	    prp->UU.Uline.endpos.xpos -= t * dx;
	    prp->UU.Uline.endpos.ypos -= t * dy;
	  }
	}
      }
      /*D ; if debuglevel > 0 then begin
         write(log,' element1 Here=');
         with envblock^ do wpair(log,here.xpos,here.ypos); writeln(log);
         printobject(prim)
         end D*/
      pexit(prp, &envblock->UU.UEMPTY7.here);
    }
    break;

  case element2:
  case element3:
    if (attstack[newp + 1].lexval != XEMPTY)
      addsuffix(chbuf, &WITH->chbufx, &WITH->length, attstack[newp + 1].xval);
    prp = findplace(envblock->son, chbuf, WITH->chbufx, WITH->length);
    if (prp == NULL) {
      newprim(&WITH->prim, XLabel, envblock);
      newstr(&WITH->prim->name);
      addstring(&freeseg, WITH->prim->name, chbuf, WITH->chbufx, WITH->length);
      prp = WITH->prim;
    } else if (prp->ptype != XLabel) {
      newprim(&WITH->prim, XLabel, envblock);
      WITH->prim->name = prp->name;
      prp->name = NULL;
      prp = WITH->prim;
    }
    if (p == element2)
      prp->aat = envblock->UU.UEMPTY7.here;
    else {
      prp->aat.xpos = attstack[newp + 3].xval;
      prp->aat.ypos = attstack[newp + 3].yval;
      /*D; if (debuglevel > 0) and (prim<>nil) then printobject(prim)D*/
    }
    break;

  case element4:
    WITH->lexval = XLBRACE;
    break;

  case element5:
    envblock->direction = WITH->lexval;
    WITH->lexval = XLBRACE;
    break;

  case element6:
    newprim(&WITH->prim, XLtroff, envblock);
    newstr(&WITH->prim->textp);
    addstring(&freeseg, WITH->prim->textp, chbuf, WITH->chbufx, WITH->length);
    break;

  case element7:
    WITH->lexval = XLBRACE;
    break;

  case element8:
    envblock->UU.UEMPTY7.here.xpos = WITH->xval;
    envblock->UU.UEMPTY7.here.ypos = WITH->yval;
    if (WITH->state == XLright || WITH->state == XLleft ||
	WITH->state == XLdown || WITH->state == XLup)
      envblock->direction = WITH->state;
    if (attstack[newp + 2].state == 0)
      attstack[newp] = attstack[newp + 2];
    break;

  case element9:
    /* blank case */
    break;

  case element10:
    /* blank case */
    break;

  case element11:
    /* blank case */
    break;

  case element12:
    if (attstack[newp + 1].prim != NULL) {
      newprim(&WITH->prim, XLtroff, envblock);
      WITH->prim->textp = attstack[newp + 1].prim->textp;
      attstack[newp + 1].prim->textp = NULL;
      if (envblock->son == attstack[newp + 1].prim)
	envblock->son = WITH->prim;
      deletestringbox(&attstack[newp + 1].prim);
    }
    break;

  case element13:
    if (attstack[newp + 1].prim != NULL) {
      if (attstack[newp + 1].prim->textp != NULL) {
	if (attstack[newp + 1].prim->textp->segmnt != NULL) {
	  WITH4 = attstack[newp + 1].prim->textp;
	  newbuf(&lastm);
	  lastm->carray[1] = nlch;
	  lastm->savedlen = 1;
	  copyleft(lastm, &inbuf);
	  FORLIM = WITH4->len;
	  for (i = 1; i <= FORLIM; i++)
	    lastm->carray[i] = WITH4->segmnt[WITH4->seginx + i - 1];
	  lastm->savedlen = WITH4->len;
	  copyleft(lastm, &inbuf);
	  lastm->carray[1] = nlch;
	  lastm->savedlen = 1;
	  copyleft(lastm, &inbuf);
	  deletestringbox(&attstack[newp + 1].prim);   /*D,2D*/
	  disposebufs(&lastm);
	}
      }
    }
    break;
    /*              | loop "}" */
    /*              | break */
    /*repeat element14,element15: ; */

  /* 30   lbrace = "<EMPTY>"   */
  case lbrace1:
    WITH->xval = envblock->UU.UEMPTY7.here.xpos;
    WITH->yval = envblock->UU.UEMPTY7.here.ypos;
    WITH->state = envblock->direction;
    break;

  /* 31   namedbox = object   */
  /* 32            | "<Label>" suffix ":" object   */
  case namedbox1:
    if (WITH->prim != NULL) {  /* then, arc, deferred shift */
      prp = WITH->prim;
      while (isthen(WITH->prim))
	WITH->prim = WITH->prim->parent;
      if (prp != WITH->prim) {
	WITH->prim->name = prp->name;
	prp->name = NULL;
      }
      if (WITH->prim->ptype == XLarc)
	arcenddir(prp);
      if (teststflag(WITH->state, XLat)) {
	WITH2 = WITH->prim;
	i = getstval(WITH->state);
	if (i == XLfloat) {
	  getnesw(WITH->prim);
	  dx = west + WITH->startchop;
	  dy = south + WITH->endchop;
	} else if (WITH->root != NULL) {
	  corner(WITH->root, i, &dx, &dy);
	  WITH->root = NULL;
	} else
	  corner(WITH->prim, i, &dx, &dy);
	if (WITH2->ptype != XLarc)
	  shift(WITH->prim, WITH->xval - dx, WITH->yval - dy);
	else {
	  x1 = WITH2->aat.xpos +
	       WITH2->UU.Uline.aradius * cos(WITH2->UU.Uline.endpos.xpos);
	      /* from */
	  y1 = WITH2->aat.ypos +
	       WITH2->UU.Uline.aradius * sin(WITH2->UU.Uline.endpos.xpos);
	  if (teststflag(WITH->state, XLto)) {
		/* to X from Here|Y implied */
		  if (i != XEMPTY && i != XDc)
	      markerror(858);
	    r = WITH2->aat.xpos + WITH2->UU.Uline.aradius * cos(
		    WITH2->UU.Uline.endpos.xpos + WITH2->UU.Uline.endpos.ypos);
		/* to */
	    s = WITH2->aat.ypos + WITH2->UU.Uline.aradius * sin(
		    WITH2->UU.Uline.endpos.xpos + WITH2->UU.Uline.endpos.ypos);
	    WITH2->aat.xpos = WITH->xval;
	    WITH2->aat.ypos = WITH->yval;
	    WITH2->UU.Uline.aradius = linlen(r - WITH2->aat.xpos,
					    s - WITH2->aat.ypos);
	    setangles(&WITH2->UU.Uline.endpos.xpos,
		      &WITH2->UU.Uline.endpos.ypos, WITH2->aat, x1, y1, r, s);
	  } else if (teststflag(WITH->state, XLfrom)) {
	    if (i != XEMPTY && i != XDc)
	      markerror(858);
	    WITH2->aat.xpos = WITH->xval;
	    WITH2->aat.ypos = WITH->yval;
	    t = datan(y1 - WITH2->aat.ypos, x1 - WITH2->aat.xpos);
	    r = WITH2->aat.xpos +
		WITH2->UU.Uline.aradius * cos(t + WITH2->UU.Uline.endpos.ypos);
	    s = WITH2->aat.ypos +
		WITH2->UU.Uline.aradius * sin(t + WITH2->UU.Uline.endpos.ypos);
	    WITH2->UU.Uline.aradius = linlen(x1 - WITH2->aat.xpos,
					    y1 - WITH2->aat.ypos);
	    setangles(&WITH2->UU.Uline.endpos.xpos,
		      &WITH2->UU.Uline.endpos.ypos, WITH2->aat, x1, y1, r, s);
	  } else
	    shift(WITH->prim, WITH->xval - dx, WITH->yval - dy);
	}
      }
    }
    break;

  case namedbox2:
    if (attstack[newp + 3].prim != NULL) {
      if (attstack[newp + 1].lexval != XEMPTY)
	addsuffix(chbuf, &WITH->chbufx, &WITH->length,
		  attstack[newp + 1].xval);
      primp = findplace(envblock->son, chbuf, WITH->chbufx, WITH->length);
      if (primp != NULL) {
	attstack[newp + 3].prim->name = primp->name;
	primp->name = NULL;
      } else {
	WITH2 = attstack[newp + 3].prim;
	/*D if debuglevel = 2 then
	   writeln(log,'Label not found, creating it'); D*/
	newstr(&WITH2->name);
	addstring(&freeseg, WITH2->name, chbuf, WITH->chbufx, WITH->length);
      }
      attstack[newp] = attstack[newp + 3];
      redubuf[reduinx + REDUMAX].prod_ = namedbox1;
      reduinx--;
    }
    break;

  /* 33   suffix = "<EMPTY>"   */
  /* 34          | "[" expression "]"   */
  case suffix1:
    WITH->lexval = XEMPTY;
    break;

  case suffix2:
    WITH->xval = attstack[newp + 1].xval;
    break;

  /* 35   position = pair   */
  /* 36            | expression "between" position "and" position   */
  /* 38            | expression "<" position "," position ">" shift   */
  case position1:
    break;

  case position2:
  case position4:
    r = WITH->xval;
    WITH->xval = attstack[newp + 2].xval +
		 r * (attstack[newp + 4].xval - attstack[newp + 2].xval);
    WITH->yval = attstack[newp + 2].yval +
		 r * (attstack[newp + 4].yval - attstack[newp + 2].yval);
    if (p == position4 && attstack[newp + 6].lexval != XEMPTY) {
      WITH->xval += attstack[newp + 6].xval;
      WITH->yval += attstack[newp + 6].yval;
    }
    break;

  /* 37          | expression "of" "the" "way" "between" position "and" position*/
  case position3:
    r = WITH->xval;
    WITH->xval = attstack[newp + 5].xval +
		 r * (attstack[newp + 7].xval - attstack[newp + 5].xval);
    WITH->yval = attstack[newp + 5].yval +
		 r * (attstack[newp + 7].yval - attstack[newp + 5].yval);
    break;

  /* 39   assignlist = assignment   */
  /* 40              | assignlist "," assignment   */
  case assignlist1:
    break;

  case assignlist2:
    WITH->xval = attstack[newp + 2].xval;
    break;

  /* 41   command = "print" expression   */
  /* 42           | "print" position   */
  /* 43           | "print" stringexpr   */
  /* 44           | "reset"   */
  /* 45           | "reset" resetlist   */
  /* 46           | "sh" stringexpr   */
  /* 47           | "copy" stringexpr   */
  /* 48           | defhead optnl "lbrace" "rbrace"   */
  /* 49           | "undefine" "<name>"   */
  /* 50           | "undefine" "<Label>"   */
  case command1:
    WITH1 = &attstack[newp + 1];
    wfloat(&stderr_, WITH1->xval);
    putc('\n', stderr_);
    consoleflush();
    break;

  case command2:
    WITH1 = &attstack[newp + 1];
    wpair(&stderr_, WITH1->xval, WITH1->yval);
    putc('\n', stderr_);
    consoleflush();
    break;

  case command3:
    WITH1 = &attstack[newp + 1];
    if (WITH1->prim != NULL) {
      wstring(&stderr_, WITH1->prim->textp);
      putc('\n', stderr_);
      consoleflush();
    }
    deletestringbox(&WITH1->prim);
    break;

  case command4:
    resetenv(0, envblock);
    break;

  case command5:
    /* blank case */
    break;

  case command6:
    WITH1 = &attstack[newp + 1];
    if (WITH1->prim != NULL) {
      if (WITH1->prim->textp != NULL) {
	WITH4 = WITH1->prim->textp;
	if (WITH4->segmnt != NULL) {
	  if (WITH4->seginx + WITH4->len >= CHBUFSIZ)
	    markerror(866);
	  else {
	    WITH4->segmnt[WITH4->seginx + WITH4->len] = '\0';
#ifdef SAFE_MODE
	    markerror(906);
#else
	    if (safemode)
	      markerror(906);
	    else
	      system(&WITH4->segmnt[WITH4->seginx]);
#endif
	  }
	}
      }
      deletestringbox(&WITH1->prim);
    }
    break;

  case command7:
    WITH1 = &attstack[newp + 1];
    if (WITH1->prim != NULL) {
#ifdef SAFE_MODE
      markerror(906);
#else
      pointinput(WITH1->prim->textp);
#endif
      deletestringbox(&WITH1->prim);
    }
    break;

  case command8:
    /* blank case */
    break;

  case command9:
  case command10:
    attstack[newp] = attstack[newp + 1];
    macp = findmacro(macros, chbuf, WITH->chbufx, WITH->length, &lastp);
    if (macp != NULL) {
      if (lastp != NULL)
	lastp->nextb = macp->nextb;
      if (macp == macros)   /*D,5D*/
	macros = macp->nextb;
      disposebufs(&macp->argbody);
      Free(macp);
    }
    break;

  /* 51   optnl = "<EMPTY>"   */
  /* 52         | NL   */
  case optnl1:
  case optnl2:
    break;

  /* 53   ifpart = ifhead "lbrace" elementlist optnl "rbrace"   */
  case ifpart1:
    break;

  /* 54   elsehead = ifpart "else"   */
  case elsehead1:
    if (WITH->xval == 0.0) {
      attstack[newp + 1].lexval = XLBRACE;
      WITH->lexval = XLBRACE;
    } else
      skiptobrace();
    break;

  /* 55   for = forhead "lbrace" elementlist optnl   */
  /* 56       | forincr elementlist optnl   */
  case for1:
  case for2:
    break;

  /* 57   stringexpr = string   */
  /* 58              | stringexpr "+" string   */
  case stringexpr1:
    break;

  case stringexpr2:
    if (attstack[newp + 2].prim != NULL) {
      WITH2 = WITH->prim;
      prp = attstack[newp + 2].prim;
      WITH2->UU.Ubox.boxwidth += prp->UU.Ubox.boxwidth;
      if (prp->textp != NULL) {
	if (WITH2->textp == NULL) {
	  WITH2->textp = prp->textp;
	  prp->textp = NULL;
	} else if (WITH2->textp->segmnt == prp->textp->segmnt) {
	  WITH2->textp->len += prp->textp->len;
	  putbval(WITH2->textp->segmnt, bval(WITH2->textp->segmnt) - 1);
	  prp->textp->segmnt = NULL;
	} else
	  appendstring(WITH2->textp, prp->textp->segmnt, prp->textp->seginx,
		       prp->textp->len);
      }
      deletetree(&attstack[newp + 2].prim);
    }
    break;

  /*      break = "break" */
  /*repeat break1: if inbuf = nil then begin end
     else if inbuf^.attrib <= 0 then begin end
     else if attstack^[inbuf^.attrib].lexval <> Xrepeat then markerror(858)
     else begin
        while inbuf^.nextb <> nil do inbuf := inbuf^.nextb ;
        inbuf^.attrib := -1 ;
        inbuf^.readx := inbuf^.savedlen+1
        end; */

  /* 59   string = "<string>"   */
  /* 60          | sprintf ")"   */
  case string1:
    newprim(&WITH->prim, XLstring, envblock);
    eb = findenv(envblock);
    WITH2 = WITH->prim;
    WITH2->UU.Ubox.boxheight = eb->UU.UEMPTY7.env[XLtextht - XLenvvar - 1];
    WITH2->UU.Ubox.boxwidth = eb->UU.UEMPTY7.env[XLtextwid - XLenvvar - 1];
    if (drawmode == xfig && WITH2->UU.Ubox.boxwidth == 0.0) {
      /* To keep xfig from crashing, assume text height is .1
         and a character is .1*0.75 wide */
      eb = findenv(envblock);
      if (WITH2->UU.Ubox.boxheight == 0.0)
	WITH2->UU.Ubox.boxheight = 0.1 * eb->UU.UEMPTY7.env[XLscale - XLenvvar - 1];
      WITH2->UU.Ubox.boxwidth = WITH2->UU.Ubox.boxheight * WITH->length * 0.75;
    }
    WITH2->UU.Ubox.boxradius = 0.0;
    newstr(&WITH2->textp);
    addstring(&freeseg, WITH2->textp, chbuf, WITH->chbufx, WITH->length);
    break;

  case string2:
    break;

  /* 61   assignment = "<name>" suffix "=" expression   */
  /* 62              | "<name>" suffix "=" assignment   */
  /* 63              | "<envvar>" "=" expression   */
  /* 64              | "<envvar>" "=" assignment   */
  case assignment1:
  case assignment2:
    if (attstack[newp + 1].lexval != XEMPTY)
      addsuffix(chbuf, &WITH->chbufx, &WITH->length, attstack[newp + 1].xval);
    if (attstack[newp + 2].lexval == XLeq) {
      WITH->varname = findname(envblock->UU.UEMPTY7.vars, chbuf, WITH->chbufx,
			       WITH->length, &lastn);
      if (WITH->varname == NULL) {
	newstr(&WITH->varname);
	addstring(&freeseg, WITH->varname, chbuf, WITH->chbufx, WITH->length);
	if (lastn == NULL)
	  envblock->UU.UEMPTY7.vars = WITH->varname;
	else
	  lastn->next_ = WITH->varname;
      }
      WITH->varname->val = attstack[newp + 3].xval;
    } else {
      WITH->varname = glfindname(envblock, chbuf, WITH->chbufx, WITH->length,
				 &lastn);
      if (WITH->varname != NULL)
	eqop(&WITH->varname->val, attstack[newp + 2].lexval,
	     attstack[newp + 3].xval);
    }
    if (WITH->varname != NULL) {
      WITH->xval = WITH->varname->val;
      /*D; if debuglevel > 0 then
         writeln(log,' varname <> nil=',varname <> nil:1) D*/
    }
    break;

  case assignment3:
  case assignment4:
    if (envblock != NULL) {
      if (WITH->lexval == XLscale)
	resetscale(attstack[newp + 2].xval, attstack[newp + 1].lexval,
		   envblock);
      else {
	if (envblock->UU.UEMPTY7.env == NULL)
	  inheritenv(envblock);
	eqop(&envblock->UU.UEMPTY7.env[WITH->lexval - XLenvvar - 1],
	     attstack[newp + 1].lexval, attstack[newp + 2].xval);
      }
      WITH->xval = envblock->UU.UEMPTY7.env[WITH->lexval - XLenvvar - 1];
      /*D if debuglevel > 0 then writeln(log,' Assignment4: lexval=',lexval:1,
         ' value=',envblock^.env^[lexval]); D*/
      WITH->startchop = WITH->lexval;
      if (WITH->lexval == XLdashwid || WITH->lexval == XLlinethick) {
	newprim(&WITH->prim, XLtroff, envblock);
	if (WITH->lexval == XLlinethick)
	  WITH->prim->lthick = WITH->xval;
	else
	  WITH->prim->lparam = WITH->xval;
      } else
	WITH->lexval = XLBRACE;
    }
    break;

  /* 65   expression = term   */
  /* 66              | "+" term   */
  /* 67              | "-" term   */
  /* 68              | expression "+" term   */
  /* 69              | expression "-" term   */
  case expression1:
    break;

  case expression2:
    WITH->xval = attstack[newp + 1].xval;
    break;

  case expression3:
    WITH->xval = -attstack[newp + 1].xval;
    break;

  case expression4:
    WITH->xval += attstack[newp + 2].xval;
    break;

  case expression5:
    WITH->xval -= attstack[newp + 2].xval;
    break;

  /* 70   ifhead = setlogic "if" logexpr "then"   */
  case ifhead1:
    inlogic = false;
    WITH->xval = attstack[newp + 2].xval;
    /*D if debuglevel > 0 then begin
        if xval <> 0.0 then writeln(log,' true') else writeln(log,' false')
        end; D*/
    if (WITH->xval != 0.0) {
      for (i = 0; i <= 3; i++)
	attstack[newp + i].lexval = XLBRACE;
    } else
      skiptobrace();
    break;

  /* 71   setlogic = "<EMPTY>"   */
  case setlogic1:
    inlogic = true;
    break;

  /* 72   logexpr = logprod   */
  /* 73           | logexpr "||" logprod   */
  case logexpr1:
    break;

  case logexpr2:
    if (WITH->xval != 0.0 || attstack[newp + 2].xval != 0.0)
      WITH->xval = 1.0;
    else
      WITH->xval = 0.0;
    break;

  /* 74   forhead = "for" assignlist "to" expression do   */
  case forhead1:
    if (attstack[newp + 1].startchop == 0.0)
      WITH->varname = attstack[newp + 1].varname;
    else
      WITH->startchop = attstack[newp + 1].startchop;
    WITH->xval = attstack[newp + 1].xval;   /* initial value  */
    WITH->yval = attstack[newp + 4].xval;   /* increment */
    r = attstack[newp + 3].xval;   /* final value */
    WITH->length = 0;
    if (WITH->xval == r)
      WITH->length = 1;
    else if (attstack[newp + 4].lexval == XSTAR && WITH->xval == 0.0)
      markerror(860);
    else if (attstack[newp + 4].lexval == XSTAR) {
      t = r / WITH->xval;
      if (t <= 0.0 || WITH->yval < 0.0)
	markerror(862);
      else if (WITH->yval == 0.0 && t > 1.0)
	markerror(860);
      else if (WITH->yval == 0.0)
	WITH->length = 1;
      else {
	r = log(t) / log(WITH->yval);
	if (r < 0.0)
	  markerror(860);
	else
	  WITH->length = (long)r + 1;
      }
    } else if (WITH->yval == 0.0)
      markerror(860);
    else {
      r = (r - WITH->xval) / WITH->yval;
      if (r >= 0.0)
	WITH->length = -((long)r + 1);
    }
    if (WITH->length == 0)
      skiptobrace();
    else {
      for (i = 0; i <= 4; i++) {
	attstack[newp + i].lexval = XLBRACE;

	/*D; if debuglevel > 0 then begin
	   write(log,'for: initial='); wfloat(log,xval);
	   write(log,' final='); wfloat(log,attstack^[newp+3].xval);
	   write(log,' incr='); wfloat(log,yval);
	   writeln(log,' count=',length:1); end; D*/
      }
    }
    break;

  /* 75   forincr = for ":"   */
  case forincr1:
    /* compute loop variable */
    if (WITH->length < 0)
      WITH->xval += WITH->yval;
    else
      WITH->xval *= WITH->yval;
    /*D if debuglevel > 0 then begin write(log,'forincr: xval=');
        wfloat(log,xval) end; D*/
    /* store loop variable */
    if (WITH->varname != NULL) {
      WITH->varname->val = WITH->xval;
      /* loop variable is an env variable */
    } else if ((long)floor(WITH->startchop + 0.5) != XLscale) {
      if (envblock->UU.UEMPTY7.env == NULL)
	inheritenv(envblock);
      envblock->UU.UEMPTY7.env[(int)((long)floor(WITH->startchop + 0.5)) -
			   XLenvvar - 1] = WITH->xval;
    } else
      resetscale(WITH->xval, XLeq, envblock);

    /*D if debuglevel > 0 then begin writeln(log,' varname <> nil=',
       varname <> nil:1) end; D*/
    /*D if debuglevel = 2 then begin prtstval(state); writeln(log,
             ' xval ', xval:7:4 ); flush(log) end; D*/
    for (i = 0; i <= 1; i++)
      attstack[newp + i].lexval = XLBRACE;
    break;

  /*      loop = loophead "{" elementlist optnl */
  /*           | loopincr elementlist optnl */
  /*repeat loop1,loop2: ; */

  /* 76   do = "do"   */
  /* 77      | by expression "do"   */
  case do1:
    WITH->xval = 1.0;
    break;

  case do2:
    WITH->xval = attstack[newp + 1].xval;
    break;

  /*      loophead = "repeat" */
  /*repeat loophead1: ; */

  /*      loopincr = loop ":" */
  /*repeat loopincr1: attstack^[newp+1].lexval := XLBRACE ; */

  /* 78   by = "by"   */
  /* 79      | "by" "*"   */
  case by1:
    break;

  case by2:
    WITH->lexval = attstack[newp + 1].lexval;
    break;

  /* 80   resetlist = "<envvar>"   */
  /* 81             | resetlist "," "<envvar>"   */
  case resetlist1:
    resetenv(WITH->lexval, envblock);
    break;

  case resetlist2:
    resetenv(attstack[newp + 2].lexval, envblock);
    break;

  /* 82   defhead = "define" "<name>"   */
  /* 83           | "define" "<Label>"   */
  case defhead1:
  case defhead2:
    attstack[newp] = attstack[newp + 1];
    macp = findmacro(macros, chbuf, WITH->chbufx, WITH->length, &lastp);
    if (macp == NULL) {   /*D,6D*/
      newarg(&macp);
      if (lastp == NULL)
	macros = macp;
      else
	lastp->nextb = macp;
    }
    disposebufs(&macp->argbody);
    newbuf(&macp->argbody);   /* copy the macro name */
    WITH5 = macp->argbody;
    FORLIM = WITH->length;
    for (i = 1; i <= FORLIM; i++)
      WITH5->carray[i] = chbuf[WITH->chbufx + i - 1];
    WITH5->savedlen = WITH->length;
    WITH5->readx = WITH->length + 1;
    readfor(macp->argbody, -WITH->length, &macp->argbody);
	/* append the body */
    lastm = macp->argbody;
    while (lastm->nextb != NULL)
      lastm = lastm->nextb;
    lastm->carray[lastm->savedlen] = etxch;
    /*D; if debuglevel > 1 then begin
       writeln(log); write(log,'def','head1');
       lastm := macp^.argbody; while lastm<> nil do begin
          wrbuf(lastm,3,0); lastm := lastm^.nextb end
       end D*/
    break;

  /* 84   sprintf = "sprintf" "(" "<string>"   */
  /* 85           | "sprintf" "(" "<string>" "," exprlist   */
  case sprintf1:
  case sprintf2:
    newprim(&WITH->prim, XLstring, envblock);
    WITH2 = WITH->prim;
    eb = findenv(envblock);
    WITH2->UU.Ubox.boxheight = eb->UU.UEMPTY7.env[XLtextht - XLenvvar - 1];
    WITH2->UU.Ubox.boxwidth = eb->UU.UEMPTY7.env[XLtextwid - XLenvvar - 1];
    WITH2->UU.Ubox.boxradius = 0.0;
    newstr(&WITH2->textp);
    if (p == sprintf1)
      mm = 0;
    else
      mm = attstack[newp + 4].state;
    if (tmpbuf == NULL)
      tmpbuf = Malloc(sizeof(chbufarray));
    i = 0;   /* expression count */
    j = 0;   /* end of current substring */
    lj = j;   /* start of current substring */
    kk = 0;   /* substring count */
    WITH1 = &attstack[newp + 2];
    while (j < WITH1->length) {
      /*D begin
         if debuglevel > 0 then begin writeln(log,
            ' looping, i,j,lj,length=',i:4,j:4,lj:4,length:4,
            ' c="', chbuf^[chbufx+j],'"'); flush(log) end; D*/
      if (chbuf[WITH1->chbufx + j] != '%') {
	j++;
	if (j == WITH1->length)
	  kk = putstring(kk, attstack[newp].prim->textp, chbuf,
			 WITH1->chbufx + lj, j - lj);
	continue;
      }
      if (chbuf[WITH1->chbufx + j + 1] == '%') {  /* %% prints % */
	kk = putstring(kk, attstack[newp].prim->textp, chbuf,
		       WITH1->chbufx + lj, j - lj + 1);
	j += 2;
	lj = j;
	continue;
      }
      if (i >= mm) {  /* not enough args */
	markerror(864);
	j = WITH1->length;
	continue;
      }
      if (j > lj) {
	kk = putstring(kk, attstack[newp].prim->textp, chbuf,
		       WITH1->chbufx + lj, j - lj);
	lj = j;
      }
      k = WITH1->length;
      j++;
      if (chbuf[WITH1->chbufx + j] == '-')
	j++;
#ifdef NO_SNPRINTF
      attstack[newp + 1].state = j;
#endif
      while (j < k) {
	if (chbuf[WITH1->chbufx + j] == 'g' ||
	    chbuf[WITH1->chbufx + j] == 'f' ||
	    chbuf[WITH1->chbufx + j] == 'e')
	  k = j;
	else if (chbuf[WITH1->chbufx + j] == '.' ||
		 isdigit(chbuf[WITH1->chbufx + j]))
	  j++;
	else
	  j = k;
      }

      if (k == WITH1->length) {
	markerror(865);
	continue;
      }
      j++;
      /*D if debuglevel > 0 then begin write(log,'format="');
        for k := lj to j-1 do write(log,chbuf^[chbufx+k]);
        writeln(log, '" nargs=',mm:2,
        ' Numerical print value=',attstack^[newp+4+2*i].xval);
        flush(log) end; D*/
      /* Write the expression to tmpbuf */
#ifdef NO_SNPRINTF
      k = attstack[newp + 1].state;
      ll = j - 1;
      s = 0.0;
      while (k < ll) {
	if (chbuf[WITH1->chbufx + k] == '.')
	  ll = k;
	else {
	  s = 10.0 * s + chbuf[WITH1->chbufx + k] - '0';
	  k++;
	}
      }
      r = 0.0;
      for (ll = k + 1; ll < j; ll++)
	r = 10.0 * r + chbuf[WITH1->chbufx + ll] - '0';
      ll = 1;
      if (s >= CHBUFSIZ || r >= CHBUFSIZ) {
	markerror(865);
	j = WITH1->length;
      } else {
	lastc = chbuf[WITH1->chbufx + j];
	chbuf[WITH1->chbufx + j] = '\0';
	sprintf(&tmpbuf[1], &chbuf[WITH1->chbufx + lj],
		 attstack[newp + i * 2 + 4].xval);
	chbuf[WITH1->chbufx + j] = lastc;
	k = CHBUFSIZ;
	while (ll < k) {
	  if (tmpbuf[ll] == '\0')
	    k = ll;
	  else
	    ll++;
	}
	ll--;
      }
#else
      lastc = chbuf[WITH1->chbufx + j];
      chbuf[WITH1->chbufx + j] = '\0';
      k = snprintf(&tmpbuf[1], CHBUFSIZ, &chbuf[WITH1->chbufx + lj],
		   attstack[newp + i * 2 + 4].xval);
      chbuf[WITH1->chbufx + j] = lastc;
      if (k > CHBUFSIZ - 2) {
	markerror(865);
	ll = CHBUFSIZ - 2;
      } else if (k > 0)
	ll = k;
      else
	ll = 0;
#endif
      /*D if debuglevel > 0 then begin
         write(log,' tmpbuf(1:',ll:1,')=');
         for lj := 1 to ll do write(log,tmpbuf^[lj]);
         writeln(log); flush(log) end; D*/
      /* Copy tmpbuf to the string */
      if (ll > 0 && ll <= CHBUFSIZ - 2)
	kk = putstring(kk, attstack[newp].prim->textp, tmpbuf, 1, ll);
      i++;
      lj = j;
    }
    /*D end; D*/
    if (i < mm)   /* Too many args */
      markerror(864);
    if (drawmode == xfig) {
      WITH2 = WITH->prim;
      if (WITH2->UU.Ubox.boxwidth == 0.0) {
	if (WITH2->UU.Ubox.boxheight == 0.0)
	  WITH2->UU.Ubox.boxheight = 0.1 * eb->UU.UEMPTY7.env[XLscale - XLenvvar - 1];
	WITH2->UU.Ubox.boxwidth = WITH2->UU.Ubox.boxheight *
				  WITH2->textp->len * 0.75;
      }
    }
    break;

  /* 86   exprlist = expression   */
  /* 87            | expression "," exprlist   */
  case exprlist1:
    WITH->state = 1;
    break;

  case exprlist2:
    WITH->state = attstack[newp + 2].state + 1;
    break;

  /* 88   object = block   */
  /* 89          | object "height" expression   */
  /* 90          | object "width" expression   */
  /* 91          | object "radius" expression   */
  /* 92          | object "diameter" expression   */
  /* 93          | object "thickness" expression   */
  /* 94          | object "scaled" expression   */
  /* 95          | object "<directon>" optexp   */
  /* 96          | object "by" pair   */
  /* 97          | object "then"   */
  /* 98          | object "<linetype>" optexp   */
  /* 99          | object "chop" optexp   */
  /*100          | object "filled" optexp   */
  /*101          | object "<arrowhd>"   */
  /*102          | object "cw"   */
  /*103          | object "ccw"   */
  /*104          | object "same"   */
  /*105          | object stringexpr   */
  /*106          | object "from" position   */
  /*107          | object "to" position   */
  /*108          | object "at" position   */
  /*109          | object "<textpos>"   */
  /*110          | object "<colrspec>" stringexpr   */
  /*111          | withobj "<corner>" "at" position   */
  /*112          | withobj "start" "at" position   */
  /*113          | withobj "end" "at" position   */
  /*114          | withobj pair "at" position   */
  /*115          | withobj "." "<Label>" suffix "at" position   */
  /*116          | "continue"   */
  case object1:
    break;

  /*                          | object "height" expression    */
  case object2:
    if (WITH->prim != NULL) {
      WITH2 = WITH->prim;
      switch (WITH2->ptype) {

      case XLbox:
      case XBLOCK:
	if (WITH2->ptype == XBLOCK) {
	  r = 0.5 * (attstack[newp + 2].xval - WITH2->UU.UEMPTY7.blockheight);
	  WITH2->UU.UEMPTY7.blockheight = attstack[newp + 2].xval;
	} else {
	  r = 0.5 * (attstack[newp + 2].xval - WITH2->UU.Ubox.boxheight);
	  WITH2->UU.Ubox.boxheight = attstack[newp + 2].xval;
	}
	if (!teststflag(WITH->state, XLat)) {
	  switch (WITH2->direction) {

	  case XLleft:
	  case XLright:
	    /* blank case */
	    break;

	  case XLup:
	    shift(WITH->prim, 0.0, r);
	    break;

	  case XLdown:
	    shift(WITH->prim, 0.0, -r);
	    break;
	  }
	}
	break;

      case XLstring:
	WITH2->UU.Ubox.boxheight = attstack[newp + 2].xval;
	break;

      case XLcircle:
	if (!teststflag(WITH->state, XLat)) {
	  switch (WITH2->direction) {

	  case XLleft:
	  case XLright:
	    /* blank case */
	    break;

	  case XLup:
	    WITH2->aat.ypos += 0.5 * attstack[newp + 2].xval - WITH2->UU.Ucircle.radius;
	    break;

	  case XLdown:
	    WITH2->aat.ypos += WITH2->UU.Ucircle.radius - 0.5 * attstack[newp + 2].xval;
	    break;
	  }
	}
	WITH2->UU.Ucircle.radius = attstack[newp + 2].xval * 0.5;
	break;

      case XLellipse:
	if (!teststflag(WITH->state, XLat)) {
	  switch (WITH2->direction) {

	  case XLleft:
	  case XLright:
	    /* blank case */
	    break;

	  case XLup:
	    WITH2->aat.ypos +=
	      0.5 * (attstack[newp + 2].xval - WITH2->UU.Uellipse.elheight);
	    break;

	  case XLdown:
	    WITH2->aat.ypos +=
	      0.5 * (WITH2->UU.Uellipse.elheight - attstack[newp + 2].xval);
	    break;
	  }
	}
	WITH2->UU.Uellipse.elheight = attstack[newp + 2].xval;
	break;

      case XLline:
      case XLarrow:
      case XLmove:
      case XLarc:
      case XLspline:
	prp = WITH->prim;
	while (prp != NULL) {
	  prp->UU.Uline.height = attstack[newp + 2].xval;
	  if (isthen(prp))
	    prp = prp->parent;
	  else
	    prp = NULL;
	}
	break;

      case XLabel:
      case XLtroff:
	markerror(858);
	break;
      }
    }
    break;

  /*                          | object "width" expression    */
  case object3:
    if (WITH->prim != NULL) {
      WITH2 = WITH->prim;
      switch (WITH2->ptype) {

      case XLbox:
      case XBLOCK:
	if (WITH2->ptype == XBLOCK) {
	  r = 0.5 * (attstack[newp + 2].xval - WITH2->UU.UEMPTY7.blockwidth);
	  WITH2->UU.UEMPTY7.blockwidth = attstack[newp + 2].xval;
	} else {
	  r = 0.5 * (attstack[newp + 2].xval - WITH2->UU.Ubox.boxwidth);
	  WITH2->UU.Ubox.boxwidth = attstack[newp + 2].xval;
	}
	if (!teststflag(WITH->state, XLat)) {
	  switch (WITH2->direction) {

	  case XLup:
	  case XLdown:
	    /* blank case */
	    break;

	  case XLright:
	    shift(WITH->prim, r, 0.0);
	    break;

	  case XLleft:
	    shift(WITH->prim, -r, 0.0);
	    break;
	  }
	}
	break;

      case XLstring:
	WITH2->UU.Ubox.boxwidth = attstack[newp + 2].xval;
	break;

      case XLcircle:
	if (!teststflag(WITH->state, XLat)) {
	  switch (WITH2->direction) {

	  case XLup:
	  case XLdown:
	    /* blank case */
	    break;

	  case XLright:
	    WITH2->aat.xpos += 0.5 * attstack[newp + 2].xval - WITH2->UU.Ucircle.radius;
	    break;

	  case XLleft:
	    WITH2->aat.xpos += WITH2->UU.Ucircle.radius - 0.5 * attstack[newp + 2].xval;
	    break;
	  }
	}
	WITH2->UU.Ucircle.radius = attstack[newp + 2].xval * 0.5;
	break;

      case XLellipse:
	if (!teststflag(WITH->state, XLat)) {
	  switch (WITH2->direction) {

	  case XLup:
	  case XLdown:
	    /* blank case */
	    break;

	  case XLright:
	    WITH2->aat.xpos +=
	      0.5 * (attstack[newp + 2].xval - WITH2->UU.Uellipse.elwidth);
	    break;

	  case XLleft:
	    WITH2->aat.xpos +=
	      0.5 * (WITH2->UU.Uellipse.elwidth - attstack[newp + 2].xval);
	    break;
	  }
	}
	WITH2->UU.Uellipse.elwidth = attstack[newp + 2].xval;
	break;

      case XLline:
      case XLarrow:
      case XLmove:
      case XLarc:
      case XLspline:
	prp = WITH->prim;
	while (prp != NULL) {
	  prp->UU.Uline.width = attstack[newp + 2].xval;
	  if (isthen(prp))
	    prp = prp->parent;
	  else
	    prp = NULL;
	}
	break;

      case XLabel:
      case XLtroff:
	markerror(858);
	break;
      }
    }
    break;

  /*                          | object "radius" expression    */
  case object4:
    if (WITH->prim != NULL) {
      WITH2 = WITH->prim;
      switch (WITH2->ptype) {

      case XLbox:
	WITH2->UU.Ubox.boxradius = attstack[newp + 2].xval;
	break;

      case XLarc:
	t = attstack[newp + 2].xval;
	if (WITH2->direction == 0) {
	  attstack[newp + 2].xval = WITH2->aat.xpos + WITH2->UU.Uline.aradius *
		cos(WITH2->UU.Uline.endpos.xpos + WITH2->UU.Uline.endpos.ypos);
	  attstack[newp + 2].yval = WITH2->aat.ypos + WITH2->UU.Uline.aradius *
		sin(WITH2->UU.Uline.endpos.xpos + WITH2->UU.Uline.endpos.ypos);
	  /*D if debuglevel = 2 then writeln(log, 'to ',
	     attstack^[newp+2].xval:7:4, attstack^[newp+2].yval:7:4); D*/
	  redubuf[reduinx + REDUMAX].prod_ = object20;
	  reduinx--;
	}
	r = cos(WITH2->UU.Uline.endpos.xpos);
	s = sin(WITH2->UU.Uline.endpos.xpos);
	WITH2->aat.xpos += WITH2->UU.Uline.aradius * r;
	WITH2->aat.ypos += WITH2->UU.Uline.aradius * s;
	WITH2->UU.Uline.aradius = t;
	WITH2->aat.xpos -= WITH2->UU.Uline.aradius * r;
	WITH2->aat.ypos -= WITH2->UU.Uline.aradius * s;
	setstflag(&WITH->state, XLradius);
	break;

      case XLcircle:
	if (!teststflag(WITH->state, XLat)) {
	  switch (WITH2->direction) {

	  case XLleft:
	    WITH2->aat.xpos += WITH2->UU.Ucircle.radius - attstack[newp + 2].xval;
	    break;

	  case XLright:
	    WITH2->aat.xpos += attstack[newp + 2].xval - WITH2->UU.Ucircle.radius;
	    break;

	  case XLup:
	    WITH2->aat.ypos += attstack[newp + 2].xval - WITH2->UU.Ucircle.radius;
	    break;

	  case XLdown:
	    WITH2->aat.ypos += WITH2->UU.Ucircle.radius - attstack[newp + 2].xval;
	    break;
	  }
	}
	WITH2->UU.Ucircle.radius = attstack[newp + 2].xval;
	setstflag(&WITH->state, XLradius);
	break;

      default:
	markerror(858);
	break;
      }
    }
    break;

  /*                          | object "diameter" expression    */
  case object5:
    if (WITH->prim != NULL) {
      WITH2 = WITH->prim;
      if (WITH2->ptype == XLcircle) {
	r = 0.5 * attstack[newp + 2].xval;
	if (!teststflag(WITH->state, XLat)) {
	  switch (WITH2->direction) {

	  case XLleft:
	    WITH2->aat.xpos += WITH2->UU.Ucircle.radius - r;
	    break;

	  case XLright:
	    WITH2->aat.xpos += r - WITH2->UU.Ucircle.radius;
	    break;

	  case XLup:
	    WITH2->aat.ypos += r - WITH2->UU.Ucircle.radius;
	    break;

	  case XLdown:
	    WITH2->aat.ypos += WITH2->UU.Ucircle.radius - r;
	    break;
	  }
	}
	WITH2->UU.Ucircle.radius = r;
      } else
	markerror(858);
    }
    break;

  /*                          | object "thickness" expression    */
  case object6:
    if (WITH->prim != NULL) {
      if (attstack[newp + 2].xval < 0.0) {
	markerror(905);
	WITH->prim->lthick = -attstack[newp + 2].xval;
      } else
	WITH->prim->lthick = attstack[newp + 2].xval;
    }
    break;

  /*                          | object "scaled" expression    */
  case object7:
    if (WITH->prim != NULL && attstack[newp + 2].lexval != XEMPTY) {
      WITH2 = WITH->prim;
      r = attstack[newp + 2].xval - 1;
      corner(WITH->prim, XDc, &x1, &y1);
      switch (WITH2->ptype) {

      case XLbox:
      case XBLOCK:
      case XLstring:
	if (teststflag(WITH->state, XLat)) {
	  dx = 0.0;
	  dy = 0.0;
	} else if (WITH2->ptype == XBLOCK) {
	  dx = WITH2->UU.UEMPTY7.blockwidth * r / 2;
	  dy = WITH2->UU.UEMPTY7.blockheight * r / 2;
	} else {
	  dx = WITH2->UU.Ubox.boxwidth * r / 2;
	  dy = WITH2->UU.Ubox.boxheight * r / 2;
	}
	scaleobj(WITH->prim, attstack[newp + 2].xval);
	switch (WITH2->direction) {

	case XLright:
	  shift(WITH->prim, x1 - WITH2->aat.xpos + dx, y1 - WITH2->aat.ypos);
	  break;

	case XLleft:
	  shift(WITH->prim, x1 - WITH2->aat.xpos - dx, y1 - WITH2->aat.ypos);
	  break;

	case XLup:
	  shift(WITH->prim, x1 - WITH2->aat.xpos, y1 - WITH2->aat.ypos + dy);
	  break;

	case XLdown:
	  shift(WITH->prim, x1 - WITH2->aat.xpos, y1 - WITH2->aat.ypos - dy);
	  break;
	}
	break;

      case XLcircle:
	WITH2->UU.Ucircle.radius = attstack[newp + 2].xval * WITH2->UU.Ucircle.radius;
	if (!teststflag(WITH->state, XLat)) {
	  switch (WITH2->direction) {

	  case XLup:
	    WITH2->aat.xpos = x1;
	    WITH2->aat.ypos = y1 + WITH2->UU.Ucircle.radius;
	    break;

	  case XLdown:
	    WITH2->aat.xpos = x1;
	    WITH2->aat.ypos = y1 - WITH2->UU.Ucircle.radius;
	    break;

	  case XLright:
	    WITH2->aat.xpos = x1 + WITH2->UU.Ucircle.radius;
	    WITH2->aat.ypos = y1;
	    break;

	  case XLleft:
	    WITH2->aat.xpos = x1 - WITH2->UU.Ucircle.radius;
	    WITH2->aat.ypos = y1;
	    break;
	  }
	}
	break;

      case XLellipse:
	WITH2->UU.Uellipse.elwidth *= attstack[newp + 2].xval;
	WITH2->UU.Uellipse.elheight *= attstack[newp + 2].xval;
	if (!teststflag(WITH->state, XLat)) {
	  switch (WITH2->direction) {

	  case XLup:
	    WITH2->aat.xpos = x1;
	    WITH2->aat.ypos = y1 + WITH2->UU.Uellipse.elheight / 2;
	    break;

	  case XLdown:
	    WITH2->aat.xpos = x1;
	    WITH2->aat.ypos = y1 - WITH2->UU.Uellipse.elheight / 2;
	    break;

	  case XLright:
	    WITH2->aat.xpos = x1 + WITH2->UU.Uellipse.elwidth / 2;
	    WITH2->aat.ypos = y1;
	    break;

	  case XLleft:
	    WITH2->aat.xpos = x1 - WITH2->UU.Uellipse.elwidth / 2;
	    WITH2->aat.ypos = y1;
	    break;
	  }
	}
	break;

      case XLline:
      case XLarrow:
      case XLmove:
      case XLarc:
      case XLspline:
	scaleobj(WITH->prim, attstack[newp + 2].xval);
	corner(WITH->prim, XDc, &r, &s);
	shift(WITH->prim, x1 - r, y1 - s);
	break;

      case XLabel:
      case XLtroff:
	markerror(858);
	break;
      }
    }
    break;

  /*                          | object "<directon>" optexp */
  case object8:
    if (WITH->prim != NULL) {
      WITH2 = WITH->prim;
      if (WITH2->ptype == XLspline || WITH2->ptype == XLarrow ||
	  WITH2->ptype == XLmove || WITH2->ptype == XLline ||
	  WITH2->ptype == XLarc) {
	i = attstack[newp + 1].lexval;
	envblock->direction = i;
	eb = findenv(envblock);
	switch (WITH2->ptype) {

	case XLarc:
	  r = cos(WITH2->UU.Uline.endpos.xpos);
	  s = sin(WITH2->UU.Uline.endpos.xpos);
	  WITH2->aat.xpos += WITH2->UU.Uline.aradius * r;
	  WITH2->aat.ypos += WITH2->UU.Uline.aradius * s;
	  if (WITH2->direction == XLup && i == XLleft ||
	      WITH2->direction == XLdown && i == XLright ||
	      WITH2->direction == XLright && i == XLup ||
	      WITH2->direction == XLleft && i == XLdown)
	    WITH2->UU.Uline.endpos.ypos = pi * 0.5;
	  else if (WITH2->direction == XLup && i == XLright ||
		   WITH2->direction == XLdown && i == XLleft ||
		   WITH2->direction == XLright && i == XLdown ||
		   WITH2->direction == XLleft && i == XLup)
	    WITH2->UU.Uline.endpos.ypos = -pi * 0.5;
	  if (attstack[newp + 2].lexval != XEMPTY)
	    WITH2->UU.Uline.aradius = attstack[newp + 2].lexval;
	  WITH2->aat.xpos -= WITH2->UU.Uline.aradius * r;
	  WITH2->aat.ypos -= WITH2->UU.Uline.aradius * s;
	  WITH2->direction = i;
	  break;

	case XLline:
	case XLmove:
	case XLarrow:
	case XLspline:
	  WITH2->direction = i;
	  if (attstack[newp + 2].lexval != XEMPTY) {
	    r = attstack[newp + 2].xval;
	    s = r;
	  } else {
	    switch (WITH2->ptype) {

	    case XLline:
	    case XLarrow:
	    case XLspline:
	      r = eb->UU.UEMPTY7.env[XLlineht - XLenvvar - 1];
	      s = eb->UU.UEMPTY7.env[XLlinewid - XLenvvar - 1];
	      break;

	    case XLmove:
	      r = eb->UU.UEMPTY7.env[XLmoveht - XLenvvar - 1];
	      s = eb->UU.UEMPTY7.env[XLmovewid - XLenvvar - 1];
	      break;
	    }
	  }
	  lineardir(WITH->prim, r, s, &WITH->state);
	  break;
	}
      } else
	markerror(858);
    }
    break;

  /*                          | object "by" pair    */
  case object9:
    if (WITH->prim != NULL) {
      if (WITH->prim->ptype == XLmove || WITH->prim->ptype == XLspline ||
	  WITH->prim->ptype == XLarrow || WITH->prim->ptype == XLline ||
	  WITH->prim->ptype == XLarc) {
	WITH2 = WITH->prim;
	x1 = attstack[newp + 2].xval + WITH2->aat.xpos;
	y1 = attstack[newp + 2].yval + WITH2->aat.ypos;
	if (WITH2->ptype == XLarc) {
	  x1 += WITH2->UU.Uline.aradius * cos(WITH2->UU.Uline.endpos.xpos);
	  y1 += WITH2->UU.Uline.aradius * sin(WITH2->UU.Uline.endpos.xpos);
	}
	attstack[newp + 2].xval = x1;
	attstack[newp + 2].yval = y1;
	redubuf[reduinx + REDUMAX].prod_ = object20;
	reduinx--;
      } else
	markerror(858);
    }
    break;

  /*                          | object "then"    */
  case object10:
    if (WITH->prim != NULL) {
      /*D if debuglevel > 0 then begin writeln(log,'lexical "then" found, ');
          prtstval(state); writeln(log) end; D*/
      appendthen(&WITH->prim);
      if (WITH->prim->ptype != XLarc)
	setstflag(&WITH->state, XEMPTY);
    }
    break;

  /*                          | object "<linetype>" optexp    */
  case object11:
    if (WITH->prim != NULL) {
      if (attstack[newp + 1].lexval == XLpath && drawmode != PSTricks) {
	/* (not (drawmode in [PSTricks,PS,PSfrag,PSmps])) */
	markerror(858);
      } else {
	setspec(&WITH->prim->spec, attstack[newp + 1].lexval);
	/* if attstack^[newp+1].lexval = XLinvis then setvis(spec,0); */
	if (attstack[newp + 2].lexval != XEMPTY) {
	  if ((attstack[newp + 1].lexval == XLpath ||
	       attstack[newp + 1].lexval == XLsolid ||
	       attstack[newp + 1].lexval == XLinvis) &&
	      (WITH->prim->ptype == XLmove || WITH->prim->ptype == XLspline ||
	       WITH->prim->ptype == XLarrow || WITH->prim->ptype == XLline))
	    lineardir(WITH->prim, attstack[newp + 2].xval,
		      attstack[newp + 2].xval, &WITH->state);
	  else if (attstack[newp + 1].lexval == XLpath ||
		   attstack[newp + 1].lexval == XLsolid ||
		   attstack[newp + 1].lexval == XLinvis)
	    markerror(858);
	  else
	    WITH->prim->lparam = attstack[newp + 2].xval;
	}
      }
    }
    break;

  /*                          | object "chop" optexp    */
  case object12:
    if (WITH->prim != NULL) {
      if (WITH->prim->ptype != XLspline && WITH->prim->ptype != XLmove &&
	  WITH->prim->ptype != XLarrow && WITH->prim->ptype != XLline)
	markerror(858);
      else {
	WITH2 = WITH->prim;
	if (attstack[newp + 2].lexval != XEMPTY)
	  r = attstack[newp + 2].xval;
	else {
	  eb = findenv(envblock);
	  r = eb->UU.UEMPTY7.env[XLcirclerad - XLenvvar - 1];
	}
	if (teststflag(WITH->state, XLchop))
	  WITH->endchop = r;
	else {
	  WITH->startchop = r;
	  WITH->endchop = r;
	  setstflag(&WITH->state, XLchop);
	}
      }
    }
    break;

  /*                          | object "fill" optexp    */
  case object13:
    if (WITH->prim != NULL) {
      WITH2 = WITH->prim;
      if (attstack[newp + 2].lexval != XEMPTY)
	s = attstack[newp + 2].xval;
      else {
	eb = findenv(envblock);
	s = eb->UU.UEMPTY7.env[XLfillval - XLenvvar - 1];
      }
      prp = WITH->prim;
      while (prp != NULL) {
	switch (WITH2->ptype) {

	case XLbox:
	  prp->UU.Ubox.boxfill = s;
	  break;

	case XLcircle:
	  prp->UU.Ucircle.cfill = s;
	  break;

	case XLellipse:
	  prp->UU.Uellipse.efill = s;
	  break;

	default:   /*,PSmps*/
	  if (((1L << ((long)drawmode)) & ((1L << ((long)xfig)) |
		 (1L << ((long)PGF)) | (1L << ((long)PSfrag)) |
		 (1L << ((long)PSTricks)) | (1L << ((long)PS)))) == 0)
	    markerror(858);
	  else {
	    switch (WITH2->ptype) {

	    case XLline:
	    case XLarrow:
	    case XLmove:
	    case XLspline:
	    case XLarc:
	      prp->UU.Uline.lfill = s;
	      break;

	    default:
	      markerror(858);
	      break;
	    }
	  }
	  break;
	}
	if (isthen(prp))
	  prp = prp->parent;
	else
	  prp = NULL;
      }
    }
    break;

  /*                          | object "<arrowhd>"    */
  case object14:
    if (WITH->prim != NULL) {
      WITH2 = WITH->prim;
      if (WITH2->ptype != XLspline && WITH2->ptype != XLarc &&
	  WITH2->ptype != XLarrow && WITH2->ptype != XLline)
	markerror(858);
      else
	WITH2->UU.Uline.atype = attstack[newp + 1].lexval;
    }
    break;

  /*                          | object "cw"    */
  case object15:
    if (WITH->prim != NULL) {
      WITH2 = WITH->prim;
      if (WITH2->ptype != XLarc)
	markerror(858);
      else {
	/*D if debuglevel = 2 then begin
	    write(log,'direction=',direction:1,' |arcangle','|=');
	    wfloat(log,endpos.ypos*180/pi); writeln(log);
	    write(log,'principal(|arcangle','|,pi)=');
	    wfloat(log,(principal(endpos.ypos,pi))*180/pi); writeln(log);
	    write(log,'2.0 * pi - principal(|arcangle','|,pi)=');
	    wfloat(log,(2.0 * pi - principal(endpos.ypos,pi))*180/pi);
	    writeln(log) end; D*/
	/* if teststflag(state,XLat) then begin
	   if endpos.ypos>0.0 then endpos.ypos := endpos.ypos-2*pi
	   end
	else */
	if (WITH2->UU.Uline.endpos.ypos > 0.0 && WITH2->direction == 0)
	  WITH2->UU.Uline.endpos.ypos = -fabs(
	      principal(2.0 * pi - WITH2->UU.Uline.endpos.ypos, 2.0 * pi));
	else if (WITH2->direction != 0) {
	  WITH2->aat.xpos += WITH2->UU.Uline.aradius *
			     cos(WITH2->UU.Uline.endpos.xpos);
	  WITH2->aat.ypos += WITH2->UU.Uline.aradius *
			     sin(WITH2->UU.Uline.endpos.xpos);
	  switch (WITH2->direction) {

	  case XLup:
	    WITH2->aat.xpos += WITH2->UU.Uline.aradius;
	    break;

	  case XLdown:
	    WITH2->aat.xpos -= WITH2->UU.Uline.aradius;
	    break;

	  case XLleft:
	    WITH2->aat.ypos += WITH2->UU.Uline.aradius;
	    break;

	  case XLright:
	    WITH2->aat.ypos -= WITH2->UU.Uline.aradius;
	    break;
	  }
	  if (WITH2->UU.Uline.endpos.ypos > 0.0)
	    WITH2->UU.Uline.endpos.xpos = principal(
		WITH2->UU.Uline.endpos.xpos + pi, pi);
	  WITH2->UU.Uline.endpos.ypos = -fabs(WITH2->UU.Uline.endpos.ypos);
	}
	setstflag(&WITH->state, XLcw);
      }
    }
    break;

  /*                          | object "ccw"    */
  case object16:
    if (WITH->prim != NULL) {
      WITH2 = WITH->prim;
      if (WITH2->ptype != XLarc)
	markerror(858);
      else {
	/* if teststflag(state,XLat) then begin
	   if endpos.ypos<0.0 then endpos.ypos := 2*pi+endpos.ypos
	   end
	else */
	if (WITH2->UU.Uline.endpos.ypos < 0.0 && WITH2->direction == 0)
	  WITH2->UU.Uline.endpos.ypos = fabs(
	      principal(WITH2->UU.Uline.endpos.ypos - 2.0 * pi, 2.0 * pi));
	else if (WITH2->direction != 0) {
	  WITH2->aat.xpos += WITH2->UU.Uline.aradius *
			     cos(WITH2->UU.Uline.endpos.xpos);
	  WITH2->aat.ypos += WITH2->UU.Uline.aradius *
			     sin(WITH2->UU.Uline.endpos.xpos);
	  switch (WITH2->direction) {

	  case XLup:
	    WITH2->aat.xpos -= WITH2->UU.Uline.aradius;
	    break;

	  case XLdown:
	    WITH2->aat.xpos += WITH2->UU.Uline.aradius;
	    break;

	  case XLleft:
	    WITH2->aat.ypos -= WITH2->UU.Uline.aradius;
	    break;

	  case XLright:
	    WITH2->aat.ypos += WITH2->UU.Uline.aradius;
	    break;
	  }
	  if (WITH2->UU.Uline.endpos.ypos < 0.0)
	    WITH2->UU.Uline.endpos.xpos = principal(
		WITH2->UU.Uline.endpos.xpos + pi, pi);
	  WITH2->UU.Uline.endpos.ypos = fabs(WITH2->UU.Uline.endpos.ypos);
	}
	setstflag(&WITH->state, XLccw);
      }
    }
    break;

  /*                          | object "same"    */
  case object17:
    if (WITH->prim != NULL) {
      prp = nthprimobj(envblock->son, 0, WITH->prim->ptype);
      if (prp == NULL)
	markerror(857);
      else {
	WITH2 = WITH->prim;
	WITH2->lparam = prp->lparam;
	WITH2->lthick = prp->lthick;
	WITH2->direction = prp->direction;
	WITH2->spec = prp->spec;
	if (hasoutline(WITH->lexval, false))
	  copystr(&freeseg, &WITH2->outlinep, prp->outlinep);
	if (hasshade(WITH->lexval, false))
	  copystr(&freeseg, &WITH2->shadedp, prp->shadedp);
      }
      if (prp != NULL) {
	WITH2 = WITH->prim;
	switch (WITH2->ptype) {

	case XLbox:
	case XLstring:
	  if (WITH2->ptype == XLbox) {
	    switch (WITH2->direction) {

	    case XLup:
	      WITH2->aat.ypos +=
		0.5 * (prp->UU.Ubox.boxheight - WITH2->UU.Ubox.boxheight);
	      break;

	    case XLdown:
	      WITH2->aat.ypos -=
		0.5 * (prp->UU.Ubox.boxheight - WITH2->UU.Ubox.boxheight);
	      break;

	    case XLleft:
	      WITH2->aat.xpos -=
		0.5 * (prp->UU.Ubox.boxwidth - WITH2->UU.Ubox.boxwidth);
	      break;

	    case XLright:
	      WITH2->aat.xpos +=
		0.5 * (prp->UU.Ubox.boxwidth - WITH2->UU.Ubox.boxwidth);
	      break;
	    }
	  }
	  WITH2->UU.Ubox.boxfill = prp->UU.Ubox.boxfill;
	  WITH2->UU.Ubox.boxheight = prp->UU.Ubox.boxheight;
	  WITH2->UU.Ubox.boxwidth = prp->UU.Ubox.boxwidth;
	  WITH2->UU.Ubox.boxradius = prp->UU.Ubox.boxradius;
	  break;

	case XBLOCK:
	  markerror(858);
	  break;

	case XLcircle:
	  switch (WITH2->direction) {

	  case XLup:
	    WITH2->aat.ypos += prp->UU.Ucircle.radius - WITH2->UU.Ucircle.radius;
	    break;

	  case XLdown:
	    WITH2->aat.ypos += WITH2->UU.Ucircle.radius - prp->UU.Ucircle.radius;
	    break;

	  case XLleft:
	    WITH2->aat.xpos += WITH2->UU.Ucircle.radius - prp->UU.Ucircle.radius;
	    break;

	  case XLright:
	    WITH2->aat.xpos += prp->UU.Ucircle.radius - WITH2->UU.Ucircle.radius;
	    break;
	  }
	  WITH2->UU.Ucircle.cfill = prp->UU.Ucircle.cfill;
	  WITH2->UU.Ucircle.radius = prp->UU.Ucircle.radius;
	  break;

	case XLellipse:
	  switch (WITH2->direction) {

	  case XLup:
	    WITH2->aat.ypos +=
	      0.5 * (prp->UU.Uellipse.elheight - WITH2->UU.Uellipse.elheight);
	    break;

	  case XLdown:
	    WITH2->aat.ypos -=
	      0.5 * (prp->UU.Uellipse.elheight - WITH2->UU.Uellipse.elheight);
	    break;

	  case XLleft:
	    WITH2->aat.xpos -= 0.5 * (prp->UU.Uellipse.elwidth - WITH2->UU.Uellipse.elwidth);
	    break;

	  case XLright:
	    WITH2->aat.xpos += 0.5 * (prp->UU.Uellipse.elwidth - WITH2->UU.Uellipse.elwidth);
	    break;
	  }
	  WITH2->UU.Uellipse.efill = prp->UU.Uellipse.efill;
	  WITH2->UU.Uellipse.elheight = prp->UU.Uellipse.elheight;
	  WITH2->UU.Uellipse.elwidth = prp->UU.Uellipse.elwidth;
	  break;

	case XLarc:
	  x1 = WITH2->aat.xpos +
	       WITH2->UU.Uline.aradius * cos(WITH2->UU.Uline.endpos.xpos);
	  y1 = WITH2->aat.ypos +
	       WITH2->UU.Uline.aradius * sin(WITH2->UU.Uline.endpos.xpos);
	  WITH2->UU.Uline.aradius = prp->UU.Uline.aradius;
	  WITH2->UU.Uline.endpos.xpos = prp->UU.Uline.endpos.xpos;
	  WITH2->aat.xpos =
	    x1 - WITH2->UU.Uline.aradius * cos(WITH2->UU.Uline.endpos.xpos);
	  WITH2->aat.ypos =
	    y1 - WITH2->UU.Uline.aradius * sin(WITH2->UU.Uline.endpos.xpos);
	  WITH2->UU.Uline.endpos.ypos = prp->UU.Uline.endpos.ypos;
	  break;

	case XLline:
	case XLarrow:
	case XLmove:
	case XLspline:
	  WITH2->UU.Uline.endpos.xpos =
	    WITH2->aat.xpos + prp->UU.Uline.endpos.xpos - prp->aat.xpos;
	  WITH2->UU.Uline.endpos.ypos =
	    WITH2->aat.ypos + prp->UU.Uline.endpos.ypos - prp->aat.ypos;
	  WITH2->UU.Uline.height = prp->UU.Uline.height;
	  WITH2->UU.Uline.width = prp->UU.Uline.width;
	  WITH2->UU.Uline.atype = prp->UU.Uline.atype;
	  break;

	case XLabel:
	case XLtroff:
	  markerror(858);
	  break;
	}
      }
    }
    break;

  /*                            | object stringexpr */
  case object18:
    if (attstack[newp + 1].prim != NULL) {
      if (WITH->prim != NULL) {
	WITH2 = WITH->prim;
	if (WITH2->textp == NULL)
	  WITH2->textp = attstack[newp + 1].prim->textp;
	else {
	  namptr = WITH2->textp;
	  i = 1;
	  while (namptr->next_ != NULL) {
	    namptr = namptr->next_;
	    i++;
	  }
	  namptr->next_ = attstack[newp + 1].prim->textp;
	  if (WITH2->ptype == XLstring)
	    WITH2->UU.Ubox.boxheight = WITH2->UU.Ubox.boxheight * (i + 1) / i;
	}
	if (((1L << ((long)drawmode)) &
	     ((1L << ((long)PS)) | (1L << ((long)PSfrag)))) != 0)
	      /*,PSmps*/
		printstate = (printstate >> 1) * 2 + 1;
      }
      attstack[newp + 1].prim->textp = NULL;
      deletestringbox(&attstack[newp + 1].prim);
    }
    break;

  /*                            | object "from" position       */
  case object19:
    if (WITH->prim != NULL) {
      WITH2 = WITH->prim;
      if (WITH2->ptype == XLmove || WITH2->ptype == XLspline ||
	  WITH2->ptype == XLarrow ||
	  WITH2->ptype == XLline || WITH2->ptype == XLarc) {
	if (WITH2->ptype == XLarc) {
	  r = attstack[newp + 2].xval;
	  s = attstack[newp + 2].yval;
	  if (teststflag(WITH->state, XLto)) {
	    attstack[newp + 2].xval = WITH2->aat.xpos +
		WITH2->UU.Uline.aradius *
		cos(WITH2->UU.Uline.endpos.xpos + WITH2->UU.Uline.endpos.ypos);
	    attstack[newp + 2].yval = WITH2->aat.ypos +
		WITH2->UU.Uline.aradius *
		sin(WITH2->UU.Uline.endpos.xpos + WITH2->UU.Uline.endpos.ypos);
	    redubuf[reduinx + REDUMAX].prod_ = object20;
	    reduinx--;
	  }
	  WITH2->aat.xpos =
	    r - WITH2->UU.Uline.aradius * cos(WITH2->UU.Uline.endpos.xpos);
	  WITH2->aat.ypos =
	    s - WITH2->UU.Uline.aradius * sin(WITH2->UU.Uline.endpos.xpos);
	} else if (!teststflag(WITH->state, XLto)) {
	  prp = WITH->prim;
	  while (isthen(prp))
	    prp = prp->parent;
	  shift(prp, attstack[newp + 2].xval - prp->aat.xpos,
		attstack[newp + 2].yval - prp->aat.ypos);
	} else {
	  WITH2->aat.xpos = attstack[newp + 2].xval;
	  WITH2->aat.ypos = attstack[newp + 2].yval;
	}
	setstflag(&WITH->state, XLfrom);
      } else
	markerror(858);
    }
    break;

  /*                            | object "to" position         */
  case object20:
    if (WITH->prim != NULL) {
      if (WITH->prim->ptype == XLmove || WITH->prim->ptype == XLspline ||
	  WITH->prim->ptype == XLarrow || WITH->prim->ptype == XLline ||
	  WITH->prim->ptype == XLarc) {
	if ((WITH->prim->ptype != XLarc) & teststflag(WITH->state, XLto)) {
	  /*D if debuglevel > 0 then begin writeln(log,'"then" inserted, ');
	      prtstval(state); writeln(log) end; D*/
	  appendthen(&WITH->prim);
	  setstflag(&WITH->state, XEMPTY);
	}
	WITH2 = WITH->prim;
	if (WITH2->ptype != XLarc) {
	  WITH2->UU.Uline.endpos.xpos = attstack[newp + 2].xval;
	  WITH2->UU.Uline.endpos.ypos = attstack[newp + 2].yval;
	} else {
	  x1 = WITH2->aat.xpos +
	       WITH2->UU.Uline.aradius * cos(WITH2->UU.Uline.endpos.xpos);
	      /* from position */
	  y1 = WITH2->aat.ypos +
	       WITH2->UU.Uline.aradius * sin(WITH2->UU.Uline.endpos.xpos);
	  dx = attstack[newp + 2].xval - x1;
	  dy = attstack[newp + 2].yval - y1;
	  ts = dx * dx + dy * dy;   /* chord^2 */
	  if (WITH2->direction != 0)
	    i = WITH2->direction;
	  else
	    i = WITH->length;
	  /*D if debuglevel = 2 then begin
	     write(log,' (x1,y1)='); wpair(log,x1,y1);
	     write(log,' (dx,dy)='); wpair(log,dx,dy);
	     write(log,' ts='); wfloat(log,ts);
	     write(log,' i=',i:1 ) end; D*/
	  if (ts == 0.0)
	    WITH2->UU.Uline.endpos.ypos = 0.0;
	  else {  /* ratio centre-to-chord/half-chord */
	    t = sqrt(Max(0.0, 4.0 * WITH2->UU.Uline.aradius * WITH2->
				UU.Uline.aradius - ts) / ts);
	    /*D if debuglevel = 2 then begin
	       write(log,' t='); wfloat(log,t);
	       write(log,' |arcangle','|='); wfloat(log,endpos.ypos*180/pi);
	       writeln(log) end; D*/
	    r = sqrt(ts);
	    if (t <= 0.0)   /* t is always nonnegative  */
	      WITH2->UU.Uline.aradius = 0.5 * r;
	    switch (i) {
		/* Determine which of the two default arcs to draw: */

	    case XLup:
	      if (WITH2->UU.Uline.endpos.ypos * (-dx - t * dy) < 0.0)
		t = -t;
	      break;

	    case XLdown:
	      if (WITH2->UU.Uline.endpos.ypos * (-dx - t * dy) > 0.0)
		t = -t;
	      break;

	    case XLright:
	      if (WITH2->UU.Uline.endpos.ypos * (dy - t * dx) < 0.0)
		t = -t;
	      break;

	    case XLleft:
	      if (WITH2->UU.Uline.endpos.ypos * (dy - t * dx) > 0.0)
		t = -t;
	      break;
	    }
	    WITH2->aat.xpos = x1 + 0.5 * (dx + t * dy);
	    WITH2->aat.ypos = y1 + 0.5 * (dy - t * dx);
	    /*D if debuglevel = 2 then begin
	       write(log,' t='); wfloat(log,t);
	       write(log,' aradius='); wfloat(log,aradius);
	       write(log,' aat='); wpair(log,aat.xpos,aat.ypos);
	       writeln(log) end; D*/
	    setangles(&WITH2->UU.Uline.endpos.xpos,
		      &WITH2->UU.Uline.endpos.ypos, WITH2->aat, x1, y1,
		      attstack[newp + 2].xval, attstack[newp + 2].yval);
	  }
	  if (WITH2->direction != 0)
	    WITH->length = WITH2->direction;
	  WITH2->direction = 0;
	}
	/*D ; if debuglevel > 0 then printobject(prim) D*/
	setstflag(&WITH->state, XLto);
      } else
	markerror(858);
    }
    break;

  /*                          | object "at" position    */
  case object21:
    if (WITH->prim != NULL) {
      WITH2 = WITH->prim;
      WITH->root = NULL;
      WITH->xval = attstack[newp + 2].xval;
      WITH->yval = attstack[newp + 2].yval;
      setstval(&WITH->state, XDc);
      setstflag(&WITH->state, XLat);
    }
    break;

  /*                          | object "<textpos>"    */
  /* This might be altered (in the case of strings, not other objects with text),
       so that aat is changed as a function of textpos.  Then
       the output routines have to take that into account.   The alternative
       is to alter nesw for strings, as now. */
  case object22:
    if (WITH->prim != NULL) {
      namptr = WITH->prim->textp;
      if (namptr != NULL) {
	while (namptr->next_ != NULL)
	  namptr = namptr->next_;
	i = (long)floor(namptr->val + 0.5);
	if (i > 8)
	  i = 0;
	switch (attstack[newp + 1].lexval) {

	case XLcenter:
	  namptr->val = 15.0;
	  break;

	case XLrjust:
	  namptr->val = i / 4.0 * 4 + 1;
	  break;

	case XLljust:
	  namptr->val = i / 4.0 * 4 + 2;
	  break;

	case XLbelow:
	  namptr->val = (i & 3) + 4.0;
	  break;

	case XLabove:
	  namptr->val = (i & 3) + 8.0;
	  break;
	}
      } else
	markerror(861);
    }
    break;

  /*                          | object ("colour"|"outline"|"shade") stringexpr */
  case object23:
    if (((1L << ((long)drawmode)) &
	 ((1L << ((long)MPost)) | (1L << ((long)PGF)) | (1L << ((long)PS)) |
	  (1L << ((long)PSfrag)) | (1L << ((long)PSTricks)))) == 0)
	  /*,PSmps*/
	    markerror(858);
    else if (attstack[newp + 2].prim != NULL && WITH->prim != NULL) {
      WITH2 = WITH->prim;
      switch (attstack[newp + 1].lexval) {

      case XLshaded:
	if (hasshade(WITH->lexval, true)) {
	  deletename(&WITH2->shadedp);
	  WITH2->shadedp = attstack[newp + 2].prim->textp;
	  attstack[newp + 2].prim->textp = NULL;
	}
	break;

      case XLoutlined:
      case XLcolour:
	if (hasoutline(WITH->lexval, true)) {
	  deletename(&WITH2->outlinep);
	  WITH2->outlinep = attstack[newp + 2].prim->textp;
	  attstack[newp + 2].prim->textp = NULL;
	  if (attstack[newp + 1].lexval == XLcolour) {
	    if (hasshade(WITH->lexval, false)) {
	      deletename(&WITH2->shadedp);
	      copystr(&freeseg, &WITH2->shadedp, WITH2->outlinep);
	    }
	  }
	}
	break;
      }
    }
    deletestringbox(&attstack[newp + 2].prim);
    break;

  /*                          | withobj "<corner>" "at" position    */
  /*                          | withobj "start" "at" position    */
  /*                          | withobj "end" "at" position    */
  /*                          | withobj pair "at" position    */
  case object24:
  case object25:
  case object26:
  case object27:
    if (WITH->prim != NULL) {
      if (WITH->root != NULL) {
	prp = WITH->prim;
	WITH->prim = WITH->root;
	WITH->root = prp;
      }
      WITH->xval = attstack[newp + 3].xval;
      WITH->yval = attstack[newp + 3].yval;
      if (p != object27)
	setstval(&WITH->state, attstack[newp + 1].lexval);
      else if (WITH->prim->ptype != XLarc && WITH->prim->ptype != XLellipse &&
	       WITH->prim->ptype != XLcircle && WITH->prim->ptype != XBLOCK &&
	       WITH->prim->ptype != XLstring && WITH->prim->ptype != XLbox)
	markerror(858);
      else {
	WITH->startchop = attstack[newp + 1].xval;
	WITH->endchop = attstack[newp + 1].yval;
	setstval(&WITH->state, XLfloat);
      }
      setstflag(&WITH->state, XLat);
    }
    break;

  /*                         | withobj "." "<Label>" suffix "at" position*/
  case object28:
    if (WITH->prim != NULL) {
      if (attstack[newp + 3].lexval != XEMPTY) {
	WITH1 = &attstack[newp + 2];
	addsuffix(chbuf, &WITH1->chbufx, &WITH1->length,
		  attstack[newp + 3].xval);
      }
      primp = findplace(WITH->prim->son, chbuf, attstack[newp + 2].chbufx,
			attstack[newp + 2].length);
      if (WITH->root != NULL) {
	WITH->prim = WITH->root;
	WITH->root = NULL;
      }
      if (primp == NULL)
	marknotfound(chbuf, attstack[newp + 2].chbufx,
		     attstack[newp + 2].length);
      else {
	WITH->root = primp;
	WITH->xval = attstack[newp + 5].xval;
	WITH->yval = attstack[newp + 5].yval;
	setstval(&WITH->state, XEMPTY);
	setstflag(&WITH->state, XLat);
      }
    }
    break;

  /*                         | "continue" */
  case object29:
    primp = NULL;
    prp = envblock->son;
    while (prp != NULL) {
      if (prp->ptype != XLtroff && prp->ptype != XLstring &&
	  prp->ptype != XBLOCK && prp->ptype != XLabel)
	primp = prp;
      prp = prp->next_;
    }
    if (primp == NULL)
      markerror(857);
    else {
      while (primp->son != NULL)
	primp = primp->son;
      WITH->prim = primp;
      redubuf[reduinx + REDUMAX].prod_ = object10;
      reduinx--;
    }
    break;

  /*117   openblock = "<EMPTY>"   */
  case openblock1:
    /*D if debuglevel > 0 then writeln(log,
       'Calling newprim(prim,',XBLOCK:1,'):'); D*/
    newprim(&WITH->prim, XBLOCK, envblock);
    WITH6 = &WITH->prim->UU.UEMPTY7.here;
    /* prim^.here := envblock^.here; */
    /* Bah! gpic compatibility: */
    WITH6->xpos = 0.0;
    WITH6->ypos = 0.0;
    envblock = WITH->prim;
    WITH->lexval = 0;
    /* ; resetenv(0,envblock) */
    /*D; if (debuglevel > 0) and (prim <> nil) then printobject(prim)D*/
    break;

  /*118   block = "<primitiv>" optexp   */
  /*119         | stringexpr   */
  /*120         | openblock "[" closeblock "]"   */
  /*121         | openblock "[]"   */
  case block1:
    if (WITH->lexval > XLprimitiv && WITH->lexval < XLenvvar) {
      newprim(&WITH->prim, WITH->lexval, envblock);
      eb = findenv(envblock);
      if (((1L << ((long)drawmode)) &
	   ((1L << ((long)MPost)) | (1L << ((long)pict2e)) |
	    (1L << ((long)PS)) | (1L << ((long)PSfrag)))) != 0 &&
	  WITH->lexval != XLmove)
	    /*,PSmps*/
	      WITH->prim->lthick = eb->UU.UEMPTY7.env[XLlinethick - XLenvvar - 1];
      if (attstack[newp + 1].lexval != XEMPTY && WITH->lexval != XLmove &&
	  WITH->lexval != XLspline &&
	  WITH->lexval != XLarrow && WITH->lexval != XLline)
	markerror(858);
      WITH2 = WITH->prim;
      switch (WITH->lexval) {

      case XLbox:
	WITH2->UU.Ubox.boxheight = eb->UU.UEMPTY7.env[XLboxht - XLenvvar - 1];
	WITH2->UU.Ubox.boxwidth = eb->UU.UEMPTY7.env[XLboxwid - XLenvvar - 1];
	WITH2->UU.Ubox.boxradius = eb->UU.UEMPTY7.env[XLboxrad - XLenvvar - 1];
	switch (WITH2->direction) {

	case XLup:
	  WITH2->aat.ypos += WITH2->UU.Ubox.boxheight * 0.5;
	  break;

	case XLdown:
	  WITH2->aat.ypos -= WITH2->UU.Ubox.boxheight * 0.5;
	  break;

	case XLleft:
	  WITH2->aat.xpos -= WITH2->UU.Ubox.boxwidth * 0.5;
	  break;

	case XLright:
	  WITH2->aat.xpos += WITH2->UU.Ubox.boxwidth * 0.5;
	  break;
	}
	break;

      case XLcircle:
	WITH2->UU.Ucircle.radius = eb->UU.UEMPTY7.env[XLcirclerad - XLenvvar - 1];
	switch (WITH2->direction) {

	case XLup:
	  WITH2->aat.ypos += WITH2->UU.Ucircle.radius;
	  break;

	case XLdown:
	  WITH2->aat.ypos -= WITH2->UU.Ucircle.radius;
	  break;

	case XLleft:
	  WITH2->aat.xpos -= WITH2->UU.Ucircle.radius;
	  break;

	case XLright:
	  WITH2->aat.xpos += WITH2->UU.Ucircle.radius;
	  break;
	}
	break;

      case XLellipse:
	WITH2->UU.Uellipse.elheight = eb->UU.UEMPTY7.env[XLellipseht - XLenvvar - 1];
	WITH2->UU.Uellipse.elwidth = eb->UU.UEMPTY7.env[XLellipsewid - XLenvvar - 1];
	switch (WITH2->direction) {

	case XLup:
	  WITH2->aat.ypos += WITH2->UU.Uellipse.elheight * 0.5;
	  break;

	case XLdown:
	  WITH2->aat.ypos -= WITH2->UU.Uellipse.elheight * 0.5;
	  break;

	case XLleft:
	  WITH2->aat.xpos -= WITH2->UU.Uellipse.elwidth * 0.5;
	  break;

	case XLright:
	  WITH2->aat.xpos += WITH2->UU.Uellipse.elwidth * 0.5;
	  break;
	}
	break;

      case XLarc:
	WITH2->UU.Uline.aradius = eb->UU.UEMPTY7.env[XLarcrad - XLenvvar - 1];
	switch (WITH2->direction) {

	case XLup:
	  WITH2->UU.Uline.endpos.xpos = 0.0;
	  WITH2->aat.xpos -= WITH2->UU.Uline.aradius;
	  break;

	case XLdown:
	  WITH2->UU.Uline.endpos.xpos = pi;
	  WITH2->aat.xpos += WITH2->UU.Uline.aradius;
	  break;

	case XLleft:
	  WITH2->UU.Uline.endpos.xpos = 0.5 * pi;
	  WITH2->aat.ypos -= WITH2->UU.Uline.aradius;
	  break;

	case XLright:
	  WITH2->UU.Uline.endpos.xpos = -0.5 * pi;
	  WITH2->aat.ypos += WITH2->UU.Uline.aradius;
	  break;
	}
	WITH2->UU.Uline.height = eb->UU.UEMPTY7.env[XLarrowht - XLenvvar - 1];
	WITH2->UU.Uline.width = eb->UU.UEMPTY7.env[XLarrowwid - XLenvvar - 1];
	WITH2->UU.Uline.atype = XEMPTY;
	WITH2->UU.Uline.endpos.ypos = pi * 0.5;
	break;

      case XLline:
      case XLarrow:
      case XLspline:
      case XLmove:
	WITH2->UU.Uline.endpos = WITH2->aat;
	if (WITH2->ptype == XLspline && attstack[newp + 1].lexval != XEMPTY) {
	  /* This implements adjusted splines */
	  WITH2->UU.Uline.aradius = attstack[newp + 1].xval;
	  attstack[newp + 1].lexval = XEMPTY;
	}  /* */
	if (attstack[newp + 1].lexval != XEMPTY)
	  r = attstack[newp + 1].xval;
	else if (WITH2->ptype == XLmove) {
	  switch (WITH2->direction) {

	  case XLup:
	  case XLdown:
	    r = eb->UU.UEMPTY7.env[XLmoveht - XLenvvar - 1];
	    break;

	  case XLleft:
	  case XLright:
	    r = eb->UU.UEMPTY7.env[XLmovewid - XLenvvar - 1];
	    break;
	  }
	} else {
	  switch (WITH2->direction) {

	  case XLup:
	  case XLdown:
	    r = eb->UU.UEMPTY7.env[XLlineht - XLenvvar - 1];
	    break;

	  case XLleft:
	  case XLright:
	    r = eb->UU.UEMPTY7.env[XLlinewid - XLenvvar - 1];
	    break;
	  }
	}
	switch (WITH2->direction) {

	case XLup:
	  WITH2->UU.Uline.endpos.ypos = WITH2->aat.ypos + r;
	  break;

	case XLdown:
	  WITH2->UU.Uline.endpos.ypos = WITH2->aat.ypos - r;
	  break;

	case XLleft:
	  WITH2->UU.Uline.endpos.xpos = WITH2->aat.xpos - r;
	  break;

	case XLright:
	  WITH2->UU.Uline.endpos.xpos = WITH2->aat.xpos + r;
	  break;
	}
	WITH2->UU.Uline.height = eb->UU.UEMPTY7.env[XLarrowht - XLenvvar - 1];
	WITH2->UU.Uline.width = eb->UU.UEMPTY7.env[XLarrowwid - XLenvvar - 1];
	if (WITH2->ptype == XLarrow)
	  WITH2->UU.Uline.atype = XRIGHTHEAD;
	else
	  WITH2->UU.Uline.atype = XEMPTY;
	break;
      }
    }
    break;

  /*                          | stringexpr */
  case block2:
    if (((1L << ((long)drawmode)) &
	 ((1L << ((long)PS)) | (1L << ((long)PSfrag)))) != 0)
	  /*,PSmps*/
	    printstate = (printstate >> 1) * 2 + 1;
    break;

  /*                          | openblock "[" closeblock "]" */
  case block3:
    if (WITH->prim != NULL) {
      WITH->prim->son = attstack[newp + 2].prim;
      envblock = WITH->prim->parent;
      getnesw(WITH->prim->son);
      WITH2 = WITH->prim;
      WITH2->UU.UEMPTY7.blockwidth = east - west;
      WITH2->UU.UEMPTY7.blockheight = north - south;
      WITH2->aat.xpos = (east + west) * 0.5;
      WITH2->aat.ypos = (north + south) * 0.5;
      dx = envblock->UU.UEMPTY7.here.xpos - WITH2->aat.xpos;
      dy = envblock->UU.UEMPTY7.here.ypos - WITH2->aat.ypos;
      switch (envblock->direction) {

      case XLright:
	dx += WITH2->UU.UEMPTY7.blockwidth * 0.5;
	break;

      case XLleft:
	dx -= WITH2->UU.UEMPTY7.blockwidth * 0.5;
	break;

      case XLup:
	dy += WITH2->UU.UEMPTY7.blockheight * 0.5;
	break;

      case XLdown:
	dy -= WITH2->UU.UEMPTY7.blockheight * 0.5;
	break;
      }
      WITH2->direction = envblock->direction;   /* gpic compatibility */
      /*D if (debuglevel > 0) and (prim^.son <> nil) then with prim^ do begin
             printobject(son);
             if son^.next <> nil then printobject(son^.next)
             end; D*/
      /*D;if debuglevel > 0 then with prim^ do begin
         write(log, 'Object3: (north,south),(west,east)');
         wpair(log,aat.ypos+blockheight*0.5,aat.ypos-blockheight*0.5);
         wpair(log,aat.xpos-blockwidth*0.5,aat.xpos+blockwidth*0.5);
         write(log, ' here=');
         wpair(log,here.xpos,here.ypos); writeln(log);
         if prim^.son<>nil then begin
            printobject(prim^.son);
            if prim^.son^.next <> nil then printobject(prim^.son^.next)
            end
         end;
      if debuglevel > 0 then begin snaptree(prim,0); writeln(log) endD*/
      shift(WITH->prim, dx, dy);
    }
    break;

  /*                          | openblock "[]" */
  case block4:
    if (WITH->prim != NULL)
      envblock = WITH->prim->parent;
    break;

  /*122   optexp = "<EMPTY>"   */
  /*123          | expression   */
  case optexp1:
    WITH->lexval = XEMPTY;
    break;

  case optexp2:
    break;

  /*124   closeblock = elementlist optnl   */
  /*    Add troff to reset env variables changed within a block */
  case closeblock1:
    if (WITH->prim != NULL && envblock->UU.UEMPTY7.env != NULL) {
      eb = findenv(envblock->parent);
      if (eb != NULL) {  /* check and reset variables: */
	if (envblock->UU.UEMPTY7.env[XLlinethick - XLenvvar - 1] !=
	    eb->UU.UEMPTY7.env[XLlinethick - XLenvvar - 1]) {
	  newprim(&attstack[newp + 2].prim, XLtroff, envblock);
	  attstack[newp + 2].prim->lthick =
	    eb->UU.UEMPTY7.env[XLlinethick - XLenvvar - 1];
	  addelem(attstack[newp + WITH->state].prim, attstack[newp + 2].prim);
	}
	if (envblock->UU.UEMPTY7.env[XLdashwid - XLenvvar - 1] !=
	    eb->UU.UEMPTY7.env[XLdashwid - XLenvvar - 1]) {
	  newprim(&attstack[newp + 2].prim, XLtroff, envblock);
	  attstack[newp + 2].prim->lparam = eb->UU.UEMPTY7.env[XLdashwid - XLenvvar - 1];
	  addelem(attstack[newp + WITH->state].prim, attstack[newp + 2].prim);
	}
      }
    }
    break;

  /*125   pair = expression "," expression   */
  /*126        | location shift   */
  case pair1:
    WITH->yval = attstack[newp + 2].xval;
    break;

  case pair2:
    if (attstack[newp + 1].lexval != XEMPTY) {
      WITH->xval += attstack[newp + 1].xval;
      WITH->yval += attstack[newp + 1].yval;
    }
    break;

  /*127   withobj = object "with"   */
  /*128           | withobj "." "<Label>" suffix   */
  case withobj1:
    break;

  case withobj2:
    if (WITH->prim != NULL) {
      if (attstack[newp + 3].lexval != XEMPTY) {
	WITH1 = &attstack[newp + 2];
	addsuffix(chbuf, &WITH1->chbufx, &WITH1->length,
		  attstack[newp + 3].xval);
      }
      primp = findplace(WITH->prim->son, chbuf, attstack[newp + 2].chbufx,
			attstack[newp + 2].length);
      if (primp == NULL) {
	marknotfound(chbuf, attstack[newp + 2].chbufx,
		     attstack[newp + 2].length);
	WITH->prim = NULL;
      } else {
	if (WITH->root == NULL)
	  WITH->root = WITH->prim;
	WITH->prim = primp;
      }
    }
    break;

  /*129   shift = "<EMPTY>"   */
  /*130         | shift "+" location   */
  /*131         | shift "-" location   */
  case shift1:
    WITH->xval = 0.0;
    WITH->yval = 0.0;
    WITH->lexval = XEMPTY;
    break;

  case shift2:
    WITH->xval += attstack[newp + 2].xval;
    WITH->yval += attstack[newp + 2].yval;
    WITH->lexval = XLfloat;
    break;

  case shift3:
    WITH->xval -= attstack[newp + 2].xval;
    WITH->yval -= attstack[newp + 2].yval;
    WITH->lexval = XLfloat;
    break;

  /*132   location = "(" position ")"   */
  /*133            | "(" position "," position ")"   */
  /*134            | place   */
  /*135            | location "*" factor   */
  /*136            | location "/" factor   */
  case location1:
    attstack[newp] = attstack[newp + 1];
    break;

  case location2:
    WITH->xval = attstack[newp + 1].xval;
    WITH->yval = attstack[newp + 3].yval;
    break;

  case location3:
    /* blank case */
    break;

  case location4:
    WITH->xval *= attstack[newp + 2].xval;
    WITH->yval *= attstack[newp + 2].xval;
    break;

  case location5:
    if (attstack[newp + 2].xval == 0.0)
      markerror(852);
    else {
      WITH->xval /= attstack[newp + 2].xval;
      WITH->yval /= attstack[newp + 2].xval;
    }
    break;

  /*137   place = placename   */
  /*138         | placename "<corner>"   */
  /*139         | "<corner>" placename   */
  /*140         | "<corner>" "of" placename   */
  /*141         | "Here"   */
  case place1:
    corner(WITH->prim, XEMPTY, &WITH->xval, &WITH->yval);
    break;

  case place2:
    corner(WITH->prim, attstack[newp + 1].lexval, &WITH->xval, &WITH->yval);
    break;

  case place3:
    corner(attstack[newp + 1].prim, WITH->lexval, &WITH->xval, &WITH->yval);
    break;

  case place4:
    corner(attstack[newp + 2].prim, WITH->lexval, &WITH->xval, &WITH->yval);
    break;

  case place5:
    WITH->xval = envblock->UU.UEMPTY7.here.xpos;
    WITH->yval = envblock->UU.UEMPTY7.here.ypos;
    break;

  /*142   factor = primary   */
  /*143          | "!" primary   */
  /*144          | primary "^" factor   */
  case factor1:
    break;

  case factor2:
    if (attstack[newp + 1].xval == 0.0)
      WITH->xval = 1.0;
    else
      WITH->xval = 0.0;
    break;

  case factor3:
    if (WITH->xval == 0.0 && attstack[newp + 2].xval < 0.0)
      markerror(852);
    else {
      j = (long)floor(attstack[newp + 2].xval + 0.5);
      r = j;
      if (r == attstack[newp + 2].xval)
	WITH->xval = intpow(WITH->xval, j);
      else if (WITH->xval < 0.0) {
	markerror(863);
	WITH->xval = 0.0;
      } else if (WITH->xval != 0.0)
	WITH->xval = exp(attstack[newp + 2].xval * log(WITH->xval));
    }
    break;

  /*145   placename = "<Label>" suffix   */
  /*146             | nth primobj   */
  /*147             | placename "." "<Label>" suffix   */
  /*148             | placename "." nth primobj   */
  case placename1:
    if (attstack[newp + 1].lexval != XEMPTY)
      addsuffix(chbuf, &WITH->chbufx, &WITH->length, attstack[newp + 1].xval);
    prp = NULL;
    primp = envblock;
    while (primp != prp) {
      prp = findplace(primp->son, chbuf, WITH->chbufx, WITH->length);
      if (prp != NULL)
	primp = prp;
      else
	primp = primp->parent;
    }
    if (prp == NULL) {
      markerror(854);
      fprintf(stderr_, "\nSearch failure for \"");
      FORLIM = WITH->length;
      for (i = 0; i < FORLIM; i++)
	putc(chbuf[WITH->chbufx + i], stderr_);
      fprintf(stderr_, "\"\n");
    }
    /*D if (debuglevel > 0) and (prp<>nil) then with prp^ do
       writeln(log,
       'placename: type ', ptype:7,', ',aat.xpos:7:4,aat.ypos:7:4); D*/
    WITH->prim = prp;
    break;

  /*            | nth primobj                   */
  case placename2:
    WITH->prim = nthprimobj(envblock->son, WITH->length,
			    attstack[newp + 1].lexval);
    if (WITH->prim == NULL)
      markerror(857);
    break;

  /*            | placename "." "<Label>" suffix  */
  case placename3:
    if (WITH->prim != NULL) {
      if (attstack[newp + 3].lexval != XEMPTY) {
	WITH1 = &attstack[newp + 2];
	addsuffix(chbuf, &WITH1->chbufx, &WITH1->length,
		  attstack[newp + 3].xval);
      }
      /*D if debuglevel > 0 then begin
         write(log,'Searching:'); printobject(prim);
         with attstack^[newp+2] do snapname(chbuf,chbufx,length);
         writeln(log) end; D*/
      primp = findplace(WITH->prim->son, chbuf, attstack[newp + 2].chbufx,
			attstack[newp + 2].length);
      if (primp == NULL) {
	/*Delse if debuglevel > 0 then begin
	   write(log,'placename:'); printobject(primp) endD*/
	marknotfound(chbuf, attstack[newp + 2].chbufx,
		     attstack[newp + 2].length);
      }
      WITH->prim = primp;
    }
    break;

  /*            | placename "." nth primobj      */
  case placename4:
    if (WITH->prim != NULL) {
      WITH->prim = nthprimobj(WITH->prim->son, attstack[newp + 2].length,
			      attstack[newp + 3].lexval);
      if (WITH->prim == NULL)
	markerror(857);
    }
    break;

  /*149   nth = ncount "th"   */
  /*150       | ncount "th" "last"   */
  /*151       | "last"   */
  case nth1:
    if (WITH->xval <= 0.0)
      markerror(856);
    else
      WITH->length = (long)floor(WITH->xval + 0.5);
    break;

  case nth2:
    if (WITH->xval <= 0.0)
      markerror(856);
    else
      WITH->length = -(long)floor(WITH->xval + 0.5);
    break;

  case nth3:
    WITH->length = 0;
    break;

  /*152   primobj = "<primitiv>"   */
  /*153           | "[]"   */
  /*154           | "<string>"   */
  /*155           | "[" "]"   */
  case primobj1:
  case primobj2:
  case primobj3:
    break;

  case primobj4:
    WITH->lexval = XBLOCK;
    break;

  /*156   ncount = "<float>"   */
  /*157          | "`" expression "'"   */
  /*158          | "lbrace" expression "rbrace"   */
  case ncount1:
    break;

  case ncount2:
  case ncount3:
    WITH->xval = attstack[newp + 1].xval;
    break;

  /*159   logprod = logval   */
  /*160           | logprod "&&" logval   */
  case logprod1:
    break;

  case logprod2:
    if (WITH->xval == 0.0 || attstack[newp + 2].xval == 0.0)
      WITH->xval = 0.0;
    else
      WITH->xval = 1.0;
    break;

  /*161   logval = expression   */
  /*162          | logval "<compare>" expression   */
  /*             "==" "!=" ">=" "<=" "<<" ">>"     */
  case logval1:
    break;

  /* D if debuglevel > 0 then writeln(log,'logval=',xval) D */
  case logval2:
    switch (attstack[newp + 1].lexval - XLlogic) {

    case 1:
      truth = (WITH->xval == attstack[newp + 2].xval);
      break;

    case 2:
      truth = (WITH->xval != attstack[newp + 2].xval);
      break;

    case 3:
      truth = (WITH->xval >= attstack[newp + 2].xval);
      break;

    case 4:
      truth = (WITH->xval <= attstack[newp + 2].xval);
      break;

    case 5:
      truth = (WITH->xval < attstack[newp + 2].xval);
      break;

    case 6:
      truth = (WITH->xval > attstack[newp + 2].xval);
      break;
    }
    if (truth)
      WITH->xval = 1.0;
    else {
      WITH->xval = 0.0;
      /* D; if debuglevel > 0 then writeln(log,'logval truth=',xval) D */
    }
    break;

  /*163   primary = "<envvar>"   */
  /*164           | "<name>" suffix   */
  /*165           | "<float>"   */
  /*166           | "(" logexpr ")"   */
  /*167           | location ".x"   */
  /*168           | location ".y"   */
  /*169           | placename "<param>"   */
  /*170           | "rand" "(" ")"   */
  /*171           | "rand" "(" expression ")"   */
  /*172           | "<func1>" "(" expression ")"   */
  /*173           | "<func2>" "(" expression "," expression ")"   */
  /*174           | "(" stringexpr "<compare>" stringexpr ")"   */
  /*175           | "(" assignlist ")"   */
  /*176           | "(" expression ">" expression ")"   */
  /*177           | "(" expression "<" expression ")"   */
  case primary1:
    if (envblock != NULL) {
      eb = findenv(envblock);
      WITH->xval = eb->UU.UEMPTY7.env[WITH->lexval - XLenvvar - 1];
    }
    break;

  /*                           | "<name>" suffix    */
  case primary2:
    if (attstack[newp + 1].lexval != XEMPTY)
      addsuffix(chbuf, &WITH->chbufx, &WITH->length, attstack[newp + 1].xval);
    namptr = glfindname(envblock, chbuf, WITH->chbufx, WITH->length, &lastn);
    if (namptr == NULL)
      WITH->xval = 0.0;
    else
      WITH->xval = namptr->val;
    break;

  /*                           | "<float>"    */
  case primary3:
    break;

  /*                           | "(" logexpr ")"    */
  case primary4:
    WITH->xval = attstack[newp + 1].xval;
    break;

  case primary5:   /*   | place ".x"  */
    break;

  case primary6:   /*   | place ".y"  */
    WITH->xval = WITH->yval;
    break;

  /*                                        | placename "<param>"  */
  case primary7:
    if (WITH->prim != NULL) {
      switch (attstack[newp + 1].lexval) {

      case XLheight:
	WITH->xval = pheight(WITH->prim);
	break;

      case XLwidth:
	WITH->xval = pwidth(WITH->prim);
	break;

      case XLradius:
      case XLdiameter:
	WITH2 = WITH->prim;
	if (WITH2->ptype == XLcircle)
	  WITH->xval = WITH2->UU.Ucircle.radius;
	else if (WITH2->ptype == XLarc)
	  WITH->xval = WITH2->UU.Uline.aradius;
	else
	  markerror(858);
	if (attstack[newp + 1].lexval == XLdiameter)
	  WITH->xval *= 2.0;
	break;
      }
    }
    break;

  /*                  | "rand" "(" ")"  random number between 0 and 1 */
  case primary8:
    WITH->xval = (double)random() / LONG_MAX;
    break;

  /*                  | "rand" "(" expression ")"  */
  case primary9:
    srandom((long)floor(attstack[newp + 2].xval + 0.5));
    WITH->xval = (double)random() / LONG_MAX;
    break;

  /*                  | "<func1>" "(" expression ")"  */
  case primary10:
    switch (WITH->lexval) {

    case XLabs:
      WITH->xval = fabs(attstack[newp + 2].xval);
      break;

    case XLacos:
      t = attstack[newp + 2].xval;
      if (fabs(t) > 1.0)
	markerror(868);
      WITH->xval = datan(sqrt(1 - t * t), t);
      break;

    case XLasin:
      t = attstack[newp + 2].xval;
      if (fabs(t) > 1.0)
	markerror(868);
      WITH->xval = datan(t, sqrt(1 - t * t));
      break;

    case XLcos:
      WITH->xval = cos(attstack[newp + 2].xval);
      break;

    case XLexp:
      WITH->xval = exp(log(10.0) * attstack[newp + 2].xval);
      break;

    case XLexpe:
      WITH->xval = exp(attstack[newp + 2].xval);
      break;

    case XLint:
      WITH->xval = (long)attstack[newp + 2].xval;
      break;

    case XLlog:
      if (attstack[newp + 2].xval <= 0.0) {
	markerror(867);
	WITH->xval = 0.0;
      } else
	WITH->xval = log(attstack[newp + 2].xval) / log(10.0);
      break;

    case XLloge:
      if (attstack[newp + 2].xval <= 0.0) {
	markerror(867);
	WITH->xval = 0.0;
      } else
	WITH->xval = log(attstack[newp + 2].xval);
      break;

    case XLsign:
      if (attstack[newp + 2].xval >= 0.0)
	WITH->xval = 1.0;
      else
	WITH->xval = -1.0;
      break;

    case XLsin:
      WITH->xval = sin(attstack[newp + 2].xval);
      break;

    case XLsqrt:
      if (attstack[newp + 2].xval < 0.0) {
	markerror(867);
	WITH->xval = 0.0;
      } else
	WITH->xval = sqrt(attstack[newp + 2].xval);
      break;

    case XLtan:
      t = cos(attstack[newp + 2].xval);
      if (t == 0.0) {
	markerror(868);
	WITH->xval = distmax;
      } else
	WITH->xval = sin(attstack[newp + 2].xval) / t;
      break;

    case XLfloor:
      WITH->xval = Floor(attstack[newp + 2].xval);
      break;
    }
    break;

  /*                  | "<func2>" "(" expression "," expression ")"  */
  case primary11:
    switch (WITH->lexval) {

    case XLatan2:
      WITH->xval = datan(attstack[newp + 2].xval, attstack[newp + 4].xval);
      break;

    case XLmax:
      WITH->xval = Max(attstack[newp + 2].xval, attstack[newp + 4].xval);
      break;

    case XLmin:
      WITH->xval = Min(attstack[newp + 2].xval, attstack[newp + 4].xval);
      break;

    case XLpmod:
      j = labs((long)floor(attstack[newp + 4].xval + 0.5));
      i = (long)floor(attstack[newp + 2].xval + 0.5) % j;
/* p2c: dpic.p, line 3730:
 * Note: Using % for possibly-negative arguments [317] */
      if (i >= 0)
	WITH->xval = i;
      else
	WITH->xval = i + j;
      break;
    }
    break;

  /*                  | "(" stringexpr "<compare>" stringexpr ")"  */
  /*                    "==" "!=" ">=" "<=" "<<" ">>"       */
  case primary12:
    i = cmpstring(attstack[newp + 1].prim, attstack[newp + 3].prim);
    switch (attstack[newp + 2].lexval - XLlogic) {

    case 1:
      truth = (i == 0);
      break;

    case 2:
      truth = (i != 0);
      break;

    case 3:
      truth = (i >= 0);
      break;

    case 4:
      truth = (i <= 0);
      break;

    case 5:
      truth = (i < 0);
      break;

    case 6:
      truth = (i > 0);
      break;

    default:
      truth = false;
      break;
    }
    if (truth)
      WITH->xval = 1.0;
    else
      WITH->xval = 0.0;
    deletestringbox(&attstack[newp + 3].prim);
    deletestringbox(&attstack[newp + 1].prim);
    break;

  /*                 | "(" assignlist ")"    */
  case primary13:
    WITH->xval = attstack[newp + 1].xval;
    break;

  /*              | "(" expression ">" expression ")"   */
  case primary14:
    if (attstack[newp + 1].xval > attstack[newp + 3].xval)
      WITH->xval = 1.0;
    else
      WITH->xval = 0.0;
    break;

  /*              | "(" expression "<" expression ")"   */
  case primary15:
    if (attstack[newp + 1].xval < attstack[newp + 3].xval)
      WITH->xval = 1.0;
    else {
      WITH->xval = 0.0;

    }
    break;
  }/* case */

  /*D; if debuglevel > 0 then printobject(prim); D*/
}


/*B.B*/
/* onefile */
/* G end.G */
/* onefile */
/*GH#include 'dpic1.p'HG*/

/* onefile */

/*--------------------------------------------------------------------*/

/* X
procedure openerror;
begin
   rewrite(stderr,'NAME=/dev/tty')
   end;
procedure openfiles;
begin
   infile := substr(parms,1,length(parms)-1);
   reset(input,'NAME='||infile);
   reset(dpictabl,'NAME=DPICTABL')
   end;
X */

/*DUGHM
procedure openlogfile;
begin
   rewrite(log,'log');
   writeln(log,'Dpic log file')
   end; MHGUD*/


int checkfile(Char *ifn, boolean isverbose)
{
  int cf, i, j;

  j = FILENAMELEN;
  i = 0;
  while (j > i) {
    if (ifn[j - 1] == ' ')
      j--;
    else
      i = j;
  }
  if (j < FILENAMELEN)
    j++;
  else
    fatal(1);
  ifn[j - 1] = '\0';
  cf = access(ifn, 4);
  /*G  cf := 4-Access(ifn,4); G*/
  if (!(isverbose && cf != 0))
    return cf;
  fprintf(stderr_, " *** dpic: Searching for file \"");
  for (i = 0; i <= j - 2; i++)
    putc(ifn[i], stderr_);
  fprintf(stderr_, "\" returns %d\n", cf);
  return cf;
}


void openerror(void)
{
  if (isatty(2)) stderr_ = stderr;
  else stderr_ = stdout;
}


void openfiles(void)
{
  /*DUGHM if (oflag>0) then openlogfile; MHGUD*/
  savebuf = NULL;
  output = stdout; input = stdin;

  if (argct >= P_argc)
    return;

  P_sun_argv(infile, sizeof(mstring), argct);
  /*GH if argct <= ParamCount then begin
     infile := ParamStr(argct); HG*/

  if (checkfile(infile, true) != 0)
    fatal(1);
  if (input != NULL)
    input = freopen(P_trimname(infile, sizeof(mstring)), "r", input);
  else
    input = fopen(P_trimname(infile, sizeof(mstring)), "r");
  if (input == NULL)
    _EscIO(FileNotFound);
}


/*B
procedure openerror;
begin
 rewrite(stderr)
 end;
procedure openfiles;
begin
 B*/
/*DBrewrite(log);BD*/
/*B
   reset(dpictabl)
   end;
B*/

/*--------------------------------------------------------------------*/
/*D procedure wrbuf D*/
/* p: fbufferp; job,r: integer */
/*D;
var i,j: integer;
begin
  if p=nil then write(log,' nil buffer ')
  else with p^ do begin
     if job > 2 then begin
        write(log,' buf[');
        if p^.prevb<>nil then write(log,ordp(p^.prevb):1);
        write(log,'<'); write(log,ordp(p):1,'>');
        if p^.nextb<>nil then write(log,ordp(p^.nextb):1);
        write(log,']')
        end;
     if job > 1 then write(log,' readx=',readx:1,' savedlen=',savedlen:1);
     if r = 0 then j := 1 else if r < 0 then j := -r else j := readx;
     if job > 0 then write(log,'(',j:1,',',savedlen:1,')');
     write(log,'|');
     if carray = nil then write(log,'nil')
     else for i:=j to savedlen do write(log,carray^[i]);
     writeln(log,'|')
     end
  end; D*/
/*--------------------------------------------------------------------*/

void writeerror(void)
{
  int inx, startlin, emi, symb_, j, FORLIM, FORLIM1;

  if (errmp <= 0)
    return;
  /*D if debuglevel > 0 then begin write(log,'writeerror[');
      if inbuf=nil then write(log,'nil') else write(log,ordp(inbuf):1);
      writeln(log,']') end; D*/
  /* Write current line              */
  currentline(&startlin);
  /* Put the error numbers below it  */
  emi = startlin + 1;
  FORLIM = errmp;
  for (inx = 1; inx <= FORLIM; inx++) {
    FORLIM1 = errmsg[inx].col;
    for (j = emi; j < FORLIM1; j++)
      putc(' ', stderr_);
    fprintf(stderr_, "%d", inx);
    emi = errmsg[inx].col + 1;
  }
  putc('\n', stderr_);
  consoleflush();
  FORLIM = errmp;
  /* Error message for each error    */
  for (inx = 1; inx <= FORLIM; inx++) {
    emi = errmsg[inx].no;
    fprintf(stderr_, "dpic: line %d ", lineno);
    if (emi < 900)
      fprintf(stderr_, "ERROR");
    else
      fprintf(stderr_, "WARNING");
    fprintf(stderr_, " %d: ", inx);
    if (emi < 800) {
      symb_ = errmsg[inx].symb_;
      if (symb_ == XLname)
	fprintf(stderr_, "Name");
      else if (symb_ == XLabel)
	fprintf(stderr_, "Label");
      else if (symb_ == XLstring)
	fprintf(stderr_, "String");
      else if (symb_ == XLtroff)
	fprintf(stderr_, "Troff");
      else if (symb_ == XLfloat)
	fprintf(stderr_, "Float");
      else if (symb_ == XERROR)
	fprintf(stderr_, "Error");
      else if (symb_ >= XLenvvar)
	fprintf(stderr_, "Environment keyword");
      else if (symb_ >= XLprimitiv)
	fprintf(stderr_, "Draw object");
      else if (symb_ >= XLdirecton)
	fprintf(stderr_, "Direction word");
      else if (symb_ >= XLarrowhd)
	fprintf(stderr_, "Arrowhead keyword");
      else if (symb_ >= XLtextpos)
	fprintf(stderr_, "Text position keyword");
      else if (symb_ >= XLcolrspec)
	fprintf(stderr_, "Color keyword");
      else if (symb_ >= XLlinetype)
	fprintf(stderr_, "Line draw-type keyword");
      else if (symb_ >= XLfunc1)
	fprintf(stderr_, "Function keyword");
      else if (symb_ >= XLparam)
	fprintf(stderr_, "Size parameter keyword");
      else if (symb_ >= XLcorner)
	fprintf(stderr_, "Object feature keyword");
      else if (symb_ > XLKWDS)
	fprintf(stderr_, "Reserved word");
      else
	fprintf(stderr_, "Punctuation characters");
      fprintf(stderr_, " found, the following were expected:\n");
    }

    switch (emi) {

    /* Expected lexical symbols        */
    /* include parserr.i */
    case 1:
      fprintf(stderr_, " <EOF> .PS\n");
      break;

    case 2:
      fprintf(stderr_,
	" + - ! <envvar> <name> <float> ( rand <func1> <func2> <Label> <corner> Here last ` {\n");
      break;

    case 3:
      fprintf(stderr_, " th\n");
      break;

    case 4:
      fprintf(stderr_, " of <Label> last <float> ` {\n");
      break;

    case 5:
      fprintf(stderr_, " <primitiv> [] <string> [\n");
      break;

    case 6:
      fprintf(stderr_, " ]\n");
      break;

    case 7:
      fprintf(stderr_, " (\n");
      break;

    case 8:
      fprintf(stderr_,
	" ) + - ! <envvar> <name> <float> ( rand <func1> <func2> <Label> <corner> Here last ` {\n");
      break;

    case 9:
      fprintf(stderr_, " <Label> last <float> ` {\n");
      break;

    case 10:
      fprintf(stderr_, " .x .y * /\n");
      break;

    case 11:
      fprintf(stderr_,
	" ! <envvar> <name> <float> ( rand <func1> <func2> <Label> <corner> Here last ` {\n");
      break;

    case 12:
      fprintf(stderr_,
	" + - <string> <name> <envvar> sprintf ! ( <float> rand <func1> <func2> <corner> Here <Label> last ` {\n");
      break;

    case 13:
      fprintf(stderr_,
	" <envvar> <name> <float> ( rand <func1> <func2> <Label> <corner> Here last ` {\n");
      break;

    case 14:
      fprintf(stderr_, " <string>\n");
      break;

    case 15:
      fprintf(stderr_, " ( <corner> Here <Label> last <float> ` {\n");
      break;

    case 16:
      fprintf(stderr_, " between of < , + -\n");
      break;

    case 17:
      fprintf(stderr_, " ,\n");
      break;

    case 18:
      fprintf(stderr_, " >\n");
      break;

    case 19:
      fprintf(stderr_, " the\n");
      break;

    case 20:
      fprintf(stderr_, " way\n");
      break;

    case 21:
      fprintf(stderr_, " between\n");
      break;

    case 22:
      fprintf(stderr_, " and\n");
      break;

    case 23:
      fprintf(stderr_, " ) ,\n");
      break;

    case 24:
      fprintf(stderr_, " )\n");
      break;

    case 25:
      fprintf(stderr_, " ) + - between of < ,\n");
      break;

    case 26:
      fprintf(stderr_, " ) + -\n");
      break;

    case 27:
      fprintf(stderr_, " <name> <envvar>\n");
      break;

    case 28:
      fprintf(stderr_, " =\n");
      break;

    case 29:
      fprintf(stderr_, " <compare> +\n");
      break;

    case 30:
      fprintf(stderr_, " <string> sprintf\n");
      break;

    case 31:
      fprintf(stderr_, " ) +\n");
      break;

    case 32:
      fprintf(stderr_, " ) ||\n");
      break;

    case 33:
      fprintf(stderr_, " , + -\n");
      break;

    case 34:
      fprintf(stderr_, " ] + -\n");
      break;

    case 35:
      fprintf(stderr_, " ' + -\n");
      break;

    case 36:
      fprintf(stderr_, " } + -\n");
      break;

    case 37:
      fprintf(stderr_, " <NL> <ERROR>\n");
      break;

    case 38:
      fprintf(stderr_, " [ []\n");
      break;

    case 39:
      fprintf(stderr_, " to ,\n");
      break;

    case 40:
      fprintf(stderr_, " + - do by\n");
      break;

    case 41:
      fprintf(stderr_, " do + -\n");
      break;

    case 42:
      fprintf(stderr_, " if\n");
      break;

    case 43:
      fprintf(stderr_, " then ||\n");
      break;

    case 44:
      fprintf(stderr_, " <name> <Label>\n");
      break;

    case 45:
      fprintf(stderr_,
	" <corner> start end . + - ( Here ! <Label> <envvar> <name> <float> rand <func1> <func2> last ` {\n");
      break;

    case 46:
      fprintf(stderr_, " <Label>\n");
      break;

    case 47:
      fprintf(stderr_, " at\n");
      break;

    case 48:
      fprintf(stderr_, " at of <Label> last <float> ` {\n");
      break;

    case 49:
      fprintf(stderr_, " {\n");
      break;

    case 50:
      fprintf(stderr_, " }\n");
      break;

    case 51:
      fprintf(stderr_, " <envvar>\n");
      break;

    case 52:
      fprintf(stderr_, " } <NL>\n");
      break;

    case 53:
      fprintf(stderr_, " <NL>\n");
      break;

    case 54:
      fprintf(stderr_, " .PE <NL> <ERROR>\n");
      break;
      /*B%include parserrB*/

    /* lexical error messages */
    case 800:
      fprintf(stderr_, "Character not recognized: ignored\n");
      break;

    case 801:
      fprintf(stderr_, "Null string not allowed\n");
      break;

    case 802:
      fprintf(stderr_, "Invalid exponent character after e in a number\n");
      break;

    case 803:
      fprintf(stderr_,
	      "Fill value must be non-negative and not greater than 1\n");
      break;

    case 804:
      fprintf(stderr_, "End of file while reading {...} contents\n");
      break;

    case 805:
      fprintf(stderr_, "Bad macro argument number\n");
      break;

    case 806:
      fprintf(stderr_, "End of file while evaluating macro argument\n");
      break;

    /* context error messages */
    case 851:
      fprintf(stderr_, "Variable not found\n");
      break;

    case 852:
      fprintf(stderr_, "Zero divisor not allowed\n");
      break;

    case 853:
      fprintf(stderr_, "Only one copy file may be open at any time\n");
      break;

    case 854:
      fprintf(stderr_, "Place name not found\n");
      break;

    case 855:
      fprintf(stderr_, "Internal name not found\n");
      break;

    case 856:
      fprintf(stderr_, "Invalid non-positive value for object count\n");
      break;

    case 857:
      fprintf(stderr_, "Enumerated or previous object not found\n");
      break;

    case 858:
      fprintf(stderr_, "This usage is inapplicable in this context\n");
      break;

    case 859:
      fprintf(stderr_, "File not readable\n");
      break;

    case 860:
      fprintf(stderr_, "Infinite looping not allowed\n");
      break;

    case 861:
      fprintf(stderr_, "Missing string\n");
      break;

    case 862:
      fprintf(stderr_,
	      "For variables must have the same sign and positive ratio\n");
      break;

    case 863:
      fprintf(stderr_, "Non-integer power of negative value\n");
      break;

    case 864:
      fprintf(stderr_, "Incorrect number of sprintf arguments\n");
      break;

    case 865:
      fprintf(stderr_, "Bad sprintf format\n");
      break;

    case 866:
      fprintf(stderr_, "String exceeds max length of 4095 characters\n");
      break;

    case 867:
      fprintf(stderr_, "Invalid log or sqrt argument\n");
      break;

    case 868:
      fprintf(stderr_, "Function argument out of bounds\n");
      break;

    /* lexical warning messages */
    case 901:
      fprintf(stderr_, "String character generated at end of line\n");
      break;

    case 902:
      fprintf(stderr_, "Input line exceeds buffer size of 4096 characters\n");
      break;

    case 903:
      fprintf(stderr_, "Picture size adjusted to maxpswid value\n");
      break;

    case 904:
      fprintf(stderr_, "Picture size adjusted to maxpsht value\n");
      break;

    case 905:
      fprintf(stderr_, "Illegal negative dimension, abs value used\n");
      break;

    case 906:
      fprintf(stderr_, "Dpic in safe mode: sh and copy not allowed\n");
      break;
    }/* case */

    putc('\n', stderr_);
    consoleflush();
  }  /* for */
  if (errcount > MAXERRCOUNT)
    fatal(3);
  errmp = 0;
}  /*writeerror */


/*--------------------------------------------------------------------*/

void stackattribute(stackinx stackp)
{
  /* This is the interface routine to store terminal attributes in the
     attribute stack */
  attribute *WITH;

  WITH = &attstack[stackp];
  /* D if debuglevel = 2 then writeln(log,
     'stackp=',stackp:1,' lexsymb=',lexsymb:1 ); D */
  WITH->chbufx = oldbufi;
  WITH->length = chbufi - oldbufi;
  WITH->prim = NULL;
  WITH->root = NULL;
  WITH->varname = NULL;
  WITH->xval = floatvalue;
  WITH->yval = 0.0;
  WITH->startchop = 0.0;
  WITH->endchop = WITH->startchop;
  WITH->state = 0;
  WITH->lexval = lexsymb;
}  /* stackattribute */


void markerror(int n)
{
  /* n: integer */
  _REC_errmsg *WITH;

  errcount++;
  /*D if debuglevel > 0 then begin
     write(log, '*** Markerror');
     if inbuf<>nil then write(log,'[',ordp(inbuf):1,']');
     writeln(log, ': no=', n:1, ', lexsymb=', lexsymb:1 ) end; D*/
  if (errmp >= ERRMAX)
    return;
  errmp++;
  WITH = &errmsg[errmp];
  WITH->no = n;
  if (inbuf != NULL)
    WITH->col = inbuf->readx - 1;
  else
    WITH->col = 0;
  /* symb := newsymb */
  WITH->symb_ = lexsymb;
}  /*markerror*/


void initrandom(void)
{
  /* initialize random number routine */
time_t seed;

  /*GH var t: TimeStamp; HG*/
  srandom(time(&seed));
  /*GH GetTimeStamp(t);
      srandom(t.Microsecond) HG*/
}


/*--------------------------------------------------------------------*/

/* procedures for input/output of characters */

void exitmacro(void)
{
  arg *ar, *lastarg;

  /*D if debuglevel > 0 then writeln(log,'exitmacro'); D*/
  ar = args;
  if (args != NULL)   /* first get rid of args */
    args = args->higherb;
  while (ar != NULL) {   /*D,1D*/
    disposebufs(&ar->argbody);
    lastarg = ar;
    ar = ar->nextb;
    Free(lastarg);
  }
}


void newbuf(fbuffer **buf)
{
  /* var buf: fbufferp */
  fbuffer *WITH;

  /*D if debuglevel > 0 then write(log,'newbuf'); D*/
  if (freebuf == NULL) {
    *buf = Malloc(sizeof(fbuffer));
    (*buf)->carray = Malloc(sizeof(chbufarray));
  } else {
    *buf = freebuf;
    freebuf = freebuf->nextb;
  }
  WITH = *buf;
  WITH->savedlen = 0;
  WITH->readx = 1;
  WITH->attrib = 0;
  WITH->higherb = NULL;
  WITH->prevb = NULL;
  WITH->nextb = NULL;
  /*D;if debuglevel > 0 then writeln(log,'[',ordp(buf):1,']'); D*/
}


void newarg(arg **arg_)
{
  /* var arg: argp */
  arg *WITH;

  /*D if debuglevel > 0 then write(log,'newarg'); D*/
  *arg_ = Malloc(sizeof(arg));
  WITH = *arg_;
  WITH->argbody = NULL;
  WITH->higherb = NULL;
  WITH->nextb = NULL;
  /*D;if debuglevel > 0 then writeln(log,'[',ordp(arg):1,']'); D*/
}


fbuffer *newinbuf(fbuffer *p)
{
  if (errmp > 0)
    writeerror();
  return p;
}


void disposebufs(fbuffer **buf)
{
  /* var buf: fbufferp; loc: integer */
  fbuffer *bu;

  if (*buf == NULL)
    return;
  /*D if debuglevel > 0 then
      writeln(log,'disposebufs(',loc:1,')[',ordp(buf):1,']'); D*/
  if (freebuf != NULL) {
    bu = *buf;
    while (bu->nextb != NULL)
      bu = bu->nextb;
    bu->nextb = freebuf;
  }
  freebuf = *buf;
  *buf = NULL;
}


void readline(FILE **infile)
{
  int ll,c;
  if (feof( *infile )) { inputeof = true; return; }
  for (ll = CHBUFSIZ-2; inbuf->savedlen < ll; ) {
     c = getc( *infile );
     if ((char)c == '\n') ll = inbuf->savedlen;
     else if ((char)c == '\r') { ll = inbuf->savedlen;
        if ((char)(c=getc( *infile )) != '\n') ungetc(c, *infile ); }
     else if (c != EOF) {
        inbuf->savedlen++; inbuf->carray[inbuf->savedlen] = (char)c; }
     else if (inbuf->savedlen == 0) { inputeof = true; return; }
     else ll = inbuf->savedlen;
  }
  if ((ll == CHBUFSIZ-2) && ((char)(c=getc( *infile )) != '\n')
     && ((char)c != '\r') && (c != EOF)){
     markerror(902);
     fscanf( *infile, "%*[^\n\r]"); getc( *infile );
  }
  inbuf->savedlen++; inbuf->carray[inbuf->savedlen] = '\n';
  inbuf->savedlen++; inbuf->carray[inbuf->savedlen] = ' ';

  /*D; if debuglevel = 2 then begin write(log,'readline');
     if inputeof then writeln(log,' inputeof') else wrbuf(inbuf,3,0) end D*/
}


void nextline(void)
{
  /* Write out error messages, and read in a line.  */
  int i;
  fbuffer *WITH;
  int FORLIM;

  writeerror();
  WITH = inbuf;
  WITH->readx = 1;
  WITH->savedlen = 0;
  do {
    lineno++;
    if (savebuf != NULL) {
      readline(&copyin);
      if (inputeof) {
	inputeof = false;
	while (inbuf->prevb != NULL)   /*D,11D*/
	  inbuf = newinbuf(inbuf->prevb);
	disposebufs(&inbuf);
	inbuf = savebuf;
	savebuf = NULL;
      }
    } else
      readline(&input);

    WITH = inbuf;

    if (WITH->carray[1] == '.') {
      if (inpic != 2) {
	if (WITH->savedlen >= 4 && WITH->carray[2] == 'P') {
	  if (savebuf != NULL)
	    WITH->savedlen = 0;   /* skip .P* lines */
	  else if (WITH->carray[3] == 'F' || WITH->carray[3] == 'S') {
	    inpic = 1;
	    WITH->readx = 4;
	  } else if (WITH->carray[3] == 'E') {
	    inpic = 3;
	    WITH->readx = 3;
	  }
	}
      } else if (WITH->savedlen < 4 || WITH->carray[2] != 'P' ||
		 savebuf != NULL)
	WITH->savedlen = 0;   /* skip .P* lines in copied files */
      else if (WITH->carray[3] == 'F' || WITH->carray[3] == 'S') {
	inpic = 1;
	WITH->readx = 4;
      } else if (WITH->carray[3] == 'E') {
	inpic = 3;
	WITH->readx = 3;
      } else
	WITH->savedlen = 0;
    }
    /*D if linesignal > 0 then begin
          i := lineno div (10*linesignal);
          if lineno = i*10*linesignal then writeln(stderr,'lineno ',lineno:1)
          end;
       if debuglevel > 1 then begin
          writeln(log); write(log,'lineno ',lineno:1,':') end; D*/

    if (inpic == 0 && !inputeof) {
      WITH = inbuf;
      FORLIM = WITH->savedlen - 2;
      for (i = 1; i <= FORLIM; i++)
	putchar(WITH->carray[i]);
      putchar('\n');
      WITH->savedlen = 0;
    }
    /* D; if debuglevel > 0 then begin
       write(log,'nextline:');
       with inbuf^ do for i := 1 to savedlen do write(log,carray^[i]);
       end D */
  } while (!(inbuf->savedlen > 0 || inputeof));
}


void inchar(void)
{
  fbuffer *tp;
  boolean bufend;
  attribute *WITH;
  fbuffer *WITH1;

  if (inbuf == NULL) {
    newbuf(&inbuf);
    inbuf->attrib = -1;
  }

  bufend = (inbuf->readx > inbuf->savedlen);
  while (bufend) {
    if (inbuf->nextb != NULL)
      inbuf = newinbuf(inbuf->nextb);
    else if (inbuf->attrib > 0) {
      while (inbuf->prevb != NULL) {
	inbuf->readx = 1;
	inbuf = newinbuf(inbuf->prevb);
      }
      WITH = &attstack[inbuf->attrib];
      /*repeat if lexval = Xrepeat then
         inbuf^.readx := 0
      else */
      if (WITH->length > 0)
	WITH->length--;
      else
	WITH->length++;
      /*D if debuglevel > 0 then
         writeln(log,'For index (length)=', length:1); D*/
      if (WITH->length == 0) {
	tp = inbuf;
	inbuf = newinbuf(inbuf->higherb);   /*D,4D*/
	disposebufs(&tp);
      } else
	inbuf->readx = 0;
    } else {
      while (inbuf->prevb != NULL)
	inbuf = newinbuf(inbuf->prevb);
      if (inbuf->nextb != NULL)   /*D,10D*/
	disposebufs(&inbuf->nextb);
      if (inbuf->higherb != NULL) {
	tp = inbuf;
	inbuf = newinbuf(inbuf->higherb);   /*D,3D*/
	disposebufs(&tp);
      } else if (!inputeof)
	nextline();
    }
    if (inputeof)
      bufend = false;
    else
      bufend = (inbuf->readx > inbuf->savedlen);
  }

  WITH1 = inbuf;

  /*D if debuglevel = 2 then with inbuf^ do begin
     write(log,'inchar[');
     if prevb<>nil then write(log,ordp(prevb):1);
     write(log,',',ordp(inbuf):1,',');
     if nextb<>nil then write(log,ordp(nextb):1);
     write(log,']: savedlen=',savedlen:1,' readx=',readx:1);
     if inputeof then writeln(log,' inputeof, ch=nlch')
     else writeln(log,' ch(',readx-1:1,')=',ord(ch):4,' "',ch,'"') end; D*/
  if (WITH1->readx <= 0) {
    ch = ':';
    writeerror();
    WITH1->readx = 1;
    return;
  }
  if (inputeof)
    ch = nlch;
  else {
    ch = WITH1->carray[WITH1->readx];
    WITH1->readx++;
  }

  /* This is a for or repeat loop */
  /* This is not a loop */
}  /* inchar */


void skiptoend(void)
{
  /* skip to end of the current input line */
  boolean cont;
  fbuffer *WITH;

  /*D if debuglevel>1 then
      writeln(log,'skiptoend: inbuf[',ordp(inbuf):1,']'); D*/
  cont = true;
  while (cont) {
    if (inbuf == NULL) {
      cont = false;
      break;
    }
    WITH = inbuf;
    /*D if (debuglevel>1) and (carray^[readx]=nlch) then
        writeln(log,'carray^[',readx:1,']=',ord(carray^[readx]):1); D*/
    if (WITH->carray[WITH->readx] == nlch)
      cont = false;
    else if (WITH->carray[WITH->readx] == etxch)
      exitmacro();
    WITH->readx++;
    if (WITH->readx > WITH->savedlen) {
      if (inbuf->nextb != NULL)
	inbuf = newinbuf(inbuf->nextb);
      else
	cont = false;
    }
  }
}


void backup(void)
{
  fbuffer *WITH;

  WITH = inbuf;
  WITH->readx--;
  ch = ' ';
}


void pointinput(nametype *txt)
{
  /* txt: strptr */
  int i, FORLIM;

  if (txt == NULL)
    return;
  if (txt->segmnt == NULL)
    return;
  if (txt->len >= FILENAMELEN)
    txt->len = FILENAMELEN - 1;
  FORLIM = txt->len;
  for (i = 0; i < FORLIM; i++)
    infile[i] = txt->segmnt[txt->seginx + i];
  for (i = txt->len; i < FILENAMELEN; i++)
    infile[i] = ' ';
  /*DUGHM if debuglevel > 0 then begin
     write(log,'Pointinput(segmnt ',seginx:1,', len ',len:1,') ');
     for i := 1 to len do write(log,infile[i]); writeln(log) end; MHGUD*/

  if (savebuf != NULL) {
    markerror(853);
    return;
  }
  if (checkfile(infile, true) != 0) {
    markerror(859);
    return;
  }
  if (copyin != NULL)
    copyin = freopen(P_trimname(infile, sizeof(mstring)), "r", copyin);
  else
    copyin = fopen(P_trimname(infile, sizeof(mstring)), "r");
  if (copyin == NULL)
    _EscIO(FileNotFound);
  backup();
  ch = nlch;
  savebuf = inbuf;
  inbuf = NULL;
}


/*--------------------------------------------------------------------*/



/*--------------------------------------------------------------------*/

void pushch(void)
{
  /* copy ch character into chbuf and get new ch */
  chbuf[chbufi] = ch;
  if (chbufi < CHBUFSIZ)   /* Leave 1 location free at the end of chbuf^ */
    chbufi++;
  else
    fatal(4);
  inchar();
}  /*pushch*/


void readtroff(void)
{
  /* read complete line into chbuf */
  while (ch != nlch)
    pushch();
  newsymb = XLtroff;
}


boolean isprint_(Char ch)
{
  return (ch >= 32 && ch <= 126);
}


int argcount(arg *ar)
{
  int i;

  if (ar == NULL)
    markerror(805);
  i = 0;
  while (ar != NULL) {
    if (ar->argbody != NULL)
      i++;
    ar = ar->nextb;
  }
  return i;
}


arg *findarg(arg *arlst, int k)
{
  arg *ar;
  int i, j;

  /*D if debuglevel > 0 then begin
      write(log, 'findarg(');
      if arlst = nil then write(log,'nil') else write(log,ordp(arlst):1);
      write(log,',',k:1,')=') end; D*/
  if (k > 0)
    ar = arlst;
  else
    ar = NULL;
  i = 1;
  j = k;
  while (i < j) {
    if (ar != NULL) {
      ar = ar->nextb;
      i++;
    } else
      j = i;
  }
  /*D if debuglevel > 0 then begin
     if (i<>k) or (ar=nil) then writeln(log,'not found')
     else wrbuf(ar^.argbody,2,1) end; D*/
  return ar;
}


void readstring(Char stringch)
{
  /* puts string terminal into chbuf */
  int j, n;
  boolean instr, pu;
  arg *ar;
  fbuffer *abuf, *WITH;
  int FORLIM;

  /*D if debuglevel > 0 then write(log,'readstring(',stringch,') '); D*/
  j = -1;
  n = 0;
  instr = true;
  pu = true;
  while (instr) {
    if (inputeof)
      instr = false;
    else if (ch == '\\') {
      pushch();
      if (ch == stringch)
	chbufi--;
      else
	pu = false;
    } else if (ch == '$' && j < 0)
      j = chbufi;
    else if (j >= 0 && isdigit(ch) != 0)
      n = n * 10 + ch - '0';
    else if (j >= 0) {
      if (n > 0 && args != NULL)   /* delete $nn */
	chbufi = j;
      ar = findarg(args, n);
      if (ar != NULL) {
	abuf = ar->argbody;
	while (abuf != NULL) {
	  WITH = abuf;
	  FORLIM = WITH->savedlen;
	  for (n = WITH->readx; n <= FORLIM; n++) {
	    chbuf[chbufi] = WITH->carray[n];
	    if (chbufi < CHBUFSIZ)
	      chbufi++;
	    else
	      fatal(4);
	  }
	  abuf = abuf->nextb;
	}
      }
      /*D if debuglevel > 0 then begin write(log,'arg(',n:1,')|');
         for n := j to chbufi-1 do write(log,chbuf^[n]);
         write(log,'| ') end; D*/
      j = -1;
      n = 0;
      pu = false;
    } else if (ch == stringch)
      instr = false;
    if (instr && pu)
      pushch();
    else
      pu = true;
  }
  if (ch != nlch)
    inchar();
  else
    markerror(901);
}


void readexponent(void)
{
  boolean neg;
  int k;

  pushch();
  if (ch == '-') {
    neg = true;
    pushch();
  } else if (ch == '+') {
    neg = false;
    pushch();
  } else
    neg = false;
  if (isdigit(ch) == 0) {
    markerror(802);
    return;
  }
  k = 0;
  do {
    k = k * 10 + ch - '0';
    pushch();
  } while (isdigit(ch) != 0);
  if (neg)
    floatvalue *= exp(-k * ln10);
  else
    floatvalue *= exp(k * ln10);
}  /* readexponent */


void readfraction(void)
{
  double x;

  x = 10.0;
  while (isdigit(ch) != 0) {
    floatvalue += (ch - '0') / x;
    x *= 10;
    pushch();
  }
}  /* readfraction */


void readconst(Char initch)
{
  if (initch == '.')
    readfraction();
  else {
    while (isdigit(ch) != 0) {
      floatvalue = 10 * floatvalue + ch - '0';
      pushch();
    }
    if (ch == '.') {
      pushch();
      readfraction();
    }
  }
  if (ch == 'e' || ch == 'E')
    readexponent();
  if (ch == 'i')   /* A rather odd way to allow inch units */
    pushch();
  newsymb = XLfloat;
}


/*D
procedure prlex(acc: boolean);
var i: integer;
begin
   if debuglevel > 0 then begin
      write(log, 'LEXICAL(oldsymb=',oldsymb:1,' newsymb=',newsymb:1,') chbuf');
      if newsymb <> XLtroff then begin
         write(log,'(',oldbufi:1,':',chbufi-1:1,')="');
         for i := oldbufi to chbufi-1 do write(log, chbuf^[i]);
         write(log,'"') end
      else write(log,'=<troff>');
      if newsymb = XLfloat then write( log,' value=',floatvalue:10:7);
      write(log,' nextch(', ord(ch):1,')"',ch,'" ');
      if not acc then write( log,'not accepted');
      writeln( log );
      consoleflush
      end
   end; D*/

fbuffer *nbuf(fbuffer *buf)
{
  fbuffer *ml;

  newbuf(&ml);
  ml->attrib = buf->attrib;
  ml->savedlen = CHBUFSIZ;
  ml->readx = CHBUFSIZ + 1;
  ml->nextb = buf;
  buf->prevb = ml;
  return ml;
}


void copyleft(fbuffer *mac, fbuffer **buf)
{
  /* mac: fbufferp; var buf: fbufferp */
  /* Push macro into the head of the input stream */
  fbuffer *ml;
  int i;
  boolean nflag;
  int FORLIM;
  fbuffer *WITH;

  /*D if debuglevel > 0 then begin
     writeln(log, 'copyleft:'); write(log,' input string'); wrbuf(mac,3,1);
     write(log,' output '); wrbuf(buf,3,1) end; D*/
  writeerror();
  ml = mac;
  while (ml != NULL) {
    mac = ml;
    ml = ml->nextb;
  }
  while (mac != NULL) {
    if (mac->carray != NULL) {
      FORLIM = mac->readx;
      for (i = mac->savedlen; i >= FORLIM; i--) {
	if (*buf == NULL)
	  nflag = true;
	else if ((*buf)->attrib >= 0)
	  nflag = true;
	else
	  nflag = false;
	if (nflag) {
	  /*D if debuglevel > 0 then
	     writeln(log,'nflag=',nflag:1,' attrib=',buf^.attrib:1); D*/
	  newbuf(&ml);
	  ml->attrib = -1;
	  ml->savedlen = CHBUFSIZ;
	  ml->readx = CHBUFSIZ + 1;
	  ml->higherb = *buf;
	  *buf = ml;
	} else if ((*buf)->readx <= 1 && (*buf)->prevb != NULL) {
	  WITH = (*buf)->prevb;
	  WITH->attrib = (*buf)->attrib;
	  WITH->savedlen = CHBUFSIZ;
	  WITH->readx = CHBUFSIZ + 1;
	  WITH->nextb = *buf;
	  *buf = (*buf)->prevb;
	} else if ((*buf)->readx <= 1)
	  *buf = nbuf(*buf);
	WITH = *buf;
	WITH->readx--;
	WITH->carray[WITH->readx] = mac->carray[i];
      }
    }
    mac = mac->prevb;
  }
  if ((*buf)->readx <= 1)
    *buf = nbuf(*buf);
  WITH = *buf;
  /*D; if debuglevel > 0 then begin
     ml := buf; write(log,' copyleft result'); while ml <> nil do begin
        wrbuf(ml,3,1); ml := ml^.nextb end end D*/
  WITH->carray[WITH->readx - 1] = nlch;
}


void copyright(fbuffer *mac, fbuffer **buf)
{
  /* Push macro into the tail of the input buffer */
  fbuffer *ml;
  int i;
  fbuffer *WITH;

  /*D if debuglevel > 0 then begin
     writeln(log, 'copyright:');
     write(log,' input'); wrbuf(mac,3,1);
     write(log,' output'); wrbuf(buf,3,0) end; D*/
  while (mac != NULL) {
    i = mac->readx;
    while (i <= mac->savedlen) {
      if (*buf == NULL) {
	newbuf(buf);
	WITH = *buf;
	WITH->attrib = -1;
	WITH->savedlen = 0;
	WITH->readx = 1;
      } else if ((*buf)->savedlen >= CHBUFSIZ) {
	newbuf(&ml);
	ml->attrib = (*buf)->attrib;
	ml->savedlen = 0;
	ml->readx = 1;
	ml->prevb = *buf;
	(*buf)->nextb = ml;
	*buf = ml;
      }
      WITH = *buf;
      WITH->savedlen++;
      WITH->carray[WITH->savedlen] = mac->carray[i];
      i++;
    }
    mac = mac->nextb;
  }
  /*D; if debuglevel > 0 then with buf^ do begin
     write(log,' result'); wrbuf(buf,3,0) end D*/
}


void definearg(int *parenlevel, fbuffer **p2)
{
  /* Stash the current argument into the arg struct*/
  int j, n;
  arg *ar;
  fbuffer *p, *p1;
  boolean inarg, instring;
  Char prevch;
  fbuffer *WITH;

  /*D if debuglevel > 0 then write(log, 'definearg: '); D*/
  while (ch == ' ' || ch == tabch)
    inchar();
  p1 = NULL;
  if (*parenlevel >= 0)
    inarg = true;
  else
    inarg = false;
  while (inarg) {
    newbuf(&p);
    p->attrib = -1;
    if (p1 != NULL) {
      p1->nextb = p;
      p->prevb = p1;
    }
    p1 = p;
    j = CHBUFSIZ;
    instring = false;
    prevch = ' ';
    do {
      WITH = p1;
      if (instring) {
	if (ch == '"' && prevch != '\\')
	  instring = false;
      } else if (ch == '(')
	(*parenlevel)++;
      else if (ch == ')')
	(*parenlevel)--;
      else if (ch == '"')
	instring = true;
      if (!instring && (*parenlevel < 0 || *parenlevel == 0 && ch == ',')) {
	j = WITH->savedlen;
	inarg = false;
      } else if (ch != '$') {
	prevch = ch;
	WITH->savedlen++;
	WITH->carray[WITH->savedlen] = ch;
	/*D if debuglevel = 2 then writeln(log,
	 'definearg2: savedlen=',savedlen:1,' ch=',ord(ch):1,'"',ch,'"');D*/
	inchar();
      } else {
	n = 0;
	prevch = ch;
	inchar();
	if (isdigit(ch) != 0) {
	  while (isdigit(ch) != 0) {
	    n = n * 10 + ch - '0';
	    inchar();
	  }
	  ar = findarg(args, n);
	  if (ar != NULL) {
	    /* else markerror(805) */
	    copyright(ar->argbody, &p1);
	  }
	} else {
	  WITH->savedlen++;
	  WITH->carray[WITH->savedlen] = prevch;
	  /*D if debuglevel = 2 then writeln(log,'definearg2: savedlen=',
	      savedlen:1,' ch=',ord(ch):1,'"',ch,'"');D*/
	}
      }
      if (inputeof) {
	markerror(806);
	j = WITH->savedlen;
	inarg = false;
	*parenlevel = -1;
      }
    } while (p1->savedlen != j);
  }
  if (p1 != NULL) {
    while (p1->prevb != NULL)
      p1 = p1->prevb;
  }
  ch = ' ';
  *p2 = p1;
  /*D; if debuglevel > 0 then with p1^ do begin
     write(log,' definearg'); wrbuf(p1,3,0) end D*/
}


void skipcontinue(void)
{
  boolean continuation;
  fbuffer *WITH;

  if (inbuf == NULL)
    return;
  WITH = inbuf;
  do {
    if (ch != '\\')
      continuation = false;
    else if (WITH->readx == WITH->savedlen - 1)
      continuation = true;
    else if (WITH->carray[WITH->readx + 1] == '#')
      continuation = true;
    else
      continuation = false;
    if (continuation) {
      WITH->readx = WITH->savedlen + 2;
      inchar();
    }
  } while (continuation);
}


void skipwhite(void)
{
  /*D if debuglevel = 2 then writeln(log, 'skipwhite: ' ); D*/
  while (ch == etxch || ch == nlch || ch == tabch || ch == ' ') {
    if (ch == etxch)
      exitmacro();
    inchar();
    skipcontinue();
  }
}


boolean ismacro(Char *chb, chbufinx obi, chbufinx chbi)
{
  arg *mac, *lastp, *ar, *lastarg, *firstarg;
  int level;
  boolean ism;

  /*D if debuglevel > 0 then begin
      write(log, 'ismacro[');
      for level:=obi to chbi-1 do write(log,chb^[level]);
      write(log,']:') end;
      D*/
  ism = false;
  if (oldsymb == XLdefine) {
    skipwhite();
    return ism;
  }
  if (oldsymb == XLundefine)
    return ism;
  mac = findmacro(macros, chb, obi, chbi - obi, &lastp);
  if (mac == NULL)
    return ism;
  ism = true;
  firstarg = NULL;
  lastarg = NULL;
  if (ch == '(')
    level = 0;
  else {
    backup();
    level = -1;
  }
  do {
    newarg(&ar);
    ar->higherb = args;
    if (lastarg == NULL)
      firstarg = ar;
    else
      lastarg->nextb = ar;
    if (level >= 0) {
      inchar();
      definearg(&level, &ar->argbody);
    }
    lastarg = ar;
  } while (level >= 0);
  args = firstarg;
  copyleft(mac->argbody, &inbuf);
  /*D if debuglevel > 0 then writeln(log,'ismacro ',ism); D*/
  return ism;
}


void copyarg(Char *chb, chbufinx chbs, chbufinx chbi)
{
  int n, i;
  arg *ar;

  /*D if debuglevel > 0 then begin write(log,'copyarg(');
     for i:= chbs to chbi-1 do write(log,chb^[i]); write(log,') ') end; D*/
  n = 0;
  for (i = chbs + 1; i < chbi; i++)
    n = n * 10 + chb[i] - '0';
  ar = findarg(args, n);
  backup();
  if (ar != NULL) {
    if (ar->argbody != NULL) {
      /* else markerror(805) */
      copyleft(ar->argbody, &inbuf);
    }
  }
}


boolean insertarg(void)
{
  int icx;

  pushch();
  /* D if debuglevel > 0 then write(log,'insertarg ch=',ch,' '); D */
  if (ch == '+') {
    backup();
    ch = '$';
    chbufi--;
    return false;
  } else {
    icx = chbufi - 1;
    while (isdigit(ch) != 0)
      pushch();
    copyarg(chbuf, icx, chbufi);
    chbufi = icx;
    inchar();
    return true;
  }
}


void lexical(void)
{
  /* sets newsymb to value of next acceptable terminal */
  int lxix;
  Char firstch;
  boolean terminalaccepted, looping;
  fbuffer *WITH;

  floatvalue = 0.0;
  lexsymb = -1;
  do {
    terminalaccepted = true;
    oldbufi = chbufi;   /* first char of current terminal in chbuf */
    while (ch == ' ' || ch == tabch)
      inchar();

    if (inpic == 1) {
      newsymb = XSTART;
      inpic = 2;
    } else if (inpic == 3) {
      /*D if linesignal > 0 then begin
         writeln(stderr,'.PE'); consoleflush end; D*/
      newsymb = XEND;
      /* ch := '.'; */
      inpic = 4;
    } else if (inpic == 4) {
      newsymb = XNL;
      skiptoend();
      ch = ' ';
      inpic = 0;
    } else if (inputeof) {
      if (oldsymb == 0) {
	/* nextline */
	writeerror();
	fatal(5);
      } else if (oldsymb == 1)
	newsymb = 0;
      else
	newsymb = 1;
    } else if (isdigit(ch) != 0)
      readconst(ch);
    else if (ch == etxch) {
      exitmacro();
      inchar();
      terminalaccepted = false;
    } else {
      firstch = ch;
      pushch();

      WITH = inbuf;
      if (firstch == '\\' && (WITH->readx == WITH->savedlen || ch == '#'))
      {  /* continuation line */
	ch = ' ';
	newsymb = -2;   /* flag for troff test */
	WITH->readx = WITH->savedlen + 2;
	terminalaccepted = false;
      } else if (firstch == '\\')
	readtroff();
      else if (firstch == '.' && isdigit(ch) != 0)
	readconst(firstch);
      else if (firstch == '.' && WITH->readx == 3 && inbuf->prevb == NULL &&
	       newsymb != -2)
	readtroff();
      else {
	/* search in lex tree */
	newsymb = entrytv[firstch];
	lxix = entryhp[firstch];
	while (lxix != 0) {
	  if (ch == '$') {
	    if (!insertarg())
	      lxix = 0;
	    continue;
	  }
	  if (lxch[lxix] == ch) {
	    newsymb = lxtv[lxix];
	    lxix = lxhp[lxix];
	    pushch();
	  } else
	    lxix = lxnp[lxix];
	}

	if (isupper(firstch) != 0 &&
	    (isalnum(ch) != 0 || ch == '_' || ch == '$')) {
	  looping = true;
	  while (looping) {
	    if (ch == '$')
	      looping = insertarg();
	    else if (isalnum(ch) != 0 || ch == '_')
	      pushch();
	    else
	      looping = false;
	  }
	  if (ismacro(chbuf, oldbufi, chbufi))
	    terminalaccepted = false;
	  else
	    newsymb = XLabel;
	} else if ((isalnum(firstch) != 0 || firstch == '_') &&
		   (isalnum(ch) != 0 || ch == '_' || ch == '$')) {
	  looping = true;
	  while (looping) {
	    if (ch == '$')
	      looping = insertarg();
	    else if (isalnum(ch) != 0 || ch == '_')
	      pushch();
	    else
	      looping = false;
	  }
	  if (ismacro(chbuf, oldbufi, chbufi))
	    terminalaccepted = false;
	  else
	    newsymb = XLname;
	} else if (newsymb == XLstring) {
	  chbufi--;
	  readstring(chbuf[chbufi]);
	} else if (newsymb == XCOMMENT) {
	  skiptoend();
	  ch = nlch;
	  terminalaccepted = false;
	} else if (newsymb == XNL &&
		   (oldsymb == XLelse || oldsymb == XLBRACE ||
		    oldsymb == XLthen || oldsymb == XNL))
	  terminalaccepted = false;
	else if (newsymb == XGT && inlogic) {
	  lexsymb = XGG;
	  newsymb = XLlogic;
	} else if (newsymb == XLT && inlogic) {
	  lexsymb = XLL;
	  newsymb = XLlogic;
	} else if (newsymb > XLeq && newsymb <= XLremeq) {
	  lexsymb = newsymb;
	  newsymb = XLeq;
	} else if (newsymb > XLcorner) {
	  lexsymb = newsymb;
	  if (newsymb > XLenvvar)
	    newsymb = XLenvvar;
	  else if (newsymb > XLprimitiv)
	    newsymb = XLprimitiv;
	  else if (newsymb > XLdirecton)
	    newsymb = XLdirecton;
	  else if (newsymb > XLarrowhd)
	    newsymb = XLarrowhd;
	  else if (newsymb > XLtextpos)
	    newsymb = XLtextpos;
	  else if (newsymb > XLcolrspec)
	    newsymb = XLcolrspec;
	  else if (newsymb > XLlinetype)
	    newsymb = XLlinetype;
	  else if (newsymb > XLfunc2)
	    newsymb = XLfunc2;
	  else if (newsymb > XLfunc1)
	    newsymb = XLfunc1;
	  else if (newsymb > XLparam)
	    newsymb = XLparam;
	  else if (newsymb > XLlogic)
	    newsymb = XLlogic;
	  else
	    newsymb = XLcorner;
	} else if (newsymb == XLarg) {
	  if (ch == '+') {
	    floatvalue = argcount(args);
	    newsymb = XLfloat;
	    inchar();
	  } else {
	    if (isdigit(ch) == 0)
	      markerror(805);
	    while (isdigit(ch) != 0)
	      pushch();
	    copyarg(chbuf, oldbufi, chbufi);
	    terminalaccepted = false;
	  }
	} else if (newsymb == XLdo) {
	  /*D else if newsymb = XAND then begin
	     chbufi := oldbufi;
	     if debuglevel > 0 then consoleflush;
	     if ord(ch) >=ord('A') then
	        linesignal := 1+ord(ch)-ord('A')
	     else if ord(ch) > ord('0') then begin
	        openlogfile;
	        debuglevel := ord(ch)-ord('0')
	        end;
	     writeln(log,'Debuglevel = ',debuglevel:1,
	        ' linesignal = ',linesignal:1); consoleflush;
	     inchar;
	     terminalaccepted := false
	     end D*/
	  skipwhite();
	} else if (newsymb == 0 && isupper(firstch) != 0) {
	  if (ismacro(chbuf, oldbufi, chbufi))
	    terminalaccepted = false;
	  else
	    newsymb = XLabel;
	} else if (newsymb == 0 && (isalnum(firstch) != 0 || firstch == '_')) {
	  if (ismacro(chbuf, oldbufi, chbufi))
	    terminalaccepted = false;
	  else
	    newsymb = XLname;
	} else if (newsymb == 0) {
	  fprintf(stderr_, "Char chr(%d)", firstch);
	  if (firstch > 32 && (firstch & 255) < 127)
	    fprintf(stderr_, "\"%c\"", firstch);
	  fprintf(stderr_, " unknown\n");
	  markerror(800);
	  terminalaccepted = false;
	}
      }
    }

    /*D prlex( terminalaccepted ); D*/
    if (newsymb != XLtroff && newsymb != XLstring && newsymb != XLabel &&
	newsymb != XLname)
      chbufi = oldbufi;
  } while (!terminalaccepted);
  if (lexsymb == -1)
    lexsymb = newsymb;
  oldsymb = newsymb;



  /* char not recognized */
  /*D if debuglevel > 0 then
     writeln (log,'800:',ord(firstch),ord(ch)); D*/
  /*lookahead terminals*/
}  /* lexical */


/*--------------------------------------------------------------------*/

void skiptobrace(void)
{
  int bracelevel;
  boolean instring;
  Char prevch;

  /*D if debuglevel = 2 then writeln(log, 'skiptobrace: ' ); D*/
  bracelevel = 1;
  prevch = ' ';
  instring = false;
  while (bracelevel > 0) {
    skipcontinue();
    if (ch == etxch)
      exitmacro();
    if (instring) {
      if (ch == '"' && prevch != '\\')
	instring = false;
    } else if (ch == '{')
      bracelevel++;
    else if (ch == '}')
      bracelevel--;
    else if (ch == '"')
      instring = true;
    if (bracelevel <= 0)
      break;
    if (inputeof) {
      bracelevel = 0;
      markerror(804);
    } else {
      prevch = ch;
      inchar();
    }
  }
}


/* Stuff the body of a for loop or a macro body into p2
   attx: attstack index or -(name length)
   p0 = nil: append the output to this buffer.
   Should we check for macro arguments? */

void readfor(fbuffer *p0, int attx, fbuffer **p2)
{
  /* p0: fbufferp; attx: integer; var p2: fbufferp */
  int j, bracelevel;
  fbuffer *p, *p1;
  boolean instring;
  Char prevch;

  /*D if debuglevel = 2 then writeln(log,'readfor: attx', attx:5 ); D*/
  writeerror();
  prevch = ' ';
  instring = false;
  bracelevel = 1;
  p1 = NULL;
  while (bracelevel > 0) {
    if (p0 == NULL)
      newbuf(&p);
    else {
      p = p0;
      p0 = NULL;
    }
    p->attrib = attx;
    if (p1 != NULL) {
      p1->nextb = p;
      p->prevb = p1;
    }
    p->higherb = inbuf;
    p1 = p;
    j = CHBUFSIZ;
    do {
      skipcontinue();
      /* D if debuglevel = 2 then write(log,
         'readfor1: ch=',ord(ch):1,'"',ch,'"'); D */
      if (instring) {  /* don't check braces in strings */
	if (ch == '"' && prevch != '\\')
	  instring = false;
      } else if (ch == '{')
	bracelevel++;
      else if (ch == '}')
	bracelevel--;
      else if (ch == '"')
	instring = true;
      if (bracelevel <= 0) {
	j = p1->savedlen + 1;
	ch = nlch;
      }
      p1->savedlen++;
      p1->carray[p1->savedlen] = ch;
      prevch = ch;
      /*D if debuglevel = 2 then writeln(log,' savedlen=',savedlen:1,
         ' carray(',savedlen:1,')=',ord(ch):1,'"',ch,'"'); D*/
      if (bracelevel > 0)
	inchar();
      if (inputeof) {
	markerror(804);
	j = p1->savedlen;
	bracelevel = 0;
      }
    } while (p1->savedlen != j);
  }
  while (p1->prevb != NULL)
    p1 = p1->prevb;
  backup();
  /*D if debuglevel > 0 then begin
     write(log,'For/macro buffer'); wrbuf(p1,3,0) end; D*/
  *p2 = p1;
}


/*--------------------------------------------------------------------*/

void bumptop(stackinx chk, stackinx *sttop)
{
  if (chk < STACKMAX)
    (*sttop)++;
  else
    fatal(6);
}


void advance(void)
{  /* perform reductions */
  int i, j;
  reduelem *WITH;
  int FORLIM;

  /*D if (debuglevel > 1) and (redutop > 0) then begin
     write(log,'advance prod nos:');
     for i:=1 to redutop do write(log,redubuf[i].prod:4);
     writeln(log);
     write(log,'        newtop  :');
     for i:=1 to redutop do write(log,redubuf[i].newtop:4);
     writeln(log)
     end; D*/

  reduinx = 1;
  while (reduinx <= redutop) {
    WITH = &redubuf[reduinx + REDUMAX];
    /*D if debuglevel > 1 then begin
       j := newtop; if oldtop > newtop then j := oldtop;
       write(log,'attstack: ');
       for i := 1 to j do write(log,i:4);                   writeln(log);
       write(log,'lexical : ');
       for i := 1 to j do write(log,attstack^[i].lexval:4); writeln(log);
       write(log,'chbufx  : ');
       for i := 1 to j do write(log,attstack^[i].chbufx:4); writeln(log);
       write(log,'length  : ');
       for i := 1 to j do write(log,attstack^[i].length:4); writeln(log);
       D*/
    /* D
              write(log,'xval    : ');
              for i := 1 to j do write(log,attstack^[i].xval:4:1); writeln(log);
              write(log,'yval    : ');
              for i := 1 to j do write(log,attstack^[i].yval:4:1); writeln(log);
              D */
    /*D
              write(log,'ptype   : ');
              for i := 1 to j do if attstack^[i].prim = nil then write(log,'    ')
                 else write(log,attstack^[i].prim^.ptype:4);
              writeln(log)
              end; D*/

    produce(WITH->newtop, WITH->prod_);   /* may change reduinx */

    if (WITH->prod_ == forhead1 && attstack[WITH->newtop].length != 0) {
      /*repeat else if (prod = loophead1) then readfor(nil,newtop,inbuf) */
      readfor(NULL, WITH->newtop, &inbuf);
    }

    /* D if debuglevel > 1 then writeln(log,
       'attstack^[', newtop:1, '].chbufx<-', attstack^[newtop-1].chbufx:1);
        D */
    /* attstack^[newtop].chbufx := attstack^[newtop-1].chbufx; */
    reduinx++;
  }


  /*update stack*/
  if (validtop != top) {
    FORLIM = stacktop - validtop;
    for (i = 1; i <= FORLIM; i++)
      parsestack[validtop + i] = parsestack[top + i];
  }

  /* This maintains the input string buffer and could be removed
                                         if the buffer is not required */
  j = attstack[stacktop - 1].chbufx;
  /*D if (debuglevel > 1) and (redutop > 0) and (j < oldbufi) then begin
     write(log,' stacktop=',stacktop:1);
     write(log,' attstack^[stacktop-1](chbufx,length) = (',
     attstack^[stacktop-1].chbufx:1,',',attstack^[stacktop-1].length:1,')')
     end;D*/

  if (redutop > 0 && j < oldbufi &&
      redubuf[redutop + REDUMAX].prod_ != closeblock1 &&
      redubuf[redutop + REDUMAX].prod_ != suffix2 &&
      redubuf[redutop + REDUMAX].prod_ != suffix1) {
    FORLIM = chbufi - oldbufi;
    /*D if debuglevel > 0 then writeln(log,
       'chbuf(', oldbufi:1, ':', chbufi-1:1, ')->(',
       j:1, ':', j+chbufi-oldbufi-1:1, ')'); D*/

    for (i = 0; i < FORLIM; i++)
      chbuf[j + i] = chbuf[oldbufi + i];
    chbufi += j - oldbufi;
    oldbufi = j;
  }


  /*Dif debuglevel > 1 then writeln(log);D*/
  /* shift */
  bumptop(stacktop, &stacktop);
  parsestack[stacktop].table = startinx;
  stackattribute(stacktop);

  /* freeze new stack situation, ready for new lookahead */
  top = stacktop;
  pseudotop = stacktop;
  validtop = stacktop;
  start = lri;
  redutop = 0;
}  /*advance*/


void backtrack(stackinx btop, int bstart)
{
  stacktop = btop;
  validtop = btop;
  pseudotop = btop;
  startinx = bstart;
  lri = bstart;
  redutop = 0;
}  /* backtrack */


void pseudoshift(void)
{
  bumptop(pseudotop, &stacktop);
  pseudotop = top + stacktop - validtop;
  parsestack[pseudotop].table = startinx;
  stackattribute(pseudotop);
}  /* pseudoshift */


Local void queue(int rs_, int p)
{
  reduelem *WITH;

  if (p >= 0) {
    if (redutop < REDUMAX)
      redutop++;
    else
      fatal(7);
    WITH = &redubuf[redutop + REDUMAX];
    /*D oldtop := stacktop; D*/
    stacktop -= rs_;
    WITH->newtop = stacktop;
    WITH->prod_ = p;
  } else
    stacktop -= rs_;
  if (stacktop <= validtop) {
    pseudotop = stacktop;
    validtop = stacktop;
  } else
    pseudotop -= rs_;
}  /* queue */


/*--------------------------------------------------------------------*/

boolean lookahead(symbol lsymbol)
{
  boolean Result, decided;
  int si;

  decided = false;
  /*Dif trace then write(log,' lri:');D*/
  do {
    /*Dif trace then write(log, lri: 4);D*/
    startinx = lri;
    switch (lr[lri + kind]) {

    case 0:
      decided = true;
      Result = true;
      parsestop = true;
      break;

    case 1:
      while (lr[lri + symb] != lsymbol && lr[lri] != 0)
	lri = lr[lri];
      decided = true;
      Result = (lr[lri + symb] == lsymbol);
      break;

    case 2:
    case 4:
    case 6:
      while (lr[lri + symb] != lsymbol && lr[lri] != 0)
	lri = lr[lri];
      if (lr[lri + kind] == 2) {
	decided = true;
	Result = true;
      } else if (lr[lri + kind] == 6) {
	pseudoshift();
	stacktop--;
	pseudotop--;
	queue(-1, lr[lri + err]);
      }
      break;

    case 3:
      queue(lr[lri + rs], lr[lri + prod]);
      break;

    case 5:
      si = parsestack[pseudotop].table;
      /*Dif trace then
          writeln(log, ' SI(', si: 1, ')');D*/
      while (lr[lri + lb] != si && lr[lri] != 0)
	lri = lr[lri];
      break;
    }/* case */
    lri = lr[lri + next];
    /*D;if trace then write(log,'|')D*/
  } while (!decided);
  /*Dif trace then writeln(log,' lookahead done')D*/
  return Result;
}  /* lookahead */


/*--------------------------------------------------------------------*/

void syntaxerror(void)
{
  boolean success;
  stackinx s, s1, FORLIM;

  /*Dif debuglevel > 0 then write(log, ' <---SYNTAXERROR');D*/

  markerror(lr[startinx + err]);
  backtrack(top, start);
  pseudoshift();
  s = 0;
  FORLIM = top;
  for (s1 = 0; s1 <= FORLIM; s1++) {
    backtrack(s1, parsestack[s1 + 1].table);
    if (lookahead(XERROR)) {
      parsestack[s1].link = s;
      s = s1;
    }
  }
  success = false;
  do {
    s1 = s;
    do {
      backtrack(s1, parsestack[s1 + 1].table);
      if (lookahead(XERROR)) {
	pseudoshift();
	success = lookahead(newsymb);
      }
      s1 = parsestack[s1].link;
    } while (!(success || s1 == 0));
    if (!success)   /*D end D*/
      lexical();
    /*D begin if debuglevel > 0 then writeln(log, ' <---SKIPPED'); D*/
  } while (!(success || parsestop));
  if (parsestop)
    fatal(8);
}  /* syntaxerror */


void parse(void)
{
  initrandom();

  chbuf = Malloc(sizeof(chbufarray));
  entrytv[ordNL] = XNL;
  entrytv[ordCR] = XNL;   /* treat ^M as line end */

  errcount = 0;
  /* change for debugging */
  /* linesignal := 0; */
  /*D trace := false;
  if trace then debuglevel := 1 else debuglevel := 0; D*/
  /*DUGHM if oflag > 0 then  debuglevel := oflag; MHGUD*/
  /*DUGHM if trace and (oflag <= 0) then openlogfile; MHGUD*/
  /* Dwriteln('debuglevel=',debuglevel); D */

  parsestack = Malloc(sizeof(tparsestack));
  produce(1, -2);
  printstate = 0;
  /* lexical initializations, see also
     production -1 */
  ch = ' ';
  lineno = 0;
  chbufi = 0;
  oldbufi = 0;
  newsymb = XNL;
  oldsymb = XNL;
  inpic = 0;
  macros = NULL;
  args = NULL;

  stackattribute(0);
  /* parser initializations */
  parsestop = false;
  top = 0;
  start = 5;
  parsestack[0].table = 0;
  parsestack[0].link = 0;
  backtrack(top, start);
  /*D stackhigh := top; D*/
  produce(1, -1);
  while (!parsestop) {
    lexical();
    /*D if trace then
       writeln(log, ' SYM:', newsymb: 3, ' STATE:', lri: 3);D*/
    if (!lookahead(newsymb))
      syntaxerror();
    advance();
  }
  /* nextline */
  writeerror();
}  /* parse */


Char optionchar(Char *fn)
{
  int j, k;

  j = 1;
  k = FILENAMELEN + 1;
  while (j < k) {
    if (fn[j - 1] == ' ')
      j++;
    else
      k = j;
  }
  if (j >= FILENAMELEN)
    return '\0';
  else if (fn[j - 1] == '-') {
    return (fn[j]);
    /*
    if fn[j+2] <> ' ' then for k:=j+2 to FILENAMELEN do fn[k-j-1] := fn[k]
    */
  } else
    return '\0';
}


void getoptions(void)
{
  Char cht;
  int istop;

  drawmode = TeX;
  /*DUGHM oflag := 0; linesignal := 0; MHGUD*/
  argct = 1;
  istop = P_argc;   /*GH ParamCount+1; HG*/
  while (argct < istop) {
    P_sun_argv(infile, sizeof(mstring), argct);
	/*GH infile := ParamStr(argct); HG*/
    cht = optionchar(infile);
    if (cht == 0) {
      istop = argct;
      continue;
    }
    /* if      cht = 'd' then drawmode := PSmps */
    /* Metapost-readable PS*/
    /*
    else */
    if (cht == 'e')
      drawmode = pict2e;
    else if (cht == 'f')
      drawmode = PSfrag;
    else if (cht == 'g')
      drawmode = PGF;
    else if (cht == 'm')
      drawmode = MFpic;
    else if (cht == 'p')
      drawmode = PSTricks;
    else if (cht == 'r')
      drawmode = PS;
    else if (cht == 's')
      drawmode = MPost;
    else if (cht == 't')
      drawmode = tTeX;
    else if (cht == 'x')
      drawmode = xfig;
    else if (cht == 'z') {
      safemode = true;
      /*DUGHM
         else if cht = 'v' then linesignal := 2
         else if (cht >= '0') and (cht <= '9') then oflag := ord(cht)-ord('0')
         MHGUD*/
    } else if (cht == 'h') {
      fprintf(stderr_, " *** ");
      fprintf(stderr_, "%s\n", Version);
      fprintf(stderr_, " options:\n");
      fprintf(stderr_, "     (none) output latex drawing commands\n");
      /* writeln(stderr,'     -d pdftex graphicx output'); */
      fprintf(stderr_, "     -e pict2e output\n");
      fprintf(stderr_, "     -f Postscript output, psfrag strings\n");
      fprintf(stderr_, "     -g PGF output\n");
      fprintf(stderr_, "     -h write this message and quit\n");
      fprintf(stderr_, "     -m mfpic output\n");
      fprintf(stderr_, "     -p PSTricks output\n");
      fprintf(stderr_, "     -r Postscript output\n");
      fprintf(stderr_, "     -s MetaPost output\n");
      fprintf(stderr_, "     -t eepicemu output\n");
      fprintf(stderr_, "     -x xfig output\n");
      fprintf(stderr_, "     -z safe mode (sh and copy disabled)\n");
      fatal(0);
    } else {
      fprintf(stderr_, " *** dpic terminating: Unknown option \"");
      if (isprint_(cht))
	fprintf(stderr_, "%c\"\n", cht);
      else
	fprintf(stderr_, "char(%d)\"\n", cht);
      fatal(0);
    }
    argct++;
  }
}  /* getoptions */


void initmachine(void)
{
  etxch = (Char)ordETX;
  nlch = (Char)ordNL;
  crch = (Char)ordCR;
  tabch = (Char)ordTAB;
  safemode = false;
}  /* initmachine */


main(int argc, Char *argv[])
{
  PASCAL_MAIN(argc, argv);
  /* dpic */
  copyin = NULL;
  stderr_ = NULL;
  output = NULL;
  input = NULL;
  initmachine();
  openerror();
  getoptions();
  /* Dwriteln('oflag=',oflag); D */
  openfiles();
  inputeof = false;
  attstack = Malloc(sizeof(attstacktype));
  parse();
  epilog();
  /*X retcode(errcount); X*/

  if (input != NULL)
    fclose(input);
  if (output != NULL)
    fclose(output);
  if (stderr_ != NULL)
    fclose(stderr_);
  if (copyin != NULL)
    fclose(copyin);
  exit(EXIT_SUCCESS);
}



/* End. */
