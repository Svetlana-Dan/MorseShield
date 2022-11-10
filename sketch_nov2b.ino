 

void loop() {
  // put your main code here, to run repeatedly:
  fill_arrays();
  decode();
  
}

void decode_letter(){ 
  for(int i=0; i < index; i++){ 
    if (duration[i] == DASH_DURATION and color[i] == SPACE){ 
      String code = ""; 
      for (int j=0; j < i; j++){ 
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
        if (code == CODES[iletter]){ 
          Serial.println(LETTERS[iletter]); 
        } 
      } 
    } 
  } 
}


void fill_arrays(){ 
  int current = digitalRead(DATA_PIN); 
  if (current == DATA_LEVEL and previous == SPACE_LEVEL){ 
    start_data = millis(); 
    duration[index] = int((millis() - start_space + 0.5 * TU) / TU); 
    color[index] = SPACE; 
    index++; 
  } 
  if (current == SPACE_LEVEL and previous == DATA_LEVEL){ 
    start_space = millis(); 
    duration[index] = int((millis() - start_data + 0.5 * TU) / TU); 
    color[index] = DATA; 
    index++; 
  } 
  previous = current; 
} 