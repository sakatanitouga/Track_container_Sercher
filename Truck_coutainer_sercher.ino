#include <SD.h>
#include "BluetoothSerial.h"
#include <driver/adc.h>

#define PSD 2800
const uint8_t cs_SD = 5;
File fo;
BluetoothSerial SerialBT;

int i = 0;
int d=0;
const char* fname ="/test1.txt";
void setup() {
  adc2_config_channel_atten(ADC2_CHANNEL_4,ADC_ATTEN_DB_11);
  
  
  delay(1000);
  SerialBT.begin("ESP_32");  
  Serial.begin(115200);
  if(SD.begin(cs_SD,SPI,24000000,"/sd"))
    Serial.println("Open_SD");
  else
    Serial.println("Error_OPEN");  
  delay(1000);
  fo=SD.open(fname,FILE_WRITE);
  if(!fo){
    Serial.println("Error_write");  
  }else{
    for(i=0;i<10;i++){
      fo.print("This is test.\n");
      delay(1000);
      Serial.println(i,DEC);
    }  
  }
  fo.close();
}

void loop() {
  int psd =0;
  adc2_get_raw(ADC2_CHANNEL_4,ADC_WIDTH_BIT_12,&psd);
  // put your main code here, to run repeatedly:
  
  if(psd>PSD){
    Serial.printf("Close   psd_sencor%d.\r\n",psd);  
    SerialBT.printf("Close   psd_sencor:%d.\r\n",psd);
  }else{
    Serial.printf("Open   psd_sencor:%d.\r\n",psd);  
    SerialBT.printf("Open   psd_sencor:%d.\r\n",psd);
  }
  delay(500);
}
