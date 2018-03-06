#include<LiquidCrystal.h>

LiquidCrystal lcd(4,5,10,11,12,13);
int life=5; int allCoins=0;
int x,y;
//поле
int map1str[14]= {0,1,0,0,0,1,0,0,0,0,1,0,0};
int map2str[14]={0,0,0,1,0,0,0,1,0,0,0,0,0};
//кнопки
int btnPinL=6;
int butLstat=0;
int btnPinR=7;
int butRstat=0;
int btnPinU=8;
int butUstat=0;
int btnPinD=9;
int butDstat=0;
//символы
byte man[8] = {
  B01110,
  B01011,
  B01110,
  B00100,
  B11111,
  B00100,
  B11011,
};
byte kust[8] = {
  B00000,
  B00000,
  B00000,
  B01110,
  B11011,
  B10101,
  B01010,
};
byte derevo[8] = {
  B01110,
  B10101,
  B11011,
  B10101,
  B01110,
  B00100,
  B01100,
};
byte coin[8] = {
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
  B00000,
};
byte enemy[9] = {
  B01010,
  B01010,
  B10101,
  B01110,
  B01010,
  B10101,
  B00100,
  B01010,
};

void setup() {
  x=8; y=2;
  pinMode(btnPinL,INPUT);

  
  lcd.begin(16,2);  
  lcd.clear();
  lcd.createChar(0, man);
  lcd.createChar(1,kust);
  lcd.createChar(2,derevo);
  lcd.createChar(3,coin);
  lcd.createChar(4,enemy);
int i;
 for(i=0;i<13;i++){
    int r=random(0,10);
    switch(r){
      case 1: map1str[i]=1; break;
      case 2: map1str[i]=2; break;
      case 4: map1str[i]=4;break;

    }
    
    r=random(0,10);
    switch(r){
      case 1: map2str[i]=1; break;
      case 2: map2str[i]=2; break;
      case 4: map2str[i]=4;break;

    }
  }
  
  mapOtris();
}

void loop() {
  butLstat=digitalRead(btnPinL);
  butRstat=digitalRead(btnPinR);
  butUstat=digitalRead(btnPinU);
  butDstat=digitalRead(btnPinD);
  if(butLstat==HIGH&&x!=0){
    
    move(-1,0);
  }
  if(butRstat==HIGH&&x!=13) { 
    move(1,0);
   }
  if(butUstat==HIGH&&y!=0) { 
    move(0,-1);
   }
   if(butDstat==HIGH&&y!=1) { 
    move(0,1);
   }
   
}


void getCoin(){
  int i;
  for(i=0;i<13;i++){
    if(map1str[i]==3&&x==i&&y==0){
      map1str[i]=0;
      life++;
      
      delay(500);
    }
  }

}

void mapOtris(){

  choosePredm(1);
  choosePredm(2);
  choosePredm(3);
  choosePredm(4);
  lcd.setCursor(15,0);
  lcd.print(life);
  int r=random(0,13);
  map1str[r]=4;
 
  if(life+allCoins<10){
  r=random(0,13);
  map1str[r]=3;
  
  allCoins++;
  }
 
  lcd.setCursor(x,y);
  lcd.write(byte(0));
}
void choosePredm(int numb){
  int i=0;
  for(i=0;i<13;i++){
    if(map1str[i]==numb){
      lcd.setCursor(i,0);
      lcd.write(byte(numb));
    }
  }
  for(i=0;i<13;i++){
    if(map2str[i]==numb){
      lcd.setCursor(i,1);
      lcd.write(byte(numb));
    }
  }
  
}

void move(int X,int Y){
    lcd.clear();
    x+=X;
    y+=Y;
    if(life<9){
      getCoin();
    }
    
    enMove();
    mapOtris();
    delay(500);
}

void enMove(){
  int i=0;
  for(i=0;i<13;i++){
    

    
    if(map1str[i]==4){
    if(i==x&&y==0){
      life--;
      break;    
    }
      if(i<x){
         map1str[i+1]=4;
         map1str[i]=0;
         break;
         //delay(500);
      }else if(i>x){
        map1str[i-1]=4;
         map1str[i]=0;
         break;
         //delay(500);
      }
    }
  }

}

