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

#define Version         "dpic version 13.Jul.09"

/* UMBX distmax = 1E25; XBMU */

#define distmax         3.40282347e+38   /* assumes at least IEEE single */
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
#define prodmax         180
#define lrmax           4742
#define lxmax           455
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
#define lbrace1         29
#define namedbox1       30
#define namedbox2       31
#define suffix1         32
#define suffix2         33
#define position1       34
#define position2       35
#define position3       36
#define position4       37
#define assignlist1     38
#define assignlist2     39
#define command1        40
#define command2        41
#define command3        42
#define command4        43
#define command5        44
#define command6        45
#define command7        46
#define command8        47
#define command9        48
#define command10       49
#define optnl1          50
#define optnl2          51
#define ifpart1         52
#define elsehead1       53
#define for1            54
#define for2            55
#define stringexpr1     56
#define stringexpr2     57
#define string1         58
#define string2         59
#define assignment1     60
#define assignment2     61
#define assignment3     62
#define assignment4     63
#define expression1     64
#define expression2     65
#define expression3     66
#define expression4     67
#define expression5     68
#define ifhead1         69
#define setlogic1       70
#define logexpr1        71
#define logexpr2        72
#define forhead1        73
#define forincr1        74
#define do1             75
#define do2             76
#define by1             77
#define by2             78
#define redirect1       79
#define redirect2       80
#define redirect3       81
#define resetlist1      82
#define resetlist2      83
#define defhead1        84
#define defhead2        85
#define sprintf1        86
#define sprintf2        87
#define exprlist1       88
#define exprlist2       89
#define object1         90
#define object2         91
#define object3         92
#define object4         93
#define object5         94
#define object6         95
#define object7         96
#define object8         97
#define object9         98
#define object10        99
#define object11        100
#define object12        101
#define object13        102
#define object14        103
#define object15        104
#define object16        105
#define object17        106
#define object18        107
#define object19        108
#define object20        109
#define object21        110
#define object22        111
#define object23        112
#define object24        113
#define object25        114
#define object26        115
#define object27        116
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
#define objectwith1     127
#define objectwith2     128
#define objectwith3     129
#define nth1            130
#define nth2            131
#define nth3            132
#define primobj1        133
#define primobj2        134
#define primobj3        135
#define primobj4        136
#define shift1          137
#define shift2          138
#define shift3          139
#define location1       140
#define location2       141
#define location3       142
#define location4       143
#define location5       144
#define place1          145
#define place2          146
#define place3          147
#define place4          148
#define place5          149
#define factor1         150
#define factor2         151
#define factor3         152
#define placename1      153
#define placename2      154
#define placename3      155
#define placename4      156
#define ncount1         157
#define ncount2         158
#define ncount3         159
#define logprod1        160
#define logprod2        161
#define logval1         162
#define logval2         163
#define logval3         164
#define lcompare1       165
#define lcompare2       166
#define lcompare3       167
#define lcompare4       168
#define primary1        169
#define primary2        170
#define primary3        171
#define primary4        172
#define primary5        173
#define primary6        174
#define primary7        175
#define primary8        176
#define primary9        177
#define primary10       178
#define primary11       179
#define primary12       180

/* include lxcst.h */
/*D XAND = 36; D*/
#define XBLOCK          26
#define XLBRACKET       21
#define XRBRACKET       22
#define XCOMMENT        42
#define XLcolrspec      137
#define XLcolour        138
#define XCARET          15
#define XCOLON          20
#define XD              25
#define XDOUBLEHEAD     150
#define XDc             98
#define XDe             94
#define XDend           97
#define XDn             92
#define XDne            88
#define XDnw            90
#define XDs             93
#define XDse            89
#define XDstart         96
#define XDsw            91
#define XDw             95
#define XEMPTY          2
#define XEND            46
#define XEQEQ           100
#define XEQ             29
#define XGE             102
#define XLE             103
#define XERROR          3
#define XFOR            84
#define XGT             105
#define XLBRACE         23
#define XLEFTHEAD       148
#define XLL             104
#define XLT             4
#define XLabel          39
#define XLabove         145
#define XLabs           112
#define XLacos          113
#define XLarc           160
#define XLarcrad        166
#define XLarg           44
#define XLarrow         162
#define XLarrowhd       147
#define XLarrowhead     183
#define XLarrowht       167
#define XLarrowwid      168
#define XLasin          114
#define XLat            55
#define XLatan2         127
#define XLbelow         146
#define XLbox           157
#define XLboxht         169
#define XLboxrad        170
#define XLboxwid        171
#define XLccw           6
#define XLcenter        142
#define XLchop          60
#define XLcircle        158
#define XLcirclerad     172
#define XLcoloneq       30
#define XLcontinue      59
#define XLcorner        87
#define XLcos           115
#define XLcw            5
#define XLdashed        134
#define XLdashwid       173
#define XLdefine        79
#define XLdiameter      110
#define XLdirecton      151
#define XLdiveq         34
#define XLdo            85
#define XLdotted        133
#define XLdown          153
#define XLellipse       159
#define XLellipseht     174
#define XLellipsewid    175
#define XLelse          83
#define XLenvvar        165
#define XLexp           116
#define XLexpe          117
#define XLfillval       184
#define XLfloat         37
#define XLfloor         125
#define XLfrom          53
#define XLfunc1         111
#define XLfunc2         126
#define XLheight        107
#define XLint           118
#define XLinvis         135
#define XLlastenv       188
#define XLlastsc        182
#define XLleft          155
#define XLline          161
#define XLlineht        176
#define XLlinethick     185
#define XLlinetype      131
#define XLlinewid       177
#define XLljust         143
#define XLlog           119
#define XLloge          120
#define XLcompare       99
#define XLmax           128
#define XLmaxpsht       186
#define XLmaxpswid      187
#define XLmin           129
#define XLminuseq       32
#define XLmove          163
#define XLmoveht        178
#define XLmovewid       179
#define XLmulteq        33
#define XLname          38
#define XLoutlined      139
#define XLparam         106
#define XLpath          136
#define XLpluseq        31
#define XLpmod          130
#define XLprimitiv      156
#define XLradius        109
#define XLremeq         35
#define XLright         154
#define XLrjust         144
#define XLscale         188
#define XLshaded        140
#define XLsign          121
#define XLsin           122
#define XLsolid         132
#define XLspline        164
#define XLsqrt          123
#define XLstring        41
#define XLtan           124
#define XLtextht        180
#define XLtextoffset    181
#define XLtextpos       141
#define XLtextwid       182
#define XLthen          58
#define XLto            54
#define XLaTeX          40
#define XLundefine      80
#define XLup            152
#define XLwidth         108
#define XNEQ            101
#define XNOT            16
#define XNL             14
#define XRBRACE         24
#define XRIGHTHEAD      149
#define XSEMICOLON      14
#define XSTAR           9
#define XSTART          45
#define XANDAND         17
#define XOROR           18
#define Xlparen         7
#define Xrparen         8
#define Xplus           10
#define Xcomma          19
#define Xminus          11
#define XSLASH          12

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
    } UEMPTY6;
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
FILE *redirect;   /*G asmname 'redi_rect'; G*/
/*D log: text; D*/
/*DG asmname 'log_file'; GD*/

mstring infname;   /* name of current input file       */
mstring outfnam;   /* name of current output file     */
/*X infname: string; X*/

boolean inputeof;   /* end of input flag                  */
int argct;   /* argument counter for options     */
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
boolean inlogic;   /* set < to <^ in logical context     */
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
short freex;   /* next free location                 */
Char *tmpbuf;   /* buffer for snprintf or sprintf     */
double scale, fsc;   /* scale factor and final scale factor*/
int splcount, spltot;   /* spline depth counter               */
primitive *snode;   /* temporary node storage             */
boolean sfill;   /* fill flag for linear objects       */
double vfill;   /* fill value */
nametype *sshade, *soutline;   /* temp values for linear objects     */
double lastfillval;   /* last-used fill density             */
double lastthick;   /* last-used line thickness           */
int printstate;   /* for passing output state info      */

/* Global tables for easy C conversion.
   Alternative: use run-time space    */
short lr[lrmax + 1]={
0,   5,1,   0,  0,   0,  10,6,   0, -1,  15,3735,1,   1,  1,
0,  20,1,  45,  7,  25, 540,2,  16,151,  30, 535,2, 165,169,
35, 525,2,  38,170,  40, 515,2,  37,171,  45, 415,2,   7,172,
50, 325,2,  81,176,  55, 315,2, 111,178,  60, 305,2, 126,179,
65, 285,2,  39,153,  70, 210,2,  87,147,  75, 205,2,  67,149,
80, 180,2,  69,132,  85, 175,2,  27,158,  90,  95,2,  23,159,
0,4468,4,   0,  7, 100, 630,1,  10,  2, 105, 575,1,  11, 66,
110, 540,1,  16,151, 115, 535,1, 165,169, 120, 525,1,  38,170,
125, 515,1,  37,171, 130, 415,1,   7,172, 135, 325,1,  81,176,
140, 315,1, 111,178, 145, 305,1, 126,179, 150, 285,1,  39,153,
155, 210,1,  87,147, 160, 205,1,  67,149, 165, 180,1,  69,132,
170, 175,1,  27,158,   0,  95,1,  23,159, 100, 630,1,  10,  2,
0,4268,3,   0,132,   0, 190,1,  68,  3, 195, 200,2,  69,131,
0,4473,4,   0,130,   0,4268,3,   2,131,   0, 300,3,   0,149,
215,1685,1,  62,  4, 220, 285,1,  39,153, 225, 180,1,  69,132,
165, 230,1,  37,157,   0, 185,3,   0,-157, 240, 275,1, 156,  5,
245, 270,1,  26,134, 250, 265,1,  41,135,   0, 255,1,  21,136,
0, 260,1,  22,  6,   0,4280,3,   1,136,   0,4280,3,   0,-135,
0,4280,3,   0,-134,   0,4280,3,   0,-133,   0,4420,3,   1,154,
290, 295,2,  21, 33,   0,3828,6,   0, 32, 100, 630,1,  10,  2,
0,4300,3,   0,-142,   0, 310,1,   7,  7, 100, 630,1,  10,  2,
0, 320,1,   7,  7, 100, 630,1,  10,  2,   0, 330,1,   7,  7,
95,1635,1,   8,  8, 340, 385,2, 106,175, 345, 360,2,  25,155,
350, 355,2,  87,146,   0,4478,4,   0,145,   0, 300,3,   1,146,
220, 375,1,  39,  9, 240, 275,1, 156,  5,   0,4420,3,   3,156,
290, 295,2,  21, 33,   0,4420,3,   3,155,   0,4460,3,   1,175,
395, 915,1,  71, 10, 400, 910,1,  72,174, 405, 920,1,   9,143,
0, 410,1,  12,144, 110, 540,1,  16, 11, 420,1285,1,  38, 12,
425,1250,1, 165, 62, 430, 630,1,  10, 65, 435, 575,1,  11, 66,
440, 415,1,   7,140, 445, 210,1,  87,147, 450, 205,1,  67,149,
455, 540,1,  16,151, 460, 770,1,  41, 58, 465, 285,1,  39,153,
470, 515,1,  37,171, 475, 325,1,  81,176, 480, 315,1, 111,178,
485, 305,1, 126,179, 160, 490,1,  86, 86,   0, 495,1,   7,  7,
0, 500,1,  41, 13, 505, 510,2,  19, 87,   0,4483,4,   0, 86,
100, 630,1,  10,  2, 520, 230,4,  68,157,   0,4488,4,   0,171,
290, 295,2,  21, 33,   0,4460,3,   1,170,   0,4460,3,   0,169,
115, 535,1, 165, 14,   0,4392,3,   1,151, 555, 560,2,  15,152,
0,4493,4,   0,150, 110, 540,1,  16, 11,   0,4392,3,   2,152,
0,3788,3,   0,-13, 110, 540,1,  16, 11, 585, 620,2,   9, 14,
590, 610,2,  12, 15, 595, 600,2,  13, 16,   0,4498,4,   0, 66,
110, 540,1,  16, 11,   0,3788,3,   2, 16, 110, 540,1,  16, 11,
0,3788,3,   2, 15, 110, 540,1,  16, 11,   0,3788,3,   2, 14,
110, 540,1,  16, 11, 640, 620,2,   9, 14, 645, 610,2,  12, 15,
650, 600,2,  13, 16,   0,4503,4,   0, 65, 660, 620,2,   9, 14,
665, 610,2,  12, 15, 670, 600,2,  13, 16,   0,4508,4,   0, 64,
680, 745,2,  19, 89, 685, 720,2,  10, 67, 690, 695,2,  11, 68,
0,4513,4,   0, 88, 110, 540,1,  16, 11, 705, 620,2,   9, 14,
710, 610,2,  12, 15, 715, 600,2,  13, 16,   0,4518,4,   0, 68,
110, 540,1,  16, 11, 730, 620,2,   9, 14, 735, 610,2,  12, 15,
740, 600,2,  13, 16,   0,4523,4,   0, 67, 100, 630,1,  10,  2,
0,4220,3,   2, 89,   0, 760,3,   4, 87,   0, 765,1,   8, 15,
0,4032,3,   1,-59,   0,4032,3,   0, 58,   0,3964,3,   0,-56,
785, 810,2,   4,163, 790, 795,2,  10, 57,   0,4528,4,   0,166,
800, 770,1,  41, 16,   0, 490,1,  86, 86,   0,3964,3,   2, 57,
800, 770,1,  41, 16, 820, 795,2,  10, 57,   0,4533,4,   0,163,
830, 835,2,  99,167,   0,4538,4,   0,162, 840, 630,1,  10, 12,
845, 575,1,  11, 66, 850, 770,1,  41, 58, 855, 540,1,  16,151,
110, 490,1,  86, 86, 865, 795,2,  10, 57,   0,4543,4,   0,168,
875, 720,2,  10, 67, 880, 695,2,  11, 68,   0,4548,4,   0,167,
890, 920,2,   9,143, 895, 410,2,  12,144, 900, 915,2,  71,173,
905, 910,2,  72,174,   0,4292,6,   0,137,   0,4460,3,   1,174,
0,4460,3,   1,-173, 110, 540,1,  16, 11,   0,4300,3,   2,143,
935,1130,2,  10,138, 940, 945,2,  11,139,   0,4553,4,   0,126,
950, 970,1,   7, 17, 955, 210,1,  87,147, 215, 205,1,  67,149,
965, 355,2,  87,146, 350, 360,2,  25,155, 975, 630,1,  10,  2,
980, 575,1,  11, 66, 985, 415,1,   7,140, 990, 210,1,  87,147,
995, 205,1,  67,149,1000, 540,1,  16,151,1005, 285,1,  39,153,
1010, 535,1, 165,169,1015, 525,1,  38,170,1020, 515,1,  37,171,
1025, 325,1,  81,176,1030, 315,1, 111,178, 160, 305,1, 126,179,
1040,1185,1,  65, 18,1045,1150,1,  62, 36,1050,1085,1,   4, 37,
1055,1065,1,  19,125,1060, 720,1,  10, 67,   0, 695,1,  11, 68,
100, 630,1,  10,  2,1075, 720,2,  10, 67,1080, 695,2,  11, 68,
0,4558,4,   0,125, 975, 630,1,  10,  2,   0,3856,3,   0,-34,
0,1100,1,  19, 19, 975, 630,1,  10,  2,   0,1110,1,  99, 20,
0,4292,6,   0,137,1120,1130,2,  10,138,1125, 945,2,  11,139,
0,4563,4,   0, 37, 950, 970,1,   7, 17,1140, 920,2,   9,143,
1145, 410,2,  12,144,   0,4568,4,   0,138,   0,1155,1,  63, 21,
0,1160,1,  64, 22,   0,1165,1,  65, 23, 975, 630,1,  10,  2,
0,1175,1,  66, 24, 975, 630,1,  10,  2,   0,3856,3,   7, 36,
975, 630,1,  10,  2,   0,1195,1,  66, 24, 975, 630,1,  10,  2,
0,3856,3,   4, 35,1210,1230,1,   8, 25,   0,1215,1,  19,141,
975, 630,1,  10,  2,   0,1225,1,   8, 15,   0,4300,3,   4,141,
0,4300,3,   2,140,1240, 920,2,   9,143,1245, 410,2,  12,144,
0,4573,4,   0,139,1255,1260,2,  29, 62,   0, 535,4,   0,169,
1265, 630,1,  10,  2,1270, 575,1,  11, 66,1275,1285,1,  38, 60,
1280,1250,1, 165, 62, 120, 540,1,  16,151, 290, 295,2,  21, 33,
1295,1300,2,  29, 60,   0, 530,4,   0,170,1265, 630,1,  10,  2,
0,4040,3,   3, 61,1315, 720,2,  10, 67,1320, 695,2,  11, 68,
0,4578,4,   0, 60,   0,4040,3,   2, 63,1335, 720,2,  10, 67,
1340, 695,2,  11, 68,   0,4583,4,   0, 62,   0,4444,3,   0,-160,
1355,1185,2,  65, 35,1360,1150,2,  62, 36,1365,1385,2,   4, 37,
1370,1065,2,  19,125,1375, 720,2,  10, 67,1380, 695,2,  11, 68,
0,4588,4,   0,165,1390, 630,1,  10,  2,1395, 575,1,  11, 66,
1400, 415,1,   7,140,1405, 540,1,  16,151,1410, 210,1,  87,147,
1415, 205,1,  67,149,1420, 535,1, 165,169,1425, 525,1,  38,170,
1430, 515,1,  37,171,1435, 325,1,  81,176,1440, 315,1, 111,178,
1445, 305,1, 126,179, 160, 285,1,  39,153,1455,1185,2,  65, 35,
1460,1150,2,  62, 36,1465,1085,2,   4, 37,1470, 720,2,  10, 67,
1475, 695,2,  11, 68,1480,1065,2,  19,125,   0,4593,4,   0,164,
0,3924,3,   0,-38,1495,1500,2,  17,161,   0,4598,4,   0, 71,
1505, 630,1,  10, 12,1510, 575,1,  11, 66,1515, 770,1,  41, 58,
105, 490,1,  86, 86,1370,1525,2,   4,164, 100, 630,1,  10,  2,
1535, 720,2,  10, 67,1480, 695,2,  11, 68,   0,4444,3,   2,161,
1550,1585,1,   8, 25,   0,1555,1,  19, 39,1560,1570,1,  38, 26,
0,1565,1, 165, 62,   0,1260,1,  29, 27, 290, 295,2,  21, 33,
0,1300,1,  29, 27,   0,3924,3,   2, 39,   0,4460,3,   2,180,
1595,1615,1,   8, 28,   0,1600,1,  18, 72,1505, 630,1,  10, 12,
1610,1500,2,  17,161,   0,4603,4,   0, 72,   0,4460,3,   2,172,
0,4300,3,   2,144,1055,1630,1,   8, 29,   0,4460,3,   3,177,
0,4460,3,   2,176,1055,1645,1,   8, 29,   0,4460,3,   3,178,
1055,1655,1,  19, 30, 100, 630,1,  10,  2,1055,1665,1,   8, 29,
0,4460,3,   5,179,1055,1675,1,  22, 31,   0,3828,3,   2, 33,
0,4420,3,   1,153, 220, 285,1,  39,  9,1695, 360,2,  25,155,
0,4608,4,   0,148,1705, 360,2,  25,155,   0,4613,4,   0,147,
1055,1715,1,  28, 32,   0, 185,3,   2,158,1055,1725,1,  24, 33,
0, 185,3,   2,159,1735, 620,2,   9, 14,1740, 610,2,  12, 15,
1745, 600,2,  13, 16,1750, 540,2,  16,151,1755, 535,2, 165,169,
1760, 525,2,  38,170,1765, 515,2,  37,171,1770, 415,2,   7,172,
1775, 325,2,  81,176,1780, 315,2, 111,178,1785, 305,2, 126,179,
1790, 285,2,  39,153,1795, 210,2,  87,147,1800, 205,2,  67,149,
1805, 180,2,  69,132,1810, 175,2,  27,158,1815,  95,2,  23,159,
0,4618,4,   0,  8,1825, 620,2,   9, 14,1830, 610,2,  12, 15,
1835, 600,2,  13, 16,   0,4623,4,   0,  9,1845,1855,1,  14, 34,
0,1850,1,   3,  6,   0,3740,3,   0, -6,   0,3740,3,   0, -5,
1865,3145,2,  39, 18,1870,3130,2, 151, 20,1875,3125,2,  40, 21,
1880,3050,2,  78, 27,1885,3035,2,  76, 28,1890,2480,2,  73, 40,
1895,2445,2,  75, 43,1900,2430,2,  77, 45,1905,2415,2,  74, 46,
1910,2360,2,  80, 48,1915,3110,6,  23, 29,1920,2225,2,  59,116,
1925,1570,2,  38, 60,1930,1565,2, 165, 62,1935,2205,2,  79, 84,
1940,2110,2,  84, 73,1945,2005,2, 156,118,1950,2185,6,  82, 70,
1955,1975,6,  21,117,1960,1975,6,  26,117,1965, 770,2,  41, 58,
1970, 490,2,  86, 86,   0,3760,6,   0, 10,1980,1990,1,  21, 35,
0,1985,1,  26,121,   0,2330,3,   1,121,1865,3145,2,  39, 18,
2000, 795,2,  10, 57,   0,4628,4,   0,119,2010, 630,2,  10, 65,
2015, 575,2,  11, 66,2020, 540,2,  16,151,2025, 535,2, 165,169,
2030, 525,2,  38,170,2035, 515,2,  37,171,2040, 415,2,   7,172,
2045, 325,2,  81,176,2050, 315,2, 111,178,2055, 305,2, 126,179,
2060, 285,2,  39,153,2065, 210,2,  87,147,2070, 205,2,  67,149,
2075, 180,2,  69,132,2080, 175,2,  27,158,2085,  95,2,  23,159,
0,4236,6,   0,122,2095, 720,2,  10, 67,2100, 695,2,  11, 68,
0,4633,4,   0,123,   0,2330,3,   1,118,1560,1570,1,  38, 26,
1550,2120,1,  54, 36, 100, 630,1,  10,  2,2130, 720,1,  10, 37,
2135, 695,1,  11, 68,2140,2175,1,  85, 75,   0,2145,1,  57, 77,
2150,2155,2,   9, 78,   0,4638,4,   0, 77,   0,2160,3,   1, 78,
100, 630,1,  10,  2,1055,2170,1,  85, 38,   0,2180,3,   2, 76,
0,2180,3,   0, 75,   0,2340,3,   4, 73,   0,2190,1,  82, 39,
1505, 630,1,  10, 12,1595,2200,1,  58, 40,   0,2350,3,   3, 69,
2210,2220,1,  38, 41,   0,2215,1,  39, 85,   0,2380,3,   1, 85,
0,2380,3,   1, 84,   0,4228,3,   0,116,2235,2315,1,  87, 42,
2240,2290,1,  55,115,2245,2265,1,  25,128,2250, 630,1,  10, 65,
2255, 575,1,  11, 66, 990, 415,1,   7,140,1055,1065,1,  19, 30,
220,2280,1,  39,  9, 240, 275,1, 156,  5,   0,2230,3,   3,129,
290, 295,2,  21, 33,   0,2230,3,   3,128, 975, 630,1,  10,  2,
0,4228,3,   2,115,   0,2305,1,  55, 43, 975, 630,1,  10,  2,
0,4228,3,   3,114, 210,2320,1,  55, 44, 975, 630,1,  10,  2,
0,4228,3,   3,113,   0,4228,3,   0,-90,1865,3145,2,  39, 18,
0,2345,1,  23, 45,1865,3145,2,  39, 18,   0,2355,1,  23, 45,
1865,3145,2,  39, 18,2365,2375,1,  38, 41,   0,2370,1,  39, 49,
0,3120,3,   1, 49,   0,3120,3,   1, 48,2385,1855,2,  14,  5,
2390,1850,2,   3,  6,   0,3936,6,   0,-50,   0,3936,3,   0,-51,
0,2405,1,  23, 45,   0,2410,1,  24, 46,   0,3120,3,   3,-47,
800, 770,1,  41, 16,2425, 795,2,  10, 57,   0,4643,4,   0, 46,
800, 770,1,  41, 16,2440, 795,2,  10, 57,   0,4648,4,   0, 45,
2450,2455,2, 165, 82,   0,4653,4,   0, 43,   0,2460,3,   0, 82,
2465,2470,2,  19, 83,   0,4658,4,   0, 44,   0,2475,1, 165, 47,
0,2460,3,   2, 83,2485, 630,1,  10, 12,2490, 575,1,  11, 66,
2495, 770,1,  41, 58,2500, 540,1,  16,151,2505, 415,1,   7,140,
2510, 490,1,  86, 86,2515, 535,1, 165,169,2520, 525,1,  38,170,
2525, 515,1,  37,171,2530, 325,1,  81,176,2535, 315,1, 111,178,
2540, 305,1, 126,179,2545, 210,1,  87,147,2550, 205,1,  67,149,
160, 285,1,  39,153,2560, 795,2,  10, 57,2565,2570,2,  99, 80,
0,4208,6,   0, 79, 795,2575,1,  99, 48, 800, 770,1,  41, 16,
2585, 795,2,  10, 57,   0,4663,4,   0, 81,2595, 795,2,  10, 57,
0,4668,4,   0, 80,   0,3120,3,   2, 42,2565,2570,2,  99, 80,
0,3120,3,   2, 41,2620, 720,2,  10, 67,2625, 695,2,  11, 68,
2630,1185,2,  65, 35,2635,1150,2,  62, 36,2640,1085,2,   4, 37,
2560,1065,2,  19,125,   0,3120,3,   2, 40,2655,3015,2,  47, 91,
2660,2995,2,  48, 92,2665,2975,2,  49, 93,2670,2955,2,  50, 94,
2675,2935,2,  51, 95,2680,2915,2,  52, 96,2685,2905,2, 151, 97,
2690,2895,2,  57, 98,2695,2890,2,  58, 99,2700,2880,2, 131,100,
2705,2870,2,  60,101,2710,2860,2,  70,102,2715,2855,2, 147,103,
2720,2850,2,   5,104,2725,2845,2,   6,105,2730,2840,2,  61,106,
2735,2820,2,  53,108,2740,2810,2,  54,109,2745,2800,2,  55,110,
2750,2795,2, 141,111,2755,2780,2, 137,112,2760,2775,2,  56,127,
2765, 770,2,  41, 58,2770, 490,2,  86, 86,   0,4673,4,   0, 30,
0,2230,3,   1,-127, 800, 770,1,  41, 16,2790, 795,2,  10, 57,
0,4678,4,   0,112,   0,4228,3,   1,111, 975, 630,1,  10,  2,
0,4228,3,   2,110, 975, 630,1,  10,  2,   0,4228,3,   2,109,
975, 630,1,  10,  2,   0,4228,3,   2,108,2835, 795,2,  10, 57,
0,4683,4,   0,107,   0,4228,3,   1,106,   0,4228,3,   1,105,
0,4228,3,   1,104,   0,4228,3,   1,103,2010, 630,2,  10, 65,
0,4228,3,   2,102,2010, 630,2,  10, 65,   0,4228,3,   2,101,
2010, 630,2,  10, 65,   0,4228,3,   2,100,   0,4228,3,   1, 99,
975, 630,1,  10,  2,   0,4228,3,   2, 98,2010, 630,2,  10, 65,
0,4228,3,   2, 97, 100, 630,1,  10,  2,2925, 720,2,  10, 67,
2930, 695,2,  11, 68,   0,4688,4,   0, 96, 100, 630,1,  10,  2,
2945, 720,2,  10, 67,2950, 695,2,  11, 68,   0,4693,4,   0, 95,
100, 630,1,  10,  2,2965, 720,2,  10, 67,2970, 695,2,  11, 68,
0,4698,4,   0, 94, 100, 630,1,  10,  2,2985, 720,2,  10, 67,
2990, 695,2,  11, 68,   0,4703,4,   0, 93, 100, 630,1,  10,  2,
3005, 720,2,  10, 67,3010, 695,2,  11, 68,   0,4708,4,   0, 92,
100, 630,1,  10,  2,3025, 720,2,  10, 67,3030, 695,2,  11, 68,
0,4713,4,   0, 91, 800, 770,1,  41, 16,3045, 795,2,  10, 57,
0,4718,4,   0, 28, 800, 770,1,  41, 16,3060, 795,2,  10, 57,
0,4723,4,   0, 27,3070,3080,1,  24, 49,   0,3075,1,  43, 74,
0,2335,3,   1, 74,   0,3816,3,   1,-26,   0,3090,1,  23, 45,
1865,3145,2,  39, 18,3100,3105,2,  83, 53,   0,4728,4,   0, 24,
0,3085,3,   1, 53,   0,3115,1,  23, 45,1865,3145,2,  39, 18,
0,3816,3,   0, 22,   0,3816,3,   0, 21,   0,3816,3,   0, 20,
3140,1555,2,  19, 39,   0,4733,4,   0, 19, 290, 295,2,  21, 33,
0,3155,1,  20, 50,3160,2225,2,  59,116,3165, 630,2,  10, 65,
3170, 575,2,  11, 66,3175,2005,2, 156,118,3180, 415,2,   7,140,
3185, 210,2,  87,147,3190, 205,2,  67,149,3195, 540,2,  16,151,
3200, 770,2,  41, 58,3205, 285,2,  39,153,3210, 535,2, 165,169,
3215, 525,2,  38,170,3220, 515,2,  37,171,3225, 325,2,  81,176,
3230, 315,2, 111,178,3235, 305,2, 126,179,3240, 490,2,  86, 86,
3245, 180,2,  69,132,3250, 175,2,  27,158,3255,  95,2,  23,159,
0,1975,6,   0,117,3265,3015,2,  47, 91,3270,2995,2,  48, 92,
3275,2975,2,  49, 93,3280,2955,2,  50, 94,3285,2935,2,  51, 95,
3290,2915,2,  52, 96,3295,2905,2, 151, 97,3300,2895,2,  57, 98,
3305,2890,2,  58, 99,3310,2880,2, 131,100,3315,2870,2,  60,101,
3320,2860,2,  70,102,3325,2855,2, 147,103,3330,2850,2,   5,104,
3335,2845,2,   6,105,3340,2840,2,  61,106,3345,2820,2,  53,108,
3350,2810,2,  54,109,3355,2800,2,  55,110,3360,2795,2, 141,111,
3365,2780,2, 137,112,3370,2775,2,  56,127,3375, 770,2,  41, 58,
3380, 490,2,  86, 86,   0,4738,4,   0, 31,   0,3816,3,   3, 18,
0,3816,3,   0, 17,   0,3760,3,   0, 11,2385,1855,2,  14,  5,
3410,3145,2,  39, 18,3415,3130,2, 151, 20,3420,3125,2,  40, 21,
3425,3050,2,  78, 27,3430,3035,2,  76, 28,3435,2480,2,  73, 40,
3440,2445,2,  75, 43,3445,2430,2,  77, 45,3450,2415,2,  74, 46,
3455,2360,2,  80, 48,3460,3110,6,  23, 29,3465,2225,2,  59,116,
3470,1570,2,  38, 60,3475,1565,2, 165, 62,3480,2205,2,  79, 84,
3485,2110,2,  84, 73,3490,2005,2, 156,118,3495,2185,6,  82, 70,
3500,1975,6,  21,117,3505,1975,6,  26,117,3510, 770,2,  41, 58,
3515, 490,2,  86, 86,   0,2395,4,   0, 51,   0,3760,3,   2, 12,
0,3530,1,  24, 46,   0,3816,3,   4, 23,2385,1855,2,  14,  5,
0,3545,1,  24, 46,   0,3816,3,   4,-25,2385,1855,2,  14,  5,
0,3560,1,  24, 46,   0,3095,3,   4,-52,2385,1855,2,  14,  5,
0,3065,3,   3,-54,2385,1855,2,  14,  5,   0,3065,3,   2,-55,
2385,1855,2,  14,  5,   0,3595,3,   1,124,   0,3600,1,  22,  6,
0,2330,3,   3,120,1840,3720,1,  46, 51,3615,3715,2,  46,  4,
3620,3145,2,  39, 18,3625,3130,2, 151, 20,3630,3125,2,  40, 21,
3635,3050,2,  78, 27,3640,3035,2,  76, 28,3645,2480,2,  73, 40,
3650,2445,2,  75, 43,3655,2430,2,  77, 45,3660,2415,2,  74, 46,
3665,2360,2,  80, 48,3670,3110,6,  23, 29,3675,2225,2,  59,116,
3680,1570,2,  38, 60,3685,1565,2, 165, 62,3690,2205,2,  79, 84,
3695,2110,2,  84, 73,3700,2005,2, 156,118,3705,2185,6,  82, 70,
3710, 770,2,  41, 58,3255, 490,2,  86, 86,   0,3725,3,   4,  4,
0,3725,3,   3,  3,1845,1855,1,  14, 34,   0,  10,3,   2,  2,
0,   0,0,   2,  0,3744,1860,5,1840    ,3748,2395,5,2380    ,
3752,3610,5,3605    ,3756,3730,5,3725    ,   0,3405,5,   0    ,
3764,3585,5,1990    ,3768,3575,5,2335    ,3772,3565,5,2345    ,
3776,3550,5,2355    ,3780,3535,5,3090    ,3784,3400,5,3115    ,
0,3605,5,   0    ,3792,1730,5,  20    ,3796, 580,5, 575    ,
3800, 635,5, 630    ,3804, 700,5, 695    ,3808, 725,5, 720    ,
3812,1820,5,1730    ,   0, 655,5,   0    ,3820,3520,5,3405    ,
3824,3520,5,3610    ,   0,3395,5,   0    ,3832, 380,5, 375    ,
3836, 530,5, 525    ,3840,1290,5,1285    ,3844,1575,5,1570    ,
3848,2285,5,2280    ,3852,3150,5,3145    ,   0,1680,5,   0    ,
3860,1095,5,1085    ,3864,1105,5,1100    ,3868,1170,5,1165    ,
3872,1180,5,1175    ,3876,1190,5,1185    ,3880,1200,5,1195    ,
3884,1220,5,1215    ,3888,1095,5,1385    ,3892,2295,5,2290    ,
3896,2310,5,2305    ,3900,2325,5,2320    ,3904,2605,5,2480    ,
3908,2805,5,2800    ,3912,2815,5,2810    ,3916,2825,5,2820    ,
3920,3385,5,3155    ,   0,1205,5,   0    ,3928,1545,5, 415    ,
3932,2115,5,2110    ,   0,3135,5,   0    ,3940,3525,5,3400    ,
3944,3540,5,3535    ,3948,3555,5,3550    ,3952,3570,5,3565    ,
3956,3580,5,3575    ,3960,3590,5,3585    ,   0,2400,5,   0    ,
3968, 780,5, 415    ,3972, 815,5, 810    ,3976, 860,5, 835    ,
3980, 780,5,1500    ,3984, 780,5,1600    ,3988, 780,5,2190    ,
3992,2420,5,2415    ,3996,2435,5,2430    ,4000,2555,5,2480    ,
4004,2590,5,2570    ,4008,2580,5,2575    ,4012,2830,5,2650    ,
4016,2785,5,2780    ,4020,3040,5,3035    ,4024,3055,5,3050    ,
4028,2830,5,3260    ,   0,1995,5,   0    ,4036, 805,5, 795    ,
0, 775,5,   0    ,4044,1325,5,1260    ,4048,1305,5,1300    ,
4052,1580,5,1555    ,   0,1485,5,   0    ,4060,1720,5,  95    ,
4064,1710,5, 175    ,4068,1670,5, 295    ,4072,1650,5, 310    ,
4076,1640,5, 320    ,4080,1625,5, 330    ,4084,1350,5, 415    ,
4088, 675,5, 510    ,4092, 675,5, 745    ,4096, 870,5, 835    ,
4100,1070,5,1065    ,4104,1330,5,1260    ,4108,1310,5,1300    ,
4112,1450,5,1385    ,4116,1520,5,1500    ,4120,1530,5,1525    ,
4124,1520,5,1600    ,4128,1660,5,1655    ,4132,2090,5,2005    ,
4136,2125,5,2120    ,4140,2165,5,2160    ,4144,1520,5,2190    ,
4148,2260,5,2230    ,4152,2615,5,2480    ,4156,2090,5,2860    ,
4160,2090,5,2870    ,4164,2090,5,2880    ,4168,2260,5,2895    ,
4172,2090,5,2905    ,4176,2920,5,2915    ,4180,2940,5,2935    ,
4184,2960,5,2955    ,4188,2980,5,2975    ,4192,3000,5,2995    ,
4196,3020,5,3015    ,   0,1035,5,   0    ,4204,2195,5,2190    ,
0,1590,5,   0    ,4212,2610,5,2605    ,4216,2645,5,2615    ,
0,2600,5,   0    ,4224, 750,5, 745    ,   0, 755,5,   0    ,
4232,3260,5,3155    ,   0,2650,5,   0    ,4240,2865,5,2860    ,
4244,2875,5,2870    ,4248,2885,5,2880    ,4252,2910,5,2905    ,
0,2105,5,   0    ,4260,2300,5,2230    ,4264,2900,5,2895    ,
0,1090,5,   0    ,4272, 365,5, 360    ,4276,2270,5,2265    ,
0, 235,5,   0    ,4284, 370,5, 365    ,4288,2275,5,2270    ,
0, 280,5,   0    ,4296,1115,5,1110    ,   0, 930,5,   0    ,
4304, 885,5, 415    ,4308,1235,5, 945    ,4312, 885,5, 970    ,
4316, 885,5,1085    ,4320, 885,5,1100    ,4324,1135,5,1130    ,
4328, 885,5,1165    ,4332, 885,5,1175    ,4336, 885,5,1185    ,
4340, 885,5,1195    ,4344, 885,5,1215    ,4348, 885,5,1385    ,
4352, 885,5,2230    ,4356, 885,5,2290    ,4360, 885,5,2305    ,
4364, 885,5,2320    ,4368, 885,5,2480    ,4372, 885,5,2800    ,
4376, 885,5,2810    ,4380, 885,5,2820    ,4384, 885,5,2895    ,
4388, 885,5,3155    ,   0, 390,5,   0    ,4396,1620,5, 410    ,
4400, 565,5, 560    ,4404, 605,5, 600    ,4408, 615,5, 610    ,
4412, 625,5, 620    ,4416, 925,5, 920    ,   0, 570,5,   0    ,
4424,1700,5, 210    ,4428, 960,5, 945    ,4432, 960,5,1130    ,
4436,1690,5,1685    ,4440,1700,5,2315    ,   0, 335,5,   0    ,
4448,1605,5,1600    ,   0,1490,5,   0    ,4456,1540,5,1500    ,
0,1345,5,   0    ,4464, 545,5, 540    ,   0, 550,5,   0    ,
0,1840,3,   0,  7,   0,4268,3,   1,130,   0, 300,3,   0,145,
0, 760,3,   2, 86,   0,4460,3,   0,-171,   0,4392,3,   0,-150,
0,4056,3,   1, 66,   0,4056,3,   1, 65,   0,4056,3,   0,-64,
0,4220,3,   0, 88,   0,4056,3,   2, 68,   0,4056,3,   2, 67,
0, 825,3,   0,-166,   0,4452,3,   2,163,   0,4452,3,   0,162,
0, 825,3,   2,168,   0, 825,3,   2,167,   0,4256,3,   1,126,
0,4256,3,   2,125,   0,3856,3,   6, 37,   0,4292,3,   2,138,
0,4292,3,   2,139,   0,4040,3,   3, 60,   0,4040,3,   2, 62,
0, 825,3,   0,-165,   0,4452,3,   2,164,   0,4200,3,   0,-71,
0,4200,3,   2, 72,   0, 300,3,   2,148,   0, 300,3,   1,147,
0,1840,3,   1,  8,   0,1840,3,   2,  9,   0,2330,3,   0,119,
0,4236,3,   0,-123,   0,2160,3,   0,-77,   0,3120,3,   1, 46,
0,3120,3,   1, 45,   0,3120,3,   0, 43,   0,3120,3,   1,-44,
0,4208,3,   2, 81,   0,4208,3,   1, 80,   0,3390,3,   0, 30,
0,4228,3,   2,112,   0,4228,3,   1,107,   0,4228,3,   2, 96,
0,4228,3,   2, 95,   0,4228,3,   2, 94,   0,4228,3,   2, 93,
0,4228,3,   2, 92,   0,4228,3,   2, 91,   0,3816,3,   1, 28,
0,3816,3,   1, 27,   0,3816,3,   0,-24,   0,3816,3,   0, 19,
0,3390,3,   3, 31

};
lxinx entryhp[ordMAXCH + 1]={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,
3,0,0,0,4,5,0,6,8,88,0,0,0,0,0,0,0,0,0,0,89,0,90,101,102,0,0,0,0,0,0,0,0,0,103,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,106,0,0,0,0,0,107,140,164,209,236,256,0,
273,279,0,0,289,315,334,335,343,0,353,373,411,439,0,447,0,0,0,0,455,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0};
lxinx lxhp[lxmax + 1]={
0,0,0,0,0,0,0,0,83,76,69,64,58,55,49,40,30,28,21,0,0,26,23,24,25,0,27,0,29,0,
0,37,34,0,35,36,0,38,39,0,45,42,43,44,0,46,47,48,0,0,52,0,53,54,0,56,57,0,60,
0,61,62,63,0,67,66,0,68,0,70,71,72,73,74,75,0,77,78,79,82,81,0,0,84,85,86,87,
0,0,0,100,0,93,94,95,96,97,98,99,0,0,0,0,104,105,0,0,136,134,133,118,116,113,
114,115,0,117,0,130,120,121,122,126,124,125,0,128,0,129,0,131,132,0,0,135,0,
138,0,139,0,156,143,0,153,145,152,150,148,149,0,151,0,0,154,155,0,162,158,159,
160,161,0,163,0,208,202,200,193,170,0,185,181,176,175,0,0,177,178,179,180,0,
182,183,184,0,186,191,188,189,190,0,192,0,194,195,196,197,198,199,0,201,0,203,
204,207,206,0,0,0,229,225,219,213,216,215,0,217,218,0,220,221,222,223,224,0,
226,227,228,0,230,231,235,233,234,0,0,244,243,239,242,241,0,0,0,247,246,0,248,
249,250,251,255,253,254,0,0,266,263,262,260,261,0,0,264,265,0,267,268,272,270,
271,0,0,275,0,276,277,278,0,0,281,0,283,284,285,286,287,288,0,313,311,299,296,
294,295,0,297,298,0,300,301,310,306,304,305,0,307,308,309,0,0,312,0,314,0,326,
325,318,319,320,324,322,323,0,0,0,327,328,329,333,331,332,0,0,0,0,337,338,339,
340,341,342,0,351,349,346,347,348,0,350,0,352,0,367,0,364,361,358,359,360,0,
362,363,0,365,366,0,370,369,0,371,372,0,409,405,401,398,395,386,384,381,382,
383,0,385,0,392,388,389,390,391,0,393,394,0,396,397,0,400,0,0,402,403,404,0,
406,407,408,0,410,0,438,425,416,415,0,424,418,419,420,421,422,423,0,0,426,427,
437,432,430,431,0,433,434,435,436,0,0,0,441,0,442,443,444,445,446,0,454,449,
452,451,0,453,0,0,0};
lxinx lxnp[lxmax + 1]={
0,0,0,0,0,0,7,0,9,10,11,12,13,14,15,16,17,18,19,20,0,22,0,0,0,0,0,0,0,0,31,32,
33,0,0,0,0,0,0,0,41,0,0,0,0,0,0,0,0,50,51,0,0,0,0,0,0,0,59,0,0,0,0,0,65,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,80,0,0,0,0,0,0,0,0,0,0,91,92,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,108,109,110,111,112,0,0,0,0,0,0,119,0,0,0,123,0,0,0,127,0,0,0,0,0,0,0,
0,0,137,0,0,0,141,142,0,144,0,146,147,0,0,0,0,0,0,0,0,0,157,0,0,0,0,0,0,0,165,
166,167,168,169,0,171,172,173,174,0,0,0,0,0,0,0,0,0,0,0,0,187,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,205,0,0,0,0,210,211,212,0,214,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,232,0,0,0,0,237,238,0,240,0,0,0,0,245,0,0,0,0,0,0,252,0,0,0,0,257,258,
259,0,0,0,0,0,0,0,0,0,269,0,0,0,0,274,0,0,0,0,0,280,0,282,0,0,0,0,0,0,0,290,
291,292,293,0,0,0,0,0,0,0,0,302,303,0,0,0,0,0,0,0,0,0,0,0,0,316,317,0,0,0,321,
0,0,0,0,0,0,0,0,330,0,0,0,0,0,336,0,0,0,0,0,0,0,344,345,0,0,0,0,0,0,0,0,354,
355,356,357,0,0,0,0,0,0,0,0,0,0,368,0,0,0,0,0,374,375,376,377,378,379,380,0,
0,0,0,0,0,387,0,0,0,0,0,0,0,0,0,0,0,399,0,0,0,0,0,0,0,0,0,0,0,0,412,413,414,
0,0,417,0,0,0,0,0,0,0,0,0,0,428,429,0,0,0,0,0,0,0,0,0,0,440,0,0,0,0,0,0,0,448,
0,450,0,0,0,0,0,0};
symbol lxtv[lxmax + 1]={
0,101,35,17,33,31,32,149,93,98,0,94,0,95,92,94,93,92,95,71,72,0,0,108,0,108,
0,95,0,92,89,0,0,91,0,0,96,0,0,93,0,0,0,0,94,109,0,0,109,88,0,90,0,0,92,0,0,
95,0,107,0,0,0,107,0,0,97,0,94,0,0,110,0,0,0,110,0,0,0,0,0,98,98,0,93,0,0,93,
34,30,148,103,0,0,0,0,0,0,0,99,150,100,102,0,0,67,26,0,0,0,0,0,55,0,0,127,0,
114,160,0,0,162,0,0,0,168,0,167,0,183,0,0,166,66,0,113,0,112,0,145,0,0,57,0,
157,0,0,0,0,171,0,170,169,0,0,93,0,0,0,0,0,65,0,146,0,0,0,0,0,5,0,0,0,0,115,
74,0,0,0,0,59,0,0,0,78,0,138,0,138,0,138,0,138,0,0,0,158,0,0,172,0,60,0,0,0,
0,142,142,6,0,0,0,85,0,0,153,0,0,133,0,50,0,0,0,50,0,0,0,79,0,0,0,0,0,173,134,
0,0,0,0,116,117,76,97,0,0,83,0,0,0,159,0,0,0,175,174,0,0,0,0,0,53,84,0,0,125,
0,70,0,0,0,184,70,0,47,0,0,0,47,82,0,118,0,0,135,0,0,0,135,0,0,0,0,0,119,120,
0,0,143,0,161,0,0,0,0,177,0,0,0,185,176,0,155,0,69,0,0,0,0,163,0,0,0,179,178,
129,128,0,0,0,0,0,187,186,68,62,0,0,0,0,0,139,139,0,0,0,0,0,73,0,130,0,136,0,
68,0,0,0,0,0,144,0,0,154,0,0,75,49,0,81,0,0,49,0,0,77,0,0,0,0,68,0,0,96,0,123,
0,0,0,0,0,86,0,0,164,0,0,132,0,122,121,0,0,140,140,0,0,188,52,0,61,0,0,68,54,
92,63,0,0,51,0,0,0,51,58,0,0,0,0,0,0,182,0,0,0,0,181,180,124,0,152,0,0,80,0,
0,80,0,0,48,0,56,0,48,64,18};
symbol entrytv[ordMAXCH + 1]={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,41,42,44,
13,36,28,7,8,9,10,19,11,25,12,0,0,0,0,0,0,0,0,0,0,20,14,4,29,105,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,0,22,15,0,27,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,23,0,24,43,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
Char lxch[lxmax + 1]={
'0','=','=','&','=','=','=','>','b','c','d','e','h','l','n','r','s','t','w',
'x','y','e','i','d','t','h','s','t','o','p','e','o','t','w','a','r','t','u',
't','h','a','i','g','h','t','d','i','u','s','e','o','w','r','t','h','e','f',
't','e','t','i','g','h','t','a','n','d','s','t','i','a','m','e','t','e','r',
'e','n','t','e','r','e','r','o','t','t','o','m','=','=','-','=','c','o','m',
'p','a','r','e','>','>','=','=','e','r','e',']','b','c','n','r','s','t','a',
'n','2','i','n','c','r','o','w','h','w','i','d','e','t','a','d','r','a','d',
'd','o','s','o','s','v','e','e','o','y','t','x','h','r','w','i','d','a','d',
't','t','o','m','l','t','w','e','e','n','o','w','c','e','h','i','o','w','l',
'm','n','p','s','y','t','i','n','u','e','m','a','n','d','o','r','u','r','e',
'd','e','d','r','c','l','e','r','a','d','o','p','n','t','e','r','e','r','w',
'a','e','i','o','t','w','n','t','e','d','a','m','e','t','e','r','f','i','n',
'e','s','h','e','w','i','d','d','l','n','x','e','p','e','c','d','l','s','e',
'i','p','s','e','h','w','i','d','t','i','l','o','r','o','m','r','o','o','r',
'l','l','e','v','a','l','d','e','t','i','g','h','t','f','n','t','v','i','s',
'i','b','l','e','a','e','i','j','o','g','e','u','s','t','n','e','h','t','w',
'i','d','h','i','c','k','t','f','t','s','t','a','i','o','v','e','h','w','i',
'd','t','n','x','p','s','h','w','i','d','t','d','f','u','t','l','i','n','e',
'd','a','m','r','i','n','t','o','d','t','h','a','d','e','i','j','u','s','t',
'g','h','t','s','e','t','d','n','d','i','u','s','a','c','h','i','o','p','q',
't','a','r','t','r','t','l','r','i','n','t','f','i','n','e','l','i','d','g',
'n','n','a','d','e','d','a','l','e','d','m','e','a','e','h','o','p','e','i',
'c','k','n','e','s','s','n','x','t','h','o','w','i','d','f','f','s','e','t',
't','n','n','p','d','e','f','i','n','e','a','i','d','t','h','t','h','y','|'};
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

/*DGHM function ordp(p:pointer): integer; forward; MHGD*/
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

#ifndef SAFE_MODE
void pointinput(nametype *txt);

void pointoutput(boolean nw, nametype *txt, int *ier);

#endif
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

void getlinshade(primitive *n, primitive **tn, nametype **ss,
			nametype **so, double *f, boolean *sf);

int ahlex(int atyp);

int ahnum(int atyp);

int pahlex(int atyp, int alex);

int pahnum(int atyp, int anum);

double ahoffset(primitive *node);

void dahead(postype point, postype shaft, double ht, double wid,
		   double ltp, postype *P, postype *L, postype *R, postype *Q,
		   double *x, double *y);

void startarc(primitive *n, postype X0, double *h, double *w,
		     postype *X1);

void endarc(primitive *n, postype X0, double *h, double *w,
		   postype *X1);

postype arcstart(primitive *n);

postype arcend(primitive *n);


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
	  WITH->carray[inx] == ' ' || WITH->carray[inx] == crch ||
	  WITH->carray[inx] == nlch)
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

/*DUBX function  ordp(var p:primitivep ): integer; external; XBUD*/
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
      XLaTeX: write(iou,'<<LaTeX>>');
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
         XLellipse,XLaTeX: i := 9;
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
            write(log,' ahlex(atype)=',ahlex(atype):1);
            write(log,' ahnum(atype)=',ahnum(atype):1)
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
            write(log,' ahlex(atype)=',ahlex(atype):1);
            write(log,' ahnum(atype)=',ahnum(atype):1)
            end;
         XLaTeX,XLabel: ;
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
    }
    r = (*p)->parent;
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
      deletename(&WITH->UU.UEMPTY6.vars);
      if (WITH->UU.UEMPTY6.env != NULL)
	Free(WITH->UU.UEMPTY6.env);
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

    case XLaTeX:
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

  case XEQ:
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
/* p2c: dpic.p, line 911:
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
     writeln(log,' nil segment(s)')
     else writeln(log,' i=',i:1,' j=',j:1,' eqstring=',k:1); D*/
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
    np = findname(eb->UU.UEMPTY6.vars, chb, chbufx, length, last);
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
  /* outbuf is freeseg */
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
    freeseg = *outbuf;
  }
  /* for i := 0 to ll-1 do outbuf^[freex+i] := srcbuf^[px+i]; */
  j = px - freex;
  FORLIM = freex + ll;
  for (i = freex; i < FORLIM; i++)
    (*outbuf)[i] = srcbuf[j + i];
  sp->segmnt = *outbuf;
  sp->seginx = freex;
  sp->len = ll;
  j = bval(*outbuf);
  putbval(*outbuf, j + 1);
  freex += ll;
  /*D; if debuglevel > 0 then begin writeln(log,
     'addstring to strptr ',ordp(sp):1,': segmnt=',ordp(freeseg):1,' seginx= ',
      sp^.seginx:1, ' links= ', bval(outbuf):1,' freex=',freex:1 );
     snapname(outbuf,sp^.seginx,sp^.len);
     write(log,' from:'); snapname(srcbuf,px,ll);
     writeln( log ) end D*/
}


/* outbuf is always freeseg: */
void copystr(Char **outbuf, nametype **sp, nametype *ip)
{
  if (ip == NULL)
    *sp = NULL;
  else {
    newstr(sp);
    addstring(outbuf, *sp, ip->segmnt, ip->seginx, ip->len);
  }
}


void appendstring(nametype *sp, Char *buf, chbufinx px, chbufinx ll)
{  /*D k := 0; D*/
  int i;
  /*D,kD*/
  int j;
  Char *tmpseg;
  int FORLIM;

  if (sp == NULL || buf == NULL)
    return;
  if (sp->segmnt == freeseg && sp->seginx + sp->len == freex &&
      freex + ll - 1 <= CHBUFSIZ) {
    for (i = 0; i < ll; i++)   /*D k := 1; D*/
      freeseg[freex + i] = buf[px + i];
    sp->len += ll;
    freex += ll;
    return;
  }
  if (sp->len + ll + 2 > CHBUFSIZ) {
    markerror(866);
    return;
  }
  tmpseg = Malloc(sizeof(chbufarray));
  FORLIM = sp->len;
  for (i = 0; i < FORLIM; i++)
    tmpseg[i + 3] = sp->segmnt[sp->seginx + i];
  j = bval(sp->segmnt);
  if (j > 1) {
    putbval(sp->segmnt, j - 1);   /*D k := 2; D*/
    if (sp->segmnt == freeseg && sp->seginx + sp->len == freex) {
      freex = sp->seginx;
      j = 3;
      while (freex > j) {
	if (sp->segmnt[freex - 1] == nlch)
	  freex--;
	else
	  j = freex;
      }
    } else {
      FORLIM = sp->seginx + sp->len;
      for (i = sp->seginx; i < FORLIM; i++)
	sp->segmnt[i] = nlch;
    }
  } else {
    if (sp->segmnt == freeseg)   /*D k := 3; D*/
      freeseg = NULL;
    Free(sp->segmnt);
  }
  for (i = 0; i < ll; i++)
    tmpseg[sp->len + i + 3] = buf[px + i];
  freeseg = tmpseg;
  freex = sp->len + ll + 3;
  putbval(freeseg, 1);
  sp->segmnt = freeseg;
  sp->seginx = 3;
  sp->len += ll;
  /*D; if debuglevel > 0 then if sp<>nil then with sp^ do begin
     write(log,'appendstring: seginx:seginx+len-1= ',
       seginx:1,':',seginx+len-1:1,' len= ',len:1, ' k=',k:1);
     snapname(segmnt,seginx,len); writeln( log )
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
    ph = pr->UU.UEMPTY6.blockheight;
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
    ph = pr->UU.UEMPTY6.blockwidth;
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
      pe->ypos = pr->aat.ypos + pr->UU.UEMPTY6.blockheight * 0.5;
      break;

    case XLdown:
      pe->ypos = pr->aat.ypos - pr->UU.UEMPTY6.blockheight * 0.5;
      break;

    case XLleft:
      pe->xpos = pr->aat.xpos - pr->UU.UEMPTY6.blockwidth * 0.5;
      break;

    case XLright:
      pe->xpos = pr->aat.xpos + pr->UU.UEMPTY6.blockwidth * 0.5;
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
    *pe = arcend(pr);
    break;

  case XLline:
  case XLarrow:
  case XLmove:
  case XLspline:
    *pe = pr->UU.Uline.endpos;
    break;

  case XLabel:
  case XLaTeX:
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
  case XLaTeX:
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
    WITH->aat = envblk->UU.UEMPTY6.here;
    WITH->direction = envblk->direction;
  }
  WITH->lparam = mdistmax;
  WITH->lthick = mdistmax;
  if (primtype == XLspline || primtype == XLarc || primtype == XLarrow ||
      primtype == XLline || primtype == XLellipse || primtype == XLcircle ||
      primtype == XLbox)
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
    WITH->UU.UEMPTY6.blockheight = 0.0;
    WITH->UU.UEMPTY6.blockwidth = 0.0;
    WITH->UU.UEMPTY6.here = WITH->aat;
    WITH->UU.UEMPTY6.vars = NULL;
    WITH->UU.UEMPTY6.env = NULL;
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
    WITH->UU.Uline.atype = pahlex(0, XEMPTY);
    break;

  case XLabel:
  case XLaTeX:
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
      WITH->UU.UEMPTY6.blockheight *= s;
      WITH->UU.UEMPTY6.blockwidth *= s;
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
  if (lexv == XEMPTY && pr->ptype != XLaTeX)
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

  case XLaTeX:
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
  if (envbl->UU.UEMPTY6.env == NULL)
    envbl->UU.UEMPTY6.env = Malloc(sizeof(envarray));
  for (i = envval - 1; i < last; i++) {
    switch (i + 1) {

    case XLarcrad:   /* scaled environmental vars */
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.25;
      break;

    case XLarrowht:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.1;
      break;

    case XLarrowwid:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.05;
      break;

    case XLboxht:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.5;
      break;

    case XLboxrad:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.0;
      break;

    case XLboxwid:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.75;
      break;

    case XLcirclerad:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.25;
      break;

    case XLdashwid:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.1;
      break;

    case XLellipseht:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.5;
      break;

    case XLellipsewid:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.75;
      break;

    case XLlineht:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.5;
      break;

    case XLlinewid:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.5;
      break;

    case XLmoveht:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.5;
      break;

    case XLmovewid:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.5;
      break;

    case XLtextht:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.0;
      break;

    case XLtextoffset:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 2.5 / 72;   /*.27*/
      break;

    case XLtextwid:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.0;
      break;

    /* The following are unscaled */
    case XLarrowhead:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 2.0;
      break;

    case XLfillval:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.3;
      break;

    case XLlinethick:   /* points */
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 0.8;
      break;

    case XLmaxpsht:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 11.0;
      break;

    case XLmaxpswid:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 8.5;
      break;

    case XLscale:
      envbl->UU.UEMPTY6.env[i - XLenvvar] = 1.0;
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
  envbl->UU.UEMPTY6.env = Malloc(sizeof(envarray));
  for (i = XLenvvar; i < XLlastenv; i++)
    envbl->UU.UEMPTY6.env[i - XLenvvar] = pr->UU.UEMPTY6.env[i - XLenvvar];
}


void resetscale(double x, int opr, primitive *envbl)
{
  double r, s;
  int i;

  resetenv(0, envbl);
  r = envbl->UU.UEMPTY6.env[XLscale - XLenvvar - 1];
  eqop(&envbl->UU.UEMPTY6.env[XLscale - XLenvvar - 1], opr, x);
  s = envbl->UU.UEMPTY6.env[XLscale - XLenvvar - 1];
  if (r == 0.0)
    markerror(852);
  else
    s /= r;
  for (i = XLenvvar; i < XLlastsc; i++)
    eqop(&envbl->UU.UEMPTY6.env[i - XLenvvar], XLmulteq, s);
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
      if (qp->UU.UEMPTY6.env[XLscale - XLenvvar - 1] > 0.0)
	*sfact = qp->UU.UEMPTY6.env[XLscale - XLenvvar - 1];
      /*D if debuglevel > 0 then begin write(log,'getscale: sfact=');
         wfloat(log,sfact); writeln(log) end; D*/
      if (east > west &&
	  (east - west) / *sfact > qp->UU.UEMPTY6.env[XLmaxpswid - XLenvvar - 1] &&
	  qp->UU.UEMPTY6.env[XLmaxpswid - XLenvvar - 1] > 0.0) {
	erno = 903;
	gs = (east - west) / qp->UU.UEMPTY6.env[XLmaxpswid - XLenvvar - 1];
      }
      if (north > south &&
	  (north - south) / *sfact > qp->UU.UEMPTY6.env[XLmaxpsht - XLenvvar - 1] &&
	  qp->UU.UEMPTY6.env[XLmaxpsht - XLenvvar - 1] > 0.0) {
	erno = 904;
	gs = Max(gs,
		 (north - south) / qp->UU.UEMPTY6.env[XLmaxpsht - XLenvvar - 1]);
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
    (*prout)->UU.UEMPTY6.blockheight = prin->UU.UEMPTY6.blockheight;
    (*prout)->UU.UEMPTY6.blockwidth = prin->UU.UEMPTY6.blockwidth;
    (*prout)->UU.UEMPTY6.here = prin->UU.UEMPTY6.here;
    (*prout)->UU.UEMPTY6.vars = prin->UU.UEMPTY6.vars;
    if (prin->UU.UEMPTY6.env != NULL) {
      (*prout)->UU.UEMPTY6.env = Malloc(sizeof(envarray));
      for (i = XLenvvar; i < XLlastenv; i++)
	(*prout)->UU.UEMPTY6.env[i - XLenvvar] = prin->UU.UEMPTY6.env[i - XLenvvar];
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
  case XLaTeX:
    /* blank case */
    break;
  }
}


void deletestringbox(primitive **pr)
{
  primitive *prx;

  if (*pr != NULL) {
    if ((*pr)->parent != NULL) {
      if ((*pr)->parent->son != NULL) {
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
/* p2c: dpic.p, line 1779:
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
  if (prp->outlinep != NULL)  /* We have to duplicate the stored string */
    copystr(&freeseg, &prp->outlinep, (*pr)->outlinep);
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

  hs = (lx == XLellipse || lx == XLcircle || lx == XLbox ||
	(((1L << ((long)drawmode)) & ((1L << ((long)PSTricks)) |
	    (1L << ((long)PGF)) | (1L << ((long)MPost)) | (1L << ((long)PS)) |
	    (1L << ((long)PSfrag)))) != 0 &&
	 (lx == XLspline || lx == XLarrow || lx == XLline || lx == XLarc)));
/* p2c: dpic.p, line 1838: 
 * Note: Line breaker spent 0.0 seconds, 5000 tries on line 3195 [251] */
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
  boolean bswitch;
  attribute *WITH, *WITH1;
  primitive *WITH2;
  attribute *WITH3;
  nametype *WITH4;
  int FORLIM;
  fbuffer *WITH5;
  postype *WITH6;

  /* D if (debuglevel > 0) then begin
        writeln(     'Production(newp=',newp:1,
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

  WITH = &attstack[newp];

  /*D with attstack^[newp] do if (debuglevel = 2) and (
     ((p >= block1) and (p <= block3)) or
     ((p > object1) and (p <= object23))
     or (p in [sprintf2,string2,element5,element11])) then printobject(prim);
  if debuglevel > 0 then with attstack^[newp] do
     if p in [ assignment1..assignment4,
               expression1..expression5,
               logexpr2,
               term2..term4,
               factor2,factor3,
               logprod2,
               logval2,logval3,
               lcompare3,lcompare4,
               primary1..primary11
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

  /*      METAGOAL = input "<EOF>"   */

  case METAGOAL1:
    break;

  /*      input = "<EMPTY>"   */
  /*            | input picture NL   */
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

  /*      picture = start NL elementlist "<END>"   */
  /*              | start NL elementlist NL "<END>"   */
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
      WITH2->UU.UEMPTY6.blockheight = north - south;
      WITH2->UU.UEMPTY6.blockwidth = east - west;
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

  /*      NL = ["^M"]"<NL>"   */
  /*         | "<ERROR>"   */
  case NL1:
  case NL2:
    break;

  /*      start = "<START>"   */
  /*            | "<START>" term   */
  /*            | "<START>" term term   */
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

  /*      elementlist = "<EMPTY>"   */
  case elementlist1:
    WITH->state = 0;
    break;

  /*                  | element   */
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

  /*                  | elementlist NL element */
  case elementlist3:
    if (attstack[newp + 2].prim != NULL) {
      if (attstack[newp + 2].lexval != XLcontinue) {
	if (WITH->prim == NULL) {
	  attstack[newp] = attstack[newp + 2];
	  redubuf[reduinx + REDUMAX].prod_ = elementlist2;
	  reduinx--;
	} else
	  addelem(attstack[newp + WITH->state].prim, attstack[newp + 2].prim);
      }
    }
    break;

  /*      term = factor   */
  /*           | term "*" factor   */
  /*           | term "/" factor   */
  /*           | term "%" factor   */
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
/* p2c: dpic.p, line 2017:
 * Note: Using % for possibly-negative arguments [317] */
    }
    break;

  /*      element = namedbox   */
  /*              | "<Label>" suffix ":" position   */
  /*              | assignlist   */
  /*              | "<directon>"   */
  /*              | "<LaTeX>"   */
  /*              | command   */
  /*              | lbrace "lbrace" elementlist optnl "rbrace"   */
  /*              | ifpart   */
  /*              | elsehead "lbrace" elementlist optnl "rbrace"   */
  /*              | for "rbrace"   */
  /*              | "command" stringexpr   */
  /*              | "exec" stringexpr   */
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
      pexit(prp, &envblock->UU.UEMPTY6.here);
    }
    break;

  case element2:
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
    prp->aat.xpos = attstack[newp + 3].xval;
    prp->aat.ypos = attstack[newp + 3].yval;
    /*D; if (debuglevel > 0) and (prim<>nil) then printobject(prim)D*/
    break;

  case element3:
    WITH->lexval = XLBRACE;
    break;

  case element4:
    envblock->direction = WITH->lexval;
    WITH->lexval = XLBRACE;
    break;

  case element5:
    newprim(&WITH->prim, XLaTeX, envblock);
    newstr(&WITH->prim->textp);
    addstring(&freeseg, WITH->prim->textp, chbuf, WITH->chbufx, WITH->length);
    break;

  case element6:
    WITH->lexval = XLBRACE;
    break;

  case element7:
    envblock->UU.UEMPTY6.here.xpos = WITH->xval;
    envblock->UU.UEMPTY6.here.ypos = WITH->yval;
    if (WITH->state == XLright || WITH->state == XLleft ||
	WITH->state == XLdown || WITH->state == XLup)
      envblock->direction = WITH->state;
    if (attstack[newp + 2].state == 0)
      attstack[newp] = attstack[newp + 2];
    break;

  case element8:
    /* blank case */
    break;

  case element9:
    /* blank case */
    break;

  case element10:
    /* blank case */
    break;

  case element11:
    if (attstack[newp + 1].prim != NULL) {
      newprim(&WITH->prim, XLaTeX, envblock);
      WITH->prim->textp = attstack[newp + 1].prim->textp;
      attstack[newp + 1].prim->textp = NULL;
      if (envblock->son == attstack[newp + 1].prim)
	envblock->son = WITH->prim;
      deletestringbox(&attstack[newp + 1].prim);
    }
    break;

  case element12:
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
    /*repeat element13,element14: ; */

  /*      lbrace = "<EMPTY>"   */
  case lbrace1:
    WITH->xval = envblock->UU.UEMPTY6.here.xpos;
    WITH->yval = envblock->UU.UEMPTY6.here.ypos;
    WITH->state = envblock->direction;
    break;

  /*      namedbox = object   */
  /*               | "<Label>" suffix ":" object   */
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

  /*      suffix = "<EMPTY>"   */
  /*             | "[" expression "]"   */
  case suffix1:
    WITH->lexval = XEMPTY;
    break;

  case suffix2:
    WITH->xval = attstack[newp + 1].xval;
    break;

  /*      position = pair   */
  case position1:
    break;

  /*               | expression "between" position "and" position   */
  /*               | expression "<" position "," position "<compare>" shift   */
  case position2:
  case position4:
    r = WITH->xval;
    WITH->xval = attstack[newp + 2].xval +
		 r * (attstack[newp + 4].xval - attstack[newp + 2].xval);
    WITH->yval = attstack[newp + 2].yval +
		 r * (attstack[newp + 4].yval - attstack[newp + 2].yval);
    if (p == position4) {
      if (attstack[newp + 5].lexval != XGT)
	markerror(869);
      else if (attstack[newp + 6].lexval != XEMPTY) {
	WITH->xval += attstack[newp + 6].xval;
	WITH->yval += attstack[newp + 6].yval;
      }
    }
    break;

  /*             | expression "of" "the" "way" "between" position "and" position*/
  case position3:
    r = WITH->xval;
    WITH->xval = attstack[newp + 5].xval +
		 r * (attstack[newp + 7].xval - attstack[newp + 5].xval);
    WITH->yval = attstack[newp + 5].yval +
		 r * (attstack[newp + 7].yval - attstack[newp + 5].yval);
    break;

  /*      assignlist = assignment   */
  /*                 | assignlist "," assignment   */
  case assignlist1:
    break;

  case assignlist2:
    WITH->xval = attstack[newp + 2].xval;
    break;

  /*      command = "print" expression redirect   */
  /*              | "print" position redirect   */
  /*              | "print" stringexpr redirect   */
  case command1:
  case command2:
  case command3:
    WITH1 = &attstack[newp + 1];
    if (attstack[newp + 2].lexval == XEMPTY) {
      switch (p) {

      case command1:
	wfloat(&stderr_, WITH1->xval);
	break;

      case command2:
	wpair(&stderr_, WITH1->xval, WITH1->yval);
	break;

      case command3:
	if (WITH1->prim != NULL)
	  wstring(&stderr_, WITH1->prim->textp);
	break;
      }
      putc('\n', stderr_);
      consoleflush();
    } else if (attstack[newp + 2].state == 0) {
#ifndef SAFE_MODE
      switch (p) {

      case command1:
	wfloat(&redirect, WITH1->xval);
	break;

      case command2:
	wpair(&redirect, WITH1->xval, WITH1->yval);
	break;

      case command3:
	if (WITH1->prim != NULL)
	  wstring(&redirect, WITH1->prim->textp);
	break;
      }
      putc('\n', redirect);
      if (redirect != NULL)
	fclose(redirect);
      redirect = NULL;
#endif
    }
    if (p == command3)
      deletestringbox(&WITH1->prim);
    break;

  /*              | "reset"   */
  case command4:
    resetenv(0, envblock);
    break;

  /*              | "reset" resetlist   */
  case command5:
    break;

  /*              | "sh" stringexpr   */
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

  /*              | "copy" stringexpr   */
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

  /*              | defhead optnl "lbrace" "rbrace"   */
  case command8:
    break;

  /*              | "undefine" "<name>"   */
  /*              | "undefine" "<Label>"   */
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

  /*      optnl = "<EMPTY>"   */
  /*            | NL   */
  case optnl1:
  case optnl2:
    break;

  /*      ifpart = ifhead "lbrace" elementlist optnl "rbrace"   */
  case ifpart1:
    break;

  /*      elsehead = ifpart "else"   */
  case elsehead1:
    if (WITH->xval == 0.0) {
      attstack[newp + 1].lexval = XLBRACE;
      WITH->lexval = XLBRACE;
    } else
      skiptobrace();
    break;

  /*      for = forhead "lbrace" elementlist optnl   */
  /*          | forincr elementlist optnl   */
  case for1:
  case for2:
    break;

  /*      stringexpr = string   */
  /*                 | stringexpr "+" string   */
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

  /*      string = "<string>"   */
  /*             | sprintf ")"   */
  case string1:
    newprim(&WITH->prim, XLstring, envblock);
    eb = findenv(envblock);
    WITH2 = WITH->prim;
    WITH2->UU.Ubox.boxheight = eb->UU.UEMPTY6.env[XLtextht - XLenvvar - 1];
    WITH2->UU.Ubox.boxwidth = eb->UU.UEMPTY6.env[XLtextwid - XLenvvar - 1];
    if (drawmode == xfig && WITH2->UU.Ubox.boxwidth == 0.0) {
      /* To keep xfig from crashing, assume text height is .1
         and a character is .1*0.75 wide */
      eb = findenv(envblock);
      if (WITH2->UU.Ubox.boxheight == 0.0)
	WITH2->UU.Ubox.boxheight = 0.1 * eb->UU.UEMPTY6.env[XLscale - XLenvvar - 1];
      WITH2->UU.Ubox.boxwidth = WITH2->UU.Ubox.boxheight * WITH->length * 0.75;
    }
    WITH2->UU.Ubox.boxradius = 0.0;
    newstr(&WITH2->textp);
    addstring(&freeseg, WITH2->textp, chbuf, WITH->chbufx, WITH->length);
    break;

  case string2:
    break;

  /*      assignment = "<name>" suffix "=" expression   */
  /*                 | "<name>" suffix "=" assignment   */
  /*                 | "<envvar>" "=" expression   */
  /*                 | "<envvar>" "=" assignment   */
  case assignment1:
  case assignment2:
    if (attstack[newp + 1].lexval != XEMPTY)
      addsuffix(chbuf, &WITH->chbufx, &WITH->length, attstack[newp + 1].xval);
    if (attstack[newp + 2].lexval == XEQ) {
      WITH->varname = findname(envblock->UU.UEMPTY6.vars, chbuf, WITH->chbufx,
			       WITH->length, &lastn);
      if (WITH->varname == NULL) {
	newstr(&WITH->varname);
	addstring(&freeseg, WITH->varname, chbuf, WITH->chbufx, WITH->length);
	if (lastn == NULL)
	  envblock->UU.UEMPTY6.vars = WITH->varname;
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
      else if (WITH->lexval == XLarrowhead && drawmode == TeX &&
	       attstack[newp + 2].xval == 0.0)
	markerror(858);
      else {
	if (envblock->UU.UEMPTY6.env == NULL)
	  inheritenv(envblock);
	eqop(&envblock->UU.UEMPTY6.env[WITH->lexval - XLenvvar - 1],
	     attstack[newp + 1].lexval, attstack[newp + 2].xval);
      }
      WITH->xval = envblock->UU.UEMPTY6.env[WITH->lexval - XLenvvar - 1];
      /*D if debuglevel > 0 then writeln(log,' Assignment4: lexval=',lexval:1,
         ' value=',envblock^.env^[lexval]); D*/
      WITH->startchop = WITH->lexval;
      if (WITH->lexval == XLdashwid || WITH->lexval == XLlinethick) {
	newprim(&WITH->prim, XLaTeX, envblock);
	if (WITH->lexval == XLlinethick)
	  WITH->prim->lthick = WITH->xval;
	else
	  WITH->prim->lparam = WITH->xval;
      } else
	WITH->lexval = XLBRACE;
    }
    break;

  /*      expression = term   */
  /*                 | "+" term   */
  /*                 | "-" term   */
  /*                 | expression "+" term   */
  /*                 | expression "-" term   */
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

  /*      ifhead = setlogic "if" logexpr "then"   */
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

  /*      setlogic = "<EMPTY>"   */
  case setlogic1:
    inlogic = true;
    break;

  /*      logexpr = logprod   */
  /*              | logexpr "||" logprod   */
  case logexpr1:
    break;

  case logexpr2:
    if (WITH->xval != 0.0 || attstack[newp + 2].xval != 0.0)
      WITH->xval = 1.0;
    else
      WITH->xval = 0.0;
    break;

  /*      forhead = "for" assignlist "to" expression do   */
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

  /*      forincr = for ":"   */
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
      if (envblock->UU.UEMPTY6.env == NULL)
	inheritenv(envblock);
      envblock->UU.UEMPTY6.env[(int)((long)floor(WITH->startchop + 0.5)) -
			   XLenvvar - 1] = WITH->xval;
    } else
      resetscale(WITH->xval, XEQ, envblock);

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

  /*      do = "do"   */
  /*         | by expression "do"   */
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

  /*      by = "by"   */
  /*         | "by" "*"   */
  case by1:
    break;

  case by2:
    WITH->lexval = attstack[newp + 1].lexval;
    break;

  /*      redirect = "<EMPTY>" */
  case redirect1:
    WITH->lexval = XEMPTY;
    break;

  /*               | "<compare>" stringexpr  */
  case redirect2:
    WITH1 = &attstack[newp + 1];
    attstack[newp].state = 1;
    bswitch = false;
    if (WITH1->prim != NULL) {
      if (WITH1->prim->textp == NULL)
	markerror(861);
      else if (p == redirect2 && attstack[newp].lexval != XGT)
	markerror(869);
      else if (safemode)
	markerror(906);
      else
	bswitch = true;
    }
#ifdef SAFE_MODE
    if (bswitch)
      markerror(906);
#else
    if (bswitch)
      pointoutput(true, WITH1->prim->textp, &attstack[newp].state);
#endif
    deletestringbox(&WITH1->prim);
    break;

  /*               | "<compare>" "<compare>" stringexpr   */
  case redirect3:
    WITH1 = &attstack[newp + 2];
    attstack[newp].state = 1;
    bswitch = false;
    if (WITH1->prim != NULL) {
      if (WITH1->prim->textp == NULL)
	markerror(861);
      else if (attstack[newp].lexval != XGT ||
	       attstack[newp + 1].lexval != XGT)
	markerror(869);
      else if (safemode)
	markerror(906);
      else
	bswitch = true;
    }
#ifdef SAFE_MODE
    if (bswitch)
      markerror(906);
#else
    if (bswitch)
      pointoutput(false, WITH1->prim->textp, &attstack[newp].state);
#endif
    deletestringbox(&WITH1->prim);
    break;

  /*      resetlist = "<envvar>"   */
  /*                | resetlist "," "<envvar>"   */
  case resetlist1:
    resetenv(WITH->lexval, envblock);
    break;

  case resetlist2:
    resetenv(attstack[newp + 2].lexval, envblock);
    break;

  /*      defhead = "define" "<name>"   */
  /*              | "define" "<Label>"   */
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

  /*      sprintf = "sprintf" "(" "<string>"   */
  /*              | "sprintf" "(" "<string>" "," exprlist   */
  case sprintf1:
  case sprintf2:
    newprim(&WITH->prim, XLstring, envblock);
    WITH2 = WITH->prim;
    eb = findenv(envblock);
    WITH2->UU.Ubox.boxheight = eb->UU.UEMPTY6.env[XLtextht - XLenvvar - 1];
    WITH2->UU.Ubox.boxwidth = eb->UU.UEMPTY6.env[XLtextwid - XLenvvar - 1];
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
    while (j < WITH1->length) {   /* end; below */
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
    /*D begin
       if debuglevel > 0 then begin writeln(log,
          ' sprintf looping, i,j,lj,length=',i:4,j:4,lj:4,length:4,
          ' c="', chbuf^[chbufx+j],'"'); flush(log) end; D*/
    /*D end; D*/
    /* begin above */
    if (i < mm)   /* Too many args */
      markerror(864);
    if (drawmode == xfig) {
      WITH2 = WITH->prim;
      if (WITH2->UU.Ubox.boxwidth == 0.0) {
	if (WITH2->UU.Ubox.boxheight == 0.0)
	  WITH2->UU.Ubox.boxheight = 0.1 * eb->UU.UEMPTY6.env[XLscale - XLenvvar - 1];
	WITH2->UU.Ubox.boxwidth = WITH2->UU.Ubox.boxheight *
				  WITH2->textp->len * 0.75;
      }
    }
    deletestringbox(&attstack[newp + 2].prim);
    break;

  /*      exprlist = expression   */
  /*               | expression "," exprlist   */
  case exprlist1:
    WITH->state = 1;
    break;

  case exprlist2:
    WITH->state = attstack[newp + 2].state + 1;
    break;

  /*      object = block  */
  /*             | object "height" expression  */
  /*             | object "width" expression  */
  /*             | object "radius" expression  */
  /*             | object "diameter" expression  */
  /*             | object "thickness" expression  */
  /*             | object "scaled" expression  */
  /*             | object "<directon>" optexp  */
  /*             | object "by" pair  */
  /*             | object "then"  */
  /*             | object "<linetype>" optexp  */
  /*             | object "chop" optexp  */
  /*             | object "filled" optexp  */
  /*             | object "<arrowhd>"  */
  /*             | object "cw"  */
  /*             | object "ccw"  */
  /*             | object "same"  */
  /*             | object stringexpr  */
  /*             | object "from" position  */
  /*             | object "to" position  */
  /*             | object "at" position  */
  /*             | object "<textpos>"  */
  /*             | object "<colrspec>" stringexpr  */
  /*             | objectwith "<corner>" "at" position  */
  /*             | objectwith pair "at" position  */
  /*             | objectwith "at" position  */
  /*             | "continue"  */

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
	  r = 0.5 * (attstack[newp + 2].xval - WITH2->UU.UEMPTY6.blockheight);
	  WITH2->UU.UEMPTY6.blockheight = attstack[newp + 2].xval;
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
      case XLaTeX:
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
	  r = 0.5 * (attstack[newp + 2].xval - WITH2->UU.UEMPTY6.blockwidth);
	  WITH2->UU.UEMPTY6.blockwidth = attstack[newp + 2].xval;
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
      case XLaTeX:
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
	  dx = WITH2->UU.UEMPTY6.blockwidth * r / 2;
	  dy = WITH2->UU.UEMPTY6.blockheight * r / 2;
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
      case XLaTeX:
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
	  WITH2->ptype == XLmove ||
	  WITH2->ptype == XLline || WITH2->ptype == XLarc) {
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
	      r = eb->UU.UEMPTY6.env[XLlineht - XLenvvar - 1];
	      s = eb->UU.UEMPTY6.env[XLlinewid - XLenvvar - 1];
	      break;

	    case XLmove:
	      r = eb->UU.UEMPTY6.env[XLmoveht - XLenvvar - 1];
	      s = eb->UU.UEMPTY6.env[XLmovewid - XLenvvar - 1];
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
      /*D if debuglevel > 0 then begin write(log,'lexical "then" found, ');
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
	  r = eb->UU.UEMPTY6.env[XLcirclerad - XLenvvar - 1];
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
	s = eb->UU.UEMPTY6.env[XLfillval - XLenvvar - 1];
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
	  if (((1L << ((long)drawmode)) &
	       ((1L << ((long)xfig)) | (1L << ((long)PGF)) |
		(1L << ((long)PSfrag)) | (1L << ((long)PSTricks)) |
		(1L << ((long)MPost)) | (1L << ((long)PS)))) == 0)
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
      else {
	WITH2->UU.Uline.atype = pahlex(WITH2->UU.Uline.atype,
				      attstack[newp + 1].lexval);
	eb = findenv(envblock);
	mm = (long)floor(eb->UU.UEMPTY6.env[XLarrowhead - XLenvvar - 1] + 0.5);
	WITH2->UU.Uline.atype = pahnum(WITH2->UU.Uline.atype, mm);
      }
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
	  WITH2->aat = arcstart(WITH->prim);
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
	  WITH2->aat = arcstart(WITH->prim);
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
	case XLaTeX:
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
	  WITH->prim->ptype == XLarrow ||
	  WITH->prim->ptype == XLline || WITH->prim->ptype == XLarc) {
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
	if (hasoutline(WITH->lexval, true)) {
	  deletename(&WITH2->outlinep);
	  WITH2->outlinep = attstack[newp + 2].prim->textp;
	  attstack[newp + 2].prim->textp = NULL;
	}
	break;

      case XLcolour:
	if (hasoutline(WITH->lexval, true)) {
	  deletename(&WITH2->outlinep);
	  WITH2->outlinep = attstack[newp + 2].prim->textp;
	  attstack[newp + 2].prim->textp = NULL;
	  if ((attstack[newp + 1].lexval == XLcolour &&
	       WITH2->ptype != XLspline && WITH2->ptype != XLarrow &&
	       WITH2->ptype != XLline &&
	       WITH2->ptype != XLarc) & hasshade(WITH->lexval, false)) {
	    deletename(&WITH2->shadedp);
	    copystr(&freeseg, &WITH2->shadedp, WITH2->outlinep);
	  }
	}
	break;
      }
    }
    deletestringbox(&attstack[newp + 2].prim);
    break;

  /*                          | objectwith "<corner>" "at" position    */
  /*                          | objectwith pair "at" position    */
  case object24:
  case object25:
    if (WITH->prim != NULL) {
      if (WITH->root != NULL) {
	prp = WITH->prim;
	WITH->prim = WITH->root;
	WITH->root = prp;
      }
      WITH->xval = attstack[newp + 3].xval;
      WITH->yval = attstack[newp + 3].yval;
      if (p == object24)
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

  /*             | objectwith "at" position  */
  case object26:
    if (WITH->prim == NULL)
      WITH->root = NULL;
    else {
      if (WITH->root != NULL) {
	prp = WITH->prim;
	WITH->prim = WITH->root;
	WITH->root = prp;
      }
      WITH->xval = attstack[newp + 2].xval;
      WITH->yval = attstack[newp + 2].yval;
      setstval(&WITH->state, XEMPTY);
      setstflag(&WITH->state, XLat);
    }
    break;

  /*                         | "continue" */
  case object27:
    primp = NULL;
    prp = envblock->son;
    while (prp != NULL) {
      if (prp->ptype != XLaTeX && prp->ptype != XLstring &&
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

  /*     openblock = "<EMPTY>"   */
  case openblock1:
    /*D if debuglevel > 0 then writeln(log,
       'Calling newprim(prim,',XBLOCK:1,'):'); D*/
    newprim(&WITH->prim, XBLOCK, envblock);
    WITH6 = &WITH->prim->UU.UEMPTY6.here;
    /* prim^.here := envblock^.here; */
    /* Bah! gpic compatibility: */
    WITH6->xpos = 0.0;
    WITH6->ypos = 0.0;
    envblock = WITH->prim;
    WITH->lexval = 0;
    /* ; resetenv(0,envblock) */
    /*D; if (debuglevel > 0) and (prim <> nil) then printobject(prim)D*/
    break;

  /*     block = "<primitiv>" optexp   */
  /*           | stringexpr   */
  /*           | openblock "[" closeblock "]"   */
  /*           | openblock "[]"   */
  case block1:
    if (WITH->lexval > XLprimitiv && WITH->lexval < XLenvvar) {
      newprim(&WITH->prim, WITH->lexval, envblock);
      eb = findenv(envblock);
      if (((1L << ((long)drawmode)) &
	   ((1L << ((long)MPost)) | (1L << ((long)pict2e)) |
	    (1L << ((long)PS)) | (1L << ((long)PSfrag)))) != 0 &&
	  WITH->lexval != XLmove)
	    /*,PSmps*/
	      WITH->prim->lthick = eb->UU.UEMPTY6.env[XLlinethick - XLenvvar - 1];
      if (attstack[newp + 1].lexval != XEMPTY && WITH->lexval != XLmove &&
	  WITH->lexval != XLspline && WITH->lexval != XLarrow &&
	  WITH->lexval != XLline)
	markerror(858);
      WITH2 = WITH->prim;
      switch (WITH->lexval) {

      case XLbox:
	WITH2->UU.Ubox.boxheight = eb->UU.UEMPTY6.env[XLboxht - XLenvvar - 1];
	WITH2->UU.Ubox.boxwidth = eb->UU.UEMPTY6.env[XLboxwid - XLenvvar - 1];
	WITH2->UU.Ubox.boxradius = eb->UU.UEMPTY6.env[XLboxrad - XLenvvar - 1];
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
	WITH2->UU.Ucircle.radius = eb->UU.UEMPTY6.env[XLcirclerad - XLenvvar - 1];
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
	WITH2->UU.Uellipse.elheight = eb->UU.UEMPTY6.env[XLellipseht - XLenvvar - 1];
	WITH2->UU.Uellipse.elwidth = eb->UU.UEMPTY6.env[XLellipsewid - XLenvvar - 1];
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
	WITH2->UU.Uline.aradius = eb->UU.UEMPTY6.env[XLarcrad - XLenvvar - 1];
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
	WITH2->UU.Uline.height = eb->UU.UEMPTY6.env[XLarrowht - XLenvvar - 1];
	WITH2->UU.Uline.width = eb->UU.UEMPTY6.env[XLarrowwid - XLenvvar - 1];
	    /* atype := XEMPTY; */
	WITH2->UU.Uline.atype = pahnum(pahlex(0, XEMPTY),
	    (long)floor(eb->UU.UEMPTY6.env[XLarrowhead - XLenvvar - 1] + 0.5));
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
	    r = eb->UU.UEMPTY6.env[XLmoveht - XLenvvar - 1];
	    break;

	  case XLleft:
	  case XLright:
	    r = eb->UU.UEMPTY6.env[XLmovewid - XLenvvar - 1];
	    break;
	  }
	} else {
	  switch (WITH2->direction) {

	  case XLup:
	  case XLdown:
	    r = eb->UU.UEMPTY6.env[XLlineht - XLenvvar - 1];
	    break;

	  case XLleft:
	  case XLright:
	    r = eb->UU.UEMPTY6.env[XLlinewid - XLenvvar - 1];
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
	WITH2->UU.Uline.height = eb->UU.UEMPTY6.env[XLarrowht - XLenvvar - 1];
	WITH2->UU.Uline.width = eb->UU.UEMPTY6.env[XLarrowwid - XLenvvar - 1];
	if (WITH2->ptype == XLarrow)
	  WITH2->UU.Uline.atype = pahlex(0, XRIGHTHEAD);
	else
	  WITH2->UU.Uline.atype = pahlex(0, XEMPTY);
	WITH2->UU.Uline.atype = pahnum(WITH2->UU.Uline.atype,
	    (long)floor(eb->UU.UEMPTY6.env[XLarrowhead - XLenvvar - 1] + 0.5));
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
      WITH2->UU.UEMPTY6.blockwidth = east - west;
      WITH2->UU.UEMPTY6.blockheight = north - south;
      WITH2->aat.xpos = (east + west) * 0.5;
      WITH2->aat.ypos = (north + south) * 0.5;
      dx = envblock->UU.UEMPTY6.here.xpos - WITH2->aat.xpos;
      dy = envblock->UU.UEMPTY6.here.ypos - WITH2->aat.ypos;
      switch (envblock->direction) {

      case XLright:
	dx += WITH2->UU.UEMPTY6.blockwidth * 0.5;
	break;

      case XLleft:
	dx -= WITH2->UU.UEMPTY6.blockwidth * 0.5;
	break;

      case XLup:
	dy += WITH2->UU.UEMPTY6.blockheight * 0.5;
	break;

      case XLdown:
	dy -= WITH2->UU.UEMPTY6.blockheight * 0.5;
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

  /*     optexp = "<EMPTY>"   */
  /*            | expression   */
  case optexp1:
    WITH->lexval = XEMPTY;
    break;

  case optexp2:
    break;

  /*     closeblock = elementlist optnl   */
  /*    Add latex to reset env variables changed within a block */
  case closeblock1:
    if (WITH->prim != NULL && envblock->UU.UEMPTY6.env != NULL) {
      eb = findenv(envblock->parent);
      if (eb != NULL) {  /* check and reset variables: */
	if (envblock->UU.UEMPTY6.env[XLlinethick - XLenvvar - 1] !=
	    eb->UU.UEMPTY6.env[XLlinethick - XLenvvar - 1]) {
	  newprim(&attstack[newp + 2].prim, XLaTeX, envblock);
	  attstack[newp + 2].prim->lthick =
	    eb->UU.UEMPTY6.env[XLlinethick - XLenvvar - 1];
	  addelem(attstack[newp + WITH->state].prim, attstack[newp + 2].prim);
	}
	if (envblock->UU.UEMPTY6.env[XLdashwid - XLenvvar - 1] !=
	    eb->UU.UEMPTY6.env[XLdashwid - XLenvvar - 1]) {
	  newprim(&attstack[newp + 2].prim, XLaTeX, envblock);
	  attstack[newp + 2].prim->lparam = eb->UU.UEMPTY6.env[XLdashwid - XLenvvar - 1];
	  addelem(attstack[newp + WITH->state].prim, attstack[newp + 2].prim);
	}
      }
    }
    break;

  /*     pair = expression "," expression   */
  /*          | location shift   */
  case pair1:
    WITH->yval = attstack[newp + 2].xval;
    break;

  case pair2:
    if (attstack[newp + 1].lexval != XEMPTY) {
      WITH->xval += attstack[newp + 1].xval;
      WITH->yval += attstack[newp + 1].yval;
    }
    break;

  /*     objectwith = object "with"  */
  /*                | objectwith "." "<Label>" suffix  */
  case objectwith1:
    break;

  case objectwith2:
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
	deletetree(&WITH->prim);
      } else {
	if (WITH->root == NULL)
	  WITH->root = WITH->prim;
	WITH->prim = primp;
      }
    }
    break;

  /*                | objectwith "." nth primobj  */
  case objectwith3:
    if (WITH->prim != NULL) {
      WITH->lexval = attstack[newp + 1].lexval;
      primp = nthprimobj(WITH->prim->son, attstack[newp + 2].length,
			 attstack[newp + 3].lexval);
      if (primp == NULL) {
	markerror(857);
	deletetree(&WITH->prim);
      } else {
	if (WITH->root == NULL)
	  WITH->root = WITH->prim;
	WITH->prim = primp;
      }
    }
    break;

  /*     shift = "<EMPTY>"   */
  /*           | shift "+" location   */
  /*           | shift "-" location   */
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

  /*     location = "(" position ")"   */
  /*              | "(" position "," position ")"   */
  /*              | place   */
  /*              | location "*" factor   */
  /*              | location "/" factor   */
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

  /*     place = placename   */
  /*           | placename "<corner>"   */
  /*           | "<corner>" placename   */
  /*           | "<corner>" "of" placename   */
  /*           | "Here"   */
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
    WITH->xval = envblock->UU.UEMPTY6.here.xpos;
    WITH->yval = envblock->UU.UEMPTY6.here.ypos;
    break;

  /*     factor = primary   */
  /*            | "!" primary   */
  /*            | primary "^" factor   */
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

  /*     placename = "<Label>" suffix   */
  /*               | nth primobj   */
  /*               | placename "." "<Label>" suffix   */
  /*               | placename "." nth primobj   */
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
       'placename: type ', ptype:7,', ',aat.xpos:7:4,aat.ypos:7:4)
        else if debuglevel > 0 then begin
           write(log,'Search failure for "');
           for i := 0 to length-1 do write(log,chbuf^[chbufx+i]);
           writeln(log,'"') end ; D*/
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

  /*     nth = ncount "th"   */
  /*         | ncount "th" "last"   */
  /*         | "last"   */
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

  /*     primobj = "<primitiv>"   */
  /*             | "[]"   */
  /*             | "<string>"   */
  /*             | "[" "]"   */
  case primobj1:
  case primobj2:
  case primobj3:
    break;

  case primobj4:
    WITH->lexval = XBLOCK;
    break;

  /*     ncount = "<float>"   */
  case ncount1:
    break;

  /*            | "`" expression "'"   */
  /*            | "lbrace" expression "rbrace"   */
  case ncount2:
  case ncount3:
    WITH->xval = attstack[newp + 1].xval;
    break;

  /*     logprod = logval   */
  case logprod1:
    break;

  /*             | logprod "&&" logval   */
  case logprod2:
    if (WITH->xval == 0.0 || attstack[newp + 2].xval == 0.0)
      WITH->xval = 0.0;
    else
      WITH->xval = 1.0;
    break;

  /*   logval = lcompare */
  case logval1:
    if (WITH->lexval == XLstring) {
      markerror(869);
      WITH->lexval = XLfloat;
      deletestringbox(&WITH->prim);
    }
    break;

  /*          | stringexpr "<" stringexpr */
  case logval2:
    i = cmpstring(WITH->prim, attstack[newp + 2].prim);
    if (i < 0)
      WITH->xval = 1.0;
    else
      WITH->xval = 0.0;
    WITH->lexval = XLfloat;
    deletestringbox(&attstack[newp + 2].prim);
    deletestringbox(&WITH->prim);
    break;

  /*          | expression "<" expression */
  case logval3:
    if (WITH->xval < attstack[newp + 2].xval)
      WITH->xval = 1.0;
    else
      WITH->xval = 0.0;
    break;

  /*   lcompare = expression */
  /*            | stringexpr */
  case lcompare1:
  case lcompare2:
    break;

  /*            | lcompare "<compare>" expression */
  /*             "==" "!=" ">=" "<=" "<^>" ">"     */
  case lcompare3:
    if (WITH->lexval == XLstring) {
      markerror(869);
      bswitch = false;
      deletestringbox(&WITH->prim);
    } else {
      switch (attstack[newp + 1].lexval - XLcompare) {

      case 1:
	bswitch = (WITH->xval == attstack[newp + 2].xval);
	break;

      case 2:
	bswitch = (WITH->xval != attstack[newp + 2].xval);
	break;

      case 3:
	bswitch = (WITH->xval >= attstack[newp + 2].xval);
	break;

      case 4:
	bswitch = (WITH->xval <= attstack[newp + 2].xval);
	break;

      case 5:
	bswitch = (WITH->xval < attstack[newp + 2].xval);
	break;

      case 6:
	bswitch = (WITH->xval > attstack[newp + 2].xval);
	break;
      }
    }
    if (bswitch)
      WITH->xval = 1.0;
    else
      WITH->xval = 0.0;
    break;

  /*            | lcompare "<compare>" stringexpr */
  case lcompare4:
    if (WITH->lexval != XLstring) {
      markerror(869);
      bswitch = false;
    } else {
      i = cmpstring(WITH->prim, attstack[newp + 2].prim);
      /*D if debuglevel > 0 then writeln(log,' cmpstring=',i:1); D*/
      switch (attstack[newp + 1].lexval - XLcompare) {

      case 1:
	bswitch = (i == 0);
	break;

      case 2:
	bswitch = (i != 0);
	break;

      case 3:
	bswitch = (i >= 0);
	break;

      case 4:
	bswitch = (i <= 0);
	break;

      case 5:
	bswitch = (i < 0);
	break;

      case 6:
	bswitch = (i > 0);
	break;

      default:
	bswitch = false;
	break;
      }
      deletestringbox(&WITH->prim);
    }
    if (bswitch)
      WITH->xval = 1.0;
    else
      WITH->xval = 0.0;
    WITH->lexval = XLfloat;
    deletestringbox(&attstack[newp + 2].prim);
    break;

  /*     primary = "<envvar>"   */
  /*             | "<name>" suffix   */
  /*             | "<float>"   */
  /*             | "(" logexpr ")"   */
  /*             | location ".x"   */
  /*             | location ".y"   */
  /*             | placename "<param>"   */
  /*             | "rand" "(" ")"   */
  /*             | "rand" "(" expression ")"   */
  /*             | "<func1>" "(" expression ")"   */
  /*             | "<func2>" "(" expression "," expression ")"   */
  /*             | "(" assignlist ")"   */
  case primary1:
    if (envblock != NULL) {
      eb = findenv(envblock);
      WITH->xval = eb->UU.UEMPTY6.env[WITH->lexval - XLenvvar - 1];
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
/* p2c: dpic.p, line 3881:
 * Note: Using % for possibly-negative arguments [317] */
      if (i >= 0)
	WITH->xval = i;
      else
	WITH->xval = i + j;
      break;
    }
    break;

  /*                 | "(" assignlist ")"    */
  case primary12:
    WITH->xval = attstack[newp + 1].xval;

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
   infname := substr(parms,1,length(parms)-1);
   reset(input,'NAME='||infname);
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

  P_sun_argv(infname, sizeof(mstring), argct);
  /*GH if argct <= ParamCount then begin
     infname := ParamStr(argct); HG*/

  if (checkfile(infname, true) != 0)
    fatal(1);
  if (input != NULL)
    input = freopen(P_trimname(infname, sizeof(mstring)), "r", input);
  else
    input = fopen(P_trimname(infname, sizeof(mstring)), "r");
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
     else for i:=j to savedlen do case ord(carray^[i]) of
        ordETX: write(log,'^C');
        ordNL: writeln(log);
        ordCR: write(log,'\r');
        ordTAB: write(log,'\t');
        otherwise write(log,carray^[i])
        end;

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
      else if (symb_ == XLaTeX)
	fprintf(stderr_, "LaTeX");
      else if (symb_ == XLfloat)
	fprintf(stderr_, "Float");
      else if (symb_ == XERROR)
	fprintf(stderr_, "Error");
      else {
	switch (symb_) {

	/* include controlerr.i */

	case 4:
	  putc('<', stderr_);
	  break;

	case 5:
	  fprintf(stderr_, "cw");
	  break;

	case 6:
	  fprintf(stderr_, "ccw");
	  break;

	case 7:
	  putc('(', stderr_);
	  break;

	case 8:
	  fprintf(stderr_, "Possibly unbalanced parentheses: )");
	  break;

	case 9:
	  putc('*', stderr_);
	  break;

	case 10:
	  putc('+', stderr_);
	  break;

	case 11:
	  putc('-', stderr_);
	  break;

	case 12:
	  putc('/', stderr_);
	  break;

	case 13:
	  putc('%', stderr_);
	  break;

	case 14:
	  fprintf(stderr_, "; or end of line");
	  break;

	case 16:
	  putc('!', stderr_);
	  break;

	case 17:
	  fprintf(stderr_, "&&");
	  break;

	case 18:
	  fprintf(stderr_, "||");
	  break;

	case 19:
	  putc(',', stderr_);
	  break;

	case 20:
	  putc(':', stderr_);
	  break;

	case 21:
	  putc('[', stderr_);
	  break;

	case 22:
	  fprintf(stderr_, "Possibly unbalanced brackets: ]");
	  break;

	case 23:
	  putc('{', stderr_);
	  break;

	case 24:
	  fprintf(stderr_, "Possibly unbalanced braces: }");
	  break;

	case 25:
	  putc('.', stderr_);
	  break;

	case 26:
	  fprintf(stderr_, "[]");
	  break;

	case 27:
	  putc('`', stderr_);
	  break;

	case 28:
	  putc('\'', stderr_);
	  break;

	case 29:
	  putc('=', stderr_);
	  break;

	case 30:
	  fprintf(stderr_, ":=");
	  break;

	case 31:
	  fprintf(stderr_, "+=");
	  break;

	case 32:
	  fprintf(stderr_, "-=");
	  break;

	case 33:
	  fprintf(stderr_, "*=");
	  break;

	case 34:
	  fprintf(stderr_, "/=");
	  break;

	case 35:
	  fprintf(stderr_, "%%=");
	  break;

	case 36:
	  putc('&', stderr_);
	  break;

	case 41:
	  fprintf(stderr_, "\" or string");
	  break;

	case 42:
	  putc('#', stderr_);
	  break;

	case 43:
	  fprintf(stderr_, "End of \"for\" body");
	  break;

	case 44:
	  fprintf(stderr_, "$ or argument reference");
	  break;

	case 47:
	  fprintf(stderr_, "height or ht");
	  break;

	case 48:
	  fprintf(stderr_, "wid or width");
	  break;

	case 49:
	  fprintf(stderr_, "rad or radius");
	  break;

	case 50:
	  fprintf(stderr_, "diam or diameter");
	  break;

	case 51:
	  fprintf(stderr_, "thick or thickness");
	  break;

	case 52:
	  fprintf(stderr_, "scaled");
	  break;

	case 53:
	  fprintf(stderr_, "from");
	  break;

	case 54:
	  fprintf(stderr_, "to");
	  break;

	case 55:
	  fprintf(stderr_, "at");
	  break;

	case 56:
	  fprintf(stderr_, "with");
	  break;

	case 57:
	  fprintf(stderr_, "by");
	  break;

	case 58:
	  fprintf(stderr_, "then");
	  break;

	case 59:
	  fprintf(stderr_, "continue");
	  break;

	case 60:
	  fprintf(stderr_, "chop");
	  break;

	case 61:
	  fprintf(stderr_, "same");
	  break;

	case 62:
	  fprintf(stderr_, "of");
	  break;

	case 63:
	  fprintf(stderr_, "the");
	  break;

	case 64:
	  fprintf(stderr_, "way");
	  break;

	case 65:
	  fprintf(stderr_, "between");
	  break;

	case 66:
	  fprintf(stderr_, "and");
	  break;

	case 67:
	  fprintf(stderr_, "Here");
	  break;

	case 68:
	  fprintf(stderr_, "nd or rd or st or th");
	  break;

	case 69:
	  fprintf(stderr_, "last");
	  break;

	case 70:
	  fprintf(stderr_, "fill or filled");
	  break;

	case 71:
	  fprintf(stderr_, ".x");
	  break;

	case 72:
	  fprintf(stderr_, ".y");
	  break;

	case 73:
	  fprintf(stderr_, "print");
	  break;

	case 74:
	  fprintf(stderr_, "copy");
	  break;

	case 75:
	  fprintf(stderr_, "reset");
	  break;

	case 76:
	  fprintf(stderr_, "exec");
	  break;

	case 77:
	  fprintf(stderr_, "sh");
	  break;

	case 78:
	  fprintf(stderr_, "command");
	  break;

	case 79:
	  fprintf(stderr_, "define");
	  break;

	case 80:
	  fprintf(stderr_, "undef or undefine");
	  break;

	case 81:
	  fprintf(stderr_, "rand");
	  break;

	case 82:
	  fprintf(stderr_, "if");
	  break;

	case 83:
	  fprintf(stderr_, "else");
	  break;

	case 84:
	  fprintf(stderr_, "for");
	  break;

	case 85:
	  fprintf(stderr_, "do");
	  break;

	case 86:
	  fprintf(stderr_, "sprintf");
	  break;

	case 88:
	  fprintf(stderr_, ".ne");
	  break;

	case 89:
	  fprintf(stderr_, ".se");
	  break;

	case 90:
	  fprintf(stderr_, ".nw");
	  break;

	case 91:
	  fprintf(stderr_, ".sw");
	  break;

	case 92:
	  fprintf(stderr_, ".n or .north or .t or .top or top");
	  break;

	case 93:
	  fprintf(stderr_, ".b or .bot or .bottom or .s or .south or bottom");
	  break;

	case 94:
	  fprintf(stderr_, ".e or .east or .r or .right");
	  break;

	case 95:
	  fprintf(stderr_, ".l or .left or .w or .west");
	  break;

	case 96:
	  fprintf(stderr_, ".start or start");
	  break;

	case 97:
	  fprintf(stderr_, ".end or end");
	  break;

	case 98:
	  fprintf(stderr_, ".c or .center or .centre");
	  break;

	case 99:
	  fprintf(stderr_, "<compare>");
	  break;

	case 100:
	  fprintf(stderr_, "==");
	  break;

	case 101:
	  fprintf(stderr_, "!=");
	  break;

	case 102:
	  fprintf(stderr_, ">=");
	  break;

	case 103:
	  fprintf(stderr_, "<=");
	  break;

	case 105:
	  putc('>', stderr_);
	  break;

	case 107:
	  fprintf(stderr_, ".height or .ht");
	  break;

	case 108:
	  fprintf(stderr_, ".wid or .width");
	  break;

	case 109:
	  fprintf(stderr_, ".rad or .radius");
	  break;

	case 110:
	  fprintf(stderr_, ".diam or .diameter");
	  break;

	case 112:
	  fprintf(stderr_, "abs");
	  break;

	case 113:
	  fprintf(stderr_, "acos");
	  break;

	case 114:
	  fprintf(stderr_, "asin");
	  break;

	case 115:
	  fprintf(stderr_, "cos");
	  break;

	case 116:
	  fprintf(stderr_, "exp");
	  break;

	case 117:
	  fprintf(stderr_, "expe");
	  break;

	case 118:
	  fprintf(stderr_, "int");
	  break;

	case 119:
	  fprintf(stderr_, "log");
	  break;

	case 120:
	  fprintf(stderr_, "loge");
	  break;

	case 121:
	  fprintf(stderr_, "sign");
	  break;

	case 122:
	  fprintf(stderr_, "sin");
	  break;

	case 123:
	  fprintf(stderr_, "sqrt");
	  break;

	case 124:
	  fprintf(stderr_, "tan");
	  break;

	case 125:
	  fprintf(stderr_, "floor");
	  break;

	case 127:
	  fprintf(stderr_, "atan2");
	  break;

	case 128:
	  fprintf(stderr_, "max");
	  break;

	case 129:
	  fprintf(stderr_, "min");
	  break;

	case 130:
	  fprintf(stderr_, "pmod");
	  break;

	case 132:
	  fprintf(stderr_, "solid");
	  break;

	case 133:
	  fprintf(stderr_, "dotted");
	  break;

	case 134:
	  fprintf(stderr_, "dashed");
	  break;

	case 135:
	  fprintf(stderr_, "invis or invisible");
	  break;

	case 136:
	  fprintf(stderr_, "path");
	  break;

	case 138:
	  fprintf(stderr_, "color or colored or colour or coloured");
	  break;

	case 139:
	  fprintf(stderr_, "outline or outlined");
	  break;

	case 140:
	  fprintf(stderr_, "shade or shaded");
	  break;

	case 142:
	  fprintf(stderr_, "center or centre");
	  break;

	case 143:
	  fprintf(stderr_, "ljust");
	  break;

	case 144:
	  fprintf(stderr_, "rjust");
	  break;

	case 145:
	  fprintf(stderr_, "above");
	  break;

	case 146:
	  fprintf(stderr_, "below");
	  break;

	case 148:
	  fprintf(stderr_, "<-");
	  break;

	case 149:
	  fprintf(stderr_, "->");
	  break;

	case 150:
	  fprintf(stderr_, "<->");
	  break;

	case 152:
	  fprintf(stderr_, "up");
	  break;

	case 153:
	  fprintf(stderr_, "down");
	  break;

	case 154:
	  fprintf(stderr_, "right");
	  break;

	case 155:
	  fprintf(stderr_, "left");
	  break;

	case 157:
	  fprintf(stderr_, "box");
	  break;

	case 158:
	  fprintf(stderr_, "circle");
	  break;

	case 159:
	  fprintf(stderr_, "ellipse");
	  break;

	case 160:
	  fprintf(stderr_, "arc");
	  break;

	case 161:
	  fprintf(stderr_, "line");
	  break;

	case 162:
	  fprintf(stderr_, "arrow");
	  break;

	case 163:
	  fprintf(stderr_, "move");
	  break;

	case 164:
	  fprintf(stderr_, "spline");
	  break;

	case 166:
	  fprintf(stderr_, "arcrad");
	  break;

	case 167:
	  fprintf(stderr_, "arrowht");
	  break;

	case 168:
	  fprintf(stderr_, "arrowwid");
	  break;

	case 169:
	  fprintf(stderr_, "boxht");
	  break;

	case 170:
	  fprintf(stderr_, "boxrad");
	  break;

	case 171:
	  fprintf(stderr_, "boxwid");
	  break;

	case 172:
	  fprintf(stderr_, "circlerad");
	  break;

	case 173:
	  fprintf(stderr_, "dashwid");
	  break;

	case 174:
	  fprintf(stderr_, "ellipseht");
	  break;

	case 175:
	  fprintf(stderr_, "ellipsewid");
	  break;

	case 176:
	  fprintf(stderr_, "lineht");
	  break;

	case 177:
	  fprintf(stderr_, "linewid");
	  break;

	case 178:
	  fprintf(stderr_, "moveht");
	  break;

	case 179:
	  fprintf(stderr_, "movewid");
	  break;

	case 180:
	  fprintf(stderr_, "textht");
	  break;

	case 181:
	  fprintf(stderr_, "textoffset");
	  break;

	case 182:
	  fprintf(stderr_, "textwid");
	  break;

	case 183:
	  fprintf(stderr_, "arrowhead");
	  break;

	case 184:
	  fprintf(stderr_, "fillval");
	  break;

	case 185:
	  fprintf(stderr_, "linethick");
	  break;

	case 186:
	  fprintf(stderr_, "maxpsht");
	  break;

	case 187:
	  fprintf(stderr_, "maxpswid");
	  break;

	case 188:
	  fprintf(stderr_, "scale");
	  break;
	  /*B%include controlerrB*/

	default:
	  fprintf(stderr_, "Punctuation characters");
	  break;
	}
      }
      fprintf(stderr_, " found.\n");
      fprintf(stderr_, " The following were expected:\n");
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
	" <name> <envvar> + - ( <corner> Here ! <string> <Label> <float> rand <func1> <func2> sprintf last ` {\n");
      break;

    case 13:
      fprintf(stderr_, " <string>\n");
      break;

    case 14:
      fprintf(stderr_,
	" <envvar> <name> <float> ( rand <func1> <func2> <Label> <corner> Here last ` {\n");
      break;

    case 15:
      fprintf(stderr_, " )\n");
      break;

    case 16:
      fprintf(stderr_, " <string> sprintf\n");
      break;

    case 17:
      fprintf(stderr_, " ( <corner> Here <Label> last <float> ` {\n");
      break;

    case 18:
      fprintf(stderr_, " between of < , + -\n");
      break;

    case 19:
      fprintf(stderr_, " ,\n");
      break;

    case 20:
      fprintf(stderr_, " <compare>\n");
      break;

    case 21:
      fprintf(stderr_, " the\n");
      break;

    case 22:
      fprintf(stderr_, " way\n");
      break;

    case 23:
      fprintf(stderr_, " between\n");
      break;

    case 24:
      fprintf(stderr_, " and\n");
      break;

    case 25:
      fprintf(stderr_, " ) ,\n");
      break;

    case 26:
      fprintf(stderr_, " <name> <envvar>\n");
      break;

    case 27:
      fprintf(stderr_, " =\n");
      break;

    case 28:
      fprintf(stderr_, " ) ||\n");
      break;

    case 29:
      fprintf(stderr_, " ) + -\n");
      break;

    case 30:
      fprintf(stderr_, " , + -\n");
      break;

    case 31:
      fprintf(stderr_, " ] + -\n");
      break;

    case 32:
      fprintf(stderr_, " ' + -\n");
      break;

    case 33:
      fprintf(stderr_, " } + -\n");
      break;

    case 34:
      fprintf(stderr_, " <NL> <ERROR>\n");
      break;

    case 35:
      fprintf(stderr_, " [ []\n");
      break;

    case 36:
      fprintf(stderr_, " to ,\n");
      break;

    case 37:
      fprintf(stderr_, " + - do by\n");
      break;

    case 38:
      fprintf(stderr_, " do + -\n");
      break;

    case 39:
      fprintf(stderr_, " if\n");
      break;

    case 40:
      fprintf(stderr_, " then ||\n");
      break;

    case 41:
      fprintf(stderr_, " <name> <Label>\n");
      break;

    case 42:
      fprintf(stderr_,
	" <corner> at . + - ( Here ! <Label> <envvar> <name> <float> rand <func1> <func2> last ` {\n");
      break;

    case 43:
      fprintf(stderr_, " at\n");
      break;

    case 44:
      fprintf(stderr_, " at of <Label> last <float> ` {\n");
      break;

    case 45:
      fprintf(stderr_, " {\n");
      break;

    case 46:
      fprintf(stderr_, " }\n");
      break;

    case 47:
      fprintf(stderr_, " <envvar>\n");
      break;

    case 48:
      fprintf(stderr_, " <compare> <string> sprintf\n");
      break;

    case 49:
      fprintf(stderr_, " } <NL>\n");
      break;

    case 50:
      fprintf(stderr_, " :\n");
      break;

    case 51:
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
      fprintf(stderr_, "Missing or blank string\n");
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

    case 869:
      fprintf(stderr_, "Improper use of logical operator\n");
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
      fprintf(stderr_, "Safe mode: sh, copy, and print to file disallowed\n");
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


void readline(FILE **infname)
{
  int ll,c;
  if (feof( *infname )) { inputeof = true; return; }
  for (ll = CHBUFSIZ-2; inbuf->savedlen < ll; ) {
     c = getc( *infname );
     if ((char)c == '\n') ll = inbuf->savedlen;
     else if ((char)c == '\r') {
        if ((char)(c=getc( *infname )) != '\n') {
           if (c != EOF) ungetc(c, *infname );
           else if (inbuf->savedlen == 0) { inputeof = true; return; }
           c = '\n'; }
        ll = inbuf->savedlen; }
     else if (c != EOF) {
        inbuf->savedlen++; inbuf->carray[inbuf->savedlen] = (char)c; }
     else if (inbuf->savedlen == 0) { inputeof = true; return; }
     else ll = inbuf->savedlen;
  }
  if (ll != CHBUFSIZ-2) { }
  else if ((char)c == '\n' || c == EOF) { }
  else {
     markerror(902);
     fscanf( *infname, "%*[^\n\r]"); getc( *infname );
  }
  inbuf->savedlen++; inbuf->carray[inbuf->savedlen] = '\n';
  inbuf->savedlen++; inbuf->carray[inbuf->savedlen] = ' ';
  /* [previous] P2CC
     int ll,c;
     if (feof( *infname )) { inputeof = true; return; }
     for (ll = CHBUFSIZ-2; inbuf->savedlen < ll; ) {
        c = getc( *infname );
        if ((char)c == '\n') ll = inbuf->savedlen;
        else if ((char)c == '\r') { ll = inbuf->savedlen;
           if ((char)(c=getc( *infname )) != '\n') ungetc(c, *infname ); }
        else if (c != EOF) {
           inbuf->savedlen++; inbuf->carray[inbuf->savedlen] = (char)c; }
        else if (inbuf->savedlen == 0) { inputeof = true; return; }
        else ll = inbuf->savedlen;
     }
     if ((ll == CHBUFSIZ-2) && ((char)(c=getc( *infname )) != '\n')
        && ((char)c != '\r') && (c != EOF)){
        markerror(902);
        fscanf( *infname, "%*[^\n\r]"); getc( *infname );
     }
     inbuf->savedlen++; inbuf->carray[inbuf->savedlen] = '\n';
     inbuf->savedlen++; inbuf->carray[inbuf->savedlen] = ' ';
     */

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
	    WITH->readx = 4;
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
	WITH->readx = 4;
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
       with inbuf^ do for i:=1 to savedlen do case ord(carray^[i]) of
          ordETX: write(log,'^C');
          ordNL: writeln(log);
          ordCR: write(log,'\r');
          ordTAB: write(log,'\t');
          otherwise write(log,carray^[i])
          end;
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
    ch = '~';
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


void readlatex(void)
{
  /* read complete line into chbuf */
  while (ch != nlch)
    pushch();
  newsymb = XLaTeX;
}


boolean isprint_(Char ch)
{
  return (ch >= 32 && ch <= 126);
}


#ifndef SAFE_MODE

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
    infname[i] = txt->segmnt[txt->seginx + i];
  for (i = txt->len; i < FILENAMELEN; i++)
    infname[i] = ' ';
  /*DUGHM if debuglevel > 0 then begin
     write(log,'Pointinput(segmnt ',seginx:1,', len ',len:1,') ');
     for i := 1 to len do write(log,infname[i]); writeln(log) end; MHGUD*/

  if (savebuf != NULL) {
    markerror(853);
    return;
  }
  if (checkfile(infname, true) != 0) {
    markerror(859);
    return;
  }
  if (copyin != NULL)
    copyin = freopen(P_trimname(infname, sizeof(mstring)), "r", copyin);
  else
    copyin = fopen(P_trimname(infname, sizeof(mstring)), "r");
  if (copyin == NULL)
    _EscIO(FileNotFound);
  backup();
  ch = nlch;
  savebuf = inbuf;
  inbuf = NULL;
}


void pointoutput(boolean nw, nametype *txt, int *ier)
{
  /* nw: boolean; txt: strptr; var ier: integer */
  int i, FORLIM;

  *ier = 1;
  if (txt->segmnt == NULL)
    return;
  if (txt->len >= FILENAMELEN)
    txt->len = FILENAMELEN - 1;
  FORLIM = txt->len;
  for (i = 0; i < FORLIM; i++) {
    outfnam[i] = txt->segmnt[txt->seginx + i];
    if (*ier == 1) {
      if (outfnam[i] > 32 && outfnam[i] <= 126)
	*ier = 0;
    }
  }
  outfnam[txt->len] = '\0';
  /*DUGHM if debuglevel > 0 then begin
     write(log,'Pointoutput(',nw,' segmnt ',seginx:1,', len ',len:1,') "');
     for i := 1 to len do write(log,outfnam[i]); writeln(log,'"') end;
  MHGUD*/
  if (*ier != 0) {
    markerror(861);
    return;
  }
  if (nw) {
    if (redirect != NULL)
      redirect = freopen(P_trimname(outfnam, sizeof(mstring)), "w", redirect);
    else
      redirect = fopen(P_trimname(outfnam, sizeof(mstring)), "w");
    if (redirect == NULL)
      _EscIO(FileNotFound);
    return;
  }
  if (redirect != NULL)
    redirect = freopen(P_trimname(outfnam, sizeof(mstring)), "a", redirect);
  else
    redirect = fopen(P_trimname(outfnam, sizeof(mstring)), "a");
  if (redirect == NULL)
    _EscIO(FileNotFound);
}


#endif

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
      write(log, 'LEXICAL(oldsymb=',oldsymb:1,' newsymb=',newsymb:1,')');
      if newsymb <> XLaTeX then begin
         write(log,' chbuf(',oldbufi:1,':',chbufi-1:1,')="');
         for i := oldbufi to chbufi-1 do write(log, chbuf^[i]);
         write(log,'"') end
      else write(log,'=<LaTeX>');
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
	newsymb = -2;   /* flag for LaTeX test */
	WITH->readx = WITH->savedlen + 2;
	terminalaccepted = false;
      } else if (firstch == '\\')
	readlatex();
      else if (firstch == '.' && isdigit(ch) != 0)
	readconst(firstch);
      else if (firstch == '.' && WITH->readx == 3 && inbuf->prevb == NULL &&
	       newsymb != -2)
	readlatex();
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
		    oldsymb == XLthen || oldsymb == XCOLON || oldsymb == XNL))
	  terminalaccepted = false;
	else if (newsymb == XLT && inlogic) {
	  lexsymb = XLL;
	  newsymb = XLcompare;
	} else if (newsymb > XEQ && newsymb <= XLremeq) {
	  lexsymb = newsymb;
	  newsymb = XEQ;
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
	  else if (newsymb > XLcompare)
	    newsymb = XLcompare;
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
	  /*D if debuglevel > 0 then
	     writeln (log,'800:',ord(firstch),ord(ch)); D*/
	  if (errmp == 0) {
	    fprintf(stderr_, "Char chr(%d)", firstch);
	    if (firstch > 32 && (firstch & 255) < 127)
	      fprintf(stderr_, "\"%c\"", firstch);
	    fprintf(stderr_, " unknown\n");
	  }
	  markerror(800);
	  terminalaccepted = false;
	}
      }
    }

    /*D prlex( terminalaccepted ); D*/
    if (newsymb != XLaTeX && newsymb != XLstring && newsymb != XLabel &&
	newsymb != XLname)
      chbufi = oldbufi;
  } while (!terminalaccepted);
  if (lexsymb == -1)
    lexsymb = newsymb;
  oldsymb = newsymb;



  /* char not recognized */
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
       writeln(log,'Attstack for next production:');
       write(log,'attstack: ');
       for i := 1 to j do write(log,i:4);                   writeln(log);
       write(log,'lexval  : ');
       for i := 1 to j do write(log,attstack^[i].lexval:4); writeln(log);
       write(log,'state   : ');
       for i := 1 to j do write(log,attstack^[i].state:4) ; writeln(log);
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

  errmp = 0;
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
    P_sun_argv(infname, sizeof(mstring), argct);
	/*GH infname := ParamStr(argct); HG*/
    cht = optionchar(infname);
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
      fprintf(stderr_,
	      "     -z safe mode (sh, copy, and print to file disabled)\n");
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
  redirect = NULL;
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
  if (redirect != NULL)
    fclose(redirect);
  exit(EXIT_SUCCESS);
}



/* End. */
