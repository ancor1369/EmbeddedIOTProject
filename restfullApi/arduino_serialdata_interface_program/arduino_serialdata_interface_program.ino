int x=0;
void setup() {
  /*Inicializa a comunicao serial a uma 
  taxa de 9600 baunds por segundo*/
  Serial.begin(9600);
}

void loop() {
  /*Serial.print("Contando: ");   //Imprime a palavra "Contando"
  Serial.print(x);              //Imprime o valor da variavel x
  Serial.println(" segundos."); //Imprime a palavra " segundos."*/
  Serial.println("Contando: "+(String)x+" segundos.");
  delay(1000);                  //Espera 1 segundo
  x++;                          //Soma x+1
}
