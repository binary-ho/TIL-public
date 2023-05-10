#define F_CPU 16000000
#include <avr/io.h>

int main(void)
{
	unsigned char keyin = 0;
	// DDRG에 0x03을 넣어줍니다.
	// 이것은 DDR 레지스터 중에 G번을 input으로서 사용하겠다는 의미입니다.
	// 이런 대입을 통해 PORT중에서 G번을 input으로 이용할 수 있게 되는 것입니다.
	// D0 & D1: output, D2 & D3  input입니다.
	DDRG=0x03;	
	
	// 이번에는 C번 포트를 output으로 사용하기 위해, 
	// DDRC 레지스터를 output으로서 사용할 것임을 알려줍니다.
	DDRC=0x01; // D0: output

	while (1)
	{
		// keyin에 버튼의 예제와 같이 PING로 입력을 받아, 
		// 1100(0x0C)과 AND 연산을 수행한 다음 오른쪽으로 2만큼 shift해줍니다.
		// 이와 같은 과정을 통해 PIN G의 입력을 받을 수 있고, 해당 값을 PORTG에 넣어줍니다.
		PORTG = keyin = (PING&0x0C)>>2;
		
		// keyin값이 0이 아니라면, 즉 어떤 버튼이든 입력이 들어온다면, 
		// output으로 사용하기로 했던 PORTC에 0x01을 넣어 주고, 부저가 울리게 됩니다.
		if(keyin) PORTC = 0x01;
		else PORTC = 0x00;
		// else 조건은 버튼에서 손을 땠을 경우 그만 울리게 하기 위해서 존재합니다.
	}
}
