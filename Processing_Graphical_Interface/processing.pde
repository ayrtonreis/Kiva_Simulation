int UNIT = 40;
int counter = 0;
ArrayList<PVector> vectors = new ArrayList<PVector>();
PVector kivaPos, missionOrigin, missionDestination;
ArrayList<PVector> path = new ArrayList<PVector>();
Boolean isOnMissionPath = false;
Boolean isRecharging = false;
Boolean isLoaded = false;
Boolean isRechargingLedRed = false;
int kivaDir = 1;
Float chargeLevel = 100.0; 
String mission = "####";
Boolean isLifting = false;
PrintWriter output;

void setup(){
  size(1280,800);
  
  buildTrajectory();
  kivaPos = vectors.get(0);
  missionOrigin = new PVector(-1,-1);
  missionDestination = new PVector(-1,-1);
}

void draw(){
  readData();
  background(240);
  drawMatrix();
  drawTrajectory();
  stroke(0);
  strokeWeight(1);
  line(0,height/2, width, height/2);
  drawMission();
  drawKiva();
  drawInfo();
  delay(100);
}

void mousePressed(){
  ellipse( mouseX, mouseY, 2, 2 );
  text( "x: " + mouseX + " y: " + mouseY, mouseX + 2, mouseY );
}