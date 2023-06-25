#define END_BASE_MEMO (int *) 0x0000
#define ACUMULADOR (int *) 0x5018
#define MEDIDOR_LEITURA (int *) 0x5014
#define MEDIDOR_ESCRITA (int *) 0x5010
int i, * ponteiro = END_BASE_MEMO, contador = 0;

int main()
{
  // 1223 ciclos
  *MEDIDOR_ESCRITA = 0;
  *MEDIDOR_ESCRITA = 1;
  for (i = 0; i < 10; i++)
  {
	  *ACUMULADOR = ponteiro[i];
  }
  *MEDIDOR_ESCRITA = 2;

  // 1323 ciclos
  *MEDIDOR_ESCRITA = 0;
  *MEDIDOR_ESCRITA = 1;
  for (i = 0; i < 10; i++)
  {
	  contador = contador + ponteiro[i];
  }
  *MEDIDOR_ESCRITA = 2;

  // 116.063 ciclos
  *MEDIDOR_ESCRITA = 0;
  *MEDIDOR_ESCRITA = 1;
  for (i = 0; i < 1000; i++)
  {
	  *ACUMULADOR = ponteiro[i];
  }
  *MEDIDOR_ESCRITA = 2;

  // 126.063 ciclos
  contador = 0;
  *MEDIDOR_ESCRITA = 0;
  *MEDIDOR_ESCRITA = 1;
  for (i = 0; i < 1000; i++)
  {
	  contador = contador + ponteiro[i];
  }
  *MEDIDOR_ESCRITA = 2;

  // 1.167.504 ou 23,35 ms
  *MEDIDOR_ESCRITA = 0;
  *MEDIDOR_ESCRITA = 1;
  for (i = 0; i < 10000; i++)
  {
	  *ACUMULADOR = ponteiro[i];
  }
  *MEDIDOR_ESCRITA = 2;

  // 1.267.504 ou 25,35 ms
  contador = 0;
  *MEDIDOR_ESCRITA = 0;
  *MEDIDOR_ESCRITA = 1;
  for (i = 0; i < 10000; i++)
  {
	  contador = contador + ponteiro[i];
  }
  *MEDIDOR_ESCRITA = 2;

  return 0;
}
