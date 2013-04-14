% Answers to exercises of the tutorial by Andre Heck
% (http://remote.science.uva.nl/~heck/Courses/mptut.pdf).

outputtemplate := "%j-%c.mps";

beginfig(1);
  u = 1cm;
  draw (0,2u)--(0,0)--(4u,0);
  pickup pencircle scaled 1pt;
  draw (0,0){up}
    for i=1 upto 8: ..(i/2, sqrt(i/2))*u endfor;
  label.lrt(btex $\sqrt{x}$ etex, (3, sqrt(3))*u);
  label.bot(btex $x$ etex, (2u,0));
  label.lft(btex $y$ etex, (0, u));
endfig;

beginfig(2);
  numeric ux, uy;
  120ux=1.2in; 4uy=2.4in;
  draw (0,4uy)--(0,0)--(120ux,0);
  pickup pencircle scaled 1pt;
  draw (0,uy){right}
    for ix=1 upto 8:
    ..(15ix*ux,uy*2/(1+cosd 15ix))
  endfor;
  label.bot(btex $x$ axis etex, (60ux,0));
  label.lft(btex $y$ axis etex rotated 90, (0,2uy));
  label.lft(btex $\displaystyle y={2\over1+\cos x}$ etex, (120ux, 4uy));
endfig;

beginfig(3);
  draw fullcircle scaled 2cm;
endfig;

beginfig(4);
  -z1=z2=(1cm,0);
  z3=(0, (2+-+1)*cm);
  draw z1--z2--z3--cycle;
endfig;

beginfig(5);
  u := .5cm;
  z1=-z4=(2u,0);
  z2=(u,2u+-+u);
  x3=-x2;
  y3=y2;
  x6=x2;
  y6=-y2;
  x5=x3;
  y5=-y3;
  draw z1--z2--z3--z4--z5--z6--z1;
endfig;

beginfig(6);
  u := 1cm;
  -z1=z2=(1u,0);
  z3=(0, 2u+-+1u);
  draw z1--z2--z3--z1;
  z0=(0,y3/3);
  draw z0--z1;
  draw z0--z2;
  draw z0--z3;

endfig;

beginfig(7);
  u := 1cm;
  z1=(u,-u);
  z2=(u,u);
  z3=(-u,u);
  z4=(-u,-u);
  draw z1--z2--z3--z4--z1;
  z11=2*z1;
  z22=2*z2;
  z33=2*z3;
  z44=2*z4;
  draw z11--z22--z33--z44--z11;
  draw z1--z11;
  draw z2--z22;
  draw z3--z33;
  draw z4--z44;
endfig;

beginfig(11);
  z1=(6cm,0);
  z2=(-3cm,0);
  z3=(0,5cm);
  draw z1--z2--z3--cycle;
  draw z1--1/2[z2,z3];
  draw z2--1/2[z1,z3];
  draw z3--1/2[z1,z2];
  dotlabel.lft("A",z2);
  dotlabel.rt("B", z1);
  dotlabel.top("C", z3);
  dotlabel.bot("C'", 1/2[z1,z2]);
  dotlabel.urt("A'", 1/2[z3,z1]);
  dotlabel.ulft("B'", 1/2[z2,z3]);
endfig;

beginfig(12);
  u := 1cm;
  for i=0 upto 4:
    z[i] = dir(90+360/5*i)*u;
  endfor
  draw z0--z1--z2--z3--z4--z0;
  dotlabel.llft("O", (0,0));
endfig;

beginfig(13);
  pair p;
  p = (1,1);
  z1=-z2=dir(135)*2cm;
  z11 = z1+p;
  z22 = z2+p;
  draw z11--z22;
  z3=dir(105)*1cm;
  z33 = z3+p;
  draw p--z3;
  draw p withpen pencircle scaled 4;
endfig;

beginfig(14);
  pair p[];
  p0 = (0,0);
  p1 = (2cm,3cm);
  p2 = (3cm,2cm);
  draw p0--p1--p2--cycle;
  fill p0--p1--p2--cycle withcolor .5white;
endfig;

beginfig(15);
  z0 = (0,0);
  z1 = (2cm, 0);
  z2 = dir(40)*2cm;
  draw z0--z1;
  draw z0--z2;
  drawarrow 1/2*z1..dir(20)*1cm..1/2*z2;
endfig;

beginfig(16);
  -z1 = z2 = (1cm,0);
  z3 = whatever[z1, (dir(60)+z1)] = whatever[z2, (dir(120)+z2)];
  z4 = 1/2[z1,z3]+dir(-30)*.4cm;
  z5 = 1/2[z1,z3]+dir(150)*.4cm;
  draw z1--z2--z3;
  draw z1{dir 30}..z3{up};
  draw z1{up}..z3{dir 30};
  pickup pencircle scaled 4pt;
  draw z1;
  draw z2;
  draw z3;
endfig;

beginfig(17);
  r1 = 2cm;
  r2 = .2cm;
  z0 = (0,-r1);
  z1 = (r1,0);
  z2 = (0,r1);
  z3 = (-r1,0);
  z4 = (0,0);
  z5 = -z6 = (0, 1/2r1);
  path p[];
  p1 = z0{right}..z1{up}..{left}z2{dir -15}..z4{dir 195}..{dir -15}cycle;
  p2 = z0{left}..z3{up}..{right}z2{dir -15};
  draw p1;
  draw p2;
  fill p1 withcolor black;
  p3 = z5+(r2,0){up}..z5+(-r2,0){down}..{up}cycle;
  draw p3;
  fill p3 withcolor black;
  p4 = z6+(r2,0){up}..z6+(-r2,0){down}..{up}cycle;
  draw p4;
  fill p4 withcolor white;
endfig;

beginfig(18);
  pair A, B, C, C';
  u := 1cm;
  A = (0,0);
  B = (5u, 0);
  C = (2u,3u);
  C' = whatever[A, B] = C + whatever*dir(1/2*angle(A-C)+1/2*angle(B-C));
  draw A--B--C--cycle;
  draw C--C';
  dotlabel.lft("A", A);
  dotlabel.urt("B", B);
  dotlabel.top("C", C);
  dotlabel.bot("C'", C');

  z1 = C + dir(angle(A-C))*.5cm;
  z2 = C + dir(angle(C'-C))*.5cm;
  z3 = C + dir(angle(B-C))*.5cm;
  a1 = 1/2*angle(A-C)+1/2*angle(C'-C);
  a2 = 1/2*angle(C'-C)+1/2*angle(B-C);
  z12 = C + dir(a1)*.5cm;
  z23 = C + dir(a2)*.5cm;
  draw z1..z12..z2..z23..z3;
  draw z12--z12+dir(a1)*.1cm;
  draw z12--z12+dir(a1)*-.1cm;
  draw z23--z23+dir(a2)*.1cm;
  draw z23--z23+dir(a2)*-.1cm;
endfig;

beginfig(19);
  pair A, B, C, A', B', C', I;
  u := 1cm;
  A = (0, 0);
  B = (4u, -2u);
  C = (1.5u, 3u);
  B' = whatever[A, C]
    = B + whatever*dir(1/2*angle(C-B)+1/2*angle(A-B));
  C' = whatever[A, B]
    = C + whatever*dir(1/2*angle(A-C)+1/2*angle(B-C));
  A' = whatever[B, C]
    = A + whatever*dir(1/2*angle(C-A)+1/2*angle(B-A));
  I = whatever[A, A'] = whatever[B, B'];
  draw A--B--C--cycle;
  draw A--A';
  draw B--B';
  draw C--C';
  draw C'..A'..B'..cycle;
  dotlabel.lft("A", A);
  dotlabel.rt("B", B);
  dotlabel.top("C", C);
  dotlabel.ulft("B'", B');
  dotlabel.urt("A'", A');
  dotlabel.bot("C'", C');
  dotlabel.llft("I", I);
endfig;

beginfig(20);
  vardef f(expr x) = sqrt(x) enddef;
  u := 1cm;
  xmin = 0; xmax = 4;
  ymin = 0; ymax = f(xmax);
  draw (0,0)--(xmax,0)*u;
  draw (0,0)--(0,ymax)*u;
  for i = 1 upto 4:
    draw (i*u, -0.05u)--(i*u, 0.05u);
  endfor;
  for i = 1 upto 2:
    draw (-0.05u,i*u)--(0.05u, i*u);
  endfor;
  for i = 0 upto 4:
    label.bot(decimal(i), (i*u, 0));
  endfor;
  for i = 0 upto 2:
    label.lft(decimal(i), (0, i*u));
  endfor;
  path p;
  p = (0,0)
    for x = 0.1 step 0.1 until 4:
    ..(x*u, f(x)*u)
  endfor;
  draw p withpen pencircle scaled 2pt;
  save labeloffset;
  labeloffset := .5cm;
  label.bot(btex $x$ etex, (2u,0));
  label.lft(btex $y$ etex, (0,1u));
  label.bot(btex $\displaystyle y=\sqrt x$ etex,
      (3u, f(3)*u)); 
endfig;

verbatimtex
  \documentclass{article}
  \usepackage{amsfonts}
  \begin{document}
  etex

  beginfig(21);
  u := 1cm;
  a := 4; b = 2;
  phi := angle(a*u, b*u);
  draw (-.5u, 0)--(a+.5,0)*u;
  draw (0,-.5u)--(0,b+.5)*u;
  draw (0,0)--(a,b)*u;
  draw (a,0)*u--(a,b)*u dashed evenly;
  draw (0,b)*u--(a,b)*u dashed evenly;
  draw (.5u,0){up}..dir(phi)*.5u{dir(phi+90)};
  label.llft("0", (0,0));
  label.bot(btex $a$ etex, (a,0)*u);
  label.lft(btex $ib$ etex, (0,b)*u);
  label.lft(btex $\mathbb{C}$ etex, (0,b+.5)*u);
  label(btex $\phi$ etex, dir(phi/2)*.8u);
  label.rt(btex $a+ib=z$ etex, (a,b)*u);
  label(btex $\lbrace$ etex xscaled 1.5 yscaled (sqrt(a*a+b*b)*2.8) rotated (phi-90),
      1/2(a,b)*u+dir(phi+90)*1mm);
  label(btex $|z|$ etex, 1/2(a,b)*u+dir(phi+90)*4mm);
endfig;

beginfig(22);
  u := 1cm;
  draw (0,0)--(.2u,0)--(.2u,0)+dir(60)*.1u--
    (.3u,0)+dir(-60)*.1u--(0.4u,0)--(5.9u,0);
  draw (0,0)--(0,.2u)--(0,.2u)+dir(60)*.1u--
    (0,.3u)+dir(30)*.1u--(0,.4u)--(0, 6.5u);
  for i=1 upto 5:
    draw (.4u+i*u, -.05u)--(.4u+i*u, .05u);
    label.bot(decimal(i*5+1975), (.4u+i*u, 0));
  endfor;
  for i=1 upto 6:
    draw (-.05u, i*u)--(.05u, i*u);
    label.lft(decimal(i*2+80), (0, i*u));
  endfor;
  vardef datapoint(expr x, y) =
    (1.4u+(x-1980)/5*1u, 1u+(y-82)/2*u)
  enddef;
  z1 = datapoint(1980, 86);
  z2 = datapoint(1985, 85);
  z3 = datapoint(1990, 91);
  z4 = datapoint(1995, 86);
  z5 = datapoint(2000, 83);
  draw z1--z2--z3--z4--z5;
  for i=1 upto 5:
    dotlabel("", z[i]);
  endfor;
  label(btex year etex, (3.4u, -.6cm));
  label(btex beer consumption (liter) etex rotated 90,
      (-.6cm, 6.5u/2));
endfig;

beginfig(23);
  vardef ff(expr r, g, b) =
    (r+g+b)/3*(1,1,1)
  enddef;
  vardef gg(expr r, g, b) =
    (.3*r+.59*g+.11*b)*(1,1,1)
  enddef;
    
  u := 1/2cm;
  save defaultscale;
  defaultscale := 10pt/fontsize(defaultfont);
  path sqr, grid;
  grid := unitsquare scaled u;
  sqr := grid xscaled 1/3;
  for i=0 upto 10:
    label.bot(decimal(i/10), ((i+1/2)*u,0));
    label.lft(decimal(i/10), (0,(i+1/2)*u));
    for j=0 upto 10:
      fill sqr shifted (i*u,j*u)
        withcolor (i*0.1, j*0.1,0);
      fill sqr shifted (i*u+1/3*u,j*u)
        withcolor (ff(i*.1, j*.1, 0));
      fill sqr shifted (i*u+2/3*u, j*u)
        withcolor (gg(i*.1, j*.1, 0));
      draw grid shifted (i*u,j*u); % draw grid
    endfor;
  endfor;
  label.bot("r",(6u,-2/3u));
  label.lft("g",(-u,6u));
  label.top("RGB(r,g,0)", (6u,11u));
endfig;

beginfig(24);
  u := 1cm;
  pair A, B;
  path p;
  A = (-4u,0); B = (-2u, 0);
  p = fullcircle scaled 1u xscaled 2 shifted (1/2[A,B]);
  draw p;
  draw p rotated 60;
  pair A', B';
  A' = A rotated 60;
  B' = B rotated 60;
  draw A{down}..A'{dir -30};
  draw B{down}..B'{dir -30};
endfig;

beginfig(25);
  u := 1cm;
  path p, q, r;
  p = (0,0)--2u*dir(30);
  q = (0,0)--2u*dir(45);
  r = buildcycle(p, fullcircle scaled 3u, q,
      fullcircle scaled 4u);
  draw p;
  draw q;
  fill r withcolor .5green;
  draw r withpen pencircle scaled 2;
endfig;

beginfig(26);
  a := 100; b := 60;
  path orbit[];
  pair S;
  orbit1 = fullcircle xscaled 2a yscaled 2b;
  S = -(a+-+b, 0);

  def draw_area(expr angleone, angletwo, pic) =
    save t, c, p;
    numeric t[];
    path c[];
    pair p[];
    (whatever, t1) = (S--(infinity*dir(angleone) shifted S))
      intersectiontimes orbit1;
    (whatever, t2) = (S--(infinity*dir(angletwo) shifted S))
      intersectiontimes orbit1;
    p1 = point t1 of orbit1;
    p2 = point t2 of orbit1;
    p3 = .5cm*dir(angleone) shifted p1;
    p4 = .5cm*dir(angletwo) shifted p2;
    c1 = S--p3;
    c2 = S--p4;
    c3 = buildcycle(c1, c2, orbit1);
    fill c3 withcolor (1, 1, 0);
    draw c1;
    draw c2;
    drawarrow 1/2[p1,p3]{direction t1 of orbit1}..
      1/2[p2,p4]{direction t2 of orbit1};
    label(pic,
        (arclength(S--point ((t1+t2)/2) of orbit1)+.5cm)*dir((angleone+angletwo)/2) shifted S);
  enddef;

  draw_area(10, 25, btex $\Delta t$ etex);
  draw_area(70, 150, btex $\Delta t'$ etex);
  draw orbit1;
  draw S withpen pencircle scaled 4pt;
  draw (-a,0)--(a,0) dashed withdots;
  label.bot("Sun", S);
endfig;

beginfig(27);
  u := 1cm;
  draw (-2u,0)--(2u,0);
  draw (0,-2u)--(0,2u);
  for i=0 upto 10:
    path p;
    if ((i mod 5) <> 0):
      p := (i*u/5,-.05cm)--(i*u/5,.05cm);
    else:
      p := (i*u/5,-.1cm)--(i*u/5,.1cm);
    fi;
    draw p;
    draw p rotated 90;
    draw p rotated 180;
    draw p rotated -90;
  endfor;
endfig;

beginfig(28);
  vardef f(expr x) = 4-x*x enddef;

  u := 1cm;
  path xaxis, yaxis;
  xaxis = (-2.1,0)--(2.1,0);
  yaxis = (0,f(2.1))--(0,f(0)+.5);

  path pf;
  pf = (-2.1,f(-2.1))
    for x=-2 step .1 until 2.2:
    ..(x,f(x))
  endfor;

  draw xaxis scaled u;
  draw yaxis scaled u;
  
  pair p;
  p = pf intersectionpoint xaxis;
  delta = abs((xpart p))/6;
  x = xpart p;
  for i=0 upto 11:
    y := max(f(x), f(x+delta));
    path c;
    c = unitsquare xscaled delta yscaled y shifted (x, 0);
    fill c scaled u withcolor (1,1,0);
    draw c scaled u;
    x := x+delta;
  endfor;
  draw pf scaled u withpen pencircle scaled 2;

  pair move; move = (150, 0);

  pf := (-2.1,f(-2.1))
    for x=-2 step .1 until 2.2:
    ..(x,f(x))
  endfor;

  draw xaxis scaled u shifted move;
  draw yaxis scaled u shifted move;
  
  pair p;
  p = pf intersectionpoint xaxis;
  delta := abs((xpart p))/6;
  x := (xpart p) + delta;
  for i=1 upto 10:
    y := min(f(x), f(x+delta));
    path c;
    c = unitsquare xscaled delta yscaled y shifted (x, 0);
    fill c scaled u shifted move withcolor (1,1,0);
    draw c scaled u shifted move;
    x := x+delta;
  endfor;
  draw pf scaled u withpen pencircle scaled 2 shifted move;
endfig;

beginfig(29);
  u := 1cm;
  draw unitsquare scaled u;
  for i=1 upto 9:
    draw (i,0)*1mm--(i,10)*1mm;
  endfor;
  for i=1 upto 9:
    draw (0,i)*mm--(10,i)*mm;
  endfor;

  picture pic[];
  pic1 = currentpicture shifted (0,1u);
  pic2 = currentpicture shifted (1u,0);
  pic3 = currentpicture shifted (1u,1u);
  draw pic1;
  draw pic2;
  draw pic3;

  pic4 = currentpicture shifted (0,2u);
  pic5 = currentpicture shifted (2u,0);
  pic6 = currentpicture shifted (2u,2u);
  draw pic4;
  draw pic5;
  draw pic6;

  draw (2u,0)--(2u,4u);
  draw (0,2u)--(4u,2u);
endfig;

beginfig(30);
  numeric n; n := 5;
  u := 1cm;
  ydelta := 1u;
  pair a[], b[];
  for i=1 upto n:
    a[i] = (0, (i-1)*ydelta);
    b[i] = a[i] shifted (2u,0);
    dotlabel.lft("a"& decimal(i), a[i]);
    dotlabel.rt("b"& decimal(i), b[i]);
  endfor;
  for i=1 upto n:
    for j=1 upto n:
      draw a[i]--b[j];
    endfor;
  endfor;
  
endfig;

beginfig(31);
  vardef snowflake_help(expr A, B, C, n) =
    if n > 0:
      save c, o, D, E, F, G, H, I, AA, BB, CC;
      path c[];
      pair o, D, E, F, G, H, I, AA, BB, CC;
      c1 = A--B--C--cycle;
      o = 1/3(A+B+C);
      AA = A rotatedaround(o, -60);
      BB = B rotatedaround(o, -60);
      CC = C rotatedaround(o, -60);
      c2 = AA--BB--CC--cycle;
      draw c1;
      draw c2;

      D = (A--B) intersectionpoint (CC--AA);
      E = (A--B) intersectionpoint (AA--BB);
      F = (C--B) intersectionpoint (AA--BB);
      G = (CC--BB) intersectionpoint (B--C);
      H = (A--C) intersectionpoint (BB--CC);
      I = (AA--CC) intersectionpoint (A--C);
      snowflake_help(A, D, I, n-1);
      snowflake_help(D, AA, E, n-1);
      snowflake_help(B, F, E, n-1);
      snowflake_help(BB, G, F, n-1);
      snowflake_help(C, H, G, n-1);
      snowflake_help(CC, I, H, n-1);
      unfill c1;
      unfill c2;
    fi;
  enddef;
  
  pair A, B, C;
  A = 2cm*dir(120);
  B = 2cm*dir(0);
  C = 2cm*dir(-120);
  snowflake_help(A, B, C, 5);
endfig;

end;
