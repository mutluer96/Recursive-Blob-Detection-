#include <iostream>
#include <fstream>
#include<vector>
#include<iomanip>
#include<Windows.h>

using namespace std;

int Blob_Compute(char **, int, int, int, int);
int ada(char**, int*, int, int);
void setpos(int, int);

vector<int> rowSum;
vector<int> colSum;
vector<int> numOfX;

int  colDistanceSum = 0;
int  rowDistanceSum = 0;
int main()
{
	ifstream dosyaOku("blobs1.txt");
	char karakter;
	int row = 0, col = 0;

	dosyaOku >> row >> col;

	int *kacsekil = new int[row*col];

	char **matris = new char*[row];
	for (int i = 0; i < row; i++)
	{
		matris[i] = new char[col];
	}

	if (dosyaOku.is_open()) {

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				dosyaOku.get(karakter);
				if (karakter == '\n')
				{
					dosyaOku.get(karakter);
				}
				if (karakter == 'x')
				{
					matris[i][j] = karakter;
				}
				if (karakter == ' ')
				{
					matris[i][j] = karakter;
				}
			}
		}
		dosyaOku.close();
	}

	int p = 0;
	int p2 = 0;
	int p3 = 0;
	int p4 = 0;

	for (int m = 0; m < row + 4; m++)
	{
		for (int n = 0; n < col + 5; n++)
		{
			if (m == 0)
			{
				if ((n == 0) || (n == 1) || (n == 2) || (n == col + 3) || (n == col + 4))
				{
					cout << " ";
				}
				else
				{
					cout << p;
					p++;
					if (p > 9)
					{
						p = 0;
					}
				}
			}
			else if (m == 1 || m == row + 2)
			{
				if ((n == 0) || (n == 1) || (n == col + 4))
				{
					cout << " ";
				}
				else if ((n == 2) || (n == col + 3))
				{
					cout << "+";
				}
				else
				{
					cout << "-";

				}
			}
			else
			{
				if (n == 0)
				{
					cout << " ";
				}
				else if (n == 1)
				{
					cout << p2;
					p2++;
					if (p2 > 9)
					{
						p2 = 0;
					}
				}
				else if (n == col + 4)
				{
					cout << p3;
					p3++;
					if (p3 > 9)
					{
						p3 = 0;
					}
				}
				else if (n == 2 || n == col + 3)
				{
					cout << "|";
				}
				else
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}

	setpos(3, 2);

	for (int m = 0; m < row; m++)
	{
		for (int n = 0; n < col; n++)
		{
			cout << matris[m][n];
		}

		setpos(3, m + 3);
	}
	cout << endl;
	for (int m = 0; m < col + 5; m++)
	{
		if ((m == 0) || (m == 1) || (m == 2) || (m == col + 3) || (m == col + 4))
		{
			cout << " ";
		}
		else
		{
			cout << p4;
			p4++;
			if (p4 > 9)
			{
				p4 = 0;
			}
		}
	}
	cout << endl;

	int qMain = ada(matris, kacsekil, row, col);

	cout << endl << endl;
	cout << setfill('-');
	cout << setw(7) << left << "+" << setw(13) << left << "+" << setw(10) << left << "+" << setw(14) << left << "+" << "+" << endl;
	cout << setfill(' ');
	cout << setw(7) << right << "|  BLOB|" << setw(13) << right << "NoOfPixels|" << setw(10) << right << "CoM Row|" << setw(14) << right << "CoM Col|" << endl;
	cout << setfill('-');
	cout << setw(7) << left << "+" << setw(13) << left << "+" << setw(10) << left << "+" << setw(14) << left << "+" << "+" << endl;
	for (int q = 0; q < qMain; q++)
	{


		cout << setfill(' ');
		cout << setw(1) << "|" << setw(6) << right << 1+q;
		cout << setw(1) << "|" << setw(12) << right << numOfX[q];
		cout << setw(1) << "|" << setw(9) << right << fixed << setprecision(2) << ((double)rowSum[q] / (double)kacsekil[q]);
		cout << setw(1) << "|" << setw(13) << right << fixed << setprecision(2) << ((double)colSum[q] / (double)kacsekil[q]);
		cout<<setw(1)<<"|"<< endl;
		cout << setfill('-');
		cout << setw(7) << left << "+" << setw(13) << left << "+" << setw(10) << left << "+" << setw(14) << left << "+" << "+" << endl;

	}





	return 0;
}



int Blob_Compute(char **M1, int r, int c, int satir, int sutun)
{

	if (r < 0 || r >= satir || c < 0 || c >= sutun)
	{
		return 0;
	}
	if (M1[r][c] == ' ')
	{
		return 0;
	}
	else
	{
		colDistanceSum = colDistanceSum + c;
		rowDistanceSum = rowDistanceSum + r;
		M1[r][c] = ' ';
		return (1 +
			Blob_Compute(M1, r - 1, c, satir, sutun) +
			Blob_Compute(M1, r, c - 1, satir, sutun) +
			Blob_Compute(M1, r, c + 1, satir, sutun) +
			Blob_Compute(M1, r + 1, c, satir, sutun));
	}

}
int ada(char **M1, int *dizi, int satir, int sutun)
{

	int islandsNumber = 0;
	int size;

	for (int i = 0; i < satir*sutun; i++)
	{
		dizi[i] = 0;
	}


	for (int i = 0; i < satir; i++)
		for (int j = 0; j < sutun; j++)
		{

			size = Blob_Compute(M1, i, j, satir, sutun);

			if (size > 0)
			{
				dizi[islandsNumber] = size;
				numOfX.push_back(size);
				islandsNumber++;
				rowSum.push_back(rowDistanceSum);
				colSum.push_back(colDistanceSum);
				rowDistanceSum = 0;
				colDistanceSum = 0;
			}
		}
	return islandsNumber;
}
void setpos(int x, int y)
{
	HANDLE sth = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(sth, pos);
}
