/* Output from p2c, the Pascal-to-C translator */
/* From input file "dpic2.p" */


/*BXsegment dpic2;XB*/
/* onefile */
/* G module dpic2; G */

/* include dp0.h */
/* dp0.x */
/* Global definitions                                                 */


#include "p2c.h"
#include <time.h>


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
extern Char tabch, nlch, crch, etxch;

/* File names                                                         */
extern FILE *input, *output, *stderr_;   /*G asmname 'std_err'; G*/
extern FILE *copyin;   /*G asmname 'copy_in'; G*/
/*D log: text; D*/
/*DG asmname 'log_file'; GD*/

extern mstring infile;   /* name of current input file         */
/*X infile: string; X*/

extern boolean inputeof;   /* end of input flag                  */
extern int argct;   /* argument counter for options       */
extern char drawmode;   /* output conversion                  */
extern boolean safemode;   /* disable sh and copy                */
/*D oflag: integer; D*/

/* Lexical analyzer character buffer                                  */
extern Char *chbuf;
extern chbufinx chbufi, oldbufi;   /* character buffer index             */

/* Lexical variables                                                  */
extern Char ch;   /* current character                  */
extern short newsymb;   /* current lexical symbol             */
extern int inpic, lexsymb;
extern _REC_errmsg errmsg[ERRMAX + 1];
extern boolean inlogic;   /* set < to << in logical context     */
extern fbuffer *inbuf, *savebuf, *freebuf;

/* Error handling                                                     */
extern int errcount;   /* becomes nonzero when errors found  */
extern errmsginx errmp;   /* index of error messages in errmsg  */
extern int lineno;   /* current input line number          */

/* Production variables                                               */
extern attribute *attstack;
/*D stackhigh: integer;D*/
extern redubufrange reduinx, redutop;
extern reduelem redubuf[REDUMAX + REDUMAX + 1];   /* reduction buffer    */

extern double floatvalue;   /* numerical value of floats read     */
extern primitive *envblock;

extern double north, south, east, west;
    /* compass corners of a primitive     */
extern double xfheight;   /* for calculating xfig coordinates   */
extern Char *freeseg;   /* segment open to store strings      */
extern chbufinx freex;   /* next free location                 */
extern Char *tmpbuf;   /* buffer for snprintf or sprintf     */
extern double scale, fsc;   /* scale factor and final scale factor*/
extern int splcount, spltot;   /* spline depth counter               */
extern double lastfillval;   /* last-used fill density             */
extern double lastthick;   /* last-used line thickness           */
extern int printstate;   /* for passing output state info      */

/* Global tables for easy C conversion.
   Alternative: use run-time space    */
extern short lr[lrmax + 1];
extern lxinx entryhp[ordMAXCH + 1];   /* assumes ordMINCH = 0    */
extern lxinx lxhp[lxmax + 1];
extern lxinx lxnp[lxmax + 1];
extern symbol lxtv[lxmax + 1];
extern symbol entrytv[ordMAXCH + 1];
extern Char lxch[lxmax + 1];
/* integer debugging constants        */
/*D debuglevel, linesignal: integer; D*/
/*D trace: boolean; D*/
/* used for debugging the parser      */

/* Parser variables */
extern int oldsymb;   /* last lexical symbol                */
extern arg *macros, *args;   /* macro and macro argument list      */
extern stackinx stacktop, pseudotop, validtop, top;
extern stackelm *parsestack;   /* parse stack          */
extern boolean parsestop;   /* parser flags                       */
extern int startinx, lri, start;


extern void snaptype(FILE **unit, int p);

/*--------------------------------------------------------------------*/
/* onefile */
/* G#include 'dp0.h'G */

/* include dp1.z */
/*dp1.x---------------------------------------------------------------*/
extern int Ceil(double x);

extern int Floor(double x);

extern double Max(double x, double y);

extern double Min(double x, double y);

extern primitive *findenv(primitive *p);

extern arg *findmacro(arg *p, Char *chb, chbufinx inx, chbufinx length,
		      arg **last);

extern boolean isthen(primitive *pr);

extern double linlen(double x, double y);

extern int lspec(int n);

/*DGH function ordp(p:pointer): integer; forward; HGD*/
extern double principal(double x, double r);

extern void checkjust(nametype *tp, boolean *A, boolean *B, boolean *L,
		      boolean *R);

extern void consoleflush(void);

extern void copyleft(fbuffer *mac, fbuffer **buf);

extern void deletetree(primitive **p);

/*D; loc: integerD*/
extern void disposebufs(fbuffer **buf);

extern void drawtree(double n, double s, double e, double w, primitive *eb);

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
/* onefile */
/* G#include 'dp1.z'G */

/* include sysdep.h */
/*DMU#include 'sysdep.h'UMD*/
/* onefile */
/* DG#include 'sysdep.h'GD */

void controls(void)
{
  printf("\n ..controls ");
}


void wrand(void)
{
  printf(" and ");
}


void ddot(void)
{
  printf("\n ..");
}


void ddash(void)
{
  printf("\n --");
}


/* procedure mpocorner( ctr:postype; x,y,r,ct,st: real ); external; */

void wfloat(FILE **iou, double y)
{
  /* var iou: text; y: real */
  char buf[25];
  int i;
  if (fabs(y)==distmax)
     sprintf(buf,"%24.6e", y);
  else if (y >= 0.0)
     sprintf(buf,"%24.6f", floor( 1000000*y+0.5)/1000000.0);
  else
     sprintf(buf,"%24.6f",-floor(-1000000*y+0.5)/1000000.0);
  for (i=23; buf[i]=='0'; ) i-- ;
  if (buf[i]=='.') buf[i] = (char)0;
  else buf[i+1] = (char)0;
  for (;(i>=0)&&(buf[i]!=' ');) i-- ;
  fprintf( *iou,"%s",&buf[i+1]);
}


void wpair(FILE **iou, double x, double y)
{
  /* var iou: text; x,y: real */
  putc('(', *iou);
  wfloat(iou, x);
  putc(',', *iou);
  wfloat(iou, y);
  putc(')', *iou);
}


void wcoord(FILE **iou, double x, double y)
{
  /* var iou: text; x,y: real */
  putc('(', *iou);
  wfloat(iou, x / fsc);
  putc(',', *iou);
  wfloat(iou, y / fsc);
  putc(')', *iou);
  /*DUGHM ;flush(iou) MHGUD*/
}


void wpos(postype pos)
{
  /* pos: postype */
  wcoord(&output, pos.xpos, pos.ypos);
}


void wstring(FILE **iou, nametype *p)
{
  /* var iou: text; p: strptr */
  int i, FORLIM;

  if (p == NULL)
    return;
  if (p->segmnt != NULL) {
    FORLIM = p->seginx + p->len;
    for (i = p->seginx; i < FORLIM; i++)
      putc(p->segmnt[i], *iou);
  }
}


void wbrace(double x)
{
  putchar('{');
  wfloat(&output, x);
  putchar('}');
}


boolean testjust(int n, int flag)
{
  boolean Result;

  switch (flag) {

  case XEMPTY:
    Result = (n == 0);
    break;

  case XLcenter:
    Result = (n == 15);
    break;

  case XLrjust:
    Result = ((n & 3) == 1);
    break;

  case XLljust:
    Result = ((n & 3) == 2);
    break;

  case XLbelow:
    Result = (n >> 2 == 1);
    break;

  case XLabove:
    Result = (n >> 2 == 2);
    break;
  }
  return Result;
}


void checkjust(nametype *tp, boolean *A, boolean *B, boolean *L,
		      boolean *R)
{
  /* tp: strptr; var A,B,L,R: boolean */
  int i;

  if (tp == NULL)
    return;
  i = (long)floor(tp->val + 0.5);
  *A = testjust(i, XLabove);
  *B = testjust(i, XLbelow);
  *L = testjust(i, XLljust);
  *R = testjust(i, XLrjust);
}


primitive *findenv(primitive *p)
{
  /* p: primitivep ): primitivep; external */
  primitive *q;

  q = NULL;
  while (p != q) {
    if (p->ptype != XBLOCK)
      p = p->parent;
    else if (p->UU.UEMPTY7.env == NULL)
      p = p->parent;
    else
      q = p;
  }
  /*D if p = nil then writeln(log,'findenv: p=nil')
     else if p^.env = nil then writeln(log,'findenv: p^.env=nil');
     flush(log); D*/
  return p;
}


double venv(primitive *p, int ind)
{
  double v;

  v = 0.0;
  if (ind <= XLenvvar || ind > XLlastenv)
    return v;
  p = findenv(p);
  if (p != NULL)
    v = p->UU.UEMPTY7.env[ind - XLenvvar - 1];
  return v;
}


double qenv(primitive *p, int ind, double localval)
{
  double y;

  if (ind == XLfillval)
    y = -1.0;
  else if (ind == XLlinethick)
    y = mdistmax;
  else
    y = 0.0;
  if (localval != y)
    return localval;
  else
    return (venv(p, ind));
}


/*        orig + mat(cs) * [x,y] */
postype affine(double x, double y, postype orig, postype cs)
{
  postype tpos;

  tpos.xpos = orig.xpos + cs.xpos * x - cs.ypos * y;
  tpos.ypos = orig.ypos + cs.ypos * x + cs.xpos * y;
  return tpos;
}


postype affang(postype point, postype shaft)
{
  double lgth;
  postype tpos;

  lgth = linlen(shaft.xpos - point.xpos, shaft.ypos - point.ypos);
  if (lgth == 0.0) {
    tpos.xpos = 1.0;
    tpos.ypos = 0.0;
  } else {
    tpos.xpos = (shaft.xpos - point.xpos) / lgth;
    tpos.ypos = (shaft.ypos - point.ypos) / lgth;
  }
  return tpos;
}


void initnesw(void)
{
  south = distmax;
  north = -south;
  west = south;
  east = -west;
}


/* Local variables for nesw: */
struct LOC_nesw {
  double heght, wdth;
} ;

Local void neswstring(primitive *pmp, struct LOC_nesw *LINK)
{
  boolean A, B, L, R;
  double x, y, offst;

  if (pmp == NULL)
    return;
  offst = venv(pmp, XLtextoffset);
  checkjust(pmp->textp, &A, &B, &L, &R);
  y = pmp->aat.ypos;
  if (A)
    y += LINK->heght * 0.5 + offst;
  else if (B)
    y += -LINK->heght * 0.5 - offst;
  x = pmp->aat.xpos;
  if (R)
    x += -LINK->wdth * 0.5 - offst;
  else if (L)
    x += LINK->wdth * 0.5 + offst;
  north = Max(north, y + LINK->heght * 0.5);
  south = Min(south, y - LINK->heght * 0.5);
  west = Min(west, x - LINK->wdth * 0.5);
  east = Max(east, x + LINK->wdth * 0.5);
}

Local void neswline(primitive *pmp, struct LOC_nesw *LINK)
{
  double aht, awd;
  postype cs, cc, cd;

  if (pmp == NULL)
    return;
  west = Min(west, Min(pmp->aat.xpos, pmp->UU.Uline.endpos.xpos));
  east = Max(east, Max(pmp->aat.xpos, pmp->UU.Uline.endpos.xpos));
  south = Min(south, Min(pmp->aat.ypos, pmp->UU.Uline.endpos.ypos));
  north = Max(north, Max(pmp->aat.ypos, pmp->UU.Uline.endpos.ypos));
  if (pmp->UU.Uline.atype == XLEFTHEAD || pmp->UU.Uline.atype == XDOUBLEHEAD) {
    cs = affang(pmp->aat, pmp->UU.Uline.endpos);
    awd = qenv(pmp, XLarrowht, pmp->UU.Uline.width);
    aht = qenv(pmp, XLarrowwid, pmp->UU.Uline.height);
    cc = affine(aht, awd / 2, pmp->aat, cs);
    cd = affine(aht, awd / -2, pmp->aat, cs);
    west = Min(west, Min(cc.xpos, cd.xpos));
    east = Max(east, Max(cc.xpos, cd.xpos));
    south = Min(south, Min(cc.ypos, cd.ypos));
    north = Max(north, Max(cc.ypos, cd.ypos));
  }
  if (pmp->UU.Uline.atype != XRIGHTHEAD && pmp->UU.Uline.atype != XDOUBLEHEAD)
    return;
  cs = affang(pmp->UU.Uline.endpos, pmp->aat);
  awd = qenv(pmp, XLarrowht, pmp->UU.Uline.width);
  aht = qenv(pmp, XLarrowwid, pmp->UU.Uline.height);
  cc = affine(aht, awd / 2, pmp->UU.Uline.endpos, cs);
  cd = affine(aht, awd / -2, pmp->UU.Uline.endpos, cs);
  west = Min(west, Min(cc.xpos, cd.xpos));
  east = Max(east, Max(cc.xpos, cd.xpos));
  south = Min(south, Min(cc.ypos, cd.ypos));
  north = Max(north, Max(cc.ypos, cd.ypos));
}

Local boolean inarc(double strt, double fin, double ang, double arcang,
		    struct LOC_nesw *LINK)
{
  boolean inarctmp;

  /*D if debuglevel > 0 then begin
     write(log,'Inarc strt,fin='); wfloat(log,strt*180.0/pi);
        write(log,' ' ); wfloat(log,fin*180.0/pi);
     write(log,' ang,arcang='); wfloat(log,ang*180.0/pi);
        write(log,' ' ); wfloat(log,arcang*180.0/pi) end; D*/
  if (arcang >= 0.0) {
    while (fin < strt)
      fin += 2.0 * pi;
    while (ang < strt)
      ang += 2.0 * pi;
    if (ang <= fin)
      inarctmp = true;
    else
      inarctmp = false;
    return inarctmp;
  }
  while (fin > strt)
    fin -= 2.0 * pi;
  while (ang > strt)
    ang -= 2.0 * pi;
  if (ang >= fin)
    inarctmp = true;
  else
    inarctmp = false;
  return inarctmp;
  /*D; if debuglevel > 0 then writeln(log,' Inarc =',inarctmp) D*/
}


void nesw(primitive *ptmp)
{
  /* ptmp: primitivep */
  struct LOC_nesw V;
  double sa, ea;

  if (ptmp == NULL)
    return;
  switch (ptmp->ptype) {

  case XLbox:
  case XLstring:
    V.heght = ptmp->UU.Ubox.boxheight;
    V.wdth = ptmp->UU.Ubox.boxwidth;
    break;

  case XBLOCK:
    V.heght = ptmp->UU.UEMPTY7.blockheight;
    V.wdth = ptmp->UU.UEMPTY7.blockwidth;
    break;

  case XLcircle:
    V.heght = 2.0 * ptmp->UU.Ucircle.radius;
    V.wdth = 2.0 * ptmp->UU.Ucircle.radius;
    break;

  case XLellipse:
    V.heght = ptmp->UU.Uellipse.elheight;
    V.wdth = ptmp->UU.Uellipse.elwidth;
    break;
  }
  switch (ptmp->ptype) {

  case XLbox:
  case XBLOCK:
  case XLcircle:
  case XLellipse:
    north = Max(north, ptmp->aat.ypos + V.heght * 0.5);
    south = Min(south, ptmp->aat.ypos - V.heght * 0.5);
    west = Min(west, ptmp->aat.xpos - V.wdth * 0.5);
    east = Max(east, ptmp->aat.xpos + V.wdth * 0.5);
    break;

  case XLstring:
    neswstring(ptmp, &V);
    break;

  case XLline:
  case XLarrow:
  case XLmove:
  case XLspline:
    neswline(ptmp, &V);
    break;

  case XLtroff:
  case XLabel:
    /* blank case */
    break;

  case XLarc:
    sa = principal(ptmp->UU.Uline.endpos.xpos, pi);
    ea = ptmp->UU.Uline.endpos.xpos + ptmp->UU.Uline.endpos.ypos;
    /*D if debuglevel > 0 then begin write(log,'(sa,ea)(deg)=');
       wpair(log,sa*180/pi,ea*180/pi); writeln(log) end; D*/
    if (inarc(sa, ea, 0.5 * pi, ptmp->UU.Uline.endpos.ypos, &V))
      north = Max(north, ptmp->aat.ypos + ptmp->UU.Uline.aradius);
    else
      north = Max(north,
	  ptmp->aat.ypos + ptmp->UU.Uline.aradius * Max(sin(sa), sin(ea)));
    if (inarc(sa, ea, -0.5 * pi, ptmp->UU.Uline.endpos.ypos, &V))
      south = Min(south, ptmp->aat.ypos - ptmp->UU.Uline.aradius);
    else
      south = Min(south,
	  ptmp->aat.ypos + ptmp->UU.Uline.aradius * Min(sin(sa), sin(ea)));
    if (inarc(sa, ea, pi, ptmp->UU.Uline.endpos.ypos, &V))
      west = Min(west, ptmp->aat.xpos - ptmp->UU.Uline.aradius);
    else
      west = Min(west,
	  ptmp->aat.xpos + ptmp->UU.Uline.aradius * Min(cos(sa), cos(ea)));
    if (inarc(sa, ea, 0.0, ptmp->UU.Uline.endpos.ypos, &V))
      east = Max(east, ptmp->aat.xpos + ptmp->UU.Uline.aradius);
    else
      east = Max(east,
	  ptmp->aat.xpos + ptmp->UU.Uline.aradius * Max(cos(sa), cos(ea)));
    break;
  }
  /*D;if debuglevel > 0 then with ptmp^ do begin
     write(log, 'nesw(',ordp(ptmp):1,') ptype=',ptype:1,' (W,S)=');
     wpair(log,west,south); write(log,' (E,N)='); wpair(log,east,north);
     writeln(log) end D*/
}  /* nesw */


double linlen(double x, double y)
{
  /* x,y: real ): real */
  double xm, ym;

  /* linlen := sqrt( x*x + y*y ) */
  if (fabs(x) > fabs(y)) {
    xm = fabs(x);
    ym = y / xm;
    return (xm * sqrt(1.0 + ym * ym));
  }
  if (y == 0.0) {
    xm = 0.0;
    ym = 0.0;
  } else {
    xm = fabs(y);
    ym = x / xm;
  }
  return (xm * sqrt(1.0 + ym * ym));
}


void stacktext(nametype *tp, boolean box)
{
  nametype *tx;
  boolean A, B, L, R;

  if (tp == NULL)
    return;
  if (box) {
    checkjust(tp, &A, &B, &L, &R);
    printf("\\makebox(0,0)");
    if (L)
      printf("[l]");
    else if (R)
      printf("[r]");
    putchar('{');
  }
  tx = tp->next_;
  if (tx != NULL)
    printf("\\shortstack{");
  do {
    checkjust(tp, &A, &B, &L, &R);
    if (L)
      printf("\\rlap{");
    else if (R)
      printf("\\llap{");
    wstring(&output, tp);
    if (L || R)
      putchar('}');
    tp = tp->next_;
    if (tp != NULL)
      printf("\\\\\n");
  } while (tp != NULL);
  if (tx != NULL)
    putchar('}');
  if (box)
    putchar('}');
}


int primdepth(primitive *ptmp)
{
  int dep;

  dep = 0;
  while (ptmp != NULL) {
    dep++;
    ptmp = ptmp->son;
  }
  return dep;
}


void pprop(postype p1, postype *p2, double a, double b, double c)
{
  if (c != 0.0) {
    p2->xpos = (a * p1.xpos + b * p2->xpos) / c;
    p2->ypos = (a * p1.ypos + b * p2->ypos) / c;
  }
}


void wprop(postype p1, postype p2, double a, double b, double c)
{
  pprop(p1, &p2, a, b, c);   /* Note: p2 is not var */
  wpos(p2);
}


boolean iscorner(double theta)
{
  /*Dif debuglevel = 2 then
    writeln(log,'iscorner(',theta*180/pi:7:4,')=',
      (abs(theta) < 0.001) or (abs(0.5*pi-abs(theta)) < 0.001)); D*/
  return (fabs(theta) < 0.001 || fabs(0.5 * pi - fabs(theta)) < 0.001);
}


int hcf(int x, int y)
{
  int i, small, large;

  if (x < 0)
    x = -x;
  if (y < 0)
    y = -y;
  if (y < x) {
    small = y;
    large = x;
  } else {
    small = x;
    large = y;
  }
  while (small > 0) {
    i = small;
    small = large % small;
/* p2c: dpic2.p, line 778:
 * Note: Using % for possibly-negative arguments [317] */
    large = i;
  }
  if (large == 0)
    return 1;
  else
    return large;
}


int iabs(int i)
{
  if (i < 0)
    return (-i);
  else
    return i;
}


void wrslope(double xp, double yp, boolean arrow)
{
  int i, ix, iy;
  double r;

  /*D if debuglevel > 0 then writeln(log,'wrslope xp,yp: ',xp,yp); D*/
  if (xp == 0.0 && yp == 0.0) {
    xp = 1.0;
    yp = 0.0;
  }
  r = linlen(xp, yp);
  if (drawmode == pict2e)
    i = 1000;   /*4096*/
  else if (drawmode == tTeX)
    i = 453;
  else if (arrow)
    i = 4;
  else
    i = 6;
  iy = (long)floor((i + 0.49999) * yp / r + 0.5);
  ix = (long)floor((i + 0.49999) * xp / r + 0.5);
  i = hcf(ix, iy);
  iy /= i;
  ix /= i;
  /*D if debuglevel > 0 then begin
         write(log,' ix,iy: ',ix:6,iy:6);
         if ix = 0 then writeln(log,' {',abs(yp)/fsc,'}')
         else writeln(log,' {',abs(xp)/fsc,'}')
         end; D*/
  printf("(%d,%d)", ix, iy);
  if (ix == 0)
    wbrace(fabs(yp) / fsc);
  else
    wbrace(fabs(xp) / fsc);
}


int lspec(int n)
{
  /* n: integer): integer */
  /* if ((n div 16) mod 2) <> 0 then lspec := XLsolid
  else */
  return ((n & 7) + XLlinetype);
}


boolean isthen(primitive *pr)
{
  /* pr: primitivep ): boolean */
  if (pr == NULL)
    return false;
  else
    return (((pr->spec >> 3) & 1) != 0);
}


boolean drawn(primitive *node, int lsp, double fill)
{
  if (node == NULL)
    return false;
  else if (node->shadedp != NULL)
    return true;
  else if (lsp == XLpath || lsp == XLdotted || lsp == XLdashed ||
	   lsp == XLsolid || fill >= 0.0 && fill <= 1.0)
    return true;
  else
    return false;
}


/* include xfig.h */
/* xfig.x */
/* Output routines for xfig */

#define xfigres         1200
#define dispres         80
#define points          72


void xfigprelude(void)
{
  /* writeln('#FIG 3.1');
     writeln('Landscape');
     writeln('Center');
     writeln('Inches');
     writeln(xfigres:1,' 2');
     writeln('# ',Version, ' for Fig 3.1')
     */

  printf("#FIG 3.2\n");
  printf("Landscape\n");
  printf("Center\n");
  printf("Inches\n");
  printf("Letter\n");
  printf("100.00\n");
  printf("Single\n");
  printf("-2\n");
  printf("# %s for Fig 3.2\n", Version);
  printf("%ld 2\n", (long)xfigres);

}


void wfigpt(double x)
{
  printf(" %ld", (long)floor(x / fsc * xfigres + 0.5));
}


void wfigcoord(double x, double y)
{
  wfigpt(x);
  wfigpt(xfheight - y);
}


void arrowline(double wid, double ht, double lth)
{
  /* arrowtype,arrowstyle: integer;
     arrowthickness,arrowwidth,arrowheight: real */
  printf("%c1 1 ", tabch);   /* style: closed, filled */
  wfloat(&output, lth * dispres / points);
  putchar(' ');
  wfloat(&output, wid * xfigres);
  putchar(' ');
  wfloat(&output, ht * xfigres);
  putchar('\n');
}


int linstyle(int i)
{
  if (i == XLsolid) {
    i = 0;
    return i;
  }
  if (i == XLdashed) {
    i = 1;
    return i;
  }
  if (i == XLdotted)
    i = 2;
  else
    i = -1;
  return i;
}


void hdrline(int object_code, int sub_type, int line_style, double lth,
		    double gfill)
{
  /* first 10 values object_code .. style_val */
  printf("%d %d %d ", object_code, sub_type, linstyle(line_style));

  if (line_style == XLinvis)
    printf("0 ");
  else
    printf("%ld ", (long)floor(lth * dispres / points + 0.5));
  printf("0 -1 0 -1 ");   /* pencolor, fillcolor, depth, penstyle */
  if (gfill == -1.0)
    printf("-1 ");   /* area fill */
  else
    printf("%ld ", (long)floor((1.0 - gfill) * 20 + 0.5));

  /* style_val */
  if (line_style == XLdashed)
    wfloat(&output, 5.0 / points * dispres);
  else if (line_style == XLdotted)
    wfloat(&output, 3.0 / points * dispres);
  else
    putchar('0');
  putchar(' ');
}


int fwdarrow(int i)
{
  if (i == XRIGHTHEAD || i == XDOUBLEHEAD)
    return 1;
  else
    return 0;
}


int bckarrow(int i)
{
  if (i == XLEFTHEAD || i == XDOUBLEHEAD)
    return 1;
  else
    return 0;
}


void polyline(int object_code, int sub_type, int line_style,
		     double lth, double gfill, double lrad, int atype,
		     double lwid, double lht, int npoints)
{
  hdrline(object_code, sub_type, line_style, lth, gfill);
  if (object_code == 3) {
    printf("0 ");   /* cap_style = butt for splines */
    /* join_style = miter, cap_style = butt, radius */
  } else
    printf("0 0 %ld ", (long)floor(lrad * dispres + 0.5));
  printf("%d %d %d\n", fwdarrow(atype), bckarrow(atype), npoints);
  if (fwdarrow(atype) == 1)
    arrowline(lwid, lht, lth);
  if (bckarrow(atype) == 1)
    arrowline(lwid, lht, lth);
}


void xfigwrtext(primitive *np, nametype *tp, double bxht, double bxwid,
		       double x, double y)
{
  double ydisp;
  int istr, nstr, figjust, i;
  boolean A, B, L, R;
  nametype *p;
  int FORLIM;

  if (bxht == 0.0)
    bxht = venv(np, XLtextht);
  if (tp != NULL) {
    nstr = 0;
    p = tp;
    do {
      nstr++;
      p = p->next_;
    } while (p != NULL);
    checkjust(tp, &A, &B, &L, &R);
    istr = 0;
  }
  while (tp != NULL) {
    istr++;
    printf("4 ");
    if (L)
      figjust = 0;
    else if (R)
      figjust = 2;
    else
      figjust = 1;
    printf("%d ", figjust);
    printf("-1 0 -1 ");   /* color, depth, penstyle */
    printf("0 10 0.0 2");   /* font, font_size, angle, font_flags */
    wfigpt(bxht);
    if (bxwid == 0)
      wfigpt(tp->len * bxht * 2 / 3);
    else
      wfigpt(bxwid);
    /*D if debuglevel > 0 then writeln(log,
      ' bxht=',bxht:9:2,' bxwid=',bxwid:9:2,' length=',tp^.len:1); D*/
    if (A)
      ydisp = bxht / 5 + venv(np, XLtextoffset);
    else if (B)
      ydisp = -bxht - venv(np, XLtextoffset);
    else
      ydisp = bxht / -3;
    wfigcoord(x, y + ydisp + ((nstr + 1.0) / 2 - istr) * bxht);
    putchar(' ');
    FORLIM = tp->len;
    for (i = 0; i < FORLIM; i++) {
      if (tp->segmnt[tp->seginx + i] == '\\')
	putchar('\\');
      putchar(tp->segmnt[tp->seginx + i]);
    }
    printf("\\001\n");
    tp = tp->next_;
  }
}


void farc(int object_code, int sub_type, int line_style, double lth,
		 double gfill, int atype, double radius, double strtang,
		 double arcang, double x, double y, double lwid, double lht)
{
  hdrline(object_code, sub_type, line_style, lth, gfill);
  printf("0 ");
  if (arcang < 0.0)
    printf("0 ");
  else
    printf("1 ");
  printf("%d %d ", fwdarrow(atype), bckarrow(atype));
  wfigcoord(x, y);
  wfigcoord(x + radius * cos(strtang), y + radius * sin(strtang));
  wfigcoord(x + radius * cos(strtang + arcang / 2),
	    y + radius * sin(strtang + arcang / 2));
  wfigcoord(x + radius * cos(strtang + arcang),
	    y + radius * sin(strtang + arcang));
  putchar('\n');
  if (fwdarrow(atype) == 1)
    arrowline(lwid, lht, lth);
  if (bckarrow(atype) == 1)
    arrowline(lwid, lht, lth);
}


void fellipse(int object_code, int sub_type, int line_style,
		     double lth, double gfill, double center_x,
		     double center_y, double radius_x, double radius_y)
{
  hdrline(object_code, sub_type, line_style, lth, gfill);
  printf("1 0.0");
  wfigcoord(center_x, center_y);
  wfigpt(radius_x);
  wfigpt(radius_y);
  wfigcoord(center_x + radius_x, center_y);
  wfigcoord(center_x + radius_x, center_y);
  putchar('\n');
}


boolean rdrawn(primitive *np)
{
  boolean rv, v;
  primitive *WITH;

  rv = false;
  while (rv == false && np != NULL) {
    WITH = np;
    if (WITH->ptype == XLbox)
      v = drawn(np, lspec(WITH->spec), WITH->UU.Ubox.boxfill);
    else if (WITH->ptype == XLcircle)
      v = drawn(np, lspec(WITH->spec), WITH->UU.Ucircle.cfill);
    else if (WITH->ptype == XLellipse)
      v = drawn(np, lspec(WITH->spec), WITH->UU.Uellipse.efill);
    else if (WITH->ptype == XLspline || WITH->ptype == XLarrow ||
	     WITH->ptype == XLline || WITH->ptype == XLarc) {
      /* v := drawn(np,lspec(spec),-1.0) */
      v = drawn(np, lspec(WITH->spec), WITH->UU.Uline.lfill);
    } else
      v = false;
    if (v || WITH->textp != NULL) {
      rv = true;
      break;
    }
    if (rdrawn(WITH->son))
      rv = true;
    else
      np = WITH->next_;
  }
  return rv;
}


void xfigdraw(primitive *node)
{
  int i, lsp;
  double fill;
  int FORLIM;

  lsp = lspec(node->spec);
  if (node->lthick < 0.0)
    node->lthick = venv(node, XLlinethick);
  /*D if debuglevel > 0 then with node^ do begin
     write(log,'xfigdraw(',ordp(node):1,'): lthick=',lthick:9:2,' ');
     snaptype(log,ptype); writeln(log)
     end; D*/
  switch (node->ptype) {

  case XLarc:
    /* if drawn(node,lsp,-1.0) then farc(5,1,lsp,lthick, */
    if (drawn(node, lsp, node->UU.Uline.lfill)) {
      /* -1.0,atype,aradius,endpos.xpos, */
      farc(5, 1, lsp, node->lthick, node->UU.Uline.lfill, node->UU.Uline.atype,
	   node->UU.Uline.aradius, node->UU.Uline.endpos.xpos,
	   node->UU.Uline.endpos.ypos, node->aat.xpos, node->aat.ypos,
	   node->UU.Uline.width, node->UU.Uline.height);
    }
    xfigwrtext(node, node->textp, 0.0, 0.0, node->aat.xpos, node->aat.ypos);
    break;

  case XLline:
  case XLarrow:
  case XLspline:
    /* if drawn(node,lsp,-1.0) then begin */
    if (drawn(node, lsp, node->UU.Uline.lfill)) {
      if (!isthen(node)) {
	spltot = primdepth(node);
	if (node->ptype == XLspline) {
	  /* -1.0,0.0,atype,width,height,spltot+1) */
	  polyline(3, 0, lsp, node->lthick, node->UU.Uline.lfill, 0.0,
		   node->UU.Uline.atype, node->UU.Uline.width,
		   node->UU.Uline.height, spltot + 1);
	} else {
	  /* -1.0,0.0,atype,width,height,spltot+1); */
	  polyline(2, 1, lsp, node->lthick, node->UU.Uline.lfill, 0.0,
		   node->UU.Uline.atype, node->UU.Uline.width,
		   node->UU.Uline.height, spltot + 1);
	}
	putchar(tabch);
	wfigcoord(node->aat.xpos, node->aat.ypos);
      }
      wfigcoord(node->UU.Uline.endpos.xpos, node->UU.Uline.endpos.ypos);
      if (node->son == NULL && node->ptype == XLspline) {
	printf("\n%c 0.0", tabch);
	FORLIM = spltot;
	for (i = 2; i <= FORLIM; i++)
	  printf(" 1.0");
	printf(" 0.0\n");
      } else if (node->son == NULL)
	putchar('\n');
    }
    xfigwrtext(node, node->textp, 0.0, 0.0,
	       0.5 * (node->UU.Uline.endpos.xpos + node->aat.xpos),
	       0.5 * (node->aat.ypos + node->UU.Uline.endpos.ypos));
    break;

  case XBLOCK:
  case XLbox:
    initnesw();
    nesw(node);
    if ((node->ptype == XBLOCK) & ((node->textp != NULL) | drawn(node, lsp,
				     -1.0) | rdrawn(node->son))) {
      node->direction = -1;
      printf("6 ");
      wfigcoord(west, north);
      wfigcoord(east, south);
      putchar('\n');
    }
    if (node->ptype == XBLOCK)
      fill = -1.0;
    else
      fill = node->UU.Ubox.boxfill;
    if (drawn(node, lsp, fill)) {
      polyline(2, 2, lsp, node->lthick, fill, 0.0, -1, 0.0, 0.0, 6);
      putchar(tabch);
      wfigcoord(west, (south + north) / 2);
      wfigcoord(west, south);
      wfigcoord(east, south);
      wfigcoord(east, north);
      wfigcoord(west, north);
      wfigcoord(west, (south + north) / 2);
      putchar('\n');
    }
    xfigwrtext(node, node->textp, 0.0, 0.0, node->aat.xpos, node->aat.ypos);
    break;

  case XLmove:
    xfigwrtext(node, node->textp, 0.0, 0.0,
	       0.5 * (node->UU.Uline.endpos.xpos + node->aat.xpos),
	       0.5 * (node->aat.ypos + node->UU.Uline.endpos.ypos));
    break;

  case XLellipse:
    if (drawn(node, lsp, node->UU.Uellipse.efill))
      fellipse(1, 1, lsp, node->lthick, node->UU.Uellipse.efill, node->aat.xpos,
	       node->aat.ypos, 0.5 * node->UU.Uellipse.elwidth,
	       0.5 * node->UU.Uellipse.elheight);
    xfigwrtext(node, node->textp, 0.0, 0.0, node->aat.xpos, node->aat.ypos);
    break;

  case XLcircle:
    if (drawn(node, lsp, node->UU.Ucircle.cfill))
      fellipse(1, 3, lsp, node->lthick, node->UU.Ucircle.cfill, node->aat.xpos,
	       node->aat.ypos, node->UU.Ucircle.radius, node->UU.Ucircle.radius);
    xfigwrtext(node, node->textp, 0.0, 0.0, node->aat.xpos, node->aat.ypos);
    break;

  case XLstring:
    xfigwrtext(node, node->textp, node->UU.Ubox.boxheight,
	       node->UU.Ubox.boxwidth, node->aat.xpos, node->aat.ypos);
    break;

  case XLtroff:
    if (node->textp != NULL) {
      wstring(&output, node->textp);
      putchar('\n');
    }
    break;
  }
}  /* xfigdraw */


/* include pgf.h */
/* pgf.x */
/* pgf output routines */
void pgfprelude(void)
{
  /* n,s,e,w: real */
  printf("\\begin{tikzpicture}[scale=2.54]\n");
  printf("%% %s for TikZ and PGF 1.01\n", Version);
  printf("\\ifx\\dpiclw\\undefined\\newdimen\\dpiclw\\fi\n");
  printf("\\global\\def\\dpicdraw{\\draw[line width=\\dpiclw]}\n");
  printf("\\global\\def\\dpicstop{;}\n");
  printf("\\dpiclw=0.8bp\n");
}


void pgfpostlude(void)
{
  printf("\\end{tikzpicture}\n");
  /*D; if debuglevel > 0 then writeln(log,'pgfpostlude done') D*/
}


void pgfwrtext(primitive *np, nametype *tp, double x, double y)
{
  /* const tof=4.0; PC versions of P2C crash on low-level const statements */
  boolean A, B, L, R;

  if (tp == NULL)
    return;
  checkjust(tp, &A, &B, &L, &R);
  printf("\\draw ");
  wcoord(&output, x, y);
  printf(" node");
  if (A || B || L || R) {
    putchar('[');
    if (A && L)
      printf("above right");
    else if (A && R)
      printf("above left");
    else if (B && L)
      printf("below right");
    else if (B && R)
      printf("below left");
    else if (A)
      printf("above");
    else if (B)
      printf("below");
    else if (L)
      printf("right");
    else if (R)
      printf("left");
    putchar('=');
    /* Assume pgf built-in text offset = 4 bp */
    wfloat(&output, (venv(np, XLtextoffset) * 72 / scale - 4.0) / fsc);
    printf("bp]");
  }
  putchar('{');
  stacktext(tp, false);
  printf("};\n");
}


void pgfendpath(void)
{
  printf("\\dpicstop\n");
}


void pgfsetthick(double lthick)
{
  if (lthick == mdistmax) {
    if (lastthick != mdistmax)
      lthick = lastthick;
    else
      lthick = 0.8;
  }
  /*Dif debuglevel > 0 then begin
     writeln(log); writeln(log,'lthick=',lthick,' lastthick=',lastthick)
     end;D*/
  if (lthick < 0.0 || lthick == lastthick)
    return;
  printf("\\dpiclw=");
  wfloat(&output, lthick);
  printf("bp\n");
  lastthick = lthick;
}


void pgfbox(postype ctr, double halfwid, double halfht, double rad)
{
  double r, h, v;

  if (rad == 0.0) {
    wcoord(&output, ctr.xpos - halfwid, ctr.ypos - halfht);
    printf(" rectangle ");
    wcoord(&output, ctr.xpos + halfwid, ctr.ypos + halfht);
    pgfendpath();
    return;
  }
  r = Min(Min(rad, halfht), halfwid);
  h = halfwid - r;
  v = halfht - r;
  mpocorner(ctr, h, v, r, 1.0, 0.0);
  mpocorner(ctr, -h, v, r, 0.0, 1.0);
  mpocorner(ctr, -h, -v, r, -1.0, 0.0);
  mpocorner(ctr, h, -v, r, 0.0, -1.0);
  printf("cycle");
  pgfendpath();
}


void pgfahead(postype *point, postype shaft, double ht, double wid)
{
  postype butx, cs;

  cs = affang(*point, shaft);
  butx = affine(ht, 0.0, *point, cs);
  wpos(butx);
  ddash();
  wpos(affine(ht, wid / 2, *point, cs));
  ddash();
  wpos(*point);
  ddash();
  wpos(affine(ht, wid / -2, *point, cs));
  printf("\n --cycle");
  pgfendpath();
  *point = butx;
}


void pgfstartdraw(int initial, primitive *node, int lsp)
{
  Char sep;
  double fill;

  if (lsp == XLinvis)
    printf("\\fill");
  else if (initial == 0)
    printf("\\dpicdraw");
  else
    printf("\\filldraw");
  fill = -1.0;
  switch (node->ptype) {

  case XBLOCK:
    /* blank case */
    break;

  case XLbox:
    fill = node->UU.Ubox.boxfill;
    break;

  case XLcircle:
    fill = node->UU.Ucircle.cfill;
    break;

  case XLellipse:
    fill = node->UU.Uellipse.efill;
    break;

  case XLline:
  case XLarrow:
  case XLmove:
  case XLspline:
    fill = node->UU.Uline.lfill;
    break;
  }
  fill = (long)floor(fill * 1000000L + 0.5) / 1000000.0;
  if (node->shadedp != NULL) {
    printf("[fill=");
    wstring(&output, node->shadedp);
    sep = ',';
  } else if (fill >= 0.0 && fill <= 1.0) {
    printf("[fill=");
    if (fill == 0.0)
      printf("black");
    else if (fill == 0.25)
      printf("darkgray");
    else if (fill == 0.5)
      printf("gray");
    else if (fill == 0.75)
      printf("lightgray");
    else if (fill == 1.0)
      printf("white");
    else {
      printf("white!");
      wfloat(&output, fill * 100);
      printf("!black");
    }
    sep = ',';
  } else
    sep = '[';
  if (node->lthick >= 0.0) {
    printf("%cline width=", sep);
    wfloat(&output, node->lthick);
    printf("bp");
    sep = ',';
  }
  if (node->outlinep != NULL) {
    printf("%cdraw=", sep);
    wstring(&output, node->outlinep);
    if (initial == 1) {
      printf(",fill=");
      wstring(&output, node->outlinep);
    }
    sep = ',';
  }
  if (lsp == XLdashed && initial != 1) {
    if (node->lparam <= 0)
      printf("%cdashed", sep);
    else {
      printf("%cdash pattern=on ", sep);
      wfloat(&output, node->lparam / fsc);
      printf("in off ");
      wfloat(&output, node->lparam / fsc);
      printf("in");
    }
    sep = ',';
  } else if (lsp == XLdotted) {
    if (node->lparam <= 0)
      printf("%cdotted", sep);
    else {
      printf("%ccap=round,dash pattern=on ", sep);
      printf("0pt off ");
      wfloat(&output, node->lparam * 72 / fsc);
      printf("bp");
    }
    sep = ',';
  }
  if (sep == ',')
    putchar(']');
  else
    putchar(' ');
}


void pgfdraw(primitive *node)
{
  /* node is always <> nil */
  int lsp, n;
  postype tmpat, X0, X3;
  primitive *tn;
  double x, y, xx, xy;
  boolean v;

  lsp = lspec(node->spec);
  switch (node->ptype) {

  case XLbox:
  case XBLOCK:
    initnesw();
    nesw(node);
    if (node->ptype == XBLOCK)
      v = drawn(node, lsp, -1.0);
    else
      v = drawn(node, lsp, node->UU.Ubox.boxfill);
    if (v) {
      pgfstartdraw(0, node, lsp);
      pgfbox(node->aat, node->UU.Ubox.boxwidth / 2,
	     node->UU.Ubox.boxheight / 2, node->UU.Ubox.boxradius);
    }
    pgfwrtext(node, node->textp, 0.5 * (east + west), 0.5 * (north + south));
    break;

  case XLellipse:
    if (drawn(node, lsp, node->UU.Uellipse.efill)) {
      pgfstartdraw(0, node, lsp);
      wpos(node->aat);
      printf(" ellipse (");
      wfloat(&output, node->UU.Uellipse.elwidth / 2 / fsc / 2.54);
      printf("in and ");
      wfloat(&output, node->UU.Uellipse.elheight / 2 / fsc / 2.54);
      printf("in)");
      pgfendpath();
    }
    pgfwrtext(node, node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLcircle:
    if (drawn(node, lsp, node->UU.Ucircle.cfill)) {
      pgfstartdraw(0, node, lsp);
      wpos(node->aat);
      printf(" circle (");
      wfloat(&output, node->UU.Ucircle.radius / fsc / 2.54);
      printf("in)");
      pgfendpath();
    }
    pgfwrtext(node, node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLspline:
    if (drawn(node, lsp, -1.0)) {
      if (node->UU.Uline.aradius == mdistmax)
	x = 2.0 / 3;
      else
	x = node->UU.Uline.aradius;
      if (!isthen(node)) {  /* first spline */
	tn = node;
	while (tn->son != NULL)
	  tn = tn->son;
	spltot = primdepth(node);
	splcount = spltot;
	tmpat = node->aat;
	if (tn->UU.Uline.atype == XDOUBLEHEAD || tn->UU.Uline.atype == XLEFTHEAD) {
	  pgfstartdraw(1, node, lsp);
	  pgfahead(&node->aat, node->UU.Uline.endpos,
		   qenv(node, XLarrowht, tn->UU.Uline.height),
		   qenv(node, XLarrowwid, tn->UU.Uline.width));
	}
	/* pgflinecap(lsp); */
	pgfstartdraw(0, node, lsp);
	wpos(node->aat);
	node->aat = tmpat;
	if (node->UU.Uline.aradius == mdistmax) {
	  ddash();
	  if (spltot > 1) {
	    wprop(node->UU.Uline.endpos, node->aat, 1.0, 1.0, 2.0);
	    controls();
	    wprop(node->aat, node->UU.Uline.endpos, 1.0, 5.0, 6.0);
	  }
	} else if (spltot > 1) {
	  controls();
	  wprop(node->aat, node->UU.Uline.endpos, 1 - x, x, 1.0);
	}
      } else if (splcount > 1) {
	wrand();
	wprop(node->aat, node->UU.Uline.endpos, (1 + x) / 2, (1 - x) / 2, 1.0);
	ddot();
	wprop(node->aat, node->UU.Uline.endpos, 1.0, 1.0, 2.0);
	controls();
	wprop(node->aat, node->UU.Uline.endpos, (1 - x) / 2, (1 + x) / 2, 1.0);
      }
      if (splcount == 1) {
	/*D; if debuglevel > 0 then writeln(log,'last node started');D*/
	if (spltot > 1 && node->UU.Uline.aradius == mdistmax) {
	  wrand();
	  wprop(node->aat, node->UU.Uline.endpos, 5.0, 1.0, 6.0);
	  ddot();
	  wprop(node->aat, node->UU.Uline.endpos, 1.0, 1.0, 2.0);
	  ddash();
	} else if (node->UU.Uline.aradius != distmax) {
	  wrand();
	  wprop(node->aat, node->UU.Uline.endpos, x, 1 - x, 1.0);
	  ddot();
	}
	tmpat = node->UU.Uline.endpos;
	if (node->UU.Uline.atype == XDOUBLEHEAD ||
	    node->UU.Uline.atype == XRIGHTHEAD) {
	  x = linlen(node->UU.Uline.endpos.xpos - node->aat.xpos,
		     node->UU.Uline.endpos.ypos - node->aat.ypos);
	  y = qenv(node, XLarrowht, node->UU.Uline.height);
	  pprop(node->aat, &tmpat, y, x - y, x);
	}
	wpos(tmpat);
	pgfendpath();
	if (node->UU.Uline.atype == XDOUBLEHEAD ||
	    node->UU.Uline.atype == XRIGHTHEAD) {
	  pgfstartdraw(1, node, lsp);
	  pgfahead(&node->UU.Uline.endpos, node->aat, y,
		   qenv(node, XLarrowwid, node->UU.Uline.width));
	}
      }
      node->ptype = XLline;
      /*D; if debuglevel > 0 then writeln(log,'node ',splcount:1);D*/
      splcount--;
    }
    break;

  case XLline:
  case XLarrow:
  case XLmove:
    if (drawn(node, lsp, -1.0)) {
      tn = node;
      while (tn->son != NULL)
	tn = tn->son;
      if (!isthen(node)) {
	tmpat = node->aat;
	if (tn->UU.Uline.atype == XDOUBLEHEAD || tn->UU.Uline.atype == XLEFTHEAD) {
	  pgfstartdraw(1, node, lsp);
	  pgfahead(&node->aat, node->UU.Uline.endpos,
		   qenv(node, XLarrowht, tn->UU.Uline.height),
		   qenv(node, XLarrowwid, tn->UU.Uline.width));
	}
	/* pgflinecap(lsp); */
	pgfstartdraw(0, node, lsp);
	wpos(node->aat);
      }
      if (node->son == NULL &&
	  (tn->UU.Uline.atype == XDOUBLEHEAD ||
	   tn->UU.Uline.atype == XRIGHTHEAD)) {
	y = qenv(node, XLarrowht, tn->UU.Uline.height);
	ddash();
	wpos(affine(y, 0.0, node->UU.Uline.endpos,
		    affang(node->UU.Uline.endpos, node->aat)));
	pgfendpath();
	pgfstartdraw(1, node, lsp);
	pgfahead(&node->UU.Uline.endpos, node->aat, y,
		 qenv(node, XLarrowwid, tn->UU.Uline.width));
      } else if (node->son == NULL) {
	/*D; if debuglevel > 0 then writeln(log,'last node started');D*/
	ddash();
	wpos(node->UU.Uline.endpos);
	pgfendpath();
      } else {
	ddash();
	wpos(node->UU.Uline.endpos);
      }
      /*D; if debuglevel > 0 then writeln(log,'node ');D*/
      /* ptype := XLline */
    }
    pgfwrtext(node, node->textp,
	      0.5 * (node->UU.Uline.endpos.xpos + node->aat.xpos),
	      0.5 * (node->aat.ypos + node->UU.Uline.endpos.ypos));
    break;

  case XLarc:
    if (drawn(node, lsp, -1.0)) {
      /* pgflinecap(lsp); */
      X0.xpos = node->aat.xpos +
		node->UU.Uline.aradius * cos(node->UU.Uline.endpos.xpos);
      X0.ypos = node->aat.ypos +
		node->UU.Uline.aradius * sin(node->UU.Uline.endpos.xpos);
      if (node->UU.Uline.atype == XDOUBLEHEAD ||
	  node->UU.Uline.atype == XLEFTHEAD) {
	if (node->UU.Uline.aradius == 0.0)
	  x = 0.0;
	else
	  x = atan(qenv(node, XLarrowht, node->UU.Uline.height) /
		   node->UU.Uline.aradius);
	if (node->UU.Uline.endpos.ypos >= 0.0) {
	  node->UU.Uline.endpos.xpos += x;
	  node->UU.Uline.endpos.ypos -= x;
	} else {
	  node->UU.Uline.endpos.xpos -= x;
	  node->UU.Uline.endpos.ypos += x;
	}
	tmpat = X0;
	X0.xpos = node->aat.xpos +
		  node->UU.Uline.aradius * cos(node->UU.Uline.endpos.xpos);
	X0.ypos = node->aat.ypos +
		  node->UU.Uline.aradius * sin(node->UU.Uline.endpos.xpos);
	pgfstartdraw(1, node, lsp);
	pgfahead(&tmpat, X0, qenv(node, XLarrowht, node->UU.Uline.height),
		 qenv(node, XLarrowwid, node->UU.Uline.width));
      }
      X3.xpos = node->aat.xpos + node->UU.Uline.aradius *
		  cos(node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
      X3.ypos = node->aat.ypos + node->UU.Uline.aradius *
		  sin(node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
      if (node->UU.Uline.atype == XDOUBLEHEAD ||
	  node->UU.Uline.atype == XRIGHTHEAD) {
	if (node->UU.Uline.aradius == 0.0)
	  x = 0.0;
	else
	  x = atan(qenv(node, XLarrowht, node->UU.Uline.height) /
		   node->UU.Uline.aradius);
	if (node->UU.Uline.endpos.ypos >= 0.0)
	  node->UU.Uline.endpos.ypos -= x;
	else
	  node->UU.Uline.endpos.ypos += x;
	tmpat = X3;
	X3.xpos = node->aat.xpos + node->UU.Uline.aradius * cos(
		      node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
	X3.ypos = node->aat.ypos + node->UU.Uline.aradius * sin(
		      node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
	pgfstartdraw(1, node, lsp);
	pgfahead(&tmpat, X3, qenv(node, XLarrowht, node->UU.Uline.height),
		 qenv(node, XLarrowwid, node->UU.Uline.width));
      }
      pgfstartdraw(0, node, lsp);
      n = (long)(1.0 + fabs(node->UU.Uline.endpos.ypos) / pi);
      node->UU.Uline.endpos.ypos /= n;
      while (n > 0) {
	wpos(X0);
	controls();
	x = cos(node->UU.Uline.endpos.ypos / 2);
	y = sin(node->UU.Uline.endpos.ypos / 2);
	xx = (4 - x) / 3;
	if (y != 0.0)
	  xy = (1.0 - x * xx) / y;
	else
	  xy = 0.0;
	tmpat.xpos = cos(
	    node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos / 2.0);
	tmpat.ypos = sin(
	    node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos / 2.0);
	wpos(affine(node->UU.Uline.aradius * xx, -node->UU.Uline.aradius * xy,
		    node->aat, tmpat));
	wrand();
	wpos(affine(node->UU.Uline.aradius * xx, node->UU.Uline.aradius * xy,
		    node->aat, tmpat));
	ddot();
	if (n > 1) {
	  node->UU.Uline.endpos.xpos += node->UU.Uline.endpos.ypos;
	  X0.xpos = node->aat.xpos +
		    node->UU.Uline.aradius * cos(node->UU.Uline.endpos.xpos);
	  X0.ypos = node->aat.ypos +
		    node->UU.Uline.aradius * sin(node->UU.Uline.endpos.xpos);
	}
	n--;
      }
      wpos(X3);
    }
    pgfendpath();
    pgfwrtext(node, node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLstring:
    pgfwrtext(node, node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLtroff:
    if (node->textp != NULL) {
      wstring(&output, node->textp);
      putchar('\n');
    } else if (node->lthick >= 0.0)
      pgfsetthick(node->lthick);
    break;
  }
}  /* pgfdraw */


/* include pst.h */
/* pst.x */
/* Output routines for PSTricks */
void pstprelude(double n, double s, double e, double w)
{
  printf("\\psset{unit=1in,cornersize=absolute,dimen=middle}%%\n");
  printf("\\begin{pspicture}");
  wcoord(&output, w, s);
  wcoord(&output, e, n);
  printf("%%\n");
  printf("%% %s for PSTricks 0.93a or later\n", Version);
}


void pstpostlude(void)
{
  printf("\\end{pspicture}%%\n");
  /*D if debuglevel > 0 then writeln(log,'pstpostlude done'); D*/
}


void pstwrtext(primitive *np, nametype *tp, double x, double y)
{
  boolean A, B, L, R;

  if (tp == NULL)
    return;
  checkjust(tp, &A, &B, &L, &R);
  if (A || B || L || R) {
    printf("\\uput{");
    wfloat(&output, venv(np, XLtextoffset) / scale * 72.27 / 5);
    printf("ex}[");
    if (B)
      putchar('d');
    else if (A)
      putchar('u');
    if (L)
      putchar('r');
    else if (R)
      putchar('l');
    putchar(']');
  } else
    printf("\\rput");
  /* offset in ex units (default 2.5pt= 0.5ex): */
  wcoord(&output, x, y);
  putchar('{');
  stacktext(tp, false);
  printf("}\n");
}


void pstlineoptions(primitive *node, int lsp, Char sep)
{
  if (node->lthick >= 0.0) {
    printf("%clinewidth=", sep);
    wfloat(&output, node->lthick);
    printf("pt");
    sep = ',';
  }
  if (node->outlinep != NULL) {
    printf("%clinecolor=", sep);
    wstring(&output, node->outlinep);
    sep = ',';
  }
  if (node->ptype == XBLOCK)
    lsp = XLinvis;
  if (lsp == XLpath || lsp == XLinvis || lsp == XLdotted || lsp == XLdashed)
  {   /* XLsolid,*/
    printf("%clinestyle=", sep);
    switch (lsp) {

    /* XLsolid: write('solid'); */
    /* solid is the default */
    case XLdashed:
      printf("dashed");
      if (node->lparam >= 0) {
	printf(",dash=");
	wfloat(&output, node->lparam / fsc);
	putchar(' ');
	wfloat(&output, node->lparam / fsc);
      }
      break;

    case XLdotted:
      printf("dotted");
      if (node->lparam >= 0) {
	printf(",dotsep=");
	wfloat(&output, node->lparam / fsc);
      }
      break;

    case XLinvis:
    case XLpath:
      printf("none");
      break;
    }
    sep = ',';
  }
  if ((node->ptype == XLarc || node->ptype == XLspline ||
       node->ptype == XLline ||
       node->ptype == XLarrow) && node->UU.Uline.atype != XEMPTY) {
    printf("%carrowsize=", sep);
    wfloat(&output, node->UU.Uline.width / scale);
    printf("in 0,arrowlength=");
    if (node->UU.Uline.width == 0.0)
      wfloat(&output, 0.0);
    else
      wfloat(&output, node->UU.Uline.height / node->UU.Uline.width);
    printf(",arrowinset=0");
    sep = ',';
  }
  if (sep == ',')
    putchar(']');
}


void pstfilloptions(primitive *node, int lsp)
{
  Char sep;
  double fill;

  fill = -1.0;
  switch (node->ptype) {

  case XBLOCK:
    /* blank case */
    break;

  case XLbox:
    fill = node->UU.Ubox.boxfill;
    break;

  case XLcircle:
    fill = node->UU.Ucircle.cfill;
    break;

  case XLellipse:
    fill = node->UU.Uellipse.efill;
    break;

  case XLline:
  case XLarrow:
  case XLmove:
  case XLspline:
    fill = node->UU.Uline.lfill;
    break;
  }
  fill = (long)floor(fill * 1000000L + 0.5) / 1000000.0;
  if (fill > 0.0 && fill < 1.0 && fill != lastfillval && fill != 0.25 &&
      fill != 0.5 && fill != 0.75) {
    lastfillval = fill;
    printf("\\newgray{fillval}");
    wbrace(fill);
    putchar('\n');
  }
  switch (node->ptype) {

  case XLbox:
  case XBLOCK:
    printf("\\psframe");
    break;

  case XLellipse:
    printf("\\psellipse");
    break;

  case XLcircle:
    printf("\\pscircle");
    break;
  }
  if (node->shadedp != NULL) {
    printf("[fillstyle=solid,fillcolor=");
    wstring(&output, node->shadedp);
    sep = ',';
  } else if (fill >= 0.0 && fill <= 1.0) {
    printf("[fillstyle=solid,fillcolor=");
    if (fill == 0.0)
      printf("black");
    else if (fill == 0.25)
      printf("darkgray");
    else if (fill == 0.5)
      printf("gray");
    else if (fill == 0.75)
      printf("lightgray");
    else if (fill == 1.0)
      printf("white");
    else
      printf("fillval");
    sep = ',';
  } else
    sep = '[';
  if (node->ptype == XLbox) {
    if (node->UU.Ubox.boxradius != 0.0) {
      printf("%clinearc=", sep);
      wfloat(&output, node->UU.Ubox.boxradius / fsc);
      sep = ',';
    }
  }
  pstlineoptions(node, lsp, sep);
}


void pstdraw(primitive *node)
{
  int lsp;
  boolean v;
  primitive *tn;

  lsp = lspec(node->spec);   /* printobject(node); */
  /*D if debuglevel > 0 then begin write(log,'pstdraw: ');
     snaptype(log,ptype); D*/
  /*D
           writeln(log) end;
        if linesignal > 0 then begin write(stderr,'pstdraw: ');
           snaptype(stderr,ptype); writeln(stderr) end D*/
  switch (node->ptype) {

  case XLbox:
  case XBLOCK:
    initnesw();
    nesw(node);
    if (node->ptype == XBLOCK)
      v = drawn(node, lsp, -1.0);
    else
      v = drawn(node, lsp, node->UU.Ubox.boxfill);
    if (v) {
      pstfilloptions(node, lsp);
      wcoord(&output, west, south);
      wcoord(&output, east, north);
      putchar('\n');
    }
    pstwrtext(node, node->textp, 0.5 * (east + west), 0.5 * (north + south));
    break;

  case XLspline:
    if (drawn(node, lsp, node->UU.Uline.lfill)) {
      if (!isthen(node)) {  /* first spline */
	printf("\\psbezier");
	pstfilloptions(node, lsp);
	tn = node;
	while (tn->son != NULL)
	  tn = tn->son;
	spltot = primdepth(node);
	splcount = spltot;
	switch (tn->UU.Uline.atype) {

	case XLEFTHEAD:
	  printf("{<-}");
	  break;

	case XDOUBLEHEAD:
	  printf("{<->}");
	  break;

	case XRIGHTHEAD:
	  printf("{->}");
	  break;
	}
	wpos(node->aat);
      }
      if (node->UU.Uline.aradius == mdistmax) {
	if (splcount == spltot && splcount > 1) {  /* 1st seg */
	  wprop(node->aat, node->UU.Uline.endpos, 5.0, 1.0, 6.0);
	      /* 1/6 from 1st to 2nd */
	  wprop(node->aat, node->UU.Uline.endpos, 4.0, 2.0, 6.0);
	      /* 1/3 from 1st to 2nd */
	  pprop(node->UU.Uline.endpos, &node->aat, 1.0, 1.0, 2.0);
	      /* set aat to halfway */
	  wpos(node->aat);
	  putchar('\n');
	}
	if (splcount > 1) {  /* interior segment */
	  wprop(node->aat, node->UU.Uline.endpos, 1.0, 2.0, 3.0);
	      /* 2/3 from 1st to 2nd */
	  pprop(node->son->UU.Uline.endpos, &node->son->aat, 1.0, 1.0, 2.0);
	      /* shift son^.aat */
	  wprop(node->UU.Uline.endpos, node->son->aat, 2.0, 1.0, 3.0);
	      /* 1/3 from endpos */
	  wpos(node->son->aat);
	} else {  /* last segment */
	  wprop(node->aat, node->UU.Uline.endpos, 2.0, 1.0, 3.0);
	      /* 1/3 along */
	  wprop(node->aat, node->UU.Uline.endpos, 1.0, 2.0, 3.0);
	      /* 2/3 along */
	  wpos(node->UU.Uline.endpos);
	}
      } else if (splcount > 1) {
	wprop(node->aat, node->UU.Uline.endpos, 1 - node->UU.Uline.aradius,
	      node->UU.Uline.aradius, 1.0);
	if (splcount > 2)
	  pprop(node->son->UU.Uline.endpos, &node->son->aat, 1.0, 1.0, 2.0);
	else
	  node->son->aat = node->son->UU.Uline.endpos;
	wprop(node->UU.Uline.endpos, node->son->aat, node->UU.Uline.aradius,
	      1 - node->UU.Uline.aradius, 1.0);
	wpos(node->son->aat);
      } else if (spltot == 1) {
	wprop(node->aat, node->UU.Uline.endpos, node->UU.Uline.aradius,
	      1 - node->UU.Uline.aradius, 1.0);
	wprop(node->aat, node->UU.Uline.endpos, 1 - node->UU.Uline.aradius,
	      node->UU.Uline.aradius, 1.0);
	wpos(node->UU.Uline.endpos);
      }
      node->ptype = XLline;
      if (node->UU.Uline.aradius == mdistmax || splcount > 1)
	putchar('\n');
      splcount--;
    }
    break;

  case XLline:
  case XLarrow:
  case XLarc:
    if (drawn(node, lsp, node->UU.Uline.lfill)) {
      if (!isthen(node)) {
	tn = node;
	while (tn->son != NULL)
	  tn = tn->son;
	if (node->ptype == XLline || node->ptype == XLarrow)
	  printf("\\psline");
	else if (node->UU.Uline.endpos.ypos > 0)
	  printf("\\psarc");
	else
	  printf("\\psarcn");
	pstfilloptions(node, lsp);
	if (tn->UU.Uline.atype == XLEFTHEAD)
	  printf("{<-}");
	else if (tn->UU.Uline.atype == XRIGHTHEAD)
	  printf("{->}");
	else if (tn->UU.Uline.atype == XDOUBLEHEAD) {
	  printf("{<->}");
	  /* else write('lbrace-rbrace') */
	}
	wpos(node->aat);
      }
      if (node->ptype == XLarc) {
	wbrace(node->UU.Uline.aradius / fsc);
	wbrace(180.0 / pi * node->UU.Uline.endpos.xpos);
	wbrace(180.0 / pi *
	       (node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos));
	putchar('\n');
      } else {
	wpos(node->UU.Uline.endpos);
	/* if son = nil then */
	putchar('\n');
      }
    }
    if (node->ptype == XLarc)
      pstwrtext(node, node->textp, node->aat.xpos, node->aat.ypos);
    else
      pstwrtext(node, node->textp,
		0.5 * (node->UU.Uline.endpos.xpos + node->aat.xpos),
		0.5 * (node->aat.ypos + node->UU.Uline.endpos.ypos));
    break;

  case XLmove:
    pstwrtext(node, node->textp,
	      0.5 * (node->UU.Uline.endpos.xpos + node->aat.xpos),
	      0.5 * (node->aat.ypos + node->UU.Uline.endpos.ypos));
    break;

  case XLellipse:
    if (drawn(node, lsp, node->UU.Uellipse.efill)) {
      pstfilloptions(node, lsp);
      wpos(node->aat);
      wcoord(&output, 0.5 * node->UU.Uellipse.elwidth,
	     0.5 * node->UU.Uellipse.elheight);
      putchar('\n');
    }
    pstwrtext(node, node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLcircle:
    if (drawn(node, lsp, node->UU.Ucircle.cfill)) {
      pstfilloptions(node, lsp);
      wpos(node->aat);
      putchar('{');
      wfloat(&output, node->UU.Ucircle.radius / fsc);
      printf("}\n");
    }
    pstwrtext(node, node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLstring:
    pstwrtext(node, node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLtroff:
    if (node->textp != NULL) {
      wstring(&output, node->textp);
      putchar('\n');
    } else if (node->lthick >= 0.0) {
      printf("\\psset{linewidth=");
      wfloat(&output, node->lthick);
      printf("pt}%%\n");
    }
    break;
  }
}  /* pstdraw */


/* include mfp.h */
/* mfp.x */
/* Output routines for mfpic */
void mfpprelude(double n, double s, double e, double w)
{
  printf("\\begin{mfpic}[72.27]");
  wbrace(w / fsc);
  wbrace(e / fsc);
  wbrace(s / fsc);
  wbrace(n / fsc);
  printf("\n%% %s for mfpic 0.5.0\n", Version);
  printf("\\dashlen=4pt\\dashspace=4pt\\dotspace=3pt\\pen{0.8pt}\n");
}


void mfppostlude(void)
{
  printf("\\end{mfpic}\n");
  /*Dif debuglevel > 0 then writeln(log,'mfpbpostlude done');D*/
}


void mfpwrtext(primitive *np, nametype *tp, double x, double y)
{
  boolean A, B, L, R;

  if (tp == NULL)
    return;
  checkjust(tp, &A, &B, &L, &R);
  printf("\\tlabel[");
  if (A)
    putchar('b');
  else if (B)
    putchar('t');
  else
    putchar('c');
  if (L)
    putchar('l');
  else if (R)
    putchar('r');
  else
    putchar('c');
  putchar(']');
  wcoord(&output, x, y);
  putchar('{');
  if (A) {
    printf("\\raisebox{");
    wfloat(&output, venv(np, XLtextoffset) * 72.27 / 5 + 0.25);
    printf("ex}{");
  } else if (B) {
    printf("\\raisebox{");
    wfloat(&output, -venv(np, XLtextoffset) * 72.27 / 5 - 0.25);
    printf("ex}{");
  }
  stacktext(tp, false);
  if (A || B)
    putchar('}');
  printf("}\n");
}


void comma(void)
{
  putchar(',');
}


void commacr(void)
{
  printf(",\n");
}


void mfpheadshape(int atype, double height, double width)
{
  if (atype != XDOUBLEHEAD && atype != XRIGHTHEAD && atype != XLEFTHEAD)
    return;
  printf("\\headlen=");
  wfloat(&output, height / scale * 72.27);
  printf("pt\\headshape{");
  if (height == 0.0)
    wfloat(&output, 0.0);
  else
    wfloat(&output, width / height);
  printf("}{infinity}{true}\n");
}


void mfpcheckarrow(int atype)
{
  if (atype == XLEFTHEAD) {
    printf("\\arrow\\reverse");
    return;
  }
  if (atype == XRIGHTHEAD)
    printf("\\arrow");
  else if (atype == XDOUBLEHEAD)
    printf("\\arrow\\reverse\\arrow");
}


void mfpsetshade(double fill)
{
  if (fill == 0.0) {
    printf("\\gfill");
    return;
  }
  if (fill == 1)
    return;
  printf("\\shadespace=");
  wfloat(&output, exp((fill - 0.3) * 2));
  printf("pt\\shade");
}


void mfpellipse(postype aat, double elwidth, double elheight)
{
  printf("\\ellipse{");
  wpos(aat);
  comma();
  wfloat(&output, 0.5 * elwidth / fsc);
  comma();
  wfloat(&output, 0.5 * elheight / fsc);
  printf("}\n");
}


void mfpcircle(postype aat, double radius)
{
  printf("\\circle{");
  wpos(aat);
  comma();
  wfloat(&output, radius / fsc);
  printf("}\n");
}


void mfsetdash(double dash)
{
  if (dash < 0.0)
    return;
  printf("\\dashlen=");
  wfloat(&output, dash);
  printf("in");
  printf("\\dashspace=");
  wfloat(&output, dash);
  printf("in");
}


void mfsetthick(double lthick)
{
  if (lthick < 0.0)
    return;
  printf("\\pen{");
  wfloat(&output, lthick);
  printf("pt}");
}


void mfpdashdot(int lsp, double param)
{
  if (lsp == XLdashed) {
    mfsetdash(param / fsc);
    printf("\\dashed");
    return;
  }
  if (lsp != XLdotted)
    return;
  if (param >= 0.0) {
    printf("\\dotspace=");
    wfloat(&output, param / fsc);
    printf("in");
  }
  printf("\\dotted");
}


void mfpdraw(primitive *node)
{
  /* node is always <> nil */
  int i, lsp;
  postype tmpos;
  primitive *tn;
  double t, r;

  lsp = lspec(node->spec);
  switch (node->ptype) {

  case XLbox:
  case XBLOCK:
    initnesw();
    nesw(node);
    if (node->ptype == XLbox) {
      if (node->UU.Ubox.boxfill >= 0.0 && node->UU.Ubox.boxfill <= 1.0) {
	mfpsetshade(node->UU.Ubox.boxfill);
	printf("\\rect{");
	wcoord(&output, west, south);
	comma();
	wcoord(&output, east, north);
	printf("}\n");
      }
      if (drawn(node, lsp, -1.0)) {
	mfsetthick(node->lthick);
	mfpdashdot(lsp, node->lparam);
	printf("\\rect{");
	wcoord(&output, west, south);
	comma();
	wcoord(&output, east, north);
	printf("}\n");
      }
    }
    mfpwrtext(node, node->textp, 0.5 * (east + west), 0.5 * (north + south));
    break;

  case XLellipse:
    if (node->UU.Uellipse.efill >= 0.0 && node->UU.Uellipse.efill <= 1.0) {
      mfpsetshade(node->UU.Uellipse.efill);
      mfpellipse(node->aat, node->UU.Uellipse.elwidth, node->UU.Uellipse.elheight);
    }
    if (drawn(node, lsp, -1.0)) {
      mfsetthick(node->lthick);
      mfpdashdot(lsp, node->lparam);
      mfpellipse(node->aat, node->UU.Uellipse.elwidth, node->UU.Uellipse.elheight);
    }
    mfpwrtext(node, node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLcircle:
    if (node->UU.Ucircle.cfill >= 0.0 && node->UU.Ucircle.cfill <= 1.0) {
      mfpsetshade(node->UU.Ucircle.cfill);
      mfpcircle(node->aat, node->UU.Ucircle.radius);
    }
    if (drawn(node, lsp, -1.0)) {
      mfsetthick(node->lthick);
      mfpdashdot(lsp, node->lparam);
      mfpcircle(node->aat, node->UU.Ucircle.radius);
    }
    mfpwrtext(node, node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLspline:
    if (drawn(node, lsp, -1.0)) {
      if (!isthen(node)) {  /* first spline */
	tn = node;
	while (tn->son != NULL)
	  tn = tn->son;
	spltot = primdepth(node);
	splcount = spltot;
	mfpheadshape(tn->UU.Uline.atype, tn->UU.Uline.height, tn->UU.Uline.width);
	mfsetthick(node->lthick);
	mfpdashdot(lsp, node->lparam);
	mfpcheckarrow(tn->UU.Uline.atype);
	printf("\\curve{");
	wpos(node->aat);
	comma();
	if (node->UU.Uline.aradius == mdistmax) {  /* spline x ie tensioned */
	  wprop(node->aat, node->UU.Uline.endpos, 3.0, 1.0, 4.0);
	  comma();
	  pprop(node->UU.Uline.endpos, &node->aat, 1.0, 1.0, 2.0);
	  wpos(node->aat);
	  commacr();
	}
      }
      node->ptype = XLline;   /* Do we need this anymore? */
      if (splcount > 1) {
	if (node->UU.Uline.aradius == mdistmax || splcount > 2)
	  pprop(node->son->UU.Uline.endpos, &node->son->aat, 1.0, 1.0, 2.0);
	else
	  node->son->aat = node->son->UU.Uline.endpos;
	if (node->UU.Uline.aradius == mdistmax)
	  r = 2.0 / 3;
	else
	  r = node->UU.Uline.aradius;
	for (i = 1; i <= 3; i++) {
	  t = i / 4.0;
	  tmpos = node->aat;
	  pprop(node->UU.Uline.endpos, &tmpos, 3 * r * t * (1 - t),
		(1 - t) * (1 - t) * (1 - t + 3 * t * (1 - r)), 1.0);
	  wprop(node->son->aat, tmpos, t * t * (t + 3 * (1 - t) * (1 - r)),
		1.0, 1.0);
	  comma();
	}
	wpos(node->son->aat);
	if (node->UU.Uline.aradius == mdistmax || splcount > 2)
	  commacr();
	else
	  printf("}\n");
      } else if (node->UU.Uline.aradius == mdistmax) {
	wprop(node->aat, node->UU.Uline.endpos, 1.0, 1.0, 2.0);
	comma();
	wpos(node->UU.Uline.endpos);
	printf("}\n");
      }
      splcount--;
    }
    break;

  case XLline:
  case XLarrow:
  case XLmove:
    if (drawn(node, lsp, -1.0)) {
      if (!isthen(node)) {
	tn = node;
	while (tn->son != NULL)
	  tn = tn->son;
	mfpheadshape(tn->UU.Uline.atype, tn->UU.Uline.height, tn->UU.Uline.width);
	mfsetthick(node->lthick);
	mfpdashdot(lsp, node->lparam);
	mfpcheckarrow(tn->UU.Uline.atype);
	printf("\\polyline{");
	wpos(node->aat);
	comma();
	wpos(node->UU.Uline.endpos);
      } else {
	commacr();
	wpos(node->UU.Uline.endpos);
      }
      if (node->son == NULL)
	printf("}\n");
    }
    mfpwrtext(node, node->textp,
	      0.5 * (node->UU.Uline.endpos.xpos + node->aat.xpos),
	      0.5 * (node->aat.ypos + node->UU.Uline.endpos.ypos));
    break;

  case XLarc:
    if (drawn(node, lsp, -1.0)) {
      mfpheadshape(node->UU.Uline.atype, node->UU.Uline.height,
		   node->UU.Uline.width);
      mfsetthick(node->lthick);
      mfpdashdot(lsp, node->lparam);
      mfpcheckarrow(node->UU.Uline.atype);
      printf("\\arc[p]{");
      wpos(node->aat);
      comma();
      wfloat(&output, 180.0 / pi * node->UU.Uline.endpos.xpos);
      comma();
      wfloat(&output,
	180.0 / pi * (node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos));
      comma();
      wfloat(&output, node->UU.Uline.aradius / fsc);
      printf("}\n");
    }
    mfpwrtext(node, node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLstring:
    mfpwrtext(node, node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLtroff:
    if (node->textp != NULL) {
      wstring(&output, node->textp);
      putchar('\n');
    } else if (node->lthick >= 0.0)
      mfsetthick(node->lthick);
    else if (node->lparam >= 0.0) {
      mfsetdash(node->lparam);
      putchar('\n');
    }
    break;
  }
}  /* mfpdraw */


/* include mpo.h */
/* mpo.x */
/* Output routines for MetaPost */
void mpoprelude(void)
{
  /* n,s,e,w: real */
  printstate++;
  printf("%% %s for MetaPost\n", Version);
  printf("beginfig(%d)\n", printstate);
  printf("def lcbutt=linecap:=butt enddef;\n");
  printf("def lcsq=linecap:=squared enddef;\n");
  printf("def lcrnd=linecap:=rounded enddef;\n");
  printf("def ljmit=linejoin:=mitered enddef;\n");
  printf("def lcolr= enddef; def drw=draw enddef; def X=;enddef;\n");
  printf("lcbutt; ljmit;\n");
}


void mpopostlude(void)
{
  printf("endfig;\n");
  /*D; if debuglevel > 0 then writeln(log,'mpobpostlude done');D*/
}


void mpowrtext(nametype *tp, double x, double y)
{
  boolean A, B, L, R;

  if (tp == NULL)
    return;
  checkjust(tp, &A, &B, &L, &R);
  printf("label");
  if (A && L)
    printf(".urt");
  else if (A && R)
    printf(".ulft");
  else if (B && L)
    printf(".lrt");
  else if (B && R)
    printf(".llft");
  else if (A)
    printf(".top");
  else if (B)
    printf(".bot");
  else if (L)
    printf(".rt");
  else if (R)
    printf(".lft");
  printf("(btex ");
  stacktext(tp, false);
  printf(" etex,");
  wcoord(&output, x, y);
  printf(") X\n");
}


void mpoahead(postype *point, postype shaft, double ht, double wid)
{
  postype butx, cs;

  cs = affang(*point, shaft);
  butx = affine(ht, 0.0, *point, cs);
  printf("fill ");
  wpos(butx);
  ddash();
  wpos(affine(ht, wid / 2, *point, cs));
  ddash();
  wpos(*point);
  ddash();
  wpos(affine(ht, wid / -2, *point, cs));
  printf("\n --cycle X\n");
  *point = butx;
}


void mposetthick(double lthick)
{
  if (lthick == mdistmax) {
    if (lastthick != mdistmax)
      lthick = lastthick;
    else
      lthick = 0.8;
  }
  /*D; if debuglevel > 0 then begin
     writeln(log); writeln(log,'lthick=',lthick,' lastthick=',lastthick)
     end;D*/
  if (lthick < 0.0 || lthick == lastthick)
    return;
  printf("pickup pencircle scaled ");
  wfloat(&output, lthick);
  printf("bp;\n");   /* Use Adobe points to conform to PSTricks */
  lastthick = lthick;
}


void mpolinecap(int lsp)
{
  switch (lsp) {

  case XLdashed:
    printf("lcsq;\n");
    break;

  case XLdotted:
    printf("lcrnd;\n");
    break;
  }
}


void addcolor(nametype *sp, double fillv)
{
  printf(" withcolor ");
  if (sp != NULL)
    wstring(&output, sp);
  else {
    wfloat(&output, fillv);
    printf("white");
  }
}


void mpodashdot(int lsp, double param, nametype *op)
{
  if (lsp == XLdashed) {
    printf(" dashed evenly");
    if (param > 0) {
      printf(" scaled ");
      wfloat(&output, param / fsc / 3);
    }
    if (op != NULL)
      addcolor(op, -1.0);
    printf(" X lcbutt;\n");
    return;
  }
  if (lsp == XLdotted) {
    printf(" dashed withdots");
    if (param > 0) {
      printf(" scaled ");
      wfloat(&output, param / 5);
    }
    if (op != NULL)
      addcolor(op, -1.0);
    printf(" X lcbutt;\n");
    return;
  }
  if (op != NULL) {
    addcolor(op, -1.0);
    printf(" X\n");
  } else
    printf(" X\n");
}


#define b               ((sqrt(2.0) - 1.0) * 4.0 / 3.0)


void mpocorner(postype ctr, double x, double y, double r, double ct,
		      double st)
{
  /* ctr:postype; x,y,r,ct,st: real */
  wcoord(&output, ctr.xpos + x + ct * r, ctr.ypos + y + st * r);
  controls();
  wcoord(&output, ctr.xpos + x + ct * r - st * r * b,
	 ctr.ypos + y + st * r + ct * r * b);
  wrand();
  wcoord(&output, ctr.xpos + x + ct * r * b - st * r,
	 ctr.ypos + y + st * r * b + ct * r);
  ddot();
  wcoord(&output, ctr.xpos + x - st * r, ctr.ypos + y + ct * r);
  ddash();
}

#undef b


void mpobox(Char *initial, postype ctr, double halfwid, double halfht,
		   double rad)
{
  double r, h, v;

  fputs(initial, stdout);
  if (rad == 0.0) {
    wcoord(&output, ctr.xpos - halfwid, ctr.ypos + halfht);
    ddash();
    wcoord(&output, ctr.xpos + halfwid, ctr.ypos + halfht);
    ddash();
    wcoord(&output, ctr.xpos + halfwid, ctr.ypos - halfht);
    ddash();
    wcoord(&output, ctr.xpos - halfwid, ctr.ypos - halfht);
    ddash();
  } else {
    r = Min(Min(rad, halfht), halfwid);
    h = halfwid - r;
    v = halfht - r;
    mpocorner(ctr, h, v, r, 1.0, 0.0);
    mpocorner(ctr, -h, v, r, 0.0, 1.0);
    mpocorner(ctr, -h, -v, r, -1.0, 0.0);
    mpocorner(ctr, h, -v, r, 0.0, -1.0);
  }
  printf("cycle");
}


#define r               ((sqrt(2.0) - 1) * 4 / 3)


void mpoellipse(Char *initial, postype ctr, double halfwid,
		       double halfht)
{
  fputs(initial, stdout);
  wcoord(&output, ctr.xpos + halfwid, ctr.ypos);
  controls();
  wcoord(&output, ctr.xpos + halfwid, ctr.ypos + halfht * r);
  wrand();
  wcoord(&output, ctr.xpos + halfwid * r, ctr.ypos + halfht);
  ddot();
  wcoord(&output, ctr.xpos, ctr.ypos + halfht);
  controls();
  wcoord(&output, ctr.xpos - halfwid * r, ctr.ypos + halfht);
  wrand();
  wcoord(&output, ctr.xpos - halfwid, ctr.ypos + halfht * r);
  ddot();
  wcoord(&output, ctr.xpos - halfwid, ctr.ypos);
  controls();
  wcoord(&output, ctr.xpos - halfwid, ctr.ypos - halfht * r);
  wrand();
  wcoord(&output, ctr.xpos - halfwid * r, ctr.ypos - halfht);
  ddot();
  wcoord(&output, ctr.xpos, ctr.ypos - halfht);
  controls();
  wcoord(&output, ctr.xpos + halfwid * r, ctr.ypos - halfht);
  wrand();
  wcoord(&output, ctr.xpos + halfwid, ctr.ypos - halfht * r);
  ddot();
  printf("cycle");
}

#undef r


void mpodraw(primitive *node)
{
  /* node is always <> nil */
  int lsp, n;
  postype tmpat, X0, X3;
  primitive *tn;
  double x, y, xx, xy;

  lsp = lspec(node->spec);
  switch (node->ptype) {

  case XLbox:
  case XBLOCK:
    initnesw();
    nesw(node);
    if (node->ptype == XLbox) {
      if (node->shadedp != NULL ||
	  node->UU.Ubox.boxfill >= 0.0 && node->UU.Ubox.boxfill <= 1.0) {
	mpobox("fill ", node->aat, node->UU.Ubox.boxwidth / 2,
	       node->UU.Ubox.boxheight / 2, node->UU.Ubox.boxradius);
	addcolor(node->shadedp, node->UU.Ubox.boxfill);
	printf(";\n");
      }
      if (drawn(node, lsp, -1.0)) {
	mposetthick(node->lthick);
	mpolinecap(lsp);
	mpobox("drw ", node->aat, node->UU.Ubox.boxwidth / 2,
	       node->UU.Ubox.boxheight / 2, node->UU.Ubox.boxradius);
	mpodashdot(lsp, node->lparam, node->outlinep);
      }
    }
    mpowrtext(node->textp, 0.5 * (east + west), 0.5 * (north + south));
    break;

  case XLellipse:
    if (node->shadedp != NULL ||
	node->UU.Uellipse.efill >= 0.0 && node->UU.Uellipse.efill <= 1.0) {
      mpoellipse("fill ", node->aat, node->UU.Uellipse.elwidth / 2,
		 node->UU.Uellipse.elheight / 2);
      addcolor(node->shadedp, node->UU.Uellipse.efill);
      printf(";\n");
    }
    if (drawn(node, lsp, -1.0)) {
      mposetthick(node->lthick);
      mpolinecap(lsp);
      mpoellipse("drw ", node->aat, node->UU.Uellipse.elwidth / 2,
		 node->UU.Uellipse.elheight / 2);
      mpodashdot(lsp, node->lparam, node->outlinep);
    }
    mpowrtext(node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLcircle:
    if (node->shadedp != NULL ||
	node->UU.Ucircle.cfill >= 0.0 && node->UU.Ucircle.cfill <= 1.0) {
      printf("fill fullcircle scaled ");
      wfloat(&output, node->UU.Ucircle.radius * 2 / fsc);
      printf(" shifted ");
      wpos(node->aat);
      addcolor(node->shadedp, node->UU.Ucircle.cfill);
      printf(";\n");
    }
    if (drawn(node, lsp, -1.0)) {
      mposetthick(node->lthick);
      mpolinecap(lsp);
      printf("drw fullcircle scaled ");
      wfloat(&output, node->UU.Ucircle.radius * 2 / fsc);
      printf(" shifted ");
      wpos(node->aat);
      mpodashdot(lsp, node->lparam, node->outlinep);
    }
    mpowrtext(node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLspline:
    if (drawn(node, lsp, -1.0)) {
      if (node->UU.Uline.aradius == mdistmax)
	x = 2.0 / 3;
      else
	x = node->UU.Uline.aradius;
      if (!isthen(node)) {  /* first spline */
	tn = node;
	while (tn->son != NULL)
	  tn = tn->son;
	mposetthick(node->lthick);
	spltot = primdepth(node);
	splcount = spltot;
	tmpat = node->aat;
	if (tn->UU.Uline.atype == XDOUBLEHEAD || tn->UU.Uline.atype == XLEFTHEAD)
	  mpoahead(&node->aat, node->UU.Uline.endpos,
		   qenv(node, XLarrowht, tn->UU.Uline.height),
		   qenv(node, XLarrowwid, tn->UU.Uline.width));
	mpolinecap(lsp);
	printf("drw ");
	wpos(node->aat);
	node->aat = tmpat;
	if (node->UU.Uline.aradius == mdistmax) {
	  ddash();
	  if (spltot > 1) {
	    wprop(node->UU.Uline.endpos, node->aat, 1.0, 1.0, 2.0);
	    controls();
	    wprop(node->aat, node->UU.Uline.endpos, 1.0, 5.0, 6.0);
	  }
	} else if (spltot > 1) {
	  controls();
	  wprop(node->aat, node->UU.Uline.endpos, 1 - x, x, 1.0);
	}
      } else if (splcount > 1) {
	wrand();
	wprop(node->aat, node->UU.Uline.endpos, (1 + x) / 2, (1 - x) / 2, 1.0);
	ddot();
	wprop(node->aat, node->UU.Uline.endpos, 1.0, 1.0, 2.0);
	controls();
	wprop(node->aat, node->UU.Uline.endpos, (1 - x) / 2, (1 + x) / 2, 1.0);
      }
      if (splcount == 1) {
	/*D; if debuglevel > 0 then writeln(log,'last node started');D*/
	if (spltot > 1 && node->UU.Uline.aradius == mdistmax) {
	  wrand();
	  wprop(node->aat, node->UU.Uline.endpos, 5.0, 1.0, 6.0);
	  ddot();
	  wprop(node->aat, node->UU.Uline.endpos, 1.0, 1.0, 2.0);
	  ddash();
	} else if (node->UU.Uline.aradius != distmax) {
	  wrand();
	  wprop(node->aat, node->UU.Uline.endpos, x, 1 - x, 1.0);
	  ddot();
	}
	tmpat = node->UU.Uline.endpos;
	if (node->UU.Uline.atype == XDOUBLEHEAD ||
	    node->UU.Uline.atype == XRIGHTHEAD) {
	  x = linlen(node->UU.Uline.endpos.xpos - node->aat.xpos,
		     node->UU.Uline.endpos.ypos - node->aat.ypos);
	  y = qenv(node, XLarrowht, node->UU.Uline.height);
	  pprop(node->aat, &tmpat, y, x - y, x);
	}
	wpos(tmpat);
	mpodashdot(lsp, node->lparam, node->outlinep);
	if (node->UU.Uline.atype == XDOUBLEHEAD ||
	    node->UU.Uline.atype == XRIGHTHEAD)
	  mpoahead(&node->UU.Uline.endpos, node->aat, y,
		   qenv(node, XLarrowwid, node->UU.Uline.width));
      }
      node->ptype = XLline;
      /*D; if debuglevel > 0 then writeln(log,'node ',splcount:1);D*/
      splcount--;
    }
    break;

  case XLline:
  case XLarrow:
  case XLmove:
    if (drawn(node, lsp, -1.0)) {
      tn = node;
      while (tn->son != NULL)
	tn = tn->son;
      if (!isthen(node)) {
	mposetthick(node->lthick);
	tmpat = node->aat;
	if (tn->UU.Uline.atype == XDOUBLEHEAD || tn->UU.Uline.atype == XLEFTHEAD)
	  mpoahead(&node->aat, node->UU.Uline.endpos,
		   qenv(node, XLarrowht, tn->UU.Uline.height),
		   qenv(node, XLarrowwid, tn->UU.Uline.width));
	mpolinecap(lsp);
	printf("drw ");
	wpos(node->aat);
      }
      if (node->son == NULL &&
	  (tn->UU.Uline.atype == XDOUBLEHEAD ||
	   tn->UU.Uline.atype == XRIGHTHEAD)) {
	y = qenv(node, XLarrowht, tn->UU.Uline.height);
	ddash();
	wpos(affine(y, 0.0, node->UU.Uline.endpos,
		    affang(node->UU.Uline.endpos, node->aat)));
	mpodashdot(lsp, node->lparam, node->outlinep);
	mpoahead(&node->UU.Uline.endpos, node->aat, y,
		 qenv(node, XLarrowwid, tn->UU.Uline.width));
      } else if (node->son == NULL) {
	/*D; if debuglevel > 0 then writeln(log,'last node started');D*/
	ddash();
	wpos(node->UU.Uline.endpos);
	mpodashdot(lsp, node->lparam, node->outlinep);
      } else {
	ddash();
	wpos(node->UU.Uline.endpos);
      }
      /*D; if debuglevel > 0 then writeln(log,'node ');D*/
      /* ptype := XLline */
    }
    mpowrtext(node->textp, 0.5 * (node->UU.Uline.endpos.xpos + node->aat.xpos),
	      0.5 * (node->aat.ypos + node->UU.Uline.endpos.ypos));
    break;

  case XLarc:
    if (drawn(node, lsp, -1.0)) {
      mposetthick(node->lthick);
      mpolinecap(lsp);
      X0.xpos = node->aat.xpos +
		node->UU.Uline.aradius * cos(node->UU.Uline.endpos.xpos);
      X0.ypos = node->aat.ypos +
		node->UU.Uline.aradius * sin(node->UU.Uline.endpos.xpos);
      if (node->UU.Uline.atype == XDOUBLEHEAD ||
	  node->UU.Uline.atype == XLEFTHEAD) {
	if (node->UU.Uline.aradius == 0.0)
	  x = 0.0;
	else
	  x = atan(qenv(node, XLarrowht, node->UU.Uline.height) /
		   node->UU.Uline.aradius);
	if (node->UU.Uline.endpos.ypos >= 0.0) {
	  node->UU.Uline.endpos.xpos += x;
	  node->UU.Uline.endpos.ypos -= x;
	} else {
	  node->UU.Uline.endpos.xpos -= x;
	  node->UU.Uline.endpos.ypos += x;
	}
	tmpat = X0;
	X0.xpos = node->aat.xpos +
		  node->UU.Uline.aradius * cos(node->UU.Uline.endpos.xpos);
	X0.ypos = node->aat.ypos +
		  node->UU.Uline.aradius * sin(node->UU.Uline.endpos.xpos);
	mpoahead(&tmpat, X0, qenv(node, XLarrowht, node->UU.Uline.height),
		 qenv(node, XLarrowwid, node->UU.Uline.width));
      }
      X3.xpos = node->aat.xpos + node->UU.Uline.aradius *
		  cos(node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
      X3.ypos = node->aat.ypos + node->UU.Uline.aradius *
		  sin(node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
      if (node->UU.Uline.atype == XDOUBLEHEAD ||
	  node->UU.Uline.atype == XRIGHTHEAD) {
	if (node->UU.Uline.aradius == 0.0)
	  x = 0.0;
	else
	  x = atan(qenv(node, XLarrowht, node->UU.Uline.height) /
		   node->UU.Uline.aradius);
	if (node->UU.Uline.endpos.ypos >= 0.0)
	  node->UU.Uline.endpos.ypos -= x;
	else
	  node->UU.Uline.endpos.ypos += x;
	tmpat = X3;
	X3.xpos = node->aat.xpos + node->UU.Uline.aradius * cos(
		      node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
	X3.ypos = node->aat.ypos + node->UU.Uline.aradius * sin(
		      node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
	mpoahead(&tmpat, X3, qenv(node, XLarrowht, node->UU.Uline.height),
		 qenv(node, XLarrowwid, node->UU.Uline.width));
      }
      printf("drw ");
      n = (long)(1.0 + fabs(node->UU.Uline.endpos.ypos) / pi);
      node->UU.Uline.endpos.ypos /= n;
      while (n > 0) {
	wpos(X0);
	controls();
	x = cos(node->UU.Uline.endpos.ypos / 2);
	y = sin(node->UU.Uline.endpos.ypos / 2);
	xx = (4 - x) / 3;
	if (y != 0.0)
	  xy = (1.0 - x * xx) / y;
	else
	  xy = 0.0;
	tmpat.xpos = cos(
	    node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos / 2.0);
	tmpat.ypos = sin(
	    node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos / 2.0);
	wpos(affine(node->UU.Uline.aradius * xx, -node->UU.Uline.aradius * xy,
		    node->aat, tmpat));
	wrand();
	wpos(affine(node->UU.Uline.aradius * xx, node->UU.Uline.aradius * xy,
		    node->aat, tmpat));
	ddot();
	if (n > 1) {
	  node->UU.Uline.endpos.xpos += node->UU.Uline.endpos.ypos;
	  X0.xpos = node->aat.xpos +
		    node->UU.Uline.aradius * cos(node->UU.Uline.endpos.xpos);
	  X0.ypos = node->aat.ypos +
		    node->UU.Uline.aradius * sin(node->UU.Uline.endpos.xpos);
	}
	n--;
      }
      wpos(X3);
      mpodashdot(lsp, node->lparam, node->outlinep);
    }
    mpowrtext(node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLstring:
    mpowrtext(node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLtroff:
    if (node->textp != NULL) {
      wstring(&output, node->textp);
      putchar('\n');
    } else if (node->lthick >= 0.0)
      mposetthick(node->lthick);
    break;
  }
}  /* mpodraw */


/* include ps.h */
/* ps.x */
/* Output routines for Postscript, PSfrag */
void pswfloat(FILE **iou, double x)
{
  putc(' ', *iou);
  wfloat(iou, x);
  /*DUGHM ;flush(iou) MHGUD*/
}


void psprelude(double n, double s, double e, double w, double lth)
{
  double wx, ex, nx, sx;

  /* writeln('%!PS'); */
  /* writeln('%!PS-Adobe-3.0 EPSF-3.0'); */
  printf("%%!PS-Adobe-3.0\n");
  wx = w / fsc - lth / 2;
  ex = e / fsc + lth / 2;
  nx = n / fsc + lth / 2;
  sx = s / fsc - lth / 2;
  printf("%%%%BoundingBox: %d %d %d %d\n",
	 Floor((long)floor(wx * 1000000L + 0.5) / 1000000.0),
	 Floor((long)floor(sx * 1000000L + 0.5) / 1000000.0),
	 Ceil((long)floor(ex * 1000000L + 0.5) / 1000000.0),
	 Ceil((long)floor(nx * 1000000L + 0.5) / 1000000.0));
  /*D; if debuglevel > 0 then begin writeln(log,'lth= ',lth);
     writeln(log,wx,' ',Floor(round(wx*1000000)/1000000.0));
     end; D*/
  printf("%%%%HiResBoundingBox:");
  pswfloat(&output, wx);
  pswfloat(&output, sx);
  pswfloat(&output, ex);
  pswfloat(&output, nx);
  printf("\n%%%%Creator: ");
  puts(Version);
  printf("%%%%Pages: 1\n");
  printf("%%%%EndComments\n");
  /* writeln('%%EndProlog'); */
  printf("%%%%Page: 1 1\n");
  /* writeln('userdict begin'); */
  printf("/DpicDict 20 dict def DpicDict begin\n");
  /* writeln('/setlinewid {0 exch 72.27 div 72 mul');
  writeln(' dtransform truncate idtransform setlinewidth pop} def'); */
  /* write('/setlineparms { [] 0 setdash 0 setlinecap 1 setlinejoin'); */
  printf("/setlineparms { [] 0 setdash 0 setlinecap 0 setlinejoin");
  printf(" 10 setmiterlimit} def\n");
  printf("/ostroke { stroke setlineparms } def\n");
  printf("/endstroke { ostroke } def /npath { newpath } def\n");
  printf(" setlineparms\n");
  if ((printstate & 1) != 1)
    return;
  if (drawmode == PS) {
    printf("/strsiz\n");
    printf(" {newpath 0 0 moveto true charpath flattenpath");
    printf(" pathbbox 4 1 roll pop pop pop}def\n");
    printf("/setcapht {(I) strsiz /capht exch def} def\n");
    printf("/postext {1 add baselineskip mul 1 sub 2 div capht mul add moveto} def\n");
    printf("/strwidth { dup stringwidth pop } def\n");
    printf("/ljust { labelsep } def\n");
    printf("/rjust { strwidth labelsep add neg } def\n");
    printf("/cjust { strwidth 2 div neg } def\n");
    printf("/above { capht 2 div labelsep add } def\n");
    printf("/below { capht 2 div neg labelsep sub } def\n");
    printf("/vjust {0 capht baselineskip mul neg rmoveto\n");
    printf(" currentpoint /y exch def /x exch def} def\n");
  } else {
    printf("/ljust { labelsep } def /rjust { labelsep neg } def ");
    printf("/cjust { 0 } def\n");
    printf("/above { labelsep } def /below { labelsep neg } def ");
  }
  printf("/vcenter { 0 } def\n");
  printf("/basefont {/Times-Roman findfont} def\n");
  printf(" basefont 11 scalefont setfont\n");
  printf("/labelsep 2 def\n");
  printf("/baselineskip 1.4 def\n");
}


void pspostlude(void)
{
  printf("showpage end\n");
  printf("%%%%EOF\n");
  /*D; if debuglevel > 0 then writeln(log,'pspostlude done');D*/
}


void psnewpath(void)
{
  printf("npath\n");
}


void pswcoord(FILE **iou, double x, double y)
{
  pswfloat(iou, x / fsc);
  /*DUGHM ;flush(iou) MHGUD*/
  pswfloat(iou, y / fsc);
}


void pswpos(postype pos)
{
  pswcoord(&output, pos.xpos, pos.ypos);
}


void pswstring(nametype *p)
{
  int i;
  Char c;
  boolean waswhite, iswhite;
  int FORLIM;

  waswhite = false;
  if (p == NULL)
    return;
  if (p->segmnt == NULL)
    return;
  FORLIM = p->len;
  for (i = 0; i < FORLIM; i++) {
    c = p->segmnt[p->seginx + i];
    iswhite = (c == etxch || c == nlch || c == tabch || c == ' ');
    if (!iswhite || !waswhite) {
      if (c == '\\' || c == ')' || c == '(')
	putchar('\\');
      putchar(c);
    }
    waswhite = iswhite;
  }
}


void pswtext(nametype *tp, double x, double y)
{
  int i;
  nametype *tx;
  boolean L, R, A, B;

  if (tp != NULL && drawmode == PS) {
    tx = tp;
    i = 0;
    do {
      i++;
      tx = tx->next_;
    } while (tx != NULL);
    printf(" setcapht");
    pswcoord(&output, x, y);
    printf(" %d postext\n", i);
    do {
      printf(" vjust (");
      checkjust(tp, &A, &B, &L, &R);
      pswstring(tp);
      printf(")\n");
      if (L)
	printf(" ljust");
      else if (R)
	printf(" rjust");
      else
	printf(" cjust");
      if (A)
	printf(" above");
      else if (B)
	printf(" below");
      else
	printf(" vcenter");
      printf(" rmoveto show x y moveto\n");
      tp = tp->next_;
    } while (tp != NULL);
    return;
  }
  if (tp == NULL)
    return;
  printf("(\\\\tex[");
  checkjust(tp, &A, &B, &L, &R);
  if (L)
    putchar('l');
  else if (R)
    putchar('r');
  else
    putchar('c');
  if (A)
    putchar('b');
  else if (B)
    putchar('t');
  else
    putchar('c');
  printf("][lB]{");
  if (tp->next_ != NULL)
    printf("\\\\shortstack{");
  tx = tp;
  do {
    if (L)
      printf("\\\\rlap{");
    else if (R)
      printf("\\\\llap{");
    pswstring(tx);
    if (L || R)
      putchar('}');
    tx = tx->next_;
    if (tx != NULL) {
      printf("\\\\\\\\ ");
      checkjust(tx, &A, &B, &L, &R);
    }
  } while (tx != NULL);
  if (tp->next_ != NULL)
    printf("}})\n");
  else
    printf("})\n");
  pswcoord(&output, x, y);
  printf(" moveto");
  checkjust(tp, &A, &B, &L, &R);
  if (L)
    printf(" ljust");
  else if (R)
    printf(" rjust");
  else
    printf(" cjust");
  if (A)
    printf(" above");
  else if (B)
    printf(" below");
  else
    printf(" vcenter");
  printf(" rmoveto show\n");
}


void psahead(postype *point, postype shaft, double ht, double wid,
		    double lth)
{
  postype butx, cs;
  double st;

  lth /= 72.27;
  if (ht == 0.0 && wid == 0.0)
    st = 1.0;
  else
    st = wid / 2 / sqrt(ht * ht + wid * wid / 4);
  cs = affang(*point, shaft);
  *point = affine(lth / 2 / st, 0.0, *point, cs);
      /*point adjusted by line thickness*/
  butx = affine(ht, 0.0, *point, cs);   /*point+((ht,0) rotated) */
  printf("newpath");
  pswpos(butx);
  printf(" moveto\n");
  pswpos(affine(ht, wid / 2, *point, cs));
  printf(" lineto");
  pswpos(*point);
  printf(" lineto");
  pswpos(affine(ht, wid / -2, *point, cs));
  printf(" lineto\n");
  printf(" closepath gsave fill grestore 0 setlinejoin stroke setlineparms\n");
  *point = butx;
}


void pssetthick(double lt)
{
  if (lt < 0.0 || lt == lastthick)
    return;
  pswfloat(&output, lt);
  printf(" setlinewidth\n");
  lastthick = lt;
}


void psendline(nametype *op)
{
  printf(" endstroke");
  if (op != NULL)
    printf(" setrgbcolor\n");
  else
    putchar('\n');
}


void pslineopts(int lsp, double param, nametype *op)
{
  if (lsp == XLdashed) {
    if (param == mdistmax)
      param = 3 * fsc;
    printf(" [");
    pswfloat(&output, param / fsc);
    pswfloat(&output, param / fsc);
    printf(" ] 0 setdash\n");
  } else if (lsp == XLdotted) {
    if (param == mdistmax)
      param = 5 * fsc;
    printf(" [ 0");
    pswfloat(&output, param / fsc);
    printf(" ] 0 setdash 1 setlinecap\n");
  }
  if (op == NULL)
    return;
  printf(" currentrgbcolor ");
  wstring(&output, op);
  printf(" setrgbcolor\n");
}


void psbox(postype aat, double halfwid, double halfht, double rad)
{
  int i;
  postype corner[4];

  psnewpath();
  corner[0].xpos = aat.xpos + halfwid;
  corner[0].ypos = aat.ypos + halfht;
  corner[1].xpos = aat.xpos - halfwid;
  corner[1].ypos = aat.ypos + halfht;
  corner[2].xpos = aat.xpos - halfwid;
  corner[2].ypos = aat.ypos - halfht;
  corner[3].xpos = aat.xpos + halfwid;
  corner[3].ypos = aat.ypos - halfht;
  pswcoord(&output, aat.xpos + halfwid, aat.ypos);
  printf(" moveto 0 setlinejoin\n");
  rad = Min(Min(fabs(rad), fabs(halfht)), fabs(halfwid));
  if (rad == 0.0) {
    for (i = 0; i <= 3; i++) {
      pswpos(corner[i]);
      printf(" lineto");
      if (i == 1 || i == 3)
	putchar('\n');
    }
  } else {
    for (i = 0; i <= 3; i++) {
      pswpos(corner[i]);
      pswpos(corner[(i + 1) & 3]);
      pswfloat(&output, rad / fsc);
      printf(" arcto 4 {pop} repeat\n");
    }
  }
  printf(" closepath");
}


void pscircle(double rd)
{
  psnewpath();
  printf(" 0 0");
  pswfloat(&output, fabs(rd) / fsc);
  printf(" 0 360 arc closepath");
}


#define r               ((sqrt(2.0) - 1) * 4 / 3)


void psellipse(double x, double y)
{
  x = fabs(x) / 2;
  y = fabs(y) / 2;
  psnewpath();
  pswcoord(&output, x, 0.0);
  printf(" moveto\n");
  pswcoord(&output, x, y * r);
  pswcoord(&output, x * r, y);
  pswcoord(&output, 0.0, y);
  printf(" curveto\n");
  pswcoord(&output, -x * r, y);
  pswcoord(&output, -x, y * r);
  pswcoord(&output, -x, 0.0);
  printf(" curveto\n");
  pswcoord(&output, -x, -y * r);
  pswcoord(&output, -x * r, -y);
  pswcoord(&output, 0.0, -y);
  printf(" curveto\n");
  pswcoord(&output, x * r, -y);
  pswcoord(&output, x, -y * r);
  pswcoord(&output, x, 0.0);
  printf(" curveto closepath\n");
}

#undef r


void pswprop(postype p1, postype p2, double a, double b, double c)
{
  pprop(p1, &p2, a, b, c);
  pswpos(p2);
}


void psdraw(primitive *node)
{
  /* node is always <> nil */
  int lsp;
  postype tmpat, X0;
  primitive *tn;
  double x, y, lth, fill;

  lsp = lspec(node->spec);
  lth = qenv(node, XLlinethick, node->lthick);   /* printobject(node); */
  /*D if debuglevel > 0 then begin write(log,'psdraw: ');
     snaptype(log,ptype); D*/
  /*D
           write(log,' lth='); wfloat(log,lth);
           writeln(log)
           end;
        if linesignal > 0 then begin write(stderr,'psdraw: ');
           snaptype(stderr,ptype); writeln(stderr) end D*/
  switch (node->ptype) {

  case XLbox:
  case XBLOCK:
    initnesw();
    nesw(node);
    if (node->ptype == XLbox) {
      if (node->UU.Ubox.boxfill >= 0.0 && node->UU.Ubox.boxfill <= 1.0 ||
	  node->shadedp != NULL) {
	psbox(node->aat, node->UU.Ubox.boxwidth / 2,
	      node->UU.Ubox.boxheight / 2, node->UU.Ubox.boxradius);
	pssetthick(lth);
	if (drawn(node, lsp, -1.0)) {
	  printf(" gsave\n");
	  if (node->shadedp == NULL) {
	    pswfloat(&output, node->UU.Ubox.boxfill);
	    printf(" setgray");
	  } else {
	    putchar(' ');
	    wstring(&output, node->shadedp);
	    printf(" setrgbcolor");
	  }
	  printf(" fill grestore\n");
	  pslineopts(lsp, node->lparam, node->outlinep);
	  psendline(node->outlinep);
	} else if (node->shadedp == NULL) {
	  printf(" currentgray");
	  pswfloat(&output, node->UU.Ubox.boxfill);
	  printf(" setgray fill setgray setlineparms\n");
	} else {
	  printf(" currentrgbcolor ");
	  wstring(&output, node->shadedp);
	  printf(" setrgbcolor fill setrgbcolor setlineparms\n");
	}
      } else if (drawn(node, lsp, -1.0)) {
	psbox(node->aat, node->UU.Ubox.boxwidth / 2,
	      node->UU.Ubox.boxheight / 2, node->UU.Ubox.boxradius);
	pssetthick(lth);
	pslineopts(lsp, node->lparam, node->outlinep);
	psendline(node->outlinep);
      }
    }
    pswtext(node->textp, 0.5 * (east + west), 0.5 * (north + south));
    break;

  case XLellipse:
  case XLcircle:
    if (node->ptype == XLellipse) {
      x = node->UU.Uellipse.elwidth;
      y = node->UU.Uellipse.elheight;
      fill = node->UU.Uellipse.efill;
    } else
      fill = node->UU.Ucircle.cfill;
    if (fill >= 0.0 && fill <= 1.0 || node->shadedp != NULL) {
      pssetthick(lth);
      printf(" gsave ");
      pswpos(node->aat);
      printf(" translate\n");
      if (node->ptype == XLellipse)
	psellipse(x, y);
      else
	pscircle(node->UU.Ucircle.radius);
      printf(" gsave ");
      if (node->shadedp == NULL) {
	pswfloat(&output, fill);
	printf(" setgray");
      } else {
	wstring(&output, node->shadedp);
	printf(" setrgbcolor");
      }
      printf(" fill grestore\n");
      if (drawn(node, lsp, -1.0)) {
	pslineopts(lsp, node->lparam, node->outlinep);
	psendline(node->outlinep);
      }
      printf(" grestore\n");
    } else if (drawn(node, lsp, -1.0)) {
      pssetthick(lth);
      printf(" gsave ");
      pswpos(node->aat);
      printf(" translate\n");
      if (node->ptype == XLellipse)
	psellipse(x, y);
      else
	pscircle(node->UU.Ucircle.radius);
      pslineopts(lsp, node->lparam, node->outlinep);
      psendline(node->outlinep);
      printf(" grestore\n");
    }
    pswtext(node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLspline:
    if (drawn(node, lsp, -1.0)) {
      if (!isthen(node)) {  /* first spline */
	tn = node;
	while (tn->son != NULL)
	  tn = tn->son;
	spltot = primdepth(node);
	splcount = spltot;
	tmpat = node->aat;
	pssetthick(lth);
	if (tn->UU.Uline.atype == XDOUBLEHEAD || tn->UU.Uline.atype == XLEFTHEAD)
	  psahead(&node->aat, node->UU.Uline.endpos,
		  qenv(node, XLarrowht, tn->UU.Uline.height),
		  qenv(node, XLarrowwid, tn->UU.Uline.width), lth);
	pslineopts(lsp, node->lparam, node->outlinep);
	psnewpath();
	pswpos(node->aat);
	node->aat = tmpat;
	printf(" moveto\n");
	if (spltot > 1 && node->UU.Uline.aradius == mdistmax) {
	  pswprop(node->UU.Uline.endpos, node->aat, 1.0, 1.0, 2.0);
	  printf(" lineto\n");
	  pswprop(node->aat, node->UU.Uline.endpos, 1.0, 5.0, 6.0);
	} else if (spltot > 1)
	  pswprop(node->aat, node->UU.Uline.endpos, 1 - node->UU.Uline.aradius,
		  node->UU.Uline.aradius, 1.0);
      } else if (splcount > 1 && node->UU.Uline.aradius == mdistmax) {
	pswprop(node->aat, node->UU.Uline.endpos, 5.0, 1.0, 6.0);
	pswprop(node->aat, node->UU.Uline.endpos, 1.0, 1.0, 2.0);
	printf(" curveto\n");
	pswprop(node->aat, node->UU.Uline.endpos, 1.0, 5.0, 6.0);
      } else if (splcount > 1) {
	pswprop(node->aat, node->UU.Uline.endpos,
		0.5 + node->UU.Uline.aradius / 2,
		0.5 - node->UU.Uline.aradius / 2, 1.0);
	pswprop(node->aat, node->UU.Uline.endpos, 1.0, 1.0, 2.0);
	printf(" curveto\n");
	pswprop(node->aat, node->UU.Uline.endpos,
		0.5 - node->UU.Uline.aradius / 2,
		0.5 + node->UU.Uline.aradius / 2, 1.0);
      }
      if (splcount == 1) {
	if (spltot > 1 && node->UU.Uline.aradius == mdistmax) {
	  pswprop(node->aat, node->UU.Uline.endpos, 5.0, 1.0, 6.0);
	  pswprop(node->aat, node->UU.Uline.endpos, 1.0, 1.0, 2.0);
	  printf(" curveto\n");
	} else if (spltot > 1)
	  pswprop(node->aat, node->UU.Uline.endpos, node->UU.Uline.aradius,
		  1 - node->UU.Uline.aradius, 1.0);
	tmpat = node->UU.Uline.endpos;
	if (node->UU.Uline.atype == XDOUBLEHEAD ||
	    node->UU.Uline.atype == XRIGHTHEAD) {
	  x = linlen(node->UU.Uline.endpos.xpos - node->aat.xpos,
		     node->UU.Uline.endpos.ypos - node->aat.ypos);
	  y = qenv(node, XLarrowht, node->UU.Uline.height);
	  pprop(node->aat, &tmpat, y, x - y, x);
	}
	pswpos(tmpat);
	if (node->UU.Uline.aradius == mdistmax)
	  printf(" lineto");
	else
	  printf(" curveto");
	psendline(node->outlinep);
	if (node->UU.Uline.atype == XDOUBLEHEAD ||
	    node->UU.Uline.atype == XRIGHTHEAD)
	  psahead(&node->UU.Uline.endpos, node->aat,
		  qenv(node, XLarrowht, node->UU.Uline.height),
		  qenv(node, XLarrowwid, node->UU.Uline.width), lth);
      }
      node->ptype = XLline;
      /*D; if debuglevel > 0 then writeln(log,'node ',splcount:1) ;D*/
      splcount--;
    }
    break;

  case XLline:
  case XLarrow:
  case XLmove:
    if (drawn(node, lsp, -1.0)) {
      tn = node;
      while (tn->son != NULL)
	tn = tn->son;
      if (!isthen(node)) {
	tmpat = node->aat;
	pssetthick(lth);
	if (tn->UU.Uline.atype == XDOUBLEHEAD || tn->UU.Uline.atype == XLEFTHEAD)
	  psahead(&node->aat, node->UU.Uline.endpos,
		  qenv(node, XLarrowht, tn->UU.Uline.height),
		  qenv(node, XLarrowwid, tn->UU.Uline.width), lth);
	pslineopts(lsp, node->lparam, node->outlinep);
	psnewpath();
	pswpos(node->aat);
	printf(" moveto\n");
      }
      if (node->son == NULL &&
	  (tn->UU.Uline.atype == XDOUBLEHEAD ||
	   tn->UU.Uline.atype == XRIGHTHEAD)) {
	y = qenv(node, XLarrowht, tn->UU.Uline.height);
	pswpos(affine(y, 0.0, node->UU.Uline.endpos,
		      affang(node->UU.Uline.endpos, node->aat)));
	printf(" lineto");
	psendline(node->outlinep);
	psahead(&node->UU.Uline.endpos, node->aat, y,
		qenv(node, XLarrowwid, tn->UU.Uline.width), lth);
      } else if (node->son == NULL) {
	/*D; if debuglevel > 0 then writeln(log,'last node started');D*/
	pswpos(node->UU.Uline.endpos);
	printf(" lineto");
	psendline(node->outlinep);
      } else {
	pswpos(node->UU.Uline.endpos);
	printf(" lineto\n");
      }
      /* ptype := XLline */
    }
    pswtext(node->textp, 0.5 * (node->UU.Uline.endpos.xpos + node->aat.xpos),
	    0.5 * (node->aat.ypos + node->UU.Uline.endpos.ypos));
    break;

  case XLarc:
    pssetthick(lth);
    if (drawn(node, lsp, -1.0)) {
      if (node->UU.Uline.atype == XDOUBLEHEAD ||
	  node->UU.Uline.atype == XLEFTHEAD) {
	tmpat.xpos = node->aat.xpos +
		     node->UU.Uline.aradius * cos(node->UU.Uline.endpos.xpos);
	tmpat.ypos = node->aat.ypos +
		     node->UU.Uline.aradius * sin(node->UU.Uline.endpos.xpos);
	if (node->UU.Uline.aradius == 0.0)
	  x = 0.0;
	else
	  x = atan(qenv(node, XLarrowht, node->UU.Uline.height) /
		   node->UU.Uline.aradius);
	if (node->UU.Uline.endpos.ypos >= 0.0) {
	  node->UU.Uline.endpos.xpos += x;
	  node->UU.Uline.endpos.ypos -= x;
	} else {
	  node->UU.Uline.endpos.xpos -= x;
	  node->UU.Uline.endpos.ypos += x;
	}
	X0.xpos = node->aat.xpos +
		  node->UU.Uline.aradius * cos(node->UU.Uline.endpos.xpos);
	X0.ypos = node->aat.ypos +
		  node->UU.Uline.aradius * sin(node->UU.Uline.endpos.xpos);
	psahead(&tmpat, X0, qenv(node, XLarrowht, node->UU.Uline.height),
		qenv(node, XLarrowwid, node->UU.Uline.width), lth);
      }
      if (node->UU.Uline.atype == XDOUBLEHEAD ||
	  node->UU.Uline.atype == XRIGHTHEAD) {
	tmpat.xpos = node->aat.xpos + node->UU.Uline.aradius *
	      cos(node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
	tmpat.ypos = node->aat.ypos + node->UU.Uline.aradius *
	      sin(node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
	if (node->UU.Uline.aradius == 0.0)
	  x = 0.0;
	else
	  x = atan(qenv(node, XLarrowht, node->UU.Uline.height) /
		   node->UU.Uline.aradius);
	if (node->UU.Uline.endpos.ypos >= 0.0)
	  node->UU.Uline.endpos.ypos -= x;
	else
	  node->UU.Uline.endpos.ypos += x;
	X0.xpos = node->aat.xpos + node->UU.Uline.aradius * cos(
		      node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
	X0.ypos = node->aat.ypos + node->UU.Uline.aradius * sin(
		      node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
	psahead(&tmpat, X0, qenv(node, XLarrowht, node->UU.Uline.height),
		qenv(node, XLarrowwid, node->UU.Uline.width), lth);
      }
      psnewpath();
      pswpos(node->aat);
      pswfloat(&output, node->UU.Uline.aradius / fsc);
      pswfloat(&output, 180.0 / pi * node->UU.Uline.endpos.xpos);
      pswfloat(&output,
	180.0 / pi * (node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos));
      if (node->UU.Uline.endpos.ypos >= 0.0)
	printf(" arc");
      else
	printf(" arcn");
      pslineopts(lsp, node->lparam, node->outlinep);
      psendline(node->outlinep);
    }
    pswtext(node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLstring:
    pswtext(node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLtroff:
    if (node->textp != NULL) {
      wstring(&output, node->textp);
      putchar('\n');
    } else {
      if (node->lthick >= 0.0)
	pssetthick(node->lthick);
    }
    break;
  }
  /*DUGHM ;flush(output) MHGUD*/
}  /* psdraw */


/* # include 'mps.h' */

/* include tex.h */
/* tex.x */
/* Output routines for TeX, tTeX (eepicemu), pict2e */

void texprelude(double n, double s, double e, double w)
{
  printf("\\setlength{\\unitlength}{1in}\n");
  if (s != distmax) {
    printf("\\begin{picture}");
    wcoord(&output, e - w, n - s);
    wcoord(&output, w, s);
    printf("\n\\thicklines\n");
  }
  printf("%% %s\n", Version);
}


void texpostlude(void)
{
  printf("\\end{picture}\n");
  /*Dif debuglevel > 0 then writeln(log,'texpostlude done');D*/
}


void arrowhead(double pointx, double pointy, double tailx,
		      double taily)
{
  double x, y, r, ct;

  r = linlen(pointx - tailx, pointy - taily);
  if (r == 0.0)
    return;
  ct = Min(0.05, 0.5 * r) / r;
  x = pointx + ct * (tailx - pointx);
  y = pointy + ct * (taily - pointy);
  printf("\n\\put");
  wcoord(&output, x, y);
  printf("{\\vector");
  wrslope(pointx - x, pointy - y, true);
  putchar('}');
}


void texwrtext(nametype *tp, double x, double y)
{
  boolean A, B, L, R;

  if (tp == NULL)
    return;
  printf("\\put");
  checkjust(tp, &A, &B, &L, &R);
  if (A)
    wcoord(&output, x, y + 0.1);
  else if (B)
    wcoord(&output, x, y - 0.05);
  else
    wcoord(&output, x, y);
  putchar('{');
  stacktext(tp, true);
  printf("}\n");
}


void p2ahead(postype *point, postype shaft, double ht)
{
  postype butx;

  /*D; if debuglevel > 0 then begin
      write(log,'p2ahead point='); wpair(log,point.xpos,point.ypos);
      write(log,' shaft='); wpair(log,shaft.xpos,shaft.ypos);
      butx := affang(point,shaft);
      write(log,' affang='); wpair(log,butx.xpos,butx.ypos);
      write(log,' ht= '); wfloat(log,ht);
      writeln(log) end ;D*/
  /* affang contains direction cosines */
  butx = affine(ht, 0.0, *point, affang(*point, shaft));
  /*D; if debuglevel > 0 then begin
      write(log,' butx='); wpair(log,butx.xpos,butx.ypos);
      writeln(log) end ;D*/
  printf("\\put");
  wpos(butx);
  printf("{\\vector");
  wrslope(point->xpos - butx.xpos, point->ypos - butx.ypos, true);
  printf("}\n");
  *point = butx;
}


void p2setthick(double lt)
{
  if (lt < 0.0 || lt == lastthick)
    return;
  printf("\\linethickness{");
  wfloat(&output, lt);
  printf("pt}\n");
  lastthick = lt;
}


void texdraw(primitive *node)
{
  int i, npts, lsp;
  double r, x, y, x1, y1, ct, st, lgth, lth;
  primitive *tn, *p;
  postype tmpat, X0, X3;

  lsp = lspec(node->spec);
  lth = qenv(node, XLlinethick, node->lthick);
  switch (node->ptype) {

  case XLbox:
  case XBLOCK:
    if (drawn(node, lsp, -1.0) || node->textp != NULL) {
      initnesw();
      nesw(node);
      if (drawmode == pict2e)
	p2setthick(lth);
      printf("\\put");
      wcoord(&output, west, south);
      if (node->ptype == XBLOCK)
	printf("{\\makebox");
      else if (lsp == XLsolid)
	printf("{\\framebox");
      else if (lsp == XLinvis)
	printf("{\\makebox");
      else if (lsp == XLdashed) {
	printf("{\\dashbox");
	if (node->lparam != mdistmax)
	  wbrace(node->lparam / fsc);
	else
	  wbrace(venv(node, XLdashwid) / fsc);
      } else if (lsp == XLdotted) {
	printf("{\\dashbox");
	printf("{0.01}");
      }
      if (node->ptype == XLbox)
	wcoord(&output, node->UU.Ubox.boxwidth, node->UU.Ubox.boxheight);
      else
	wcoord(&output, node->UU.UEMPTY7.blockwidth, node->UU.UEMPTY7.blockheight);
      putchar('{');
      stacktext(node->textp, false);
      printf("}}\n");
    }
    break;

  case XLline:
  case XLarrow:
    if (drawn(node, lsp, -1.0)) {
      tn = node;
      while (tn->son != NULL)
	tn = tn->son;
      if (!isthen(node)) {  /* first segment */
	if (drawmode == pict2e)
	  p2setthick(lth);
	if (tn->UU.Uline.atype == XDOUBLEHEAD || tn->UU.Uline.atype == XLEFTHEAD)
	  p2ahead(&node->aat, node->UU.Uline.endpos,
		  qenv(node, XLarrowht, tn->UU.Uline.height));
      }
      if (node->son == NULL &&
	  (node->UU.Uline.atype == XDOUBLEHEAD ||
	   node->UU.Uline.atype == XRIGHTHEAD))
	p2ahead(&node->UU.Uline.endpos, node->aat,
		qenv(node, XLarrowht, tn->UU.Uline.height));
      lgth = linlen(node->UU.Uline.endpos.xpos - node->aat.xpos,
		    node->UU.Uline.endpos.ypos - node->aat.ypos);
      if (drawmode == pict2e ||
	  lsp == XLsolid && (lgth > 0.18 || drawmode == tTeX)) {
	printf("\\put");
	wpos(node->aat);
	printf("{\\line");
	wrslope(node->UU.Uline.endpos.xpos - node->aat.xpos,
		node->UU.Uline.endpos.ypos - node->aat.ypos, false);
	printf("}\n");
      } else if (lsp == XLsolid) {
	npts = (long)floor(lgth / 0.005 + 0.5);
	printf("\\multiput");
	wpos(node->aat);
	wcoord(&output, (node->UU.Uline.endpos.xpos - node->aat.xpos) / npts,
	       (node->UU.Uline.endpos.ypos - node->aat.ypos) / npts);
	printf("{%d}", npts + 1);
	printf("{\\makebox(0.005555,0.00825){\\tiny .}}\n");
      } else if (lsp == XLdashed) {
	printf("\\put");
	wpos(node->aat);
	printf("{\\dashline[50]");
	if (node->lparam != mdistmax)
	  wbrace(node->lparam / fsc);
	else
	  wbrace(venv(node, XLdashwid) / fsc);
	printf("(0,0)");
	wcoord(&output, node->UU.Uline.endpos.xpos - node->aat.xpos,
	       node->UU.Uline.endpos.ypos - node->aat.ypos);
	printf("}\n");
      } else if (lsp == XLdotted) {
	printf("\\dottedline{%7.4f}", 0.05 / fsc);
	wpos(node->aat);
	wpos(node->UU.Uline.endpos);
      }
    }
    texwrtext(node->textp, 0.5 * (node->UU.Uline.endpos.xpos + node->aat.xpos),
	      0.5 * (node->aat.ypos + node->UU.Uline.endpos.ypos));
    break;

  case XLspline:
    if ((drawmode == pict2e) & drawn(node, lsp, -1.0)) {
      if (!isthen(node)) {  /* first spline */
	tn = node;
	while (tn->son != NULL)
	  tn = tn->son;
	spltot = primdepth(node);
	splcount = spltot;
	tmpat = node->aat;
	p2setthick(lth);
	if (tn->UU.Uline.atype == XDOUBLEHEAD || tn->UU.Uline.atype == XLEFTHEAD)
	  p2ahead(&node->aat, node->UU.Uline.endpos,
		  qenv(node, XLarrowht, tn->UU.Uline.height));
	/* p2lineopts(lsp,lparam,outlinep); */
	if (spltot > 1 && node->UU.Uline.aradius == mdistmax) {
	  printf("\\put");
	  wcoord(&output, node->aat.xpos, node->aat.ypos);
	  printf("{\\line");
	  wrslope((node->UU.Uline.endpos.xpos - node->aat.xpos) / 2,
		  (node->UU.Uline.endpos.ypos - node->aat.ypos) / 2, false);
	  printf("}\n");
	  printf("\\cbezier");
	  wprop(node->UU.Uline.endpos, node->aat, 1.0, 1.0, 2.0);
	  wprop(node->aat, node->UU.Uline.endpos, 1.0, 5.0, 6.0);
	} else if (spltot > 1) {
	  printf("\\cbezier");
	  wpos(node->aat);
	  node->aat = tmpat;
	  wprop(node->aat, node->UU.Uline.endpos, 1 - node->UU.Uline.aradius,
		node->UU.Uline.aradius, 1.0);
	}
      } else if (splcount > 1 && node->UU.Uline.aradius == mdistmax) {
	wprop(node->aat, node->UU.Uline.endpos, 5.0, 1.0, 6.0);
	wprop(node->aat, node->UU.Uline.endpos, 1.0, 1.0, 2.0);
	printf("%%\n");
	printf("\\cbezier");
	wprop(node->aat, node->UU.Uline.endpos, 1.0, 1.0, 2.0);
	wprop(node->aat, node->UU.Uline.endpos, 1.0, 5.0, 6.0);
      } else if (splcount > 1) {
	wprop(node->aat, node->UU.Uline.endpos,
	      0.5 + node->UU.Uline.aradius / 2,
	      0.5 - node->UU.Uline.aradius / 2, 1.0);
	wprop(node->aat, node->UU.Uline.endpos, 1.0, 1.0, 2.0);
	printf("%%\n");
	printf("\\cbezier");
	wprop(node->aat, node->UU.Uline.endpos, 1.0, 1.0, 2.0);
	wprop(node->aat, node->UU.Uline.endpos,
	      0.5 - node->UU.Uline.aradius / 2,
	      0.5 + node->UU.Uline.aradius / 2, 1.0);
      }
      if (splcount == 1) {
	tmpat = node->UU.Uline.endpos;
	if (node->UU.Uline.atype == XDOUBLEHEAD ||
	    node->UU.Uline.atype == XRIGHTHEAD) {
	  x = linlen(node->UU.Uline.endpos.xpos - node->aat.xpos,
		     node->UU.Uline.endpos.ypos - node->aat.ypos);
	  y = qenv(node, XLarrowht, node->UU.Uline.height);
	  pprop(node->aat, &node->UU.Uline.endpos, y, x - y, x);
	}
	if (spltot > 1 && node->UU.Uline.aradius == mdistmax) {
	  wprop(node->aat, node->UU.Uline.endpos, 5.0, 1.0, 6.0);
	  wprop(node->aat, node->UU.Uline.endpos, 1.0, 1.0, 2.0);
	  printf("%%\n");
	  printf("\\put");
	  wprop(node->aat, node->UU.Uline.endpos, 1.0, 1.0, 2.0);
	  printf("{\\line");
	  wrslope((node->UU.Uline.endpos.xpos - node->aat.xpos) / 2,
		  (node->UU.Uline.endpos.ypos - node->aat.ypos) / 2, false);
	  printf("}\n");
	} else if (spltot > 1) {
	  wprop(node->aat, node->UU.Uline.endpos, node->UU.Uline.aradius,
		1 - node->UU.Uline.aradius, 1.0);
	  wpos(node->UU.Uline.endpos);
	  printf("%%\n");
	}
	if (node->UU.Uline.atype == XDOUBLEHEAD ||
	    node->UU.Uline.atype == XRIGHTHEAD)
	  p2ahead(&tmpat, node->aat,
		  qenv(node, XLarrowht, node->UU.Uline.height));
      }
      node->ptype = XLline;
      /*D; if debuglevel > 0 then writeln(log,'node ',splcount:1) ;D*/
      splcount--;
    } else if (lsp == XLdotted || lsp == XLdashed || lsp == XLsolid) {
      if (!isthen(node) &&
	  (node->UU.Uline.atype == XDOUBLEHEAD ||
	   node->UU.Uline.atype == XLEFTHEAD))
	    /* first spline */
	      arrowhead(node->aat.xpos, node->aat.ypos,
			node->UU.Uline.endpos.xpos, node->UU.Uline.endpos.ypos);
      printf("\\spline");
      wpos(node->aat);
      wpos(node->UU.Uline.endpos);
      if (node->son == NULL)
	putchar('\n');
      else if (node->son->son == NULL) {
	wpos(node->son->UU.Uline.endpos);
	if (node->UU.Uline.atype == XRIGHTHEAD ||
	    node->UU.Uline.atype == XDOUBLEHEAD)
	  arrowhead(node->son->UU.Uline.endpos.xpos,
		    node->son->UU.Uline.endpos.ypos, node->son->aat.xpos,
		    node->son->aat.ypos);
	node->ptype = XLline;
	putchar('\n');
	/* son := nil */
	deletetree(&node->son);
      } else {
	pprop(node->son->UU.Uline.endpos, &node->son->aat, 1.0, 1.0, 2.0);
	wpos(node->son->aat);
	node->ptype = XLline;
	putchar('\n');
      }
    }
    break;

  case XLmove:
    texwrtext(node->textp, 0.5 * (node->UU.Uline.endpos.xpos + node->aat.xpos),
	      0.5 * (node->aat.ypos + node->UU.Uline.endpos.ypos));
    break;

  case XLellipse:
    if (drawmode == pict2e)
      p2setthick(lth);
    printf("\\put");
    wpos(node->aat);
    if (drawmode == TeX) {
      printf("{\\ellipse");
      wbrace(node->UU.Uellipse.elwidth / fsc);
      wbrace(node->UU.Uellipse.elheight / fsc);
      printf("}\n");
    } else {
      printf("{\\oval");
      wcoord(&output, node->UU.Uellipse.elwidth, node->UU.Uellipse.elheight);
      printf("}\n");
    }
    texwrtext(node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLcircle:
    if (lsp != XLinvis) {
      if (drawmode == pict2e)
	p2setthick(lth);
      printf("\\put");
      wpos(node->aat);
      printf("{\\circle");
      wbrace(2.0 * node->UU.Ucircle.radius / fsc);
      printf("}\n");
    }
    texwrtext(node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLarc:
    if ((drawmode == pict2e) & drawn(node, lsp, -1.0)) {
      p2setthick(node->lthick);   /* p2linecap(lsp); */
      X0.xpos = node->aat.xpos +
		node->UU.Uline.aradius * cos(node->UU.Uline.endpos.xpos);
      X0.ypos = node->aat.ypos +
		node->UU.Uline.aradius * sin(node->UU.Uline.endpos.xpos);
      if (node->UU.Uline.atype == XDOUBLEHEAD ||
	  node->UU.Uline.atype == XLEFTHEAD) {
	if (node->UU.Uline.aradius == 0.0)
	  x = 0.0;
	else
	  x = atan(qenv(node, XLarrowht, node->UU.Uline.height) /
		   node->UU.Uline.aradius);
	if (node->UU.Uline.endpos.ypos >= 0.0) {
	  node->UU.Uline.endpos.xpos += x;
	  node->UU.Uline.endpos.ypos -= x;
	} else {
	  node->UU.Uline.endpos.xpos -= x;
	  node->UU.Uline.endpos.ypos += x;
	}
	tmpat = X0;
	X0.xpos = node->aat.xpos +
		  node->UU.Uline.aradius * cos(node->UU.Uline.endpos.xpos);
	X0.ypos = node->aat.ypos +
		  node->UU.Uline.aradius * sin(node->UU.Uline.endpos.xpos);
	p2ahead(&tmpat, X0, qenv(node, XLarrowht, node->UU.Uline.height));
      }
      X3.xpos = node->aat.xpos + node->UU.Uline.aradius *
		  cos(node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
      X3.ypos = node->aat.ypos + node->UU.Uline.aradius *
		  sin(node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
      if (node->UU.Uline.atype == XDOUBLEHEAD ||
	  node->UU.Uline.atype == XRIGHTHEAD) {
	if (node->UU.Uline.aradius == 0.0)
	  x = 0.0;
	else
	  x = atan(qenv(node, XLarrowht, node->UU.Uline.height) /
		   node->UU.Uline.aradius);
	if (node->UU.Uline.endpos.ypos >= 0.0)
	  node->UU.Uline.endpos.ypos -= x;
	else
	  node->UU.Uline.endpos.ypos += x;
	tmpat = X3;
	X3.xpos = node->aat.xpos + node->UU.Uline.aradius * cos(
		      node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
	X3.ypos = node->aat.ypos + node->UU.Uline.aradius * sin(
		      node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos);
	p2ahead(&tmpat, X3, qenv(node, XLarrowht, node->UU.Uline.height));
      }
      npts = (long)(1.0 + fabs(node->UU.Uline.endpos.ypos) / pi);
      node->UU.Uline.endpos.ypos /= npts;
      while (npts > 0) {
	printf("\\cbezier");
	wpos(X0);
	x = cos(node->UU.Uline.endpos.ypos / 2);
	y = sin(node->UU.Uline.endpos.ypos / 2);
	x1 = (4 - x) / 3;
	if (y != 0.0)
	  y1 = (1.0 - x * x1) / y;
	else
	  y1 = 0.0;
	tmpat.xpos = cos(
	    node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos / 2.0);
	tmpat.ypos = sin(
	    node->UU.Uline.endpos.xpos + node->UU.Uline.endpos.ypos / 2.0);
	wpos(affine(node->UU.Uline.aradius * x1, -node->UU.Uline.aradius * y1,
		    node->aat, tmpat));
	wpos(affine(node->UU.Uline.aradius * x1, node->UU.Uline.aradius * y1,
		    node->aat, tmpat));
	if (npts > 1) {
	  node->UU.Uline.endpos.xpos += node->UU.Uline.endpos.ypos;
	  X0.xpos = node->aat.xpos +
		    node->UU.Uline.aradius * cos(node->UU.Uline.endpos.xpos);
	  X0.ypos = node->aat.ypos +
		    node->UU.Uline.aradius * sin(node->UU.Uline.endpos.xpos);
	  wpos(X0);
	  printf("%%\n");
	}
	npts--;
      }
      wpos(X3);
      printf("%%\n");   /*; p2dashdot(lsp,lparam,outlinep) */
    } else if (iscorner(principal(node->UU.Uline.endpos.xpos, 0.5 * pi)) &&
	       fabs(fabs(node->UU.Uline.endpos.ypos) - pi / 2.0) < 0.001) {
      if (drawmode == pict2e)
	p2setthick(lth);
      printf("\\put");
      wpos(node->aat);
      printf("{\\oval");
      wcoord(&output, 2 * node->UU.Uline.aradius / fsc,
	     2 * node->UU.Uline.aradius / fsc);
      if (node->direction != XLdown && node->direction != XLup &&
	  node->direction != XLright && node->direction != XLleft) {
	p = findenv(node);
	if (p != NULL)
	  node->direction = p->direction;
      }
      if (node->direction == XLleft && node->UU.Uline.endpos.ypos < 0.0 ||
	  node->direction == XLdown && node->UU.Uline.endpos.ypos > 0.0)
	printf("[bl]}\n");
      else if (node->direction == XLleft && node->UU.Uline.endpos.ypos > 0.0 ||
	       node->direction == XLup && node->UU.Uline.endpos.ypos < 0.0)
	printf("[tl]}\n");
      else if (node->direction == XLright && node->UU.Uline.endpos.ypos < 0.0 ||
	       node->direction == XLup && node->UU.Uline.endpos.ypos > 0.0)
	printf("[tr]}\n");
      else
	printf("[br]}\n");
      texwrtext(node->textp, node->aat.xpos, node->aat.ypos);
    } else if (((1L << ((long)drawmode)) &
		((1L << ((long)TeX)) | (1L << ((long)pict2e)))) != 0 &&
	       node->UU.Uline.aradius > 0.0) {
      if (node->UU.Uline.aradius >= 0.05 / sin(pi / 18.0)) {
	npts = (long)floor(fabs(node->UU.Uline.endpos.ypos) / (pi / 18.0) + 0.5);
	if (npts < 4)
	  npts = 4;
      } else
	npts = (long)floor(fabs(node->UU.Uline.endpos.ypos) / atan(
			     0.05 / node->UU.Uline.aradius) + 0.5);
      r = node->UU.Uline.endpos.ypos / npts;
      ct = cos(r);
      st = sin(r);
      x = node->UU.Uline.aradius * cos(node->UU.Uline.endpos.xpos);
      y = node->UU.Uline.aradius * sin(node->UU.Uline.endpos.xpos);
      /*D            if debuglevel = 2 then writeln(log,'x,y',x:7:4,y:7:4);  D*/
      for (i = 1; i <= npts; i++) {
	x1 = ct * x - st * y;
	y1 = st * x + ct * y;
	/*D               if debuglevel = 2 then writeln(log,x1:7:4,y1:7:4);   D*/
	printf("\\put");
	wcoord(&output, node->aat.xpos + x, node->aat.ypos + y);
	printf("{\\line");
	wcoord(&output, x1 - x, y1 - y);
	if (fabs(x1 - x) != 0.0)
	  wbrace(fabs(x1 - x) / fsc);
	else
	  wbrace(fabs(y1 - y) / fsc);
	printf("}\n");
	if (i == 1 && (node->UU.Uline.atype == XDOUBLEHEAD ||
		       node->UU.Uline.atype == XLEFTHEAD))
	  arrowhead(node->aat.xpos + x, node->aat.ypos + y,
		    node->aat.xpos + x1, node->aat.ypos + y1);
	else if (i == npts && (node->UU.Uline.atype == XDOUBLEHEAD ||
			       node->UU.Uline.atype == XRIGHTHEAD))
	  arrowhead(node->aat.xpos + x1, node->aat.ypos + y1,
		    node->aat.xpos + x, node->aat.ypos + y);
	x = x1;
	y = y1;
      }
      texwrtext(node->textp, node->aat.xpos, node->aat.ypos);
    }
    break;

  case XLstring:
    texwrtext(node->textp, node->aat.xpos, node->aat.ypos);
    break;

  case XLtroff:
    if (node->textp != NULL) {
      wstring(&output, node->textp);
      putchar('\n');
    }
    break;
  }
  /*DUGHM ; flush(output) MHGUD*/
}  /* texdraw */


void treedraw(primitive *node)
{
  while (node != NULL) {
    switch (drawmode) {

    case TeX:
    case tTeX:
    case pict2e:
      texdraw(node);
      break;

    case PGF:
      pgfdraw(node);
      break;

    case PSTricks:
      pstdraw(node);
      break;

    case MFpic:
      mfpdraw(node);
      break;

    case PS:
    case PSfrag:
      psdraw(node);
      break;

    /* PSmps: mpsdraw(node); */
    case MPost:
      mpodraw(node);
      break;

    case xfig:
      xfigdraw(node);
      break;
    }
    if (node->son != NULL)
      treedraw(node->son);
    if (drawmode == xfig) {
      if (node->ptype == XBLOCK && node->direction == -1)
	printf("-6\n");
    }
    node = node->next_;
  }
}


void drawtree(double n, double s, double e, double w, primitive *eb)
{
  /* n,s,e,w: real; eb: primitivep */
  double fsctmp;

  switch (drawmode) {

  case PGF:   /* n,s,e,w */
    pgfprelude();
    treedraw(eb);
    pgfpostlude();
    break;

  case PSTricks:
    pstprelude(n, s, e, w);
    treedraw(eb);
    pstpostlude();
    break;

  case MFpic:
    mfpprelude(n, s, e, w);
    treedraw(eb);
    mfppostlude();
    break;

  case PS:
  case PSfrag:
    fsctmp = fsc;
    fsc /= 72;
    psprelude(n, s, e, w, venv(eb, XLlinethick));
    treedraw(eb);
    pspostlude();
    fsc = fsctmp;
    break;

  /* PSmps: begin
     fsctmp := fsc; fsc := fsc/72;
     mpsprelude(n,s,e,w);
     treedraw( eb );
     mpspostlude;
     fsc := fsctmp
     end; */
  case MPost:
    fsctmp = fsc;
    fsc /= 72;   /* n,s,e,w */
    mpoprelude();
    treedraw(eb);
    mpopostlude();
    fsc = fsctmp;
    break;

  case xfig:
    xfigprelude();
    treedraw(eb);
    /* xfigpostlude */
    break;

  case TeX:
  case tTeX:
  case pict2e:
    if (s != distmax) {
      texprelude(n, s, e, w);
      treedraw(eb);
      texpostlude();
    }
    break;
  }
}


/*B.B*/
/* onefile */
/* G end. G */



/* End. */
