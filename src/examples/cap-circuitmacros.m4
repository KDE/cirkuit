% cap-circuitmacros.m4
.PS

gen_init
elen = 0.5
linethick_(1.0)

darrow_init

define(`black2',`0.0, 0.0, 0.0')
define(`grey',`0.9, 0.9, 0.9')
define(`grey4',`0.3, 0.3, 0.5')
define(`coord',`(elen*(`$1'),elen*(`$2'))')

  box at coord(0, 0.6) ht 0.3*elen wid 3*elen fill 0.7
  h = 0.3

  rgbfill(grey, line from coord(1.5,0.0) to coord(-1.5,0.0) \
      to coord(-1.5,h) \
      to coord(1.5,h) \
      to coord(1.5,0.0)
  )
 
thinlines_
box at coord(0, 0.15) ht 0.3*elen wid 1.42*elen fill 1.0
box at coord(0, 0.15) ht 0.3*elen wid 1.36*elen fill 0.7 
thicklines_
line from coord(1.5,0.0) to coord(-1.5,0.0)
line from coord(1.5,h) to coord(-1.5,h)

thinlines_
box at coord(0, 0.35) ht 0.05*elen wid 4*elen fill 0.3
thicklines_
box at coord(0, 0.6) ht 0.3*elen wid 3*elen fill 0.7
box at coord(0, 1.25) ht 1.0*elen wid 0.8*elen fill 0.7

rgbdraw(grey4, arrow from coord(2.3, 1.0) to coord(1.8, 0.38) )
rgbdraw(grey4, arrow from coord(1.1, -0.5) to coord(0.7, -0.02) )
setrgb(grey4)

darrow(from (0.6*elen,1.41*elen) down_ 0.2,,t,0.1*elen,,,->)
darrow(from (0.6*elen,1.4*elen) up_ 0.2,,t,0.1*elen,,,->)

setrgb(black2)

move to coord(-1.2,0.0)
line thick 2.0*elen to coord(-1.2,-0.2)
line thick 2.0*elen to coord(-1.8,-0.2)
dot
move left_ 0.5*elen
"Shield"

move to coord(-1.0,0.75)
line thick 2.0*elen to coord(-1.0,1.4)
line thick 2.0*elen to coord(-1.4,1.4)
dot

move left_ 0.98*elen
"\lq Low\rq \,terminal"
move to coord(0.0,-0.0)
line thick 2.0*elen to coord(0.0,-0.7)
line thick 2.0*elen to coord(-0.4,-0.7)
dot

move left_ 0.98*elen
"\lq High\rq \,terminal"

move to coord(2.95,1.0)
"Specimen"

move to coord(1.7,-0.5)
"Insulator"


.PE')

