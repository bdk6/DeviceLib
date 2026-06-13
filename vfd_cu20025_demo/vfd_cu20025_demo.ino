///////////////////////////////////////////////////////////////////////
///  VFD Itron CU20025 (BG Micro) demo
///  wrc Nov 19, 2020
///////////////////////////////////////////////////////////////////////

#define DATAPORT   PORTB

#define RS_PIN   12
#define E_PIN    13
#define RW_PIN    5     // Read /Write

#define RS_CMD    0
#define RS_DATA   1

#define CMD_CLEAR  0x01
#define CMD_HOME   0x02
#define dummy

void VFD_Command(uint8_t cmd)
{
  digitalWrite(RS_PIN, RS_CMD);
  uint8_t p = DATAPORT;
  p &= 0xf0;    // clear low bits
  p |= (cmd >> 4);  // set high bits of cmd
  DATAPORT = p;
  digitalWrite(E_PIN, HIGH);
  digitalWrite(E_PIN, LOW);
  // now low bits
  p = DATAPORT;
  p &= 0xf0;
  p |= (cmd & 0x0f);
  DATAPORT = p;
  digitalWrite(E_PIN, HIGH);
  digitalWrite(E_PIN, LOW);
  delay(1);
  
}

void VFD_Data(uint8_t dat)
{
  digitalWrite(RS_PIN, RS_DATA);
  uint8_t p = DATAPORT;
  p &= 0xf0;    // clear low bits
  p |= (dat >> 4);  // set high bits of cmd
  DATAPORT = p;
  digitalWrite(E_PIN, HIGH);
  digitalWrite(E_PIN, LOW);
  // now low bits
  p = DATAPORT;
  p &= 0xf0;
  p |= (dat & 0x0f);
  DATAPORT = p;
  digitalWrite(E_PIN, HIGH);
  digitalWrite(E_PIN, LOW);
  delay(1);
}

void VFD_Write(uint8_t dat, int cd = RS_DATA)
{
  digitalWrite(RS_PIN, cd);
  uint8_t p = DATAPORT;
  p &= 0xf0;    // clear low bits
  p |= (dat >> 4);  // set high bits of cmd
  DATAPORT = p;
  digitalWrite(E_PIN, HIGH);
  digitalWrite(E_PIN, LOW);
  // now low bits
  p = DATAPORT;
  p &= 0xf0;
  p |= (dat & 0x0f);
  DATAPORT = p;
  digitalWrite(E_PIN, HIGH);
  digitalWrite(E_PIN, LOW);
  delay(1);
}

void VFD_WriteCommand(uint8_t cmd)
{
  VFD_Write(cmd, RS_CMD);
}

void VFD_WriteData(uint8_t dat)
{
  VFD_Write(dat, RS_DATA);
}

void VFD_SetFourBitMode()
{
  uint8_t d = DATAPORT;
  d &= 0xf0;
  d |= 0x02;
  DATAPORT = d;
  digitalWrite(E_PIN, HIGH);
  delay(1);
  digitalWrite(E_PIN, LOW);
}

void setup() 
{
  pinMode(RW_PIN, OUTPUT);
  digitalWrite(RW_PIN, LOW);
  pinMode(RS_PIN, OUTPUT);
  digitalWrite(RS_PIN, LOW);
  pinMode(E_PIN, OUTPUT);
  digitalWrite(E_PIN, LOW);
  int ddr = DDRB;     // get current settings
  ddr |= 0x0f;        // set data pins as outputs
  DDRB = ddr;

  // Init display
  // Set 4 bit mode
  //VFD_Command(0x20);
//  uint8_t d = DATAPORT;
//  d &= 0xf0;
//  d |= 0x02;
//  DATAPORT = d;
//  digitalWrite(E_PIN, HIGH);
//  delay(1);
//  digitalWrite(E_PIN, LOW);
  VFD_SetFourBitMode();
  
  // Set brightness to 100%
  VFD_WriteData(0x02);

// clear display
  VFD_WriteCommand(0x01);
  delay(5);

 // VFD_Data('H');
 // VFD_Data('i');
  for(uint8_t c = 128; c < 148; c++)
  {
    VFD_WriteData(c);
  }
  
  
  

}

void loop() 
{
  // put your main code here, to run repeatedly:

}
