#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
// 玩家和庄家点数
int playerPoints, dealerPoints;
// 玩家和庄家A数
int playerANum, dealerANum;
// 牌堆
int cardNum = 52;
int cardLibrary[10] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 16 };
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

int main()
{
	// 初始三张牌
	char card1[20], card2[20], dealerCard[20];
	// 停牌标志位
	int stand = 1;
	// 获取初始三张牌
	gets(card1);
	gets(card2);
	gets(dealerCard);
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
	char newCard[20];
	while (1 && stand)
	{
		gets(newCard);
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
	gets(newCard);
	dealerPoints += calculatePoints(newCard, 0);
	// 庄家后续行为
	while (1)
	{
		char action[20];
		// 庄家的行动
		gets(action);
		if (strcmp(action, "Stand") == 0)
			break;
		gets(newCard);
		dealerPoints += calculatePoints(newCard, 0);
	}
	// 判断时候有通过A加点数的可能
	playerPoints = Aboost(1);
	dealerPoints = Aboost(0);
	// 判断胜负
	if (playerPoints <= 21 && dealerPoints <= 21)
	{
		if (playerPoints > dealerPoints)
			printf("Win\n");
		else if (playerPoints == dealerPoints)
			printf("Push\n");
		else if (playerPoints < dealerPoints)
			printf("Lose\n");
	}
	else
	{
		if (playerPoints > 21)
			printf("Lose\n");
		else if (dealerPoints > 21)
			printf("Win\n");
	}
	printf("%d %d\n", playerPoints, dealerPoints);
	fflush(stdout);
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