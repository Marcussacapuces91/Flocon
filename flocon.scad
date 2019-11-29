module flocon() {
    for (a=[0:5]) rotate([0,0,a*60])
    for (i=[1:5], j=[0:i-1]) {
        translate([j * 50 * sqrt(3), i * 100 - j * 50, 0]) rotate([0,0,55-60*a]) led();
    }
    rotate([0,0,55]) led();
}

module led() {
    difference() {
        color("white") cube([50,50,18], center=true);
        cylinder(d=45, h=10);
        translate([22.5,-22.5,10]) rotate([0,0,45])cube([20,10,10],center=true);
    }
    translate([0,12.5,-10]) rotate([0,180,0]) text("Vdd");
    translate([25,12.5,-10]) rotate([0,180,0]) text("Di");
    translate([-7.5,-22.5,-10]) rotate([0,180,0]) text("Do");
    translate([25,-22.5,-10]) rotate([0,180,0]) text("Gnd");
    
    color("grey") for (x=[-27+4.5, 27-4.5], y=[-21+4.5, 21-4.5]) translate([x,y,-5]) cube([9,9,10], center=true);
}

*translate([0,0,1.5]) rotate([180,0,0]) flocon();

difference() {
    cube([1100,1200,25], center=true);
  
    for (a=[0:5]) rotate([0,0,a*60]) for (i=[1:5], j=[0:i-1]) {
        translate([j * 50 * sqrt(3), i * 100 - j * 50, 25-19]) rotate([0,0,35-60*a]) cube([51,55,25],center=true);
    }
    translate([0,0,25-19]) rotate([0,0,35]) cube([51,55,25],center=true);
    
    for (b=[-5:5], a=[-27.5,0,27.5]) translate([b*50*sqrt(3) + a,0,42.5]) rotate([0,45,0]) cube([50,1300,50], center=true);
}
