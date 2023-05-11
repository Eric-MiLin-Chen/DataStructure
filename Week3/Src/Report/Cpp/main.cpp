#include <iostream>
#include <fstream>
#include <string>
#include "BSTest.h"
using namespace std;

int main()
{
    double ansdata[3][3][9][2] = {0}; // 算法 数据类型 数据规模 数据域(比较次数/时间)
    int ASL = 0;
    string DataName[3] = {{"OrderedData"},
                          {"NormalOrderedData"},
                          {"RandomOrderedData"}};
    string fsize[9] = {
        {"32"},
        {"64"},
        {"128"},
        {"256"},
        {"512"},
        {"1024"},
        {"2048"},
        {"4096"},
        {"8192"}};
    int num;
    for (int i = 0; i < 3; i++)
    {
        double compare_sum_BS = 0;
        double compare_sum_FS = 0;
        double compare_sum_IS = 0;
        for (int j = 0; j < 9; j++)
        {
            int size = stoi(fsize[j]);
            int data[size];
            ifstream file("./../../../Data/" + DataName[i] + fsize[j] + ".txt");
            // cout << DataName[i] + fsize[j] + ".txt" << endl;
            for (int i = 0; i < size; i++)
                file >> data[i];
            file.close();
            for (int target = 0; target < 10 * size; target++)
            {
                compare_sum_BS += BinarySearch(data, target, size).compare;
                compare_sum_FS += FibSearch(data, target, size).compare;
                compare_sum_IS += InterpolationSearch(data, target, size).compare;
            }
            ansdata[0][i][j][1] = compare_sum_BS / size;
            ansdata[1][i][j][1] = compare_sum_FS / size;
            ansdata[2][i][j][1] = compare_sum_IS / size;
            compare_sum_BS = 0;
            compare_sum_FS = 0;
            compare_sum_IS = 0;
            for (int target = 0; target < size; target++)
            {
                compare_sum_BS += BinarySearch(data, data[target], size).compare;
                compare_sum_FS += FibSearch(data, data[target], size).compare;
                compare_sum_IS += InterpolationSearch(data, data[target], size).compare;
            }
            ansdata[0][i][j][0] = compare_sum_BS / size;
            ansdata[1][i][j][0] = compare_sum_FS / size;
            ansdata[2][i][j][0] = compare_sum_IS / size;
        }
    }
    for (int f = 0; f < 3; f++)
    {
        cout << "func" << f << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << "   " << DataName[i] << endl;
            for (int d = 0; d < 2; d++)
            {
                cout << "        ";
                for (int j = 0; j < 9; j++)
                {
                    cout << ansdata[f][i][j][d] << " ";
                }
                cout << endl;
            }
        }
    }
    ofstream outfile;
    outfile.open("./../../../Data/file.txt", ios::out);
    for (int f = 0; f < 3; f++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int d = 0; d < 2; d++)
            {
                for (int j = 0; j < 9; j++)
                {
                    outfile << ansdata[f][i][j][d] << " ";
                }
                outfile << "\n";
            }
        }
    }
    outfile.close();
    return 0;
}
