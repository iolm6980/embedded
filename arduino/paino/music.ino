#define buzzerPin 8
int songLength = 50;

  char notes[] = "dgbD DCbab  gbDG GGFEF  aDFA GFeFG FeDCbCDCga";
  double beats[] = {
  1,1,1,2,0, //dgbD0
  1,1,1,1,3,0, //DCbab0
  1.5,0.5,0.5,0.5,2,0, //-gbDG0
  1,1,1,1,3,0, //GGFEF0
  1.5,0.5,0.5,0.5,2,0,// -aDFA0
  1,1,1,1,2,0, //GFeFG0
  1,2,1,1,1,1,1,1,1,3 //FeDCbCDCga
  };
double tempo = 400;

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  double duration;

  for(int i=0; i < songLength; i++){
    duration = beats[i] * tempo;
    if(notes[i] == ' '){
      delay(duration);
    }
    else{
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);
    }

   delay(tempo / 10);
  }
}

int frequency(char note){
  int i;
  int notes = 11;

  char names[] = {'d', 'g', 'b', 'D', 'C', 'a', 'G', 'F', 'E', 'A' ,'e'};
  int frequencies[] = {293, 391, 466, 587, 523, 440, 783, 698, 622, 880, 659};
  for(i=0; i < notes; i++){
    if(names[i] == note)
      return(frequencies[i]);
  }
  return(0);
}
