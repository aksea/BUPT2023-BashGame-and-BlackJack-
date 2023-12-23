#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#define ARRAY_SIZE 6000
// 玩家和庄家点数
int playerPoints, dealerPoints;
// 玩家和庄家A数
int playerANum, dealerANum;
// 牌堆
int cardNum = 52;
int cardLibrary[10] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 16 };
// 计数
int win;  // 胜利次数
int lose; // 失败次数
// 随机数表
int RandNum[ARRAY_SIZE];
int RandNumPoint;
/**
 * @brief       将原点数计算成分数
 * @param       card      牌内容
 * @param       identity  身份
 * @return      int       分数
 */
int calculatePoints(char card[], int identity);

/**
 * @brief    判断是否要牌
 * @return   int
 */
int check(void);

/**
 * @brief    获取当前通过A可获取到的最大点数
 * @return 	 int
 */
int Aboost(int identity);

/**
 * @brief    随机生成一张牌
 */
void GenerateCard(char card[]);

int main()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		RandNum[i] = rand() % 13; // 生成 0 到 12 之间的随机数
	}
	int testNum = 1000;
	while (testNum--)
	{
		for (int i = 0; i < 10; i++)
		{
			if (i == 9)
				cardLibrary[i] = 16;
			else
				cardLibrary[i] = 4;
		}
		// 初始三张牌
		char card1[20], card2[20], dealerCard[20];
		// 停牌标志位
		int stand = 1;
		// 获取初始三张牌
		GenerateCard(card1);
		GenerateCard(card2);
		GenerateCard(dealerCard);
		// 计算初始时双方的点数
		playerPoints = calculatePoints(card1, 1) + calculatePoints(card2, 1);
		dealerPoints = calculatePoints(dealerCard, 0);
		if (check())
		{
			printf("Hit\n");
			fflush(stdout);
		}
		else
		{
			printf("Stand\n");
			fflush(stdout);
			stand = 0;
		}
		// 玩家阶段
		fflush(stdout);
		char newCard[20];
		while (1 && stand)
		{
			GenerateCard(newCard);
			playerPoints += calculatePoints(newCard, 1);
			// 如果爆牌则停止
			if (playerPoints > 21)
			{
				printf("Bust\n");
				fflush(stdout);
				break;
			}
			// 进行判断
			if (check())
			{
				printf("Hit\n");
				fflush(stdout);
			}
			else
			{
				printf("Stand\n");
				fflush(stdout);
				stand = 0;
			}
		}
		// 庄家阶段
		// 展示一张牌
		printf("dealertime\n");
		fflush(stdout);
		GenerateCard(newCard);
		dealerPoints += calculatePoints(newCard, 0);
		// 庄家后续行为
		while (1)
		{
			if (playerPoints > 21)
				break;
			dealerPoints = Aboost(0);
			if (dealerPoints >= 17)
				break;
			GenerateCard(newCard);
			dealerPoints += calculatePoints(newCard, 0);
		}
		// 判断时候有通过A加点数的可能
		playerPoints = Aboost(1);
		// 判断胜负
		if (playerPoints <= 21 && dealerPoints <= 21)
		{
			if (playerPoints > dealerPoints)
			{
				printf("Win\n");
				win++;
			}
			else if (playerPoints == dealerPoints)
			{
				printf("Push\n");
				win++;
				lose++;
			}
			else if (playerPoints < dealerPoints)
			{
				printf("Lose\n");
				lose++;
			}
		}
		else
		{
			if (playerPoints > 21)
			{
				printf("Lose\n");
				lose++;
			}
			else if (dealerPoints > 21)
			{
				printf("Win\n");
				win++;
			}
		}
		printf("%d %d\n\n", playerPoints, dealerPoints);
		printf("\n");
		fflush(stdout);
		Sleep(2);
	}
	float rate = 100 * (float)win / (win + lose);
	printf("胜场：%d 负场：%d 胜率：%.2f%%\n", win, lose, rate);
	printf("RandNumPoint:%d", RandNumPoint);
	return 0;
}

int calculatePoints(char card[], int identity)
{
	cardNum--;
	int pos = strlen(card) - 1;
	if (isdigit(card[pos]))
	{
		if (card[pos] == '0')
		{
			cardLibrary[9]--;
			return 10;
		}
		else
		{
			int result = card[pos] - '0';
			cardLibrary[result - 1]--;
			return result;
		}
	}
	else
	{
		if (card[pos] == 'A')
		{
			cardLibrary[0]--;
			if (identity == 1)
				playerANum++;
			else
				dealerANum++;
			return 1;
		}
		else
		{
			cardLibrary[9]--;
			return 10;
		}
	}
}

int check()
{
	if (Aboost(1) >= 20)
	{
		return 0;
	}
	if (playerPoints < 17)
	{
		return 1;
		if (playerPoints <= 11)
			return 1;
		else
		{
			if (dealerPoints < 6)
				return 0;
			else
				return 1;
		}
	}
	else
		return 0;
}

int Aboost(int identity)
{
	int tempPoints = 0;
	if (identity == 1)
	{
		tempPoints = playerPoints;
		for (int i = 0; i < playerANum; i++)
		{
			if (tempPoints + 10 <= 21)
				tempPoints += 10;
			else
				break;
		}
	}
	else
	{
		tempPoints = dealerPoints;
		for (int i = 0; i < dealerANum; i++)
		{
			if (tempPoints + 10 <= 21)
				tempPoints += 10;
			else
				break;
		}
	}
	return tempPoints;
}

void GenerateCard(char card[])
{
	int CardNum = RandNum[RandNumPoint++];
	while (1)
	{
		int temp = CardNum > 9 ? 9 : CardNum;
		if (cardLibrary[temp] != 0)
			break;
		else
			CardNum = RandNum[RandNumPoint++];
	}
	char Card[3] = { 0 };
	if (CardNum == 0)
	{
		Card[0] = 'A';
		Card[1] = '\0';
	}
	else if (CardNum < 9)
	{
		Card[0] = CardNum + 1 + '0';
		Card[1] = '\0';
	}
	else
	{
		Card[0] = '1';
		Card[1] = '0';
		Card[2] = '\0';
	}
	char Output[20] = "C ";
	Output[2] = Card[0];
	Output[3] = Card[1];
	Output[4] = Card[2];
	strcpy(card, Output);
	printf("%s\n", card);
}