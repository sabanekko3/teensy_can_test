#include<stdint.h>

//#define ARDUINO_TEENSY41
#include<Arduino.h>
#include"..\lib\FlexCAN_T4-master\FlexCAN_T4.h"
void can_setup(void);
void can_tx(uint32_t id,uint8_t* tx_data);
void can_rx();
void canSniff(const CAN_message_t &msg);

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16>*my_can1 = new FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16>();

void setup(){
    can_setup();
}

void loop(){
    uint8_t can_tx_data[8]={0,1,2,3,4,5,6,7};
    can_tx(0x1,can_tx_data);
    delay(1000);
}

void can_setup(void){
    my_can1->begin();
    my_can1->setBaudRate(1000000);
    my_can1->setMaxMB(16);
    my_can1->enableFIFO();
    my_can1->enableFIFOInterrupt();
    my_can1->onReceive(MB0, canSniff);
    my_can1->mailboxStatus();
    //CAN message config
}

void can_tx(uint32_t id,uint8_t* tx_data){
    static CAN_message_t* can_msg;
    for(uint8_t i = 0; i < 8; i++){
        can_msg->buf[i] = *(tx_data + i);
    }
    can_msg->id = id;
    my_can1->write(*can_msg);
}

void canSniff(const CAN_message_t &msg){

}