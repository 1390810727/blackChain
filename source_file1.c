/*
ʶ��ؼ��ʵĸ���ΪSUM��
nΪ�����ж�Ӧ�ؼ��ʵ����кţ���������sRecog�еĵ�һ���ؼ���Ϊ��kai deng�����Ӧ�����к�Ϊ0��
Voice.Initialise();��ʼ���������뷽ʽMIC/MONO��
*/
#include <TimerOne.h>
#include <avr/wdt.h>
#include <Voice.h>
#include <Syn6288.h>
#include <DHT.h>

#define DHTTYPE DHT11   // DHT 11 

Syn6288 syn;
uint8  nAsrStatus=0;
#define SUM 11

#define DHT11_PIN 6          //DHT11�����������ֿ�6
#define light_sensor_pin A2  //���ߴ�������ģ���2
#define light_threshold 200  //���ߴ�������ֵ
/*#define gas_sensor_pin A1    //���崫������ģ���1
#define gas_threshold 700*/    //���崫����������ֵ
#define relay 8              //�̵��������ֿ�8
#define state_led 7          //״ָ̬ʾ�Ʋ����ֿ�7

DHT dht(DHT11_PIN, DHTTYPE);

char sRecog[SUM][30] = {"xiao jian guo","xian zai wen du zen me yang","kai deng","guan deng","xu yao kai deng ma","xiao jian","xiao","jian guo","wen du","kai","guan"};
//С����������¶���ô�������ƣ��صƣ���Ҫ������

uint8_t text1[]={0xC1,0xE3,0xD2,0xBB,0xB6,0xFE,0xC8,0xFD,0xCB,0xC4,0xCE,0xE5,0xC1,0xF9,0xC6,0xDF,0xB0,0xCB,0xBE,0xC5,0xCA,0xAE};//��һ�����������߰˾�ʮ
uint8_t text2[]={0xC4,0xFA,0xBA,0xC3};// ����
uint8_t text3[]={0xB5,0xB1,0xC7,0xB0,0xCE,0xC2,0xB6,0xC8,0xCE,0xAA};//��ǰ�¶�Ϊ
/*uint8_t text4[]={0xCA,0xAA,0xB6,0xC8,0xCE,0xAA,0xB0,0xD9,0xB7,0xD6,0xD6,0xAE};//ʪ��Ϊ�ٷ�֮
uint8_t text5[]={0xC9,0xE3,0xCA,0xCF,0xB6,0xC8};//���϶�
uint8_t text6[]="soundn";//������
uint8_t text7[]={0xC7,0xEB,0xD7,0xA2,0xD2,0xE2,0xA3,0xAC,0xD3,0xD0,0xCE,0xA3,0xCF,0xD5,0xC6,0xF8,0xCC,0xE5,0xD0,0xB9,0xC2,0xA9};//��ע�⣬��Σ������й©*/
uint8_t text8[]={0xD5,0xFD,0xD4,0xDA,0xBF,0xAA,0xB5,0xC6};//���ڿ���
uint8_t text9[]={0xD5,0xFD,0xD4,0xDA,0xB9,0xD8,0xB5,0xC6};//���ڹص�
uint8_t text10[]={0xC7,0xEB,0xCE,0xCA,0xC4,0xE3,0xD4,0xDA,0xCB,0xB5,0xCA,0xB2,0xC3,0xB4,0xA3,0xBF};//��������˵ʲô��
uint8_t text11[]={0xB9,0xE2,0xCF,0xDF,0xB2,0xBB,0xD7,0xE3,0x20,0xA3,0xAC,0xD5,0xFD,0xD4,0xDA,0xBF,0xAA,0xB5,0xC6};//���߲��㣬���ڿ���
uint8_t text12[]={0xCF,0xD6,0xD4,0xDA,0xB9,0xE2,0xCF,0xDF,0xC3,0xF7,0xC1,0xC1,0xA3,0xAC,0xB2,0xBB,0xD0,0xE8,0xD2,0xAA,0xBF,0xAA,0xB5,0xC6};//��������������Ҫ����

uint8_t text[2];
uint8_t flag;  //��־λ���յ�С����������Ϊ1������ִ���������

void finally(uint8_t n) //nΪsRecog�����ж�Ӧ�ؼ��ʵ����к�
{
  switch(n)
  {
        case 0: syn.play(text2,sizeof(text2),0);flag=1;break; // ����
  /*  case 1:       //�����¶���ô��
             if(flag==1)  //�յ�С����ĳ��������
             {
          flag=0;
          uint8_t h = dht.readHumidity();
                                  uint8_t t = dht.readTemperature();  //��ȡ�¶�
          /*Serial.print("Temperature:");
          Serial.print(DHT.temperature);
          Serial.print("   humidity:");
          Serial.println(DHT.humidity);
          uint8_t pig1 = t/10;  //�¶���ֵʮλ
          uint8_t pig2 = t%10;  //�¶���ֵ��λ
          uint8_t pig3 = h/10;    //ʪ����ֵʮλ
          uint8_t pig4 = h%10;    //ʪ����ֵ��λ
          syn.play(text3,sizeof(text3),0);  //��ǰ�¶�Ϊ    
          if(pig1>0){
          text[0]=text1[pig1*2];
          text[1]=text1[pig1*2+1];
          syn.play(text,sizeof(text),0);    //�����¶���ֵʮλ
          text[0]=text1[20];
          text[1]=text1[21];
          syn.play(text,sizeof(text),0);    //��������ʮ
          }
          if(pig2>0){
          text[0]=text1[pig2*2];
          text[1]=text1[pig2*2+1];
          syn.play(text,sizeof(text),0);    //�����¶���ֵ��λ  
          }         
          syn.play(text5,sizeof(text5),0);  //�������϶�
          syn.play(text4,sizeof(text4),0);  //����ʪ��Ϊ�ٷ�֮
          
          if(pig3>0){
          text[0]=text1[pig3*2];
          text[1]=text1[pig3*2+1];
          syn.play(text,sizeof(text),0);  //����ʪ����ֵʮλ
          text[0]=text1[20];
          text[1]=text1[21];
          syn.play(text,sizeof(text),0); //��������ʮ
          }
          if(pig4>0){
          text[0]=text1[pig4*2];
          text[1]=text1[pig4*2+1];
          syn.play(text,sizeof(text),0);  //����ʪ����ֵ��λ  
          }         
             }
      break;*/
    case 2: //����
             if(flag==1)
             {
               syn.play(text8,sizeof(text8),0); //�������ڿ���
               digitalWrite(relay,HIGH);  //�ߵ�ƽ����
               flag=0;  
             }
      break;  
        case 3: //�ص�
       if(flag==1)
       {
        syn.play(text9,sizeof(text9),0); //�������ڹص�
        digitalWrite(relay,LOW);
        flag=0;
      }
      break;
        case 4: //��Ҫ������
      if(flag==1)
       {
        int shine=analogRead(light_sensor_pin); //��ȡ���ն�ģ����
        //Serial.print("Light:");
        //Serial.println(shine);
        if(shine < light_threshold) //С�ڹ��նȷ�ֵʱ
        {
          syn.play(text11,sizeof(text11),0); //���߲��㣬���ڿ���
          digitalWrite(relay,HIGH);
        }
        else 
        {
          syn.play(text12,sizeof(text12),0); //��������������Ҫ����
          digitalWrite(relay,LOW);
        }
        flag=0;
       }
            break;
    default:syn.play(text10,sizeof(text10),0);break;  //�����������������˵ʲô     
  }
}

void ExtInt0Handler ()
{
  Voice.ProcessInt0();  //оƬ�ͳ��ж��ź�
        
}
void timerIsr()
{
  wdt_reset();
}
void setup()
{
  Serial.begin(9600);
  Voice.Initialise(MIC,VoiceRecognitionV1);//Initialise mode MIC or MONO,default is MIC
                                           //VoiceRecognitionV1 is VoiceRecognitionV1.0 shield
                                           //VoiceRecognitionV2 is VoiceRecognitionV2.1 module  
  attachInterrupt(0,ExtInt0Handler,LOW);
 
  pinMode(relay,OUTPUT);
  digitalWrite(relay,LOW);
  pinMode(state_led,OUTPUT);
  digitalWrite(state_led,LOW);
  Timer1.initialize(90000);
  Timer1.attachInterrupt(timerIsr); // attach the service routine here
  wdt_enable(WDTO_120MS);
}
void loop()
{  
    static uint8_t nAsrRes=0;
    static unsigned long time = millis();
  if(millis()-time>100)
  {  
      /* int gas=analogRead(gas_sensor_pin);
       if(gas > gas_threshold)
       {
      syn.play(text6,sizeof(text6),0);
      syn.play(text7,sizeof(text7),0);
       }*/
    switch(nAsrStatus)
    {
      case LD_ASR_RUNING:
      case LD_ASR_ERROR:break;
      case LD_ASR_NONE:
      {
        nAsrStatus=LD_ASR_RUNING;
                if (Voice.RunASR(SUM,30,sRecog)==0) //ʶ����ȷ
        {
          nAsrStatus= LD_ASR_ERROR;
                    Serial.println( "ASR_ERROR"); 
        }

                Serial.println( "ASR_RUNING.....");
        digitalWrite(state_led,HIGH);
        break;
      }
      case LD_ASR_FOUNDOK:
      {
        digitalWrite(state_led,LOW);
        nAsrRes =Voice. LD_GetResult();// һ��ASRʶ�����̽�����ȥȡASRʶ����            
                finally(nAsrRes);
        nAsrStatus = LD_ASR_NONE;
        break;
      }
      case LD_ASR_FOUNDZERO:
      default:
      { 
        digitalWrite(state_led,LOW);
        nAsrStatus = LD_ASR_NONE;
        break;
      }
      }// switch

  }//if
}
