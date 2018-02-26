void buildTrajectory(){
  PVector temp_v = new PVector(width/2 - UNIT*13, height/2);
  PVector right = new PVector(UNIT, 0);
  PVector left = new PVector(-UNIT, 0);
  PVector up = new PVector(0, -UNIT);
  PVector down = new PVector(0, UNIT);
  
  //vectors.add(temp_v);
  temp_v = PVector.add(temp_v, down);
  
  for(int i = 0; i < 2; i++){
    temp_v = PVector.add(temp_v, up);
    vectors.add(temp_v);
  }
  
  for(int i = 0; i < 6; i++){
    temp_v = PVector.add(temp_v, up);
    vectors.add(temp_v);
    temp_v = PVector.add(temp_v, right);
    vectors.add(temp_v);
  }
  
  for(int i = 0; i < 15; i++){
    temp_v = PVector.add(temp_v, right);
    vectors.add(temp_v);
  }
  
  for(int i = 0; i < 6; i++){
    temp_v = PVector.add(temp_v, down);
    vectors.add(temp_v);
    temp_v = PVector.add(temp_v, right);
    vectors.add(temp_v);
  }
  vectors.remove(vectors.size() -1);
  temp_v = vectors.get(vectors.size()-1);
  
  for(int i = 0; i < 2; i++){
    temp_v = PVector.add(temp_v, down);
    vectors.add(temp_v);
  }
  
  for(int i = 0; i < 6; i++){
    temp_v = PVector.add(temp_v, down);
    vectors.add(temp_v);
    temp_v = PVector.add(temp_v, left);
    vectors.add(temp_v);
  }
  
  for(int i = 0; i < 15; i++){
    temp_v = PVector.add(temp_v, left);
    vectors.add(temp_v);
  }
  
  for(int i = 0; i < 6; i++){
    temp_v = PVector.add(temp_v, up);
    vectors.add(temp_v);
    temp_v = PVector.add(temp_v, left);
    vectors.add(temp_v);
  }
  
  vectors.remove(vectors.size() -1); 
}

void drawMatrix(){
  strokeWeight(1);
  for(int h = 0; h <= height; h += UNIT){
    stroke(200);
    line(0, h, width, h);  
  }
    for(int w = 0; w <= width; w += UNIT){
    stroke(200);
    line(w, 0, w, height);  
  }
}

void drawTrajectory(){
  strokeWeight(8);
  for(int i = 0; i < vectors.size(); i++){
    PVector v = vectors.get(i);
    point(v.x, v.y);
  }
}

void writeFileTrajectory(){
  output = createWriter("trajectory.txt"); 
  for(int i = 0; i < vectors.size(); i++){
    PVector v = vectors.get(i);
    output.println(v.x + " " + v.y + "\n");
  }
  output.flush(); // Writes the remaining data to the file
  output.close(); // Finishes the file
}

void drawKiva(){
  pushMatrix();
    translate(kivaPos.x, kivaPos.y);
    fill(0);
    textSize(12);
    text("("+kivaPos.x/10+","+kivaPos.y/10+")",20,10);
    if(kivaDir == 2)
      rotate(PI/2);
    else if(kivaDir == 3)
      rotate(PI);
    else if(kivaDir == 4)
      rotate(-PI/2);
    noStroke();
    rectMode(CENTER);
    fill(100);
    rect(-20,0, 8,20,4);
    rect(20,0, 8,20,4);
 
    stroke(0);
    strokeWeight(1);
    fill(232, 130, 58);
    rect(0,0, UNIT, 1.1*UNIT, UNIT/2);
    
    if(isLoaded){
      stroke(#683810,80);
      strokeWeight(2);
      fill(#683810,60);
      rect(0,0, UNIT+10, 1.1*UNIT+10);
    }
    
    noStroke();
    
    if(!isRecharging){
      fill(254, 180, 80);
    }
    else if(!isRechargingLedRed){
      fill(255,0,0);
      isRechargingLedRed = true;
    }
    else{
      fill(0, 255, 0);
      isRechargingLedRed = false;
    }
    
    ellipse(0,-18, 4,4);
    
  popMatrix();
}

void readData(){

  Table table = loadTable("../kiva_car/cpp_output.csv", "header");
  TableRow row = table.getRow(0);
  int x = row.getInt("lastPosX") * 10;
  int y = row.getInt("lastPosY") *10;
  kivaDir = row.getInt("lastOrientation");
  isLoaded = boolean(row.getInt("isLoaded"));
  
  if(row.getFloat("chargeLevel") > chargeLevel)
    isRecharging = true;
  else
    isRecharging = false;
  
  chargeLevel = row.getFloat("chargeLevel");
  mission = row.getString("mission");
  
  println(x, " - ", y);
  println("------------");
  
  kivaPos = new PVector(x,y);
  
  Boolean isNone = false;
  for(int i = 0; i< mission.length(); i++){
    if(mission.charAt(i) == 'n' || mission.charAt(i) == 'o'){
      isNone = true;
      break;
    }
  }
  
  if(!isNone){
    println(mission);
    String[] stringList = split(mission, ' ');
    
    stringList[0] = stringList[0].substring(1, stringList[0].length()-1);
    stringList[1] = stringList[1].substring(1, stringList[1].length()-1);
    String[] originList = split(stringList[0], ';');
    String[] destinationList = split(stringList[1], ';');
    
    PVector o = new PVector(Integer.parseInt(originList[0])*10, Integer.parseInt(originList[1])*10);
    PVector d = new PVector(Integer.parseInt(destinationList[0])*10, Integer.parseInt(split(destinationList[1], ")")[0])*10);
    
    if(o.x != missionOrigin.x && o.y != missionOrigin.y  && d.x != missionDestination.x && d.y != missionDestination.y){
      isOnMissionPath = false;
      path.clear();
      missionOrigin = o;
      missionDestination = d;
    }
    
    if(isLoaded){
      isOnMissionPath = true;
    }
    
    if(isOnMissionPath){
      path.add(new PVector(x,y));
    }
    
  }
  else{
    missionOrigin.x = -1;
    missionOrigin.y = -1;
    missionDestination.x = -1;
    missionDestination.y = -1;
    isOnMissionPath = false;
    path.clear();
    if(isRecharging)
      mission = "recharging...";
    else if(chargeLevel < 30)
      mission = "recharge battery";
  }
}

void drawInfo(){
  pushMatrix();
    translate(width/2 - 130, height/2);
    fill(100, 60);
    textSize(30);
    text("KIVA SIMULATION",0,-10);
    fill(100, 80);
    textSize(20);
    text("by: Ayrton Reis, Matheus Traldi, Nilo Freitas",-80,20);
    
  popMatrix();
  
  pushMatrix();
    translate(width-200, height-60);
    fill(0);
    textSize(12);
    text("Mission: "+mission,0,0);
    if(chargeLevel <= 30)
      fill(255,0,0);
    text("Battery: "+nf(chargeLevel, 2, 2)+"%",0,20);
    text("Current Dir: "+kivaDir,0,40);
  popMatrix();
}

void drawMission(){
  if(missionOrigin.x != -1 && missionDestination.x != -1){
    noStroke();
    fill(0,200,100);
    ellipse(missionOrigin.x, missionOrigin.y, 12, 12);
    fill(220,40,20);
    ellipse(missionDestination.x, missionDestination.y, 12, 12);
    
    stroke(#444444, 50);
    strokeWeight(4);
    for (int i = 0; i < path.size()-1; i++){
      line(path.get(i).x, path.get(i).y,path.get(i+1).x, path.get(i+1).y);
    }
    
    println("Path: "+path.size());
    
  }
}