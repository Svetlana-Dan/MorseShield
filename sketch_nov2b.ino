#define DATA_PIN 2
#define DATA_LEVEL LOW
#define SPACE_LEVEL HIGH
#define SPACE false //красное
#define DATA true
#define DASH_DURATION 3
#define DOT_DURATION 1
#define LETTER_DURATION 3	
#define WORD_DURATION 7	
#define TU 100

long start_data, start_space;
long duration[20];
bool color[20];
long duration_space[20]; //добавлено
int index = 0;
int previous = SPACE_LEVEL;
String CODES[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
// String CODES[] = {".-", "--.."};
// char LETTERS[] = {'A', 'Z'};
int NLETTERS = 26; 
bool isEndWord = false;
String message = "";

void loop() {
  // put your main code here, to run repeatedly:
  fill_arrays();
  decode();
  
}

void decode_letter(){ //обратно декодируем буквы
  bool isEditing = false;
  for(int i=0; i < index; i++){ //считываем
    if (duration[i] == DASH_DURATION and color[i] == SPACE){ //если была пауза после букв
      String code = ""; 
      for (int j=0; j < i; j++){ //сбор кода буквы
          if (duration[j] == DASH_DURATION and color[j] == DATA){ 
            code += '-'; 
          } 
          if (duration[j] == DOT_DURATION and color[j] == DATA){ 
            code += '.'; 
          } 
          duration[j] = 0; 
      } 
      duration[i] = 0; 
      for (int iletter=0; iletter < NLETTRERS; iletter++){ 
        if (code == CODES[iletter]){ //соотносим код с буквой
          isEditing = true;
          message += LETTERS[iletter];
          Serial.print(message);
        } 
      } 
    } 
    if (isEditing && isEndWord)	// Если мы доставали все буквы
    {
      Serial.print("\n");	// Конец передачи
      index = 0;	// Сброс 
      isEndWord = false;	
    }
  }
  if (isEditing)
  {
  	index = 0;
    message = "";
  } 
}


void fill_arrays(){  //чтобы буквы приходили полностью, проверяет начались или закончились данные
  int current = digitalRead(DATA_PIN); 
  if (current == DATA_LEVEL and previous == SPACE_LEVEL){ 
    start_data = millis(); 
    duration[index] = int((millis() - start_space + 0.5 * TU) / TU); 
    color[index] = SPACE; //красные(расстояние)
    index++; 
  } 
  else if (current == SPACE_LEVEL and previous == DATA_LEVEL){ 
    isEndWord = false;
    start_space = millis(); 
    duration[index] = int((millis() - start_data + 0.5 * TU) / TU); 
    color[index] = DATA;  (синие(точки-тире))
    index++; 
  } 
  else if (isEndWord == false && current == SPACE_LEVEL && previous == SPACE_LEVEL){
    long temp = millis() - start_space;	
    if (temp > TU * WORD_DURATION)	
    {
    	isEndWord = true;
    	duration[index] = WORD_DURATION;
      	index++;	
  	}
  }
  previous = current; 
} 
