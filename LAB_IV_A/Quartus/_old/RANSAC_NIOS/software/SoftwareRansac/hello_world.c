#define END_BASE_MEMO (int *) 0x0000
#define SENDER_READ (int *) 0x3100c
#define SENDER_WRITE (int *) 0x31008
#define RECEIVER_READ (int *) 0x31010
#define PARALLEL_PORT_BASE (int *) 0x31000
//#define SENDER_PIO (int *) 0x31000
//#define RECEIVER_PIO (int *) 0x31010

int i, * ponteiro = END_BASE_MEMO;
int a, b, c;
int main()
{
  a = 1;
  b = 3;
  c = 4;

  while(1){

	  *SENDER_READ = *PARALLEL_PORT_BASE;
	  *SENDER_READ = b;

  }

  return 0;
}
