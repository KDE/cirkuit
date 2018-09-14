% simple-circuitmacros.m4
%
% From "M4 Macros for Electric Circuit Diagrams in LaTeX Documents" (author Dwight Aplevich).
%
.PS                            # Pic input begins with .PS
cct_init                       # Set defaults

elen = 0.75
Origin: Here
   source(up_ elen); llabel(-,v_s,+)
   resistor(right_ elen);  rlabel(,R,)
   dot
     { 
      capacitor(down_ to (Here,Origin))     #(Here,Origin) = (Here.x,Origin.y)
      rlabel(+,v,-); llabel(,C,)
      dot
      }
   line right_ elen*2/3
   inductor(down_ Here.y-Origin.y); rlabel(,L,); b_current(i)
   line to Origin

.PE                            # Pic input ends with .PE

