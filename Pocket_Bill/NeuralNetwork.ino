#define NEURONS 7
#define HIDEN_NEURONS 3
#define NUM_Output 7

float SampleValue[7][3], Output[7], preData;
const float training_data[7][3] = {{86,88,72},    //100
                                   {50,100,90},   //50
                                   {55,108,65},   //20
                                   {60,94,80},    //10
                                   {73,95,66},    //5
                                   {63,105,65},   //2
                                   {0,0,0},};     //1                                
void Neural_Network()
{

    for(int j=0; j<NEURONS; j++)
    {
        Output[j] = 0;
        for(int i=0; i<HIDEN_NEURONS; i++)
        {
          SampleValue[j][i] = (1-abs(color[i] - training_data[j][i]));
          Output[j] += SampleValue[j][i];
//          Serial.print(SampleValue[j][i]);
        }  
//        Serial.println();
    }

    preData = Output[0];
    for(int j=0; j<NUM_Output;j++)
    {if(preData < Output[j]){preData = Output[j]; Numb = j;}}
  
//    Serial.println("//////////////////////////////////////////////////////////");
//    Serial.print("Seratus Rubu Rupiah: ");Serial.println(Output[0]);
//    Serial.print("Lima Puluh Ribu Rupiah: ");Serial.println(Output[1]);
//    Serial.print("Dua Puluh Ribu Rupiah: ");Serial.println(Output[2]);
//    Serial.print("Sepuluh Ribu Rupiah: ");Serial.println(Output[3]);
//    Serial.print("Lima Ribu Rupiah: ");Serial.println(Output[4]);
//    Serial.print("Dua Ribu Rupiah: ");Serial.println(Output[5]);
//    Serial.print("Seribu Rupiah: ");Serial.println(Output[6]);
//    Serial.println("//////////////////////////////////////////////////////////");
//    Serial.println(preData);
//    Serial.println("//////////////////////////////////////////////////////////");
}
