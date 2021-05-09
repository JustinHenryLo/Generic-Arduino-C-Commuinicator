const int maxParams = 10;

class Communicator{
  private:
    String buffer;

  public:
    enum states {idle, processing, ready};
    states status = idle;
    String command;
    String* params = new String[maxParams];
    
  void listen(char input){
    this->status = processing;
    buffer += input;

    if(input == ';'){
      //instuctions are ; separated
      Serial.println("parsing start...");
      parseInstruction();
    }

    else if(input == '\n'){
      //instruction sets are ended with \n
      this->status = idle;
    }
  }

  void parseInstruction(){
    bool firstParam = true; //1st param is command
    int currentParam = 0;
    for (int i = 0; i < buffer.length() ; i++)
    {
      char curr = this->buffer[i];
      if(firstParam){
        if(curr == ','){
          firstParam = false;
        }
        else{
          this->command += curr;
        }
      }
      else{
        if(curr == ','){
          currentParam++;
        }
        else{
          this->params[currentParam] += curr;
        }
      }
     
    }
    this->buffer = "";
    this->status = ready;
  }

  void setStatus(states state){
    this->status = state;
    
    if(state == processing){
      this->command = "";
      this->buffer = "";
      for (int i = 0; i < maxParams; i++)
      {
        this->params[i] = "";
      }
    }
  }
};

void setup() {
  Serial.begin(9600);

}

Communicator comm;
void loop() {
  if(Serial.available()){
    comm.listen(Serial.read());
  }
  if(comm.status == comm.ready){
    Serial.println("command "+comm.command);
    Serial.println("param0 "+comm.params[0]);
    Serial.println("param1 "+comm.params[1]);
    Serial.println("param2 "+comm.params[2]);
    Serial.println("param3 "+comm.params[3]);
    Serial.println("param4 "+comm.params[4]);
    comm.setStatus(comm.processing);
  }

}
