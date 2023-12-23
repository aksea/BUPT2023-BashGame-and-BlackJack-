#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#define ARRAY_SIZE 6000
// ��Һ�ׯ�ҵ���
int playerPoints, dealerPoints;
// ��Һ�ׯ��A��
int playerANum, dealerANum;
// �ƶ�
int cardNum = 52;
int cardLibrary[10] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 16 };
// ����
int win;  // ʤ������
int lose; // ʧ�ܴ���
// �������
int RandNum[ARRAY_SIZE];
int RandNumPoint;
/**
 * @brief       ��ԭ��������ɷ���
 * @param       card      ������
 * @param       identity  ���
 * @return      int       ����
 */
int calculatePoints(char card[], int identity);

/**
 * @brief    �ж��Ƿ�Ҫ��
 * @return   int
 */
int check(void);

/**
 * @brief    ��ȡ��ǰͨ��A�ɻ�ȡ����������
 * @return 	 int
 */
int Aboost(int identity);

/**
 * @brief    �������һ����
 */
void GenerateCard(char card[]);

int main()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		RandNum[i] = rand() % 13; // ���� 0 �� 12 ֮��������
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
		// ��ʼ������
		char card1[20], card2[20], dealerCard[20];
		// ͣ�Ʊ�־λ
		int stand = 1;
		// ��ȡ��ʼ������
		GenerateCard(card1);
		GenerateCard(card2);
		GenerateCard(dealerCard);
		// �����ʼʱ˫���ĵ���
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
		// ��ҽ׶�
		fflush(stdout);
		char newCard[20];
		while (1 && stand)
		{
			GenerateCard(newCard);
			playerPoints += calculatePoints(newCard, 1);
			// ���������ֹͣ
			if (playerPoints > 21)
			{
				printf("Bust\n");
				fflush(stdout);
				break;
			}
			// �����ж�
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
		// ׯ�ҽ׶�
		// չʾһ����
		printf("dealertime\n");
		fflush(stdout);
		GenerateCard(newCard);
		dealerPoints += calculatePoints(newCard, 0);
		// ׯ�Һ�����Ϊ
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
		// �ж�ʱ����ͨ��A�ӵ����Ŀ���
		playerPoints = Aboost(1);
		// �ж�ʤ��
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
	printf("ʤ����%d ������%d ʤ�ʣ�%.2f%%\n", win, lose, rate);
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