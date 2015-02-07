
int  outputPins[] = {8, 12,9,6,5,4,7,10,11};
int layer1=2;
int layer2=3;
int layer3=13;

const int buttonPin = 15;
int currentMode = 0;
int isButtonPressed = false;


void setup() {   
  Serial.begin(9600);
  
  pinMode(layer1, OUTPUT);
  pinMode(layer2, OUTPUT);
  pinMode(layer3, OUTPUT);
   
    for(int i=0; i<= sizeof(outputPins)-1;i++){
        pinMode(outputPins[i], OUTPUT);  
        delay(100); 
    }  
  
}

void loop() {
  activateCubeMode(currentMode);
  currentMode = getModeFromInput();
  
}

void activateCubeMode(int mode){
  
  switch(mode){
       case 1 : elevatorPatternCube();
         break;
       case 2 : wallModeCube();
         break;
       case 3:  randomModeCube();
         break;
       case 4:  combineModes();
         break;
       case 0 : break;  
  }
  
}

int getModeFromInput(){
  int buttonState = digitalRead(buttonPin);
  int mode = currentMode;
  
   
  if(buttonState == HIGH && !isButtonPressed){
      isButtonPressed = true;
      Serial.println("Next");
      if( currentMode == 4){
         mode = 0;
      } else {
         mode++;
      }
      
    } else if (buttonState == LOW && isButtonPressed) {
      isButtonPressed = false;
   } else if(buttonState == HIGH ){
      isButtonPressed = true;
   } else if(buttonState == LOW ){
     isButtonPressed = false;
   }
   Serial.println(mode);
   return mode;
   
}

void combineModes(){
  wallModeCube();
  randomModeCube();
  elevatorPatternCube();
}

//-----------------------------------------------------------------------------------------------------------------------//
//WALL MODE CUBE
//-----------------------------------------------------------------------------------------------------------------------//

void wallModeCube(){
  int leds[] = {12,9,6,5,4,7,10,11};
  int layers[] = {layer1,layer2,layer3 };
  
   for( int i=0; i<= 7;i++){
      for( int t=0; t <= 8;t++){
        
          int thirdLayerOppositeLED = getOppositeLED(i);
          blinkLED(layer3, thirdLayerOppositeLED, leds);
          blinkLED(layer3, -1, NULL);
          blinkLED(layer3, i, leds);
                    
          int secondLayerOppositeLED = getOppositeLED(i);
          blinkLED(layer1, secondLayerOppositeLED, leds);
          blinkLED(layer1, -1, leds);
          blinkLED(layer1, i, leds);
             
          int firstLayerOppositeLED = getOppositeLED(i);
          blinkLED(layer2, firstLayerOppositeLED, leds);
          blinkLED(layer2, -1, NULL);
          blinkLED(layer2, i, leds);

          delay(1);
               
       }
   } 
  
}

int getOppositeLED(int startingLED){
  
 int ledAhead = startingLED + 4;
 int numOfMovingLEDs = 8 ;
 
 if(ledAhead == numOfMovingLEDs){
     return 0;
 }  
 else if(ledAhead > numOfMovingLEDs){
     return ledAhead - numOfMovingLEDs;
 }
 else return ledAhead;

}

void blinkLED(int layer, int led, int leds[]){
   // Central column which is always 'ON'
  int ledPin = 8;
  
  if(led >= 0){
    ledPin = leds[led]; 
  } 
 
  digitalWrite(layer, HIGH);
  digitalWrite(ledPin, HIGH); 
  delay(2);
  digitalWrite(ledPin, LOW);
  digitalWrite(layer, LOW); 
  
}

//-----------------------------------------------------------------------------------------------------------------------//
//ELEVATOR PATTERN CUBE
//-----------------------------------------------------------------------------------------------------------------------//

void elevatorPatternCube(){
  int leds[] = {12,9,6,5,4,7,10,11,8};
  int layers[] = {layer1,layer2,layer3, layer2 };
 
  for( int layer=0; layer <= 3; layer++){
     
     digitalWrite(layers[layer], HIGH);
    
     for( int t = 0; t <= 10; t++){              
         for( int i = 0; i <= 8; i++){                 
             digitalWrite(leds[i], HIGH);
             delay(2);
             digitalWrite(leds[i], LOW);               
          }
      } 
    
     digitalWrite(layers[layer], LOW);
  }
}

//-----------------------------------------------------------------------------------------------------------------------//
//RANDOM MODE CUBE
//-----------------------------------------------------------------------------------------------------------------------//

void randomModeCube(){
  int leds[] = {8, 12,9,6,5,4,7,10,11};
  int layers[] = {layer1,layer2,layer3, layer2 };
  int numOfConcurrentActiveLEDs = random(26);
  
  for(int i=0; i <= numOfConcurrentActiveLEDs; i++){
      lightLed(leds, layers);
  }
}

void lightLed(int leds[], int layers[]){
  int randLed = random(9); 
  int randLayer = random(3);
  int randDelay = random(30);

  digitalWrite(layers[randLayer],HIGH);
  digitalWrite(leds[randLed],HIGH);
 
  delay(randDelay);
 
  digitalWrite(leds[randLed],LOW);
  digitalWrite(layers[randLayer],LOW); 
 
}
//-----------------------------------------------------------------------------------------------------------------------//
