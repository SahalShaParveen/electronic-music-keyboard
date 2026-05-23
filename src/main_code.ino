int passiveBuzzer = 32;

int buttonC = 13; 
int buttonD = 12; 
int buttonE = 14;
int buttonF = 27; 
int buttonG = 26; 
int buttonA = 25;
int buttonB = 33;
int buttonC2 = 18; 

int onButton =  21; 

int redLED = 15; 
int greenLED = 19; 
int blueLED = 5; 

int pot = 34; 

int buzzerChannel = 0;
int currentFreq = 0;

const String notesInOctave[] = {"C", "D", "E", "F", "G", "A", "B", "C2"}; 


void setup() {

    pinMode(onButton, INPUT_PULLUP); 

    pinMode(buttonC, INPUT_PULLUP);
    pinMode(buttonD, INPUT_PULLUP);
    pinMode(buttonE, INPUT_PULLUP);
    pinMode(buttonF, INPUT_PULLUP);
    pinMode(buttonG, INPUT_PULLUP);
    pinMode(buttonA, INPUT_PULLUP);
    pinMode(buttonB, INPUT_PULLUP);
    pinMode(buttonC2, INPUT_PULLUP); 

    pinMode(pot, INPUT); 

    pinMode(redLED, OUTPUT); 
    pinMode(blueLED, OUTPUT); 
    pinMode(greenLED, OUTPUT); 

    ledcSetup(buzzerChannel, 2000, 8);
    ledcAttachPin(passiveBuzzer, buzzerChannel);
    ledcWriteTone(buzzerChannel, 0); 

    digitalWrite(redLED, LOW); 
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
} // setup


int octaveNum = 0;
bool onState = false; 
bool prevOnState = false; 
bool wasPressed = false; 


void loop() {
    onState = turnOnButton(prevOnState); 
    
    if (onState != prevOnState) {
        if (onState) {
            startupMusic(); 
        } else {
            shutdownMusic(); 
        }
    }

    if (onState){
        octaveNum = potOctave(octaveNum); 
        octaveLED(octaveNum); 
        piano(octaveNum); 
    } else {
        ledcWriteTone(buzzerChannel, 0);
        digitalWrite(redLED, LOW);
        digitalWrite(greenLED, LOW);
        digitalWrite(blueLED, LOW); 
    }

    prevOnState = onState; 
} // END loop 


// returns the frequency of the necessary note
//
int giveFreq(String note, int octaveNum) {
    int frequency = 0; 
    const int baseFrequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};

    float octaveFactor = 1;  

    switch (octaveNum) {
        case 0:
            octaveFactor = 1; 
            break;
        case 1:
            octaveFactor = 2;
            break;
        case -1:
            octaveFactor = 0.5;
            break;
        default:

            break;
    }

    for (int i=0; i<8; i++) {
        if (note.equals(notesInOctave[i])) {
            frequency = round(baseFrequencies[i] * octaveFactor);
            break;
        }
    }

    return frequency; 
} // END giveFreq


// Takes input from a potentiometer and changes the octave accordingly
//
int potOctave(int octaveNum) {

    int value = analogRead(pot);  

    if (value <= 1365 ) {
        octaveNum = -1; 
    } else if (value <= 2730) {
        octaveNum = 0; 
    } else if (value <= 4095) {
        octaveNum = 1; 
    }

    return octaveNum; 
} // END potOctave


// Plays a note when repective button is pressed. OctaveNum needs to be provided (-1, 0, 1)
// Should be called repeatedly to work properly. 
//
void piano(int octaveNum) {
    int newFreq = currentFreq;  
    bool anyPressed = false;

    if (!digitalRead(buttonC))  { newFreq = giveFreq("C", octaveNum ); anyPressed = true; }
    if (!digitalRead(buttonD))  { newFreq = giveFreq("D", octaveNum ); anyPressed = true; }
    if (!digitalRead(buttonE))  { newFreq = giveFreq("E", octaveNum ); anyPressed = true; }
    if (!digitalRead(buttonF))  { newFreq = giveFreq("F", octaveNum ); anyPressed = true; }
    if (!digitalRead(buttonG))  { newFreq = giveFreq("G", octaveNum ); anyPressed = true; }
    if (!digitalRead(buttonA))  { newFreq = giveFreq("A", octaveNum ); anyPressed = true; }
    if (!digitalRead(buttonB))  { newFreq = giveFreq("B", octaveNum ); anyPressed = true; }
    if (!digitalRead(buttonC2)) { newFreq = giveFreq("C2", octaveNum ); anyPressed = true; }

    if (!anyPressed) {
        newFreq = 0;
    }

    if (newFreq != currentFreq) {
        ledcWriteTone(buzzerChannel, newFreq);
        currentFreq = newFreq;
    }
} // END


// Lights LED accordingly when provided with the octaveNum
//
void octaveLED(int octaveNum) {
    switch (octaveNum) {
        case -1:
            digitalWrite(redLED, HIGH); 
            digitalWrite(greenLED, LOW);
            digitalWrite(blueLED, LOW); 
            break;
        case 0:
            digitalWrite(redLED, LOW); 
            digitalWrite(greenLED, HIGH);
            digitalWrite(blueLED, LOW); 
            break;
        case 1: 
            digitalWrite(redLED, LOW); 
            digitalWrite(greenLED, LOW);
            digitalWrite(blueLED, HIGH); 
            break;
    }
} // END octaveLED  


// Turns the device on or off
//
bool turnOnButton(bool onState) {
    bool isPressed = !digitalRead(onButton);  
    
    if (wasPressed && !isPressed){
        onState = !onState;  
    }

    wasPressed = isPressed; 
    return onState; 
} // END turnOnButton


// Plays a note (not used in the piano method)
// 
void playTone(int freq, int durationMs) {
    if (freq <= 0) {
        ledcWriteTone(buzzerChannel, 0);
    } else {
        ledcWriteTone(buzzerChannel, freq);
    }
    delay(durationMs);
} // END playTone


// Plays two notes simultaneously (Not used in the piano method)
//
void playArpeggio(int freq1, int freq2, int totalDurationMs) {
    int slice = totalDurationMs / 4;

    for (int i = 0; i < 2; i++) {
        ledcWriteTone(buzzerChannel, freq1);
        delay(slice);
        ledcWriteTone(buzzerChannel, freq2);
        delay(slice);
    }

    ledcWriteTone(buzzerChannel, 0);
} // END playArpeggio

// Plays startup music
//
void startupMusic() {
    playArpeggio(131, 165, 500); 
    playTone(196, 500);          
    playTone(0,   500);       

    ledcWriteTone(buzzerChannel, 0);
} // END startupMusic


// plays shutdown music 
//
void shutdownMusic(){
    playArpeggio(131, 165, 500);   
    playTone(196, 500);           
    playTone(0,   500);            

    playArpeggio(165, 349, 500);   
    playArpeggio(262, 440, 500);   
    playTone(0,   500);    

    ledcWriteTone(buzzerChannel, 0);
} // END shudownMusic


