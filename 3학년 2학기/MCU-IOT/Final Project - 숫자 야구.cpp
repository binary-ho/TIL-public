#define F_CPU	16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include<stdlib.h>

/* 음별 주파수 */
#define D1	587		// 레
#define G1	784		// 솔
#define A1	880		// 라
#define D2	D1*2		
#define G2	G1*2	
#define A2	A1*2	
#define D3 D2*2
#define G3 G2*2

#define DLY_8	2
#define DLY_16	1
		
// display
const unsigned char Segment_Data[] =
{0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x6F};

//clock	
unsigned char count_int=0;

//piano
volatile unsigned char TIMERvalue=0xFF;
volatile int freq = 1000;

// piano
void Shimpyo(int time);
void Cutoff_Play(void);

// custom
int getRandomNum();
void setBall();

int getResult();

int inputNumber();
void resetTimer();
void ShowContent(int *content, int size);
void ShowNumber(int *content, int size);
int showResult(int strike, int ballCnt);
void play_bgm(volatile int *music, volatile int *music_length,int size);

int go[] = {0x3D, 0x3F, 0x53};
int RE2[] = {0x77, 0x79, 0x00, 0x00};
int RE3[] = {0x77, 0x79, 0x53};
int in[] = {0x30, 0x54, 0x3F, 0x4F};
int result[] = {0x6D, 0x3F, 0x7C, 0x3F};
int	userInput[] = {0x3F, 0x3F, 0x3F, 0x3F};
int winText[] = {0x3E, 0x3E, 0x30, 0x54};
int loseText[] = {0x38, 0x3F, 0x6D, 0x79};
int ball[3], inputNum, input, input_timer, timer_ms, timer, gameCnt, isWin;

/* STANDBY: 게임 대기, GAME: 게임중, IGNORE: 입력 무시 */
#define STANDBY 0
#define GAME 1
#define IGNORE 2
int mode = STANDBY;

/* TRUE, FALSE */
#define TRUE 1
#define FALSE 0

/* win과 lose bgm 재생을 위한 배열들 */
volatile int Win_sound[5] = {D3, D2, A2, D3, A2};
volatile int Lose_sound[4] = {G3, D3, G2, G2};
volatile int Win_length[5]={DLY_16,DLY_16,DLY_8,DLY_16,DLY_8};
volatile int Lose_length[4]={DLY_8,DLY_16,DLY_16,DLY_16};

/* 랜덤 숫자를 랜더링 하기 위한 타이머를 돌린다. 
TIMER0 오버플로우 인터럽트 발생시 count_int의 값을 1만큼 키운다.
이 count_int는 srand의 seed가 된다.*/
ISR(TIMER0_OVF_vect)
{
	count_int++;
	/* 숫자가 어느 정도 커지면 0으로 바꾼다. 100인 이유는 특별히 없다. 적당한 숫자 */
	if(count_int == 100) count_int = 0;
}

/* TIMER2 오버플로우 인터럽트 발생시 마다 TCNT2에 0xFF를 넣어주고, 스피커 포트 B를 toggle */
ISR(TIMER2_OVF_vect)
{
	TCNT2= TIMERvalue;
	PORTB ^= 0x10;	
}

ISR(INT0_vect)
{
	/*	standby 모드에서 0을 누르면 ignore 모드로 바꾸고, 다음 진행을 기다린다.
		game 모드에서 0을 누르면 input 숫자를 1만큼 줄이고 resetTimer를 호출. */
	if (mode == STANDBY) mode = IGNORE;
	else if (mode == GAME) {
		input--;
		if (input < 0) input = 9;
		resetTimer();
	}
}

ISR(INT1_vect)
{
	/*	standby 모드에서 1을 누르면 ignore 모드로 바꾸고, 다음 진행을 기다린다.
	game 모드에서 1을 누르면 input 숫자를 1만큼 늘리고 resetTimer를 호출. */
	if (mode == STANDBY) mode = IGNORE;
	else if (mode == GAME) {
		input = (input + 1) % 10;
		resetTimer();
	}
}

ISR(INT2_vect)
{
	/*	standby 모드에서 2을 누르면 ignore 모드로 바꾸고, 다음 진행을 기다린다.
	game 모드에서 2을 누르면 input 숫자를 2만큼 늘리고 resetTimer를 호출. */
	if (mode == STANDBY) mode = IGNORE;
	else if (mode == GAME) {
		input = (input + 2) % 10;
		resetTimer();
	}
}

int main(void)
{
	/* 자릿수 표시를 위한 DDRC 0xff: 4자리를 모두 사용
	Seven Segment를 위한 DDRA 0xff: A ~ G까지 모두 사용 */
	DDRC = 0xff;
	DDRA = 0xff;

	DDRB = 0x10;	/* 0001 0000 PB4를 스피커의 출력으로 지정 */

	/* timer/counter 0 */
	TCCR0 = 0x06;	/* 256분주 */
	/* TCNT0 = 0000 0000, 0 부터 시작하는 타이머 카운터 값 
	256에서 0번 타이머 인터럽트 발생 */
	TCNT0 = 0x00;	
	
	/* timer/counter 2 */
	TCCR2 = 0x04;	/* 64분주 */
	TCNT2 = 0x00;	
	
	/* Timer/Counter interrupt register TIMSK = 65 = 0100 0001
	TOIE0, TOIE2가 1로 설정됨 && SREG가 |= 1 이면, 
	Timer/Counter 0, 2의 오버플로우 인터럽트가 허용상태로 된다.*/
	TIMSK = 0x41;
	
	/* EICRA = 0x3F = 63 = 0011 1111 
	INT0, INT1, INT2 핀의 Rising 에지가 인터럽트를 비동기적으로 트리거함. */
	EICRA = 0x3F;
	
	/* EIMSK = 0000 0111 
	INT0, INT1, INT2 인터럽트를 허용한다고 설정 */
	EIMSK = 0x07;
	
	SREG |= 0x80; /* 글로벌 인터럽트 허용 */

	/* idx는 다용도 인덱스 변수이고, 
	isExist는 입력이 중복되는 경우를 체크하기 위한 변수
	isFirstGame은 첫 게임 여부를 확인하기 위한 변수 */
	int idx, isExist, isFirstGame = TRUE;
	while (1) 
	{
		/* 게임 대기 모드 */
		mode = STANDBY;
		while (1)
		{
			/*
			isFirstGame의 값에 따라 첫 게임에는 GO? 라는 글씨를 보여주고,
			두 번째 부터는 RE? 라는 글씨를 출력하게 한다.
			모든 출력은 ShowContent를 통해 이루어진다.
			0, 1, 2 중 아무 숫자나 누르면 시작한다. */
			if (isFirstGame == TRUE) ShowContent(go, 3);
			else ShowContent(RE3, 3);
			
			/* 계속 대기 상태에 있다가, 
			입력이 들어와서 STANDBY 상태가 깨지면 loop를 벗어난다 */
			if (mode != STANDBY) break;
		}
		
		/* isFirstGame를 FALSE로 만들어 주면서, 이후 부터는 대기 상황에서 re?를 보여주게 한다.
		isWin은 승리 여부를 표현하는 변수 */
		isFirstGame = isWin = FALSE;
		
		/* 게임 개시 9번의 기회가 주어진다. 
		setBall은 랜덤으로 중복 없는 숫자 3개를 선택한다. 
		그 3개의 숫자와 배치 순서가 답이 된다.*/
		gameCnt = 9;
		setBall();
		while (gameCnt--)
		{
			idx = 0;
			/* 
			답이 3자리 숫자이므로 숫자 3개의 입력을 받는다.
			userInput에 입력을 받는다. 겹치는 입력을 받게 되는 경우 isExist가 TRUE가 되면서
			해당 인덱스 입력을 다시 받게 하였다.
			*/
			while (idx < 3) 
			{
				isExist = FALSE;
				userInput[idx] = inputNumber();
				for (int i = 0; i < idx; i++) {
					if (userInput[i] == userInput[idx]) isExist = TRUE;
				}
				
				timer = 200;
				if (isExist == FALSE) {
					/* 겹치지 않은 입력인 경우, idx를 1 늘려주면서 입력을 받아들이고,
					ShowNumber 메서드를 통해 이제까지 입력한 숫자를 보여준다.	*/
					idx++;
					while (timer--) ShowNumber(userInput, idx);
				}
				else {
					/*	겹치는 입력인 경우 re?라는 글씨를 출력하고
						idx를 그대로 두면서 입력을 반려한다. */
					while (timer--) ShowContent(RE2, 4);
				}
			}
			/*	이번에 받은 입력이 정답인 경우, game 진행 loop를 탈출한다. */
			if (getResult() == TRUE) break;
		}
	}
}

/* 입력 값에 따라 딜레이가 발생 */
void Shimpyo(int time)
{
	for(int i=0;i<time;i++) _delay_ms(50);
}

/* 음악 정지 */
void Cutoff_Play(void)
{
	_delay_ms(300);
	TIMERvalue=255;
	_delay_ms(20);
}


/* Custom Methods */

/* setBall()
랜덤 넘버 3개를 만들어내는 메서드
보통의 난수 랜더링에는 시드 값으로 현재 시간이 들어가는 경우가 일반적이나,
mcu상에서는 제대로 작동하지 않는 것을 확인하였다. 
그래서 cnt_int라는 카운터를 사용하여 시드 값으로 이용했다.	*/
void setBall() {
	srand(count_int);
	int idx = 0, temp;
	int isExist;
	while (idx < 3) {
		isExist = FALSE;
		/* 일의 자리수 랜덤 숫자를 만드는 메서드	*/
		temp = getRandomNum();
		for (int i = 0; i < idx; i++) if (ball[i] == temp) isExist = TRUE;
		if (isExist == FALSE) {
			ball[idx] = temp;
			idx++;
		}
	}
}

/* getRandomNum()
난수를 생성한 다음, 10의 나머지를 반환한다. 
이렇게 하면 0 ~ 9의 랜덤 숫자가 생성된다. */
int getRandomNum() { 
	return rand() % 10; 
}

/* getResult()
유저 인풋으로 결과를 확인하는 메서드 
숫자 야구 규칙 그대로 숫자와 위치가 일치하면 strike, 
숫자만 같고 위치는 다르면 ball이다. */
int getResult() {
	int strikeCnt = 0, ballCnt = 0;
	for (int i = 0; i < 3; i++) {
		if (ball[i] == userInput[i]) strikeCnt++;
		for (int j = 0; j < 3; j++) {
			if (i == j) continue;
			if (userInput[i] == ball[j]) ballCnt++;
		}
	}
	return showResult(strikeCnt, ballCnt);
}

/* showResult(int strike, int ballCnt)
결과를 출력하는 메서드, */
int showResult(int strikeCnt, int ballCnt) {
	int T = 3;	/* 3번 보여준다. */
	
	/* 결과는 SXbY 형태로 strike 갯수 X와 ball 갯수 Y를 보여준다. */
	result[0] = 0x6D;	// S
	result[1] = Segment_Data[strikeCnt];
	result[2] = 0x7C;	// b
	result[3] = Segment_Data[ballCnt];
	
	/* strike가 3개인 경우 승리!! */
	if (strikeCnt == 3) isWin = TRUE;
	
	/* 승리한 경우 win_sound를 출력하고, 
	9회차가 모두 끝났는데도 실패한 상태인 경우 lose_sound를 재생한다. */
	if (isWin == TRUE) play_bgm(Win_sound, Win_length, 5);
	else if (gameCnt == 0) play_bgm(Lose_sound, Lose_length, 4);

	while (T--) {
		timer = 150;
		/*	승리한 경우 winText를 출력한다. 패배한 경우 loseText를 출력한다.
		그 외의 모든 경우엔 유저 인풋을 보여준다. */
		if (isWin == TRUE) while (timer--) ShowContent(winText, 4);
		else if (gameCnt > 0) while (timer--) ShowNumber(userInput, 3);
		else while (timer--) ShowContent(loseText, 4);
		
		timer = 150;
		/* 여기에서는 메서드 도입부에서 만든 SXbY 형태의 결과를 보여준다. */
		while (timer--) ShowContent(result, 4);
	}
	/* showResult 메서드를 종합하자면,
	1. 정답을 맞춘 경우: 승리 음악을 들려주고, 승리 문구 WIn과 게임 결과를 번갈아 3번 보여준다.
	3. 틀린 경우: 유저가 입력한 숫자 3개와 게임 결과를 번갈아 3번 보여준다. 
	3. 패배한 경우: 패배 음악을 들려주고, 패배 문구 LOSE와 게임 결과를 번갈아 3번 보여준다. 
	그다음 승리 여부를 return 한다. */
	return isWin;
}

/* ShowContent(int *content, int size)
원하는 텍스트를 보여주기 위한 메서드
헥스로 표현된 숫자 배열과, 배열 사이즈를 함께 넣으면 출력해준다. */
void ShowContent(int *content, int size)
{
	for(int i = 0 ; i < size ; i++)
	{
		PORTC = ~(0x01<<i);
		PORTA = content[i];
		_delay_ms(2);
	}
}

/* ShowNumber 
원하는 숫자를 보여주기 위한 메서드
정수로 표현된 숫자 배열과 사이즈를 넣어주면, 숫자들을 세그먼트에 출력하기 위한 hex 표현으로 바꾸어준다. */ 
void ShowNumber(int *content, int size)
{
	for(int i = 0 ; i < size ; i++)
	{
		PORTC = ~(0x01<<i);
		PORTA = Segment_Data[content[i]];
		_delay_ms(2);
	}
}

/* void resetTimer()
입력을 받을 때 3초의 제한시간이 주어지는데, 제한시간을 초기화 해주기 위한 메서드	*/
void resetTimer() {
	input_timer = 3;
	timer_ms = 0;
}

/* int inputNumber()
입력을 받는 메서드, 시작하면 모드를 GAME으로 바꿔준 다음 타이머를 초기화 한다.
그다음 in이라는 배열을 출력하는데 inXY로 구성 되어있다.
X는 0부터 시작하는 유저의 입력이고, Y는 입력을 위해 주어지는 3초짜리 타이머의 잔여 시간이다.
GAME 모드에서는 인터럽트 스위치 0, 1, 2를 통해 X를 변경할 수 있다.
0을 누르는 경우 input--, 1을 누르는 경우 += 1, 2를 누르는 경우 += 2이다. 
물론 9 보다 커지면 0으로, 0 보다 작아지면 9로 바뀐다.
모든 버튼이 눌릴 때마다 타이머는 다시 3초로 초기화 된다.
이 3초의 타이머가 끝나면, X는 input으로 확정된다.
그러니까, 인터럽트 스위치 0, 1, 2를 통해 입력하고 싶은 숫자를 표현하고 3초를 기다리면 원하는 숫자를 입력으로 넣어줄 수 있는 것이다. 
그 다음 입력을 막아주기 위해서 mode를 IGNORE로 변경해준다.	*/
int inputNumber() {
	input = 0;
	mode = GAME;
	resetTimer();
	while (0 < input_timer) {	/* 3초 후의 input 값이 배열에 입력되게 된다. */
		in[2] = Segment_Data[input];
		in[3] = Segment_Data[input_timer];
		ShowContent(in, 4);	/* 현재 숫자와 잔여 초를 보여주는 부분 */
		
		/* 시간을 재는 부분 */ 
		timer_ms++;
		if (timer_ms > 99) {
			input_timer--;
			timer_ms = 0;
		}
	}
	mode = IGNORE;
	return input;
}

/*	void play_bgm(volatile int *music, volatile int *music_length,int size)
계이름이 담긴 배열과 각 음의 길이를 담은 배열을 넣어주면 재생된다.
*/
void play_bgm(volatile int *music, volatile int *music_length,int size) {
	for(int i = 0; i < size; i++)
	{
		freq = music[i];
		TIMERvalue = 255-(1000000/(8*freq));
		Shimpyo(music_length[i]);
		Cutoff_Play();
	}
	_delay_ms(1000);
}
