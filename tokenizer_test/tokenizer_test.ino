void setup() {
  Serial.begin(9600);
  char str[] = "Geeks-for-Geeks";
 
    // Returns first token
    char* token = strtok(str, "-");
   
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL)
    {
        //Serial.print("%s\n");
        Serial.println(token);
        token = strtok(NULL, "-");
    }

}

void loop() {
  // put your main code here, to run repeatedly:

}
