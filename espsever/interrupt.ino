void humin(){
  human=not(human);
  Serial.println(human);
  if (human){
    digitalWrite(humanled,LOW);
  }
  else{
    digitalWrite(humanled,HIGH);
  }
}


void soundchange(){
  Serial.println("sound change");
  soundChage= true;
  music=music+1;
  if (music>=4){
    music=0;
  }
  Serial.println(music);
}


void playmusic(){
  if(music==0){
    
  }
  else if(music==1){
    
  }
  else if(music==2){
    
  }
  else{
    
  }
  delay(100);
}

