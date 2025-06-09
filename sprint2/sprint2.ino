// sprint 1 kk

//Vinícius Soares Peroni
//Arthur Marques Santos
//Guilherme Bazon
//Flávio

// define os pinos dos leds que demonstram os personagens
const int ledMago = 2;
const int ledEscudeiro = 3;
const int ledCavaleiro = 4;

const int ledMonstro = 5;

byte led = 0;

//define a constante do pino onde botão está
const int botaoDados = 6;

//define a constante do pino onde a buzzer está
const int pinbuzzer = 7;

// Definindo as notas musicais
#define DO  262
#define DOs 277
#define RE  294
#define REs 311
#define MI  330
#define FA  349
#define FAs 370
#define SOL 392
#define SOLs 415
#define LA  440
#define LAs 466
#define SI  494

//string para comando, girar o dado
String restarto = "";

//Para utilizar o for 
byte i;

//Variável para escolha de monstros
byte monstro;
String monstros;

//Numero dado
byte rodado = 0;
byte rodadoM = 0;

//Variável para a escolha de personagem
String perso = "";

//Variável para a escolha do nome
String name = "";

// Variáveis status personagens
int atk = 0;
int hp = 0;
int hpT = 0;

// Variáveis status monstros
int atkM = 0;
int hpM = 0;

// Variáveis para quantidade de monstros mortos
byte monMortos = 0;

// Variáveis para dano
int danoP = 0;
int danoM = 0;

////Variáveis para controle de saída
//bool saidaSC = false;


void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(A0));

  // configura LEDs como saída
  pinMode(ledMago, OUTPUT);
  pinMode(ledEscudeiro, OUTPUT);
  pinMode(ledCavaleiro, OUTPUT);

  //configura a buzzer como saida
  pinMode(pinbuzzer, OUTPUT);

  // configura o botão como entrada
  pinMode(ledMonstro, INPUT);

  piscaLed();
  piscaLed();
  piscaLed();


  delay(1000);

  nome();
  escolha();
}

void loop() {
  endJogo();
}


void escolha(){
 Serial.println("Classes: Cavaleiro , Mago , Escudeiro");
 delay(2000);
 Serial.println("Status Cavaleiro: 10 atk e 750 hp");

 Serial.println("Status Mago: 15 atk e 500 hp");

 Serial.println("Status Escudeiro: 5 atk e 1000 hp");
 delay(5000);

 Serial.println("Qual classe voce deseja (Por favor escreva igual o nome da classe): ");

 while(Serial.available() == 0){
  //esperar até digitar
 }
 
 //Variável para controlar a quantidade de mensagens
 byte debugar = 0;

 while(true){
    perso = Serial.readString();
    perso.trim(); 
    perso.toUpperCase(); 

    if (perso == "CAVALEIRO"){
      Serial.println("Voce escolheu a classe Cavaleiro!! \n Seu status sao: 10 atk e 750 hp");
      atk = 10;
      hp = 750;
      hpT = 750;
      led = 4;
      break;
    }

    else if (perso == "MAGO"){
      Serial.println("Voce escolheu a classe Mago!! \n Seu status sao: 15 atk e 500 hp");
      atk = 15;
      hp = 500;
      hpT = 500;
      led = 2;
      break;
   
    }

    else if (perso == "ESCUDEIRO"){
      Serial.println("Voce escolheu a classe Escudeiro!! \n Seu status sao: 5 atk e 1000 hp");
      atk = 5;
      hp = 1000;
      hpT = 1000;
      led = 3;
      break;
      }

    else{
      if (debugar == 0){
        Serial.println("Classe inexistente, digite uma das acima!");
      }
      // perso = Serial.readString();
      // perso.trim(); 
      // perso.toUpperCase(); 
      debugar ++;
      continue;
 }
}
 digitalWrite(led, 1);
}

void nome(){

  Serial.println("Ola Bem Vindo! ao nosso RPG!!!");
  Serial.println("Qual é o seu nome?");

  while(Serial.available() == 0){
  //esperar até digitar
 }

  name = Serial.readString();

  Serial.println("");
  Serial.print("Ola, ");
  Serial.print(name);
  Serial.print(" !!");
  Serial.println("");
}


void sistema(){
    andando();
      escolhaMonstros();
      while (hpM > 0){
      dados();
      danoP = rodado * atk;
      hpM -= danoP;

      Serial.println("");
      Serial.println("O dano do player foi de:");
      Serial.print(danoP);
      Serial.println("");
      delay(1500);

      Serial.println("");
      Serial.println("A vida do monstro eh de:");
      Serial.print(hpM);
      Serial.println("");
      delay(1500);

      if (hpM < 0 || hpM == 0){
        break;
      }

      dadosMonstro();

      danoM = rodadoM * atkM;
      hp -= danoM;

      Serial.println("");
      Serial.println("O dano do monstro foi de: ");
      Serial.print(danoM);
      Serial.println("");
      delay(1500);

      Serial.println("");
      Serial.println("A sua vida eh de:");
      Serial.print(hp);
      Serial.println("");
      delay(1500);

      if (hp < 0 || hp == 0){
       Serial.println("GAME OVER");
       delay(1500);
       digitalWrite(led, 1);


       Serial.println("");
       Serial.println("");
       Serial.println(name);
       Serial.print("... Continue determinado");

       Serial.println("");
       Serial.println("");
       Serial.println("-Reinicie o arduino para tentar novamente-");
       
       while (true){
        //loop infinito
      }

      }


    }
    Serial.println("Voce derrotou o monstro !!");
    hp = hpT;
    
    digitalWrite(ledMonstro, 0);

    Serial.println("");
    Serial.println("");
    Serial.println("Sua vida foi totalmente restaurada!!");

  }

void endJogo(){
    while (monMortos!= 3){
      sistema();
      monMortos++;
    }
    boss();

    Serial.println("");

    Serial.println("Parabens!!");
    Serial.print(name);
    Serial.print("Voce zerou o jogo!!");

    musicaVitoria();

    Serial.println("");
    Serial.println("");
    Serial.println("Se quiser jogar novamente digite -RESTART-");
    restartar();
    //saidaSC = true;
    //if (saidaSC == true){
    monMortos = 0;
    //}

}


void restartar(){
  while(true){
    while(Serial.available() == 0){
      //esperar até digitar
    }

    restarto = Serial.readString();
    restarto.trim();
    restarto.toUpperCase();

    if (restarto == "RESTART"){
      break;
    }
  }//fim while true
}


void dados(){
  Serial.println("Pressione o botao ao lado do led vermelho para girar o dado: ");
  
  while(digitalRead(botaoDados) == 0){
   //espera até o botão ser presseionado
  }

  if(digitalRead(botaoDados) == 1){
    rodado = random(1, 21);

    Serial.println("");
    Serial.println("O numero que foi sorteado no dado foi: ");
    Serial.print(rodado);
    Serial.println("");
    delay(750);

    }
  }

// void dadosBruxa(){
//   Serial.print("Digite 'Girar' para girar o dado: ");
  
//   while(Serial.available() == 0){
   
//   }

//   String il = Serial.readString();
//   il.trim();
  
//   if(il == "Girar"){
//     randNumber = random(5, 21);

//     Serial.println("");
//     Serial.print("O numero que foi sorteado no dado foi: ");
//     Serial.println(randNumber);
//     delay(500);
//   }
//   else{
//     Serial.print("Comando não reconhecido");
//   }
// }


void dadosMonstro(){
  rodadoM = random(1, 16);

  Serial.println("");
  Serial.println("O numero que foi sorteado no dado do monstro foi: ");
  Serial.print(rodadoM);
  Serial.println("");
  delay(750);
}


void escolhaMonstros(){
  monstro = random(1, 4);

  if (monstro == 1){
    monstros = "Arvores";
    atkM = 5;
    hpM = 800;
  }
  else if (monstro == 2){
    monstros = "Zumbis";
    atkM = 10;
    hpM = 600;
  }
  else {
    monstros = "lobosFantasmas";
    atkM = 15;
    hpM = 400;
  }
  Serial.print("O monstro encontrado eh: ");
  Serial.println(monstros);
  digitalWrite(ledMonstro, 1);
}


void boss(){
  atkM = 15; 
  hpM = 800;

  digitalWrite(ledMonstro, 1);

  Serial.println("Voce encontrou um -BOSS-");
  delay(1500);

  Serial.println("Voce realmente acha que e forte o suficiente?");

  while (hpM > 0){
      dados();
      danoP = rodado * atk;
      hpM -= danoP;

      Serial.println("O dano do player foi de:");
      Serial.print(danoP);
      Serial.println("");
      delay(1500);

      Serial.println("A vida do BOSS eh de:");
      Serial.print(hpM);
      Serial.println("");
      delay(1500);

      if (hpM < 0 || hpM == 0){
        break;
      }

      dadosMonstro();

      danoM = rodadoM * atkM;
      hp -= danoM;

      Serial.println("O dano do BOSS foi de: ");
      Serial.print(danoM);
      Serial.println("");
      delay(1500);

      Serial.println("A sua vida eh de:");
      Serial.print(hp);
      Serial.println("");
      delay(1500);

      if (hp < 0 || hp == 0){
       Serial.println("GAME OVER");
       digitalWrite(led, 1);

       delay(1500);

       Serial.println("");
       Serial.println("");
       Serial.println("Resetar e sempre uma opcao... XD");
       Serial.println("");
       Serial.println("");
       Serial.println("-Reinicie o arduino para tentar novamente-");
       Serial.println("(Ou só fica aí refletindo suas escolhas)");

       while (true){
        //loop infinito
       }
    }
  }
    Serial.println("Voce derrotou o -BOSS- !!");
    hp = hpT;
    
    Serial.println("");
    Serial.println("Essa foi so a beta! A batalha oficial sera muito mais desafiadora!!");
    
    digitalWrite(ledMonstro, 0);
}


void piscaLed(){
  digitalWrite(ledMago, 1);
  digitalWrite(ledEscudeiro, 1);
  digitalWrite(ledCavaleiro, 1);
  delay(750);

  digitalWrite(ledMago, 0);
  digitalWrite(ledEscudeiro, 0);
  digitalWrite(ledCavaleiro, 0);
  delay(750);

}


void andando (){
  for(i = 1; i < 4; i++){
    Serial.println("Procurando monstros .");
    delay(300);

    Serial.println("Procurando monstros ..");
    delay(300);

    Serial.println("Procurando monstros ...");
    delay(250);
  }
}

void musicaVitoria(){
// Duração das notas
  int tempoNota = 300;
// Parte 1: Introdução Triunfante
  tone(pinbuzzer, DO, tempoNota);   // DO
  delay(tempoNota);
  tone(pinbuzzer, DO, tempoNota);   // DO
  delay(tempoNota);
  tone(pinbuzzer, RE, tempoNota);   // RE
  delay(tempoNota);
  tone(pinbuzzer, MI, tempoNota);   // MI
  delay(tempoNota);
  tone(pinbuzzer, DO, tempoNota);   // DO
  delay(tempoNota);
  tone(pinbuzzer, DO, tempoNota);   // DO
  delay(tempoNota);

// Parte 2: Explosão (crescendo)
  tone(pinbuzzer, SOL, tempoNota);  // SOL
  delay(tempoNota);
  tone(pinbuzzer, SOL, tempoNota);  // SOL
  delay(tempoNota);
  tone(pinbuzzer, SOL, tempoNota);  // SOL
  delay(tempoNota);
  tone(pinbuzzer, RE, tempoNota);   // RE
  delay(tempoNota);
  tone(pinbuzzer, MI, tempoNota);   // MI
  delay(tempoNota);
  tone(pinbuzzer, FA, tempoNota);   // FA
  delay(tempoNota);
  tone(pinbuzzer, SOL, tempoNota);  // SOL
  delay(tempoNota);
  
// Parte 3: Mais intensidade
  tone(pinbuzzer, LA, tempoNota);   // LA
  delay(tempoNota);
  tone(pinbuzzer, SI, tempoNota);   // SI
  delay(tempoNota);
  tone(pinbuzzer, LA, tempoNota);   // LA
  delay(tempoNota);
  tone(pinbuzzer, SOL, tempoNota);  // SOL
  delay(tempoNota);
  
// Parte 4: Final Explosivo
  tone(pinbuzzer, SOL, tempoNota);  // SOL
  delay(tempoNota);
  tone(pinbuzzer, SOL, tempoNota);  // SOL
  delay(tempoNota);
  tone(pinbuzzer, SOL, tempoNota);  // SOL
  delay(tempoNota);
  tone(pinbuzzer, RE, tempoNota);   // RE
  delay(tempoNota);

// Final com uma nota alta
  tone(pinbuzzer, LA, 500);          // LA (nota alta)
  delay(500);
  tone(pinbuzzer, DO, 500);          // DO (final)
  delay(500);

// Pausa antes de repetir
  delay(1000); // Pausa antes de repetir a música
}