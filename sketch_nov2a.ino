#define DATA_LEVEL LOW 
#define SPACE_LEVEL HIGH 
#define DASH_DURATION 3 
#define DOT_DURATION 1 
#define LETTER_DURATION 3	
#define WORD_DURATION 7	
#define TU 100 
#define DATA_PIN 9 

//#define SPACE false //красное 
//#define DATA true 
//long start_data, start_space; 
//long duration[20]; 
//bool color[20]; 
//int index = 0; 
//int previous = SPACE_LEVEL; 

String CODES[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int NLETTERS = 27;

void setup() { 
  pinMode(DATA_PIN, OUTPUT); 
  digitalWrite(DATA_PIN, SPACE_LEVEL); 
  Serial.begin(9600); 
} 

void loop() {  //считывает инф с монитору ищет и декодирует
//available() показывает сколько символов пришло 
  if(Serial.available() >= 1){ 
    Serial.println(code);
    char letter = Serial.read();
    if(letter == ' '){ //если пробел идем к сл слову
      send_word();
    }
    else{  //кодируем
      for(int iletter; iletter<NLETTERS; iletter++){ 
        if(letter == LETTERS[iletter]){ 
          String code = CODES[iletter]; 
          send_letter(code); 
        } 
      }
    }
  } 
} 

void send_letter(String code){  //смотрим что пришло то кодируем символы как на схеме
  int code_len = code.length(); 
  for(int i=0; i<code_len; i++){ 
    char symbol = code[i]; 
    if(symbol == '.'){ 
      digitalWrite(DATA_PIN, DATA_LEVEL); 
      delay(DOT_DURATION *TU); 
    } 
    else{ 
      digitalWrite(DATA_PIN, DATA_LEVEL); 
      delay(DASH_DURATION*TU); 
    } 
    digitalWrite(DATA_PIN, SPACE_LEVEL); 
    delay(TU); 
  } 
  delay((LETTER_DURATION - 1)* TU ); 
}

void send_word(){ //если пришел пробел начинает отпр сл слово
  digitalWrite(DATA_PIN, SPACE_LEVEL);
  delay((WORD_DURATION - LETTER_DURATION) * TU);
  Serial.print(" ");
}
