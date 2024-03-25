#include <lcom/lcf.h>
#include <stdint.h>

// LSB -> Less Significant Bits isto serve para preservar os 8 bits menos significativos, que são os que interessam 
int(util_get_LSB)(uint16_t val, uint8_t *lsb) {  //recebe como argumentos um valor de 16 bits e um apontador para um valor de 8 bits
  if (lsb == NULL) return 1; // o apontador deve ser válido
  *lsb = 0xFF & val;         // serve para preservar os 8 bits menos significativos, que são os que interessam 0xff = 11111111 e os restantes bits ficam a 0, ou seja 1111111100000000
  return 0;                   //os bits menos significativos servem para guardar a informação que queremos, isto quer dizer que os bits mais significativos são irrelevantes
}

// MSB -> Most Significant Bits
int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if (msb == NULL) return 1;
  *msb = val >> 8;            // serve para preservar os 8 bits mais significativos, que são os que interessam, val >> 8 faz com que os 8 bits mais significativos fiquem nos 8 bits menos significativos, ficamos com 0000000011111111
  return 0;
}

// Transform 32 bit output in 8 bit output. Error prevention.
int (util_sys_inb)(int port, uint8_t *value) {     //esta função serve para ler um byte de um porto de I/O, ou seja ler um byte de um dispositivo, de uma porta de I/O, uma porta é um endereço de memória que é usado para comunicar com um dispositivo
  if (value == NULL) return 1;    // o apontador deve ser válido
  uint32_t val;                   // variável auxiliar de 32 bits, serve para guardar o valor lido de port, mas 32 bits porque é o tamanho de um inteiro em C e é o que a função sys_inb() retorna
  int ret = sys_inb(port, &val);  // val ficará com o valor lido de port, ret é uma variável que guarda o valor de retorno da função sys_inb()
  *value = 0xFF & val;            // value ficará apenas com os primeiros 8 bits do resultado, e fezemos isto porque é o que nos interessa, os restantes bits são irrelevantes
  return ret;
}

//util sys inb serve para ler um byte de um porto de I/O, ou seja ler um byte de um dispositivo, de uma porta de I/O, uma porta é um endereço de memória que é usado para comunicar com um dispositivo
//recebe como argumentos um porto de I/O e um apontador para um valor de 8 bits, que serve para guardar o valor lido de port e retorna 0 se a leitura for bem sucedida e 1 caso contrário