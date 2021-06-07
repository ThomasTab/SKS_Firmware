// Initializing data arrays
//------------------------------------------------------------------------------
// Pin/Switch matching
//-------------------------
//  [0]     [1]      [2]
//  [3]     [4]      [5]
//-------------------------
int tab_switch[6]={7,2,8,13,4,12};

// Pin/LED matching
//-------------------------
//  [0]     [1]      [2]
//  [3]     [4]      [5]
//-------------------------
int tab_led[6]={9,10,11,6,3,5};

// Default brightness for each LED (usefull if all LED aren't the same)
int brightness[6]={5,5,5,5,5,5};

// Value to send on serial port for each switch
int tab_keys[6]={1,2,3,4,5,6};

// Runtime arrays of the switchs states
int tab_switch_on[6]={0,0,0,0,0,0};
int tab_switch_on_back[6]={0,0,0,0,0,0};
//------------------------------------------------------------------------------

void setup()
{
  // Input and output pins initialization
  for (int i=0;i<6;i++)
  {
    pinMode(tab_switch[i],INPUT_PULLUP);
    pinMode(tab_led[i], OUTPUT);
  }
  
  // Initializing serial at 9600 bauds
  Serial.begin(9600); 
  while(!Serial);

  // LEDS autotest
  for (int i=0;i<256;i++)
  {
    for(int j=0;j<6;j++)
    {
      analogWrite(tab_led[j],i);
    }
    delay(5);
  }
  for(int i=0;i<6;i++)
  {
    analogWrite(tab_led[i],0);
  }
  
  analogWrite(tab_led[1],255);
  delay(250);
  analogWrite(tab_led[1],0);
  analogWrite(tab_led[0],127);
  analogWrite(tab_led[2],127);
  delay(250);
  analogWrite(tab_led[0],0);
  analogWrite(tab_led[2],0);
  analogWrite(tab_led[3],127);
  analogWrite(tab_led[5],127);
  delay(250);
  analogWrite(tab_led[3],0);
  analogWrite(tab_led[5],0);
  analogWrite(tab_led[4],127);
  delay(250);
  analogWrite(tab_led[4],0);

  for (int i=0;i<2;i++)
  {
    delay(250);
    for(int j=0;j<6;j++)
    {
      analogWrite(tab_led[j],127);
    }
    delay(250);
    for(int k=0;k<6;k++)
    {
      analogWrite(tab_led[k],0);
    }
  }
}

void loop()
{
  // Input pins pooling
  for (int i=0;i<6;i++)
  {
    if (digitalRead(tab_switch[i])==HIGH)
    {
      tab_switch_on[i]=1;
      analogWrite(tab_led[i],brightness[i]);
    }
    else
    {
      analogWrite(tab_led[i],0);
      tab_switch_on[i]=0;
    }
  }

  // Sending switch state to computer
  for (int i=0;i<6;i++)
  {
    // If switch was flipped
    if (tab_switch_on[i]!=tab_switch_on_back[i])
    {
      // If it is on send the configured value else send value+6
      if(tab_switch_on[i]==1){
        Serial.print(tab_keys[i]);
      } else {
        Serial.print(tab_keys[i]+6);
      }
    }
    tab_switch_on_back[i]=tab_switch_on[i];
  }
  
  // wait 10ms before next loop
  delay(10); 
}