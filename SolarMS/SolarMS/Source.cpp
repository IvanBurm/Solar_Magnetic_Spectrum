#include <cmath>
#include <iostream>
#include <string> // подключаем строки
#include <fstream>
#include <stdlib.h>

using namespace std;

double chislo(string str_2, double* HN, double* nN, double* HS, double* nS)
{
	string str_3, str_4;
	int power = 0, i, j;
	double znachenie = 0;
	znachenie = atof(str_2.c_str());
	if (znachenie > 0)
	{
		*HS = *HS + znachenie;
		*nS = *nS + 1;
	}
	if (znachenie < 0)
	{
		*HN = *HN + znachenie;
		*nN = *nN + 1;
	}
	return (znachenie);

}

void main()
{
	string str;
	fstream fin;
	fin.open("22.txt");
	int i, j, k = 0, m = 0, size_X=0, size_Y=0,L,N;
	string number;
	double znachenie;
	ofstream fout("1_out.txt", std::ios::binary | std::ios::app);
	double  HN = 0, nN = 0, HS = 0, nS = 0, HC = 0, nC = 0, Y = 0, P_iN, P_iS, L_N = 0, L_S = 0, K_N = 0, K_S = 0, EN = 0, ES = 0, SEN, SES;
	while (!fin.eof()) {
		getline(fin, str);
		size_Y++;
		i = str.size();
		j = 1;
		while (j < i)
		{
			while (((int)str[j] != 34) && ((int)str[j] != 44))
			{
				number = number + str[j];
				j++;
			}
			if (number != "")
			{
				size_X++;
			}			
			number = "";
			j++;
		}
		
	}
	fin.close();
	fin.clear();
	size_Y--;
	size_X = size_X / size_Y;
	//cout << size_X <<" "<< size_Y << endl;
	L = size_X;
	N = size_Y;
	double **arr = new double* [size_Y];
	for (int count = 0; count < size_Y; count++)
		arr[count] = new double[size_X];
	arr[0][0] = 153;
	

	fin.open("22.txt");
	while (!fin.eof()) {
		
		getline(fin, str);
		ofstream fout("1_out.txt", std::ios::binary | std::ios::app);
		i = str.size();
		j = 1;
		
		while (j < i)
		{
			//cout << 2 << endl;
			while (((int)str[j] != 34) && ((int)str[j] != 44))
			{
				number = number + str[j];
				j++;
			}
			if (number != "")
			{
				znachenie = chislo(number, &HN, &nN, &HS, &nS);
				fout << znachenie << "\r\n";
				if ((k < L - 1) && (m <= N - 1))
				{
					arr[m][k] = znachenie;
					k++;
					
				}
				else if ((k == L - 1) && (m < N - 1))
				{
					arr[m][k] = znachenie;
					k = 0;
					m++;

				}
				else if ((k == L - 1) && (m == N - 1))
				{
					arr[m][k] = znachenie;
				}

			}
			number = "";
			j++;
		}
		fout.close();
	}
	//cout << arr[0][539] << endl;
	/*cout << arr[1][0] << endl;
	cout << arr[1][539] << endl;
	cout << arr[332][539] << endl;
	system("pause");*/
	//cout << size_Y << endl;// надо на 1 меньше
	nC = nS + nN;
	HC = abs(HN) + abs(HS);
	Y = (abs(HN) - abs(HS)) / HC;
	cout << "HN = " << HN << endl;
	cout << "HS = " << HS << endl;
	cout << "nN = " << nN << endl;
	cout << "nS = " << nS << endl;
	cout << "nC = " << nC << endl;
	cout << "HC = " << HC << endl;
	cout << "Y = " << Y << endl;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < L; j++)
		{
			if (arr[i][j] < 0)
			{
				//cout << arr[i][j] << " ";
				P_iN = arr[i][j] / HN;
				L_N = L_N + j*P_iN; // координаты центров
				K_N = K_N + i*P_iN;// координаты центров
				EN = EN + P_iN*log(1 / P_iN);// структурна энтропи€ магнитного потока северной пол€рности
			}
			if (arr[i][j] > 0)
			{
				//cout << arr[i][j] << " ";
				P_iS = arr[i][j] / HS;
				L_S = L_S + j*P_iS;// координаты центров
				K_S = K_S + i*P_iS;// координаты центров
				ES = ES + P_iS*log(1 / P_iS);// структурна энтропи€ магнитного потока южной пол€рности
			}

		}
	}
	SEN = exp(EN); //эффективна€ площадь потока северной пол€рности
	SES = exp(ES); //эффективна€ площадь потока южной пол€рности
	cout << "L_N = " << L_N << endl;
	cout << "K_N = " << K_N << endl;
	cout << "EN = " << EN << endl;
	cout << "L_S = " << L_S << endl;
	cout << "K_S = " << K_S << endl;
	cout << "ES = " << ES << endl;
	cout << "SEN = " << SEN << endl;
	cout << "SES = " << SES << endl;
	system("pause");

}
