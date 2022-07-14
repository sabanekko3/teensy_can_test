#include<stdint.h>

//#define ARDUINO_TEENSY41
#include<Arduino.h>
#include"..\lib\FlexCAN_T4-master\FlexCAN_T4.h"
void can_setup(void);
void can_tx(uint32_t id,uint8_t* tx_data);
void can_rx(const CAN_message_t &can_msg);

uint8_t can_rx_flag = 0;

FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> can3;

void setup(){
    Serial.begin(9600);
    can_setup();
}

void loop(){
    uint8_t can_tx_data[8]={0,1,2,3,4,5,6,7};
    can_tx(0x1<<5,can_tx_data);
    if(can_rx_flag){

    }
    //can3.events();
    delay(1000);
}

void can_setup(void){
    can3.begin();
    can3.setBaudRate(500000);
    can3.setMaxMB(16);
    can3.enableFIFO();
    can3.enableFIFOInterrupt();
    can3.onReceive(can_rx);
    can3.mailboxStatus();
    //CAN message config
}

void can_tx(uint32_t id,uint8_t* tx_data){
    static CAN_message_t can_msg;
    for(uint8_t i = 0; i < 8; i++){
        can_msg.buf[i] = *(tx_data + i);
    }
    can_msg.id = id;
    can3.write(can_msg);

    if(can_rx_flag){
        can_rx_flag = 0;
    }
    
    delay(1000);
}

void can_rx(const CAN_message_t &can_msg){
    can_rx_flag = 1;
    Serial.print("id:");
    Serial.println(can_msg.id);
    for(uint8_t i = 0; i< 8; i++){
        Serial.print(" data");
        Serial.print(i);
        Serial.print(":");
        Serial.print(can_msg.buf[i]);
    }
    Serial.println("");
    
    //can_read(msg);
}