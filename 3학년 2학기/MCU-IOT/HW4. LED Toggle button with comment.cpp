#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRG = 0x03;
	// 처음엔 두 LED 모두 불이 들어오지 않습니다.
	PORTG = 0x00;
	unsigned char keyin = 0;

	while (1)
	{
		// 0x0C은 이진수로 나타내면 1100(2)이다.
		// 이 1100과 PING를 AND 연산을 하여, 버튼의 입력을 받는 상위 두 bit을 남깁니다.
		// 이후 shift연산을 하여 자릿수를 이동시킵니다. (사용의 편의를 위하여)
		// 이 값을 keyin에 대입해줍니다. keyin을 통해 버튼을 눌렀는지, 어떤 버튼이 눌렸는지 확인 가능합니다.
		keyin = (PING&0x0C)>>2;

		// keyin이 0이 아닌 경우 -> 아무 버튼이나 눌린 경우
		if (keyin != 0) {

			// PORTG 값을 늘려줍니다. 각 PORTG 값은 아래와 같은 의미를 갖습니다.
			// PORTG가 0x00: 모든 LED 꺼짐
			// PORTG가 0x01: LED0 켜짐
			// PORTG가 0x02: LED1 켜짐
			// PORTG가 0x03: LED0, 1 켜짐
			// 따라서, PORTG 값을 1 늘려주는 것은 PORTG값이 0x03이 아닐 때엔,
			// 명세에서 요구하는 대로 LED를 켜지고 꺼지게 합니다.
			PORTG++;

			// 단, 0x03에서 0x04로 증가하면, 명세에 따라 PORTG 값을 0x01로 바꾸어 줌으로써 LED0에 불이 들어오게 합니다.
			if (PORTG > 0x03) PORTG = 0x01;

			// 버튼의 입력이 있을 때, 딜레이를 넣어줘야 합니다.
			// 딜레이가 없는 경우 인간의 인지보다 빠르게 동작하여, 마치 의도대로 동작하지 않는 것처럼 보이게 됩니다.
			_delay_ms(500);
		}
	}
}
